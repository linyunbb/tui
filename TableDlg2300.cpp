// TableDlg2300.cpp : implementation file
//

#include "stdafx.h"
#include "TUI.h"
#include "TableDlg2300.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTableDlg2300 dialog


CTableDlg2300::CTableDlg2300(CWnd* pParent /*=NULL*/)
	: CDialog(CTableDlg2300::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTableDlg2300)
	//}}AFX_DATA_INIT
}


void CTableDlg2300::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTableDlg2300)
	DDX_Control(pDX, IDC_DOCTOER_NAME, m_DoctorNameCtrl);
	DDX_Control(pDX, IDC_OTHER_SOURCE, m_G12);
	DDX_Control(pDX, IDC_PERSONAL_PAID, m_G11);
	DDX_Control(pDX, IDC_OTHER_COMMERCIAL_REIMBURSEMENT, m_G10);
	DDX_Control(pDX, IDC_GLOBAL_FUND_REIMBURSEMENT, m_G9);
	DDX_Control(pDX, IDC_MEDICARE_ACTUAL_REIMBURSEMENT, m_G8);
	DDX_Control(pDX, IDC_EXPENSE_FOR_ACCOMMODATION, m_G6);
	DDX_Control(pDX, IDC_EXPENSE_FOR_TRAVAL, m_G5);
	DDX_Control(pDX, IDC_EXPENSE_FOR_ASSISTANT_MEDICINE, m_G4);
	DDX_Control(pDX, IDC_ANTI_TUB_MEDICINE, m_G3);
	DDX_Control(pDX, IDC_EXPENSE_FOR_INJECTION, m_G2);
	DDX_Control(pDX, IDC_EXPENSE_RANDOM_CHECK, m_G1);
	DDX_Control(pDX, IDC_MEDICAL_CARE_CATEGORY, m_MedicareCategoryCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTableDlg2300, CDialog)
	//{{AFX_MSG_MAP(CTableDlg2300)
	ON_BN_CLICKED(IDC_CONFIRM, OnConfirm)
	ON_CBN_SELCHANGE(IDC_MEDICAL_CARE_CATEGORY, OnSelchangeMedicalCareCategory)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableDlg2300 message handlers

void CTableDlg2300::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CTableDlg2300::OnConfirm() 
{
	// TODO: Add your control notification handler code here
	SAVE_DATA("G1", IDC_EXPENSE_RANDOM_CHECK);
	SAVE_DATA("G2", IDC_EXPENSE_FOR_INJECTION);
	SAVE_DATA("G3", IDC_ANTI_TUB_MEDICINE);
	SAVE_DATA("G4", IDC_EXPENSE_FOR_ASSISTANT_MEDICINE);
	SAVE_DATA("G5", IDC_EXPENSE_FOR_TRAVAL);
	SAVE_DATA("G6", IDC_EXPENSE_FOR_ACCOMMODATION);
	SAVE_DATA_COMBO("G7", IDC_MEDICAL_CARE_CATEGORY);
	int nSel = m_MedicareCategoryCtrl.GetCurSel();
	if( nSel == 0 || nSel == 1)//нч
	{
		pInd->SetUnessaryData("G8", "G8");
	}
	else if(nSel >= 2)
	{
		SAVE_DATA("G8", IDC_MEDICARE_ACTUAL_REIMBURSEMENT);
	}
	SAVE_DATA("G9", IDC_GLOBAL_FUND_REIMBURSEMENT);
	SAVE_DATA("G10", IDC_OTHER_COMMERCIAL_REIMBURSEMENT);
	SAVE_DATA("G11", IDC_PERSONAL_PAID);
	SAVE_DATA("G12", IDC_OTHER_SOURCE);
	SAVE_DATA("G13", IDC_DOCTOER_NAME);
	SAVE_DATA_DATE("G14", IDC_FILLING_DATE);
	CDialog::OnOK();
}

void CTableDlg2300::OnOK() 
{
	// TODO: Add extra validation here
	return;	
	CDialog::OnOK();
}

BOOL CTableDlg2300::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_G1.InitEdit(DATA_TYPE_MONEY, 9, "");
	m_G2.InitEdit(DATA_TYPE_MONEY, 9, "");
	m_G3.InitEdit(DATA_TYPE_MONEY, 9, "");
	m_G4.InitEdit(DATA_TYPE_MONEY, 9, "");
	m_G5.InitEdit(DATA_TYPE_MONEY, 9, "");
	m_G6.InitEdit(DATA_TYPE_MONEY, 9, "");

	m_G8.InitEdit(DATA_TYPE_MONEY, 9, "");
	m_G9.InitEdit(DATA_TYPE_MONEY, 9, "");
	m_G10.InitEdit(DATA_TYPE_MONEY, 9, "");
	m_G11.InitEdit(DATA_TYPE_MONEY, 9, "");
	m_G12.InitEdit(DATA_TYPE_MONEY, 9, "");
	
	m_DoctorNameCtrl.InitEdit(DATA_TYPE_BUTT, 20, "");

	TABLE_DLG_INIT();
	
	LOAD_DATA("G1", IDC_EXPENSE_RANDOM_CHECK);
	LOAD_DATA("G2", IDC_EXPENSE_FOR_INJECTION);
	LOAD_DATA("G3", IDC_ANTI_TUB_MEDICINE);
	LOAD_DATA("G4", IDC_EXPENSE_FOR_ASSISTANT_MEDICINE);
	LOAD_DATA("G5", IDC_EXPENSE_FOR_TRAVAL);
	LOAD_DATA("G6", IDC_EXPENSE_FOR_ACCOMMODATION);
	LOAD_DATA_COMBO("G7", IDC_MEDICAL_CARE_CATEGORY);
	OnSelchangeMedicalCareCategory();
	LOAD_DATA("G8", IDC_MEDICARE_ACTUAL_REIMBURSEMENT);
	LOAD_DATA("G9", IDC_GLOBAL_FUND_REIMBURSEMENT);
	LOAD_DATA("G10", IDC_OTHER_COMMERCIAL_REIMBURSEMENT);
	LOAD_DATA("G11", IDC_PERSONAL_PAID);
	LOAD_DATA("G12", IDC_OTHER_SOURCE);
	LOAD_DATA("G13", IDC_DOCTOER_NAME);
	LOAD_DATA_DATE("G14", IDC_FILLING_DATE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTableDlg2300::OnSelchangeMedicalCareCategory() 
{
	int nSel = m_MedicareCategoryCtrl.GetCurSel();
	if( nSel == 0 || nSel == 1)//нч
	{
		GetDlgItem(IDC_MEDICARE_ACTUAL_REIMBURSEMENT)->EnableWindow(FALSE);
	}
	else if(nSel >= 2)
	{
		GetDlgItem(IDC_MEDICARE_ACTUAL_REIMBURSEMENT)->EnableWindow(TRUE);
	}	
}
