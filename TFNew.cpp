//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TMain.h"

#include "TFNew.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "WPDefs"
#pragma link "WPPrint"
#pragma link "WPRich"
#pragma link "WpWinCtr"
#pragma link "Grids_ts"
#pragma link "TSGrid"
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
__fastcall TFormNew::TFormNew(TComponent* Owner)
    : TForm(Owner)
{

  Width = 450;
  Height = 270;
  BorderStyle = bsSingle;
  Position = poMainFormCenter;
  WindowState = wsNormal;

  LoadCombo();
  
  LoadList();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::BNewClick(TObject *Sender)
{
    TFormNew *FormNew = new TFormNew(this);
    if( FormNew->ShowModal() == mrOk )
    {
      int row = FormNew->tsGrid->CurrentDataRow;
      if( row > NULL )
      {
          String txt = FormNew->tsGrid->Cell[COL_FORM][row];
          TXelm *elm = prj->Select(NODE_TAG_Project)->FindName(txt);
          String _caption = txt + "  New ";
          if( elm != NULL )
              CallForm(elm, -1L, _caption);
      }
    }
    delete FormNew;
}
//---------------------------------------------------------------------------
void __fastcall TFormNew::tsGridDblClickCell(TObject *Sender, int DataCol,
      int DataRow, TtsClickPosition Pos)
{
    ModalResult = mrOk;
}
//---------------------------------------------------------------------------
// if order - true, then sort by name
void TFormNew::LoadList(void)
{
    bool order = RbyName->Checked;

    mapOrder.clear();
    // load all single forms
    vecxml lst = prj->Select(NODE_TAG_Project)->Select(NODE_TAG_Item);
    for(int i = 0; i < (int)lst.size(); i++)
        if( order )
            mapOrder[lst[i]->atName] = lst[i];
        else
            mapOrder[lst[i]->getAttr(ATTR_TAG_Description)] = lst[i];
    // load all mulipage forms
    lst = prj->Select(NODE_TAG_Project)->Select(NODE_TAG_Group);
    for(int i = 0; i < (int)lst.size(); i++)
        if( order )
            mapOrder[lst[i]->atName] = lst[i];
        else
            mapOrder[lst[i]->getAttr(ATTR_TAG_Description)] = lst[i];

    int row = 1;
    map<String, TXelm *>::iterator i_ptr;

    bool allTypes = ComboBox->ItemIndex == 0;

    for( i_ptr = mapOrder.begin(); i_ptr != mapOrder.end(); i_ptr++)
    {
        TXelm *elm = (*i_ptr).second;

        if( allTypes || elm->atType == ComboBox->Text )
        {
          tsGrid->Rows = row;  
          tsGrid->Cell[COL_FORM][row] = elm->atName;
          tsGrid->Cell[COL_DESC][row++] = elm->getAttr(ATTR_TAG_Description);
        }
    }
}
//---------------------------------------------------------------------------
// if order - true, then sort by name
void TFormNew::LoadCombo(void)
{
    ComboBox->Clear();
    ComboBox->Items->Add("All types");

    // load all single forms
    vecxml lst = prj->Select(NODE_TAG_Project)->Select(NODE_TAG_Item);
    for(int i = 0; i < (int)lst.size(); i++)
        TypeDoc.insert(lst[i]->atType);

    // load all mulipage forms
    lst = prj->Select(NODE_TAG_Project)->Select(NODE_TAG_Group);
    for(int i = 0; i < (int)lst.size(); i++)
        TypeDoc.insert(lst[i]->atType);

    set<String>::iterator s_ptr;
    for( s_ptr = TypeDoc.begin(); s_ptr != TypeDoc.end(); s_ptr++)
        ComboBox->Items->Add(*s_ptr);
    ComboBox->ItemIndex = 0;
}
//---------------------------------------------------------------------------
void __fastcall TFormNew::RbyNameClick(TObject *Sender)
{
   tsGrid->Rows = 0;
   LoadList();
}
//---------------------------------------------------------------------------
void __fastcall TFormNew::ComboBoxChange(TObject *Sender)
{
   LoadList();
}
//---------------------------------------------------------------------------
void __fastcall TFormNew::tsGridButtonClick(TObject *Sender, int DataCol,
      int DataRow)
{
    ComboBox->ItemIndex = ComboBox->Items->IndexOf(DataRow);
}
//---------------------------------------------------------------------------

