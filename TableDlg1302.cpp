// TableDlg1302.cpp : implementation file
//

#include "stdafx.h"
#include "TUI.h"
#include "TableDlg1302.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1302 dialog


CTableDlg1302::CTableDlg1302(CWnd* pParent /*=NULL*/)
	: CDialog(CTableDlg1302::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTableDlg1302)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTableDlg1302::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTableDlg1302)
	DDX_Control(pDX, IDC_IS_TO_NATIONAL, m_IsToNationalCtrl);
	DDX_Control(pDX, IDC_IS_TO_PROVINCE, m_IsToProvinceCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTableDlg1302, CDialog)
	//{{AFX_MSG_MAP(CTableDlg1302)
	ON_CBN_SELCHANGE(IDC_IS_TO_PROVINCE, OnSelchangeIsToProvince)
	ON_CBN_SELCHANGE(IDC_IS_TO_NATIONAL, OnSelchangeIsToNational)
	ON_BN_CLICKED(IDC_CONFIRM, OnConfirm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1302 message handlers

void CTableDlg1302::OnOK() 
{
	return;	
}
	
void CTableDlg1302::OnConfirm() 
{
	SAVE_DATA_COMBO("C12", IDC_IS_TO_PROVINCE);
	int iSel = m_IsToProvinceCtrl.GetCurSel();
	if (iSel == 2) //是
	{
		SAVE_DATA_DATE("C13", IDC_TO_PROVINCE_DATE);
	}
	else//否或尚未确定
	{
		pInd->SaveData("C13", "");
	}

	SAVE_DATA_COMBO("C14", IDC_IS_TO_NATIONAL);
	iSel = m_IsToNationalCtrl.GetCurSel();
	if (iSel == 2)//是
	{
		SAVE_DATA_DATE("C15", IDC_TO_NATIONAL_DATE);
	}
	else//否或尚未确定
	{
		pInd->SaveData("C15", "");
	}
	CDialog::OnOK();
}

void CTableDlg1302::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CTableDlg1302::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	TABLE_DLG_INIT();
	LOAD_DATA_COMBO("C12", IDC_IS_TO_PROVINCE);
	OnSelchangeIsToProvince();
	LOAD_DATA_DATE("C13", IDC_TO_PROVINCE_DATE);
	LOAD_DATA_COMBO("C14", IDC_IS_TO_NATIONAL);
	OnSelchangeIsToNational();
	LOAD_DATA_DATE("C15", IDC_TO_NATIONAL_DATE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTableDlg1302::OnSelchangeIsToProvince() 
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

void CTableDlg1302::OnSelchangeIsToNational() 
{
	int iSel = m_IsToNationalCtrl.GetCurSel();
	if( iSel != 2) //不是Yes
	{
		GetDlgItem(IDC_TO_NATIONAL_DATE)->EnableWindow(FALSE);
		pInd->SetUnessaryData("C15", "C15");
	}
	else
	{
		GetDlgItem(IDC_TO_NATIONAL_DATE)->EnableWindow(TRUE);
	}
}
