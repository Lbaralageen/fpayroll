object FormOpen: TFormOpen
  Left = 341
  Top = 227
  Width = 528
  Height = 344
  HelpContext = 12
  Caption = 'Find Form'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 520
    Height = 281
    HelpContext = 12
    Align = alClient
    TabOrder = 0
    object tsGrid: TtsGrid
      Left = 1
      Top = 105
      Width = 518
      Height = 175
      HelpContext = 1
      Align = alClient
      CheckBoxStyle = stCheck
      HeadingFont.Charset = DEFAULT_CHARSET
      HeadingFont.Color = clWindowText
      HeadingFont.Height = -10
      HeadingFont.Name = 'MS Sans Serif'
      HeadingFont.Style = []
      ParentShowHint = False
      Rows = 0
      ShowHint = True
      StoreData = True
      TabOrder = 0
      Version = '2.01'
      OnDblClickCell = tsGridDblClickCell
      ColProperties = <
        item
          DataCol = 1
          FieldName = 'ID'
          Col.FieldName = 'ID'
          Col.Visible = False
        end
        item
          DataCol = 2
          FieldName = 'Form'
          Col.FieldName = 'Form'
          Col.Width = 100
        end
        item
          DataCol = 3
          FieldName = 'Document'
          Col.FieldName = 'Document'
          Col.Width = 255
        end
        item
          DataCol = 4
          FieldName = 'Date'
          Col.FieldName = 'Date'
          Col.Width = 97
        end>
      Data = {0000000000000000}
    end
    object Panel5: TPanel
      Left = 1
      Top = 1
      Width = 518
      Height = 104
      HelpContext = 12
      Align = alTop
      TabOrder = 1
      object Label1: TLabel
        Left = 7
        Top = 7
        Width = 55
        Height = 13
        Caption = 'Form Types'
      end
      object Label2: TLabel
        Left = 176
        Top = 7
        Width = 49
        Height = 13
        Caption = 'From Date'
      end
      object Label3: TLabel
        Left = 299
        Top = 7
        Width = 39
        Height = 13
        Caption = 'To Date'
      end
      object Label4: TLabel
        Left = 7
        Top = 52
        Width = 28
        Height = 13
        Caption = 'Name'
      end
      object ComboBoxType: TComboBox
        Left = 7
        Top = 26
        Width = 156
        Height = 21
        ItemHeight = 13
        TabOrder = 0
      end
      object EditText: TEdit
        Left = 7
        Top = 72
        Width = 286
        Height = 24
        TabOrder = 1
      end
      object Button1: TButton
        Left = 308
        Top = 72
        Width = 102
        Height = 20
        Caption = '&Find'
        TabOrder = 2
        OnClick = Button1Click
      end
      object EditFrom: TOvcDateEdit
        Left = 176
        Top = 24
        Width = 115
        Height = 24
        AllowIncDec = True
        ButtonGlyph.Data = {
          1A020000424D1A0200000000000036000000280000000B0000000B0000000100
          200000000000E401000000000000000000000000000000000000008080000000
          0000000000000000000000000000000000000000000000000000000000000000
          00000080800000000000C0C0C000C0C0C00080808000C0C0C000C0C0C0008080
          8000C0C0C000C0C0C000C0C0C00000000000000000000000FF00C0C0C0008080
          80000000FF00C0C0C000808080000000FF00C0C0C000C0C0C000000000000000
          0000808080008080800080808000808080008080800080808000808080008080
          8000808080000000000000000000C0C0C000C0C0C00080808000C0C0C000C0C0
          C00080808000C0C0C000C0C0C000C0C0C00000000000000000000000FF00C0C0
          C000808080000000FF00C0C0C000808080000000FF00C0C0C000C0C0C0000000
          0000000000008080800080808000808080008080800080808000808080008080
          800080808000808080000000000000000000C0C0C000C0C0C00080808000C0C0
          C000C0C0C00080808000C0C0C000C0C0C000C0C0C00000000000000000000000
          FF00C0C0C000808080000000FF00C0C0C000808080000000FF00C0C0C000C0C0
          C000000000000000000000000000000000000000000000000000000000000000
          00000000000000000000000000000000000000808000FF000000FF0000008080
          800080808000808080008080800080808000FF000000FF00000000808000}
        Controller = OvcController
        Epoch = 0
        ForceCentury = False
        LabelInfo.Visible = False
        PopupAnchor = paLeft
        PopupColors.ActiveDay = clRed
        PopupColors.ColorScheme = cscalCustom
        PopupColors.DayNames = clMaroon
        PopupColors.Days = clBlack
        PopupColors.InactiveDays = clGray
        PopupColors.MonthAndYear = clBlue
        PopupColors.Weekend = clRed
        PopupDateFormat = dfLong
        PopupDayNameWidth = 3
        PopupFont.Charset = DEFAULT_CHARSET
        PopupFont.Color = clWindowText
        PopupFont.Height = -11
        PopupFont.Name = 'MS Sans Serif'
        PopupFont.Style = []
        PopupHeight = 140
        PopupOptions = [cdoShortNames, cdoShowYear, cdoShowInactive, cdoShowRevert, cdoShowToday, cdoShowNavBtns]
        PopupWidth = 200
        PopupWeekStarts = dtSunday
        ReadOnly = False
        RequiredFields = [rfMonth, rfDay]
        ShowButton = True
        TabOrder = 3
        TodayString = '/'
      end
      object EditTo: TOvcDateEdit
        Left = 296
        Top = 24
        Width = 115
        Height = 24
        AllowIncDec = True
        ButtonGlyph.Data = {
          1A020000424D1A0200000000000036000000280000000B0000000B0000000100
          200000000000E401000000000000000000000000000000000000008080000000
          0000000000000000000000000000000000000000000000000000000000000000
          00000080800000000000C0C0C000C0C0C00080808000C0C0C000C0C0C0008080
          8000C0C0C000C0C0C000C0C0C00000000000000000000000FF00C0C0C0008080
          80000000FF00C0C0C000808080000000FF00C0C0C000C0C0C000000000000000
          0000808080008080800080808000808080008080800080808000808080008080
          8000808080000000000000000000C0C0C000C0C0C00080808000C0C0C000C0C0
          C00080808000C0C0C000C0C0C000C0C0C00000000000000000000000FF00C0C0
          C000808080000000FF00C0C0C000808080000000FF00C0C0C000C0C0C0000000
          0000000000008080800080808000808080008080800080808000808080008080
          800080808000808080000000000000000000C0C0C000C0C0C00080808000C0C0
          C000C0C0C00080808000C0C0C000C0C0C000C0C0C00000000000000000000000
          FF00C0C0C000808080000000FF00C0C0C000808080000000FF00C0C0C000C0C0
          C000000000000000000000000000000000000000000000000000000000000000
          00000000000000000000000000000000000000808000FF000000FF0000008080
          800080808000808080008080800080808000FF000000FF00000000808000}
        Controller = OvcController
        Epoch = 0
        ForceCentury = False
        LabelInfo.Visible = False
        PopupAnchor = paLeft
        PopupColors.ActiveDay = clRed
        PopupColors.ColorScheme = cscalCustom
        PopupColors.DayNames = clMaroon
        PopupColors.Days = clBlack
        PopupColors.InactiveDays = clGray
        PopupColors.MonthAndYear = clBlue
        PopupColors.Weekend = clRed
        PopupDateFormat = dfLong
        PopupDayNameWidth = 3
        PopupFont.Charset = DEFAULT_CHARSET
        PopupFont.Color = clWindowText
        PopupFont.Height = -11
        PopupFont.Name = 'MS Sans Serif'
        PopupFont.Style = []
        PopupHeight = 140
        PopupOptions = [cdoShortNames, cdoShowYear, cdoShowInactive, cdoShowRevert, cdoShowToday, cdoShowNavBtns]
        PopupWidth = 200
        PopupWeekStarts = dtSunday
        ReadOnly = False
        RequiredFields = [rfMonth, rfDay]
        ShowButton = True
        TabOrder = 4
        TodayString = '/'
      end
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 281
    Width = 520
    Height = 36
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    object Panel3: TPanel
      Left = 346
      Top = 0
      Width = 174
      Height = 36
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 0
      object Button2: TButton
        Left = 91
        Top = 7
        Width = 74
        Height = 20
        Caption = 'Cancel'
        ModalResult = 2
        TabOrder = 0
      end
      object ButtonOpen: TButton
        Left = 7
        Top = 7
        Width = 73
        Height = 20
        Caption = 'Open'
        ModalResult = 1
        TabOrder = 1
      end
    end
    object Panel4: TPanel
      Left = 0
      Top = 0
      Width = 346
      Height = 36
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 1
      object Button4: TButton
        Left = 7
        Top = 7
        Width = 73
        Height = 20
        Caption = 'Delete'
        ModalResult = 6
        TabOrder = 0
      end
    end
  end
  object OvcController: TOvcController
    EntryCommands.TableList = (
      'Default'
      True
      ()
      'WordStar'
      False
      ()
      'Grid'
      False
      ())
    EntryOptions = [efoAutoSelect, efoBeepOnError, efoInsertPushes]
    Epoch = 2000
    Left = 8
    Top = 8
  end
end
