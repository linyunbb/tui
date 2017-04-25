// TableDlg1201.cpp : implementation file
//

#include "stdafx.h"
#include "TUI.h"
#include "TableDlg1201.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1201 dialog


CTableDlg1201::CTableDlg1201(CWnd* pParent /*=NULL*/)
	: CDialog(CTableDlg1201::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTableDlg1201)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTableDlg1201::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTableDlg1201)
	DDX_Control(pDX, IDC_EXAMINE_RESULT, m_ExamineResultCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTableDlg1201, CDialog)
	//{{AFX_MSG_MAP(CTableDlg1201)
	ON_BN_CLICKED(IDC_CONFIRM, OnConfirm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1201 message handlers

void CTableDlg1201::OnOK() 
{
	// TODO: Add extra validation here
	return;
}

void CTableDlg1201::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CTableDlg1201::OnInitDialog() 
{
	CDialog::OnInitDialog();

	TABLE_DLG_INIT();

	LOAD_DATA_DATE("B1", IDC_EXAMINE_START_DATE);
	LOAD_DATA_DATE("B2", IDC_REPORT_DATE);
	LOAD_DATA_COMBO("B3", IDC_EXAMINE_RESULT);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTableDlg1201::OnConfirm() 
{
	//Check B2: 报告日期不应早于涂片日期
	CHECK_REPORT_DATE(IDC_EXAMINE_START_DATE, IDC_REPORT_DATE, "“结果报告日期”不应早于“菌型鉴定开始日期”");

	SAVE_DATA_DATE("B1", IDC_EXAMINE_START_DATE);
	SAVE_DATA_DATE("B2", IDC_REPORT_DATE);
	SAVE_DATA_COMBO("B3", IDC_EXAMINE_RESULT);
	pInd->CheckAllTableItems();
	CDialog::OnOK();
}