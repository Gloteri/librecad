;NSIS Modern User Interface
;Basic Example Script

;--------------------------------
;Include Modern UI

  !include "MUI2.nsh"
  !include "WinVer.nsh"

  !define MUI_ICON "..\..\librecad\res\main\librecad.ico"

;--------------------------------
;General

  ;Name and file
  Name "LibreCAD"
  OutFile "LibreCAD-Installer.exe"

  ;Default installation folder
  InstallDir "$PROGRAMFILES\LibreCAD"

  ;Get installation folder from registry if available
  InstallDirRegKey HKCU "Software\LibreCAD" ""

  ;Request application privileges for Windows Vista
  RequestExecutionLevel admin
  ;TargetMinimalOS 5.1

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_LICENSE "../../licenses/gpl-2.0.txt"
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES

  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES

;--------------------------------
;Languages

  !insertmacro MUI_LANGUAGE "English"



Function .onInit

  Push $R0
  Push $R1
  Push $R2

; get account info into $R2
  userInfo::getAccountType
  pop $0
  StrCpy $R2 $0 5

${If} ${IsWin2000}
    strCmp $R2 "Admin" lbl_checkok
    messageBox MB_OK "I am sorry, this installer needs Admin privileges, Please login as an administrator and install the software."
    Quit
${EndIf}

${If} ${IsWinXP}
    strCmp $R2 "Admin" lbl_checkok
    messageBox MB_OK "I am sorry, this installer needs Admin privileges, Please login as an administrator and install the software."
    Quit
${EndIf}

  lbl_checkok:
  Pop $R2
  Pop $R1
  Pop $R0

FunctionEnd

;--------------------------------
;Installer Sections

Section "Install Section" SecInstall

  SetOutPath "$INSTDIR"
  File /r "..\..\windows\*.*"
  File "C:\QtSDK\mingw\bin\libgcc_s_dw2-1.dll"
  File "C:\QtSDK\Desktop\Qt\4.8.0\mingw\bin\mingwm10.dll"
  File "C:\QtSDK\Desktop\Qt\4.8.0\mingw\bin\QtCore4.dll"
  File "C:\QtSDK\Desktop\Qt\4.8.0\mingw\bin\QtGui4.dll"
  File "C:\QtSDK\Desktop\Qt\4.8.0\mingw\bin\QtXml4.dll"
  File "C:\QtSDK\Desktop\Qt\4.8.0\mingw\bin\QtHelp4.dll"
  File "C:\QtSDK\Desktop\Qt\4.8.0\mingw\bin\QtSql4.dll"
  File "C:\QtSDK\Desktop\Qt\4.8.0\mingw\bin\QtClucene4.dll"
  File "C:\QtSDK\Desktop\Qt\4.8.0\mingw\bin\QtNetwork4.dll"
  File "C:\QtSDK\Desktop\Qt\4.8.0\mingw\bin\QtSvg4.dll"
  SetOutPath "$INSTDIR\sqldrivers"
  File "C:\QtSDK\Desktop\Qt\4.8.0\mingw\plugins\sqldrivers\qsqlite4.dll"
  SetOutPath "$INSTDIR\imageformats"
  File "C:\QtSDK\Desktop\Qt\4.8.0\mingw\plugins\imageformats\qgif4.dll"
  File "C:\QtSDK\Desktop\Qt\4.8.0\mingw\plugins\imageformats\qjpeg4.dll"
  File "C:\QtSDK\Desktop\Qt\4.8.0\mingw\plugins\imageformats\qtiff4.dll"
  File "C:\QtSDK\Desktop\Qt\4.8.0\mingw\plugins\imageformats\qmng4.dll"
  File "C:\QtSDK\Desktop\Qt\4.8.0\mingw\plugins\imageformats\qsvg4.dll"
  File "C:\QtSDK\Desktop\Qt\4.8.0\mingw\plugins\imageformats\qtga4.dll"

  ;Store installation folder
  WriteRegStr HKCU "Software\LibreCAD" "" $INSTDIR

  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

  ; create shortcuts
  createShortCut "$DESKTOP\LibreCAD.lnk" "$INSTDIR\LibreCAD.exe"

  ; Startmenu shortcuts
  createDirectory "$SMPROGRAMS\LibreCAD\"
  createShortCut "$SMPROGRAMS\LibreCAD\LibreCAD.lnk" "$INSTDIR\LibreCAD.exe"
  createShortCut "$SMPROGRAMS\LibreCAD\Uninstall.lnk" "$INSTDIR\Uninstall.exe"

  ; Open Donate URL
  IfSilent +2
  Exec "rundll32 url.dll,FileProtocolHandler http://librecad.org/donate.html"

SectionEnd

;--------------------------------
;Descriptions

  ;Language strings
  LangString DESC_SecInstall ${LANG_ENGLISH} "A test section."

;--------------------------------
;Uninstaller Section

Section "Uninstall"

  ;ADD YOUR OWN FILES HERE...

  Delete "$INSTDIR\Uninstall.exe"
  RMDir /r "$SMPROGRAMS\LibreCAD\"
  RMDir /r $INSTDIR

  RMDir "$INSTDIR"

  DeleteRegKey /ifempty HKCU "Software\LibreCAD"

SectionEnd

