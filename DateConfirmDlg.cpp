// DateConfirmDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TUI.h"
#include "DateConfirmDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDateConfirmDlg dialog


CDateConfirmDlg::CDateConfirmDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDateConfirmDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDateConfirmDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDateConfirmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDateConfirmDlg)
	DDX_Control(pDX, IDC_DATE_INPUT, m_DateCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDateConfirmDlg, CDialog)
	//{{AFX_MSG_MAP(CDateConfirmDlg)
	ON_BN_CLICKED(IDC_CONFIRM, OnConfirm)
	ON_NOTIFY(MCN_SELCHANGE, IDC_DATE_INPUT, OnSelchangeDateInput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDateConfirmDlg message handlers

void CDateConfirmDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDateConfirmDlg::OnConfirm() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CDateConfirmDlg::OnOK() 
{
	return;
	CDialog::OnOK();
}

BOOL CDateConfirmDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CTime date = CTime::GetCurrentTime();	
	CString msg;
	msg.Format("%d/%02d/%02d", date.GetYear(), date.GetMonth(), date.GetDay());
	GetDlgItem(IDC_CUR_INPUT_DATE)->SetWindowText(msg);	
	m_CurDate = msg;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString CDateConfirmDlg::GetInputDate()
{
	return m_CurDate;
}

void CDateConfirmDlg::OnSelchangeDateInput(NMHDR* pNMHDR, LRESULT* pResult) 
{
	SYSTEMTIME querytime;
    m_DateCtrl.GetCurSel(&querytime);
	querytime.wHour = querytime.wMinute = querytime.wSecond = querytime.wMilliseconds = 0;
    CString date;
    date.Format("%d/%02d/%02d",querytime.wYear,querytime.wMonth,querytime.wDay);
	GetDlgItem(IDC_CUR_INPUT_DATE)->SetWindowText(date);	
	m_CurDate = date;
	*pResult = 0;
}
