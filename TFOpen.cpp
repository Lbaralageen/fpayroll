//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "TMain.h"

#include "TFOpen.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "WPDefs"
#pragma link "WPPrint"
#pragma link "WPRich"
#pragma link "WpWinCtr"
#pragma link "Grids_ts"
#pragma link "TSGrid"
#pragma link "OvcBase"
#pragma link "OvcEdCal"
#pragma link "OvcEditF"
#pragma link "OvcEdPop"
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
__fastcall TFormOpen::TFormOpen(TComponent* Owner)
    : TForm(Owner)
{
    LoadCombo();
    
  Width = 540;
  Height = 350;
  
  BorderStyle = bsSingle;
  Position = poMainFormCenter;
  WindowState = wsNormal;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Open1Click(TObject *Sender)
{
    TFormOpen *FormOpen = new TFormOpen(this);
    if( FormOpen->ShowModal() == mrOk )
    {
      int row = FormOpen->tsGrid->CurrentDataRow;
      if( row > NULL )
      {
          String txt = FormOpen->tsGrid->Cell[COL_FORM_OPEN][row];
          long id = FormOpen->tsGrid->Cell[COL_ID_OPEN][row];
          TXelm *elm = prj->Select(NODE_TAG_Project)->FindSName(txt);
          String _caption = txt + " "+FormOpen->tsGrid->Cell[COL_DOC_OPEN][row];
          if( elm != NULL )
              CallForm(elm, id, _caption);
      }
    }
    delete FormOpen;
}
//---------------------------------------------------------------------------
void TFormOpen::LoadCombo(void)
{
    lstForm.clear();
    lstForm = prj->Select(NODE_TAG_Project)->Select(NODE_TAG_Item);
    vecxml lst = prj->Select(NODE_TAG_Project)->Select(NODE_TAG_Group);

    for(int i = 0; i < (int)lst.size(); i++)
        lstForm.push_back(lst[i]);

    ComboBoxType->Clear();
    ComboBoxType->Items->Add("All forms");
    
    for(int i = 0; i < (int)lstForm.size(); i++)
        ComboBoxType->Items->Add(lstForm[i]->atSName);
    ComboBoxType->ItemIndex = 0;
}
//---------------------------------------------------------------------------
void __fastcall TFormOpen::EditFromDblClick(TObject *Sender)
{
    EditFrom->Text = DateToStr(Now());
}
//---------------------------------------------------------------------------
void __fastcall TFormOpen::EditToDblClick(TObject *Sender)
{
    EditTo->Text = DateToStr(Now());
}
//---------------------------------------------------------------------------
static void LoadLstTitul(vector<dataDoc> &lst, String Table, String Where)
{
   if( Table.IsEmpty() )
    return;
   TADOQuery *qr = base->RemoteQuery;
   if( !Where.IsEmpty() )
        Where = " WHERE " + Where;
   String SQLcommand = "SELECT * FROM " + Table + Where + ";";
   base->_Query(qr, SQLcommand);
   while( !qr->Eof )
   {
        dataDoc val;
        val.ID = qr->FieldByName(ATTR_TAG_ID)->AsInteger;
        val.Name = qr->FieldByName(ATTR_TAG_Short_Name)->AsString;
        val.SName = Table;
        val.Date = getFDate(qr->FieldByName("DT")->AsInteger);

        lst.push_back(val);
        qr->Next();
   }
   qr->Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormOpen::Button1Click(TObject *Sender)
{
    lstDoc.clear();
    tsGrid->Rows = 0;
    int row = 1;
//    if( ComboBoxType->Text.Trim() == "?" )
    {
        String Where;
        TDateTime dtFrom = EditFrom->Date;
        TDateTime dtTo = EditTo->Date;

        if( (int)dtFrom > 0 )
			Where = " DT > " + String(getFDate(dtFrom));
        if( (int)dtTo > 0 )
        {
            if( !Where.IsEmpty() )
                Where += " AND ";
            Where += " DT < " + String(getFDate(dtTo));
        }
        if( !EditText->Text.IsEmpty() )
        {
            if( !Where.IsEmpty() )
                Where += " AND ";
            Where += " EditName LIKE '%" + EditText->Text.Trim() + "%' ";
        }
        if( !Where.IsEmpty() )
            Where = "(" + Where + ") AND (Flag = No )";

        if( ComboBoxType->ItemIndex <= 0 )
        {
          for(int i = 0; i < (int)lstForm.size(); i++)
          {
              String table = lstForm[i]->atSName;
              LoadLstTitul(lstDoc, table, Where.Trim());
          }
        }else
              LoadLstTitul(lstDoc, ComboBoxType->Text, Where.Trim());

        tsGrid->Rows = lstDoc.size();
        for(int row = 1; row <= tsGrid->Rows; row++)
        {
            tsGrid->Cell[COL_ID_OPEN][row] = lstDoc[row-1].ID;
            tsGrid->Cell[COL_FORM_OPEN][row] = lstDoc[row-1].SName;
            tsGrid->Cell[COL_DOC_OPEN][row] = lstDoc[row-1].Name;
            tsGrid->Cell[COL_DATE_OPEN][row] = lstDoc[row-1].Date.FormatString("MM/dd/yyyy");
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormOpen::tsGridDblClickCell(TObject *Sender, int DataCol,
      int DataRow, TtsClickPosition Pos)
{
    ModalResult = mrOk;
}
//---------------------------------------------------------------------------



