// TableDlg1204.cpp : implementation file
//

#include "stdafx.h"
#include "TUI.h"
#include "TableDlg1204.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1204 dialog


CTableDlg1204::CTableDlg1204(CWnd* pParent /*=NULL*/)
	: CDialog(CTableDlg1204::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTableDlg1204)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTableDlg1204::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTableDlg1204)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTableDlg1204, CDialog)
	//{{AFX_MSG_MAP(CTableDlg1204)
	ON_BN_CLICKED(IDC_CONFIRM, OnConfirm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1204 message handlers

void CTableDlg1204::OnOK() 
{
	// TODO: Add extra validation here
	return;
}

void CTableDlg1204::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CTableDlg1204::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	TABLE_DLG_INIT();
	
	LOAD_DATA_DATE("B16", IDC_START_DATE);
	LOAD_DATA_DATE("B17", IDC_REPORT_DATE);
	LOAD_DATA_COMBO("B18", IDC_YYJ_RESULT);
	LOAD_DATA_COMBO("B19", IDC_LFP_RESULT);
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTableDlg1204::OnConfirm() 
{
	CHECK_REPORT_DATE(IDC_START_DATE,IDC_REPORT_DATE, "“结果报告日期”应该晚于“开始日期”");
	SAVE_DATA_DATE("B16", IDC_START_DATE);
	SAVE_DATA_DATE("B17", IDC_REPORT_DATE);
	SAVE_DATA_COMBO("B18", IDC_YYJ_RESULT);
	SAVE_DATA_COMBO("B19", IDC_LFP_RESULT);
	
	CDialog::OnOK();

}
