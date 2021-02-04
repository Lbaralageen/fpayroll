
                                          //----------------------------------------------------------------------------
//Borland C++Builder
//Copyright (c) 1987, 1998 Borland International Inc. All Rights Reserved.
//----------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TMain.h"
#include "TMidi.h"

//---------------------------------------------------------------------------
void __fastcall TFChild::ScrollBarHChange(TObject *Sender)
{
    if(  BrushEmf == NULL || SBarV == NULL )
        return;
  {
      TRect area = getSrcRect(0, SBarV->Position);
      if(  BrushEmf->Height < ( area.Bottom - 50 ) ) // check the bottom boundary
      {
          SBarV->Position = SBarV->Position - 1;
          return;
      }
  }
  for(int i = 0; i < (int)lstRect.size(); i++)
  {
		if( lstRect[i].edit )
		{
		  lstRect[i].edit->Visible = false;
		  lstRect[i].edit->Top = lstRect[i].Top;
		  lstRect[i].edit->Left = lstRect[i].Left;
		}else if( lstRect[i].box )
			lstRect[i].box->Visible = false;
  }
  Refresh(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFChild::WPEditKeyPress(TObject *Sender, char &Key)
{


	TWPEdit *edit = dynamic_cast<TWPEdit *>(Sender);
	try
	{
	  if( edit )
	  {
		  TXelm *elm = (TXelm *)edit->Tag;
		  // check jump command - in money field you may jump in next field if press any symbol from line jump
		  String jmp = elm->getAttr(ATTR_TAG_Jump);
		  if( !jmp.IsEmpty() )
			  for(int i = 1; i <= jmp.Length(); i++)
				  if( jmp[i] == Key )
				  {
					Key = '\0';
					WPEditEnter(Sender);
					return;
				  }

		  if( elm->atType == ATTR_TAG_INT || elm->atType == ATTR_TAG_PHONE  || elm->atType == ATTR_TAG_MONEY )
		  {
			  if( !isdigit( Key ) )
			  {
				  if( !( elm->atType == ATTR_TAG_PHONE  && Key == '-') ) // dush is avalaible in phone number
				  {
					  Key = '\0';
					  return;
				  }
			  }
			  if( elm->getAttr(ATTR_TAG_Length) == "1" )
			  {
				  edit->Text = Key;
				  WPEditEnter(Sender);
			  }
		  }else if( elm->atType == ATTR_TAG_DATE )
		  {
			  String text = edit->Text;
			  if( !(isdigit( Key ) || Key == '/') )
			  {
				  Key = '\0';
				  return;
			  }else
			  {
				  int num = text.Length();
				  if( num == 0 && Key == '/' )
				  {
					  Key = '\0';
					  return;
				  }else  if( num > 0 && *text.AnsiLastChar() == '/' && Key == '/' )
				  {
					  Key = '\0';
					  return;
				  }
				  if( num == 1 && Key != '/')    // check the month
				  {
					  int dg1 = text[1] - '0';
					  int dg2 = Key - '0';
					  if( dg1 > 1 || dg2 > 2 )
					  {
						Key = '\0';
						return;
					  }
				  }
				  int ld = text.LastDelimiter("/");
				  int ps = text.Pos("/");
				  if( isdigit(Key) ) // control for number of digits
				  {
					if( ps == ld )
					{
						if( ps == 0 && num > 1 )
						{
							Key = '\0';
							return;
						}else if( ps > 0 && (num-ps) > 1 )
						{
							Key = '\0';
							return;
						}
						if( ps > 0 && (num - ps) > 0  ) // check the day
						{
							int dg1 = text[ps+1] - '0';
							int dg2 = Key - '0';
							if( dg1 > 3 || (dg1 == 3 && dg2 > 1 ) )
							{
							  Key = '\0';
							  return;
							}
						}
					}else          // typing year
					{
					  if( (num-ld) > 3 ) // check the number digits for year
					  {
						  Key = '\0';
						  return;
					  }
					}
				  }
			  }
		  }else
		  {
			  TCheckBox *check = dynamic_cast<TCheckBox *>(Sender);
			  if( check )
			  {
				  check->Checked = !check->Checked;
				  return;
			  }
		  }
	  }
	}catch(...){}
}
//---------------------------------------------------------------------------
void __fastcall TFChild::WPEditShiftTabPressed(TObject *Sender)
{
	shiftKey = true;
}
//---------------------------------------------------------------------------
void __fastcall TFChild::WPEditKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
	flag = true;
      if( Key == '\t' )
      {
          Key = '\0';
          WPEditEnter(Sender);
      }
        if( Key == '\r' )
      {
          Key = '\0';
          WPEditEnter(Sender);
      }
}
//---------------------------------------------------------------------------
void __fastcall TFChild::WPEditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	flag = true;
	switch( Key )
	{
		case VK_TAB : case '\r' :
		{
		  if( Shift.Contains(ssShift) )
			  shiftKey = true;
		  Key = '\0';
		}break;
		case '\b' :
		{
		  TWPEdit *edit = dynamic_cast<TWPEdit *>(Sender);
		  if( edit )
		  {
			TXelm *elm = (TXelm *)edit->Tag;
			if( edit->CPPosition < 2 && elm && elm->atType == ATTR_TAG_INT && elm->getAttr(ATTR_TAG_Length) == 1 )
			{
				if( edit->CPPosition == 1 )   // delete symbol
					edit->Text = "";
				shiftKey = true;
				WPEditEnter(Sender);
			}
		  }
		}break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFChild::WPEditEnter(TObject *Sender)
{
	if( !flag )      // protection from autogeneration of steping
	   return;

	flag = false;

    if( Element ) // resotore settings for perv. element
    {
        TWPEdit *edit = dynamic_cast<TWPEdit *>(Element);
        if( edit && !edit->Transparent )
        {
           edit->Transparent = true;
           edit->Refresh();
        }
    }

    Element = (TWinControl *)Sender;

    TComp focus = lstRect[0];
    for(int i = 0; i < (int)lstRect.size(); i++)
      if( Element == lstRect[i].getPtr() )
      {
          focus = lstRect[i];
          break;
      }

    TComp fedit;
    bool ReviewFlag = false;
    if( !shiftKey ) // set next field
        fedit = getNextField(focus, ReviewFlag);
    else
        fedit = getPrevField(focus, ReviewFlag);

//    TRect area = getSrcRect(SBarH->Position, SBarV->Position);
    TRect area(0, 0, form->Width, form->Height - 28);

//    area.Bottom = area.Bottom - 28;


    if( !CheckRect(fedit.Cur, area ) || ReviewFlag )
      SetVisibleRect(fedit);
    try{
      if( fedit.edit )
      {
        fedit.edit->Visible = true;
        fedit.edit->SetFocus();
        fedit.edit->Transparent = false;
        fedit.edit->Refresh();
        Element = (TWinControl *)fedit.edit;

      }else if( fedit.box )
      {
        fedit.box->Visible = true;
        fedit.box->SetFocus();
        Element = (TWinControl *)fedit.box;
      }
    }catch(...){SetVisibleRect(fedit);}

    shiftKey = false;

  FormMain->BitBtnSaveAs->Enabled = true;
  FormMain->SaveButton->Enabled = true;
  FormMain->SaveMenu->Enabled = true;
}
//---------------------------------------------------------------------------
static bool mouseFlag = false;
void __fastcall TFChild::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if( Key == VK_LBUTTON )
        mouseFlag = true;
}
//---------------------------------------------------------------------------
void __fastcall TFChild::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    mouseFlag = false;
}
//---------------------------------------------------------------------------
void __fastcall TFChild::WPEditClick(TObject *Sender)
{
    if( Sender != NULL )
    {
        TWPEdit *edit = NULL;
        if( Element )
        {
            edit = dynamic_cast<TWPEdit *>(Element);
            if( edit && !edit->Transparent )
            {
               edit->Transparent = true;
               edit->Refresh();
            }
        }

        Element = (TWinControl *)Sender;
		Element->SetFocus();
	}
	TWPEdit *edit = dynamic_cast<TWPEdit *>(Sender);
	if( edit )
	{
	   edit->Transparent = false;
	   edit->Refresh();
	}
}
//---------------------------------------------------------------------------



