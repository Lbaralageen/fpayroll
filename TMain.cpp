//----------------------------------------------------------------------------
//Borland C++Builder
//Copyright (c) 1987, 1998 Borland International Inc. All Rights Reserved.
//----------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TMain.h"
#include <Printers.hpp>
#include "about.h"
#include "Screen.h"
//---------------------------------------------------------------------------
#pragma link "XmlObjModel"
#pragma link "XmlParser"
#pragma link "XmlObjModel"
#pragma link "XmlParser"
#pragma link "WPDefs"
#pragma link "WPPanel"
#pragma link "WPTbar"
#pragma link "WPTCtrl"
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::About1Click(TObject *Sender)
{
  TAboutBox* AboutBox = new TAboutBox(this);
  AboutBox->ShowModal();
  delete AboutBox;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ArrangeIcons1Click(TObject *Sender)
{
  ArrangeIcons();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::CascadeMenuClick(TObject *Sender)
{
  for(int i = 0; i < MDIChildCount; i++)
      MDIChildren[i]->WindowState = wsNormal	;
  this->ActiveMDIChild->WindowState = wsNormal	;
  Cascade();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Close1Click(TObject *Sender)
{
  if (ActiveMDIChild != NULL)
    this->ActiveMDIChild->Close();

  if( MDIChildCount <= 0 )
  {
      CloseMenu->Enabled = false;
      CloseAll->Enabled = false;
      ClearMenu->Enabled = false;
      InitializeMenu->Enabled = false;
      PrintMenu->Enabled = false;
      PrintAll->Enabled = false;
      SaveButton->Enabled = false;
      SaveMenu->Enabled = false;
      BitBtnSaveAs->Enabled = false;
      BitBtnClear->Enabled = false;
      BitBtnInit->Enabled = false;
      ButtonPrint->Enabled = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::CloseAllClick(TObject *Sender)
{
    CloseAllWMenuClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
  Application->OnHint = ShowHint;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::TileHorizClick(TObject *Sender)
{
  TileMode = tbHorizontal;
  Tile();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::WindowMenuClick(TObject *Sender)
{
  TileVert->Enabled               = (ActiveMDIChild != NULL);
  TileHoriz->Enabled   = (ActiveMDIChild != NULL);
  CascadeMenu->Enabled            = (ActiveMDIChild != NULL);
  CloseAllWMenu->Enabled       = (ActiveMDIChild != NULL);
  MinimazeMenu->Enabled       = (ActiveMDIChild != NULL);
  MinimazeAllMenu->Enabled       = (ActiveMDIChild != NULL);
}
//---------------------------------------------------------------------
void __fastcall TFormMain::ShowHint(TObject *Sender)
{
  StatusBar->Panels->Items[0]->Text = Application->Hint;
}
//---------------------------------------------------------------------
void __fastcall TFormMain::TileVertClick(TObject *Sender)
{
  TileMode = tbVertical;
  Tile();
}
//---------------------------------------------------------------------------
bool TFormMain::CheckForm(String obj)
{
    if( obj.IsEmpty() )
        return false;

    map<String, TFChild *>::iterator i_ptr;
    for( i_ptr = ListForms.begin(); i_ptr != ListForms.end(); i_ptr++)
        if( (*i_ptr).first == obj )
            return true;

    return false;
}
//---------------------------------------------------------------------------
TFChild *TFormMain::getForm(String obj)
{
    return ListForms[obj];
}
//---------------------------------------------------------------------------
void TFormMain::DelForm(TFChild *obj)
{
    int cnt = WindowMenu->Count;
    for( int i = 0; i < cnt; i++ )
    {
        TMenuItem *ptr = WindowMenu->Items[ i ];
        if( ptr->Tag == (long)obj )
        {
            WindowMenu->Delete(i);
            break;
        }
    }

    map<String, TFChild *>::iterator i_ptr;
    for( i_ptr = ListForms.begin(); i_ptr != ListForms.end(); i_ptr++)
        if( (*i_ptr).second == obj )
        {
            ListForms.erase((*i_ptr).first);
            break;
        }
}
//---------------------------------------------------------------------------
String DelSymbol(String path, char chr)
{
  int ps = path.Pos(chr);
  int ln = path.Length();
  if( ln < 3 )
    return path;
  if( ps > 0 )
  {
     if( ps == 1 )
        path = path.SubString(2, ln);
     else
     {
        String left  = path.SubString(1, ps-1);
        String right = path.SubString(ps+1, ln);
        path = left + right;
     }
  }
  return path;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::OpenWindowsMenu(TObject *Sender)
{
//  String Name = DelSymbol(((TMenuItem *)Sender)->Caption, '&');
  String Name = ((TMenuItem *)Sender)->Name;
  TFChild *form = (TFChild *)((TMenuItem *)Sender)->Tag;
  form->WindowState = wsNormal;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::CloseAllWMenuClick(TObject *Sender)
{
  for(int i = 0; i < MDIChildCount; i++)
      MDIChildren[i]->Close();
  this->ActiveMDIChild->Close();

  if( MDIChildCount <= 0 )
  {
      CloseMenu->Enabled = false;
      CloseAll->Enabled = false;
      ClearMenu->Enabled = false;
      InitializeMenu->Enabled = false;
      PrintMenu->Enabled = false;
      PrintAll->Enabled = false;
      SaveButton->Enabled = false;
      SaveMenu->Enabled = false;
      BitBtnSaveAs->Enabled = false;
      BitBtnClear->Enabled = false;
      BitBtnInit->Enabled = false;
      ButtonPrint->Enabled = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MinimazeMenuClick(TObject *Sender)
{
  this->ActiveMDIChild->WindowState = wsMinimized;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::MinimazeAllMenuClick(TObject *Sender)
{
  this->ActiveMDIChild->WindowState = wsMinimized;
  for(int i = 0; i < MDIChildCount; i++)
      MDIChildren[i]->WindowState = wsMinimized;
  this->ActiveMDIChild->WindowState = wsMinimized;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Exit1Click(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
void TFormMain::loadProvince(TComboBox *cbox, bool flag)
{
    assert(cbox);
    vecxml lst = dom->root->Select0(NODE_TAG_Province)->Select(NODE_TAG_Item);
    for(int i = 0; i < (int)lst.size(); i++)
        if( flag )
            cbox->Items->Add(lst[i]->atName);
        else
            cbox->Items->Add(lst[i]->atSName);
    cbox->ItemIndex = 0;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::BitBtnInitClick(TObject *Sender)
{
    try
    {
        TFChild *form = dynamic_cast<TFChild *>(this->ActiveMDIChild);
        if( form )
            form->Init();
        else
            BitBtnInit->Enabled = false;
    }
    catch(...){}
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::BitBtnClearClick(TObject *Sender)
{
    try
    {
        TFChild *form = dynamic_cast<TFChild *>(this->ActiveMDIChild);
        if( form )
            form->Clear();
        else
        {
            BitBtnClear->Enabled = false;
            ClearMenu->Enabled = false;
        }
    }
    catch(...){}
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SaveButtonClick(TObject *Sender)
{
    try
    {
        TFChild *form = dynamic_cast<TFChild *>(this->ActiveMDIChild);
        if( form )
            form->Save();
        SaveButton->Enabled = false;
        SaveMenu->Enabled = false;
        BitBtnSaveAs->Enabled = false;
    }
    catch(...){}
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::BitBtnSaveAsClick(TObject *Sender)
{
    try
    {
        TFChild *form = dynamic_cast<TFChild *>(this->ActiveMDIChild);
        if( form )
            form->SaveAs();
        else
            BitBtnSaveAs->Enabled = false;
    }
    catch(...){}
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::CheckBoxCketchClick(TObject *Sender)
{
    try
    {
        TFChild *form = dynamic_cast<TFChild *>(this->ActiveMDIChild);
        if( form )
            form->Refresh(Sender);
        else
            CheckBoxCketch->Enabled = false;
    }
    catch(...){}
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    if( FormScreen->Enabled )
    {
        FormScreen->ShowModal();
        FormScreen->Enabled = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Contents1Click(TObject *Sender)
{
    Application->HelpContext(0);
//    Application->HelpCommand(HELP_CONTENTS, 22);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Index1Click(TObject *Sender)
{
    Application->HelpCommand(HELP_FINDER, 0);
}
//---------------------------------------------------------------------------





