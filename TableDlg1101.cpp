// Table1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "TUI.h"
#include "TableDlg1101.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1101 dialog


CTableDlg1101::CTableDlg1101(CWnd* pParent /*=NULL*/)
	: CDialog(CTableDlg1101::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTableDlg1101)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTableDlg1101::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTableDlg1101)
	DDX_Control(pDX, IDC_AGE, m_AgeCtrl);
	DDX_Control(pDX, IDC_BORN_ADDRESS, m_BornAddressCtrl);
	DDX_Control(pDX, IDC_ADDRESS, m_CurrentAddressCtrl);
	DDX_Control(pDX, IDC_CONTACT_INFO, m_ContactInfoCtrl);
	DDX_Control(pDX, IDC_NAME, m_NameCtrl);
	DDX_Control(pDX, IDC_REGISTER_ID, m_RegisterNoCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTableDlg1101, CDialog)
	//{{AFX_MSG_MAP(CTableDlg1101)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CONFIRM, OnConfirm)
	ON_CBN_SETFOCUS(IDC_SEX_COMBO, OnSetfocusSexCombo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1101 message handlers

void CTableDlg1101::OnOK() 
{
	return;
	CDialog::OnOK();
}

void CTableDlg1101::OnCancel() 
{

	CDialog::OnCancel();
}


void CTableDlg1101::OnConfirm() 
{
	//Check A18: 报告日期不应早于涂片日期
	CHECK_REPORT_DATE(IDC_SAMPLE_DATE,IDC_SAMPLE_REPORT_DATE,"“涂片报告日期”不应早于“涂片日期”");
	
//	SAVE_DATA("A1", IDC_ID);
	SAVE_DATA("A2", IDC_REGISTER_ID);
	SAVE_DATA("A3", IDC_NAME);
	SAVE_DATA_COMBO("A4", IDC_SEX_COMBO);
	SAVE_DATA("A5", IDC_AGE);
	SAVE_DATA("A6", IDC_CONTACT_INFO);
	SAVE_DATA("A7", IDC_ADDRESS);
	SAVE_DATA("A8", IDC_BORN_ADDRESS);
	SAVE_DATA_DATE("A9", IDC_DIANOSTIC_DATE);
	SAVE_DATA_DATE("A10", IDC_REGISTER_DATE);
	SAVE_DATA_DATE("A11", IDC_PHLEGM_DATE);
	SAVE_DATA_DATE("A12", IDC_CURL_START_DATE);
	//A12“开始一线药治疗日期”为可选项
	if (pInd->GetItem("A12") == "")
	{
		pInd->itemStatus[CIndividual::GetItemIndex("A12")] = 2;
	}
	SAVE_DATA_COMBO("A13", IDC_SCREEN_OBJECT);
	SAVE_DATA_COMBO("A14", IDC_CURE_CATEGORY);
	SAVE_DATA_COMBO("A15", IDC_REGISTER_CATEGORY);
	SAVE_DATA_COMBO("A16", IDC_MEDCINE_HISTORY_CATEGORY);
	SAVE_DATA_DATE("A17", IDC_SAMPLE_DATE);
	SAVE_DATA_DATE("A18", IDC_SAMPLE_REPORT_DATE);
	SAVE_DATA_COMBO("A19", IDC_SAMPLE_RESULT);

	CDialog::OnOK();
}

BOOL CTableDlg1101::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	TABLE_DLG_INIT();

	//Init Edit
	m_AgeCtrl.InitEdit(DATA_TYPE_AGE, 5, "");
	m_ContactInfoCtrl.InitEdit(DATA_TYPE_BUTT, 200, "");
	m_CurrentAddressCtrl.InitEdit(DATA_TYPE_BUTT, 200, "");
	m_BornAddressCtrl.InitEdit(DATA_TYPE_BUTT, 200, "");

	//LoadData
//	LOAD_DATA("A1", IDC_ID);
	SetDlgItemText(IDC_ID, pInd->LoadData("A1")+"（创建于："+pInd->createDate+"）");

	LOAD_DATA("A2", IDC_REGISTER_ID);
	LOAD_DATA("A3", IDC_NAME);
	LOAD_DATA_COMBO("A4", IDC_SEX_COMBO);
	LOAD_DATA("A5", IDC_AGE);
	LOAD_DATA("A6", IDC_CONTACT_INFO);
	LOAD_DATA("A7", IDC_ADDRESS);
	LOAD_DATA("A8", IDC_BORN_ADDRESS);
	LOAD_DATA_DATE("A9", IDC_DIANOSTIC_DATE);
	LOAD_DATA_DATE("A10", IDC_REGISTER_DATE);
	LOAD_DATA_DATE("A11", IDC_PHLEGM_DATE);
	LOAD_DATA_DATE("A12", IDC_CURL_START_DATE);
	LOAD_DATA_COMBO("A13", IDC_SCREEN_OBJECT);
	LOAD_DATA_COMBO("A14", IDC_CURE_CATEGORY);
	LOAD_DATA_COMBO("A15", IDC_REGISTER_CATEGORY);
	LOAD_DATA_COMBO("A16", IDC_MEDCINE_HISTORY_CATEGORY);
	LOAD_DATA_DATE("A17", IDC_SAMPLE_DATE);
	LOAD_DATA_DATE("A18", IDC_SAMPLE_REPORT_DATE);
	LOAD_DATA_COMBO("A19", IDC_SAMPLE_RESULT);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTableDlg1101::GotoNextInput(CWnd* pCurWnd)
{
	CWnd *pWnd;
	pWnd = GetNextDlgTabItem(pCurWnd);
	pWnd->SetFocus();
}

HBRUSH CTableDlg1101::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	int id = pWnd->GetDlgCtrlID();
	
	if( ( id == IDC_ID ) )
	{
		pDC->SetTextColor(RGB(0,0,255));
#if 0
		CFont font;
		font.CreateFont(
			12,                        // nHeight
			0,                         // nWidth
			0,                         // nEscapement
			0,                         // nOrientation
			FW_BOLD,                 // nWeight
			FALSE,                     // bItalic
			FALSE,                     // bUnderline
			0,                         // cStrikeOut
			ANSI_CHARSET,              // nCharSet
			OUT_DEFAULT_PRECIS,        // nOutPrecision
			CLIP_DEFAULT_PRECIS,       // nClipPrecision
			DEFAULT_QUALITY,           // nQuality
			DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
			"宋体");                 // lpszFacename
		pWnd->SetFont(&font, FALSE);
#endif
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}


void CTableDlg1101::OnSetfocusSexCombo() 
{
//	m_SexCtrl.ShowDropDown(TRUE);	
}
