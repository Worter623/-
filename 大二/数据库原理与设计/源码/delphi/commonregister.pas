unit commonregister;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, DB, ADODB;

type
  Tcommonregisterform = class(TForm)
    Button1: TButton;
    Label2: TLabel;
    Edit1: TEdit;
    Edit2: TEdit;
    Label1: TLabel;
    Label3: TLabel;
    Edit3: TEdit;
    Label4: TLabel;
    Edit4: TEdit;
    MyADOq: TADOQuery;
    DataSource1: TDataSource;
    ADOConnection1: TADOConnection;
    ADOTable1: TADOTable;
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  commonregisterform: Tcommonregisterform;

implementation

{$R *.dfm}

procedure Tcommonregisterform.Button1Click(Sender: TObject);
begin
    MYADOQ.SQL.Clear;//���SQL
    MYADOQ.SQL.Text:='select * from users where id = :admid' ;
    MYADOQ.Parameters.ParamByName('admid').Value:=Edit1.Text;
    MYADOQ.Open;
    if ADOTable1.Locate('id',edit1.Text,[loCaseInsensitive]) then
     Application.MessageBox('���˺��Ѿ����ڣ����������롣','��ʾ',mb_ok)
    else
    begin
      MYADOQ.close;
      MYADOQ.SQL.Clear;
      MYADOQ.SQL.Text:='insert into users values( :e1,2,:e2,:e4,:e3)';
      myadoq.Parameters.ParamByName('e1').Value:=Edit1.Text;
      myadoq.Parameters.ParamByName('e2').Value:=Edit2.Text;
      myadoq.Parameters.ParamByName('e4').Value:=Edit4.Text;
      myadoq.Parameters.ParamByName('e3').Value:=Edit3.Text;
      MYADOQ.ExecSQL;
      if MessageDlg('ע��ɹ�����رմ��ڣ����ص�¼������е�¼',mtConfirmation,[mbYes,mbno],0)=mryes then
      Self.Close;
    end;
  MYADOQ.SQL.Clear;
  self.CloseQUERY;
  edit1.Clear;
  edit2.Clear;
  edit3.Clear;
  edit4.Clear;
end;

end.
