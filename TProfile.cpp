//----------------------------------------------------------------------------
//Borland C++Builder
//Copyright (c) 1987, 1998 Borland International Inc. All Rights Reserved.
//----------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TMain.h"
#include "TFormDB.h"

#include "Tprofile.h"
//---------------------------------------------------------------------------
#pragma link "OvcBase"
#pragma link "OvcEdCal"
#pragma link "OvcEditF"
#pragma link "OvcEdPop"
#pragma resource "*.dfm"

static const char *_GUID = "FR_PROFILE";

//---------------------------------------------------------------------------
__fastcall TTSetupProfile::TTSetupProfile(TComponent* Owner)
    : TFChild(Owner)
{
  saveFlag = clearFlag = true;
  ComboBox->Clear();
  FormMain->loadProvince(ComboBoxProv);
  FormMain->loadProvince(ComboBoxProvMail);
  FormMain->loadProvince(ComboBoxProvBus);
  FormActivate(NULL);
  WindowState = wsNormal;
  FormMain->BitBtnSaveAs->Enabled = false;
  FormMain->SaveButton->Enabled = false;
  FormMain->SaveMenu->Enabled = false;
  Position = poDefault;
  Left = 0;
  Top = 0;
  BorderStyle = bsSingle;
  Width = 640;
  Height = PanelActiveProfile->Height * 2  + ( EditPhoneHome->Height * 4 + LabelStreet->Height * 4 ) * 2;
}
//---------------------------------------------------------------------------
void TTSetupProfile::loadSeted(void)
{
    if( person.SIN > 0 )
    {
        CopyPersonToForm(person);
        LabelActivePersonal->Caption = person.FullName();
    }
    if( company.ID > 0 )
    {
        CopyCompanyToForm(company);
        LabelActiveCompany->Caption = company.IncName;
    }
}
//---------------------------------------------------------------------------
void TTSetupProfile::SelectPage(bool pb)
{
    if( pb == true )
    {
        Caption = "Personal Information" ;
        PageControl->ActivePage = TabSheetPersonal;
        SetFocus();
        WindowState = wsNormal;
        LoadPersonal();
    }else
    {
        Caption = "Bussines Information" ;
        PageControl->ActivePage = TabSheetCompany;
        SetFocus();
        WindowState = wsNormal;
        LoadCompany();
    }
    FormMain->BitBtnSaveAs->Enabled = false;
    FormMain->SaveButton->Enabled = false;
    FormMain->SaveMenu->Enabled = false;
}
//---------------------------------------------------------------------------
void TTSetupProfile::LoadPersonal(void)
{
    loadAllPerson();

    ComboBox->Clear();
    map<long, dataPerson>::iterator i_ptr;
    for( i_ptr = lstPerson.begin(); i_ptr != lstPerson.end(); i_ptr++)
    {
        dataPerson *val = &(*i_ptr).second;
        ComboBox->Items->Add(val->FullName());
    }
}
//---------------------------------------------------------------------------
void TTSetupProfile::LoadCompany(void)
{
    loadAllCompany();

    ComboBox->Clear();
    map<long, dataCompany>::iterator i_ptr;
    for( i_ptr = lstCompany.begin(); i_ptr != lstCompany.end(); i_ptr++)
    {
        dataCompany *val = &(*i_ptr).second;
        ComboBox->Items->Add(val->IncName);
    }
}
//---------------------------------------------------------------------------
void TTSetupProfile::Execute(bool pb)
{
    Caption = _GUID;
    FormMain->RegisterForm("", this);
    loadSeted();
    SelectPage(pb);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::PersonalMenuClick(TObject *Sender)
{
    PersonalMenu->Checked = false;
    BusinessMenu->Checked = false;
    TMenuItem *tmenu = (TMenuItem *)Sender;
    tmenu->Checked = true;
    if( !CheckForm(_GUID) )
    {
      if( PersonalMenu->Checked  )
      {
          TTSetupProfile* ch = new TTSetupProfile(this);
          ch->Execute(true);
      }else if( BusinessMenu->Checked )
      {
          TTSetupProfile* ch = new TTSetupProfile(this);
          ch->Execute(false);
      }
    }else
    {
      if( PersonalMenu->Checked  )
      {
        TTSetupProfile *ptr = (TTSetupProfile *)getForm(_GUID);
        ptr->SelectPage(true);
      }else if( BusinessMenu->Checked )
      {
        TTSetupProfile *ptr = (TTSetupProfile *)getForm(_GUID);
        ptr->SelectPage(false);
      }
    }
}
//---------------------------------------------------------------------------
void TTSetupProfile::Save(void)
{
    if( PageControl->ActivePage == TabSheetPersonal )
    {
      dataPerson CurrentPerson;
      CopyFormToPerson(CurrentPerson);

      String message = CurrentPerson.CheckData();
      if( message.IsEmpty() )
      {
          CurrentPerson.SaveToDB();
          LoadPersonal();
      }else
          ShowMessage(message);
      if( person.ID == CurrentPerson.ID )
          CopyFormToPerson(person);
    }else if( PageControl->ActivePage == TabSheetCompany )
    {
      dataCompany CurrentCompany;
      CopyFormToCompany(CurrentCompany);

      String message = CurrentCompany.CheckData();
      if( message.IsEmpty() )
      {
          CurrentCompany.SaveToDB();
          LoadCompany();
          if( company.ID == CurrentCompany.ID )
              CopyFormToCompany(company);
      }else
          ShowMessage(message);
    }
}
//---------------------------------------------------------------------------
void TTSetupProfile::loadAllCompany(void)
{
    lstCompany.clear();

     TADOQuery *qr = base->RemoteQuery;
     String SQLcommand = "SELECT * FROM Company ;";
     base->_Query(qr, SQLcommand);
     while( !qr->Eof )
     {
        dataCompany val;
          val.ID = qr->FieldByName("ID")->AsInteger;
          val.IncName = qr->FieldByName("Name")->AsString;
          val.CertName = qr->FieldByName("Certificate")->AsString;
          val.TradeName = qr->FieldByName("Trade")->AsString;
          val.Position = qr->FieldByName("Stateman")->AsString;
          val.SaleName = qr->FieldByName("Saleman")->AsString;
          val.Phone = qr->FieldByName("Phone")->AsString;
          val.FirstName = qr->FieldByName("FirstName")->AsString;
          val.LastName  = qr->FieldByName("LastName")->AsString;
          val.PhonePerson = qr->FieldByName("PhonePerson")->AsString;
          val.Mail_Street = qr->FieldByName("StreetMail")->AsString;
          val.Mail_Province  = qr->FieldByName("ProvinceMail")->AsString;
          val.Mail_County  = qr->FieldByName("CountyMail")->AsString;
          val.Mail_City  = qr->FieldByName("CityMail")->AsString;
          val.Mail_Index  = qr->FieldByName("IndexMail")->AsString;
          val.Mail_Telephone   = qr->FieldByName("PhoneMail")->AsString;
          val.Mail_Fax   = qr->FieldByName("FaxMail")->AsString;
          val.Bus_Street = qr->FieldByName("StreetBus")->AsString;
          val.Bus_Province  = qr->FieldByName("ProvinceBus")->AsString;
          val.Bus_County  = qr->FieldByName("CountyBus")->AsString;
          val.Bus_City  = qr->FieldByName("CityBus")->AsString;
          val.Bus_Index  = qr->FieldByName("IndexBus")->AsString;
          val.Bus_Telephone   = qr->FieldByName("PhoneBus")->AsString;
          val.Bus_Fax   = qr->FieldByName("FaxBus")->AsString;
          val.Federal   = qr->FieldByName("Federal")->AsString;
          val.Provincial   = qr->FieldByName("Provincial")->AsString;
          val.Payroll   = qr->FieldByName("Payroll")->AsFloat;
          val.GST   = qr->FieldByName("GST")->AsFloat;
          val.PST   = qr->FieldByName("PST")->AsFloat;
          val.HealthTax   = qr->FieldByName("Health")->AsFloat;
          val.HealthSfty   = qr->FieldByName("Cfty")->AsFloat;
          long dts = qr->FieldByName("StartPeriod")->AsInteger;
          val.Start   =     getFDate( dts );
          val.select   = qr->FieldByName("IndexPeriod")->AsInteger;

          lstCompany[val.ID] = val;
          qr->Next();
     }
     qr->Close();
}
//---------------------------------------------------------------------------
void TTSetupProfile::loadAllPerson(void)
{
    lstPerson.clear();

    TADOQuery *qr = base->RemoteQuery;
     String SQLcommand = "SELECT * FROM Person ;";
     base->_Query(qr, SQLcommand);
     while( !qr->Eof )
     {
        dataPerson val;
          val.ID = qr->FieldByName("ID")->AsInteger;
          val.FirstName = qr->FieldByName("Name")->AsString;
          val.MiddleName  = qr->FieldByName("Middle")->AsString;
          val.LastName  = qr->FieldByName("Last_Name")->AsString;
          val.SIN = qr->FieldByName("SIN")->AsInteger;
          int sex = qr->FieldByName("Sex")->AsInteger;
          val.Sex = sex > 0 ? true : false;
          WORD day = qr->FieldByName("BirthDay")->AsInteger;
          WORD month = qr->FieldByName("BirthMonth")->AsInteger;
          WORD year = qr->FieldByName("BirthYear")->AsInteger;
          val.Birth = EncodeDate(year, month, day);
          val.Street  = qr->FieldByName("Street")->AsString;
          val.City  = qr->FieldByName("City")->AsString;
          val.Province  = qr->FieldByName("Province")->AsString;
          val.County  = qr->FieldByName("County")->AsString;
          val.Index   = qr->FieldByName("Post_Box")->AsString;
          val.PhoneHome   = qr->FieldByName("Phone_Home")->AsString;
          val.Fax   = qr->FieldByName("Fax")->AsString;
          val.PhoneWork   = qr->FieldByName("Phone_Work")->AsString;

          lstPerson[val.ID] = val;
          qr->Next();
     }
     qr->Close();
}
//---------------------------------------------------------------------------
void TTSetupProfile::ClearPersonal(void)
{
    EditStreet->Text = " ";
    EditMidName->Text = " ";
    EditLastName->Text = " ";
    EditFirstName->Text = " ";
    EditCity->Text = " ";
    ComboBoxProv->Text = " ";
    EditCounty->Text = " ";
    EditPhoneHome->Text = " ";
    EditFax->Text = " ";
    EditPhoneWork->Text = " ";
    EditIndex->Text = " ";
    EditSIN->Text = 0L;
    EditDay->Text = " ";
    EditYear->Text = " ";
    ComboBoxMonth->ItemIndex  = 0;
}
//---------------------------------------------------------------------------
void TTSetupProfile::ClearCompany(void)
{
// 1.0
    EditIncName->Text = " ";                   EditCertName->Text = " ";
    EditTradeName->Text = " ";                 EditPosition->Text = " ";
    EditSale->Text = " ";                      EditPhone->Text = " ";
    EditFirstNameCo->Text = " ";               EditLastNameCo->Text = " ";
    EditPhoneCo->Text = " ";
// 2.0
    EditStreetMail->Text = " ";                ComboBoxProvMail->ItemIndex = 0;
    EditCityMail->Text = " ";                  EditCountyMail->Text = " ";
    EditIndexMail->Text = " ";                 EditPhoneMail->Text = " ";
    EditFaxMail->Text  = " ";
// 3.0
    EditStreetBus->Text = " ";                 EditCityBus->Text = " ";
    ComboBoxProvBus->ItemIndex = 0;            EditCountyBus->Text = " ";
    EditIndexBus->Text = " ";                  EditPhoneBus->Text = " ";
    EditFaxBus->Text = " ";
// 4.0
    EditFederal->Text = " ";                   EditProvincial->Text = " ";
    EditPayroll->Text = " ";                   EditPST->Text = " ";
    EditGST->Text = " ";                       EditTax->Text = " ";
    EditSfty->Text = " ";
// 5.0
    EditStart->Text = " ";                     rbNo->Checked = true;
}
//---------------------------------------------------------------------------
bool CheckSIN(long _sin)
{
    if( _sin > 0L )
        return true;
    else
        return false;
}
//---------------------------------------------------------------------------
void __fastcall TTSetupProfile::ButtonCloseClick(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
void __fastcall TTSetupProfile::Clear(void)
{
    if( PageControl->ActivePage == TabSheetPersonal )
    {
        currentPerson = -1;
        ClearPersonal();
    }else if( PageControl->ActivePage == TabSheetCompany )
    {
        currentCompany = -1;
        ClearCompany();
    }
}
//---------------------------------------------------------------------------
void __fastcall TTSetupProfile::BooleaComboBoxChange(TObject *Sender)
{
    int idx = ComboBox->ItemIndex;
    if( PageControl->ActivePage == TabSheetPersonal )
    {
         map<long, dataPerson>::iterator i_ptr;
         int i = 0;
         for( i_ptr = lstPerson.begin(); i_ptr != lstPerson.end(); i_ptr++)
             if( i++ ==  idx)
             {
                dataPerson person = (*i_ptr).second;
                CopyPersonToForm((*i_ptr).second);
                ButtonSetClick(Sender);
                FormMain->BitBtnSaveAs->Enabled = false;
                FormMain->SaveButton->Enabled = false;
                FormMain->SaveMenu->Enabled = false;
                return;
             }
    }else if( PageControl->ActivePage == TabSheetCompany )
    {
         map<long, dataCompany>::iterator i_ptr;
         int i = 0;
         for( i_ptr = lstCompany.begin(); i_ptr != lstCompany.end(); i_ptr++)
             if( i++ ==  idx)
             {
                dataCompany company = (*i_ptr).second;
                CopyCompanyToForm((*i_ptr).second);
                ButtonSetClick(Sender);
                FormMain->BitBtnSaveAs->Enabled = false;
                FormMain->SaveButton->Enabled = false;
                FormMain->SaveMenu->Enabled = false;
                return;
             }
    }
}
//---------------------------------------------------------------------------
void TTSetupProfile::CopyCompanyToForm(dataCompany &Who)
{
    currentCompany = Who.ID;
        EditIncName->Text = Who.IncName;        EditCertName->Text = Who.CertName;
        EditTradeName->Text = Who.TradeName;      EditPosition->Text = Who.Position;
        EditSale->Text = Who.SaleName;           EditPhone->Text = Who.Phone;
        EditFirstNameCo->Text = Who.FirstName;    EditLastNameCo->Text = Who.LastName;
        EditPhoneCo->Text = Who.PhonePerson;
// 2.0
        EditStreetMail->Text = Who.Mail_Street;     EditCityMail->Text = Who.Mail_City;
        ComboBoxProvMail->ItemIndex = ComboBoxProvMail->Items->IndexOf(Who.Mail_Province);
        EditCountyMail->Text = Who.Mail_County;      EditIndexMail->Text = Who.Mail_Index;
        EditPhoneMail->Text = Who.Mail_Telephone;    EditFaxMail->Text = Who.Mail_Fax;
// 3.0
        EditStreetBus->Text = Who.Bus_Street;     EditCityBus->Text = Who.Bus_City;
        ComboBoxProvBus->ItemIndex =  ComboBoxProvMail->Items->IndexOf(Who.Bus_Province);
        EditCountyBus->Text = Who.Bus_County;      EditIndexBus->Text = Who.Bus_Index;
        EditPhoneBus->Text = Who.Bus_Telephone;    EditFaxBus->Text = Who.Bus_Fax;
// 4.0
        EditFederal->Text = Who.Federal;      EditProvincial->Text = Who.Provincial;
        EditPayroll->Text = Who.Payroll;     EditPST->Text = Who.PST;
        EditGST->Text = Who.GST;         EditTax->Text = Who.HealthTax;
        EditSfty->Text = Who.HealthSfty;
// 5.0
        EditStart->Text = FormatDateTime("MM/dd/yyyy", Who.Start);
        switch(Who.select)
        {
            case 0: rbNo->Checked = true;     break;
            case 1: rbMonth->Checked = true;  break;
            case 2: rbQuarty->Checked = true; break;
            case 3: rbSemi->Checked = true;   break;
            case 4: rbAnn->Checked = true;    break;
        }
}
//---------------------------------------------------------------------------
void TTSetupProfile::CopyPersonToForm(dataPerson &Who)
{
    currentPerson = Who.ID;
    WORD year, month, day;
    DecodeDate(Who.Birth, year, month, day);
    EditDay->Text = day;
    EditYear->Text = year;
    ComboBoxMonth->ItemIndex = month - 1;

    EditStreet->Text = Who.Street;
    EditMidName->Text = Who.MiddleName;
    EditLastName->Text = Who.LastName;
    EditFirstName->Text = Who.FirstName;
    EditCity->Text = Who.City;

    if( Who.Sex )
        RadioButtonSex->Checked = true;
    else
        RadioButtonFemail->Checked = true;

    ComboBoxProv->Text = Who.Province;
    EditCounty->Text = Who.County;
    EditPhoneHome->Text = Who.PhoneHome;
    EditFax->Text = Who.Fax;
    EditPhoneWork->Text = Who.PhoneWork;
    EditIndex->Text = Who.Index;
    char str[20];
    EditSIN->Text = ltoa(Who.SIN, str, 10);
}
//---------------------------------------------------------------------------
void TTSetupProfile::CopyFormToCompany(dataCompany &Who)
{
    Who.ID = currentCompany;
        Who.IncName = EditIncName->Text.Trim();
        Who.CertName = EditCertName->Text.Trim();
        Who.TradeName = EditTradeName->Text.Trim();
        Who.Position = EditPosition->Text.Trim();
        Who.SaleName = EditSale->Text.Trim();
        Who.Phone = EditPhone->Text.Trim();
        Who.FirstName = EditFirstNameCo->Text.Trim();
        Who.LastName = EditLastNameCo->Text.Trim();
        Who.PhonePerson = EditPhoneCo->Text.Trim();
// 2.0
        Who.Mail_Street = EditStreetMail->Text.Trim();
        Who.Mail_City = EditCityMail->Text.Trim();
        Who.Mail_Province = ComboBoxProvMail->Text.Trim();
        Who.Mail_County = EditCountyMail->Text.Trim();
        Who.Mail_Index = EditIndexMail->Text.Trim();
        Who.Mail_Telephone = EditPhoneMail->Text.Trim();
        Who.Mail_Fax = EditFaxMail->Text.Trim();
// 3.0
        Who.Bus_Street = EditStreetBus->Text.Trim();
        Who.Bus_City = EditCityBus->Text.Trim();
        Who.Bus_Province = ComboBoxProvBus->Text.Trim();
        Who.Bus_County = EditCountyBus->Text.Trim();
        Who.Bus_Index = EditIndexBus->Text.Trim();
        Who.Bus_Telephone = EditPhoneBus->Text.Trim();
        Who.Bus_Fax = EditFaxBus->Text.Trim();
// 4.0
        Who.Federal = EditFederal->Text;
        Who.Provincial = EditProvincial->Text;
        Who.Payroll = atof(EditPayroll->Text.Trim().c_str());
        Who.PST = atof(EditPST->Text.Trim().c_str());
        Who.GST = atof(EditGST->Text.Trim().c_str());
        Who.HealthTax = atof(EditTax->Text.Trim().c_str());
        Who.HealthSfty = atof(EditSfty->Text.Trim().c_str());
// 5.0
        String strDate = EditStart->Text.Trim();
        try
        {
		  if( !strDate.IsEmpty() )
		  {
			  strDate = replace(strDate, '.', '/');
			  Who.Start =  StrToDate(strDate.Trim());
		  }
        }catch(...)
        {
            Who.Start = Now();
            ShowMessage("You have wrong date : " + EditStart->Text);
        }
        String ffd = FormatDateTime("MM/dd/yyyy", Who.Start);

        if( rbNo->Checked )
            Who.select = 0;
        else if( rbMonth->Checked )
            Who.select = 1;
        else if( rbQuarty->Checked )
            Who.select = 2;
        else if( rbSemi->Checked )
            Who.select = 3;
        else if( rbAnn->Checked )
            Who.select = 4;

}
//---------------------------------------------------------------------------
void TTSetupProfile::CopyFormToPerson(dataPerson &Who)
{
    Who.ID = currentPerson;
    // check date
    WORD day = atoi(EditDay->Text.c_str());
    WORD year = atoi(EditYear->Text.c_str());
    WORD month = ComboBoxMonth->ItemIndex + 1;

    if( day <= 0 || day > 31 )
    {
        ShowMessage("you typed wrong day!");
        EditStreet->Focused();
        return;
    }
    if( month <= 0 || month > 12 )
    {
        ShowMessage("you selected wrong month!");
        EditStreet->Focused();
        return;
    }
    if( year <= 1800 || year > 2012 )
    {
        ShowMessage("you typed wrong year!");
        EditStreet->Focused();
        return;
    }

    Who.Birth = EncodeDate(year, month, day);

    Who.Sex = RadioButtonSex->Checked;
    Who.Street = EditStreet->Text;
    Who.MiddleName = EditMidName->Text;
    Who.LastName = EditLastName->Text;
    Who.FirstName = EditFirstName->Text;
    Who.City = EditCity->Text;

    Who.Province = ComboBoxProv->Text;
    Who.County = EditCounty->Text;
    Who.PhoneHome = EditPhoneHome->Text;
    Who.Fax = EditFax->Text;
    Who.PhoneWork = EditPhoneWork->Text;
    Who.Index = EditIndex->Text;

    Who.SIN = atol(EditSIN->Text.c_str());
}
//---------------------------------------------------------------------------
void __fastcall TTSetupProfile::ButtonDelClick(TObject *Sender)
{
    if( PageControl->ActivePage == TabSheetPersonal )
    {
      if( currentPerson < 1L )
          return;
      try
      {
         if( person.ID == currentPerson )
         {
              LabelActivePersonal->Caption = "";
              person.Clear();
         }
         String SQLcommand = "DELETE FROM Person WHERE ID= " + String(currentPerson) + " ;";
         base->RunSQL( SQLcommand );
         Clear();
         LoadPersonal();
      }
      catch(...){ShowMessage("Cannot delete current recod");}
    }else if( PageControl->ActivePage == TabSheetCompany )
    {
      if( currentCompany < 1L )
          return;
      try
      {
         if( company.ID == currentCompany )
         {
              LabelActiveCompany->Caption = "";
              company.Clear();
         }
         String SQLcommand = "DELETE FROM Company WHERE ID= " + String(currentCompany) + " ;";
         base->RunSQL( SQLcommand );
         Clear();
         LoadCompany();
      }
      catch(...){ShowMessage("Cannot delete current recod");}
    }
}
//---------------------------------------------------------------------------
void __fastcall TTSetupProfile::PageControlChange(TObject *Sender)
{
    if( PageControl->ActivePage == TabSheetPersonal )
        SelectPage(true);
    else
        if( PageControl->ActivePage == TabSheetCompany )
            SelectPage(false);
}
//---------------------------------------------------------------------------
void __fastcall TTSetupProfile::EditCountyMailDblClick(TObject *Sender)
{
    EditCountyMail->Text = "CANADA";
}
//---------------------------------------------------------------------------

void __fastcall TTSetupProfile::EditCountyBusDblClick(TObject *Sender)
{
    EditCountyBus->Text = "CANADA";
}
//---------------------------------------------------------------------------

void __fastcall TTSetupProfile::EditCountyDblClick(TObject *Sender)
{
    EditCounty->Text = "CANADA";
}
//---------------------------------------------------------------------------
void __fastcall TTSetupProfile::AChange(TObject *Sender)
{
    FormMain->BitBtnSaveAs->Enabled = false;
    FormMain->SaveButton->Enabled = true;
    FormMain->SaveMenu->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TTSetupProfile::EditSINExit(TObject *Sender)
{
    if( !EditSIN->Text.IsEmpty() )
        if( EditSIN->Text.Length() != 9 )
        {
            ShowMessage("S.I.N. number must have 9 digits!");
            EditSIN->Focused();
        }
}
//---------------------------------------------------------------------------
void __fastcall TTSetupProfile::EditDayExit(TObject *Sender)
{
    int day = atoi(EditDay->Text.Trim().c_str());
    if( day < 1 || day > 31 )
    {
        ShowMessage("You typed wrong number!");
        EditDay->Focused();
    }
}
//---------------------------------------------------------------------------
void __fastcall TTSetupProfile::ComboBoxMonthExit(TObject *Sender)
{
    if( ComboBoxMonth->Text.IsEmpty() )
    {
        ShowMessage("You have to choose month!");
        ComboBoxMonth->Focused();
    }
}
//---------------------------------------------------------------------------
void __fastcall TTSetupProfile::EditYearExit(TObject *Sender)
{
    unsigned short year, month, day;
    Now().DecodeDate(&year, &month, &day);

    int y = atoi(EditYear->Text.Trim().c_str());
    if( y > year )
    {
        ShowMessage("You typed wrong year!");
        EditYear->Focused();
    }
}
//---------------------------------------------------------------------------
void __fastcall TTSetupProfile::ButtonSetClick(TObject *Sender)
{
    Save();

    if( PageControl->ActivePage == TabSheetPersonal )
    {
      CopyFormToPerson(person);
      LabelActivePersonal->Caption = person.FullName();
      FormMain->StatusBar->Panels->Items[1]->Text = "P: " + person.FullName();
      FormMain->ButtonCPer->Enabled = true;
    }else if( PageControl->ActivePage == TabSheetCompany )
    {
      CopyFormToCompany(company);
      LabelActiveCompany->Caption = company.IncName;
      FormMain->StatusBar->Panels->Items[2]->Text = "B: " + company.IncName;
      FormMain->ButtonCComp->Enabled = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonCPerClick(TObject *Sender)
{
      StatusBar->Panels->Items[1]->Text = "P:";
      person.Clear();
      ButtonCPer->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ButtonCCompClick(TObject *Sender)
{
      StatusBar->Panels->Items[2]->Text = "B:";
      company.Clear();
      ButtonCComp->Enabled = false;
}
//---------------------------------------------------------------------------

