//---------------------------------------------------------------------------

#ifndef TFormDBH
#define TFormDBH

#include "TMain.h"

#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <Db.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Db.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <Menus.hpp>

#include <map>

#include "TFrameDB.h"

typedef map<long, String> mapstr;

//---------------------------------------------------------------------------
class Tbase : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TPanel *Panel2;
    TButton *ButtonOK;
    TButton *ButtonCancel;
    TPanel *Panel3;
    TPanel *Panel4;
    TADOConnection *RemoteDB;
    TADOQuery *RemoteQuery;
private:	// User declarations
public:		// User declarations
    TFrameDB *FrameDB;
    int __fastcall Execute(void);

    bool CreateTables(TXelm * node, TProgressBar *bar);
    bool CreateFTables(TXelm * node, TProgressBar *bar);
    bool CreateTable(TXelm * node);
    bool CreateFTable(TXelm * node);

    void CreateIndex(TXelm * node );
    void CreatePrimaryKey(TXelm * node );
    bool RunSQL( String SQLcommand );
    void ExecSQLs(TXelm * node );

    mapstr Select( String NameTable, String Field, String Where);
    long MaxID(String table);
    long __fastcall CountRecords(TADOQuery *qr, String nameTable);
    long __fastcall MaxNumber(TADOQuery *qr, String field, String table, String where = "");
    vecstr __fastcall SQuery(String query, String field);
    vecflt __fastcall FQuery(String query, String field);
    String __fastcall SQuery0(String query, String field);
    long __fastcall LQuery0(String query, String field);
    double __fastcall FQuery0(String query, String field);
    bool IniDB(TProgressBar *bar, TXelm *elm_db); //  create structure of database : false - local
    bool __fastcall _Query(TADOQuery *qr, String query);
    String Ext; // extension for database
    String __fastcall SetDBStation(String dbname);
    String __fastcall SetDB(TADOConnection *db, String file);
    void CheckIniDB(void);
    __fastcall Tbase(TComponent* Owner);
};


extern PACKAGE Tbase *base;
//---------------------------------------------------------------------------
#endif
