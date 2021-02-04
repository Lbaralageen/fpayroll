//----------------------------------------------------------------------------
//Borland C++Builder
//Copyright (c) 1987, 1998 Borland International Inc. All Rights Reserved.
//----------------------------------------------------------------------------
//---------------------------------------------------------------------------
#ifndef TMidiH
#define TMidiH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <OleCtnrs.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include "WPRich.hpp"

#include "XMLclass.h"
#include <Buttons.hpp>
#include "TFormDB.h"


class TComp : public TRect
{
public :
    TRect Original(void); // original size from xml
    TRect Current(void); // original size from component
    String getName(){return edit?edit->Name:box->Name;}
    TWinControl *getPtr(){return edit?(TWinControl *)edit:(TWinControl *)box;}

    int Height;
    double vls;
    TWPEdit *edit;
    TCheckBox *box;
    TXelm *elm;
	__property TRect Src = {read=Original};
	__property TRect Cur = {read=Current};

    TComp() : elm(NULL), edit(NULL), box(NULL){}
};



enum {FORM_NONE, FORM_PIC};
//---------------------------------------------------------------------------
class TFChild : public TForm
{
__published:	// IDE-managed Components
    TPanel *PanelMidi;
    TPageControl *PageControlMidi;
    TScrollBar *SBarV;
    TScrollBar *SBarH;

    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall WPEditEnter(TObject *Sender);
    void __fastcall ImageMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
    void __fastcall Refresh(TObject *Sender);
    void __fastcall PImageResize(TObject *Sender);
    void __fastcall ScrollBarHChange(TObject *Sender);
    void __fastcall PageControlMidiChange(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall FormMouseWheelDown(TObject *Sender, TShiftState Shift,
          TPoint &MousePos, bool &Handled);
    void __fastcall FormMouseWheelUp(TObject *Sender, TShiftState Shift,
          TPoint &MousePos, bool &Handled);
    void __fastcall FormClick(TObject *Sender);
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall FormResize(TObject *Sender);
private:	// User declarations
    TFileName FFileName;
    bool FSaved;
    double koef;
    TImage *img;
    TXelm *groupNode;
    vecxml lst; // list of all fields
    TWindowState FState;

    void __fastcall VerbClick(TObject *Sender);

    void SetNewField(TWPEdit *tedit);
    void __fastcall WPEditKeyPress(TObject *Sender, char &Key);
    void __fastcall WPEditShiftTabPressed(TObject *Sender);
    void __fastcall WPEditKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall WPEditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall fOnProgress(TObject* Sender, TProgressStage Stage, Byte PercentDone, bool RedrawNow, const Windows::TRect &R, const AnsiString Msg);

    TRect DrawImage(void);
    TForm *form;     // owner
    TRect srcRect;
    bool flag;
    bool shiftKey;

    void SetNode(TXelm *nodePage);
    bool LoadPicture(TXelm *page);
    void __fastcall CreateFromFile(TFileName FileName, bool Linked);
    void __fastcall SaveFile(TFileName FileName);
    TComp getNextField(TComp &obj, bool &ReviewFlag);
    TComp getPrevField(TComp &obj, bool &ReviewFlag);
    void SetVisibleRect(TRect &component);
    TRect getSrcRect(int Hor, int Vert);

    __property TFileName FileName = {read=FFileName};

	void InsertForm(String NameForm);
	void DeleteForm(String NameForm, bool Flag=false);
	void __fastcall LoadFromDB(long _id);
	void TrashForm(String NameForm, bool Flag);

    map<TXelm *, TWPEdit *> lstElement;
	map<long, String>  lstForm;
	map<long, String>::iterator i_ptr;
	String NameRecord;
public:		// User declarations
	TCheckBox *oldCh1, *oldCh2, *oldCh3, *oldCh4, *oldCh5;
	int year1, year2, year3, year4, year5;
//    vector<float> Money;

	void UnProcessMoney(void);
	void ProcessMoney(void);
	TWPEdit *NextEdit(TXelm *node);
	void UnProcessData(TWPEdit *Tyear, TWPEdit *Tmonth, TWPEdit *Tday, bool flag = false);
	bool ProcessData(int &Ptryear, TWPEdit *Tyear, TWPEdit *Tmonth, TWPEdit *Tday, bool flag = false);
	void LoadProcessMoney(void);

	void __fastcall WPEditClick(TObject *Sender);
	vector<TComp> lstRect;
	map<int, TComp> mapRect;
	int form_code; // need for printing
	int Page;

	bool printFlag, clearFlag, initFlag, saveFlag, saveAsFlag, scFlag, mouseFlag;
	String _guide; // unique number for this form
	TXelm *node;
	TWinControl *Element;

	void virtual __fastcall Clear(void);
	virtual void Init(void){}
	virtual void Save(void);
	virtual void SaveAs(void);

	void DrawElementMetaFile(TComp *val, Graphics::TMetafile *ptr);
	void SetComponents(TGraphic *bmp);

    Graphics::TBitmap *BrushBmp;
    TMetafile *BrushEmf;
    double proportion;


    void DrawElement(TComp *val, Graphics::TBitmap *ptr, bool print=true);
    Print();
    int _Width(), _Height();
    int topDist;
    TDateTime DT;
    TDateTime virtual getDate(void){return Now();} // get from DT put on Form
    void virtual putDate(void){DT = Now();}; // get from From and put to DT
    void virtual Calc(void){};
    void virtual PostLoad(void){}
    bool virtual BeforeSave(void){return false;} // true = error
    void virtual PostSave(void){}
    String readMoney(TXelm *record, String val);

    void SetForm( TForm *_form ); // set list of components from from
    bool Execute(TXelm *nodePage, long _id=-1L);
	virtual __fastcall TFChild(TComponent* Owner);
//	~TFChild();
};
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
extern TDateTime getFDate(long dta);
extern long getFDate(String dtstring);
extern long getFDate(TDateTime dta);
extern long getFDate(unsigned short year, unsigned short month, unsigned short day);
extern bool CheckRect(TRect &component, TRect &area);

//---------------------------------------------------------------------------
#endif
