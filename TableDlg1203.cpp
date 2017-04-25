// TableDlg1203.cpp : implementation file
//

#include "stdafx.h"
#include "TUI.h"
#include "TableDlg1203.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1203 dialog


CTableDlg1203::CTableDlg1203(CWnd* pParent /*=NULL*/)
	: CDialog(CTableDlg1203::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTableDlg1203)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTableDlg1203::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTableDlg1203)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTableDlg1203, CDialog)
	//{{AFX_MSG_MAP(CTableDlg1203)
	ON_BN_CLICKED(IDC_CONFIRM, OnConfirm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1203 message handlers

void CTableDlg1203::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CTableDlg1203::OnOK() 
{
	return;
}

BOOL CTableDlg1203::OnInitDialog() 
{
	CDialog::OnInitDialog();
		
	TABLE_DLG_INIT();

	LOAD_DATA_DATE("B12", IDC_START_DATE);
	LOAD_DATA_DATE("B13", IDC_REPORT_DATE);
	LOAD_DATA_COMBO("B14", IDC_YYJ_RESULT);
	LOAD_DATA_COMBO("B15", IDC_LFP_RESULT);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTableDlg1203::OnConfirm() 
{
	CHECK_REPORT_DATE(IDC_START_DATE,IDC_REPORT_DATE, "“结果报告日期”应该晚于“开始日期”");
	// TODO: Add extra validation here
	SAVE_DATA_DATE("B12", IDC_START_DATE);
	SAVE_DATA_DATE("B13", IDC_REPORT_DATE);
	SAVE_DATA_COMBO("B14", IDC_YYJ_RESULT);
	SAVE_DATA_COMBO("B15", IDC_LFP_RESULT);
	
	CDialog::OnOK();
}
