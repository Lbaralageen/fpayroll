//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TMain.h"
#include "TTaxProp.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TMidi"
#pragma resource "*.dfm"
//TFTaxProp *FTaxProp;

static const char *_GUID = "FR_TAX";

//---------------------------------------------------------------------------
__fastcall TFTaxProp::TFTaxProp(TComponent* Owner)
    : TFChild(Owner)
{
  Width = 440;
  Height = 260;
  BorderStyle = bsSingle;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::TaxParameters1Click(TObject *Sender)
{
    if( !CheckForm(_GUID) )
    {
        TFTaxProp* ch = new TFTaxProp(this);
        RegisterForm(_GUID, ch);
    }else
    {
        TFTaxProp *ptr = (TFTaxProp *)getForm(_GUID);
        ptr->SetFocus();
        ptr->WindowState = wsNormal;
    }
}
//---------------------------------------------------------------------------

