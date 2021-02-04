
                                          //----------------------------------------------------------------------------
//Borland C++Builder
//Copyright (c) 1987, 1998 Borland International Inc. All Rights Reserved.
//----------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TMain.h"

#include "TMidi.h"

//---------------------------------------------------------------------------
void TFChild::UnProcessData(TWPEdit *Tyear, TWPEdit *Tmonth, TWPEdit *Tday, bool flag)
{
    if( flag ) // for unoptional documents
         if( (Tyear->Text.IsEmpty() && Tmonth->Text.IsEmpty() && Tday->Text.IsEmpty()) )
            return;
    // Fill date from DB
	long dt = atol(Tyear->Text.c_str());
	unsigned short year, month, day;
	getFDate(dt).DecodeDate( &year, &month, &day );
    if( year <= 0 || year > 2100 )
        Tyear->Text = "";
    else
        Tyear->Text = year;
    if( month <= 0 || month > 12 )
        Tmonth->Text = "";
    else
        Tmonth->Text = month;
    if( day <= 0 || day > 31 )
        Tday->Text = "";
    else
        Tday->Text = day;
}
//---------------------------------------------------------------------------
bool TFChild::ProcessData(int &Ptryear, TWPEdit *Tyear, TWPEdit *Tmonth, TWPEdit *Tday, bool flag)
{
    if( flag ) // for unoptional documents
         if( (Tyear->Text.IsEmpty() && Tmonth->Text.IsEmpty() && Tday->Text.IsEmpty()) )
            return false;
   Ptryear =  Tyear->Text.ToInt();
	int oldYear;
	try
	{
	  // process Birth Date
	  Word Year = atoi(Tyear->Text.c_str());
	  oldYear = Year;
	  Word Month  = atoi(Tmonth->Text.c_str());
	  Word Day = atoi(Tday->Text.c_str());
	  if( Day == 0 || Month == 0 || Year == 0 )
	  {
		unsigned short year, month, day;
		Now().DecodeDate( &year, &month, &day );
		Tyear->Text = year;
		Tday->Text = year;
		Tmonth->Text = year;
		if( Day == 0 )
			Tday->Text = day;
		if( Month == 0 )
			Tmonth->Text = month;
		if( Year == 0 )
			Tyear->Text = year;
		ShowMessage("Wrong Date!");
		WPEditClick(Tyear);
		return true;
	  }else
	  {
		  TDateTime dts = EncodeDate(Year, Month, Day);
		  Tyear->Text = getFDate( dts );
	  }
	}catch(...){
		ShowMessage("Wrong Date!");
		WPEditClick(Tyear);
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------
TWPEdit *TFChild::NextEdit(TXelm *node)
{
    assert(node);
    TXelm *nextNode = (TXelm *)node->NextSibling;
    // to process all fields with type 'Money'
    vector<TComp>::iterator j_ptr, i_ptr;
    for(j_ptr = lstRect.begin(); j_ptr != lstRect.end(); j_ptr++)
    {
        TComp *val = &(*j_ptr);
        if( val->elm == nextNode )
        {
            TWPEdit *editSender = val->edit;
            return editSender;
        }
    }
    return NULL;
}
//---------------------------------------------------------------------------
void TFChild::ProcessMoney(void)
{
    // to process all fields with type 'Money'
    vector<TComp>::iterator j_ptr, i_ptr;
    for(j_ptr = lstRect.begin(); j_ptr != lstRect.end(); j_ptr++)
    {
        TComp *val = &(*j_ptr);
        TWPEdit *editSender = val->edit;                      
        if( editSender )
        {
          TXelm *elm = (TXelm *)editSender->Tag;
          if( elm != NULL )
          {
              if( elm->atType == ATTR_TAG_MONEY )
              {
                  int drop = atol(NextEdit(elm)->Text.c_str());
                  float drp = ((float)drop/100);
                  float result = (float)atol(editSender->Text.c_str()) + drp;
                  editSender->Text = result;
              }
          }
        }
    }
}
//---------------------------------------------------------------------------
void TFChild::UnProcessMoney(void)
{
    // to unprocess all fields with type 'Money'
    vector<TComp>::iterator j_ptr, i_ptr;
    for(j_ptr = lstRect.begin(); j_ptr != lstRect.end(); j_ptr++)
    {
        TComp *val = &(*j_ptr);
        TWPEdit *editSender = val->edit;
        if( editSender )
        {
          TXelm *elm = (TXelm *)editSender->Tag;
          if( elm != NULL )
          {
              if( elm->atType == ATTR_TAG_MONEY )
              {
                  long vals = atol(editSender->Text.Trim().c_str());
                  if( vals == 0L )
                      editSender->Text = "";
                  else
                      editSender->Text = vals;
              }
          }
        }
    }
}
//---------------------------------------------------------------------------
void TFChild::LoadProcessMoney(void)
{
    // to unprocess all fields with type 'Money'
    vector<TComp>::iterator j_ptr, i_ptr;
    for(j_ptr = lstRect.begin(); j_ptr != lstRect.end(); j_ptr++)
    {
        try
        {
		  TComp *val = &(*j_ptr);
          TXelm *elm = (TXelm *)val->elm;
          if( elm != NULL )
          {
              if( elm->atType == ATTR_TAG_MONEY )
              {
                  TWPEdit *editSender = (TWPEdit *)val->edit;
                  if( editSender )
                  {
					  double vl = atof( editSender->Text.c_str() );
                      long whole = (long)vl;
                      double drop =  vl - (double)whole;
                      if( whole == 0L )
                          editSender->Text = "";
                      else
                          editSender->Text = whole;
                      int dp = ceil(1000.0 * drop);
                      dp /= 10;
                      if( dp == 0 )
                          NextEdit(elm)->Text = "";
                      else
                      {
                          if( dp < 10 )
                              NextEdit(elm)->Text = String("0") + dp;
                          else
                              NextEdit(elm)->Text = dp;
                      }
                  }
              }
          }
        }catch(...){}
    }
}
//---------------------------------------------------------------------------
// set list of components from from
void TFChild::SetForm(TForm *_form)
{
    try
    {
      SBarV->Position = 0;
      SBarV->Visible = true;
	  SBarV->OnChange = ScrollBarHChange;

      SBarH->Visible = true;
      SBarH->OnChange = ScrollBarHChange;
      SBarH->Position = 0;

      form = _form;
      form->WindowState = wsMaximized;
      FState = wsMaximized;
      int rs = form->Width;
      form->OnResize = PImageResize;
      form->OnPaint = Refresh;
      form->OnClose = FormClose;
      form->OnMouseMove = ImageMouseMove;
      form_code = FORM_PIC;

      FormMain->ProgressBar->Position = 0;
      register int sz = form->ComponentCount;
      FormMain->ProgressBar->Max = sz;
      for(int i = 0; i < sz; i++)
	  {
		 try
		 {
			TWPEdit *tedit = dynamic_cast<TWPEdit *>(form->Components[i]);
			if( tedit )
			{
				TComp val;
				TWPFont *font = tedit->Font;
				font->Size = 14;
				tedit->Height = 28;
//                val.edit->SetDefaultFont( font );
				val.edit = tedit;
				val.edit->ReadOnly = false;
				val.edit->Transparent = true;

				val.edit->Color = clInfoBk;
				val.edit->TabStop = false;
				val.edit->WPToolBar = FormMain->WPToolBar;
				val.edit->WantTabs = false;
				val.edit->Ctl3D = false;
                val.edit->ViewOptions << wpUseDoubleBuffer;
                val.edit->BorderStyle = bsNone;
                val.edit->UseRightToLeftAlignment();
                val.edit->Enabled = false;
                lstRect.push_back(val);
            }
            TCheckBox *check = dynamic_cast<TCheckBox *>(form->Components[i]);
            if( check && (check->Name != String("CheckBox")) )
            {
                TComp val;
                val.box = check;
                val.box->Caption = " ";
                val.box->Color = clWhite;
                val.box->OnKeyPress = WPEditKeyPress;
                val.box->OnKeyUp = WPEditKeyUp;
                val.box->TabStop = false;
                val.box->OnKeyDown = WPEditKeyDown;
                val.box->OnEnter    = WPEditEnter;
                val.box->Enabled = true;
                lstRect.push_back(val);
			}
         }catch(...)
         {
           ShowMessage("Error in SetNode");
		 }
         FormMain->ProgressBar->Position = i;
      }
    }catch(...)
    {
       ShowMessage("Error in SetNode");
    }
  FormMain->ProgressBar->Position = 0;

  scFlag = saveAsFlag = printFlag = initFlag = clearFlag = saveFlag = true;
  FormMain->BitBtnInit->Enabled = true;
}
//---------------------------------------------------------------------------
void TFChild::SetNode(TXelm *nodePage)
{
	assert(nodePage);
	LoadPicture(nodePage);

//	String color = "0x" + FormMain->Edit1->Text;
	String color = nodePage->getAttr(ATTR_TAG_Color);
	form->Color  = color.IsEmpty() ? clWhite : StringToColor( color );


	vector<TComp>::iterator i_ptr;
	int i = 0;
	mapRect.clear();
	for(i_ptr = lstRect.begin(); i_ptr != lstRect.end(); i_ptr++)
	{
		TComp *val = &(*i_ptr);
		try
		{
		  String name = val->getName();
		  TXelm *elm = nodePage->FindName( name );
		  if( elm != NULL )
		  {
			  // for only visual page
//			  if( node->getAttr( ATTR_TAG_Visible ) == ATTR_TAG_ReadOnly )
//			  	return;
//				  DrawElementMetaFile(val, BrushEmf);
				  
			  int tab_order = elm->Parent->ChildNodes->IndexOf(elm);
              
              String name = elm->atName;
              val->elm = elm;
              if( val->edit )
              {
                val->edit->Tag = (long)elm;
				val->edit->Enabled = true;
                val->edit->Visible = false;
				val->edit->Height = 27  ;
				val->edit->ReadOnly = elm->getAttr(ATTR_TAG_ReadOnly) == ATTR_TAG_Yes;
                val->edit->TabOrder = val->edit->ReadOnly ? 0 : tab_order;
                val->edit->TabStop = false;
				if( val->edit->ReadOnly )
				{
				  val->edit->OnKeyPress = NULL;
				  val->edit->OnKeyUp = NULL;
				  val->edit->OnKeyDown = NULL;
				  val->edit->ShiftTabPressed = NULL;
				  val->edit->OnEnter    = NULL;
				  val->edit->OnClick    = NULL;
				}else
				{
				  val->edit->OnKeyPress = WPEditKeyPress;
				  val->edit->OnKeyUp = WPEditKeyUp;
				  val->edit->OnKeyDown = WPEditKeyDown;
				  val->edit->ShiftTabPressed = WPEditShiftTabPressed;
				  val->edit->OnEnter    = WPEditEnter;
				  val->edit->OnClick    = WPEditClick;
				}
				val->edit->MaxLength = atoi(elm->getAttr(ATTR_TAG_Length).c_str());
				val->edit->ShowHint = true;
				String hint = elm->getAttr(ATTR_TAG_Hint);
				val->edit->Hint = hint.IsEmpty() ? name : hint;
				// + " - Zoom : " + String(val->edit->Zooming) + "-L:" + String(val->Left)+ "-R:" + String(val->Right);
			  }else if( val->box )
			  {
				val->box->Checked = false;
				val->box->TabOrder = tab_order;
			  }
			  val->Left = elm->getAttr(ATTR_TAG_Left).ToInt();
			  val->Top = elm->getAttr(ATTR_TAG_Top).ToInt();
			  val->Height = elm->getAttr(ATTR_TAG_Height).ToInt();
			  val->Right = atoi(elm->getAttr(ATTR_TAG_Right).Trim().c_str());
              if( val->Right <= 0 )  // this for checkboxes
                val->Right = val->Left + val->Height;
              val->Bottom = val->Top + val->Height;

              mapRect[ tab_order ] = *val;
          }else
              if( val->edit )
              {
                val->edit->Enabled = false;
                val->edit->Visible = false;
              }
        }catch(...)
        {
            ShowMessage("Error in SetNode");
        }
    }
    topDist = PageControlMidi->PageCount > 0 ? PanelMidi->Top + PanelMidi->Height : 0;
    if( Element == NULL )
    {
        map<int, TComp>::iterator i_ptr;
        for(i_ptr = mapRect.begin(); i_ptr != mapRect.end(); i_ptr++)
        {
            TWPEdit *edit = (TWPEdit *)(*i_ptr).second.edit;
            if( edit) // find first edit element
            {
                edit->Transparent = false;
                Element = (*i_ptr).second.getPtr();
                break;
            }
        }
	}
    if( Element->Visible && Element->Enabled )
    {
        WPEditClick(NULL);
    }
    FState = wsMaximized;
}
//---------------------------------------------------------------------------
