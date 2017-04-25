// TableDlg1206.cpp : implementation file
//

#include "stdafx.h"
#include "TUI.h"
#include "TableDlg1206.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1206 dialog


CTableDlg1206::CTableDlg1206(CWnd* pParent /*=NULL*/)
	: CDialog(CTableDlg1206::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTableDlg1206)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTableDlg1206::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTableDlg1206)
	DDX_Control(pDX, IDC_DIAGNOSTIC_RESULT, m_DiagResultCtrl);
	DDX_Control(pDX, IDC_PATIENT_SEARCH_INFO, m_PatientInfoCtrl);
	DDX_Control(pDX, IDC_WILLING_TO_BE_SEARCHED, m_IsWillingToBeSearched);
	DDX_Control(pDX, IDC_IS_SUITABLE, m_IsSuitableCtrl);
	DDX_Control(pDX, IDC_NDY_REGISTER_NO, m_NDYRegisterNoCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTableDlg1206, CDialog)
	//{{AFX_MSG_MAP(CTableDlg1206)
	ON_BN_CLICKED(IDC_CONFIRM, OnConfirm)
	ON_CBN_SELCHANGE(IDC_IS_SUITABLE, OnSelchangeIsSuitable)
	ON_CBN_SELCHANGE(IDC_WILLING_TO_BE_SEARCHED, OnSelchangeWillingToBeSearched)
	ON_CBN_SELCHANGE(IDC_PATIENT_SEARCH_INFO, OnSelchangePatientSearchInfo)
	ON_CBN_SELCHANGE(IDC_DIAGNOSTIC_RESULT, OnSelchangeDiagnosticResult)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1206 message handlers

void CTableDlg1206::OnCancel() 
{
	// TODO: Add extra cleanup here
	CDialog::OnCancel();
}

void CTableDlg1206::OnOK() 
{
	return;
}

BOOL CTableDlg1206::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	TABLE_DLG_INIT();
	
	m_NDYRegisterNoCtrl.InitEdit(DATA_TYPE_BUTT, 20, "");

	LOAD_DATA_COMBO("B26", IDC_DIAGNOSTIC_RESULT);
	OnSelchangeDiagnosticResult();
	LOAD_DATA_DATE("B27", IDC_REPORT_DATE);
	LOAD_DATA("B28", IDC_NDY_REGISTER_NO);
	LOAD_DATA_COMBO("B29", IDC_IS_SUITABLE);
	OnSelchangeIsSuitable();
	LOAD_DATA_COMBO("B30", IDC_WILLING_TO_BE_SEARCHED);
	OnSelchangeWillingToBeSearched();
	LOAD_DATA_COMBO("B31", IDC_PATIENT_SEARCH_INFO);
	OnSelchangePatientSearchInfo();
	LOAD_DATA_DATE("B32", IDC_PATIENT_SEARCH_INFO_DATE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTableDlg1206::OnConfirm() 
{
	int nSel;
	// TODO: Add extra validation here
	SAVE_DATA_COMBO("B26", IDC_DIAGNOSTIC_RESULT);
	nSel = m_DiagResultCtrl.GetCurSel();
	if( nSel == 4 || nSel == 5)
	{
		SAVE_DATA_DATE("B27", IDC_REPORT_DATE);
		SAVE_DATA("B28", IDC_NDY_REGISTER_NO);
	}
	else
	{
		pInd->SetUnessaryData("B27", "B28");
	}
	SAVE_DATA_COMBO("B29", IDC_IS_SUITABLE);
	nSel = m_IsSuitableCtrl.GetCurSel();
	if( nSel == 0 || nSel == 1)
	{
		pInd->SetUnessaryData("B30", "B32");
	}
	else if(nSel == 2)
	{
		SAVE_DATA_COMBO("B30", IDC_WILLING_TO_BE_SEARCHED);
		if( m_IsWillingToBeSearched.GetCurSel() == 2)
		{
			SAVE_DATA_COMBO("B31", IDC_PATIENT_SEARCH_INFO);
			nSel = m_PatientInfoCtrl.GetCurSel();
			if( nSel >=1 && nSel <=4)
			{
				SAVE_DATA_DATE("B32", IDC_PATIENT_SEARCH_INFO_DATE);
			}
			else
			{
				pInd->SetUnessaryData("B32", "B32");
			}
		}
		else
		{
			pInd->SetUnessaryData("B31", "B32");
		}
	}
	pInd->CheckAllTableItems();	
	CDialog::OnOK();
}

void CTableDlg1206::OnSelchangeIsSuitable() 
{
	int nSel = m_IsSuitableCtrl.GetCurSel();
	if( nSel == 0 || nSel == 1)
	{
		m_IsWillingToBeSearched.EnableWindow(FALSE);
		m_PatientInfoCtrl.EnableWindow(FALSE);
	}
	else if(nSel == 2)
	{
		m_IsWillingToBeSearched.EnableWindow(TRUE);
		if( m_IsWillingToBeSearched.GetCurSel() == 2)
		{
			m_PatientInfoCtrl.EnableWindow(TRUE);
		}
	}
}

void CTableDlg1206::OnSelchangeWillingToBeSearched() 
{
	int nSel = m_IsWillingToBeSearched.GetCurSel();
	if( nSel == 0 || nSel == 1)
	{
		m_PatientInfoCtrl.EnableWindow(FALSE);
	}
	else if(nSel == 2)
	{
		m_PatientInfoCtrl.EnableWindow(TRUE);
	}
}

void CTableDlg1206::OnSelchangePatientSearchInfo() 
{
	int nSel = m_PatientInfoCtrl.GetCurSel();
	if( nSel >=1 && nSel <=4)
	{
		GetDlgItem(IDC_PATIENT_SEARCH_INFO_DATE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_PATIENT_SEARCH_INFO_DATE)->EnableWindow(FALSE);
	}
}

void CTableDlg1206::OnSelchangeDiagnosticResult() 
{
	int nSel = m_DiagResultCtrl.GetCurSel();
	if( nSel == 4 || nSel == 5)
	{
		GetDlgItem(IDC_REPORT_DATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_NDY_REGISTER_NO)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_REPORT_DATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_NDY_REGISTER_NO)->EnableWindow(FALSE);
	}	
}