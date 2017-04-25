// TableDlg1202.cpp : implementation file
//

#include "stdafx.h"
#include "TUI.h"
#include "TableDlg1202.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1202 dialog


CTableDlg1202::CTableDlg1202(CWnd* pParent /*=NULL*/)
	: CDialog(CTableDlg1202::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTableDlg1202)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTableDlg1202::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTableDlg1202)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTableDlg1202, CDialog)
	//{{AFX_MSG_MAP(CTableDlg1202)
	ON_BN_CLICKED(IDC_CONFIRM, OnConfirm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1202 message handlers

void CTableDlg1202::OnOK() 
{
	// TODO: Add extra validation here
	return;
}

void CTableDlg1202::OnCancel() 
{
	// TODO: Add extra cleanup here
	CDialog::OnCancel();
}

BOOL CTableDlg1202::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	TABLE_DLG_INIT();
	
	LOAD_DATA_DATE("B4", IDC_START_DATE);
	LOAD_DATA_DATE("B5", IDC_REPORT_DATE);
	LOAD_DATA_COMBO("B6", IDC_YYJ_RESULT);
	LOAD_DATA_COMBO("B7", IDC_LFP_RESULT);
	LOAD_DATA_COMBO("B8", IDC_YADC_RESULT);
	LOAD_DATA_COMBO("B9", IDC_LMS_RESULT);
	LOAD_DATA_COMBO("B10", IDC_YFSX_RESULT);
	LOAD_DATA_COMBO("B11", IDC_KNMS_RESULT);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTableDlg1202::OnConfirm() 
{
	// TODO: Add your control notification handler code here
	CHECK_REPORT_DATE(IDC_START_DATE,IDC_REPORT_DATE, "“结果报告日期”应该晚于“开始药敏日期”");
	SAVE_DATA_DATE("B4", IDC_START_DATE);
	SAVE_DATA_DATE("B5", IDC_REPORT_DATE);
	SAVE_DATA_COMBO("B6", IDC_YYJ_RESULT);
	SAVE_DATA_COMBO("B7", IDC_LFP_RESULT);
	SAVE_DATA_COMBO("B8", IDC_YADC_RESULT);
	SAVE_DATA_COMBO("B9", IDC_LMS_RESULT);
	SAVE_DATA_COMBO("B10", IDC_YFSX_RESULT);
	SAVE_DATA_COMBO("B11", IDC_KNMS_RESULT);	
	CDialog::OnOK();
}
