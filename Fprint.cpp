//----------------------------------------------------------------------------
//Borland C++Builder
//Copyright (c) 1987, 1998 Borland International Inc. All Rights Reserved.
//----------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "graphics.hpp"

#include "TMain.h"

#include "TMidi.h"

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TFChild::SetComponents(TGraphic *bmp)
{
  vector<TComp>::iterator i_ptr;

  TXelm *node = NULL;
  vecxml lst;
  if( PageControlMidi->Visible && PageControlMidi->PageCount > 0 )
  {
      long addr = PageControlMidi->ActivePage->Tag;
      node = (TXelm *)addr;
      if( node )
          lst = node->Select(NODE_TAG_Field);
  }
  for(i_ptr = lstRect.begin(); i_ptr != lstRect.end(); i_ptr++)
  {
    Graphics::TBitmap *ptr = (Graphics::TBitmap *)bmp;
    TComp *val = &(*i_ptr);
    TXelm *elm = val->elm;

    if( node != NULL  )
    {
      for(int i = 0; i < (int)lst.size(); i++)
        if( lst[i] == elm )
        {
            DrawElement(val, ptr);
			break;
		}
	}else
	  DrawElement(val, ptr);
	Application->ProcessMessages();
  }
}
//---------------------------------------------------------------------------
// draw uneditable elements
void TFChild::DrawElement(TComp *val, Graphics::TBitmap *ptr, bool print)
{
	try
	{
	  TRect rect = (TRect)*val;
	  TRect srcrect = TRect(0, 0, (int)(rect.Right-rect.Left), val->Height);
	  String value = " ";
	  TWPEdit *edit = val->edit;
	  TXelm *elm = val->elm;
	  if( edit )
	  {
		 ptr->Canvas->Font->Assign(edit->Font);
		 if( print )
		 {
		   ptr->Canvas->Font->Size = elm->getAttr(ATTR_TAG_Usage) == "View" ? 16 : 14 ;
		   ptr->Canvas->Font->Style << fsBold;
		 }

		 String str = val->elm->getAttr(ATTR_TAG_Space);
		 int space = atoi(str.Trim().c_str());
		 int sz = edit->Text.Length();
		 if( space > 0 )
		 {
			for(int i = 1; i <= sz; i++)
			{
				String  nspc = " ";
				for(int j = 0; j <= space; j++)
					nspc += " ";
				value += String(edit->Text[i]) + " ";
			}
		 }else
			value = edit->Text;
	  }else if( val->box )
		value = val->box->Checked ? "X" : " ";
//      if( print )
//    DrawText( ptr->Canvas->Handle, value.c_str(), value.Length(), &rect, DT_CENTER | DT_VCENTER	| DT_END_ELLIPSIS | DT_MODIFYSTRING | DT_SINGLELINE );
	  String color = val->elm->Parent->getAttr(ATTR_TAG_Color);
      ptr->Canvas->Brush->Color  = color.IsEmpty() ? clWhite : StringToColor( color );
      ptr->Canvas->FillRect(rect);
//      SetBkMode(ptr->Canvas, TRANSPARENT);
	  ptr->Canvas->TextOut(rect.Left, rect.Top, value.Trim());
//      HDC hDC = ptr->Canvas->Handle;
//      DrawText(hDC , value.c_str(), value.Length, &rect, DT_WORDBREAK | DT_CENTER | DT_VCENTER );
//      else      PlayMetafile     TMetafileCanvas
///          ptr->Canvas->TextOut(edit->Left, edit->Top, value.Trim());
  }
	catch(...){}
}
//---------------------------------------------------------------------------
void TFormMain::PrintBitmap(Graphics::TBitmap *ABitmap, String title)
{
	int relHeight, relWidth;

	Screen->Cursor = crHourGlass;

    TPrinter *prn = Printer();
    prn->BeginDoc();
	prn->Title = title;
    if( (ABitmap->Width / ABitmap->Height) > (prn->PageWidth / prn->PageHeight) )
    {
        relWidth  = prn->PageWidth;
        relHeight = MulDiv(ABitmap->Height,  prn->PageWidth, ABitmap->Width);
    }else
    {
        relWidth = MulDiv(ABitmap->Width, prn->PageHeight, ABitmap->Height);
        relHeight = prn->PageHeight;
    }
    prn->Canvas->StretchDraw(Rect(0, 0, relWidth, relHeight), ABitmap);
    prn->EndDoc();

    Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------
void TFormMain::PrintWMF(Graphics::TMetafile *MFile, String title)
{
	int relHeight, relWidth;

	Screen->Cursor = crHourGlass;

	TPrinter *prn = Printer();
	prn->BeginDoc();
	prn->Title = title;
	if( (MFile->Width / MFile->Height) > (prn->PageWidth / prn->PageHeight) )
	{
		relWidth  = prn->PageWidth;
		relHeight = MulDiv(MFile->Height,  prn->PageWidth, MFile->Width);
	}else
    {
        relWidth = MulDiv(MFile->Width, prn->PageHeight, MFile->Height);
        relHeight = prn->PageHeight;
    }
    prn->Canvas->StretchDraw(Rect(0, 0, relWidth, relHeight), MFile);
    prn->EndDoc();

    Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::PrintForm(TFChild *form)
{
    assert(form);
    try
    {

        if( form->BrushBmp )
        {
          Graphics::TBitmap *prnBmp = new Graphics::TBitmap;
          if( form->BrushEmf )
          {
            form->BrushEmf->Width = 1500;
            form->BrushEmf->Height = 1500 * form->proportion;

            prnBmp->Width = form->BrushEmf->Width;
            prnBmp->Height = form->BrushEmf->Height;
            StatusBar->Panels->Items[0]->Text = "Create image...";
            prnBmp->Canvas->Draw(0, 0, form->BrushEmf);
          }

          StatusBar->Panels->Items[0]->Text = "Set values...";
          form->SetComponents(prnBmp);
		  StatusBar->Panels->Items[0]->Text = "Send to printer...";
          PrintBitmap(prnBmp, form->Caption);
          delete prnBmp;
          StatusBar->Panels->Items[0]->Text = "Done.";
        }
    }
    catch(...){}
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::PrintFormWMF(TFChild *form)
{
    assert(form);
    try
    {
          TMetafile *prnWmf = new TMetafile;

            form->BrushEmf->Width = 1500;
            form->BrushEmf->Height = 1500 * form->proportion;

            prnWmf->Width = form->BrushEmf->Width;
            prnWmf->Height = form->BrushEmf->Height;
//            prnWmf->Canvas->CopyRect(0, 0, form->BrushEmf);

          form->SetComponents(prnWmf);
          PrintWMF(prnWmf, form->Caption);
          delete prnWmf;
    }
    catch(...){}
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonPrintClick(TObject *Sender)
{
	if( PrintDialog->Execute() )
    {
	  ButtonPrint->Enabled = false;
	  PrintMenu->Enabled = false;
	  TFChild *form = dynamic_cast<TFChild *>(this->ActiveMDIChild);
	  if( form->form_code == FORM_PIC )
      {
          if( form->PageControlMidi->Visible && form->PageControlMidi->PageCount > 0 )
          {
              TTabSheet *saveTab = form->PageControlMidi->ActivePage;
              for(int i = 0; i < form->PageControlMidi->PageCount; i++)
              {
                form->PageControlMidi->ActivePage = form->PageControlMidi->Pages[i];
                form->PageControlMidiChange(Sender);
                
                PrintForm(form);
              }
              form->PageControlMidi->ActivePage = saveTab;
          }else
    		  PrintForm(form);
      }
	  ButtonPrint->Enabled = true;
	  PrintMenu->Enabled = true;
	  form->Refresh(Sender);
	  form->Refresh(Sender);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::PrintAllClick(TObject *Sender)
{
	if( PrintDialog->Execute() )
	{
	  ProgressBar->Position = 0;
	  ProgressBar->Max = MDIChildCount;
	  for(int i = 0; i < MDIChildCount; i++)
	  {
			TFChild *form = dynamic_cast<TFChild *>(MDIChildren[i]);
			if( form->form_code == FORM_PIC )
				PrintForm(form);
			ProgressBar->Position = i;
	  }
	  ProgressBar->Position = 0;
	}
}
//---------------------------------------------------------------------------
// draw uneditable elements
void TFChild::DrawElementMetaFile(TComp *val, Graphics::TMetafile *ptr)
{
	assert(ptr);
	try
	{
		TMetafileCanvas *TMCanvas = &TMetafileCanvas( ptr, 0 );

	  TRect rect = (TRect)*val;
	  TRect srcrect = TRect(0, 0, (int)(rect.Right-rect.Left), val->Height);
	  String value = " ";
	  TWPEdit *edit = val->edit;
	  TXelm *elm = val->elm;
	  if( elm && edit )
	  {
		 TMCanvas->Font->Assign(edit->Font);

		 String str = val->elm->getAttr(ATTR_TAG_Space);
		 int space = atoi(str.Trim().c_str());
		 int sz = edit->Text.Length();
		 if( space > 0 )
		 {
			for(int i = 1; i <= sz; i++)
			{
				String  nspc = " ";
				for(int j = 0; j <= space; j++)
					nspc += " ";
				value += String(edit->Text[i]) + " ";
			}
		 }else
			value = edit->Text;
	  }else if( val->box )
		value = val->box->Checked ? "X" : " ";
//      if( print )

	HDC ptt =   (void *) ptr->Handle;
	int ln = value.Length();
	int tt = DrawText(ptt , value.c_str(), ln, &rect, DT_CENTER | DT_VCENTER	| DT_END_ELLIPSIS | DT_MODIFYSTRING | DT_SINGLELINE );
//		  TMCanvas->TextOut(rect.Left, rect.Top, value.c_str());


//           DrawText(hDC , value.c_str(), value.Length, &rect, DT_WORDBREAK | DT_CENTER | DT_VCENTER );
//      else      PlayMetafile     TMetafileCanvas
///          ptr->Canvas->TextOut(edit->Left, edit->Top, value.Trim());
  }
	catch(...){}
}
//---------------------------------------------------------------------------


