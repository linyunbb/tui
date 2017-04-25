// TableDlg1401.cpp : implementation file
//

#include "stdafx.h"
#include "TUI.h"
#include "TableDlg1401.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1401 dialog


CTableDlg1401::CTableDlg1401(CWnd* pParent /*=NULL*/)
	: CDialog(CTableDlg1401::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTableDlg1401)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTableDlg1401::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTableDlg1401)
	DDX_Control(pDX, IDC_PROJECT_SEL, m_ProjectSelCtrl);
	DDX_Control(pDX, IDC_PROJECT, m_FirstTreatProjectCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTableDlg1401, CDialog)
	//{{AFX_MSG_MAP(CTableDlg1401)
	ON_BN_CLICKED(IDC_CONFIRM, OnConfirm)
	ON_CBN_SELCHANGE(IDC_PROJECT_SEL, OnSelchangeProjectSel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1401 message handlers

void CTableDlg1401::OnOK() 
{
	return;	
}

void CTableDlg1401::OnConfirm() 
{
	int nSel = m_ProjectSelCtrl.GetCurSel();
	if (nSel == 13)//其他
	{
		SAVE_DATA("D1", IDC_PROJECT);
	}
	else if (nSel == 0)
	{
		pInd->SaveData("D1", "");
	}
	else
	{
		SAVE_DATA("D1", IDC_PROJECT_SEL);
	}	
	SAVE_DATA_DATE("D2", IDC_FIRST_TREAT_DATE);
	CDialog::OnOK();
}

void CTableDlg1401::OnCancel() 
{
	CDialog::OnCancel();
}

BOOL CTableDlg1401::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_FirstTreatProjectCtrl.InitEdit(DATA_TYPE_NO_CHINESE, 0, "");

	TABLE_DLG_INIT();
	CString itemText = pInd->GetItem("D1");
	char* sProjectSel[] = {
		"",
		"6 Z Am Lfx PAS Pto/18 Z Lfx PAS Pto",
		"6 Z Am Lfx PAS Pto/18 Z Lfx E Pto",
		"6 Z Am Lfx E Pto/18 Z Lfx PAS Pto",
		"6 Z Am Lfx E Pto/18 Z Lfx E Pto",
		"6 Z Cm Lfx PAS Pto/18 Z Lfx PAS Pto",
		"6 Z Cm Lfx PAS Pto/18 Z Lfx E Pto",
		"6 Z Cm Lfx E Pto/18 Z Lfx PAS Pto",
		"6 Z Cm Lfx E Pto/18 Z Lfx E Pto",
		"6 Z Km Lfx PAS Pto/18 Z Lfx PAS Pto",
		"6 Z Km Lfx PAS Pto/18 Z Lfx E Pto",
		"6 Z Km Lfx E Pto/18 Z Lfx PAS Pto",
		"6 Z Km Lfx E Pto/18 Z Lfx E Pto",
		"其他",
	};
	int nSel = -1;
	int count = sizeof(sProjectSel)/sizeof(char*);
	for(int i=0; i<count; i++)
	{
		if(itemText == sProjectSel[i])
		{
			nSel = i;
			break;
		}
	}
	if(i==count) //其他
	{
		m_ProjectSelCtrl.SetCurSel(count-1);
		LOAD_DATA("D1", IDC_PROJECT);
		OnSelchangeProjectSel();
	}
	else
	{
		m_ProjectSelCtrl.SetCurSel(nSel);
		OnSelchangeProjectSel();
	}
	LOAD_DATA_DATE("D2", IDC_FIRST_TREAT_DATE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTableDlg1401::OnSelchangeProjectSel()
{
	int nSel = m_ProjectSelCtrl.GetCurSel();
	if (nSel == 13)//其他
	{
		GetDlgItem(IDC_PROJECT)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_PROJECT)->EnableWindow(FALSE);
	}
}
