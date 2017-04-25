// ResearchTableDlg1.cpp : implementation file
//

#include "stdafx.h"
#include "TUI.h"
#include "ResearchTableDlg1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResearchTableDlg1 dialog


CResearchTableDlg1::CResearchTableDlg1(CWnd* pParent /*=NULL*/)
	: CDialog(CResearchTableDlg1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResearchTableDlg1)
	//}}AFX_DATA_INIT
}


void CResearchTableDlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResearchTableDlg1)
	DDX_Control(pDX, IDC_IS_AGREED, m_IsWillingCtrl);
	DDX_Control(pDX, IDC_RESPIRATORY_SYSTEM_DISEASE_YESNO, m_HasRespitatoryCtrl);
	DDX_Control(pDX, IDC_CHRONIC_DISEASE_HISTORY, m_HasChronicCtrl);
	DDX_Control(pDX, IDC_IS_EXCLUDED_BY_X, m_IsExcludedCtrl);
	DDX_Control(pDX, IDC_TUB_HISTORY_YESNO, m_HasHistoryCtrl);
	DDX_Control(pDX, IDC_DOCTOR_NAME, m_DoctorNameCtrl);
	DDX_Control(pDX, IDC_CONTACT_INFO, m_ContactInfo);
	DDX_Control(pDX, IDC_LOCAL_LIVING_YEAR, m_LivingYearsCtrl);
	DDX_Control(pDX, IDC_AGE, m_AgeCtrl);
	DDX_Control(pDX, IDC_NAME, m_NameCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResearchTableDlg1, CDialog)
	//{{AFX_MSG_MAP(CResearchTableDlg1)
	ON_BN_CLICKED(IDC_CONFIRM, OnConfirm)
	ON_EN_CHANGE(IDC_LOCAL_LIVING_YEAR, OnChangeLocalLivingYear)
	ON_CBN_SELCHANGE(IDC_TUB_HISTORY_YESNO, OnSelchangeTubHistoryYesno)
	ON_CBN_SELCHANGE(IDC_IS_EXCLUDED_BY_X, OnSelchangeIsExcludedByX)
	ON_CBN_SELCHANGE(IDC_CHRONIC_DISEASE_HISTORY, OnSelchangeChronicDiseaseHistory)
	ON_CBN_SELCHANGE(IDC_RESPIRATORY_SYSTEM_DISEASE_YESNO, OnSelchangeRespiratorySystemDiseaseYesno)
	ON_CBN_SELCHANGE(IDC_IS_AGREED, OnSelchangeIsAgreed)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResearchTableDlg1 message handlers

void CResearchTableDlg1::OnConfirm() 
{
	SAVE_DATA("H1", IDC_ID);
	SAVE_DATA("H2", IDC_NAME);
	SAVE_DATA_COMBO("H3", IDC_SEX_COMBO);
	SAVE_DATA("H4", IDC_AGE);
	SAVE_DATA("H5", IDC_CONTACT_INFO);
	SAVE_DATA("H6", IDC_LOCAL_LIVING_YEAR);
	CString itemText;
	m_LivingYearsCtrl.GetWindowText(itemText);
	int nLivingAge = atoi(itemText);
	if (itemText == "" || nLivingAge == 0)
	{
		pInd->SetUnessaryData("H7", "H12");
	}
	else
	{
		SAVE_DATA_COMBO("H7",IDC_TUB_HISTORY_YESNO);
		if(m_HasHistoryCtrl.GetCurSel() == 1)
		{
			SAVE_DATA_COMBO("H8", IDC_IS_EXCLUDED_BY_X);
			if(m_IsExcludedCtrl.GetCurSel() ==2 )
			{
				SAVE_DATA_COMBO("H9", IDC_CHRONIC_DISEASE_HISTORY);
				if(m_HasChronicCtrl.GetCurSel() ==1)
				{
					SAVE_DATA_COMBO("H10", IDC_RESPIRATORY_SYSTEM_DISEASE_YESNO);
					if(m_HasRespitatoryCtrl.GetCurSel() == 1)
					{
						SAVE_DATA_COMBO("H11", IDC_IS_AGREED);
						if(m_IsWillingCtrl.GetCurSel() == 2)
						{
							SAVE_DATA_COMBO("H12", IDC_IS_OBSORBED);
						}
						else
						{
							pInd->SetUnessaryData("H12", "H12");
						}
					}
					else
					{
						pInd->SetUnessaryData("H11", "H12");
					}
				}
				else
				{
					pInd->SetUnessaryData("H10", "H12");
				}
			}
			else
			{
				pInd->SetUnessaryData("H9", "H12");
			}
		}
		else
		{
			pInd->SetUnessaryData("H8", "H12");
		}
	}
	SAVE_DATA("H13", IDC_DOCTOR_NAME);
	SAVE_DATA_DATE("H14", IDC_FILLING_DATE);
	CDialog::OnOK();
	
}

void CResearchTableDlg1::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CResearchTableDlg1::OnOK() 
{
	// TODO: Add extra validation here
	return;
	CDialog::OnOK();
}

BOOL CResearchTableDlg1::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_AgeCtrl.InitEdit(DATA_TYPE_NUMBER, 3, "");
	m_LivingYearsCtrl.InitEdit(DATA_TYPE_NUMBER, 3, "");
	m_NameCtrl.InitEdit(DATA_TYPE_BUTT, 20, "");

	// TODO: Add extra initialization here
	TABLE_DLG_INIT();
	LOAD_DATA("H1", IDC_ID);
	LOAD_DATA("H2", IDC_NAME);
	LOAD_DATA_COMBO("H3", IDC_SEX_COMBO);
	LOAD_DATA("H4", IDC_AGE);
	LOAD_DATA("H5", IDC_CONTACT_INFO);
	LOAD_DATA("H6", IDC_LOCAL_LIVING_YEAR);
	OnChangeLocalLivingYear();
	LOAD_DATA_COMBO("H7",IDC_TUB_HISTORY_YESNO);
	OnSelchangeTubHistoryYesno();
	LOAD_DATA_COMBO("H8", IDC_IS_EXCLUDED_BY_X);
	OnSelchangeIsExcludedByX();
	LOAD_DATA_COMBO("H9", IDC_CHRONIC_DISEASE_HISTORY);
	OnSelchangeChronicDiseaseHistory();
	LOAD_DATA_COMBO("H10", IDC_RESPIRATORY_SYSTEM_DISEASE_YESNO);
	OnSelchangeRespiratorySystemDiseaseYesno();
	LOAD_DATA_COMBO("H11", IDC_IS_AGREED);
	OnSelchangeIsAgreed();
	LOAD_DATA_COMBO("H12", IDC_IS_OBSORBED);
	LOAD_DATA("H13", IDC_DOCTOR_NAME);
	LOAD_DATA_DATE("H14", IDC_FILLING_DATE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CResearchTableDlg1::OnChangeLocalLivingYear() 
{
	CString itemText;
	m_LivingYearsCtrl.GetWindowText(itemText);
	int nLivingAge = atoi(itemText);
	if (itemText == "" || nLivingAge == 0)
	{
		GetDlgItem(IDC_TUB_HISTORY_YESNO)->EnableWindow(FALSE);
		GetDlgItem(IDC_IS_EXCLUDED_BY_X)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHRONIC_DISEASE_HISTORY)->EnableWindow(FALSE);
		GetDlgItem(IDC_RESPIRATORY_SYSTEM_DISEASE_YESNO)->EnableWindow(FALSE);
		GetDlgItem(IDC_IS_AGREED)->EnableWindow(FALSE);
		GetDlgItem(IDC_IS_OBSORBED)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_TUB_HISTORY_YESNO)->EnableWindow(TRUE);
		if(m_HasHistoryCtrl.GetCurSel() == 1)
		{
			GetDlgItem(IDC_IS_EXCLUDED_BY_X)->EnableWindow(TRUE);
			if(m_IsExcludedCtrl.GetCurSel() ==2 )
			{
				GetDlgItem(IDC_CHRONIC_DISEASE_HISTORY)->EnableWindow(TRUE);
				if(m_HasChronicCtrl.GetCurSel() ==1)
				{
					GetDlgItem(IDC_RESPIRATORY_SYSTEM_DISEASE_YESNO)->EnableWindow(TRUE);
					if(m_HasRespitatoryCtrl.GetCurSel() == 1)
					{
						GetDlgItem(IDC_IS_AGREED)->EnableWindow(TRUE);
						if(m_IsWillingCtrl.GetCurSel() == 2)
						{
							GetDlgItem(IDC_IS_OBSORBED)->EnableWindow(TRUE);
						}
					}
				}
			}
		}
	}
}

void CResearchTableDlg1::OnSelchangeTubHistoryYesno() 
{
	int nSel = m_HasHistoryCtrl.GetCurSel();
	if( nSel != 1) //无
	{
		GetDlgItem(IDC_IS_EXCLUDED_BY_X)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHRONIC_DISEASE_HISTORY)->EnableWindow(FALSE);
		GetDlgItem(IDC_RESPIRATORY_SYSTEM_DISEASE_YESNO)->EnableWindow(FALSE);
		GetDlgItem(IDC_IS_AGREED)->EnableWindow(FALSE);
		GetDlgItem(IDC_IS_OBSORBED)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_IS_EXCLUDED_BY_X)->EnableWindow(TRUE);
		if(m_IsExcludedCtrl.GetCurSel() ==2 )
		{
			GetDlgItem(IDC_CHRONIC_DISEASE_HISTORY)->EnableWindow(TRUE);
			if(m_HasChronicCtrl.GetCurSel() ==1)
			{
				GetDlgItem(IDC_RESPIRATORY_SYSTEM_DISEASE_YESNO)->EnableWindow(TRUE);
				if(m_HasRespitatoryCtrl.GetCurSel() == 1)
				{
					GetDlgItem(IDC_IS_AGREED)->EnableWindow(TRUE);
					if(m_IsWillingCtrl.GetCurSel() == 2)
					{
						GetDlgItem(IDC_IS_OBSORBED)->EnableWindow(TRUE);
					}
				}
			}
		}
	}
}

void CResearchTableDlg1::OnSelchangeIsExcludedByX() 
{
	int nSel = m_IsExcludedCtrl.GetCurSel();
	if( nSel != 2) //是
	{
		GetDlgItem(IDC_CHRONIC_DISEASE_HISTORY)->EnableWindow(FALSE);
		GetDlgItem(IDC_RESPIRATORY_SYSTEM_DISEASE_YESNO)->EnableWindow(FALSE);
		GetDlgItem(IDC_IS_AGREED)->EnableWindow(FALSE);
		GetDlgItem(IDC_IS_OBSORBED)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_CHRONIC_DISEASE_HISTORY)->EnableWindow(TRUE);
		if(m_HasChronicCtrl.GetCurSel() ==1)
		{
			GetDlgItem(IDC_RESPIRATORY_SYSTEM_DISEASE_YESNO)->EnableWindow(TRUE);
			if(m_HasRespitatoryCtrl.GetCurSel() ==1)
			{
				GetDlgItem(IDC_IS_AGREED)->EnableWindow(TRUE);
				if(m_IsWillingCtrl.GetCurSel() == 2)
				{
					GetDlgItem(IDC_IS_OBSORBED)->EnableWindow(TRUE);
				}
			}
		}
	}
}

void CResearchTableDlg1::OnSelchangeChronicDiseaseHistory() 
{
	int nSel = m_HasChronicCtrl.GetCurSel();
	if( nSel != 1) //无
	{
		GetDlgItem(IDC_RESPIRATORY_SYSTEM_DISEASE_YESNO)->EnableWindow(FALSE);
		GetDlgItem(IDC_IS_AGREED)->EnableWindow(FALSE);
		GetDlgItem(IDC_IS_OBSORBED)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_RESPIRATORY_SYSTEM_DISEASE_YESNO)->EnableWindow(TRUE);
		if(m_HasRespitatoryCtrl.GetCurSel() ==1)
		{
			GetDlgItem(IDC_IS_AGREED)->EnableWindow(TRUE);
			if(m_IsWillingCtrl.GetCurSel() == 2)
			{
				GetDlgItem(IDC_IS_OBSORBED)->EnableWindow(TRUE);
			}
		}
	}
}

void CResearchTableDlg1::OnSelchangeRespiratorySystemDiseaseYesno() 
{
	int nSel = m_HasRespitatoryCtrl.GetCurSel();
	if( nSel != 1) //无
	{
		GetDlgItem(IDC_IS_AGREED)->EnableWindow(FALSE);
		GetDlgItem(IDC_IS_OBSORBED)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_IS_AGREED)->EnableWindow(TRUE);
		if(m_IsWillingCtrl.GetCurSel() == 2)
		{
			GetDlgItem(IDC_IS_OBSORBED)->EnableWindow(TRUE);
		}
	}
}

void CResearchTableDlg1::OnSelchangeIsAgreed() 
{
	int nSel = m_IsWillingCtrl.GetCurSel();
	if( nSel != 2) //无
	{
		GetDlgItem(IDC_IS_OBSORBED)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_IS_OBSORBED)->EnableWindow(TRUE);
	}
}
