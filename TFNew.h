//---------------------------------------------------------------------------

#ifndef TFNewH
#define TFNewH
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
#include <set>

#include "TSGrid.hpp"
#include "Grids_ts.hpp"
//---------------------------------------------------------------------------
class TFormNew : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel5;
    TLabel *Label2;
    TComboBox *ComboBox;
    TRadioButton *RbyName;
    TRadioButton *RbyDecription;
    TButton *BOk;
    TButton *BCancel;
    TtsGrid *tsGrid;
    void __fastcall tsGridDblClickCell(TObject *Sender, int DataCol,
          int DataRow, TtsClickPosition Pos);
    void __fastcall RbyNameClick(TObject *Sender);
    void __fastcall ComboBoxChange(TObject *Sender);
    void __fastcall tsGridButtonClick(TObject *Sender, int DataCol,
          int DataRow);
private:	// User declarations
    map<String, TXelm *> mapOrder;
    set<String> TypeDoc;

    void LoadCombo(void);
    void LoadList(void);
public:		// User declarations
    __fastcall TFormNew(TComponent* Owner);
};
//---------------------------------------------------------------------------
enum {COL_FORM=1, COL_DESC};
//---------------------------------------------------------------------------
#endif
