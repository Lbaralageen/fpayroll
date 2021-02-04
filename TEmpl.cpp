//----------------------------------------------------------------------------
//Borland C++Builder
//Copyright (c) 1987, 1998 Borland International Inc. All Rights Reserved.
//----------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TMain.h"

#include "TEmpl.h"
//---------------------------------------------------------------------------
#pragma link "OvcBase"
#pragma link "OvcEdCal"
#pragma link "OvcEditF"
#pragma link "OvcEdPop"
#pragma resource "*.dfm"

static const char *_GUID = "FR_EMPL";

dataEmpl CurrentEmpl;

//---------------------------------------------------------------------------
__fastcall TTEmploees::TTEmploees(TComponent* Owner)
	: TFChild(Owner)
{
  Width = 630;
  Height = 530;

  BorderStyle = bsSingle;
  Position = poMainFormCenter;
  WindowState = wsNormal;

  saveFlag = clearFlag = true;
  ComboProvince->Clear();
  FormMain->loadProvince(ComboProvince);
  FormMain->BitBtnSaveAs->Enabled = false;
  FormMain->SaveButton->Enabled = false;
  FormMain->SaveMenu->Enabled = false;

  vecxml lst = dom->Select(NODE_TAG_Code)->Select(NODE_TAG_Item);
  for(int i = 0; i < (int)lst.size(); i++)
    ComboCode->Items->Add(lst[i]->atName);
}
//---------------------------------------------------------------------------
void TTEmploees::Save(void)
{
    ButtonPostClick(NULL);
}
//---------------------------------------------------------------------------
void TTEmploees::Execute(bool pb)
{
//    MainForm->RegisterForm(_GUID, this);
//    SelectPage(pb);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::EmployessMenuClick(TObject *Sender)
{
    if( !CheckForm(_GUID) )
    {
        TTEmploees* ch = new TTEmploees(this);
        RegisterForm(_GUID, ch);
    }else
    {
        TTEmploees *ptr = (TTEmploees *)getForm(_GUID);
        ptr->SetFocus();
        ptr->WindowState = wsNormal;
    }
}
//---------------------------------------------------------------------------
void __fastcall TTEmploees::Clear(void)
{
    CurrentEmpl.Clear();

    EditLast->Text = " ";
    EditFirst->Text = " ";
    EditSIN->Text = " ";
    EditHired->Text = "";
    EditTitle->Text = " ";
    ComboProvince->ItemIndex = -1;
    EditAddress->Text = " ";
    EditCity->Text = " ";
    EditPostBox->Text = " ";
    EditNumber->Text = " ";
    EditPeriod->Text = "";
    EditHour->Text = 0L;
    EditEiIns->Text = " ";
    EditEiNon->Text = " ";
    EditRPP->Text = " ";
    EditUnion->Text = " ";
    EditAlimony->Text = " ";
    EditFederal->Text = " ";
    EditAddTax->Text = " ";
    EditProvincial->Text = " ";
    EditTaxCredit->Text = " ";
    ComboCode->ItemIndex = -1;
    EditDpnd->Text = " ";
    EditAnnual->Text = " ";
}
//---------------------------------------------------------------------------
void TTEmploees::CopyEmplToForm(dataEmpl &Who)
{
    EditLast->Text = Who.LastName;     EditFirst->Text = Who.FirstName;
    EditSIN->Text = Who.getSIN();        EditHired->Date = Who.Hired;
    EditTitle->Text = Who.Title;       EditCity->Text = Who.City;
    ComboProvince->ItemIndex = ComboProvince->Items->IndexOf(Who.Province);
    EditAddress->Text = Who.Street;    EditPostBox->Text = Who.Index;
    EditNumber->Text = Who.Number;     EditPeriod->Date = Who.Period;
    EditHour->Text = Who.Hour;         EditEiIns->Text = Who.EiIns;
    EditEiNon->Text = Who.EiNon;       EditRPP->Text = Who.RPP;
    EditUnion->Text = Who.Union;       EditAlimony->Text = Who.Alimony;
    EditAddTax->Text = Who.AddTax;
    EditFederal->Text = Who.Federal;   EditProvincial->Text = Who.Provincial;
    EditTaxCredit->Text = Who.TaxCredit;   ComboCode->ItemIndex = ComboCode->Items->IndexOf(Who.ComboCode);
    EditDpnd->Text = Who.Dpnd;         EditAnnual->Text = Who.Annual;
}
//---------------------------------------------------------------------------
void TTEmploees::CopyFormToEmpl(dataEmpl &Who)
{
    Who.LastName = EditLast->Text; if( Who.LastName.IsEmpty() ) Who.LastName = " ";
    Who.FirstName = EditFirst->Text; if( Who.FirstName.IsEmpty() ) Who.FirstName = " ";
    Who.SIN = atol(EditSIN->Text.Trim().c_str());
    Who.Hired = EditHired->Date;
    Who.Title = EditTitle->Text;        if( Who.Title.IsEmpty() ) Who.Title = " ";
    Who.City = EditCity->Text;          if( Who.City.IsEmpty() ) Who.City = " ";
    Who.Province = ComboProvince->Text; if( Who.Province.IsEmpty() ) Who.Province = " ";
    Who.Street = EditAddress->Text;     if( Who.Street.IsEmpty() ) Who.Street = " ";
    Who.Index = EditPostBox->Text;      if( Who.Index.IsEmpty() ) Who.Index = " ";
    Who.Number = EditNumber->Text;      if( Who.Number.IsEmpty() ) Who.Number = " ";
    Who.Period = EditPeriod->Date;
    Who.Hour = atof(EditHour->Text.Trim().c_str());
    Who.EiIns = atof(EditEiIns->Text.Trim().c_str());
    Who.EiNon = atof(EditEiNon->Text.Trim().c_str());
    Who.RPP = atof(EditRPP->Text.Trim().c_str());
    Who.Union = atof(EditUnion->Text.Trim().c_str());
    Who.Alimony = atof(EditAlimony->Text.Trim().c_str());
    Who.Federal = atof(EditFederal->Text.Trim().c_str());
    Who.Provincial = atof(EditProvincial->Text.Trim().c_str());
    Who.TaxCredit = atof(EditTaxCredit->Text.Trim().c_str());
    Who.AddTax = atof(EditAddTax->Text.Trim().c_str());
    Who.ComboCode = ComboCode->Text;    if( Who.ComboCode.IsEmpty() ) Who.ComboCode = " ";
    Who.Dpnd = atoi(EditDpnd->Text.Trim().c_str());
    Who.Annual = atof(EditAnnual->Text.Trim().c_str());
}
//---------------------------------------------------------------------------
void dataEmpl::Clear(void)
{
    ID = -1L;
    FirstName = "";
    LastName = "";
    SIN = 0L;

    Title = "";
    Street = "";;
    Province = "";
    City = "";
    Index = "";
    Number = 0;
    // Salary / Wage
    Hour = 0;
    EiIns = 0;
    EiNon = 0;
    // Deduction
    RPP = 0;
    Union = 0;
    Alimony = 0;
    // Other Credits
    Federal = 0;
    Provincial = 0;
    // TD1 Credits
    TaxCredit = 0;
    AddTax = 0;
    ComboCode = "";
    Dpnd = 0;
    Annual = 0;
}
//---------------------------------------------------------------------------
void dataEmpl::SaveToDB()
{
	String _Hired =  getFDate(Hired);
    String _Period =  getFDate(Period);
    if( ID > 0 ) // we have to update person
    {
        try
        {
           String SQLcommand = String("UPDATE Employee SET ") +
           "FirstName = '" + FirstName + "', " +
           "LastName = '" + LastName + "', " +
           "SIN = " + getSIN() + ", " +
           "Hired = " + _Hired + ", " +
           "Title = '" + Title + "', " +
           "typeJob = " + (typeJob?"Yes":"No") + ", " +
           "Street = '" + Street + "', " +
           "Province = '" + Province + "', " +
           "City = '" + City + "', " +
           "PostBox = '" + Index + "', " +
           "Nmb = '" + Number + "', " +
           "Salary = " + (Salary?"Yes":"No") + ", " +
           "Prd = " + _Period + ", " +
           "Hr = " + String(Hour) + ", " +
           "EiIns = " + String(EiIns) + ", " +
           "EiNon = " + String(EiNon) + ", " +
           "RPP = " + String(RPP) + ", " +
           "Unn = " + String(Union) + ", " +
           "Alimony = " + String(Alimony) + ", " +
           "Federal = " + String(Federal) + ", " +
           "Provincial = " + String(Provincial) + ", " +
           "AddTax = " + String(AddTax) + ", " +
           "TaxCredit = " + String(TaxCredit) + ", " +
           "ComboCode = '" + ComboCode + "', " +
           "Dpnd = " + String(Dpnd) + ", " +
           "Annual = " + String(Annual) + " " +
           " WHERE ID = " + String(ID) + ";";
           base->RunSQL( SQLcommand );
        }
        catch(...){}
     }else
     {   // otherwise add new record
        try
        {
           String ID = base->MaxID(ATTR_TAG_Employee) + 1L;
           String SQLcommand = "INSERT INTO Employee (";
           vecxml lst = dom->Select(NODE_TAG_Database)->FindName(ATTR_TAG_Remote)->FindName(ATTR_TAG_Employee)->Select(NODE_TAG_Field);
           for(int i = 0; i < (int)lst.size(); i++)
             SQLcommand += lst[i]->atSName + ", ";
           SQLcommand[ SQLcommand.Length() - 1 ] = ')';
           SQLcommand += " VALUES (" +
           ID + ", '" +
           FirstName + "', '" +
           LastName + "', " +
           getSIN() + ", " +
           _Hired + ", '" +
           Title + "', " +
           (typeJob?"Yes":"No") + ", '" +
           Street + "', '" +
           Province + "', '" +
           City + "', '" +
           Index + "', '" +
           Number + "', " +
           (Salary?"Yes":"No") + ", " +
           String(_Period) + ", " +
           String(Hour) + ", " +
           String(EiIns) + ", " +
           String(EiNon) + ", " +
           String(RPP) + ", " +
           String(Union) + ", " +
           String(Alimony) + ", " +
           String(Federal) + ", " +
           String(Provincial) + ", " +
           String(AddTax) + ", " +
           String(TaxCredit) + ", '" +
           ComboCode + "', " +
           String(Dpnd) + ", " +
           String(Annual) + ");";

           base->RunSQL( SQLcommand );
        }
        catch(...){}
     }
}
//---------------------------------------------------------------------------
void __fastcall TTEmploees::ButtonPostClick(TObject *Sender)
{
    CopyFormToEmpl(CurrentEmpl);
    CurrentEmpl.SaveToDB();
}
//---------------------------------------------------------------------------
void loadRecordToObject(TADOQuery *qr, dataEmpl &val)
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
}
//---------------------------------------------------------------------------
void  StepEmpl(method_step val)
{
    TADOQuery *qr = base->RemoteQuery;
    String SQLcommand = "SELECT * FROM Employee ;";
    try
    {
        switch( val )
        {
            case STEP_FIRST :{
                base->_Query(qr, SQLcommand);
                loadRecordToObject(qr, CurrentEmpl);
            }  break;
            case STEP_LAST :
            {
                base->_Query(qr, SQLcommand);
                qr->Last();
                loadRecordToObject(qr, CurrentEmpl);
            }  break;
            case STEP_LEFT :
            {
                if( CurrentEmpl.ID > 0 )
                    SQLcommand = "SELECT * FROM Employee WHERE ID <" + String(CurrentEmpl.ID) + ";";
                base->_Query(qr, SQLcommand);
                if( !qr->Eof )
                {
                    qr->Last();
                    loadRecordToObject(qr, CurrentEmpl);
                }
            }  break;
            case STEP_RIGHT :
            {
                if( CurrentEmpl.ID > 0 )
                    SQLcommand = "SELECT * FROM Employee WHERE ID >" + String(CurrentEmpl.ID) + ";";
                base->_Query(qr, SQLcommand);
                if( !qr->Eof )
                    loadRecordToObject(qr, CurrentEmpl);
            }  break;
        }
     }catch(...){}
     qr->Close();
}
//---------------------------------------------------------------------------
void __fastcall TTEmploees::ButtonFirstClick(TObject *Sender)
{
    StepEmpl(STEP_FIRST);
    CopyEmplToForm(CurrentEmpl);
}
//---------------------------------------------------------------------------
void __fastcall TTEmploees::ButtonLastClick(TObject *Sender)
{
    StepEmpl(STEP_LAST);
    CopyEmplToForm(CurrentEmpl);
}
//---------------------------------------------------------------------------
void __fastcall TTEmploees::ButtonLeftClick(TObject *Sender)
{
    StepEmpl(STEP_LEFT);
    CopyEmplToForm(CurrentEmpl);
}
//---------------------------------------------------------------------------
void __fastcall TTEmploees::ButtonRightClick(TObject *Sender)
{
    StepEmpl(STEP_RIGHT);
    CopyEmplToForm(CurrentEmpl);
}
//---------------------------------------------------------------------------
void __fastcall TTEmploees::ButtonDelClick(TObject *Sender)
{
    if( CurrentEmpl.ID > 0 )
    {
        String SQLcommand = "DELETE FROM Employee WHERE ID=" + String(CurrentEmpl.ID) + ";";
        base->RunSQL( SQLcommand );
        Clear();
    }
}
//---------------------------------------------------------------------------
void __fastcall TTEmploees::RadioSalaryClick(TObject *Sender)
{
    LabelSalary->Caption =  RadioSalary->Checked ?  "Regular Salary" : "$ per hour";
}
//---------------------------------------------------------------------------

