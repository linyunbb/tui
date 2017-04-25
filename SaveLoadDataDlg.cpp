// SaveLoadDataDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TUI.h"
#include "SaveLoadDataDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaveLoadDataDlg dialog


CSaveLoadDataDlg::CSaveLoadDataDlg(CData &data, CWnd* pParent /*=NULL*/)
	: CDialog(CSaveLoadDataDlg::IDD, pParent), m_Data(data)
{
	//{{AFX_DATA_INIT(CSaveLoadDataDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSaveLoadDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaveLoadDataDlg)
	DDX_Control(pDX, IDC_LOAD_DATA_PROGRESS, m_SaveLoadDataCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSaveLoadDataDlg, CDialog)
	//{{AFX_MSG_MAP(CSaveLoadDataDlg)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaveLoadDataDlg message handlers

void CSaveLoadDataDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	return;
	CDialog::OnCancel();
}

void CSaveLoadDataDlg::OnOK() 
{
	// TODO: Add extra validation here
	return;
	CDialog::OnOK();
}

BOOL CSaveLoadDataDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_SaveLoadDataCtrl.SetRange(0, m_Data.GetTotalTown());
	m_SaveLoadDataCtrl.SetStep(1);
	m_SaveLoadDataCtrl.SetPos(0);

	if (isSaving)
	{
		SetDlgItemText(IDC_STATIC_TIP, "保存数据中，请等待...");
	}
	else
	{
		SetDlgItemText(IDC_STATIC_TIP, "载入数据中，请等待...");
	}

	SetTimer(1, 100, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSaveLoadDataDlg::OnTimer(UINT nIDEvent) 
{
	if( nIDEvent == 1)
	{
		KillTimer(1);
		m_Data.pProgress = &m_SaveLoadDataCtrl;
		m_Data.Serialize(isSaving);
		SetTimer(2, 100, NULL);
	}
	else if (nIDEvent == 2)
	{
		CDialog::OnTimer(nIDEvent);
		CDialog::OnOK();
	}
	CDialog::OnTimer(nIDEvent);
}
