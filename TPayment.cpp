//----------------------------------------------------------------------------
//Borland C++Builder
//Copyright (c) 1987, 1998 Borland International Inc. All Rights Reserved.
//----------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TMain.h"

#include "TPayment.h"
//---------------------------------------------------------------------------
#pragma link "OvcBase"
#pragma link "OvcEdCal"
#pragma link "OvcEditF"
#pragma link "OvcEdPop"
#pragma resource "*.dfm"
//TTSetupProfile *TSetupProfile;

static const char *_GUID = "FR_PAY";

//---------------------------------------------------------------------------
__fastcall TFPayment::TFPayment(TComponent* Owner)
	: TFChild(Owner)
{
  Width = 820;
  Height = 630;

  Position = poMainFormCenter;
  WindowState = wsNormal;
  BorderStyle = bsSingle;

  FormMain->loadProvince(ComboProvince, false);
}
//---------------------------------------------------------------------------
void TFPayment::Execute(void)
{
    loadEmpl(lstEmpl);
    ComboBox->Clear();

    map<long, dataEmpl>::iterator i_ptr;
    for( i_ptr = lstEmpl.begin(); i_ptr != lstEmpl.end(); i_ptr++)
    {
        dataEmpl *val = &(*i_ptr).second;
        ComboBox->Items->Add(val->FullName());

    }
    ComboBox->ItemIndex = 0;
    ComboBoxChange(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::PayrollMenuClick(TObject *Sender)
{
    TFPayment *form = NULL;
    if( !CheckForm(_GUID) )
    {
        form = new TFPayment(this);
        form->Caption = _GUID;
        RegisterForm("", form);
    }else
    {
        form = (TFPayment *)getForm(_GUID);
        form->SetFocus();
        form->WindowState = wsNormal;
    }
    if( form )
        form->Execute();
}
//---------------------------------------------------------------------------
void TFPayment::loadEmpl(map<long, dataEmpl> &lst)
{
     lst.clear();

     TADOQuery *qr = base->RemoteQuery;
     String SQLcommand = "SELECT * FROM Employee ;";
     base->_Query(qr, SQLcommand);
     while( !qr->Eof )
     {
        dataEmpl val;

        try
        {
          val.ID = qr->FieldByName("ID")->AsInteger;
          val.FirstName = qr->FieldByName("FirstName")->AsString;
          val.LastName  = qr->FieldByName("LastName")->AsString;
          val.SIN = qr->FieldByName("SIN")->AsInteger;
          long  dts = qr->FieldByName("Hired")->AsInteger;
		  val.Hired   =     getFDate( dts );
          val.Title  = qr->FieldByName("Title")->AsString;
          val.typeJob  = qr->FieldByName("typeJob")->AsBoolean;
          val.Street  = qr->FieldByName("Street")->AsString;
          val.Province  = qr->FieldByName("Province")->AsString;
          val.City  = qr->FieldByName("City")->AsString;
          val.Index  = qr->FieldByName("PostBox")->AsString;
          val.Number  = qr->FieldByName("Nmb")->AsString;
          val.Salary  = qr->FieldByName("Salary")->AsBoolean;
          dts = qr->FieldByName("Prd")->AsInteger;
          val.Period   =     getFDate( dts );
          val.Hour  = qr->FieldByName("Hr")->AsFloat;
          val.EiIns  = qr->FieldByName("EiIns")->AsFloat;
          val.EiNon  = qr->FieldByName("EiNon")->AsFloat;
          val.RPP  = qr->FieldByName("RPP")->AsFloat;
          val.Union  = qr->FieldByName("Unn")->AsFloat;
          val.Alimony  = qr->FieldByName("Alimony")->AsFloat;
          val.Federal  = qr->FieldByName("Federal")->AsFloat;
          val.Provincial  = qr->FieldByName("Provincial")->AsFloat;
          val.AddTax  = qr->FieldByName("AddTax")->AsFloat;
          val.TaxCredit  = qr->FieldByName("TaxCredit")->AsFloat;
          val.ComboCode  = qr->FieldByName("ComboCode")->AsString;
          val.Dpnd  = qr->FieldByName("Dpnd")->AsFloat;
          val.Annual  = qr->FieldByName("Annual")->AsFloat;
        }catch(...){}
        lst[val.ID] = val;
        qr->Next();
     }
     qr->Close();
}
//---------------------------------------------------------------------------
void __fastcall TFPayment::ButtonFirstClick(TObject *Sender)
{
    StepEmpl(STEP_FIRST);
    CopyEmplToForm(CurrentEmpl);
}
//---------------------------------------------------------------------------
void __fastcall TFPayment::ButtonLeftClick(TObject *Sender)
{
    StepEmpl(STEP_LEFT);
    CopyEmplToForm(CurrentEmpl);
}
//---------------------------------------------------------------------------
void __fastcall TFPayment::ButtonRightClick(TObject *Sender)
{
    StepEmpl(STEP_RIGHT);
    CopyEmplToForm(CurrentEmpl);
}
//---------------------------------------------------------------------------
void __fastcall TFPayment::ButtonLastClick(TObject *Sender)
{
    StepEmpl(STEP_LAST);
    CopyEmplToForm(CurrentEmpl);
}
//---------------------------------------------------------------------------
void TFPayment::CopyEmplToForm(dataEmpl &Who)
{
    EditLastName->Text = Who.LastName;     EditFirstName->Text = Who.FirstName;
    EditSIN->Text = Who.getSIN();        EditHired->Date = Who.Hired;
    ComboProvince->ItemIndex = ComboProvince->Items->IndexOf(Who.Province);
    EditNumber->Text = Who.Number;     EditPeriod->Date = Who.Period;
    EditEiNon->Text = Who.EiNon;       EditEiIns->Text = Who.EiIns;
    EditAnnual->Text = Who.Annual;     EditUnion->Text = Who.Union;
    EditRPP->Text = Who.RPP;           EditAlimony->Text = Who.Alimony;
    EditFederal->Text = Who.Federal;   EditProvincial->Text = Who.Provincial;
    EditDpnd->Text = Who.Dpnd;         EditZone->Text =  Who.ComboCode;
    EditTaxCredit->Text = Who.TaxCredit;
}
//---------------------------------------------------------------------------
void __fastcall TFPayment::ComboBoxChange(TObject *Sender)
{
    int idx = ComboBox->ItemIndex;
    map<long, dataEmpl>::iterator i_ptr;
    int i = 0;
    for( i_ptr = lstEmpl.begin(); i_ptr != lstEmpl.end(); i_ptr++, i++)
        if( i == idx )
        {
            CopyEmplToForm((*i_ptr).second);
            break;
        }
}
//---------------------------------------------------------------------------
void __fastcall TFPayment::ButtonCloseClick(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------

