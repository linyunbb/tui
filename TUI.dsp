# Microsoft Developer Studio Project File - Name="TUI" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=TUI - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TUI.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TUI.mak" CFG="TUI - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TUI - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TUI - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TUI - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"Release/结核病发病模式研究数据录入软件.exe"

!ELSEIF  "$(CFG)" == "TUI - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "TUI - Win32 Release"
# Name "TUI - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CSpreadSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\Data.cpp
# End Source File
# Begin Source File

SOURCE=.\DateConfirmDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\global.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportDataDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MyComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\MyEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\MyTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\PatientInputDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ResearchInputDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ResearchTableDlg1.cpp
# End Source File
# Begin Source File

SOURCE=.\ResearchTableDlg2.cpp
# End Source File
# Begin Source File

SOURCE=.\ResearchTableDlg3.cpp
# End Source File
# Begin Source File

SOURCE=.\SaveLoadDataDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StatsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Table.cpp
# End Source File
# Begin Source File

SOURCE=.\TableDlg1101.cpp
# End Source File
# Begin Source File

SOURCE=.\TableDlg1102.cpp
# End Source File
# Begin Source File

SOURCE=.\TableDlg1201.cpp
# End Source File
# Begin Source File

SOURCE=.\TableDlg1202.cpp
# End Source File
# Begin Source File

SOURCE=.\TableDlg1203.cpp
# End Source File
# Begin Source File

SOURCE=.\TableDlg1204.cpp
# End Source File
# Begin Source File

SOURCE=.\TableDlg1205.cpp
# End Source File
# Begin Source File

SOURCE=.\TableDlg1206.cpp
# End Source File
# Begin Source File

SOURCE=.\TableDlg1301.cpp
# End Source File
# Begin Source File

SOURCE=.\TableDlg1302.cpp
# End Source File
# Begin Source File

SOURCE=.\TableDlg1303.cpp
# End Source File
# Begin Source File

SOURCE=.\TableDlg1401.cpp
# End Source File
# Begin Source File

SOURCE=.\TableDlg1402TO1425.cpp
# End Source File
# Begin Source File

SOURCE=.\TableDlg1426.cpp
# End Source File
# Begin Source File

SOURCE=.\TableDlg2001.cpp
# End Source File
# Begin Source File

SOURCE=.\TableDlg2200.cpp
# End Source File
# Begin Source File

SOURCE=.\TableDlg2300.cpp
# End Source File
# Begin Source File

SOURCE=.\Tools.cpp
# End Source File
# Begin Source File

SOURCE=.\TUI.cpp
# End Source File
# Begin Source File

SOURCE=.\TUI.rc
# End Source File
# Begin Source File

SOURCE=.\TUIDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CSpreadSheet.h
# End Source File
# Begin Source File

SOURCE=.\Data.h
# End Source File
# Begin Source File

SOURCE=.\DateConfirmDlg.h
# End Source File
# Begin Source File

SOURCE=.\global.h
# End Source File
# Begin Source File

SOURCE=.\ImportDataDlg.h
# End Source File
# Begin Source File

SOURCE=.\MyComboBox.h
# End Source File
# Begin Source File

SOURCE=.\MyEdit.h
# End Source File
# Begin Source File

SOURCE=.\MyTabCtrl.h
# End Source File
# Begin Source File

SOURCE=.\PatientInputDlg.h
# End Source File
# Begin Source File

SOURCE=.\ResearchInputDialog.h
# End Source File
# Begin Source File

SOURCE=.\ResearchTableDlg1.h
# End Source File
# Begin Source File

SOURCE=.\ResearchTableDlg2.h
# End Source File
# Begin Source File

SOURCE=.\ResearchTableDlg3.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SaveLoadDataDlg.h
# End Source File
# Begin Source File

SOURCE=.\StatsDialog.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TableDlg1101.h
# End Source File
# Begin Source File

SOURCE=.\TableDlg1102.h
# End Source File
# Begin Source File

SOURCE=.\TableDlg1201.h
# End Source File
# Begin Source File

SOURCE=.\TableDlg1202.h
# End Source File
# Begin Source File

SOURCE=.\TableDlg1203.h
# End Source File
# Begin Source File

SOURCE=.\TableDlg1204.h
# End Source File
# Begin Source File

SOURCE=.\TableDlg1205.h
# End Source File
# Begin Source File

SOURCE=.\TableDlg1206.h
# End Source File
# Begin Source File

SOURCE=.\TableDlg1301.h
# End Source File
# Begin Source File

SOURCE=.\TableDlg1302.h
# End Source File
# Begin Source File

SOURCE=.\TableDlg1303.h
# End Source File
# Begin Source File

SOURCE=.\TableDlg1401.h
# End Source File
# Begin Source File

SOURCE=.\TableDlg1402TO1425.h
# End Source File
# Begin Source File

SOURCE=.\TableDlg1426.h
# End Source File
# Begin Source File

SOURCE=.\TableDlg2001.h
# End Source File
# Begin Source File

SOURCE=.\TableDlg2200.h
# End Source File
# Begin Source File

SOURCE=.\TableDlg2300.h
# End Source File
# Begin Source File

SOURCE=.\Tools.h
# End Source File
# Begin Source File

SOURCE=.\TUI.h
# End Source File
# Begin Source File

SOURCE=.\TUIDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bk.bmp
# End Source File
# Begin Source File

SOURCE=".\res\button green alt.ico"
# End Source File
# Begin Source File

SOURCE=".\res\emoticon-7.ico"
# End Source File
# Begin Source File

SOURCE=".\res\favorites-add.ico"
# End Source File
# Begin Source File

SOURCE=.\res\favorites.ico
# End Source File
# Begin Source File

SOURCE=".\res\file-doc-finished.ico"
# End Source File
# Begin Source File

SOURCE=".\res\file-doc.ico"
# End Source File
# Begin Source File

SOURCE=.\res\finished.ico
# End Source File
# Begin Source File

SOURCE=.\res\finished_sel.ico
# End Source File
# Begin Source File

SOURCE=".\res\folder-blue.ico"
# End Source File
# Begin Source File

SOURCE=.\res\ldy_patient.ico
# End Source File
# Begin Source File

SOURCE=.\res\ldy_patient_finished.ico
# End Source File
# Begin Source File

SOURCE=.\res\ldy_patient_finished_sel.ico
# End Source File
# Begin Source File

SOURCE=.\res\ldy_patient_sel.ico
# End Source File
# Begin Source File

SOURCE=.\res\lock.ico
# End Source File
# Begin Source File

SOURCE=.\res\Nst.ico
# End Source File
# Begin Source File

SOURCE=.\res\ok.ico
# End Source File
# Begin Source File

SOURCE=.\res\ok_sel.ico
# End Source File
# Begin Source File

SOURCE=.\res\patient.ico
# End Source File
# Begin Source File

SOURCE=.\res\patient_sel.ico
# End Source File
# Begin Source File

SOURCE=.\res\performance.ico
# End Source File
# Begin Source File

SOURCE=.\res\TUI.ico
# End Source File
# Begin Source File

SOURCE=.\res\TUI.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
