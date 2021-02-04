//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TMain.h"

#include "TFormDB.h"

#include "TFrameDB.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//TFrameDB *FrameDB;
//---------------------------------------------------------------------------
__fastcall TFrameDB::TFrameDB(TComponent* Owner)
    : TFrame(Owner), obj(NULL)  
{
  Visible = true;
  Align = alClient;
  Bip->Enabled = base->RemoteDB->Connected;
  
    ButtonStation->Enabled = true;
    LabelPathStation->Enabled = true;
    EditPath->Enabled = true;
}
//---------------------------------------------------------------------------
bool __fastcall TFrameDB::Execute(TWinControl *owner, TXobj *_obj)
{
  Parent = owner;
  assert(_obj);
  obj = _obj;
  TXelm *project = obj->Project;

  EditUser->Text = project->getAttr(ATTR_TAG_User);
  EditPassword->Text = project->getAttr(ATTR_TAG_Password);
  return true;
}
bool TFrameDB::CheckDB(TXobj *obj)
{
  if( obj == NULL )
    return false;
  Bip->Enabled = base->RemoteDB->Connected;
  if( !Bip->Enabled ) // hasn't connect
  {
        String db;
        if( obj )  // try to get path from project info
            db = obj->root->getAttr(ATTR_TAG_Station);
        if( db.IsEmpty() )
        {
            if( EditPath->Text.IsEmpty() )
            {
              db = GlobalPath + "Projects\\";
              if( !PathExists(db) )
                  CreateDir(db);
              db += "Station.mdb";
            }else
              db = EditPath->Text;
        }

        if( !FileExists(db) )
            CopyFile((GlobalPath + "Template.mdb").c_str(), db.c_str(), true);

        db = base->SetDBStation(db);
        if( obj )
            obj->root->setAttr(ATTR_TAG_Station, db);
  }
  Bip->Enabled = base->RemoteDB->Connected;
  if( !Bip->Enabled )
       obj->root->setAttr(ATTR_TAG_Station, "");
}
//---------------------------------------------------------------------------
void __fastcall TFrameDB::BtBConnectClick(TObject *Sender)
{
    CheckDB(dom);
}
//---------------------------------------------------------------------------
void __fastcall TFrameDB::ButtonStationClick(TObject *Sender)
{
    if( OpenDialog->Execute() )
    {
        String file = OpenDialog->FileName;
        if( file.Pos(".") < 1 )
            file += ".mdb";
        EditPath->Text = file;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFrameDB::BitBtnCheckClick(TObject *Sender)
{
    ((Tbase *)Parent)->CheckIniDB();
}
//---------------------------------------------------------------------------

