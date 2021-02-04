//----------------------------------------------------------------------------
//Borland C++Builder
//Copyright (c) 1987, 1998 Borland International Inc. All Rights Reserved.
//----------------------------------------------------------------------------
//  made by lepsik :)
//  (c) 2001 Waterloo Hydrogeologic, Inc.
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TMain.h"
#include "TFormEdit.h"

#include <wprtfinp.hpp>

#include "TMidi.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
__fastcall TFChild::TFChild(TComponent* Owner)
	: TForm(Owner) , node(NULL), BrushBmp(NULL), koef(1.0),
        printFlag(false), clearFlag(false), initFlag(true), saveFlag(false), saveAsFlag(false), scFlag(false),
        Element(NULL), BrushEmf(NULL), proportion(1.5), FState(wsMaximized), form_code(FORM_NONE), Page(1)
{
    form = (TForm *)Owner;
    DT = Now();
    topDist = 0;
}
//---------------------------------------------------------------------------
/*
~TFChild::TFChild()
{
    int sz = lstElement.size(;
    for(int i = 0; i < sz; i++)
        delete lstElement[i];
}
*/
//---------------------------------------------------------------------------
TRect TComp::Original(void)
{
    TRect result;
//    String name = elm->atName;
    result.Left = atoi( elm->getAttr(ATTR_TAG_Left).Trim().c_str() ) ;
    result.Top = atoi(elm->getAttr(ATTR_TAG_Top).Trim().c_str()) ;

    int height = atoi(elm->getAttr(ATTR_TAG_Height).Trim().c_str()) ;
    if(  height < 10 )
        height = 24;
    result.Bottom = result.Top + height;

    int right = atoi(elm->getAttr(ATTR_TAG_Right).Trim().c_str());
    if( right < 5 )
        right = result.Left + height;

    result.Right = right;

    return result;
}
//---------------------------------------------------------------------------
TRect TComp::Current(void)
{
    TRect result;

    if( edit )
    {
        result.Left = edit->Left;
        result.Top = edit->Top;
        result.Bottom = edit->Top + edit->Height;
        result.Right = edit->Left + edit->Width;
    }else if( box )
        result = box->ClientRect;

    return result;
}
//---------------------------------------------------------------------------
bool CheckRect(TRect &component, TRect &area)
{
    if( area.Left < component.Left && area.Top < component.Top &&
        area.Right > component.Right && area.Bottom > component.Bottom )
        return true;
    else
        return false;
}
//---------------------------------------------------------------------------
TComp TFChild::getNextField(TComp &obj, bool &ReviewFlag)
{
    ReviewFlag = false; // don't refresh screen
    TComp result;
    vecxml lst = obj.elm->Parent->Select(NODE_TAG_Field);
    int i = 0;

    TXelm *nextField = NULL;
    // try to find current node
    for(; i < (int)lst.size(); i++)
        if( obj.elm == lst[i] )
            break;
    int sz = lst.size()-1;
    do
    {
        if( i >= sz )
        {
            ReviewFlag = true;
            i = 0;
            nextField = lst[ i ];
        }else
            nextField = lst[ ++i ];
    }while( nextField->getAttr(ATTR_TAG_ReadOnly) == ATTR_TAG_Yes );

    if( nextField != NULL )
    {
      for(int i=0; i < (int)lstRect.size(); i++)
      {
          TXelm *elm = lstRect[i].elm;
              if( nextField == elm )
                  return lstRect[i];
      }
    }
    return result;
}
//---------------------------------------------------------------------------
TComp TFChild::getPrevField(TComp &obj, bool &ReviewFlag)
{
    ReviewFlag = false; // don't refresh screen
    TComp result;
    vecxml lst = obj.elm->Parent->Select(NODE_TAG_Field);
    int i = 0;
    TXelm *prevField = NULL;
    for(; i < (int)lst.size(); i++)
        if( obj.elm == lst[i] )
            break;
    int sz = lst.size()-1;
    do
    {
        if( i <= 0 )
        {
            return obj;
/*
            ReviewFlag = true;
            i = 0;
            prevField = lst[ i ];
*/
        }else
            prevField = lst[ --i ];
    }while( prevField->getAttr(ATTR_TAG_ReadOnly) == ATTR_TAG_Yes );

    if( prevField != NULL )
    {
      for(int i=lstRect.size()-1; i >= 0; i--)
      {
          TXelm *elm = lstRect[i].elm;
              if( prevField == elm )
                  return lstRect[i];
      }
    }
    return result;
}
//---------------------------------------------------------------------------
static TMetafile *LoadMetaFile(int index)
{
    TMetafile *result = NULL;
    if( index <= 0 )
        return result;
    TResourceStream *ResStream = NULL;
    try
    {
        ResStream = new TResourceStream((int)HInstance, index, RT_RCDATA);
        assert(ResStream);
        result = new TMetafile;
        result->LoadFromStream(ResStream);
    }
    catch(...){}
    delete ResStream;
    return result;
}
//---------------------------------------------------------------------------
static TMetafile *LoadMetaFile(String file)
{
    TMetafile *result = NULL;
    if( file.IsEmpty() )
        return result;
    try
    {
        result = new TMetafile;
        result->LoadFromFile(file);
    }
    catch(...){}
    return result;
}
//---------------------------------------------------------------------------
void __fastcall TFChild::fOnProgress(TObject* Sender, TProgressStage Stage, Byte PercentDone, bool RedrawNow, const Windows::TRect &R, const AnsiString Msg)
{
    Application->ProcessMessages();
}
//---------------------------------------------------------------------------
bool TFChild::LoadPicture(TXelm *page)
{

  String file = page->getAttr(ATTR_TAG_File);
  int ps = file.Pos(".");
  BrushBmp = new Graphics::TBitmap;
  if( file[ps+1] == 'b' )
  {
      BrushBmp->LoadFromFile( file );
  }else
  {
    int idx = atoi(page->atSID.Trim().c_str());
    if( idx < 1 )
        BrushEmf = LoadMetaFile(file);
    else
        BrushEmf = LoadMetaFile(idx);
    BrushEmf->OnProgress = fOnProgress;

    proportion = (double)BrushEmf->Height / (double)BrushEmf->Width;
    BrushEmf->Width = 1500;
    BrushEmf->Height = 1500 * proportion;

    BrushBmp->Width = BrushEmf->Width;
    BrushBmp->Height = BrushEmf->Height;
    BrushBmp->Canvas->Draw(0,0,BrushEmf);
  }

  return true;
}
//---------------------------------------------------------------------------
void __fastcall TFChild::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  FormMain->DelForm(this);
  Action = caFree;
  if( BrushBmp )
  {
      delete BrushBmp;
      BrushBmp = NULL;
  }
  if( BrushEmf )
  {
      delete BrushEmf;
      BrushEmf = NULL;
  }

    FormMain->ButtonPrint->Enabled = false;
    FormMain->PrintMenu->Enabled = false;

    FormMain->BitBtnClear->Enabled = false;
    FormMain->ClearMenu->Enabled = false;

    FormMain->BitBtnInit->Enabled = false;
    FormMain->InitializeMenu->Enabled = false;

    FormMain->SaveButton->Enabled = false;
    FormMain->SaveMenu->Enabled = false;

    FormMain->BitBtnSaveAs->Enabled = false;
    FormMain->SaveAsMenu->Enabled = false;

    FormMain->CheckBoxCketch->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFChild::FormCloseQuery(TObject *Sender,
      bool &CanClose)
{
  CanClose = True;
  if( CanClose )
  {
    int key = mrNo;
    if( FormMain->SaveButton->Enabled )
        key = MessageDlg("Would you like to save changes of form [" + Caption + "] ?",
                       mtConfirmation, TMsgDlgButtons() << mbYes <<  mbNo << mbCancel, 0);

    switch ( key ){
      case mrYes:
          Save();
          FormMain->SaveButton->Enabled = false;
          FormMain->SaveMenu->Enabled = false;
          FormMain->BitBtnSaveAs->Enabled = false;
          break;
      case mrNo:
          break;
      case mrCancel:
      CanClose = False;
          break;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TFChild::ImageMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    if( FormMain->CheckBoxCketch->Checked )
    {
       int _x = srcRect.Left * koef + X;
       FormMain->StatusBar->Panels->Items[1]->Text = "x: " + String(_x);

       int _y = srcRect.Top * koef + Y;
       if( node->Parent->NodeName ==  NODE_TAG_Group )
            _y -= PageControlMidi->Height;
       FormMain->StatusBar->Panels->Items[2]->Text = "Y: " + String(_y);
    }
}
//---------------------------------------------------------------------------
void TFChild::SetVisibleRect(TRect &component)
{
    for(int y = 0; y <= SBarV->Max; y++)
        for(int x = 0; x <= SBarH->Max; x++)
        {
            TRect area = getSrcRect(x, y);
            double koef = (double)form->Width / 1500;
            TRect rect = (TRect)component;
            rect.Left *= koef;
            rect.Top *= koef;
            rect.Right *= koef;
            rect.Bottom *= koef;

            if( CheckRect(rect, area) )
            {
                SBarV->Position = y >= SBarV->Max ? y : y + 1;
                SBarH->Position = 0; // x >= SBarH->Max ? x : x + 1;
                ScrollBarHChange(NULL);
                return;
            }
        }
}
//---------------------------------------------------------------------------
int TFChild::_Width()
{
    return form->Width - SBarV->Width;
}
//---------------------------------------------------------------------------
int TFChild::_Height()
{
    if( SBarH->Visible )
        return form->Height - topDist - SBarH->Height;
    else
        return form->Height - topDist;
}
//---------------------------------------------------------------------------
#define _BLOCK_(p){    double bmp_height = p->Height;\
       double bmp_width = p->Width;\
       double VPos = bmp_height / _Height() * 5 - 5;\
       double HPos = bmp_width / _Width()  * 5 - 5;}\
//---------------------------------------------------------------------------
TRect TFChild::getSrcRect(int Hor, int Vert)
{
    if( BrushBmp )
        _BLOCK_(BrushBmp);
    if( BrushEmf )
        _BLOCK_(BrushEmf);
//       double ostatokV = VPos - bmp_height / _Height();
       int y0 = Vert * _Height() / 5;
       int x0 = Hor * _Width() / 5;
       int y1 = y0 + _Height()/koef;
       int x1 = x0 + _Width()/koef;

      return  Rect(x0, y0, x1, y1);
}
//---------------------------------------------------------------------------
TRect TFChild::DrawImage(void)
{
    if( koef < 0.1 )
        koef = 1.0;

    TGraphic *ptrPic = NULL;

    if( BrushEmf && BrushEmf->Width != Width )
    {
      if( FormMain->CheckBoxCketch->Checked )
          BrushEmf->Width = 1500;
      else
          BrushEmf->Width = form->Width;

      BrushEmf->Height = BrushEmf->Width * proportion;
      BrushBmp->Width = BrushEmf->Width;
      BrushBmp->Height = BrushEmf->Height;
      BrushBmp->Canvas->Draw(0,0,BrushEmf);
    }

    ptrPic = BrushBmp;

    srcRect = Rect(0,0,0,0);
    if( ptrPic == NULL )
        return srcRect;
    try
    {
       double bmp_height = ptrPic->Height;
       double bmp_width = ptrPic->Width;

       double VPos = fabs(bmp_height / _Height() * 5);
       double HPos = fabs(bmp_width / _Width()  * 5);

      if( bmp_height < _Height() )
        SBarV->Visible = false;
      else
      {
        SBarV->Max = VPos;
        SBarV->Visible = true;
      }

      if( bmp_width < _Width() )
        SBarH->Visible = false;
      else
        SBarH->Max = HPos;

      int y0 = SBarV->Position * _Height() / 5;
      int x0 = SBarH->Position * _Width() / 5;

      form->Canvas->Pen->Color = clInfoBk;
      form->Canvas->Pen->Style = psSolid;
      form->Canvas->Rectangle(0, topDist, _Width(), topDist + _Height());

      if( SBarV->Position < SBarV->Max )
      {
        TRect distRect = Rect(0, topDist, _Width(), topDist + _Height());
        srcRect = getSrcRect(SBarH->Position, SBarV->Position);

        form->Canvas->CopyRect(distRect, BrushBmp->Canvas, srcRect);
      }
    }
    catch(...){}
    return srcRect;
}
//---------------------------------------------------------------------------
static bool firstFlag = false;
static bool IniFlag = false;
void __fastcall TFChild::Refresh(TObject *Sender)
{
  if( Height < 10 || Width < 100 || form == NULL || BrushEmf == NULL )
    return;

  if( !firstFlag && !BrushEmf )
  {
	firstFlag = true;
	return;
  }

	SBarH->Visible = FormMain->CheckBoxCketch->Checked;

	if( BrushEmf == NULL )
		koef = (double) form->Width / (double) BrushBmp->Width;
	else
		koef = 1.0;

  IniFlag = true;
  TRect srcdist = DrawImage();


  for(int i = 0; i < (int)lstRect.size(); i++)
  {
	double koef = (double)form->Width / 1500;
	TRect rect = (TRect)lstRect[i];
	rect.Left *= koef;
	rect.Top *= koef;
	rect.Right *= koef;
	rect.Bottom *= koef;
	TXelm *elm = lstRect[i].elm;

	if( CheckRect(rect, srcdist )  ) // check if component inside current rectanle
	{
		char str[20];
		TWPEdit *edit = lstRect[i].edit;
		if( edit && edit->Enabled )
		{
			if( node->getAttr( ATTR_TAG_Visible ) == ATTR_TAG_ReadOnly )
			{
				  if( lstRect[i].edit->Visible )
					  lstRect[i].edit->Visible = false;
				  lstRect[i].edit->Zooming = 150 * koef;
				  lstRect[i].edit->Height = 36 * koef;

				  String color = node->getAttr(ATTR_TAG_Color);
                  SetBkMode(BrushBmp->Canvas, TRANSPARENT);
				  BrushBmp->Canvas->Brush->Color  = color.IsEmpty() ? clInfoBk : StringToColor( color );
				  BrushBmp->Canvas->FillRect(rect);
				  BrushBmp->Canvas->Font->Color = clBlack;
                  String value = lstRect[i].edit->Text;
                  HDC hDC = BrushBmp->Canvas->Handle;
				  BrushBmp->Canvas->TextOut(rect.Left, rect.Top + 2, value);
                  continue;
            }

			if( elm->getAttr(ATTR_TAG_Usage) == ATTR_TAG_View )
			{
			  lstRect[i].edit->Zooming = 150 * koef;
			  lstRect[i].edit->Height = 36 * koef;
			}else
			{
				int _hgt = lstRect[i].Height;
				if( _hgt < 5 )
				  _hgt = 28;
				lstRect[i].edit->Zooming = 100 * koef;
				lstRect[i].edit->Height = 28 * koef;
			}
			if( FormMain->CheckBoxCketch->Checked )
			{
				koef = 1; // editor mode ussualy  doesn't use it
				lstRect[i].edit->Top = topDist + (lstRect[i].Top - srcdist.Top)*koef;
				lstRect[i].edit->Left = (lstRect[i].Left - srcdist.Left)*koef;
				lstRect[i].edit->Width = (lstRect[i].Right - lstRect[i].Left)*koef;
			}else
			{
				lstRect[i].edit->Top = topDist + (lstRect[i].Top*koef - srcdist.Top);
				lstRect[i].edit->Left = (lstRect[i].Left*koef - srcdist.Left);
				lstRect[i].edit->Width = (lstRect[i].Right*koef - lstRect[i].Left*koef);
			}
            if( !lstRect[i].edit->Visible )
                lstRect[i].edit->Visible = true;

		}else if( lstRect[i].box && lstRect[i].box->Enabled )
		{
		  TCheckBox *box  = lstRect[i].box;
		  box->Visible = true;
		  box->Height = lstRect[i].Height * koef;
		  box->Top = topDist + (lstRect[i].Top*koef - srcdist.Top);
		  box->Left = (lstRect[i].Left*koef - srcdist.Left);
		  box->Width = lstRect[i].Height * koef;
		}//else // for only visual page
//			if( node->getAttr( ATTR_TAG_Visible ) == ATTR_TAG_ReadOnly )
//				  BrushBmp->Canvas->TextOut(rect.Left, rect.Top + 5, lstRect[i].edit->Text);
	}else
	{
		if( lstRect[i].edit )
			lstRect[i].edit->Visible = false;
		else if( lstRect[i].box )
			lstRect[i].box->Visible = false;
	}
  }
  if( Element && Element->Visible )
  {
       SetFocus();
	   Element->SetFocus();
  }
}
//---------------------------------------------------------------------------
void __fastcall TFChild::PImageResize(TObject *Sender)
{
    if( node == NULL || !IniFlag || mouseFlag )
        return;
    if( SBarV != NULL && SBarH != NULL )
    {
//      SBarV->Position = 0;
//      SBarH->Position = 0;

      for(int i = 0; i < (int)lstRect.size(); i++)
      {
        if( lstRect[i].edit )
        {
            lstRect[i].edit->Visible = false;
            lstRect[i].edit->Top = lstRect[i].Top;
            lstRect[i].edit->Left = lstRect[i].Left;
        }else if( lstRect[i].box )
        {
            lstRect[i].box->Visible = false;
            lstRect[i].box->Top = lstRect[i].Top;
            lstRect[i].box->Left = lstRect[i].Left;
        }
      }
      Refresh(Sender);
    }
}
//---------------------------------------------------------------------------
bool TFChild::Execute(TXelm *nodePage, long _id)
{
   if( nodePage == NULL )
    return false;
   node = nodePage;

   Visible = true;
   if( node->NodeName == ATTR_TAG_Group )
   {
       PanelMidi->Visible = true;
       PanelMidi->Enabled = true;
       groupNode = node;
       lst = node->Select(NODE_TAG_Item);

       PageControlMidi->MultiLine = true;
       for(int i = 0; i < (int)lst.size(); i++)
       {
            TTabSheet *tab = new TTabSheet(this);
            tab->PageControl = PageControlMidi;
            tab->TabVisible = true;
            tab->Caption = "Page" + String(i + 1);
            tab->Tag = (long)lst[i];
       }

       node = lst[0];
       lst = node->Select(NODE_TAG_Field);
   }else
       lst = node->Select(NODE_TAG_Field);
   int sz = lst.size();
   if( sz <= 0 )
    return false;

   SetNode(node);

   if( _id <= 0L )
       Init();
   else
   {
       LoadFromDB(_id);
       Calc();
   }

   FormMain->ButtonPrint->Enabled = true;
   FormMain->PrintMenu->Enabled = true;
   return true;
}
//---------------------------------------------------------------------------
void __fastcall TFChild::PageControlMidiChange(TObject *Sender)
{
    Calc();

    delete BrushBmp;
    BrushBmp = NULL;
    delete BrushEmf;
    BrushEmf = NULL;

    SBarV->Position = 0;
    SBarH->Position = 0;

    node = (TXelm *)PageControlMidi->ActivePage->Tag;
    assert(node);
    lst = node->Select(NODE_TAG_Field);
    SetNode(node);
    Refresh(Sender);

   FormMain->ButtonPrint->Enabled = true;
   FormMain->PrintMenu->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFChild::FormMouseWheelDown(TObject *Sender,
      TShiftState Shift, TPoint &MousePos, bool &Handled)
{
    if( SBarV != NULL )
      if( SBarV->Position < SBarV->Max )
      {
          TRect area = getSrcRect(0, SBarV->Position + 1);
          if(  BrushEmf->Height > (area.Bottom  - 50 )) // check the bottom boundary
              SBarV->Position = SBarV->Position + 1;
      }
}
//---------------------------------------------------------------------------
void __fastcall TFChild::FormMouseWheelUp(TObject *Sender,
      TShiftState Shift, TPoint &MousePos, bool &Handled)
{
    if( SBarV != NULL )
        if( SBarV->Position > SBarV->Min )
            SBarV->Position = SBarV->Position -1;
}
//---------------------------------------------------------------------------
void __fastcall TFChild::FormClick(TObject *Sender)
{
    if( Element && Element->Visible )
        Element->SetFocus();
    else
        FocusControl(SBarV);
}
//---------------------------------------------------------------------------
void __fastcall TFChild::FormActivate(TObject *Sender)
{
    initFlag = true;

    FormMain->ButtonPrint->Enabled = printFlag;
    FormMain->PrintMenu->Enabled = printFlag;

    FormMain->BitBtnClear->Enabled = clearFlag;
    FormMain->ClearMenu->Enabled = clearFlag;

    FormMain->BitBtnInit->Enabled = initFlag;
    FormMain->InitializeMenu->Enabled = initFlag;

    FormMain->SaveButton->Enabled = saveFlag;
    FormMain->SaveMenu->Enabled = saveFlag;

    FormMain->BitBtnSaveAs->Enabled = saveAsFlag;
    FormMain->SaveAsMenu->Enabled = saveAsFlag;

    FormMain->CheckBoxCketch->Enabled = scFlag;

    if( Element && Element->Visible )
        Element->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFChild::Clear(void)
{
  for(int i = 0; i < (int)lstRect.size(); i++)
	if( lstRect[i].edit )
		lstRect[i].edit->Text = "";
	else if( lstRect[i].box )
		lstRect[i].box->Checked = true;
  Refresh(this);
}
//---------------------------------------------------------------------------
void __fastcall TFChild::FormResize(TObject *Sender)
{
	if( form )
		FState = form->WindowState;
	String name = Caption;
}
//---------------------------------------------------------------------------
void TFChild::SaveAs(void)
{
    TFormEdit *form = new TFormEdit(NULL);
    String name = node->atSName;
    if( node->Parent->NodeName ==  NODE_TAG_Group )
        name = node->Parent->atSName;
    if( form->Execute(name + " - " + Now().DateString()) == mrOk )
    {
        NameRecord = form->EditName->Text.Trim();
        InsertForm(NameRecord);
    }
    delete form;
}
//---------------------------------------------------------------------------


