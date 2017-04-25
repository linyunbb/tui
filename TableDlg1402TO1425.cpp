// TableDlg1402TO1425.cpp : implementation file
//

#include "stdafx.h"
#include "TUI.h"
#include "TableDlg1402TO1425.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1402TO1425 dialog


CTableDlg1402TO1425::CTableDlg1402TO1425(CWnd* pParent /*=NULL*/)
	: CDialog(CTableDlg1402TO1425::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTableDlg1402TO1425)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTableDlg1402TO1425::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTableDlg1402TO1425)
	DDX_Control(pDX, IDC_IS_IN_HOSPITAL, m_IsInHospitalCtrl);
	DDX_Control(pDX, IDC_OTHER_MEDICINE, m_TakeOthersCtrl);
	DDX_Control(pDX, IDC_WEIGHT, m_WeightCtrl);
	DDX_Control(pDX, IDC_IN_HOSPITAL_DAY, m_InHispitalDaysCtrl);
	DDX_Control(pDX, IDC_IS_PROJECT_CHANGED, m_IsProjectChangedCtrl);
	DDX_Control(pDX, IDC_ABNORMAL_TYPE, m_AbnormalCategoryCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTableDlg1402TO1425, CDialog)
	//{{AFX_MSG_MAP(CTableDlg1402TO1425)
	ON_BN_CLICKED(IDC_CONFIRM, OnConfirm)
	ON_CBN_SELCHANGE(IDC_ABNORMAL_TYPE, OnSelchangeAbnormalType)
	ON_CBN_SELCHANGE(IDC_IS_PROJECT_CHANGED, OnSelchangeIsProjectChanged)
	ON_CBN_SELCHANGE(IDC_IS_IN_HOSPITAL, OnSelchangeIsInHospital)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1402TO1425 message handlers

void CTableDlg1402TO1425::OnOK() 
{
	return;
	CDialog::OnOK();
}


void CTableDlg1402TO1425::OnConfirm() 
{
	// TODO: Add extra validation here
	int i=0;
	SAVE_DATA_COMBO(items[i++], IDC_SAMPLE_RESULT);
	SAVE_DATA_COMBO(items[i++], IDC_CULTIVATE_RESULT);
	SAVE_DATA_COMBO(items[i++], IDC_IS_IN_HOSPITAL);
	if( m_IsInHospitalCtrl.GetCurSel() != 2 )
	{
		pInd->SetUnessaryData(items[3], items[3]);
		i = i+1;
	}
	else
	{
		SAVE_DATA(items[i++], IDC_IN_HOSPITAL_DAY);
	}

	SAVE_DATA(items[i++], IDC_WEIGHT);
	SAVE_DATA_COMBO(items[i++], IDC_ABNORMAL_TYPE);
	int iSel = m_AbnormalCategoryCtrl.GetCurSel();
	if( iSel <=0 || iSel == 1) //无不良反应
	{
		pInd->SetUnessaryData(items[6], items[8]);
		i = i+3;
	}
	else
	{
		SAVE_DATA_COMBO(items[i++], IDC_ABNORMAL_LEVEL);
		SAVE_DATA_DATE(items[i++], IDC_ABNORMAL_DATE);
		SAVE_DATA_COMBO(items[i++], IDC_IMPACT);
	}
	SAVE_DATA_COMBO(items[i++], IDC_IS_PROJECT_CHANGED);
	iSel = m_IsProjectChangedCtrl.GetCurSel();
	if( iSel != 2 )//更改方案
	{
		pInd->SetUnessaryData(items[10], items[11]);
		i = i+2;
	}
	else
	{
		SAVE_DATA_DATE(items[i++], IDC_PROJECT_CHANGED_DATE);
		SAVE_DATA(items[i++], IDC_CHANGED_PROJECT);
	}
	pInd->CheckAllTableItems();
	SAVE_DATA_COMBO(items[i++], IDC_Z_YESNO);
	SAVE_DATA_COMBO(items[i++], IDC_E_YESNO);
	SAVE_DATA_COMBO(items[i++], IDC_KM_YESNO);
	SAVE_DATA_COMBO(items[i++], IDC_AM_YESNO);
	SAVE_DATA_COMBO(items[i++], IDC_CM_YESNO);
	SAVE_DATA_COMBO(items[i++], IDC_OFX_YESN);
	SAVE_DATA_COMBO(items[i++], IDC_LFX_YESNO);
	SAVE_DATA_COMBO(items[i++], IDC_MFX_YESNO);
	SAVE_DATA_COMBO(items[i++], IDC_PTO_YESNO);
	SAVE_DATA_COMBO(items[i++], IDC_CS_YESNO);
	SAVE_DATA_COMBO(items[i++], IDC_PAS_YESNO);
	SAVE_DATA(items[i++], IDC_OTHER_MEDICINE);
	//“领取的其他药物”是可选项
	if (pInd->GetItem(items[i-1]) == "") 
		pInd->itemStatus[CIndividual::GetItemIndex(items[i-1])] = 2;
	CDialog::OnOK();
}

void CTableDlg1402TO1425::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CTableDlg1402TO1425::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_InHispitalDaysCtrl.InitEdit(DATA_TYPE_NUMBER, 5, "");
	m_WeightCtrl.InitEdit(DATA_TYPE_NUMBER, 3, "");
	m_TakeOthersCtrl.InitEdit(DATA_TYPE_BUTT, 50, "");

	for(int i=0; i<24; i++)
	{
		items[i].Format("D%d", (m_Month-1)*24+3+i);
	}

	pInd = (CIndividual*)CData::GetData(g_CurIId);
	ASSERT(pInd);
	g_WndText.Format("第%d个月治疗情况", m_Month);
	SetWindowText(pInd->GetWndText()+g_WndText);
	
	i=0;
	LOAD_DATA_COMBO(items[i++], IDC_SAMPLE_RESULT);
	LOAD_DATA_COMBO(items[i++], IDC_CULTIVATE_RESULT);
	LOAD_DATA_COMBO(items[i++], IDC_IS_IN_HOSPITAL);
	OnSelchangeIsInHospital();
	LOAD_DATA(items[i++], IDC_IN_HOSPITAL_DAY);
	LOAD_DATA(items[i++], IDC_WEIGHT);
	LOAD_DATA_COMBO(items[i++], IDC_ABNORMAL_TYPE);
	OnSelchangeAbnormalType();
	LOAD_DATA_COMBO(items[i++], IDC_ABNORMAL_LEVEL);
	LOAD_DATA_DATE(items[i++], IDC_ABNORMAL_DATE);
	LOAD_DATA_COMBO(items[i++], IDC_IMPACT);
	LOAD_DATA_COMBO(items[i++], IDC_IS_PROJECT_CHANGED);
	OnSelchangeIsProjectChanged();
	LOAD_DATA_DATE(items[i++], IDC_PROJECT_CHANGED_DATE);
	LOAD_DATA(items[i++], IDC_CHANGED_PROJECT);

	LOAD_DATA_COMBO(items[i++], IDC_Z_YESNO);
	LOAD_DATA_COMBO(items[i++], IDC_E_YESNO);
	LOAD_DATA_COMBO(items[i++], IDC_KM_YESNO);
	LOAD_DATA_COMBO(items[i++], IDC_AM_YESNO);
	LOAD_DATA_COMBO(items[i++], IDC_CM_YESNO);
	LOAD_DATA_COMBO(items[i++], IDC_OFX_YESN);
	LOAD_DATA_COMBO(items[i++], IDC_LFX_YESNO);
	LOAD_DATA_COMBO(items[i++], IDC_MFX_YESNO);
	LOAD_DATA_COMBO(items[i++], IDC_PTO_YESNO);
	LOAD_DATA_COMBO(items[i++], IDC_CS_YESNO);
	LOAD_DATA_COMBO(items[i++], IDC_PAS_YESNO);
	LOAD_DATA(items[i++], IDC_OTHER_MEDICINE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTableDlg1402TO1425::OnSelchangeAbnormalType() 
{
	int iSel = m_AbnormalCategoryCtrl.GetCurSel();
	if( iSel <=0 || iSel == 1) //无不良反应
	{
		GetDlgItem(IDC_ABNORMAL_LEVEL)->EnableWindow(FALSE);
		GetDlgItem(IDC_ABNORMAL_DATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_IMPACT)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_ABNORMAL_LEVEL)->EnableWindow(TRUE);
		GetDlgItem(IDC_ABNORMAL_DATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_IMPACT)->EnableWindow(TRUE);
	}
}

void CTableDlg1402TO1425::OnSelchangeIsProjectChanged() 
{
	int iSel = m_IsProjectChangedCtrl.GetCurSel();
	if( iSel != 2 )//更改方案
	{
		GetDlgItem(IDC_PROJECT_CHANGED_DATE)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHANGED_PROJECT)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_PROJECT_CHANGED_DATE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHANGED_PROJECT)->EnableWindow(TRUE);
	}
}

void CTableDlg1402TO1425::OnSelchangeIsInHospital()
{
	int iSel = m_IsInHospitalCtrl.GetCurSel();
	if( iSel != 2 )//非是
	{
		GetDlgItem(IDC_IN_HOSPITAL_DAY)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_IN_HOSPITAL_DAY)->EnableWindow(TRUE);
	}	
}
