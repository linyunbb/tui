#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "Tools.h"

//Variarbles
extern CString g_ItemText;
extern CString g_FormatText;
extern CString g_WndText;
extern CString g_ExeclFile;
extern CTime g_CurTime;
extern CTools g_Tools;
extern CTime g_TempTimeA;
extern CTime g_TempTimeB;
extern CString g_LockReason;
extern int g_Month;
extern BOOL g_bTown91or92;
extern unsigned int g_SWVer; 
extern unsigned int g_DataVer;


/* Macros */
#define WM_QUIZ_END					WM_USER+1
#define WM_NEXT_QUESTION			WM_USER+2
#define WM_SET_FOCUS				WM_USER+3
#define WM_USER_IMPORT_ITEM_CHANGE	WM_USER+4
#define MAX_FILL_NUM  6
#define THRAD_EXIT_BY_USER_BREAK 100

#define WriteLog(sMsg) \
	g_fileLog.Write(sMsg,sMsg.GetLength());\
	g_fileLog.Write("\r\n",2);



/* ---------------------------- Init TABLE Dialog ---------------------------------- */
#define TABLE_DLG_INIT() \
	pInd = (CIndividual*)CData::GetData(g_CurIId);\
	ASSERT(pInd);\
	GetWindowText(g_WndText);\
	SetWindowText(pInd->GetWndText()+g_WndText);


/* ---------------------------- LOAD DATA from pInd ---------------------------------- */
#define LOAD_DATA(item, id) \
	SetDlgItemText(id, pInd->LoadData(item));

#define LOAD_DATA_COMBO(item, id) \
	((CComboBox*)GetDlgItem(id))->SetCurSel(pInd->LoadDataInt(item));

#define LOAD_DATA_DATE(item, id)\
	((CDateTimeCtrl*)GetDlgItem(id))->SetTime(&pInd->LoadDataDate(item));


/* ---------------------------- SAVE DATA to pInd ---------------------------------- */
#define SAVE_DATA(item, id) \
	GetDlgItemText(id, g_ItemText); \
	pInd->SaveData(item, g_ItemText);

#define SAVE_DATA_DATE(item, id)\
	if (((CDateTimeCtrl*)GetDlgItem(id))->GetTime(g_CurTime) == GDT_VALID )\
	{\
		pInd->SaveData(item, g_CurTime.Format("%Y/%m/%d"));\
	}\
	else\
	{\
		pInd->SaveData(item, "");\
	}\

#define SAVE_DATA_COMBO(item, id) \
	if(((CComboBox*)GetDlgItem(id))->GetCurSel() > 0)\
	{\
	g_FormatText.Format("%d:", ((CComboBox*)GetDlgItem(id))->GetCurSel());\
	GetDlgItemText(id, g_ItemText);\
	pInd->SaveData(item, g_FormatText+g_ItemText);\
	}\
	else\
	{\
		pInd->SaveData(item, "");\
	}

#define CHECK_REPORT_DATE(SID, DID, Msg) \
	if( (((CDateTimeCtrl*)GetDlgItem(SID))->GetTime(g_TempTimeA) != GDT_NONE)\
   && 	(((CDateTimeCtrl*)GetDlgItem(DID))->GetTime(g_TempTimeB) != GDT_NONE))\
	{\
	if (atoi(g_TempTimeB.Format("%Y%m%d"))<atoi(g_TempTimeA.Format("%Y%m%d")))\
	{\
		AfxMessageBox(Msg);\
		return;\
	}\
	}

#define GET_CUR_IND() \
	ASSERT(g_CurIId);\
	CIndividual* pInd = (CIndividual*)(CData::GetData(g_CurIId));\
	ASSERT(pInd);
#endif