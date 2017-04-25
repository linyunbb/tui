// TableDlg1301.cpp : implementation file
//

#include "stdafx.h"
#include "TUI.h"
#include "TableDlg1301.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1301 dialog


CTableDlg1301::CTableDlg1301(CWnd* pParent /*=NULL*/)
	: CDialog(CTableDlg1301::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTableDlg1301)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTableDlg1301::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTableDlg1301)
	DDX_Control(pDX, IDC_IS_BLOOD_TAKEN, m_IsBloodTakenCtrl);
	DDX_Control(pDX, IDC_INSTITUTION_LEVEL, m_InstitutionLevelCtrl);
	DDX_Control(pDX, IDC_IS_QUESTIONAIR_FINISHED, m_IsFinishedCtrl);
	DDX_Control(pDX, IDC_IS_ACKED, m_IsAckedCtrl);
	DDX_Control(pDX, IDC_BLOOD_ML, m_BloodMLCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTableDlg1301, CDialog)
	//{{AFX_MSG_MAP(CTableDlg1301)
	ON_CBN_SELCHANGE(IDC_IS_ACKED, OnSelchangeIsAcked)
	ON_CBN_SELCHANGE(IDC_IS_QUESTIONAIR_FINISHED, OnSelchangeIsQuestionairFinished)
	ON_CBN_SELCHANGE(IDC_INSTITUTION_LEVEL, OnSelchangeInstitutionLevel)
	ON_CBN_SELCHANGE(IDC_IS_BLOOD_TAKEN, OnSelchangeIsBloodTaken)
	ON_BN_CLICKED(IDC_CONFIRM, OnConfirm)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1301 message handlers

void CTableDlg1301::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CTableDlg1301::OnOK() 
{
	// TODO: Add your control notification handler code here
	return;	
}
	
void CTableDlg1301::OnConfirm() 
{
	//该表所有信息都应该有
	SAVE_DATA_COMBO("C1", IDC_IS_ACKED);
	int iSel = m_IsAckedCtrl.GetCurSel();
	if( iSel != 2) //非"是", C2-C9 DISABLED
	{
		pInd->SaveDataToEmpty("C2", "C9");
	}
	else
	{
		SAVE_DATA_COMBO("C2", IDC_IS_QUESTIONAIR_FINISHED);
		if(m_IsFinishedCtrl.GetCurSel() == 2)
		{
			SAVE_DATA_DATE("C3", IDC_FINISHED_DATE);
			SAVE_DATA_COMBO("C4", IDC_IS_QUESTIONAIR_COMPLETE);
		}
		else
		{
			pInd->SaveDataToEmpty("C3", "C4");
		}
		SAVE_DATA_COMBO("C5", IDC_IS_BLOOD_TAKEN);
		if( m_IsBloodTakenCtrl.GetCurSel() == 2)
		{
			SAVE_DATA_DATE("C6", IDC_BLOOD_TAKEN_DATE);
			SAVE_DATA_COMBO("C7", IDC_BLOOD_TAKEN_NO);
			SAVE_DATA("C8", IDC_BLOOD_ML);
			SAVE_DATA_COMBO("C9", IDC_IS_RESERVED_20);
		}
		else
		{
			pInd->SaveDataToEmpty("C6", "C9");
		}
	}
	SAVE_DATA_COMBO("C10", IDC_INSTITUTION_LEVEL);
	iSel = m_InstitutionLevelCtrl.GetCurSel();
	if( iSel != 1)//省级
	{
		pInd->SetUnessaryData("C16", "C19");
	}
	else
	{
		pInd->SetNessaryData("C16", "C19");
	}
	SAVE_DATA_COMBO("C11", IDC_IS_RESERVED_4);
	CDialog::OnOK();
}

BOOL CTableDlg1301::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	TABLE_DLG_INIT();
	m_BloodMLCtrl.InitEdit(DATA_TYPE_NUMBER, 6, "");

	LOAD_DATA_COMBO("C1", IDC_IS_ACKED);
	OnSelchangeIsAcked();
	LOAD_DATA_COMBO("C2", IDC_IS_QUESTIONAIR_FINISHED);
	OnSelchangeIsQuestionairFinished();
	LOAD_DATA_DATE("C3", IDC_FINISHED_DATE);
	LOAD_DATA_COMBO("C4", IDC_IS_QUESTIONAIR_COMPLETE);
	LOAD_DATA_COMBO("C5", IDC_IS_BLOOD_TAKEN);
	OnSelchangeIsBloodTaken();
	LOAD_DATA_DATE("C6", IDC_BLOOD_TAKEN_DATE);
	LOAD_DATA_COMBO("C7", IDC_BLOOD_TAKEN_NO);
	LOAD_DATA("C8", IDC_BLOOD_ML);
	LOAD_DATA_COMBO("C9", IDC_IS_RESERVED_20);
	LOAD_DATA_COMBO("C10", IDC_INSTITUTION_LEVEL);
	LOAD_DATA_COMBO("C11", IDC_IS_RESERVED_4);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTableDlg1301::OnSelchangeIsAcked() 
{
	int iSel = m_IsAckedCtrl.GetCurSel();
	if( iSel != 2) //非"是", C2-C9 DISABLED
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

		if(m_IsFinishedCtrl.GetCurSel() == 2)
		{
			GetDlgItem(IDC_FINISHED_DATE)->EnableWindow(TRUE);
			GetDlgItem(IDC_IS_QUESTIONAIR_COMPLETE)->EnableWindow(TRUE);
		}
		
		GetDlgItem(IDC_IS_BLOOD_TAKEN)->EnableWindow(TRUE);
		if(m_IsBloodTakenCtrl.GetCurSel() == 2)
		{
			GetDlgItem(IDC_BLOOD_TAKEN_DATE)->EnableWindow(TRUE);
			GetDlgItem(IDC_BLOOD_TAKEN_NO)->EnableWindow(TRUE);
			GetDlgItem(IDC_BLOOD_ML)->EnableWindow(TRUE);
			GetDlgItem(IDC_IS_RESERVED_20)->EnableWindow(TRUE);
		}
	}
}

void CTableDlg1301::OnSelchangeIsQuestionairFinished() 
{
	int iSel = m_IsFinishedCtrl.GetCurSel();
	if( iSel != 2) //非"是", C3-C4 DISABLED
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

void CTableDlg1301::OnSelchangeInstitutionLevel() 
{
}

void CTableDlg1301::OnSelchangeIsBloodTaken() 
{
	int iSel = m_IsBloodTakenCtrl.GetCurSel();
	if( iSel != 2) //非"是", C6-C9 DISABLED
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