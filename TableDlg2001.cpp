// TableDlg2001.cpp : implementation file
//

#include "stdafx.h"
#include "TUI.h"
#include "TableDlg2001.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTableDlg2001 dialog


CTableDlg2001::CTableDlg2001(CWnd* pParent /*=NULL*/)
	: CDialog(CTableDlg2001::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTableDlg2001)
	//}}AFX_DATA_INIT
}


void CTableDlg2001::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTableDlg2001)
	DDX_Control(pDX, IDC_DOCTOER_NAME, m_DoctorName);
	DDX_Control(pDX, IDC_FEE_FOR_DINNER_ACCOMPANY, m_FeeForMealsACtrl);
	DDX_Control(pDX, IDC_HOW_MANY_DINNERS_ACCOMPANY, m_HowManyMealsACtrl);
	DDX_Control(pDX, IDC_FEE_FOR_STAY_OUTSIDE_ACCOMPANY, m_FeeForStayOutSideACtrl);
	DDX_Control(pDX, IDC_FEE_FOR_VEHICLE_ACCOMPANY, m_FeeForVehicleACtrl);
	DDX_Control(pDX, IDC_HOW_MANY_ACCOMPANY, m_HowManyAccomanyCtrl);
	DDX_Control(pDX, IDC_FEE_FOR_DINNER, m_FeeForMealCtrl);
	DDX_Control(pDX, IDC_HOW_MANY_DINNERS, m_HowManyMealsCtrl);
	DDX_Control(pDX, IDC_FEE_FOR_STAY_OUTSIDE, m_FeeForStayOutsideCtrl);
	DDX_Control(pDX, IDC_FEE_FOR_VEHICLE, m_FeeForVehicleCtrl);
	DDX_Control(pDX, IDC_HOW_FAR, m_HowFarCtrl);
	DDX_Control(pDX, IDC_IS_STAY_OUTSIDE_ACCOMPANY, m_IsCompanyStayOutSide);
	DDX_Control(pDX, IDC_IS_ACCOMPANY, m_HasCompanyCtrl);
	DDX_Control(pDX, IDC_IS_STAY_OUTSIDE, m_IsStayOutside);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTableDlg2001, CDialog)
	//{{AFX_MSG_MAP(CTableDlg2001)
	ON_BN_CLICKED(IDC_CONFIRM, OnConfirm)
	ON_CBN_SELCHANGE(IDC_IS_STAY_OUTSIDE, OnSelchangeIsStayOutside)
	ON_CBN_SELCHANGE(IDC_IS_ACCOMPANY, OnSelchangeIsAccompany)
	ON_CBN_SELCHANGE(IDC_IS_STAY_OUTSIDE_ACCOMPANY, OnSelchangeIsStayOutsideAccompany)
	ON_EN_CHANGE(IDC_HOW_MANY_DINNERS, OnChangeHowManyDinners)
	ON_EN_CHANGE(IDC_HOW_MANY_DINNERS_ACCOMPANY, OnChangeHowManyDinnersAccompany)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableDlg2001 message handlers

void CTableDlg2001::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CTableDlg2001::OnConfirm() 
{
	CString itemText;
	int itemValue;

	SAVE_DATA("E1", IDC_HOW_FAR);
	SAVE_DATA_COMBO("E2", IDC_BY_WHAT_VEHICLE);
	SAVE_DATA_COMBO("E3", IDC_HOW_LONG);
	SAVE_DATA("E4", IDC_FEE_FOR_VEHICLE);
	SAVE_DATA_COMBO("E5", IDC_IS_STAY_OUTSIDE);
	int iSel = m_IsStayOutside.GetCurSel();
	if( iSel != 2) //是
	{
		pInd->SetUnessaryData("E6", "E6");
	}
	else
	{
		SAVE_DATA("E6", IDC_FEE_FOR_STAY_OUTSIDE);
	}
	SAVE_DATA("E7", IDC_HOW_MANY_DINNERS);
	m_HowManyMealsCtrl.GetWindowText(itemText);
	itemValue = atoi(itemText);
	if (itemValue <= 0)
	{
		pInd->SetUnessaryData("E8", "E8");
	}else
	{
		SAVE_DATA("E8", IDC_FEE_FOR_DINNER);
	}

	SAVE_DATA_COMBO("E9", IDC_IS_ACCOMPANY);
	iSel = m_HasCompanyCtrl.GetCurSel();
	if( iSel != 2) //有
	{
		pInd->SetUnessaryData("E10", "E15");
	}
	else
	{
		SAVE_DATA("E10", IDC_HOW_MANY_ACCOMPANY);
		SAVE_DATA("E11", IDC_FEE_FOR_VEHICLE_ACCOMPANY);
		SAVE_DATA_COMBO("E12", IDC_IS_STAY_OUTSIDE_ACCOMPANY);
		if( m_IsCompanyStayOutSide.GetCurSel() == 1) //否
		{
			pInd->SetUnessaryData("E13", "E13");
		}
		else
		{
			SAVE_DATA("E13", IDC_FEE_FOR_STAY_OUTSIDE_ACCOMPANY);
		}	
		SAVE_DATA("E14", IDC_HOW_MANY_DINNERS_ACCOMPANY);
		m_HowManyMealsACtrl.GetWindowText(itemText);
		itemValue = atoi(itemText);
		if (itemValue <= 0)
		{
			pInd->SetUnessaryData("E15", "E15");
		}else
		{
			SAVE_DATA("E15", IDC_FEE_FOR_DINNER_ACCOMPANY);
		}
	}
	SAVE_DATA("E16", IDC_DOCTOER_NAME);
	SAVE_DATA_DATE("E17", IDC_FILLING_DATE);
	CDialog::OnOK();
}

void CTableDlg2001::OnOK() 
{
	return;	
	CDialog::OnOK();
}

BOOL CTableDlg2001::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_DoctorName.InitEdit(DATA_TYPE_BUTT, 20, "");
	m_FeeForMealCtrl.InitEdit(DATA_TYPE_MONEY, 9, "");
	m_FeeForMealsACtrl.InitEdit(DATA_TYPE_MONEY, 9, "");
	m_FeeForStayOutsideCtrl.InitEdit(DATA_TYPE_MONEY, 9, "");
	m_FeeForStayOutSideACtrl.InitEdit(DATA_TYPE_MONEY, 9, "");
	m_FeeForVehicleCtrl.InitEdit(DATA_TYPE_MONEY, 9, "");
	m_FeeForVehicleACtrl.InitEdit(DATA_TYPE_MONEY, 9, "");
	m_HowManyAccomanyCtrl.InitEdit(DATA_TYPE_NUMBER, 3, "");
	m_HowManyMealsCtrl.InitEdit(DATA_TYPE_NUMBER, 3, "");
	m_HowManyMealsACtrl.InitEdit(DATA_TYPE_NUMBER, 3, "");
	m_HowFarCtrl.InitEdit(DATA_TYPE_MONEY, 6, "");

	// TODO: Add extra initialization here
	TABLE_DLG_INIT();

	LOAD_DATA("E1", IDC_HOW_FAR);
	LOAD_DATA_COMBO("E2", IDC_BY_WHAT_VEHICLE);
	LOAD_DATA_COMBO("E3", IDC_HOW_LONG);
	LOAD_DATA("E4", IDC_FEE_FOR_VEHICLE);
	LOAD_DATA_COMBO("E5", IDC_IS_STAY_OUTSIDE);
	OnSelchangeIsStayOutside();
	LOAD_DATA("E6", IDC_FEE_FOR_STAY_OUTSIDE);
	LOAD_DATA("E7", IDC_HOW_MANY_DINNERS);
	OnChangeHowManyDinners();
	LOAD_DATA("E8", IDC_FEE_FOR_DINNER);
	LOAD_DATA_COMBO("E9", IDC_IS_ACCOMPANY);
	OnSelchangeIsAccompany();
	LOAD_DATA("E10", IDC_HOW_MANY_ACCOMPANY);
	LOAD_DATA("E11", IDC_FEE_FOR_VEHICLE_ACCOMPANY);
	LOAD_DATA_COMBO("E12", IDC_IS_STAY_OUTSIDE_ACCOMPANY);
	LOAD_DATA("E13", IDC_FEE_FOR_STAY_OUTSIDE_ACCOMPANY);
	OnSelchangeIsStayOutsideAccompany();
	LOAD_DATA("E14", IDC_HOW_MANY_DINNERS_ACCOMPANY);
	OnChangeHowManyDinnersAccompany();
	LOAD_DATA("E15", IDC_FEE_FOR_DINNER_ACCOMPANY);
	LOAD_DATA("E16", IDC_DOCTOER_NAME);
	LOAD_DATA_DATE("E17", IDC_FILLING_DATE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTableDlg2001::OnSelchangeIsStayOutside() 
{
	int iSel = m_IsStayOutside.GetCurSel();
	if( iSel != 2) //是
	{
		GetDlgItem(IDC_FEE_FOR_STAY_OUTSIDE)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_FEE_FOR_STAY_OUTSIDE)->EnableWindow(TRUE);
	}
}

void CTableDlg2001::OnSelchangeIsAccompany() 
{
	int iSel = m_HasCompanyCtrl.GetCurSel();
	if( iSel != 2) //有
	{
		GetDlgItem(IDC_HOW_MANY_ACCOMPANY)->EnableWindow(FALSE);
		GetDlgItem(IDC_FEE_FOR_VEHICLE_ACCOMPANY)->EnableWindow(FALSE);
		GetDlgItem(IDC_IS_STAY_OUTSIDE_ACCOMPANY)->EnableWindow(FALSE);
		GetDlgItem(IDC_FEE_FOR_STAY_OUTSIDE_ACCOMPANY)->EnableWindow(FALSE);
		GetDlgItem(IDC_HOW_MANY_DINNERS_ACCOMPANY)->EnableWindow(FALSE);
		GetDlgItem(IDC_FEE_FOR_DINNER_ACCOMPANY)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_HOW_MANY_ACCOMPANY)->EnableWindow(TRUE);
		GetDlgItem(IDC_FEE_FOR_VEHICLE_ACCOMPANY)->EnableWindow(TRUE);
		GetDlgItem(IDC_IS_STAY_OUTSIDE_ACCOMPANY)->EnableWindow(TRUE);
		GetDlgItem(IDC_FEE_FOR_STAY_OUTSIDE_ACCOMPANY)->EnableWindow(TRUE);
		GetDlgItem(IDC_HOW_MANY_DINNERS_ACCOMPANY)->EnableWindow(TRUE);
		OnChangeHowManyDinnersAccompany();
		//GetDlgItem(IDC_FEE_FOR_DINNER_ACCOMPANY)->EnableWindow(TRUE);
	}	
}

void CTableDlg2001::OnSelchangeIsStayOutsideAccompany() 
{
	int iSel = m_IsCompanyStayOutSide.GetCurSel();
	if( iSel != 2) //是
	{
		GetDlgItem(IDC_FEE_FOR_STAY_OUTSIDE_ACCOMPANY)->SetWindowText("");
		GetDlgItem(IDC_FEE_FOR_STAY_OUTSIDE_ACCOMPANY)->EnableWindow(FALSE);
	}
	else
	{
		if( m_HasCompanyCtrl.GetCurSel() == 2)
		{
			GetDlgItem(IDC_FEE_FOR_STAY_OUTSIDE_ACCOMPANY)->EnableWindow(TRUE);
		}
	}	
}

void CTableDlg2001::OnChangeHowManyDinners() 
{
	CString itemText;
	int itemValue;
	m_HowManyMealsCtrl.GetWindowText(itemText);
	itemValue = atoi(itemText);
	if (itemValue <= 0)
	{
		m_FeeForMealCtrl.EnableWindow(FALSE);
	}else
	{
		m_FeeForMealCtrl.EnableWindow(TRUE);
	}
}

void CTableDlg2001::OnChangeHowManyDinnersAccompany() 
{
	CString itemText;
	int itemValue;
	m_HowManyMealsACtrl.GetWindowText(itemText);
	itemValue = atoi(itemText);
	if (itemValue <= 0)
	{
		m_FeeForMealsACtrl.EnableWindow(FALSE);
	}else
	{
		m_FeeForMealsACtrl.EnableWindow(TRUE);
	}
}
