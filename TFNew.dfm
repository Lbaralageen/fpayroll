object FormNew: TFormNew
  Left = 348
  Top = 222
  HelpContext = 1
  BorderStyle = bsSingle
  Caption = 'Open New Form'
  ClientHeight = 309
  ClientWidth = 530
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 120
  TextHeight = 16
  object Panel5: TPanel
    Left = 0
    Top = 196
    Width = 530
    Height = 113
    HelpContext = 1
    Align = alBottom
    TabOrder = 0
    object Label2: TLabel
      Left = 16
      Top = 16
      Width = 46
      Height = 16
      Caption = 'Display'
    end
    object ComboBox: TComboBox
      Left = 9
      Top = 41
      Width = 144
      Height = 24
      ItemHeight = 16
      TabOrder = 0
      OnChange = ComboBoxChange
      Items.Strings = (
        'All')
    end
    object RbyName: TRadioButton
      Left = 176
      Top = 16
      Width = 113
      Height = 17
      Caption = 'By Form Name'
      Checked = True
      TabOrder = 1
      TabStop = True
      OnClick = RbyNameClick
    end
    object RbyDecription: TRadioButton
      Left = 176
      Top = 57
      Width = 113
      Height = 16
      Caption = 'By Description'
      TabOrder = 2
      OnClick = RbyNameClick
    end
    object BOk: TButton
      Left = 320
      Top = 16
      Width = 92
      Height = 27
      Caption = 'Open'
      ModalResult = 1
      TabOrder = 3
    end
    object BCancel: TButton
      Left = 320
      Top = 57
      Width = 92
      Height = 27
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 4
    end
  end
  object tsGrid: TtsGrid
    Left = 0
    Top = 0
    Width = 530
    Height = 196
    HelpContext = 1
    Align = alClient
    CheckBoxStyle = stCheck
    Cols = 2
    HeadingFont.Charset = DEFAULT_CHARSET
    HeadingFont.Color = clWindowText
    HeadingFont.Height = -13
    HeadingFont.Name = 'MS Sans Serif'
    HeadingFont.Style = []
    ParentShowHint = False
    Rows = 1
    ShowHint = True
    StoreData = True
    TabOrder = 1
    Version = '2.01'
    OnButtonClick = tsGridButtonClick
    OnDblClickCell = tsGridDblClickCell
    ColProperties = <
      item
        DataCol = 1
        FieldName = 'Form'
        Col.FieldName = 'Form'
        Col.Width = 144
      end
      item
        DataCol = 2
        FieldName = 'Description'
        Col.FieldName = 'Description'
        Col.Width = 267
      end>
    Data = {0100000002000000010000000001000000000000000000000000}
  end
end
