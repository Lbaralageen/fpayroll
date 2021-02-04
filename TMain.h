//----------------------------------------------------------------------------
//Borland C++Builder
//Copyright (c) 1987, 1998 Borland International Inc. All Rights Reserved.
//----------------------------------------------------------------------------
//---------------------------------------------------------------------------
#ifndef TMainH
#define TMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>

#include <assert.h>
#include <dir.h>
#include "XmlObjModel.hpp"
#include "XmlParser.hpp"
#include <ADODB.hpp>

#include "Staff.h"
#include "TMidi.h"

#include "XMLclass.h"
#include "WPDefs.hpp"
#include "WPPanel.hpp"
#include "WPTbar.hpp"
#include "WPTCtrl.hpp"
#include <map>

#include <ToolWin.hpp>
//---------------------------------------------------------------------------

enum ListTForm {FR_NONE = -1, FR_PROFILE, FR_TAX, FR_PAYROLL,
    FR_11076=11076,  FR_TD1E=10001, FR_NAS2120B=10003, FR_GST34A=104, FR_GST34B=105, FR_PRO336=336 };


class TFormMain : public TForm
{
__published:	// IDE-managed Components
    TMainMenu *MainMenu;
    TMenuItem *FormMenu;
	TMenuItem *Open1;
    TMenuItem *SaveMenu;
    TMenuItem *SaveAsMenu;
	TMenuItem *N2;
    TMenuItem *CloseMenu;
    TMenuItem *CloseAll;
	TMenuItem *N1;
	TMenuItem *Exit1;
    TMenuItem *WindowMenu;
    TMenuItem *TileVert;
    TMenuItem *TileHoriz;
    TMenuItem *CascadeMenu;
    TMenuItem *CloseAllWMenu;
	TMenuItem *Help1;
	TMenuItem *About1;
    TOpenDialog *OpenDialog;
	TSaveDialog *SaveDialog1;
    TMenuItem *ClearMenu;
    TMenuItem *N3;
    TMenuItem *PrintMenu;
    TMenuItem *PrintAll;
    TMenuItem *Payroll1;
    TMenuItem *PayrollMenu;
    TMenuItem *EmployessMenu;
    TMenuItem *Report1;
    TMenuItem *SetupMenu;
    TMenuItem *FProfilesMenu;
    TMenuItem *TaxParameters1;
    TMenuItem *Index1;
    TMenuItem *Contents1;
    TMenuItem *PersonalMenu;
    TMenuItem *BusinessMenu;
    TXmlObjModel *XmlObjModel1;
    TXmlParser *XmlParser1;
    TMenuItem *MinimazeMenu;
    TMenuItem *MinimazeAllMenu;
    TMenuItem *WinMenuDiv;
    TMenuItem *DatabaseOptions;
    TPanel *Panel3;
    TStatusBar *StatusBar;
    TProgressBar *ProgressBar;
    TMenuItem *N4;
    TMenuItem *InitializeMenu;
    TPrintDialog *PrintDialog;
    TMenuItem *NewMenu;
    TMenuItem *SendEmailMenu;
    TWPToolPanel *WPToolPanel1;
    TWPToolBar *WPToolBar;
    TWPToolPanel *WPToolPanel2;
    TSpeedButton *BNew;
    TSpeedButton *OpenButton;
    TSpeedButton *SaveButton;
    TSpeedButton *BitBtnSaveAs;
    TSpeedButton *BitBtnClear;
    TSpeedButton *ButtonCPer;
    TSpeedButton *ButtonCComp;
    TWPToolPanel *WPToolPanel4;
    TSpeedButton *BitBtnInit;
    TSpeedButton *ButtonPrint;
    TCheckBox *CheckBoxCketch;
	TEdit *Edit1;
	void __fastcall About1Click(TObject *Sender);
	void __fastcall ArrangeIcons1Click(TObject *Sender);
	void __fastcall CascadeMenuClick(TObject *Sender);
	void __fastcall Close1Click(TObject *Sender);
	void __fastcall CloseAllClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Open1Click(TObject *Sender);
	void __fastcall TileHorizClick(TObject *Sender);
	void __fastcall WindowMenuClick(TObject *Sender);
    void __fastcall TileVertClick(TObject *Sender);
    void __fastcall PersonalMenuClick(TObject *Sender);
    void __fastcall CloseAllWMenuClick(TObject *Sender);
    void __fastcall MinimazeMenuClick(TObject *Sender);
    void __fastcall MinimazeAllMenuClick(TObject *Sender);
    void __fastcall TaxParameters1Click(TObject *Sender);
    void __fastcall DatabaseOptionsClick(TObject *Sender);
    void __fastcall EmployessMenuClick(TObject *Sender);
    void __fastcall BNewClick(TObject *Sender);
    void __fastcall PayrollMenuClick(TObject *Sender);
    void __fastcall OpenWindowsMenu(TObject *Sender);
    void __fastcall Exit1Click(TObject *Sender);
    void __fastcall ButtonPrintClick(TObject *Sender);
    void __fastcall BitBtnInitClick(TObject *Sender);
    void __fastcall BitBtnClearClick(TObject *Sender);
    void __fastcall SaveButtonClick(TObject *Sender);
    void __fastcall BitBtnSaveAsClick(TObject *Sender);
    void __fastcall CheckBoxCketchClick(TObject *Sender);
    void __fastcall PrintAllClick(TObject *Sender);
    void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall ButtonCPerClick(TObject *Sender);
    void __fastcall ButtonCCompClick(TObject *Sender);
    void __fastcall Contents1Click(TObject *Sender);
    void __fastcall Index1Click(TObject *Sender);
    void __fastcall SendEmailMenuClick(TObject *Sender);
private:	// User declarations
    String FileName;
private:	// User declarations
    void __fastcall ShowHint(TObject *Sender);
public:		// User declarations
    bool __fastcall RunSQL( String SQLcommand );
    map<long, String> Select( String NameTable, String Field, String Where);
    long getIDbyName( String NameTable, String Field);
    void __fastcall FillTypeTable(void);
    long MaxID(String table);
    long __fastcall NumOfTable(String TableName, String term);
    void loadProvince(TComboBox *cbox, bool flag=true);
    void PrintBitmap(Graphics::TBitmap *ABitmap, String title);
    void PrintWMF(TMetafile *MFile, String title);
    void __fastcall PrintFormWMF(TFChild *form);
    void __fastcall PrintForm(TFChild *form);

public:		// User declarations
    bool __fastcall DatabaseOptionsMenu(void);
    map<String, TFChild *> ListForms;

    void RegisterForm(String obj, TFChild *form);
    void __fastcall CallForm(TXelm *page, long _id, String _caption);
    TFChild *getForm(String obj);
    bool CheckForm(String obj);
    void DelForm(TFChild *obj);

	virtual __fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TFormMain *FormMain;
extern String GlobalPath;
extern TXobj *dom;
extern TXobj *prj;
//---------------------------------------------------------------------------
#endif
