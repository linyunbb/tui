// TableDlg1205.cpp : implementation file
//

#include "stdafx.h"
#include "TUI.h"
#include "TableDlg1205.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1205 dialog


CTableDlg1205::CTableDlg1205(CWnd* pParent /*=NULL*/)
	: CDialog(CTableDlg1205::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTableDlg1205)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTableDlg1205::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTableDlg1205)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTableDlg1205, CDialog)
	//{{AFX_MSG_MAP(CTableDlg1205)
	ON_BN_CLICKED(IDC_CONFIRM, OnConfirm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1205 message handlers

void CTableDlg1205::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CTableDlg1205::OnOK() 
{
	// TODO: Add extra validation here
	return;
}

BOOL CTableDlg1205::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	TABLE_DLG_INIT();
	
	LOAD_DATA_DATE("B20", IDC_START_DATE);
	LOAD_DATA_DATE("B21", IDC_REPORT_DATE);
	LOAD_DATA_COMBO("B22", IDC_YYJ_RESULT);
	LOAD_DATA_COMBO("B23", IDC_LFP_RESULT);
	LOAD_DATA_COMBO("B24", IDC_YADC_RESULT);
	LOAD_DATA_COMBO("B25", IDC_LMS_RESULT);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTableDlg1205::OnConfirm() 
{
	CHECK_REPORT_DATE(IDC_START_DATE,IDC_REPORT_DATE, "“结果报告日期”应该晚于“开始日期”");
	SAVE_DATA_DATE("B20", IDC_START_DATE);
	SAVE_DATA_DATE("B21", IDC_REPORT_DATE);
	SAVE_DATA_COMBO("B22", IDC_YYJ_RESULT);
	SAVE_DATA_COMBO("B23", IDC_LFP_RESULT);
	SAVE_DATA_COMBO("B24", IDC_YADC_RESULT);
	SAVE_DATA_COMBO("B25", IDC_LMS_RESULT);
	
	CDialog::OnOK();
}
