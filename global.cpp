#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "stdafx.h"

CString g_ExeclFile;
CTools g_Tools;
CString g_ItemText;
CString g_FormatText;
CString g_WndText;
CTime g_CurTime;
CTime g_TempTimeA;
CTime g_TempTimeB;
CString g_LockReason;
int g_Month =0;
BOOL g_bTown91or92 = FALSE;
unsigned int g_SWVer = 1; 
unsigned int g_DataVer = 0;
/*
	Ver = NULL, init version
	Ver = 1,  Change IID from 3 digital to 4 digital
  */