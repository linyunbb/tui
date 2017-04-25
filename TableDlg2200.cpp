// TableDlg2200.cpp : implementation file
//

#include "stdafx.h"
#include "TUI.h"
#include "TableDlg2200.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTableDlg2200 dialog


CTableDlg2200::CTableDlg2200(CWnd* pParent /*=NULL*/)
	: CDialog(CTableDlg2200::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTableDlg2200)
	//}}AFX_DATA_INIT
}


void CTableDlg2200::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTableDlg2200)
	DDX_Control(pDX, IDC_DOCTOER_NAME, m_DoctorNameCtrl);
	DDX_Control(pDX, IDC_OTHER_SOURCE, m_F18);
	DDX_Control(pDX, IDC_PERSONAL_PAID, m_F17);
	DDX_Control(pDX, IDC_OTHER_COMMERCIAL_REIMBURSEMENT, m_F16);
	DDX_Control(pDX, IDC_GLOBAL_FUND_REIMBURSEMENT, m_F15);
	DDX_Control(pDX, IDC_MEDICARE_ACTUAL_REIMBURSEMENT, m_F14);
	DDX_Control(pDX, IDC_EXPENSE_FOR_ACCOMMODATION, m_F12);
	DDX_Control(pDX, IDC_EXPENSE_FOR_TRAVAL, m_F11);
	DDX_Control(pDX, IDC_EXPENSE_OTHERS, m_F10);
	DDX_Control(pDX, IDC_EXPENSE_SURGERY, m_F9);
	DDX_Control(pDX, IDC_EXPENSE_FOR_ASSISTANT_MEDICINE, m_F8);
	DDX_Control(pDX, IDC_ANTI_TUB_MEDICINE, m_F7);
	DDX_Control(pDX, IDC_EXPENSE_OTHER_ASSAY, m_F6);
	DDX_Control(pDX, IDC_EXPENSE_DIAGNOS, m_F5);
	DDX_Control(pDX, IDC_EXPENSE_FOR_NURSING_CARE, m_F4);
	DDX_Control(pDX, IDC_EXPENSE_FOR_BED, m_F3);
	DDX_Control(pDX, IDC_ACTUAL_TOTAL, m_F2);
	DDX_Control(pDX, IDC_IN_HOSPITAL_NO, m_F1);
	DDX_Control(pDX, IDC_MEDICAL_CARE_CATEGORY, m_MedicareCategoryCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTableDlg2200, CDialog)
	//{{AFX_MSG_MAP(CTableDlg2200)
	ON_BN_CLICKED(IDC_CONFIRM, OnConfirm)
	ON_CBN_SELCHANGE(IDC_MEDICAL_CARE_CATEGORY, OnSelchangeMedicalCareCategory)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableDlg2200 message handlers

void CTableDlg2200::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CTableDlg2200::OnConfirm() 
{
	// TODO: Add your control notification handler code here
	SAVE_DATA("F1", IDC_IN_HOSPITAL_NO);
	SAVE_DATA("F2", IDC_ACTUAL_TOTAL);
	SAVE_DATA("F3", IDC_EXPENSE_FOR_BED);
	SAVE_DATA("F4", IDC_EXPENSE_FOR_NURSING_CARE);
	SAVE_DATA("F5", IDC_EXPENSE_DIAGNOS);
	SAVE_DATA("F6", IDC_EXPENSE_OTHER_ASSAY);
	SAVE_DATA("F7", IDC_ANTI_TUB_MEDICINE);
	SAVE_DATA("F8", IDC_EXPENSE_FOR_ASSISTANT_MEDICINE);
	SAVE_DATA("F9", IDC_EXPENSE_SURGERY);
	SAVE_DATA("F10", IDC_EXPENSE_OTHERS);
	SAVE_DATA("F11", IDC_EXPENSE_FOR_TRAVAL);
	SAVE_DATA("F12", IDC_EXPENSE_FOR_ACCOMMODATION);
	SAVE_DATA_COMBO("F13", IDC_MEDICAL_CARE_CATEGORY);
	int nSel = m_MedicareCategoryCtrl.GetCurSel();
	if( nSel == 0 || nSel == 1)//нч
	{
		pInd->SetUnessaryData("F14", "F14");
	}
	else if(nSel >= 2)
	{
		SAVE_DATA("F14", IDC_MEDICARE_ACTUAL_REIMBURSEMENT);
	}
	SAVE_DATA("F15", IDC_GLOBAL_FUND_REIMBURSEMENT);
	SAVE_DATA("F16", IDC_OTHER_COMMERCIAL_REIMBURSEMENT);
	SAVE_DATA("F17", IDC_PERSONAL_PAID);
	SAVE_DATA("F18", IDC_OTHER_SOURCE);
	SAVE_DATA("F19", IDC_DOCTOER_NAME);
	SAVE_DATA_DATE("F20", IDC_FILLING_DATE);
	CDialog::OnOK();
	
}

void CTableDlg2200::OnOK() 
{
	// TODO: Add extra validation here
	return;	
	CDialog::OnOK();
}

BOOL CTableDlg2200::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_F1.InitEdit(DATA_TYPE_BUTT, 20, "");
	m_F2.InitEdit(DATA_TYPE_MONEY, 9, "");
	m_F3.InitEdit(DATA_TYPE_MONEY, 9, "");
	m_F4.InitEdit(DATA_TYPE_MONEY, 9, "");
	m_F5.InitEdit(DATA_TYPE_MONEY, 9, "");
	m_F6.InitEdit(DATA_TYPE_MONEY, 9, "");
	m_F7.InitEdit(DATA_TYPE_MONEY, 9, "");
	m_F8.InitEdit(DATA_TYPE_MONEY, 9, "");
	m_F9.InitEdit(DATA_TYPE_MONEY, 9, "");
	m_F10.InitEdit(DATA_TYPE_MONEY, 9, "");
	m_F11.InitEdit(DATA_TYPE_MONEY, 9, "");
	m_F12.InitEdit(DATA_TYPE_MONEY, 9, "");

	m_F14.InitEdit(DATA_TYPE_MONEY, 9, "");
	m_F15.InitEdit(DATA_TYPE_MONEY, 9, "");
	m_F16.InitEdit(DATA_TYPE_MONEY, 9, "");
	m_F17.InitEdit(DATA_TYPE_MONEY, 9, "");
	m_F18.InitEdit(DATA_TYPE_MONEY, 9, "");
	
	m_DoctorNameCtrl.InitEdit(DATA_TYPE_BUTT, 20, "");

	TABLE_DLG_INIT();

	LOAD_DATA("F1", IDC_IN_HOSPITAL_NO);
	LOAD_DATA("F2", IDC_ACTUAL_TOTAL);
	LOAD_DATA("F3", IDC_EXPENSE_FOR_BED);
	LOAD_DATA("F4", IDC_EXPENSE_FOR_NURSING_CARE);
	LOAD_DATA("F5", IDC_EXPENSE_DIAGNOS);
	LOAD_DATA("F6", IDC_EXPENSE_OTHER_ASSAY);
	LOAD_DATA("F7", IDC_ANTI_TUB_MEDICINE);
	LOAD_DATA("F8", IDC_EXPENSE_FOR_ASSISTANT_MEDICINE);
	LOAD_DATA("F9", IDC_EXPENSE_SURGERY);
	LOAD_DATA("F10", IDC_EXPENSE_OTHERS);
	LOAD_DATA("F11", IDC_EXPENSE_FOR_TRAVAL);
	LOAD_DATA("F12", IDC_EXPENSE_FOR_ACCOMMODATION);
	LOAD_DATA_COMBO("F13", IDC_MEDICAL_CARE_CATEGORY);
	OnSelchangeMedicalCareCategory();
	LOAD_DATA("F14", IDC_MEDICARE_ACTUAL_REIMBURSEMENT);
	LOAD_DATA("F15", IDC_GLOBAL_FUND_REIMBURSEMENT);
	LOAD_DATA("F16", IDC_OTHER_COMMERCIAL_REIMBURSEMENT);
	LOAD_DATA("F17", IDC_PERSONAL_PAID);
	LOAD_DATA("F18", IDC_OTHER_SOURCE);
	LOAD_DATA("F19", IDC_DOCTOER_NAME);
	LOAD_DATA_DATE("F20", IDC_FILLING_DATE);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTableDlg2200::OnSelchangeMedicalCareCategory() 
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
