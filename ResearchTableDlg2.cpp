// ResearchTableDlg2.cpp : implementation file
//

#include "stdafx.h"
#include "TUI.h"
#include "ResearchTableDlg2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResearchTableDlg2 dialog


CResearchTableDlg2::CResearchTableDlg2(CWnd* pParent /*=NULL*/)
	: CDialog(CResearchTableDlg2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResearchTableDlg2)
	//}}AFX_DATA_INIT
}


void CResearchTableDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResearchTableDlg2)
	DDX_Control(pDX, IDC_IS_BLOOD_TAKEN, m_IsBloodTaken);
	DDX_Control(pDX, IDC_IS_QUESTIONAIR_FINISHED, m_IsFinished);
	DDX_Control(pDX, IDC_IS_ACKED, m_IsAcked);
	DDX_Control(pDX, IDC_BLOOD_ML, m_BloodCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResearchTableDlg2, CDialog)
	//{{AFX_MSG_MAP(CResearchTableDlg2)
	ON_BN_CLICKED(IDC_CONFIRM, OnConfirm)
	ON_CBN_SELCHANGE(IDC_IS_ACKED, OnSelchangeIsAcked)
	ON_CBN_SELCHANGE(IDC_IS_QUESTIONAIR_FINISHED, OnSelchangeIsQuestionairFinished)
	ON_CBN_SELCHANGE(IDC_IS_BLOOD_TAKEN, OnSelchangeIsBloodTaken)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResearchTableDlg2 message handlers

void CResearchTableDlg2::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CResearchTableDlg2::OnOK() 
{
	// TODO: Add extra validation here
	return;	
	CDialog::OnOK();
}

void CResearchTableDlg2::OnConfirm() 
{
	SAVE_DATA_COMBO("H15", IDC_IS_ACKED);
	if( m_IsAcked.GetCurSel() == 2) //是
	{
		SAVE_DATA_COMBO("H16", IDC_IS_QUESTIONAIR_FINISHED);
		if (m_IsFinished.GetCurSel() == 2)
		{
			SAVE_DATA_DATE("H17", IDC_FINISHED_DATE);
			SAVE_DATA_COMBO("H18", IDC_IS_QUESTIONAIR_COMPLETE);
		}
		else
		{
			pInd->SetUnessaryData("H17", "H18");
		}
		SAVE_DATA_COMBO("H19", IDC_IS_BLOOD_TAKEN);
		if (m_IsBloodTaken.GetCurSel() == 2)
		{
			SAVE_DATA_DATE("H20", IDC_BLOOD_TAKEN_DATE);
			SAVE_DATA_COMBO("H21", IDC_BLOOD_TAKEN_NO);
			SAVE_DATA("H22", IDC_BLOOD_ML);
			SAVE_DATA_COMBO("H23", IDC_IS_RESERVED_20);
		}
		else
		{
			pInd->SetUnessaryData("H20", "H23");
		}
	}
	else
	{
		pInd->SetUnessaryData("H16", "H23");
	}
	CDialog::OnOK();
}

BOOL CResearchTableDlg2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	TABLE_DLG_INIT();
	m_BloodCtrl.InitEdit(DATA_TYPE_NUMBER, 6, "");
	
	LOAD_DATA_COMBO("H15", IDC_IS_ACKED);
	OnSelchangeIsAcked();
	LOAD_DATA_COMBO("H16", IDC_IS_QUESTIONAIR_FINISHED);
	OnSelchangeIsQuestionairFinished();
	LOAD_DATA_DATE("H17", IDC_FINISHED_DATE);
	LOAD_DATA_COMBO("H18", IDC_IS_QUESTIONAIR_COMPLETE);
	LOAD_DATA_COMBO("H19", IDC_IS_BLOOD_TAKEN);
	OnSelchangeIsBloodTaken();
	LOAD_DATA_DATE("H20", IDC_BLOOD_TAKEN_DATE);
	LOAD_DATA_COMBO("H21", IDC_BLOOD_TAKEN_NO);
	LOAD_DATA("H22", IDC_BLOOD_ML);
	LOAD_DATA_COMBO("H23", IDC_IS_RESERVED_20);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CResearchTableDlg2::OnSelchangeIsAcked() 
{
	int iSel = m_IsAcked.GetCurSel();
	if( iSel != 2) //是
	{
		GetDlgItem(IDC_IS_QUESTIONAIR_FINISHED)->EnableWindow(FALSE);
		GetDlgItem(IDC_FINISHED_DATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_IS_QUESTIONAIR_COMPLETE)->EnableWindow(FALSE);
		GetDlgItem(IDC_IS_BLOOD_TAKEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_BLOOD_TAKEN_DATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BLOOD_TAKEN_NO)->EnableWindow(FALSE);
		GetDlgItem(IDC_BLOOD_ML)->EnableWindow(FALSE);
		GetDlgItem(IDC_IS_RESERVED_20)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_IS_QUESTIONAIR_FINISHED)->EnableWindow(TRUE);
		if (m_IsFinished.GetCurSel() == 2)
		{
			GetDlgItem(IDC_FINISHED_DATE)->EnableWindow(TRUE);
			GetDlgItem(IDC_IS_QUESTIONAIR_COMPLETE)->EnableWindow(TRUE);
		}
		GetDlgItem(IDC_IS_BLOOD_TAKEN)->EnableWindow(TRUE);
		if (m_IsBloodTaken.GetCurSel() == 2)
		{
			GetDlgItem(IDC_BLOOD_TAKEN_DATE)->EnableWindow(TRUE);
			GetDlgItem(IDC_BLOOD_TAKEN_NO)->EnableWindow(TRUE);
			GetDlgItem(IDC_BLOOD_ML)->EnableWindow(TRUE);
			GetDlgItem(IDC_IS_RESERVED_20)->EnableWindow(TRUE);
		}
	}
	
}

void CResearchTableDlg2::OnSelchangeIsQuestionairFinished() 
{
	int iSel = m_IsFinished.GetCurSel();
	if( iSel != 2) //是
	{
		GetDlgItem(IDC_FINISHED_DATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_IS_QUESTIONAIR_COMPLETE)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_FINISHED_DATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_IS_QUESTIONAIR_COMPLETE)->EnableWindow(TRUE);
	}	
}

void CResearchTableDlg2::OnSelchangeIsBloodTaken() 
{
	int iSel = m_IsBloodTaken.GetCurSel();
	if( iSel != 2) //是
	{
		GetDlgItem(IDC_BLOOD_TAKEN_DATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BLOOD_TAKEN_NO)->EnableWindow(FALSE);
		GetDlgItem(IDC_BLOOD_ML)->EnableWindow(FALSE);
		GetDlgItem(IDC_IS_RESERVED_20)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_BLOOD_TAKEN_DATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BLOOD_TAKEN_NO)->EnableWindow(TRUE);
		GetDlgItem(IDC_BLOOD_ML)->EnableWindow(TRUE);
		GetDlgItem(IDC_IS_RESERVED_20)->EnableWindow(TRUE);
	}
}
