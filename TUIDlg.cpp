// TUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TUI.h"
#include "TUIDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
#include "PatientInputDlg.h"
#include "ResearchInputDialog.h"
#include "SaveLoadDataDlg.h"

#include "TableDlg1101.h"
#include "TableDlg1102.h"

#include "TableDlg1201.h"
#include "TableDlg1202.h"
#include "TableDlg1203.h"
#include "TableDlg1204.h"
#include "TableDlg1205.h"
#include "TableDlg1206.h"

#include "TableDlg1301.h"
#include "TableDlg1302.h"
#include "TableDlg1303.h"

#include "TableDlg1401.h"
#include "TableDlg1402TO1425.h"
#include "TableDlg1426.h"

#include "TableDlg2001.h"
#include "TableDlg2200.h"
#include "TableDlg2300.h"

#include "ResearchTableDlg1.h"
#include "ResearchTableDlg2.h"
#include "ResearchTableDlg3.h"

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTUIDlg dialog

CTUIDlg::CTUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTUIDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTUIDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTUIDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTUIDlg, CDialog)
	//{{AFX_MSG_MAP(CTUIDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PATIENT_INPUT, OnPatientInput)
	ON_BN_CLICKED(IDC_HEALTH_INFO_BUTTON, OnHealthInfoButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTUIDlg message handlers

BOOL CTUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	InitGlobalData();
	SerializeFileInfo(FALSE); //load data

	CID sId(1);
	WORD wCode;
	UINT nLen;
	UINT nId = sId.GetId(TUI_ID_CITY_TYPE);
	nId = sId.GetId(TUI_ID_TOWN_TYPE);
	nId = sId.GetId(TUI_ID_IND_TYPE);
	
	CID sId2(1,23,456);
	nId = sId2.GetId(TUI_ID_CITY_TYPE);

	nId = sId2.GetId(TUI_ID_TOWN_TYPE);
	nId = sId2.GetId(TUI_ID_IND_TYPE);

	CID sId3(123);
	nId = sId3.GetId(TUI_ID_CITY_TYPE);
	wCode = sId3.GetCode(TUI_ID_CITY_TYPE);
	nLen = sId3.GetMaxCode(TUI_ID_CITY_TYPE);
	nId = sId3.GetId(TUI_ID_TOWN_TYPE);
	wCode = sId3.GetCode(TUI_ID_TOWN_TYPE); 
	nLen = sId3.GetMaxCode(TUI_ID_TOWN_TYPE);
	nId = sId3.GetId(TUI_ID_IND_TYPE);
	nLen = sId3.GetMaxCode(TUI_ID_IND_TYPE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTUIDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTUIDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTUIDlg::OnOK() 
{
	return;	
	CDialog::OnOK();
}

void CTUIDlg::OnCancel() 
{
	if( MessageBox("确定退出?","提示",MB_YESNO|MB_ICONQUESTION|MB_SYSTEMMODAL) == IDNO )
	{
		return;
	}
	SerializeFileInfo(TRUE);
	m_Data.DeleteAll();

	for(UINT i=0; i<gSectionNameSize; i++)
	{
		for(UINT j=0; j<gTableSize[i]; j++)
		{
			if (gTable[i][j].pDlg) delete gTable[i][j].pDlg;
			for(UINT k=0; k<gTable[i][j].subsize; k++)
			{
				if (gTable[i][j].sub[k].pDlg) delete gTable[i][j].sub[k].pDlg;
			}
		}
	}
	for(i=0; i<gResearchTableSize; i++)
	{
		if(gResearchTable[i].pDlg) delete gResearchTable[i].pDlg;
	}
	CDialog::OnCancel();
}

void CTUIDlg::OnPatientInput() 
{
	CPatientInputDlg dlg(m_Data);
	dlg.DoModal();
}

void CTUIDlg::InitGlobalData()
{
	//Append Town Id from code
	for(UINT i=0; i<gCTinfoSize; i++){
		for(UINT j=0; j<gCTinfo[i].townsize; j++){
			gCTinfo[i].pTown[j].id = CID(gCTinfo[i].id, gCTinfo[i].pTown[j].id, 0).GetId(TUI_ID_TOWN_TYPE);
		}
	}
	gTable[0][0].sub[0].pDlg = new CTableDlg1101;
	gTable[0][0].sub[1].pDlg = new CTableDlg1102;

	gTable[0][1].sub[0].pDlg = new CTableDlg1201;
	gTable[0][1].sub[0].checkFun = CheckTable1201;
	gTable[0][1].sub[1].pDlg = new CTableDlg1202;
	gTable[0][1].sub[1].checkFun = CheckTable1202;
	gTable[0][1].sub[2].pDlg = new CTableDlg1203;
	gTable[0][1].sub[2].checkFun = CheckTable1203;
	gTable[0][1].sub[3].pDlg = new CTableDlg1204;
	gTable[0][1].sub[3].checkFun = CheckTable1204;
	gTable[0][1].sub[4].pDlg = new CTableDlg1205;
	gTable[0][1].sub[4].checkFun = CheckTable1205;
	
	gTable[0][1].sub[5].pDlg = new CTableDlg1206;
	gTable[0][1].sub[5].checkFun = CheckTable1206;

	gTable[0][2].sub[0].pDlg = new CTableDlg1301;
	gTable[0][2].sub[0].checkFun = CheckTable1301;
	
	gTable[0][2].sub[1].pDlg = new CTableDlg1302;
	gTable[0][2].sub[1].checkFun = CheckTable1302;

	gTable[0][2].sub[2].pDlg = new CTableDlg1303;
	gTable[0][2].sub[2].checkFun = CheckTable1303;

	gTable[0][3].sub[0].pDlg = new CTableDlg1401;
	gTable[0][3].sub[0].checkFun = CheckTable1401;
	
	CTableDlg1402TO1425* pDlg =NULL;
	for(i=1; i<25; i++)
	{
		pDlg = new CTableDlg1402TO1425;
		pDlg->m_Month = i;
		gTable[0][3].sub[i].pDlg = pDlg;
		gTable[0][3].sub[i].checkFun = CheckTable1402_25;
	}
	gTable[0][3].sub[25].pDlg = new CTableDlg1426;
	gTable[0][3].sub[25].checkFun = CheckTable1426;


	gTable[1][0].pDlg = new CTableDlg2001;
	gTable[1][0].checkFun = CheckTable2100;

	gTable[1][1].pDlg = new CTableDlg2200;
	gTable[1][1].checkFun = CheckTable2200;

	gTable[1][2].pDlg = new CTableDlg2300;
	gTable[1][2].checkFun = CheckTable2300;

	gResearchTable[0].pDlg = new CResearchTableDlg1;
	gResearchTable[1].pDlg = new CResearchTableDlg2;
	gResearchTable[1].checkFun = CheckResearchTable2;
	gResearchTable[2].pDlg = new CResearchTableDlg3;
	gResearchTable[2].checkFun = CheckResearchTable3;
}

void CTUIDlg::SerializeFileInfo(BOOL isSaving)
{
	//Config Data
	CArchive *pAr;
	pAr = g_Tools.GetArchive(".\\config.tui", isSaving, FALSE);
	if (pAr)
	{
		m_Data.SerializeConfig(*pAr);
		g_Tools.CloseArchive();
	}
	//City&Town&Ind
	CSaveLoadDataDlg dlg(m_Data);
	dlg.isSaving = isSaving;
	dlg.DoModal();
}

void CTUIDlg::OnHealthInfoButton() 
{
	CResearchInputDialog dlg(m_Data);
	dlg.DoModal();
}
