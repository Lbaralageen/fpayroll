//---------------------------------------------------------------------------

#ifndef FGST34aH
#define FGST34aH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>

#include "WPDefs.hpp"
#include "WPPrint.hpp"
#include "WPRich.hpp"
#include "WpWinCtr.hpp"

#include "TMidi.h"
//---------------------------------------------------------------------------

class TTGST34a : public TFChild
{
__published:	// IDE-managed Components
    TWPEdit *EditName;
    TWPEdit *EditFrom;
    TWPEdit *EditTo;
    TWPEdit *EditDate;
    TWPEdit *Edit101;
    TWPEdit *Edit103;
    TWPEdit *Edit104;
    TWPEdit *Edit106;
    TWPEdit *Edit107;
    TWPEdit *Edit111;
    TWPEdit *Edit205;
    TWPEdit *Edit405;
    TWPEdit *Edit114;
    TWPEdit *Edit105;
    TWPEdit *Edit108;
    TWPEdit *Edit109;
    TWPEdit *Edit112;
    TWPEdit *Edit113A;
    TWPEdit *Edit113B;
    TWPEdit *Edit113C;
    TWPEdit *Edit115;
    TWPEdit *Edit101A;
    TWPEdit *Edit103A;
    TWPEdit *Edit106A;
    TWPEdit *Edit107A;
    TWPEdit *Edit110A;
    TWPEdit *Edit111A;
    TWPEdit *Edit205A;
    TWPEdit *Edit405A;
    TWPEdit *Edit104A;
    TWPEdit *Edit105A;
    TWPEdit *Edit108A;
    TWPEdit *Edit109A;
    TWPEdit *Edit112A;
    TWPEdit *Edit113BA;
    TWPEdit *Edit113CA;
    TWPEdit *Edit115A;
    TWPEdit *Edit109Z;
    TWPEdit *Edit113AZ;
    TWPEdit *Edit113AA;
    TWPEdit *Edit113CZ;
    TWPEdit *Edit110;
    TWPEdit *EditDay;
    TWPEdit *EditMonth;
    TWPEdit *EditYear;
	TWPEdit *Edit101_1;
	TWPEdit *Edit101_2;
	TWPEdit *Edit101_3;
	TWPEdit *Edit101_4;
	TWPEdit *Edit101_5;
	TWPEdit *Edit101_6;
	TWPEdit *Edit101_7;
	TWPEdit *Edit101_8;
	TWPEdit *Edit101_9;
	TWPEdit *Edit101_10;
	TWPEdit *Edit110_1;
	TWPEdit *Edit110_2;
	TWPEdit *Edit110_3;
	TWPEdit *Edit110_4;
	TWPEdit *Edit110_5;
	TWPEdit *Edit110_6;
	TWPEdit *Edit110_7;
	TWPEdit *Edit110_8;
	TWPEdit *Edit110_9;
	TWPEdit *Edit110A_1;
	TWPEdit *Edit110A_2;
	TWPEdit *Edit111_1;
	TWPEdit *Edit111_2;
	TWPEdit *Edit111_3;
	TWPEdit *Edit111_4;
	TWPEdit *Edit111_5;
	TWPEdit *Edit111_6;
	TWPEdit *Edit111_7;
	TWPEdit *Edit111_8;
	TWPEdit *Edit111_9;
	TWPEdit *Edit111A_1;
	TWPEdit *Edit111A_2;
	TWPEdit *Edit205_1;
	TWPEdit *Edit205_2;
	TWPEdit *Edit205_3;
	TWPEdit *Edit205_4;
	TWPEdit *Edit205_5;
	TWPEdit *Edit205_6;
	TWPEdit *Edit205_7;
	TWPEdit *Edit205_8;
	TWPEdit *Edit205_9;
	TWPEdit *Edit205A_1;
	TWPEdit *Edit205A_2;
	TWPEdit *Edit405_1;
	TWPEdit *Edit405_2;
	TWPEdit *Edit405_3;
	TWPEdit *Edit405_4;
	TWPEdit *Edit405_5;
	TWPEdit *Edit405_6;
	TWPEdit *Edit405_7;
	TWPEdit *Edit405_8;
	TWPEdit *Edit405_9;
	TWPEdit *Edit405A_1;
	TWPEdit *Edit405A_2;
	TWPEdit *Edit105_1;
	TWPEdit *Edit105_2;
	TWPEdit *Edit105_3;
	TWPEdit *Edit105_4;
	TWPEdit *Edit105_5;
	TWPEdit *Edit105_6;
	TWPEdit *Edit105_7;
	TWPEdit *Edit105_8;
	TWPEdit *Edit105_9;
	TWPEdit *Edit105A_1;
	TWPEdit *Edit105A_2;
	TWPEdit *Edit108_1;
	TWPEdit *Edit108_2;
	TWPEdit *Edit108_3;
	TWPEdit *Edit108_4;
	TWPEdit *Edit108_5;
	TWPEdit *Edit108_6;
	TWPEdit *Edit108_7;
	TWPEdit *Edit108_8;
	TWPEdit *Edit108_9;
	TWPEdit *Edit108A_1;
	TWPEdit *Edit108A_2;
	TWPEdit *Edit109_1;
	TWPEdit *Edit109_2;
	TWPEdit *Edit109_3;
	TWPEdit *Edit109_4;
	TWPEdit *Edit109_5;
	TWPEdit *Edit109_6;
	TWPEdit *Edit109_7;
	TWPEdit *Edit109_8;
	TWPEdit *Edit109_9;
	TWPEdit *Edit109A_1;
	TWPEdit *Edit109A_2;
	TWPEdit *Edit109_M;
	TWPEdit *Edit114_1;
	TWPEdit *Edit114_2;
	TWPEdit *Edit114_3;
	TWPEdit *Edit114_4;
	TWPEdit *Edit114_5;
	TWPEdit *Edit114_6;
	TWPEdit *Edit114_7;
	TWPEdit *Edit114_8;
	TWPEdit *Edit114_9;
	TWPEdit *Edit114A_1;
	TWPEdit *Edit114A_2;
	TWPEdit *Edit115_1;
	TWPEdit *Edit115_2;
	TWPEdit *Edit115_3;
	TWPEdit *Edit115_4;
	TWPEdit *Edit115_5;
	TWPEdit *Edit115_6;
	TWPEdit *Edit115_7;
	TWPEdit *Edit115_8;
	TWPEdit *Edit115_9;
	TWPEdit *Edit115A_1;
	TWPEdit *Edit115A_2;
	TWPEdit *EditBN;
public:		// User declarations
    void __fastcall Sum112Change(TObject *Sender);
    void __fastcall SetEdit(void);
    void __fastcall Sum105Change(TObject *Sender);
    void __fastcall Sum108Change(TObject *Sender);
    void __fastcall Sum109Change(TObject *Sender);
    void __fastcall Sum113Change(TObject *Sender);
    void __fastcall Sum113aChange(TObject *Sender);
    void __fastcall Sum1145Change(TObject *Sender);
    void __fastcall Sum113cChange(TObject *Sender);
    void Calc();

    void virtual PostLoad(void);
    bool virtual BeforeSave(void);
    void virtual PostSave(void);
    
    TDateTime virtual getDate(void); // get from DT put on Form
    void virtual putDate(void); // get from From and put to DT
    void Init(void);
    __fastcall TTGST34a(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
