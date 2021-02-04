//----------------------------------------------------------------------------
//Borland C++Builder
//Copyright (c) 1987, 1998 Borland International Inc. All Rights Reserved.
//----------------------------------------------------------------------------
//---------------------------------------------------------------------------
#ifndef TprofileH
#define TprofileH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <OleCtnrs.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>

#include "TMidi.h"
#include "OvcBase.hpp"
#include "OvcEdCal.hpp"
#include "OvcEditF.hpp"
#include "OvcEdPop.hpp"

//---------------------------------------------------------------------------
class dataPerson
{
public:
    long ID;
    String FirstName, LastName, MiddleName;
    double long SIN;
    String getSIN();
    bool Sex;
    // address
    String Street, Province, County, City, Index;
    String Fax, PhoneHome, PhoneWork;
    TDateTime   Birth;

    String CheckData(void); // check valid data
    String FullName(void);
    void SaveToDB(void);
    void Clear(void);

    dataPerson(){}
};
//---------------------------------------------------------------------------
class dataCompany
{
public:
    long ID;
// 1.
    String IncName, CertName, TradeName, Position, SaleName, Phone;
    String FirstName, LastName, PhonePerson;
// 2.
    String Mail_Street, Mail_Province, Mail_County, Mail_City, Mail_Index;
    String Mail_Telephone, Mail_Fax;
// 3.
    String Bus_Street, Bus_Province, Bus_County, Bus_City, Bus_Index;
    String Bus_Telephone, Bus_Fax;
// 4.
    String Federal, Provincial;
    double Payroll, GST, PST;
    double HealthTax, HealthSfty;
// 5.
    TDateTime Start;
    int select;

    String CheckData(void); // check valid data
    String FullName(void);
    void SaveToDB(void);
    void Clear(void);

    dataCompany(){}
};
//---------------------------------------------------------------------------
class TTSetupProfile : public TFChild
{
__published:	// IDE-managed Components
	TPanel *PanelActiveProfile;
    TPageControl *PageControl;
    TTabSheet *TabSheetPersonal;
    TPanel *Panel2;
    TTabSheet *TabSheetCompany;
    TLabel *LabeAAA;
    TLabel *Label24;
    TLabel *Label25;
    TComboBox *ComboBox;
	TPageControl *PageControlPersonal;
    TTabSheet *TabSheet1;
    TTabSheet *TabSheet2;
    TLabel *Label5;
    TEdit *EditFirstName;
    TLabel *Label1;
    TEdit *EditMidName;
    TLabel *Label2;
    TEdit *EditLastName;
    TLabel *Label3;
    TEdit *EditSIN;
    TLabel *Label6;
    TRadioButton *RadioButtonSex;
    TRadioButton *RadioButtonFemail;
    TLabel *Label10;
    TEdit *EditDay;
    TComboBox *ComboBoxMonth;
    TLabel *Label11;
    TLabel *Label12;
    TEdit *EditYear;
    TLabel *Label13;
    TPanel *Panel3;
    TPanel *Panel4;
    TButton *ButtonClose;
    TPanel *Panel5;
    TButton *ButtonSet;
    TPageControl *PageControl2;
    TTabSheet *TabSheet3;
    TTabSheet *TabSheet4;
    TTabSheet *TabSheet5;
    TTabSheet *TabSheet6;
    TTabSheet *TabSheet7;
    TEdit *EditIncName;
    TLabel *Label4;
    TLabel *Label7;
    TEdit *EditSale;
    TEdit *EditTradeName;
    TLabel *Label15;
    TLabel *Label21;
    TLabel *Label9;
    TEdit *EditCertName;
    TEdit *EditPosition;
    TEdit *EditPhone;
    TLabel *Label14;
    TGroupBox *GroupBox1;
    TLabel *Label8;
    TEdit *EditFirstNameCo;
    TLabel *Label23;
    TEdit *EditLastNameCo;
    TLabel *Label26;
    TEdit *EditPhoneCo;
    TButton *ButtonDel;
    TLabel *Label27;
    TRadioButton *rbNo;
    TRadioButton *rbMonth;
    TRadioButton *rbQuarty;
    TRadioButton *rbSemi;
    TRadioButton *rbAnn;
    TLabel *Label28;
    TEdit *EditFederal;
    TLabel *Label29;
    TEdit *EditProvincial;
    TLabel *Label30;
    TEdit *EditPayroll;
    TLabel *Label31;
    TEdit *EditGST;
    TLabel *Label32;
    TEdit *EditTax;
    TLabel *Label33;
    TEdit *EditPST;
    TLabel *Label34;
    TEdit *EditSfty;
    TLabel *Label16;
    TEdit *EditStreetMail;
    TLabel *Label17;
    TEdit *EditCityMail;
    TComboBox *ComboBoxProvMail;
    TLabel *Label18;
    TLabel *Label19;
    TEdit *EditCountyMail;
    TLabel *Label20;
    TEdit *EditPhoneMail;
    TLabel *Label35;
    TEdit *EditFaxMail;
    TLabel *Label36;
    TEdit *EditIndexMail;
	TLabel *LabelStreet;
    TEdit *EditStreet;
    TLabel *Label38;
    TLabel *Label39;
    TComboBox *ComboBoxProv;
    TEdit *EditCity;
    TLabel *Label40;
    TLabel *Label41;
    TEdit *EditIndex;
    TEdit *EditCounty;
    TLabel *Label42;
    TEdit *EditPhoneHome;
    TLabel *Label43;
    TEdit *EditFax;
    TLabel *Label44;
    TEdit *EditPhoneWork;
    TEdit *EditStreetBus;
    TLabel *Label45;
    TLabel *Label46;
    TLabel *Label47;
    TComboBox *ComboBoxProvBus;
    TEdit *EditCityBus;
    TLabel *Label48;
    TEdit *EditCountyBus;
    TLabel *Label49;
    TEdit *EditIndexBus;
    TLabel *Label50;
    TEdit *EditPhoneBus;
    TEdit *EditFaxBus;
    TLabel *Label51;
    TLabel *LabelActiveBus;
    TLabel *LabelActivePersonal;
    TLabel *LabelActiveCompany;
    TOvcDateEdit *EditStart;
    TOvcController *OvcController1;
    void __fastcall ButtonCloseClick(TObject *Sender);
    void __fastcall ButtonSetClick(TObject *Sender);
    void __fastcall BooleaComboBoxChange(TObject *Sender);
    void __fastcall ButtonDelClick(TObject *Sender);
    void __fastcall PageControlChange(TObject *Sender);
    void __fastcall EditCountyMailDblClick(TObject *Sender);
    void __fastcall EditCountyBusDblClick(TObject *Sender);
    void __fastcall EditCountyDblClick(TObject *Sender);
    void __fastcall AChange(TObject *Sender);
    void __fastcall EditSINExit(TObject *Sender);
    void __fastcall EditDayExit(TObject *Sender);
    void __fastcall ComboBoxMonthExit(TObject *Sender);
    void __fastcall EditYearExit(TObject *Sender);
private:	// User declarations

    TFileName FFileName;
    bool FSaved;
    void __fastcall VerbClick(TObject *Sender);

    void CopyPersonToForm(dataPerson &Who);
    void CopyFormToPerson(dataPerson &Who);
    void ClearPersonal(void);
    void loadAllPerson(void);
    map<long, dataPerson> lstPerson;
    long currentPerson;
    void LoadPersonal(void);

    void CopyCompanyToForm(dataCompany &Who);
    void CopyFormToCompany(dataCompany &Who);
    void ClearCompany(void);
    void loadAllCompany(void);
    map<long, dataCompany> lstCompany;
    long currentCompany;
    void LoadCompany(void);
    void loadSeted(void);

public:		// User declarations
    void virtual __fastcall Clear(void);
    virtual void Save(void);

    void SelectPage(bool pb);
    void Execute(bool pb);
	virtual __fastcall TTSetupProfile(TComponent* Owner);
};
extern bool CheckSIN(long _sin);
extern dataPerson person;
extern dataCompany company;
//---------------------------------------------------------------------------
#endif


