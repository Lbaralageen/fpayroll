//---------------------------------------------------------------------------

#ifndef TFOpenH
#define TFOpenH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "WPDefs.hpp"
#include "WPPrint.hpp"
#include "WPRich.hpp"
#include "WpWinCtr.hpp"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "Grids_ts.hpp"
#include "TSGrid.hpp"
#include "OvcBase.hpp"
#include "OvcEdCal.hpp"
#include "OvcEditF.hpp"
#include "OvcEdPop.hpp"
//---------------------------------------------------------------------------
struct dataDoc
{
    long ID;
    String SName, Name;
    TDateTime Date;
    dataDoc():ID(-1L){}
};
//---------------------------------------------------------------------------

class TFormOpen : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TPanel *Panel2;
    TPanel *Panel3;
    TButton *Button2;
    TButton *ButtonOpen;
    TPanel *Panel4;
    TButton *Button4;
    TtsGrid *tsGrid;
    TPanel *Panel5;
    TComboBox *ComboBoxType;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TEdit *EditText;
    TButton *Button1;
    TOvcDateEdit *EditFrom;
    TOvcController *OvcController;
    TOvcDateEdit *EditTo;
    void __fastcall EditFromDblClick(TObject *Sender);
    void __fastcall EditToDblClick(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall tsGridDblClickCell(TObject *Sender, int DataCol,
          int DataRow, TtsClickPosition Pos);
private:	// User declarations
    void LoadCombo(void);

    vector<dataDoc> lstDoc;
    vecxml lstForm;
public:		// User declarations
    __fastcall TFormOpen(TComponent* Owner);
};
//---------------------------------------------------------------------------
enum {COL_ID_OPEN=1, COL_FORM_OPEN, COL_DOC_OPEN, COL_DATE_OPEN};
//---------------------------------------------------------------------------
#endif
