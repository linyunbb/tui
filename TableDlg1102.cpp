// TableDlg1102.cpp : implementation file
//

#include "stdafx.h"
#include "TUI.h"
#include "TableDlg1102.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1102 dialog


CTableDlg1102::CTableDlg1102(CWnd* pParent /*=NULL*/)
	: CDialog(CTableDlg1102::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTableDlg1102)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTableDlg1102::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTableDlg1102)
	DDX_Control(pDX, IDC_CULTIVATE_RESULT, m_CultivateResultCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTableDlg1102, CDialog)
	//{{AFX_MSG_MAP(CTableDlg1102)
	ON_BN_CLICKED(IDC_CONFIRM, OnConfirm)
	ON_CBN_SELCHANGE(IDC_CULTIVATE_RESULT, OnSelchangeCultivateResult)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1102 message handlers

void CTableDlg1102::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CTableDlg1102::OnOK() 
{
	// TODO: Add extra validation here
	return;
	CDialog::OnOK();
}

BOOL CTableDlg1102::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	TABLE_DLG_INIT();
	LOAD_DATA_DATE("A20", IDC_CULTIVATE_DATE);
	LOAD_DATA_DATE("A21", IDC_REPORT_DATE);
	LOAD_DATA_COMBO("A22", IDC_CULTIVATE_RESULT);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTableDlg1102::OnConfirm() 
{
	//Check A21: 报告日期不应早于涂片日期
	CHECK_REPORT_DATE(IDC_CULTIVATE_DATE,IDC_REPORT_DATE,"“结果报告日期”不应早于“开始培养日期”");

	SAVE_DATA_DATE("A20", IDC_CULTIVATE_DATE);
	SAVE_DATA_DATE("A21", IDC_REPORT_DATE);
	SAVE_DATA_COMBO("A22", IDC_CULTIVATE_RESULT);
	pInd->CheckAllTableItems();
	CDialog::OnOK();
}

void CTableDlg1102::OnSelchangeCultivateResult() 
{
	pInd->CheckAllTableItems();	
}
