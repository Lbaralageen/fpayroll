//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ParseString.h"
#include "TMain.h"

#include "TFormDB.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tbase *base;
//---------------------------------------------------------------------------
__fastcall Tbase::Tbase(TComponent* Owner)
    : TForm(Owner)
{
    FrameDB = new TFrameDB(this);
    FrameDB->Parent = this;

    String source = dom->root->getAttr(ATTR_TAG_Database);
    String before = base->RemoteDB->ConnectionString;
//    if( !source.IsEmpty() )
    {
        try
        {
          base->RemoteDB->ConnectionString = source;
          base->RemoteDB->Connected = true;
        }
        catch(...)
        {
            base->RemoteDB->ConnectionString = before;
            dom->root->setAttr(ATTR_TAG_Station, "");
            dom->root->setAttr(ATTR_TAG_Database, "");
            ShowMessage("You have to find or create database before!");
            FrameDB->ButtonStationClick(NULL);
            if( !FrameDB->EditPath->Text.IsEmpty() )
            {
              dom->root->setAttr(ATTR_TAG_Database, SetDBStation(FrameDB->EditPath->Text));
              dom->Save();
              FrameDB->CheckDB(dom);
            }else
            {
              FrameDB->CheckDB(dom);
              CheckIniDB();
            }
        }
    }
}
//---------------------------------------------------------------------------
// execute SQL command for table
map<long, String> Tbase::Select( String NameTable, String Field, String Where)
{
   map<long, String> result;
   if( NameTable.IsEmpty())
      return result;
   TADOQuery *qr = base->RemoteQuery;

   if( !base->RemoteDB->Connected )
      return result;

    String SQLcommand = "SELECT ID, " + Field + " FROM " + NameTable;
    if( !Where.IsEmpty() )
        SQLcommand += " WHERE " + Where;
    SQLcommand += ";";
   base->_Query(qr, SQLcommand);
   while( !qr->Eof )
   {
        long id = qr->FieldByName("ID")->AsInteger;
        String value = qr->FieldByName(Field)->AsString;
        result[id] = value;
        qr->Next();
   }
   qr->Close();
   return result;
}
//---------------------------------------------------------------------------
// execute SQL command for table
bool Tbase::RunSQL( String SQLcommand )
{
    if( SQLcommand.IsEmpty() )
        return false; // have a error
    TADOQuery *qr = RemoteQuery;
    try
    {
      qr->Close();
      qr->SQL->Clear();
      qr->SQL->Add( SQLcommand );
      qr->ExecSQL();
      qr->Close();
    }catch(...)
    {
        ShowMessage("Cannot execute this SQL coomand :" + SQLcommand);
        return false;
    };
    return true;
}
//---------------------------------------------------------------------------
// create index if we have
void Tbase::CreatePrimaryKey(TXelm * node )
{
    assert(node);
    vecxml lst = node->Select( NODE_TAG_Field );
    String key;
    int Nkey = 0;
    for(int i = 0; i < (int)lst.size(); i++)
    {
        key = lst[i]->getAttr(ATTR_TAG_Primary);
        if( key.IsEmpty() )
        {
            Nkey = i;
            break;
        }
        Application->ProcessMessages();
    }
    String kfld;
    for(int i = 0; i < Nkey; i++)
    {
        String val = lst[i]->atSName + ((i > 0 && i == Nkey-1) ? "" : ", ");
        if( kfld.IsEmpty() )
            kfld = val;
        else
            kfld += val;
    }
    key = "ALTER TABLE "+node->atSName+" ADD CONSTRAINT "+node->atSName+" PRIMARY KEY (";
    if( !kfld.IsEmpty() )
        RunSQL(key + kfld + ");"); // execute SQL operations for this table
}
//---------------------------------------------------------------------------
// create index if we have
void Tbase::CreateIndex(TXelm * node )
{
    assert(node);
    vecxml lst = node->Select( NODE_TAG_Field );
    for(int i = 0; i < (int)lst.size(); i++)
    {
        String index = lst[i]->getAttr(ATTR_TAG_Index);
        if( index.IsEmpty() )
            continue;
        Application->ProcessMessages();
        if( index == String(ATTR_TAG_Yes) )
            index = "CREATE INDEX " + lst[i]->atSName + " ON " + node->atSName + "("+lst[i]->atSName+");";
        else if( index == String(ATTR_TAG_UNIQUE) )
            index = "CREATE UNIQUE INDEX " + lst[i]->atSName + " ON " + node->atSName + "("+lst[i]->atSName+");";
        RunSQL(index); // execute SQL operations for this table
    }
}
//---------------------------------------------------------------------------
// execute all SQL command from node
void Tbase::ExecSQLs(TXelm * node )
{
    assert(node);
    vecxml lst = node->Select( NODE_TAG_SQL );
    for(int i = 0; i < (int)lst.size(); i++)
    {
        Application->ProcessMessages();
        RunSQL(lst[i]->atSQL); // execute current SQL operation
    }
}
//---------------------------------------------------------------------------
bool Tbase::CreateTable(TXelm * node)
{
   assert(node);
   TADOConnection *db = RemoteDB;
   TADOQuery *qr = RemoteQuery;
   FILE *f;
   try
   {
       f = fopen("createtmp.txt", "a");
       String nameTable = node->atSName;
       // we need to check existing this table or not
       TStringList *TableList = new TStringList;
       try{
          db->GetTableNames(TableList, false);
          for(int i = 0; i < TableList->Count; i++)
            if( TableList->Strings[i] == nameTable )
            {
               delete TableList;
               return true; // if table is existing, it's not a big problem, just don't touch that
            }
       }catch(...) { fclose(f); return false; }
       delete TableList;
        // create table in database
       String sql = "CREATE TABLE ";
       vecxml lst = node->Select(NODE_TAG_Field);
       sql += nameTable + " ( ";
       for(int j = 0; j < (int)lst.size(); j++)
            sql += lst[j]->atSName + " " + lst[j]->atSQL + ", ";
       sql = sql.SubString(1, sql.Length()-2) + ");";
       try
       {
          fputs((sql+"\n").c_str(), f);
          fclose(f);
          qr->Close();
          qr->SQL->Clear();
          qr->SQL->Add( sql );
          qr->ExecSQL();
          qr->Close();
       }
       catch(...){
          qr->Close();
          ShowMessage("Cannot create table :" + sql);
          fclose(f);
          return false;
       }
        // create index of table
       CreateIndex(node);
       CreatePrimaryKey(node);
       ExecSQLs(node ); // execute all sql commands for this table
   }catch(...){
      ShowMessage("Cannot create table :" + node->atName);
      fclose(f);
      return false;
   }
   fclose(f);
   return true;
}
//---------------------------------------------------------------------------
bool Tbase::CreateFTable(TXelm * node)
{
   assert(node);
   TADOConnection *db = RemoteDB;
   TADOQuery *qr = RemoteQuery;
   try
   {
       String nameTable = node->atSName;
       // we need to check existing this table or not
       TStringList *TableList = new TStringList;
       try{
          db->GetTableNames(TableList, false);
          for(int i = 0; i < TableList->Count; i++)
            if( TableList->Strings[i] == nameTable )
            {
               delete TableList;
               return true; // if table is existing, it's not a big problem, just don't touch that
            }
       }catch(...) { return false; }
       delete TableList;
        // create table in database
       String sql = "CREATE TABLE ";
       vecxml lstPage = node->Select(NODE_TAG_Item);
	   sql += nameTable + " ( ID LONG, Flag BIT, Short_Name VARCHAR(64), DT LONG ";

       int szPage = lstPage.size();
       for(int k = 0; k <= szPage; k++ )
       {
         if( k == szPage && szPage > 0 )
            break;
         if( szPage > 0 )
            node = lstPage[k];
         if( node->getAttr(ATTR_TAG_Database) == ATTR_TAG_No )
            continue;
         vecxml lst = node->Select(NODE_TAG_Field);
         for(int j = 0; j < (int)lst.size(); j++)
         {
             if( lst[j]->getAttr(ATTR_TAG_Database) == ATTR_TAG_No )
                continue;
             String t_SQL = lst[j]->getAttr(ATTR_TAG_Type);
             String sqlN = lst[j]->getAttr(ATTR_TAG_SQL);
             String leng = lst[j]->getAttr(ATTR_TAG_Length);

             if( sqlN.IsEmpty() )
             {
               if( leng.IsEmpty() )
                  leng = 16;
               if( leng == 1 )
                   sqlN = "BYTE";
               else
                   sqlN = "VARCHAR(" + leng + ")";
             }
             sql += ", " + lst[j]->atName + " " + sqlN;
         }
       }
	   sql += ");";

       try
       {
          qr->Close();
          qr->SQL->Clear();
          qr->SQL->Add( sql );
          qr->ExecSQL();
          qr->Close();
       }
       catch(...){
          qr->Close();
          ShowMessage("Cannot create table :" + sql);
          return false;
       }
        // create index of table
       CreateIndex(node);
       CreatePrimaryKey(node);
       ExecSQLs(node ); // execute all sql commands for this table
   }catch(...){
      ShowMessage("Cannot create table :" + node->atName);
      return false;
   }
   return true;
}
//---------------------------------------------------------------------------
// create aditional tables
bool Tbase::CreateTables(TXelm * node, TProgressBar *bar)
{
    assert(node);
    String NameTb = node->atName;
    vecxml lst = node->Select( NODE_TAG_Table );
    for(int i = 0; i < (int)lst.size(); i++)
    {
       bar->Max = lst.size();
       bar->Position = i;
       TXelm *node = lst[i];
       CreateTable( node );
       // if node 'table' has children then process it
       vecxml ChildLst = node->Select( NODE_TAG_Table );
       if( (int)ChildLst.size() > 0 )
            CreateTables(lst[i], bar);
    }
    // process groups of tables
    lst = node->Select( NODE_TAG_Group );
    for(int i = 0; i < (int)lst.size(); i++)
    {
       bar->Max = lst.size();
       bar->Position = i;
       CreateTables(lst[i], bar);
    }
    bar->Position = 0;
    return true;
}
//---------------------------------------------------------------------------
// create aditional tables
bool Tbase::CreateFTables(TXelm * node, TProgressBar *bar)
{
    assert(node);
    String NameTb = node->atName;

    vecxml lst = node->Select( NODE_TAG_Item );

    vecxml lstf = node->Select( NODE_TAG_Group );
    // merge two lists
    for(int i = 0; i < (int)lstf.size(); i++)
        lst.push_back( lstf[i] );

    int sz = (int)lst.size();
    for(int i = 0; i < sz; i++)
    {
       bar->Max = lst.size();
       bar->Position = i;
       TXelm *node = lst[i];
       CreateFTable( node );
    }
    bar->Position = 0;
    return true;
}
//---------------------------------------------------------------------------
//  create structure of database
bool Tbase::IniDB(TProgressBar *bar, TXelm *elm_db)
{
  if( elm_db == NULL )
    return false;
  if( !CreateTables(elm_db, bar) )
      ShowMessage("Cannot create tables in remote database");
  if( prj )
  {
      if( !CreateFTables(prj->root->Select0(NODE_TAG_Project), bar) )
          ShowMessage("Cannot create form tables");
  }
  return base->RemoteDB->Connected;
}                                                 
//---------------------------------------------------------------------------
String __fastcall Tbase::SetDBStation(String file)
{
    if( file.IsEmpty() )
        return "";
    return SetDB(RemoteDB, file);
}
//---------------------------------------------------------------------------
String __fastcall Tbase::SetDB(TADOConnection *db, String file)
{
    assert(db);
    db->Connected = false; // ??

    TParseString *parser = new TParseString;
    assert( parser );
    deque<String> word_list;
    parser->Delimiters = ';';
    int cnt = parser->Parse_Words( db->ConnectionString, word_list );
    bool DSfound =false;
    for(int i = 0; i < cnt; i++)
    {
        String val = word_list[i];
        if( val.Pos("Data Source") )
        {
            val = val.SetLength(val.Pos("="));
            word_list[i] = val + file;
            DSfound = true;
            break;
        }
    }
    delete parser;
    String result = word_list[0];
    for(int i = 1; i < cnt; i++)
        result += ";" + word_list[i];
    if( !DSfound ) // add data source if not found them
        result += ";Data Source=" + file;
    db->ConnectionString = result;
    try
    {
        db->Connected = true;
        return file;
    }
    catch(...){ShowMessage("Database doesn't allow to have a connection!");}
    return result;
}

//---------------------------------------------------------------------------
int __fastcall Tbase::Execute(void)
{
    return ShowModal();
}
//---------------------------------------------------------------------------
void Tbase::CheckIniDB(void)
{
       base->FrameDB->CheckDB(dom);   // check connect to DB

      TXelm *node = dom->Select(NODE_TAG_Database)->FindName(ATTR_TAG_Remote);
      if( node )
      {
        FormMain->StatusBar->Panels->Items[0]->Text = "Check structure of DB! ...";
        base->IniDB(FormMain->ProgressBar, node);
      }
      FormMain->StatusBar->Panels->Items[0]->Text = "Done ...";
      dom->root->setAttr(ATTR_TAG_Database, base->RemoteDB->ConnectionString);
      dom->Save();
}
//---------------------------------------------------------------------------
bool __fastcall TFormMain::DatabaseOptionsMenu(void)
{
    if( base->Execute() == mrOk )
    {
       base->CheckIniDB();
       return true;
    }
    return false;

}
//---------------------------------------------------------------------------
void __fastcall TFormMain::DatabaseOptionsClick(TObject *Sender)
{
    DatabaseOptionsMenu() ;
}
//---------------------------------------------------------------------------
long Tbase::MaxID(String table)
{
   TADOQuery *qr = base->RemoteQuery;
   long maxnum = 0L;
   try
   {
       String sql = "SELECT ID FROM "+ table + ";";
       if( base->_Query(qr, sql) )
       {
         if( !qr->Eof )
         {
           sql = "SELECT Max(ID) AS tempCount FROM "+ table + ";";
           base->_Query(qr, sql);
           maxnum = qr->FieldByName("tempCount")->AsInteger;
         }
         qr->Close();
       }
   }
   catch(...){return 0L;}
   return maxnum;
}
//---------------------------------------------------------------------------
long __fastcall Tbase::CountRecords(TADOQuery *qr, String nameTable)
{
   long count = 0;
   try
   {
       String sql = "SELECT COUNT(ID) AS tempCount FROM "+ nameTable + ";";
       _Query(qr, sql);
       count = qr->FieldByName("tempCount")->AsInteger;
       qr->Close();
   }
   catch(...){return 0L;}
   return count;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------





