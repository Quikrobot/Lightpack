; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "Lightpack"
#define MyAppVersion "5.8"
#define MyAppPublisher "Lightpack"
#define MyAppURL "http://code.google.com/p/lightpack/"
#define MyAppExeName "Lightpack.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppID={{3432F228-E502-4398-9FDE-53A317F25FA1}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
AllowNoIcons=true
LicenseFile=gpl-3.0.txt
OutputBaseFilename=setup_lightpack
SetupIconFile=Lightpack.ico
Compression=lzma/Max
SolidCompression=true
AppCopyright=Lightpack
AppVerName=5.8
UninstallDisplayName={cm:UninstallName}
UninstallDisplayIcon={app}\Lightpack.exe
VersionInfoDescription=Lightpack is a monitor light device used for presence effect strengthening. 
AppMutex=LightpackAppMutex
VersionInfoVersion=5.8
VersionInfoProductName=Lightpack
VersionInfoProductVersion=5.8
Uninstallable=IsNormalInstall

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; Check: IsNormalInstall
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1; Check: IsNormalInstall
Name: "startupicon"; Description: "{cm:CreateStartupIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; Check: IsNormalInstall

[Files]
Source: "Lightpack.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "libgcc_s_dw2-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "mingwm10.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "QtCore4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "QtGui4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "QtNetwork4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "LightpackMain.conf"; DestDir: "{app}"; Flags: ignoreversion; Check: IsPortableInstall
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Check: IsNormalInstall
Name: "{group}\{cm:ProgramOnTheWeb,{#MyAppName}}"; Filename: "{#MyAppURL}"; Check: IsNormalInstall
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"; Check: IsNormalInstall
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon; Check: IsNormalInstall
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: quicklaunchicon; Check: IsNormalInstall
Name: "{commonstartup}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: startupicon; Check: IsNormalInstall

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent
Filename: "http://code.google.com/p/lightpack/w/list"; Description: "{cm:OpenWiki}"; Flags: postinstall shellexec skipifsilent runasoriginaluser 

[UninstallDelete]
Name: "{app}\*.*"; Type: filesandordirs
Name: (app); Type: dirifempty

[CustomMessages]
; Startup icon name
russian.CreateStartupIcon=�������� � ������������
english.CreateStartupIcon=Add to startup folder

; Uninstall name
russian.UninstallName =Lightpack (������ ��������)
english.UninstallName =Lightpack (remove only)

; Docs link name
russian.OpenWiki =������� �������� � �������������
english.OpenWiki =Open documentation

; Portable install form name
russian.InstallTypeForm_Caption =��� ���������
english.InstallTypeForm_Caption =Install type

; Protable form description
russian.InstallTypeForm_Description =�������� ����� ���������
english.InstallTypeForm_Description =Please choose install type

; Radiobuttons
russian.NormalInstallRadioButton_Caption =������� ��������� (�������������)
english.NormalInstallRadioButton_Caption =Typical install (recommend)
russian.PortableInstallRadioButton_Caption =����������� ���������
english.PortableInstallRadioButton_Caption =Portable install

; Radiobuttons descriptions
russian.PortableInstallLabel_Caption1 =������ ��� ��������� �� ���������� ��������.
russian.PortableInstallLabel_Caption2 =��� ��������� �������� � ����� � ����������.
english.PortableInstallLabel_Caption1 =Version for install on removable devices. 
english.PortableInstallLabel_Caption2 =All settings are located in the program folder.

[Code]
var
  InstallTypePage: TWizardPage;
    NormalInstallRadio: TRadioButton;
    PortableInstallRadio: TRadioButton;    
    PortableInstallLabel1: TLabel;    
    PortableInstallLabel2: TLabel;  
  
  procedure  PortableRadioOnClick(Sender: TObject);
    begin    
    PortableInstallLabel1.Enabled := True;
    PortableInstallLabel2.Enabled := True;
    end;
  
  procedure  NormalRadioOnClick(Sender: TObject);
    begin    
    PortableInstallLabel1.Enabled := False;
    PortableInstallLabel2.Enabled := False;
    end;
    
    procedure InitializeWizard;    
    begin
      InstallTypePage := CreateCustomPage( wpWelcome, ExpandConstant('{cm:InstallTypeForm_Caption}'), ExpandConstant('{cm:InstallTypeForm_Description}') );
      WizardForm.NextButton.Enabled := True;
      { NormalInstallRadio }
      NormalInstallRadio := TRadioButton.Create(InstallTypePage); 
      with NormalInstallRadio do
      begin
        Parent := InstallTypePage.Surface; 
        Caption := ExpandConstant('{cm:NormalInstallRadioButton_Caption}'); 
        Left := ScaleX(0); 
        Top := ScaleY(40); 
        Width := ScaleX(InstallTypePage.SurfaceWidth); 
        Height := ScaleY(20); 
        Checked := True;
        OnClick := @NormalRadioOnClick;
      end;   
    
      { PortableInstallRadio }
      PortableInstallRadio := TRadioButton.Create(InstallTypePage); 
      with PortableInstallRadio do
      begin
        Parent := InstallTypePage.Surface; 
        Caption := ExpandConstant('{cm:PortableInstallRadioButton_Caption}'); 
        Left := ScaleX(0); 
        Top := ScaleY(70); 
        Width := ScaleX(InstallTypePage.SurfaceWidth); 
        Height := ScaleY(20); 
        OnClick := @PortableRadioOnClick;
      end;     
    
      { PortableInstallLabel1 }
      PortableInstallLabel1 := TLabel.Create(InstallTypePage); 
       with PortableInstallLabel1 do
      begin
        Parent := InstallTypePage.Surface; 
         Caption := ExpandConstant('{cm:PortableInstallLabel_Caption1}'); 
        Left := ScaleX(20); 
        Top := ScaleY(90); 
        Width := ScaleX(InstallTypePage.SurfaceWidth); 
        Height := ScaleY(20); 
        Enabled := False;
      end;   
    
      { PortableInstallLabel2 }
      PortableInstallLabel2 := TLabel.Create(InstallTypePage); 
      with PortableInstallLabel2 do
      begin
        Parent := InstallTypePage.Surface; 
        Caption := ExpandConstant('{cm:PortableInstallLabel_Caption2}'); 
        Left := ScaleX(20); 
        Top := ScaleY(105); 
        Width := ScaleX(InstallTypePage.SurfaceWidth); 
        Height := ScaleY(20); 
        Enabled := False;
      end;      
    end; 
    
    function IsPortableInstall : Boolean;
    begin
      Result := PortableInstallRadio.Checked;
    end;
  
  function IsNormalInstall : Boolean;
    begin
      Result := NormalInstallRadio.Checked;
    end;
     
    
    function ShouldSkipPage(CurPageID: Integer): Boolean;
    var
      ResultCode: Boolean;     
    begin            
      If PortableInstallRadio.Checked then
      begin
        case CurPageID of
          wpSelectTasks:
            ResultCode := True;
          wpSelectProgramGroup:
            ResultCode := True;            
        end;        
      end;
      Result := ResultCode;
    end;      
    
    procedure CurPageChanged(CurPageID: Integer);
    begin
      If PortableInstallRadio.Checked then
      begin
        case CurPageID of
          wpSelectDir:
            WizardForm.DirEdit.Text := 'C:\Lightpack\';            
        end;
      end;
    end;
end.

 