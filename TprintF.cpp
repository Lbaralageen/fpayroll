//----------------------------------------------------------------------------
//Borland C++Builder
//Copyright (c) 1987, 1998 Borland International Inc. All Rights Reserved.
//----------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

int ScaleX, ScaleY, I, Count;
HDC *DC;
TForm *F;

//----------------------------------------------------------------------------
TRect ScaleToPrinter(TRect &R)
{
  R.Top = (R.Top + F->VertScrollBar->Position) * ScaleY;
  R.Left = (R.Left + F->HorzScrollBar->Position) * ScaleX;
  R.Bottom = (R.Bottom + F->VertScrollBar->Position) * ScaleY;
  R.Right = (R.Right + F->HorzScrollBar->Position) * ScaleY;
  return R;
}

void PrintMComponent(TMemo *MC)
{
    char C[255];
    int CLen;
    WORD Format;
    TRect R;

    Printer->Canvas->Font = MC->Font;
    DC = Printer->CanvasMCHandle;
    R = ScaleToPrinter(MCMCBoundsRect);
    TCustomLabel *lbl = dynamic_cast<TCustomLabel *>(FMCComponents[I]);
    if( !(lbl != NULL && (MC->BorderStyle == bsSingle) )
        Printer->Canvas->Rectangle(R.Left,R.Top,R.Right,R.Bottom);
    Format = DT_LEFT;
    if( F->Components[I] is TEdit) or (F.Components[I] is TCustomMaskEdit) then
Format := Format or DT_SINGLELINE or DT_VCENTER
else
begin
if MC.WordWrap then Format := DT_WORDBREAK;
if MC.Alignment = taCenter then Format := Format or DT_CENTER;
if MC.Alignment = taRightJustify then Format := Format or DT_RIGHT;
R.Bottom := R.Bottom + Printer.Canvas.Font.Height;
end;
CLen := MC.GetTextBuf(C,255);
R.Left := R.Left + ScaleX + ScaleX;
WinProcs.DrawText(DC, C, CLen, R, Format);
inc(Count);
end;
//----------------------------------------------------------------------------
int PrintForm(TForm *AForm, long ATag)
{
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

