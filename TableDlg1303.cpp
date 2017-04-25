// TableDlg1303.cpp : implementation file
//

#include "stdafx.h"
#include "TUI.h"
#include "TableDlg1303.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1303 dialog


CTableDlg1303::CTableDlg1303(CWnd* pParent /*=NULL*/)
	: CDialog(CTableDlg1303::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTableDlg1303)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTableDlg1303::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTableDlg1303)
	DDX_Control(pDX, IDC_IS_TO_NATIONAL, m_IsToNationalCtrl);
	DDX_Control(pDX, IDC_IS_TO_PROVINCE, m_IsToProvinceCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTableDlg1303, CDialog)
	//{{AFX_MSG_MAP(CTableDlg1303)
	ON_CBN_SELCHANGE(IDC_IS_TO_PROVINCE, OnSelchangeIsToProvince)
	ON_CBN_SELCHANGE(IDC_IS_TO_NATIONAL, OnSelchangeIsToNational)
	ON_BN_CLICKED(IDC_CONFIRM, OnConfirm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1303 message handlers

void CTableDlg1303::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CTableDlg1303::OnOK() 
{
	return;	
}

void CTableDlg1303::OnConfirm() 
{
	// TODO: Add extra validation here
	SAVE_DATA_COMBO("C16", IDC_IS_TO_PROVINCE);
	int iSel = m_IsToProvinceCtrl.GetCurSel();
	if (iSel == 2)//是
	{
		SAVE_DATA_DATE("C17", IDC_TO_PROVINCE_DATE);
	}
	else
	{
		pInd->SaveData("C17", "");
	}

	if (pInd->GetItem("C10") != "1:省级")
	{
		pInd->SetUnessaryData("C18", "C19");
	}
	else
	{
		SAVE_DATA_COMBO("C18", IDC_IS_TO_NATIONAL);
		iSel = m_IsToNationalCtrl.GetCurSel();
		if (iSel == 2)//是
		{
			SAVE_DATA_DATE("C19", IDC_TO_NATIONAL_DATE);
		}
		else
		{
			pInd->SaveData("C19", "");
		}
	}
	
	CDialog::OnOK();
}

BOOL CTableDlg1303::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	TABLE_DLG_INIT();
	LOAD_DATA_COMBO("C16", IDC_IS_TO_PROVINCE);
	OnSelchangeIsToProvince();
	LOAD_DATA_DATE("C17", IDC_TO_PROVINCE_DATE);
	LOAD_DATA_COMBO("C18", IDC_IS_TO_NATIONAL);
	if (pInd->GetItem("C10") == "1:省级")
	{
		OnSelchangeIsToNational();
	}
	else
	{
		GetDlgItem(IDC_IS_TO_NATIONAL)->EnableWindow(FALSE);
		GetDlgItem(IDC_TO_NATIONAL_DATE)->EnableWindow(FALSE);
	}
	LOAD_DATA_DATE("C19", IDC_TO_NATIONAL_DATE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTableDlg1303::OnSelchangeIsToProvince() 
{
	int iSel = m_IsToProvinceCtrl.GetCurSel();
	if( iSel != 2) //不是Yes
	{
		GetDlgItem(IDC_TO_PROVINCE_DATE)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_TO_PROVINCE_DATE)->EnableWindow(TRUE);
	}	
}

void CTableDlg1303::OnSelchangeIsToNational() 
{
	int iSel = m_IsToNationalCtrl.GetCurSel();
	if( iSel != 2) //不是Yes
	{
		GetDlgItem(IDC_TO_NATIONAL_DATE)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_TO_NATIONAL_DATE)->EnableWindow(TRUE);
	}
}