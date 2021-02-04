object FormEdit: TFormEdit
  Left = 318
  Top = 267
  Width = 449
  Height = 131
  Caption = 'Project definition'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 120
  TextHeight = 16
  object Panel1: TPanel
    Left = 0
    Top = 57
    Width = 441
    Height = 42
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    object Panel2: TPanel
      Left = 166
      Top = 0
      Width = 275
      Height = 42
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
        OnClick = ButtonOKClick
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
      Width = 166
      Height = 42
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 1
    end
  end
  object Panel4: TPanel
    Left = 0
    Top = 0
    Width = 441
    Height = 57
    Align = alClient
    TabOrder = 1
    object Label1: TLabel
      Left = 9
      Top = 25
      Width = 37
      Height = 16
      Caption = 'Name'
    end
    object EditName: TEdit
      Left = 73
      Top = 26
      Width = 336
      Height = 24
      Hint = 'Name of project'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
    end
  end
end
