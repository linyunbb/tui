// ResearchTableDlg3.cpp : implementation file
//

#include "stdafx.h"
#include "TUI.h"
#include "ResearchTableDlg3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResearchTableDlg3 dialog


CResearchTableDlg3::CResearchTableDlg3(CWnd* pParent /*=NULL*/)
	: CDialog(CResearchTableDlg3::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResearchTableDlg3)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CResearchTableDlg3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResearchTableDlg3)
	DDX_Control(pDX, IDC_IS_TO_NATIONAL, m_IsToNational);
	DDX_Control(pDX, IDC_IS_TO_PROVINCE, m_IsToProvince);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResearchTableDlg3, CDialog)
	//{{AFX_MSG_MAP(CResearchTableDlg3)
	ON_BN_CLICKED(IDC_CONFIRM, OnConfirm)
	ON_CBN_SELCHANGE(IDC_IS_TO_PROVINCE, OnSelchangeIsToProvince)
	ON_CBN_SELCHANGE(IDC_IS_TO_NATIONAL, OnSelchangeIsToNational)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResearchTableDlg3 message handlers

void CResearchTableDlg3::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CResearchTableDlg3::OnOK() 
{
	// TODO: Add extra validation here
	return;	

}

void CResearchTableDlg3::OnConfirm() 
{
	SAVE_DATA_COMBO("H24", IDC_IS_TO_PROVINCE);
	if( m_IsToProvince.GetCurSel() == 2)
	{
		SAVE_DATA_DATE("H25", IDC_TO_PROVINCE_DATE);
	}
	else
	{
		pInd->SetUnessaryData("H25", "H25");
	}
	SAVE_DATA_COMBO("H26", IDC_IS_TO_NATIONAL);
	if (m_IsToNational.GetCurSel() == 2)
	{
		SAVE_DATA_DATE("H27", IDC_TO_NATIONAL_DATE);
	}
	else
	{
		pInd->SetUnessaryData("H27", "H27");
	}
	CDialog::OnOK();		
}

BOOL CResearchTableDlg3::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	TABLE_DLG_INIT();
	LOAD_DATA_COMBO("H24", IDC_IS_TO_PROVINCE);
	OnSelchangeIsToProvince();
	LOAD_DATA_DATE("H25", IDC_TO_PROVINCE_DATE);
	LOAD_DATA_COMBO("H26", IDC_IS_TO_NATIONAL);
	OnSelchangeIsToNational();
	LOAD_DATA_DATE("H27", IDC_TO_NATIONAL_DATE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CResearchTableDlg3::OnSelchangeIsToProvince() 
{
	int iSel = m_IsToProvince.GetCurSel();
	if( iSel != 2)//ÊÇ
	{
		GetDlgItem(IDC_TO_PROVINCE_DATE)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_TO_PROVINCE_DATE)->EnableWindow(TRUE);
	}
}

void CResearchTableDlg3::OnSelchangeIsToNational() 
{
	int iSel = m_IsToNational.GetCurSel();
	if( iSel != 2)//ÊÇ
	{
		GetDlgItem(IDC_TO_NATIONAL_DATE)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_TO_NATIONAL_DATE)->EnableWindow(TRUE);
	}	
}
