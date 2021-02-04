//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Screen.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormScreen *FormScreen;
//---------------------------------------------------------------------------
__fastcall TFormScreen::TFormScreen(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormScreen::ImageClick(TObject *Sender)
{
    Close();    
}
//---------------------------------------------------------------------------
void __fastcall TFormScreen::ButtonOKClick(TObject *Sender)
{
    Close();    
}
//---------------------------------------------------------------------------

