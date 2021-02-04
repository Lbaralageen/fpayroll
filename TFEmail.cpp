//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TMain.h"
#include "TFEmail.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "WPDefs"
#pragma link "WPPrint"
#pragma link "WPRich"
#pragma link "WpWinCtr"
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
__fastcall TFEmail::TFEmail(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
int TFEmail::Execute(void)
{
    return ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SendEmailMenuClick(TObject *Sender)
{
    TFEmail *form = new TFEmail(NULL);
    form->Execute();
    delete form;
}
//---------------------------------------------------------------------------




