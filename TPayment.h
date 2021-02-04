//----------------------------------------------------------------------------
//Borland C++Builder
//Copyright (c) 1987, 1998 Borland International Inc. All Rights Reserved.
//----------------------------------------------------------------------------
//---------------------------------------------------------------------------
#ifndef TPaymentH
#define TPaymentH
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
#include "TEmpl.h"
#include <Buttons.hpp>
#include "OvcBase.hpp"
#include "OvcEdCal.hpp"
#include "OvcEditF.hpp"
#include "OvcEdPop.hpp"

//---------------------------------------------------------------------------
class TFPayment : public TFChild
{
__published:	// IDE-managed Components
    TPanel *PanelMainPay;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label3;
    TLabel *Label6;
    TGroupBox *GroupBox;
    TLabel *Label12;
    TLabel *Label13;
    TLabel *Label14;
    TEdit *Edit10;
    TEdit *EditEiIns;
    TGroupBox *GroupBox1;
    TGroupBox *GroupBox2;
    TLabel *Label15;
    TLabel *Label16;
    TLabel *Label17;
    TEdit *EditRPP;
    TEdit *EditUnion;
    TEdit *EditAlimony;
    TGroupBox *GroupBox3;
    TLabel *Label19;
    TLabel *Label20;
    TEdit *EditFederal;
    TEdit *EditProvincial;
    TComboBox *ComboBox;
    TEdit *EditLastName;
    TEdit *EditFirstName;
    TEdit *EditSIN;
    TGroupBox *GroupBox5;
    TCheckBox *CheckBox1;
    TComboBox *ComboProvince;
    TEdit *EditNumber;
    TEdit *Edit2;
    TLabel *Label7;
    TLabel *Label8;
    TEdit *EditEiNon;
    TLabel *Label9;
    TEdit *EditAnnual;
    TComboBox *ComboBox1;
    TLabel *Label10;
    TEdit *Edit6;
    TCheckBox *CheckBox2;
    TCheckBox *CheckBox3;
    TLabel *Label11;
    TEdit *EditRequested;
    TGroupBox *GroupBox4;
    TLabel *Label18;
    TLabel *Label21;
    TEdit *EditZone;
    TEdit *EditTaxCredit;
    TEdit *EditDpnd;
    TLabel *Label22;
    TGroupBox *GroupBox6;
    TGroupBox *GroupBox8;
    TLabel *Label27;
    TLabel *Label28;
    TEdit *Edit24;
    TEdit *Edit25;
    TEdit *Edit20;
    TLabel *Label23;
    TLabel *Label24;
    TEdit *Edit21;
    TLabel *Label25;
    TEdit *Edit22;
    TLabel *Label26;
    TEdit *Edit23;
    TLabel *Label32;
    TEdit *Edit29;
    TGroupBox *GroupBox7;
    TLabel *Label35;
    TLabel *Label36;
    TEdit *Edit32;
    TEdit *Edit33;
    TEdit *Edit26;
    TEdit *Edit27;
    TLabel *Label29;
    TLabel *Label30;
    TLabel *Label31;
    TLabel *Label33;
    TEdit *Edit30;
    TLabel *Label34;
    TEdit *Edit31;
    TGroupBox *GroupBox9;
    TRadioButton *RadioButton3;
    TRadioButton *RadioButton4;
    TGroupBox *GroupBox10;
    TRadioButton *RadioButton5;
    TRadioButton *RadioButton6;
    TButton *Button5;
    TSpeedButton *ButtonFirst;
    TSpeedButton *ButtonLeft;
    TSpeedButton *ButtonRight;
    TSpeedButton *ButtonLast;
    TSpeedButton *ButtonAdd;
    TSpeedButton *ButtonDel;
    TSpeedButton *ButtonPost;
    TButton *ButtonClose;
    TOvcDateEdit *EditHired;
    TOvcController *OvcController1;
    TOvcDateEdit *EditPeriod;
    void __fastcall ButtonFirstClick(TObject *Sender);
    void __fastcall ButtonLeftClick(TObject *Sender);
    void __fastcall ButtonRightClick(TObject *Sender);
    void __fastcall ButtonLastClick(TObject *Sender);
    void __fastcall ComboBoxChange(TObject *Sender);
    void __fastcall ButtonCloseClick(TObject *Sender);
private:	// User declarations
    TFileName FFileName;
    bool FSaved;
    map<long, dataEmpl>lstEmpl;

    void CopyEmplToForm(dataEmpl &Who);
    void loadEmpl(map<long, dataEmpl> &lst);
    void __fastcall VerbClick(TObject *Sender);
public:		// User declarations
    
    void Execute(void);
	virtual __fastcall TFPayment(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
