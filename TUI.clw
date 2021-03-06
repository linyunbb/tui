; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CStatsDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TUI.h"

ClassCount=33
Class1=CTUIApp
Class2=CTUIDlg
Class3=CAboutDlg

ResourceCount=30
Resource1=IDD_TABLE_1101
Resource2=IDR_MAINFRAME
Resource3=2797
Class4=CPatientInputDlg
Resource4=IDD_TABLE_1205
Class5=CTableDlg1101
Resource5=IDD_RESEARCH_TABLE_2
Resource6=IDD_TABLE_1203
Class6=CMyTabCtrl
Class7=CMyCombo
Class8=CMyComboBox
Class9=CMyDateTimeCtrl
Class10=CTableDlg1102
Resource7=IDD_STATS_DIALOG
Class11=CTableDlg1201
Resource8=IDD_TABLE_1402_1425
Resource9=IDD_TABLE_1206
Resource10=IDD_RESEARCH_INPUT_DIAGLOG
Resource11=IDD_ABOUTBOX
Resource12=IDD_RESEARCH_TABLE_3
Class12=CTableDlg1202
Class13=CTableDlg1203
Class14=CTableDlg1204
Class15=CTableDlg1205
Class16=CTableDlg1206
Resource13=IDD_TABLE_1401
Class17=CTableDlg1301
Resource14=IDD_TABLE_1204
Class18=CTableDlg1302
Resource15=IDD_IMPORT_DATA
Class19=CTableDlg1303
Resource16=IDD_RESEARCH_TABLE_1
Class20=CTableDlg1401
Resource17=IDD_DATE_CONFIRM_DIALOG
Class21=CTableDlg1402TO1425
Resource18=IDD_TABLE_1102
Class22=CTableDlg1426
Resource19=IDD_TABLE_1202
Class23=CTableDlg2001
Resource20=IDD_TABLE_2200
Class24=CTableDlg2200
Resource21=IDD_TABLE_1426
Class25=CTableDlg2300
Resource22=IDD_TABLE_1201
Class26=CResearchInputDialog
Resource23=IDD_PATIENT_INPUT_DIALOG
Class27=CResearchTableDlg3
Resource24=IDD_TABLE_2001
Class28=CResearchTableDlg1
Resource25=IDD_TUI_DIALOG
Class29=CResearchTableDlg2
Resource26=IDD_TABLE_1302
Class30=CDateConfirmDlg
Resource27=IDD_TABLE_1303
Class31=CStatsDialog
Resource28=IDD_TABLE_2300
Class32=CImportDataDlg
Resource29=IDD_TABLE_1301
Class33=CSaveLoadDataDlg
Resource30=IDD_SAVE_LOAD_DATA_DLG

[CLS:CTUIApp]
Type=0
HeaderFile=TUI.h
ImplementationFile=TUI.cpp
Filter=N

[CLS:CTUIDlg]
Type=0
HeaderFile=TUIDlg.h
ImplementationFile=TUIDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CTUIDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=TUIDlg.h
ImplementationFile=TUIDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TUI_DIALOG]
Type=1
Class=CTUIDlg
ControlCount=4
Control1=IDC_STATIC_BK,static,1342243342
Control2=IDCANCEL,button,1342242816
Control3=IDC_HEALTH_INFO_BUTTON,button,1342242816
Control4=IDC_PATIENT_INPUT,button,1342242816

[DLG:IDD_PATIENT_INPUT_DIALOG]
Type=1
Class=CPatientInputDlg
ControlCount=20
Control1=IDC_CITY_SEL_COMBO,combobox,1344339971
Control2=IDC_TOWN_SEL_COMBO,combobox,1344339971
Control3=IDC_FILTER,edit,1350631556
Control4=IDC_PATIENT_LIST,SysListView32,1350631688
Control5=IDC_TABLE_LIST,SysListView32,1350631432
Control6=IDCANCEL,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC_CT,button,1342177287
Control10=IDC_NEW_PATIENT,button,1342242816
Control11=IDC_STATIC_PATIENT_LIST,button,1342177287
Control12=IDC_DELETE_PATIENT,button,1342242816
Control13=IDC_SUB_SECTION_TAB,SysTabControl32,1342177280
Control14=IDC_SECTION_TAB,SysTabControl32,1342177280
Control15=IDC_EXPORT_DATA,button,1342242816
Control16=IDC_STATIC_FILTER,static,1342308352
Control17=IDC_EXPORT_PROGRESS,msctls_progress32,1082130432
Control18=IDC_STATIC_EXPORT,static,1342308352
Control19=IDC_CHECK_STAT,button,1342242816
Control20=IDC_IMPORT_DATA,button,1342242816

[CLS:CPatientInputDlg]
Type=0
HeaderFile=PatientInputDlg.h
ImplementationFile=PatientInputDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_CITY_SEL_COMBO
VirtualFilter=dWC

[DLG:2797]
Type=1
Class=?
ControlCount=33
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC,static,1342308352
Control3=IDC_ID,edit,1484849280
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT2,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT3,edit,1350631552
Control11=IDC_EDIT4,edit,1350631552
Control12=IDC_COMBO1,combobox,1344339970
Control13=IDC_DATETIMEPICKER1,SysDateTimePick32,1342242848
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_EDIT5,edit,1350631552
Control24=IDC_EDIT6,edit,1350631552
Control25=IDC_DATETIMEPICKER2,SysDateTimePick32,1342242848
Control26=IDC_DATETIMEPICKER3,SysDateTimePick32,1342242848
Control27=IDC_DATETIMEPICKER4,SysDateTimePick32,1342242848
Control28=IDC_COMBO2,combobox,1344339970
Control29=IDC_COMBO3,combobox,1344339970
Control30=IDC_COMBO4,combobox,1344339970
Control31=IDC_COMBO5,combobox,1344339970
Control32=IDC_STATIC,static,1342308352
Control33=IDC_DATETIMEPICKER5,SysDateTimePick32,1342242848

[CLS:CTableDlg1101]
Type=0
HeaderFile=tabledlg1101.h
ImplementationFile=tabledlg1101.cpp
BaseClass=CDialog
LastObject=IDC_AGE
Filter=D
VirtualFilter=dWC

[DLG:IDD_TABLE_1101]
Type=1
Class=CTableDlg1101
ControlCount=40
Control1=IDC_REGISTER_ID,edit,1350631556
Control2=IDC_NAME,edit,1350631556
Control3=IDC_SEX_COMBO,combobox,1344339971
Control4=IDC_AGE,edit,1350631556
Control5=IDC_CONTACT_INFO,edit,1350631556
Control6=IDC_ADDRESS,edit,1350631556
Control7=IDC_BORN_ADDRESS,edit,1350631556
Control8=IDC_DIANOSTIC_DATE,SysDateTimePick32,1342242850
Control9=IDC_REGISTER_DATE,SysDateTimePick32,1342242850
Control10=IDC_PHLEGM_DATE,SysDateTimePick32,1342242850
Control11=IDC_CURL_START_DATE,SysDateTimePick32,1342242850
Control12=IDC_SCREEN_OBJECT,combobox,1344339971
Control13=IDC_CURE_CATEGORY,combobox,1344339971
Control14=IDC_REGISTER_CATEGORY,combobox,1344339971
Control15=IDC_MEDCINE_HISTORY_CATEGORY,combobox,1344339971
Control16=IDC_SAMPLE_DATE,SysDateTimePick32,1342242850
Control17=IDC_SAMPLE_REPORT_DATE,SysDateTimePick32,1342242850
Control18=IDC_SAMPLE_RESULT,combobox,1344339971
Control19=IDC_CONFIRM,button,1342242816
Control20=IDCANCEL,button,1342242816
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342308352
Control32=IDC_STATIC,static,1342308352
Control33=IDC_STATIC,static,1342308352
Control34=IDC_STATIC,static,1342308352
Control35=IDC_STATIC,static,1342308352
Control36=IDC_STATIC,static,1342308352
Control37=IDC_ID,static,1342308352
Control38=IDC_STATIC,static,1342308352
Control39=IDC_STATIC,static,1342308352
Control40=IDC_STATIC,static,1342308352

[CLS:CMyTabCtrl]
Type=0
HeaderFile=MyTabCtrl.h
ImplementationFile=MyTabCtrl.cpp
BaseClass=CTabCtrl
Filter=W
VirtualFilter=UWC
LastObject=CMyTabCtrl

[CLS:CMyCombo]
Type=0
HeaderFile=MyCombo.h
ImplementationFile=MyCombo.cpp
BaseClass=CComboBox
Filter=W
VirtualFilter=cWC

[CLS:CMyComboBox]
Type=0
HeaderFile=MyComboBox.h
ImplementationFile=MyComboBox.cpp
BaseClass=CComboBox
Filter=W
VirtualFilter=cWC

[CLS:CMyDateTimeCtrl]
Type=0
HeaderFile=MyDateTimeCtrl.h
ImplementationFile=MyDateTimeCtrl.cpp
BaseClass=CDateTimeCtrl
Filter=W
VirtualFilter=4WC

[DLG:IDD_TABLE_1102]
Type=1
Class=CTableDlg1102
ControlCount=8
Control1=IDC_CULTIVATE_DATE,SysDateTimePick32,1342242850
Control2=IDC_REPORT_DATE,SysDateTimePick32,1342242850
Control3=IDC_CULTIVATE_RESULT,combobox,1344339971
Control4=IDC_CONFIRM,button,1342242816
Control5=IDCANCEL,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

[CLS:CTableDlg1102]
Type=0
HeaderFile=TableDlg1102.h
ImplementationFile=TableDlg1102.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CTableDlg1102

[DLG:IDD_TABLE_1201]
Type=1
Class=CTableDlg1201
ControlCount=8
Control1=IDC_EXAMINE_START_DATE,SysDateTimePick32,1342242850
Control2=IDC_REPORT_DATE,SysDateTimePick32,1342242850
Control3=IDC_EXAMINE_RESULT,combobox,1344339971
Control4=IDC_CONFIRM,button,1342242816
Control5=IDCANCEL,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

[CLS:CTableDlg1201]
Type=0
HeaderFile=TableDlg1201.h
ImplementationFile=TableDlg1201.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CTableDlg1201

[DLG:IDD_TABLE_1202]
Type=1
Class=CTableDlg1202
ControlCount=18
Control1=IDC_START_DATE,SysDateTimePick32,1342242850
Control2=IDC_REPORT_DATE,SysDateTimePick32,1342242850
Control3=IDC_YYJ_RESULT,combobox,1344339971
Control4=IDC_LFP_RESULT,combobox,1344339971
Control5=IDC_YADC_RESULT,combobox,1344339971
Control6=IDC_LMS_RESULT,combobox,1344339971
Control7=IDC_YFSX_RESULT,combobox,1344339971
Control8=IDC_KNMS_RESULT,combobox,1344339971
Control9=IDC_CONFIRM,button,1342242816
Control10=IDCANCEL,button,1342242816
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352

[DLG:IDD_TABLE_1203]
Type=1
Class=CTableDlg1203
ControlCount=10
Control1=IDC_START_DATE,SysDateTimePick32,1342242850
Control2=IDC_REPORT_DATE,SysDateTimePick32,1342242850
Control3=IDC_YYJ_RESULT,combobox,1344339971
Control4=IDC_LFP_RESULT,combobox,1344339971
Control5=IDC_CONFIRM,button,1342242816
Control6=IDCANCEL,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352

[DLG:IDD_TABLE_1204]
Type=1
Class=CTableDlg1204
ControlCount=10
Control1=IDC_START_DATE,SysDateTimePick32,1342242850
Control2=IDC_REPORT_DATE,SysDateTimePick32,1342242850
Control3=IDC_YYJ_RESULT,combobox,1344339971
Control4=IDC_LFP_RESULT,combobox,1344339971
Control5=IDC_CONFIRM,button,1342242816
Control6=IDCANCEL,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352

[DLG:IDD_TABLE_1205]
Type=1
Class=CTableDlg1205
ControlCount=14
Control1=IDC_START_DATE,SysDateTimePick32,1342242850
Control2=IDC_REPORT_DATE,SysDateTimePick32,1342242850
Control3=IDC_YYJ_RESULT,combobox,1344339971
Control4=IDC_LFP_RESULT,combobox,1344339971
Control5=IDC_YADC_RESULT,combobox,1344339971
Control6=IDC_LMS_RESULT,combobox,1344339971
Control7=IDC_CONFIRM,button,1342242816
Control8=IDCANCEL,button,1342242816
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352

[DLG:IDD_TABLE_1206]
Type=1
Class=CTableDlg1206
ControlCount=16
Control1=IDC_DIAGNOSTIC_RESULT,combobox,1344339971
Control2=IDC_REPORT_DATE,SysDateTimePick32,1342242850
Control3=IDC_NDY_REGISTER_NO,edit,1350631556
Control4=IDC_IS_SUITABLE,combobox,1344339971
Control5=IDC_WILLING_TO_BE_SEARCHED,combobox,1344339971
Control6=IDC_PATIENT_SEARCH_INFO,combobox,1344339971
Control7=IDC_PATIENT_SEARCH_INFO_DATE,SysDateTimePick32,1342242850
Control8=IDC_CONFIRM,button,1342242816
Control9=IDCANCEL,button,1342242816
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352

[CLS:CTableDlg1202]
Type=0
HeaderFile=TableDlg1202.h
ImplementationFile=TableDlg1202.cpp
BaseClass=CDialog
Filter=D
LastObject=CTableDlg1202
VirtualFilter=dWC

[CLS:CTableDlg1203]
Type=0
HeaderFile=TableDlg1203.h
ImplementationFile=TableDlg1203.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CTableDlg1203

[CLS:CTableDlg1204]
Type=0
HeaderFile=TableDlg1204.h
ImplementationFile=TableDlg1204.cpp
BaseClass=CDialog
Filter=D
LastObject=CTableDlg1204
VirtualFilter=dWC

[CLS:CTableDlg1205]
Type=0
HeaderFile=TableDlg1205.h
ImplementationFile=TableDlg1205.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CTableDlg1205

[CLS:CTableDlg1206]
Type=0
HeaderFile=TableDlg1206.h
ImplementationFile=TableDlg1206.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_DIAGNOSTIC_RESULT

[DLG:IDD_TABLE_1301]
Type=1
Class=CTableDlg1301
ControlCount=24
Control1=IDC_IS_ACKED,combobox,1344339971
Control2=IDC_IS_QUESTIONAIR_FINISHED,combobox,1344339971
Control3=IDC_FINISHED_DATE,SysDateTimePick32,1342242850
Control4=IDC_IS_QUESTIONAIR_COMPLETE,combobox,1344339971
Control5=IDC_IS_BLOOD_TAKEN,combobox,1344339971
Control6=IDC_BLOOD_TAKEN_DATE,SysDateTimePick32,1342242850
Control7=IDC_BLOOD_TAKEN_NO,combobox,1344339971
Control8=IDC_BLOOD_ML,edit,1350631556
Control9=IDC_IS_RESERVED_20,combobox,1344339971
Control10=IDC_INSTITUTION_LEVEL,combobox,1344339971
Control11=IDC_IS_RESERVED_4,combobox,1344339971
Control12=IDCANCEL,button,1342242816
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_CONFIRM,button,1342242816

[CLS:CTableDlg1301]
Type=0
HeaderFile=TableDlg1301.h
ImplementationFile=TableDlg1301.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_INSTITUTION_LEVEL

[DLG:IDD_TABLE_1302]
Type=1
Class=CTableDlg1302
ControlCount=10
Control1=IDC_IS_TO_PROVINCE,combobox,1344339971
Control2=IDC_TO_PROVINCE_DATE,SysDateTimePick32,1342242850
Control3=IDC_IS_TO_NATIONAL,combobox,1344339971
Control4=IDC_TO_NATIONAL_DATE,SysDateTimePick32,1342242850
Control5=IDCANCEL,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_CONFIRM,button,1342242816

[CLS:CTableDlg1302]
Type=0
HeaderFile=TableDlg1302.h
ImplementationFile=TableDlg1302.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CTableDlg1302

[DLG:IDD_TABLE_1303]
Type=1
Class=CTableDlg1303
ControlCount=10
Control1=IDC_IS_TO_PROVINCE,combobox,1344339971
Control2=IDC_TO_PROVINCE_DATE,SysDateTimePick32,1342242850
Control3=IDC_IS_TO_NATIONAL,combobox,1344339971
Control4=IDC_TO_NATIONAL_DATE,SysDateTimePick32,1342242850
Control5=IDCANCEL,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_CONFIRM,button,1342242816

[CLS:CTableDlg1303]
Type=0
HeaderFile=TableDlg1303.h
ImplementationFile=TableDlg1303.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CTableDlg1303

[DLG:IDD_TABLE_1401]
Type=1
Class=CTableDlg1401
ControlCount=8
Control1=IDC_PROJECT,edit,1353781252
Control2=IDC_FIRST_TREAT_DATE,SysDateTimePick32,1342242850
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_CONFIRM,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_PROJECT_SEL,combobox,1344339971

[CLS:CTableDlg1401]
Type=0
HeaderFile=TableDlg1401.h
ImplementationFile=TableDlg1401.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_PROJECT

[DLG:IDD_TABLE_1402_1425]
Type=1
Class=CTableDlg1402TO1425
ControlCount=51
Control1=IDC_SAMPLE_RESULT,combobox,1344339971
Control2=IDC_CULTIVATE_RESULT,combobox,1344339971
Control3=IDC_IS_IN_HOSPITAL,combobox,1344339971
Control4=IDC_IN_HOSPITAL_DAY,edit,1350631556
Control5=IDC_WEIGHT,edit,1350631556
Control6=IDC_ABNORMAL_TYPE,combobox,1344339971
Control7=IDC_ABNORMAL_LEVEL,combobox,1344339971
Control8=IDC_ABNORMAL_DATE,SysDateTimePick32,1342242850
Control9=IDC_IMPACT,combobox,1344339971
Control10=IDC_IS_PROJECT_CHANGED,combobox,1344339971
Control11=IDC_PROJECT_CHANGED_DATE,SysDateTimePick32,1342242850
Control12=IDC_CHANGED_PROJECT,edit,1353781252
Control13=IDC_Z_YESNO,combobox,1344339971
Control14=IDC_E_YESNO,combobox,1344339971
Control15=IDC_KM_YESNO,combobox,1344339971
Control16=IDC_AM_YESNO,combobox,1344339971
Control17=IDC_CM_YESNO,combobox,1344339971
Control18=IDC_OFX_YESN,combobox,1344339971
Control19=IDC_LFX_YESNO,combobox,1344339971
Control20=IDC_MFX_YESNO,combobox,1344339971
Control21=IDC_PTO_YESNO,combobox,1344339971
Control22=IDC_CS_YESNO,combobox,1344339971
Control23=IDC_PAS_YESNO,combobox,1344339971
Control24=IDC_OTHER_MEDICINE,edit,1350631556
Control25=IDC_CONFIRM,button,1342242816
Control26=IDCANCEL,button,1342242816
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342308352
Control32=IDC_STATIC,static,1342308352
Control33=IDC_STATIC,static,1342308352
Control34=IDC_STATIC,static,1342308352
Control35=IDC_STATIC,static,1342308352
Control36=IDC_STATIC,static,1342308352
Control37=IDC_STATIC,static,1342308352
Control38=IDC_STATIC,static,1342308352
Control39=IDC_STATIC,static,1342308352
Control40=IDC_STATIC,static,1342308352
Control41=IDC_STATIC,static,1342308352
Control42=IDC_STATIC,static,1342308352
Control43=IDC_STATIC,static,1342308352
Control44=IDC_STATIC,static,1342308352
Control45=IDC_STATIC,static,1342308352
Control46=IDC_STATIC,static,1342308352
Control47=IDC_STATIC,static,1342308352
Control48=IDC_STATIC,static,1342308352
Control49=IDC_STATIC,static,1342308352
Control50=IDC_STATIC,static,1342308352
Control51=IDC_STATIC,button,1342177287

[CLS:CTableDlg1402TO1425]
Type=0
HeaderFile=TableDlg1402TO1425.h
ImplementationFile=TableDlg1402TO1425.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_IS_IN_HOSPITAL

[DLG:IDD_TABLE_1426]
Type=1
Class=CTableDlg1426
ControlCount=6
Control1=IDC_ALTER_TYPE,combobox,1344339971
Control2=IDC_ALTER_DATE,SysDateTimePick32,1342242850
Control3=IDCANCEL,button,1342242816
Control4=65535,static,1342308352
Control5=65535,static,1342308352
Control6=IDC_CONFIRM,button,1342242816

[CLS:CTableDlg1426]
Type=0
HeaderFile=TableDlg1426.h
ImplementationFile=TableDlg1426.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=65535

[DLG:IDD_TABLE_2001]
Type=1
Class=CTableDlg2001
ControlCount=38
Control1=IDC_HOW_FAR,edit,1350631556
Control2=IDC_BY_WHAT_VEHICLE,combobox,1344339971
Control3=IDC_HOW_LONG,combobox,1344339971
Control4=IDC_FEE_FOR_VEHICLE,edit,1350631556
Control5=IDC_IS_STAY_OUTSIDE,combobox,1344339971
Control6=IDC_FEE_FOR_STAY_OUTSIDE,edit,1350631556
Control7=IDC_HOW_MANY_DINNERS,edit,1350631556
Control8=IDC_FEE_FOR_DINNER,edit,1350631556
Control9=IDC_IS_ACCOMPANY,combobox,1344339971
Control10=IDC_HOW_MANY_ACCOMPANY,edit,1350631556
Control11=IDC_FEE_FOR_VEHICLE_ACCOMPANY,edit,1350631556
Control12=IDC_IS_STAY_OUTSIDE_ACCOMPANY,combobox,1344339971
Control13=IDC_FEE_FOR_STAY_OUTSIDE_ACCOMPANY,edit,1350631556
Control14=IDC_HOW_MANY_DINNERS_ACCOMPANY,edit,1350631556
Control15=IDC_FEE_FOR_DINNER_ACCOMPANY,edit,1350631556
Control16=IDC_DOCTOER_NAME,edit,1350631556
Control17=IDC_FILLING_DATE,SysDateTimePick32,1342242850
Control18=IDC_CONFIRM,button,1342242816
Control19=IDCANCEL,button,1342242816
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342308352
Control32=IDC_STATIC,static,1342308352
Control33=IDC_STATIC,static,1342308352
Control34=IDC_STATIC,static,1342308352
Control35=IDC_STATIC,static,1342308352
Control36=IDC_STATIC,static,1342308352
Control37=IDC_STATIC,button,1342177287
Control38=IDC_STATIC,button,1342177287

[CLS:CTableDlg2001]
Type=0
HeaderFile=TableDlg2001.h
ImplementationFile=TableDlg2001.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_HOW_MANY_DINNERS

[DLG:IDD_TABLE_2200]
Type=1
Class=CTableDlg2200
ControlCount=60
Control1=IDC_IN_HOSPITAL_NO,edit,1350631556
Control2=IDC_ACTUAL_TOTAL,edit,1350631556
Control3=IDC_EXPENSE_FOR_BED,edit,1350631556
Control4=IDC_EXPENSE_FOR_NURSING_CARE,edit,1350631556
Control5=IDC_EXPENSE_DIAGNOS,edit,1350631556
Control6=IDC_EXPENSE_OTHER_ASSAY,edit,1350631556
Control7=IDC_ANTI_TUB_MEDICINE,edit,1350631556
Control8=IDC_EXPENSE_FOR_ASSISTANT_MEDICINE,edit,1350631556
Control9=IDC_EXPENSE_SURGERY,edit,1350631556
Control10=IDC_EXPENSE_OTHERS,edit,1350631556
Control11=IDC_EXPENSE_FOR_TRAVAL,edit,1350631556
Control12=IDC_EXPENSE_FOR_ACCOMMODATION,edit,1350631556
Control13=IDC_MEDICAL_CARE_CATEGORY,combobox,1344339971
Control14=IDC_MEDICARE_ACTUAL_REIMBURSEMENT,edit,1350631556
Control15=IDC_GLOBAL_FUND_REIMBURSEMENT,edit,1350631556
Control16=IDC_OTHER_COMMERCIAL_REIMBURSEMENT,edit,1350631556
Control17=IDC_PERSONAL_PAID,edit,1350631556
Control18=IDC_OTHER_SOURCE,edit,1350631556
Control19=IDC_DOCTOER_NAME,edit,1350631556
Control20=IDC_FILLING_DATE,SysDateTimePick32,1342242850
Control21=IDC_CONFIRM,button,1342242816
Control22=IDCANCEL,button,1342242816
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342308352
Control32=IDC_STATIC,static,1342308352
Control33=IDC_STATIC,static,1342308352
Control34=IDC_STATIC,static,1342308352
Control35=IDC_STATIC,static,1342308352
Control36=IDC_STATIC,static,1342308352
Control37=IDC_STATIC,static,1342308352
Control38=IDC_STATIC,static,1342308352
Control39=IDC_STATIC,static,1342308352
Control40=IDC_STATIC,static,1342308352
Control41=IDC_STATIC,static,1342308352
Control42=IDC_STATIC,static,1342308352
Control43=IDC_STATIC,static,1342308352
Control44=IDC_STATIC,static,1342308352
Control45=IDC_STATIC,static,1342308352
Control46=IDC_STATIC,static,1342308352
Control47=IDC_STATIC,static,1342308352
Control48=IDC_STATIC,static,1342308352
Control49=IDC_STATIC,static,1342308352
Control50=IDC_STATIC,static,1342308352
Control51=IDC_STATIC,static,1342308352
Control52=IDC_STATIC,static,1342308352
Control53=IDC_STATIC,static,1342308352
Control54=IDC_STATIC,static,1342308352
Control55=IDC_STATIC,static,1342308352
Control56=IDC_STATIC,static,1342308352
Control57=IDC_STATIC,static,1342308352
Control58=IDC_STATIC,static,1342308352
Control59=IDC_STATIC,button,1342177287
Control60=IDC_STATIC,button,1342177287

[CLS:CTableDlg2200]
Type=0
HeaderFile=TableDlg2200.h
ImplementationFile=TableDlg2200.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CTableDlg2200

[DLG:IDD_TABLE_2300]
Type=1
Class=CTableDlg2300
ControlCount=43
Control1=IDC_EXPENSE_RANDOM_CHECK,edit,1350631556
Control2=IDC_EXPENSE_FOR_INJECTION,edit,1350631556
Control3=IDC_ANTI_TUB_MEDICINE,edit,1350631556
Control4=IDC_EXPENSE_FOR_ASSISTANT_MEDICINE,edit,1350631556
Control5=IDC_EXPENSE_FOR_TRAVAL,edit,1350631556
Control6=IDC_EXPENSE_FOR_ACCOMMODATION,edit,1350631556
Control7=IDC_MEDICAL_CARE_CATEGORY,combobox,1344339971
Control8=IDC_MEDICARE_ACTUAL_REIMBURSEMENT,edit,1350631556
Control9=IDC_GLOBAL_FUND_REIMBURSEMENT,edit,1350631556
Control10=IDC_OTHER_COMMERCIAL_REIMBURSEMENT,edit,1350631556
Control11=IDC_PERSONAL_PAID,edit,1350631556
Control12=IDC_OTHER_SOURCE,edit,1350631556
Control13=IDC_DOCTOER_NAME,edit,1350631556
Control14=IDC_FILLING_DATE,SysDateTimePick32,1342242850
Control15=IDC_CONFIRM,button,1342242816
Control16=IDCANCEL,button,1342242816
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,button,1342177287
Control32=IDC_STATIC,button,1342177287
Control33=IDC_STATIC,static,1342308352
Control34=IDC_STATIC,static,1342308352
Control35=IDC_STATIC,static,1342308352
Control36=IDC_STATIC,static,1342308352
Control37=IDC_STATIC,static,1342308352
Control38=IDC_STATIC,static,1342308352
Control39=IDC_STATIC,static,1342308352
Control40=IDC_STATIC,static,1342308352
Control41=IDC_STATIC,static,1342308352
Control42=IDC_STATIC,static,1342308352
Control43=IDC_STATIC,static,1342308352

[CLS:CTableDlg2300]
Type=0
HeaderFile=TableDlg2300.h
ImplementationFile=TableDlg2300.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EXPENSE_RANDOM_CHECK

[DLG:IDD_RESEARCH_INPUT_DIAGLOG]
Type=1
Class=CResearchInputDialog
ControlCount=16
Control1=IDC_CITY_SEL_COMBO,combobox,1344339971
Control2=IDC_TOWN_SEL_COMBO,combobox,1344339971
Control3=IDC_FILTER,edit,1350631556
Control4=IDC_PATIENT_LIST,SysListView32,1350631708
Control5=IDC_TABLE_LIST,SysListView32,1350631432
Control6=IDCANCEL,button,1342242816
Control7=65535,static,1342308352
Control8=65535,static,1342308352
Control9=IDC_STATIC_CT,button,1342177287
Control10=IDC_NEW_PATIENT,button,1342242816
Control11=IDC_STATIC_LIST,button,1342177287
Control12=IDC_DELETE_PATIENT,button,1342242816
Control13=IDC_EXPORT_DATA,button,1342242816
Control14=IDC_STATIC_FILTER,static,1342308352
Control15=IDC_EXPORT_PROGRESS,msctls_progress32,1082130432
Control16=IDC_STATIC_EXPORT,static,1342308352

[CLS:CResearchInputDialog]
Type=0
HeaderFile=ResearchInputDialog.h
ImplementationFile=ResearchInputDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CResearchInputDialog

[DLG:IDD_RESEARCH_TABLE_3]
Type=1
Class=CResearchTableDlg3
ControlCount=10
Control1=IDC_IS_TO_PROVINCE,combobox,1344339971
Control2=IDC_TO_PROVINCE_DATE,SysDateTimePick32,1342242850
Control3=IDC_IS_TO_NATIONAL,combobox,1344339971
Control4=IDC_TO_NATIONAL_DATE,SysDateTimePick32,1342242850
Control5=IDC_CONFIRM,button,1342242816
Control6=IDCANCEL,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352

[CLS:CResearchTableDlg3]
Type=0
HeaderFile=ResearchTableDlg3.h
ImplementationFile=ResearchTableDlg3.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CResearchTableDlg3

[DLG:IDD_RESEARCH_TABLE_1]
Type=1
Class=CResearchTableDlg1
ControlCount=30
Control1=IDC_NAME,edit,1350631556
Control2=IDC_SEX_COMBO,combobox,1344339971
Control3=IDC_AGE,edit,1350631556
Control4=IDC_CONTACT_INFO,edit,1350631556
Control5=IDC_LOCAL_LIVING_YEAR,edit,1350631556
Control6=IDC_TUB_HISTORY_YESNO,combobox,1344339971
Control7=IDC_IS_EXCLUDED_BY_X,combobox,1344339971
Control8=IDC_CHRONIC_DISEASE_HISTORY,combobox,1344339971
Control9=IDC_RESPIRATORY_SYSTEM_DISEASE_YESNO,combobox,1344339971
Control10=IDC_IS_AGREED,combobox,1344339971
Control11=IDC_IS_OBSORBED,combobox,1344339971
Control12=IDC_DOCTOR_NAME,edit,1350631556
Control13=IDC_FILLING_DATE,SysDateTimePick32,1342242850
Control14=IDC_CONFIRM,button,1342242816
Control15=IDCANCEL,button,1342242816
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_ID,static,1342308352
Control30=IDC_STATIC,static,1342308352

[CLS:CResearchTableDlg1]
Type=0
HeaderFile=ResearchTableDlg1.h
ImplementationFile=ResearchTableDlg1.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_IS_EXCLUDED_BY_X
VirtualFilter=dWC

[DLG:IDD_RESEARCH_TABLE_2]
Type=1
Class=CResearchTableDlg2
ControlCount=20
Control1=IDC_IS_ACKED,combobox,1344339971
Control2=IDC_IS_QUESTIONAIR_FINISHED,combobox,1344339971
Control3=IDC_FINISHED_DATE,SysDateTimePick32,1342242850
Control4=IDC_IS_QUESTIONAIR_COMPLETE,combobox,1344339971
Control5=IDC_IS_BLOOD_TAKEN,combobox,1344339971
Control6=IDC_BLOOD_TAKEN_DATE,SysDateTimePick32,1342242850
Control7=IDC_BLOOD_TAKEN_NO,combobox,1344339971
Control8=IDC_BLOOD_ML,edit,1350631556
Control9=IDC_IS_RESERVED_20,combobox,1344339971
Control10=IDC_CONFIRM,button,1342242816
Control11=IDCANCEL,button,1342242816
Control12=65535,static,1342308352
Control13=65535,static,1342308352
Control14=65535,static,1342308352
Control15=65535,static,1342308352
Control16=65535,static,1342308352
Control17=65535,static,1342308352
Control18=65535,static,1342308352
Control19=65535,static,1342308352
Control20=65535,static,1342308352

[CLS:CResearchTableDlg2]
Type=0
HeaderFile=ResearchTableDlg2.h
ImplementationFile=ResearchTableDlg2.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_IS_ACKED

[DLG:IDD_DATE_CONFIRM_DIALOG]
Type=1
Class=CDateConfirmDlg
ControlCount=6
Control1=IDC_CONFIRM,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_CUR_INPUT_DATE,edit,1350633600
Control5=IDC_STATIC,static,1342308352
Control6=IDC_DATE_INPUT,SysMonthCal32,1342242832

[CLS:CDateConfirmDlg]
Type=0
HeaderFile=DateConfirmDlg.h
ImplementationFile=DateConfirmDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDateConfirmDlg

[DLG:IDD_STATS_DIALOG]
Type=1
Class=CStatsDialog
ControlCount=6
Control1=IDC_STATS_ONE,SysListView32,1350631425
Control2=IDC_STATS_TWO,SysListView32,1350631425
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EXPORT,button,1342242816
Control6=IDC_MONTH_SEL,SysDateTimePick32,1342242848

[CLS:CStatsDialog]
Type=0
HeaderFile=StatsDialog.h
ImplementationFile=StatsDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_MONTH_SEL

[DLG:IDD_IMPORT_DATA]
Type=1
Class=CImportDataDlg
ControlCount=10
Control1=IDCANCEL,button,1342242816
Control2=IDC_IND_LIST,listbox,1352728833
Control3=IDC_CONFLICT_INFO_LIST,listbox,1353777409
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_IMPORT_PROGRESS,msctls_progress32,1350565888
Control7=IDC_STATIC_TIP,static,1342308352
Control8=IDC_CONFIRM,button,1476460544
Control9=IDC_IND_OK_LIST,listbox,1352728833
Control10=IDC_STATIC,static,1342308352

[CLS:CImportDataDlg]
Type=0
HeaderFile=ImportDataDlg.h
ImplementationFile=ImportDataDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CImportDataDlg

[DLG:IDD_SAVE_LOAD_DATA_DLG]
Type=1
Class=CSaveLoadDataDlg
ControlCount=2
Control1=IDC_LOAD_DATA_PROGRESS,msctls_progress32,1350565888
Control2=IDC_STATIC_TIP,static,1342308352

[CLS:CSaveLoadDataDlg]
Type=0
HeaderFile=SaveLoadDataDlg.h
ImplementationFile=SaveLoadDataDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

