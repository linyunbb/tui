// TableDlg1426.cpp : implementation file
//

#include "stdafx.h"
#include "TUI.h"
#include "TableDlg1426.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1426 dialog


CTableDlg1426::CTableDlg1426(CWnd* pParent /*=NULL*/)
	: CDialog(CTableDlg1426::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTableDlg1426)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTableDlg1426::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTableDlg1426)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTableDlg1426, CDialog)
	//{{AFX_MSG_MAP(CTableDlg1426)
	ON_BN_CLICKED(IDC_CONFIRM, OnConfirm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1426 message handlers

void CTableDlg1426::OnOK() 
{
	// TODO: Add your control notification handler code here
	return;
}
	
void CTableDlg1426::OnConfirm() 
{
	// TODO: Add extra validation here
	SAVE_DATA_COMBO("D579", IDC_ALTER_TYPE);
	SAVE_DATA_DATE("D580", IDC_ALTER_DATE);

	CDialog::OnOK();
}

void CTableDlg1426::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CTableDlg1426::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	TABLE_DLG_INIT();
	LOAD_DATA_COMBO("D579", IDC_ALTER_TYPE);
	LOAD_DATA_DATE("D580", IDC_ALTER_DATE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}