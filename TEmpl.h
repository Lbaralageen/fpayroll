//----------------------------------------------------------------------------
//Borland C++Builder
//Copyright (c) 1987, 1998 Borland International Inc. All Rights Reserved.
//----------------------------------------------------------------------------
//---------------------------------------------------------------------------
#ifndef TEmplH
#define TEmplH
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
#include <DBCtrls.hpp>

//---------------------------------------------------------------------------
#include "Tprofile.h"
#include "OvcBase.hpp"
#include "OvcEdCal.hpp"
#include "OvcEditF.hpp"
#include "OvcEdPop.hpp"
#include <Buttons.hpp>

class dataEmpl : public dataPerson
{
public:
//    long ID;
//    String FirstName, LastName;
//    double long SIN;
//    String getSIN();

    // address
    TDateTime   Hired, Period;
    String Title;
    bool typeJob; // true  - employee else self
    String Street, Province, City, Index;
    String Number;
    // Salary / Wage
    bool Salary; //  true - sal, ekse by hour
    float Hour, EiIns, EiNon;
    // Deduction
    float RPP, Union, Alimony;
    // Other Credits
    float Federal, Provincial;
    // TD1 Credits
    float TaxCredit, AddTax;
    String ComboCode;
    int Dpnd;
    float Annual;

    void SaveToDB(void);
    void Clear(void);

    dataEmpl(){}
};
//---------------------------------------------------------------------------
class TTEmploees : public TFChild
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TLabel *Label1;
    TEdit *EditLast;
    TLabel *Label2;
    TEdit *EditFirst;
    TLabel *Label3;
    TEdit *EditSIN;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TComboBox *ComboProvince;
    TRadioButton *RadioEmpl;
    TRadioButton *RadioButton2;
    TLabel *Label7;
    TLabel *LabelCity;
    TLabel *Label9;
    TEdit *EditAddress;
    TEdit *EditCity;
    TLabel *Label10;
    TLabel *Label11;
    TEdit *EditPostBox;
    TEdit *EditNumber;
    TGroupBox *GroupBox;
    TRadioButton *RadioSalary;
    TRadioButton *RadioPerHour;
    TLabel *LabelSalary;
    TEdit *EditHour;
    TLabel *Label13;
    TEdit *EditEiIns;
    TEdit *EditEiNon;
    TLabel *Label14;
    TGroupBox *GroupBox1;
    TGroupBox *GroupBox2;
    TLabel *Label15;
    TEdit *EditRPP;
    TLabel *Label16;
    TEdit *EditUnion;
    TLabel *Label17;
    TEdit *EditAlimony;
    TGroupBox *GroupBox3;
    TLabel *Label19;
    TLabel *Label20;
    TEdit *EditFederal;
    TEdit *EditProvincial;
    TGroupBox *GroupBox4;
    TLabel *Label18;
    TLabel *Label21;
    TLabel *Label22;
    TEdit *EditTaxCredit;
    TEdit *EditAddTax;
    TEdit *EditDpnd;
    TComboBox *ComboCode;
    TLabel *Label23;
    TEdit *EditAnnual;
    TLabel *Label24;
    TSpeedButton *ButtonAdd;
    TSpeedButton *ButtonDel;
    TSpeedButton *ButtonPost;
    TSpeedButton *ButtonFirst;
    TSpeedButton *ButtonLast;
    TSpeedButton *ButtonLeft;
    TSpeedButton *ButtonRight;
    TComboBox *EditTitle;
    void __fastcall ButtonPostClick(TObject *Sender);
    void __fastcall ButtonFirstClick(TObject *Sender);
    void __fastcall ButtonLastClick(TObject *Sender);
    void __fastcall ButtonLeftClick(TObject *Sender);
    void __fastcall ButtonRightClick(TObject *Sender);
    void __fastcall ButtonDelClick(TObject *Sender);
    void __fastcall RadioSalaryClick(TObject *Sender);
private:	// User declarations
    TFileName FFileName;
    bool FSaved;

    void __fastcall FormMouseWheelDown(TObject *Sender, TShiftState Shift,
          TPoint &MousePos, bool &Handled){}
    void __fastcall FormMouseWheelUp(TObject *Sender, TShiftState Shift,
          TPoint &MousePos, bool &Handled){}
    void __fastcall FormClick(TObject *Sender){}

    void CopyFormToEmpl(dataEmpl &Who)  ;
    void CopyEmplToForm(dataEmpl &Who);
public:		// User declarations
    void __fastcall Clear(void);
    virtual void Save(void);

    void SelectPage(bool pb);
    void Execute(bool pb);
	virtual __fastcall TTEmploees(TComponent* Owner);
};
//---------------------------------------------------------------------------
enum method_step{STEP_FIRST, STEP_LEFT, STEP_RIGHT, STEP_LAST};
extern void  StepEmpl(method_step val);
extern void loadRecordToObject(TADOQuery *qr, dataEmpl &val);
extern dataEmpl CurrentEmpl;
//---------------------------------------------------------------------------
#endif
