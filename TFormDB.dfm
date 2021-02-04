object base: Tbase
  Left = 260
  Top = 183
  Width = 414
  Height = 392
  Caption = 'Database options'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 120
  TextHeight = 16
  object Panel1: TPanel
    Left = 0
    Top = 322
    Width = 406
    Height = 43
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    object Panel2: TPanel
      Left = 130
      Top = 0
      Width = 276
      Height = 43
      Align = alRight
      BevelOuter = bvNone
      TabOrder = 0
      object ButtonOK: TButton
        Left = 39
        Top = 10
        Width = 93
        Height = 24
        Caption = 'OK'
        ModalResult = 1
        TabOrder = 0
      end
      object ButtonCancel: TButton
        Left = 167
        Top = 10
        Width = 93
        Height = 24
        Caption = 'Cancel'
        ModalResult = 2
        TabOrder = 1
      end
    end
    object Panel3: TPanel
      Left = 0
      Top = 0
      Width = 130
      Height = 43
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 1
    end
  end
  object Panel4: TPanel
    Left = 0
    Top = 0
    Width = 406
    Height = 322
    Align = alClient
    TabOrder = 1
  end
  object RemoteDB: TADOConnection
    ConnectionString = 'Provider=Microsoft.Jet.OLEDB.4.0;Password=""'
    LoginPrompt = False
    Mode = cmReadWrite
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 336
    Top = 49
  end
  object RemoteQuery: TADOQuery
    Connection = RemoteDB
    Parameters = <>
    Left = 368
    Top = 49
  end
end
