// PatientInputDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TUI.h"
#include "PatientInputDlg.h"
#include "TableDlg1101.h"
#include "CSpreadSheet.h"
#include "DateConfirmDlg.h"
#include "StatsDialog.h"
#include "ImportDataDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPatientInputDlg dialog


CPatientInputDlg::CPatientInputDlg(CData &data, CWnd* pParent /*=NULL*/)
	: CDialog(CPatientInputDlg::IDD, pParent), m_Data(data)
{
	//{{AFX_DATA_INIT(CPatientInputDlg)
	//}}AFX_DATA_INIT
	m_pTableImageList = NULL;
	m_PatientSel = -1;
}


void CPatientInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPatientInputDlg)
	DDX_Control(pDX, IDC_STATIC_EXPORT, m_StaticExportCtrl);
	DDX_Control(pDX, IDC_EXPORT_PROGRESS, m_ExportProgressCtrl);
	DDX_Control(pDX, IDC_FILTER, m_FilterCtrl);
	DDX_Control(pDX, IDC_TABLE_LIST, m_TableListCtrl);
	DDX_Control(pDX, IDC_SUB_SECTION_TAB, m_SubSectionTabCtrl);
	DDX_Control(pDX, IDC_SECTION_TAB, m_SectionTabCtrl);
	DDX_Control(pDX, IDC_TOWN_SEL_COMBO, m_TownSelCtrl);
	DDX_Control(pDX, IDC_PATIENT_LIST, m_PatientListCtrl);
	DDX_Control(pDX, IDC_CITY_SEL_COMBO, m_CitySelCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPatientInputDlg, CDialog)
	//{{AFX_MSG_MAP(CPatientInputDlg)
	ON_BN_CLICKED(IDOK, OnOk)
	ON_WM_CANCELMODE()
	ON_NOTIFY(NM_DBLCLK, IDC_TABLE_LIST, OnDblclkTableList)
	ON_CBN_SELCHANGE(IDC_CITY_SEL_COMBO, OnSelchangeCitySelCombo)
	ON_NOTIFY(TCN_SELCHANGE, IDC_SECTION_TAB, OnSelchangeSectionTab)
	ON_BN_CLICKED(IDC_NEW_PATIENT, OnNewPatient)
	ON_NOTIFY(NM_CLICK, IDC_PATIENT_LIST, OnClickPatientList)
	ON_CBN_SELCHANGE(IDC_TOWN_SEL_COMBO, OnSelchangeTownSelCombo)
	ON_NOTIFY(TCN_SELCHANGE, IDC_SUB_SECTION_TAB, OnSelchangeSubSectionTab)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_DELETE_PATIENT, OnDeletePatient)
	ON_BN_CLICKED(IDC_EXPORT_DATA, OnExportData)
	ON_EN_CHANGE(IDC_FILTER, OnChangeFilter)
	ON_NOTIFY(NM_DBLCLK, IDC_PATIENT_LIST, OnDblclkPatientList)
	ON_BN_CLICKED(IDC_CHECK_STAT, OnCheckStat)
	ON_BN_CLICKED(IDC_IMPORT_DATA, OnImportData)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPatientInputDlg message handlers

void CPatientInputDlg::OnOk() 
{
	return;	
}

void CPatientInputDlg::OnCancel() 
{
	CIndividual* pInd = (CIndividual*)CData::GetData(g_CurIId);
	if(pInd != NULL)
	{
		pInd->UpdateStatus(FALSE);
	}
	g_CurIId = 0;
	CDialog::OnCancel();
}

BOOL CPatientInputDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	InitUI();
	m_CurDate = "";
	m_WndBottomOffset = 280;
	g_CurIId = 0;

	//Set Window Size and Position
	CenterWindow();
	GetWindowRect(orginalRect);
	CRect rect = orginalRect;
	rect.bottom -=m_WndBottomOffset;
	MoveWindow(rect);

	//Set Current City and Town Selection
    SetTimer(1, 50, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPatientInputDlg::OnCancelMode() 
{
	CDialog::OnCancelMode();
}

void CPatientInputDlg::InitUI()
{
	UINT i=0;
	//Add City Combo Items
	for(i=0; i<gCTinfoSize; i++)
	{
		m_CitySelCtrl.AddString(gCTinfo[i].name);
	}
	
	//Add Section Tab
	TCITEM tc;
	tc.mask=(TCIF_TEXT|TCIF_IMAGE);
	for(i=0; i<gSectionNameSize; i++)
	{
		tc.iImage=i;
		tc.pszText = gSectionName[i];
		m_SectionTabCtrl.InsertItem(i,&tc);
		m_SectionTabCtrl.caption.Add(gSectionName[i]);
	}

	m_pTableImageList = new CImageList();
	m_pTableImageList->Create(48, 48, ILC_COLORDDB, 9, 9);
	m_pTableImageList->SetBkColor(CLR_NONE);
	m_TableListCtrl.SetExtendedStyle(LVS_EX_TRACKSELECT|m_TableListCtrl.GetExtendedStyle());
	m_TableListCtrl.SetImageList(m_pTableImageList, LVSIL_NORMAL);
	m_pTableImageList->Add(AfxGetApp()->LoadIcon(IDI_TABLE_1));
	m_pTableImageList->Add(AfxGetApp()->LoadIcon(IDI_TABLE_LOCK));
	m_pTableImageList->Add(AfxGetApp()->LoadIcon(IDI_TABLE_FINISHED));

	m_pPatientImageList = new CImageList();
	m_pPatientImageList->Create(32, 32, ILC_COLORDDB, 8, 8);
	m_PatientListCtrl.SetImageList(m_pPatientImageList, LVSIL_NORMAL);
	//XYZ: X:finished, Y:selected, Z: ldy
	m_pPatientImageList->Add(AfxGetApp()->LoadIcon(IDI_PATIENT));					//000
	m_pPatientImageList->Add(AfxGetApp()->LoadIcon(IDI_LDY_PATIENT));				//001
	m_pPatientImageList->Add(AfxGetApp()->LoadIcon(IDI_PATIENT_SEL));				//010
	m_pPatientImageList->Add(AfxGetApp()->LoadIcon(IDI_LDY_PATIENT_SEL));			//011
	m_pPatientImageList->Add(AfxGetApp()->LoadIcon(IDI_PATIENT_FINISHED));			//100
	m_pPatientImageList->Add(AfxGetApp()->LoadIcon(IDI_LDY_PATIENT_FINISHED));		//101
	m_pPatientImageList->Add(AfxGetApp()->LoadIcon(IDI_PATIENT_FINISHED_SEL));		//110
	m_pPatientImageList->Add(AfxGetApp()->LoadIcon(IDI_LDY_PATIENT_FINISHED_SEL));	//111

	//LoadTableList(0);
}

void CPatientInputDlg::OnDblclkTableList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMLISTVIEW pNMListView = (NM_LISTVIEW *)pNMHDR;
	
	//是否点击了有效的项目。
    if (pNMListView->iItem == -1) return;

	CIndividual* pInd = (CIndividual*)CData::GetData(g_CurIId);
	CString oldName = pInd->name;
	CString itemText;

	TABLE_STRUCT* pTable = (TABLE_STRUCT*)m_TableListCtrl.GetItemData(pNMListView->iItem);
	CDialog* pDlg = pTable->pDlg;
	if (pDlg)
	{
		if(pTable->checkFun)
		{
			g_Month = pTable->param;
			if( !pTable->checkFun())
			{
				AfxMessageBox(g_LockReason);
				*pResult = 0;
				return;
			}
		}
		if( pDlg->DoModal() == IDCANCEL)
		{
			*pResult = 0;
			return;
		}

		//Name is modified
		if( pInd->name != oldName)
		{
			//Update Current Patient
			if( pInd->name == "")
			{
				itemText.Format("%d", CID(pInd->id).GetCode(TUI_ID_IND_TYPE));
			}else
			{
				itemText.Format("%d\n(", CID(pInd->id).GetCode(TUI_ID_IND_TYPE));
				itemText = itemText+pInd->name+")";
			}
			m_PatientListCtrl.SetItemText(m_PatientSel, 0, itemText);
		}

		UpdatePatient(m_PatientSel);

		//BBQ: TODO temp solution.
		int iSection = m_SectionTabCtrl.GetCurSel();
		int iSubSection = m_SubSectionTabCtrl.GetCurSel();
		if( iSection == 0)
		{
			LoadTableList(g_CurIId, iSection, iSubSection);
		}
		else if (iSection == 1)
		{
			LoadTableList(g_CurIId, iSection, 0);
		}
	}
	*pResult = 0;
}

void CPatientInputDlg::OnDblclkPatientList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if( g_CurIId == 0)
		return;
	CIndividual* pInd = (CIndividual*)CData::GetData(g_CurIId);
	CString oldName = pInd->name;
	CString itemText;

	gTable[0][0].sub[0].pDlg->DoModal();
	//Name is modified
	if( pInd->name != oldName)
	{
		//Update Current Patient
		if( pInd->name == "")
		{
			itemText.Format("%d", CID(pInd->id).GetCode(TUI_ID_IND_TYPE));
		}else
		{
			itemText.Format("%d\n(", CID(pInd->id).GetCode(TUI_ID_IND_TYPE));
			itemText = itemText+pInd->name+")";
		}
		m_PatientListCtrl.SetItemText(m_PatientSel, 0, itemText);
	}
	UpdatePatient(m_PatientSel);
	*pResult = 0;
}


BOOL CPatientInputDlg::DestroyWindow() 
{
	if (m_pTableImageList)
	{
		delete m_pTableImageList;
	}
	
	if (m_pPatientImageList)
	{
		delete m_pPatientImageList;
	}

	return CDialog::DestroyWindow();
}

void CPatientInputDlg::OnNewPatient() 
{
	BOOL bHasTownToAdd = FALSE;
	UINT iTId = 0;
	for(;;)
	{
		int nCity = m_CitySelCtrl.GetCurSel();
		if (nCity == -1) break;
		int nTown = m_TownSelCtrl.GetCurSel();
		if (nTown == -1) break;
		iTId = gCTinfo[nCity].pTown[nTown].id;
		
		CID sId(iTId);
		if(iTId % sId.GetMaxCode(TUI_ID_TOWN_TYPE) == 0) break;
		bHasTownToAdd = TRUE;
		break;
	}
	if (!bHasTownToAdd){
		AfxMessageBox("请选择所在城市和县区，再新建!");
		return;
	}
	
	UINT iId = CData::GetNewIndId(iTId);
	if (iId == 0){
		AfxMessageBox("该地区重大编号已使用完!");
		return;
	}

	if (m_CurDate.IsEmpty())
	{
		CDateConfirmDlg dateDlg;
		if (dateDlg.DoModal() == IDCANCEL) return;
		m_CurDate = dateDlg.GetInputDate();
	}

	//Set Filter to "" to Reload All Patients
	CString filter;
	m_FilterCtrl.GetWindowText(filter);
	if (!filter.IsEmpty())
	{
		m_FilterCtrl.SetWindowText("");
		OnChangeFilter();
	}

	//Add New One
	CIndividual* pInd = (CIndividual*)CData::CreateData(iId);
	ASSERT(pInd==CData::GetData(iId));
	g_CurIId = 0;
	//Check All Fucntions:
	pInd->CheckAllTableItems();

	//Update Patient name
	CString name;
	name.Format("%d", CID(iId).GetCode(TUI_ID_IND_TYPE));
	int curPos = m_PatientListCtrl.GetItemCount();
	m_PatientListCtrl.InsertItem(curPos, name, 0);
	m_PatientListCtrl.SetItemData(curPos, iId);
	pInd->createDate = m_CurDate;

	//UpdateWindowRect(-1);
	ClickOnePatient(curPos);
	m_PatientListCtrl.EnsureVisible(curPos, FALSE);

	//Update Total
	CString itemText;
	int nTotal = m_PatientListCtrl.GetItemCount();
	itemText.Format("患者登记列表：(总数%d)", nTotal);
	SetDlgItemText(IDC_STATIC_PATIENT_LIST, itemText);
}

void CPatientInputDlg::ClickOnePatient(int iSel)
{
	UpdateWindowRect(iSel);	//Update window size
	UpdatePatient(m_PatientSel, FALSE);	//Update Current Selection
	UpdatePatient(iSel);//Update New Selection
	m_PatientSel = iSel;
	(iSel==-1)? (g_CurIId = 0):(g_CurIId = m_PatientListCtrl.GetItemData(iSel));
	LoadTableList(g_CurIId, m_SectionTabCtrl.GetCurSel(), 0);	
}

void CPatientInputDlg::OnClickPatientList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMLISTVIEW pNMListView = (NM_LISTVIEW *)pNMHDR;
	ClickOnePatient(pNMListView->iItem);
	*pResult = 0;
}

void CPatientInputDlg::OnSelchangeCitySelCombo() 
{
    m_TownSelCtrl.ResetContent();
    //Add All Town Name
    int nCity = m_CitySelCtrl.GetCurSel();
	for(UINT i=0; i<gCTinfo[nCity].townsize; i++)
    {
        m_TownSelCtrl.AddString(gCTinfo[nCity].pTown[i].name);
    }

	UpdatePatient(m_PatientSel, FALSE);
	m_PatientListCtrl.DeleteAllItems();
	
	if( g_CurIId != 0)
	{
		g_CurIId = 0;
		m_PatientSel = -1;
		UpdateWindowRect(-1);
	}
	if(nCity == m_CitySelCtrl.GetCount()-1)//Last one is 全部
	{
		SetDlgItemText(IDC_EXPORT_DATA, "导出“所有地市”信息!");
		SetDlgItemText(IDC_STATIC_PATIENT_LIST, "患者登记列表：");
		m_TownSelCtrl.SetCurSel(m_TownSelCtrl.GetCount()-1);
		OnSelchangeTownSelCombo();
	}
	else
	{
		SetDlgItemText(IDC_EXPORT_DATA, "导出“"+CString(gCTinfo[nCity].name)+"所有县区”信息!");
	}
}

void CPatientInputDlg::OnSelchangeTownSelCombo() 
{
	int nCity = m_CitySelCtrl.GetCurSel();
	int nTown = m_TownSelCtrl.GetCurSel();
	UINT cId = gCTinfo[nCity].id;
    UINT tId = gCTinfo[nCity].pTown[nTown].id;
	
	if(nCity == m_CitySelCtrl.GetCount()-1)
	{
		cId = 0;
	}
	UpdatePatient(m_PatientSel, FALSE);
	if(nTown == m_TownSelCtrl.GetCount()-1)//Last one is 全部
	{
		SetDlgItemText(IDC_EXPORT_DATA, "导出“"+CString(gCTinfo[nCity].name)+"所有县区”信息!");
		m_PatientListCtrl.DeleteAllItems();
		SetDlgItemText(IDC_STATIC_PATIENT_LIST, "患者登记列表：");
		CID sId(cId);
		tId = sId.GetId(TUI_ID_TOWN_TYPE);
	}
	else
	{
		//Specific Town
		SetDlgItemText(IDC_EXPORT_DATA, "导出“"+CString(gCTinfo[nCity].pTown[nTown].name)+"”信息");
	}
	m_FilterCtrl.SetWindowText("");
	LoadPatientList(cId, tId);
    CData::cSel=nCity;
    CData::tSel=nTown;
	
	if( g_CurIId != 0)
	{
		g_CurIId = 0;
		m_PatientSel = -1;
		UpdateWindowRect(-1);
	}
}

void CPatientInputDlg::LoadPatientList(UINT cId, UINT tId)
{
//	g_Tools.StartTimeCount();

	m_PatientListCtrl.DeleteAllItems();	
	
	CCity* pCity = NULL;
	CTown* pTown = NULL;
	CIndividual* pInd = NULL;
	CString name;
	int nPreIndex =0;
	CString curIndId;
	CString nameOrId;
	m_FilterCtrl.GetWindowText(nameOrId);
	nameOrId.TrimLeft();
	nameOrId.TrimRight();
	int nTotal = 0;
	int i,j,k;
	
	CID sId(cId);
	UINT tIdOfAll = sId.GetId(TUI_ID_TOWN_TYPE);

	CWaitCursor wait;
	for(k=0; k<m_Data.m_CList.GetSize(); k++)
	{
		pCity = m_Data.m_CList.GetAt(k);	
		if ((cId != 0) && (pCity->id != cId))
			continue;
		for(i=0; i<pCity->m_TList.GetSize(); i++)
		{
			pTown = pCity->m_TList.GetAt(i);
			if ((tId!=tIdOfAll) && (pTown->id != tId))
				continue;
			if (CID(pTown->id).GetCode(TUI_ID_TOWN_TYPE)>90)
				continue;
			for (j=0; j<pTown->m_IList.GetSize(); j++)
			{
				pInd = pTown->m_IList.GetAt(j);
				if( tId != tIdOfAll){
					curIndId.Format("%04d", CID(pInd->id).GetCode(TUI_ID_IND_TYPE)); //bbq: 03?
				}else{
					curIndId.Format("%d", pInd->id);
				}
				//Filter pInd by ID or name
				if( nameOrId != "")
				{
					if( (pInd->name.Find(nameOrId) == -1)
					 && (curIndId.Find(nameOrId) == -1))
						continue;
				}
				name = curIndId;
				if (pInd->name != ""){
					name = name+"\n("+pInd->name+")";
				}
				nPreIndex = m_PatientListCtrl.InsertItem(nPreIndex, name, pInd->status);
				m_PatientListCtrl.SetItemData(nPreIndex, pInd->id);
				nTotal++;
				if( nTotal == 25 )
				{
					m_PatientListCtrl.UpdateWindow();
				}
			}
		}
	}
	//Sort Item
	m_PatientListCtrl.SortItems(PatientListCtrlCompareProc, 0);

	CString itemText;
	itemText.Format("患者登记列表：(总数%d)", nTotal);
	SetDlgItemText(IDC_STATIC_PATIENT_LIST, itemText);

// 	double myTime;
// 	g_Tools.ElapsedTime(&myTime);
// 	CString msg;
// 	msg.Format("%f", myTime);
// 	AfxMessageBox(msg);
}


void CPatientInputDlg::OnSelchangeSectionTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
    if (g_CurIId != 0) 
        LoadTableList(g_CurIId, m_SectionTabCtrl.GetCurSel(), 0);
    *pResult = 0;
}

void CPatientInputDlg::OnSelchangeSubSectionTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    if (g_CurIId != 0) 
    {
		LoadTableList(g_CurIId, m_SectionTabCtrl.GetCurSel(), m_SubSectionTabCtrl.GetCurSel());
	}
    *pResult = 0;
}

void CPatientInputDlg::LoadTableList(UINT iId, UINT iSection, UINT iSubSection)
{
    m_TableListCtrl.DeleteAllItems();	
    UINT i = 0;
    if( iId == 0)
    {
        return;
    }
    
	CIndividual* pInd = (CIndividual*)CData::GetData(iId);
	ASSERT(pInd);

    UINT tableSize = gSectionNameSize;
    TABLE_STRUCT* pTable = gTable[iSection];
    ASSERT(pTable);
    
	tableSize = gTableSize[iSection];
	//Setup SubSection Tab
	m_SubSectionTabCtrl.DeleteAllItems();
    if (pTable[iSubSection].sub != NULL)
    {
        TCITEM tc;
        tc.mask=(TCIF_TEXT|TCIF_IMAGE);

		for(i=0; i<tableSize; i++)
        {
            tc.iImage=i;
            tc.pszText = pTable[i].name;
            m_SubSectionTabCtrl.InsertItem(i,&tc);
			m_SubSectionTabCtrl.caption.Add(pTable[i].name);
        }
        m_SubSectionTabCtrl.SetCurSel(iSubSection);

        tableSize = pTable[iSubSection].subsize;
        pTable = pTable[iSubSection].sub;
    }
    
    //Setup Tables
	int iItem = 0;
    for (i = 0; i < tableSize; i++) {
        g_Month = pTable[i].param;
		if(pTable[i].checkFun && !pTable[i].checkFun())
		{
			m_TableListCtrl.InsertItem(iItem, pTable[i].name, 1);
			pInd->SetUnessaryData(pTable[i].itemStart, pTable[i].itemEnd);
		}
		else
		{
			//Found Bug: Set Necessary First, then Check if finished
			pInd->SetNessaryData(pTable[i].itemStart, pTable[i].itemEnd);
			if (pInd->IsTableFinished(iSection, iSubSection, i))
			{
				m_TableListCtrl.InsertItem(iItem, pTable[i].name, 2);
			}
			else
			{
				m_TableListCtrl.InsertItem(iItem, pTable[i].name, 0);
			}
		}
        m_TableListCtrl.SetItemData(iItem, (DWORD)&pTable[i]);
		iItem++;
    }
}

void CPatientInputDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	// Do not call CDialog::OnPaint() for painting messages
}

void CPatientInputDlg::OnDeletePatient() 
{
	if (g_CurIId == 0)
		return;
	POSITION pos = m_PatientListCtrl.GetFirstSelectedItemPosition();
	if (pos) 
	{ 
		int nIndex = m_PatientListCtrl.GetNextSelectedItem(pos);
		ASSERT(g_CurIId == m_PatientListCtrl.GetItemData(nIndex));
		CString msg;
		msg.Format("确定删除重大专项ID: “%d” ?", g_CurIId);
		if( MessageBox(msg,"提示",MB_YESNO|MB_ICONQUESTION|MB_SYSTEMMODAL) == IDNO )
		{
			return;
		}
		CData::RemoveInd((CIndividual*)CData::GetData(g_CurIId));
		m_PatientListCtrl.DeleteItem(nIndex);
		UpdateWindowRect(-1);
		g_CurIId = 0;
		m_PatientSel = -1;

		m_FilterCtrl.SetWindowText("");
		OnChangeFilter();
	}
}

void CPatientInputDlg::UpdateWindowRect(int iPatientSel)
{
    CRect curRect;
	GetWindowRect(curRect);
	if ( iPatientSel == -1) 
	{
		if ((curRect.bottom-curRect.top) >= (orginalRect.bottom-orginalRect.top))
		{
			curRect.bottom -=m_WndBottomOffset;
			MoveWindow(curRect);
		}
		m_TableListCtrl.DeleteAllItems();	
		g_CurIId = 0;
		return;
	}
	else
	{
		if ((curRect.bottom-curRect.top) < (orginalRect.bottom-orginalRect.top-m_WndBottomOffset/2))
		{
			curRect.bottom +=m_WndBottomOffset;
			MoveWindow(curRect);
		}
	}
}

BOOL CPatientInputDlg::ExportToExcel(CString filename, CString sItem, CString eItem, BOOL bIncludeId, BOOL bIsIndex)
{
	CString sOutputFile = filename;
	
	if( bIsIndex == FALSE)
	{
		sOutputFile = sOutputFile.Left(sOutputFile.GetLength()-4);
		sOutputFile = sOutputFile+"-文字.xls";
	}

	CFile filetry;
	if( filetry.Open(sOutputFile,CFile::modeReadWrite|CFile::modeCreate) == FALSE )
	{
		AfxMessageBox("无法打开文件："+sOutputFile+"，如该文件已打开，请先关闭!");
		return FALSE;
	}
	else
	{
		filetry.Close();
		CFile::Remove(sOutputFile);
	}

	int iStart = CIndividual::GetItemIndex(sItem);
	int iEnd = CIndividual::GetItemIndex(eItem);

	CStringArray titleArray;
	/* 导出选定的文件 */
	CSpreadSheet SS1(sOutputFile,"Sheet1",false);
	SS1.BeginTransaction();
	

	//导出Header:
	int i=0, j=0;
	//是否加上前三项
	if( bIncludeId)
	{
		titleArray.Add(gAItemInfo[0].name);
		titleArray.Add(gAItemInfo[1].name);
		titleArray.Add(gAItemInfo[2].name);
	}
	for(i=iStart; i<=iEnd; i++)
	{
		titleArray.Add(gAItemInfo[i].name);
	}
	SS1.AddHeaders(titleArray);
	
	//加入内容
	CStringArray answerArray;
	int nCount = m_IExportList.GetSize();
	CIndividual* pInd;
	CString text;
	CString text2;
	int value;
	
	for(i=0; i<nCount; i++)
	{
		answerArray.RemoveAll();
		pInd = m_IExportList.GetAt(i);

		if (bIncludeId)
		{
			answerArray.Add(pInd->items[0]);
			answerArray.Add(pInd->items[1]);
			answerArray.Add(pInd->items[2]);
		}
		
		for(j=iStart; j<=iEnd; j++)
		{
			text = pInd->items[j];
			text2 = text;
			switch( gAItemInfo[j].type)
			{
			case 0://Edit
				if(pInd->itemStatus[j] == 1)
					answerArray.Add(text);
				else if(pInd->itemStatus[j] == 2)
					answerArray.Add("8888");
				else 
					answerArray.Add("9999");
				break;
			case 1: //Sel
				if( pInd->itemStatus[j] == 1)
				{
					text2 = text.Mid(2);
					text = text.Left(1);
					//Minus offset
					if( gAItemInfo[j].offset != 0)
					{
						value = atoi(text);
						value-=gAItemInfo[j].offset;
						text.Format("%d", value);
					}
					//Special Selection value
					if( (text2 == "不清楚")
						||(text2 == "不详")
						||(text2 == "未查")
					)
					{
						text = "9";
					}
					if( (text2 == "不需查"))
					{
						text = "8";
					}

					if( bIsIndex)
					{
						answerArray.Add(text);
					}else
					{
						answerArray.Add(text2);
					}
				}
				else if (pInd->itemStatus[j] == 2)
				{
					answerArray.Add("8888");
				}
				else
				{
					answerArray.Add("9999");
				}
				break;
			case 2: //Date
				if( pInd->itemStatus[j] == 1)
					answerArray.Add(text);
				else if( pInd->itemStatus[j] == 2)
					answerArray.Add("8888/88/88");
				else
					answerArray.Add("9999/99/99");
				break;
			}
		}
		SS1.AddRow(answerArray);
		m_ExportProgressCtrl.StepIt();
		m_ExportProgressCtrl.UpdateWindow();
	}
	SS1.Commit();
	return TRUE;
}

void CPatientInputDlg::OnExportData()
{
	//导出数据
	int cSel = m_CitySelCtrl.GetCurSel();
	if ( cSel == -1)
	{
		AfxMessageBox("没有要导出的记录!");
		return;
	}

	int tSel = m_TownSelCtrl.GetCurSel();
	if ( tSel == -1)
	{
		tSel = m_TownSelCtrl.GetCount()-1;
	}

	m_IExportList.RemoveAll();
	CString dirName;
	if (cSel == m_CitySelCtrl.GetCount()-1)
	{
		dirName = "全部地市县区";
	}
	else
	{
		dirName = gCTinfo[cSel].name;
		dirName = dirName + "_" + gCTinfo[cSel].pTown[tSel].name;
		dirName.Replace("(导出时使用)", "");
	}
	
	UINT cId = gCTinfo[cSel].id;
	UINT tId = gCTinfo[cSel].pTown[tSel].id;
	UINT tIdOfResearch = CID(cId).GetId(TUI_ID_TOWN_TYPE);

	CCity* pCity;
	CTown* pTown;
	CIndividual* pInd;
	int i,j,k;
	for(i=0; i<m_Data.m_CList.GetSize();i++)
	{
		pCity = m_Data.m_CList.GetAt(i);
		if( (cId != 0) && (cId != pCity->id))
			continue;
		for(j=0; j<pCity->m_TList.GetSize(); j++)
		{
			pTown = pCity->m_TList.GetAt(j);
			if (CID(pTown->id).GetCode(TUI_ID_TOWN_TYPE)>90) continue;
			if ((tId != tIdOfResearch) && (tId!=pTown->id))
				continue;
			for(k=0; k<pTown->m_IList.GetSize(); k++)
			{
				pInd = pTown->m_IList.GetAt(k);
				m_IExportList.Add(pInd);
			}
		}
	}
	if (m_IExportList.GetSize() == 0)
	{
		AfxMessageBox("没有要导出的记录!");
		return;
	}
	if( MessageBox("确定导出数据到Excel?","提示",MB_YESNO|MB_ICONQUESTION|MB_SYSTEMMODAL) == IDNO )
	{
		return;
	}
	CWaitCursor cursorWait;

	CString exportDir;
	CString exportFileName;
	exportDir = g_Tools.GetRunPath()+dirName+"\\";
	exportFileName = exportDir + "<table>.xls";
	
	if( !g_Tools.IsDirExist(exportDir))
	{
		g_Tools.CreateDir(exportDir);
	}
	CString tempName = exportFileName.Left(exportFileName.GetLength()-4);
	CString table1FileName = exportFileName;
	CString table2FileName = exportFileName;
	CString table3FileName = exportFileName;
	CString table4FileName = exportFileName;
	CString table5FileName = exportFileName;
	table1FileName.Replace("<table>", "研究对象纳入和病例对照研究");
	table2FileName.Replace("<table>", "患者治疗1-8月");
	table3FileName.Replace("<table>", "患者治疗9-16月");
	table4FileName.Replace("<table>", "患者治疗17-24月及转归");
	table5FileName.Replace("<table>", "费用支出记录");

	m_ExportProgressCtrl.ShowWindow(SW_SHOW);
	m_StaticExportCtrl.SetWindowText("导出中，请等待...");
	m_ExportProgressCtrl.SetRange(0, m_IExportList.GetSize()*10);
	m_ExportProgressCtrl.SetStep(1);
	m_ExportProgressCtrl.SetPos(0);
	
	BOOL isOK = FALSE;
	for(;;)
	{
		if (!ExportToExcel(table1FileName, "A1", "C19", FALSE, TRUE)) break;
		if (!ExportToExcel(table1FileName, "A1", "C19", FALSE, FALSE)) break;
		if (!ExportToExcel(table2FileName, "D1", "D194", TRUE, TRUE)) break;
		if (!ExportToExcel(table2FileName, "D1", "D194", TRUE, FALSE)) break;
		if (!ExportToExcel(table3FileName, "D195", "D386", TRUE, TRUE)) break;
		if (!ExportToExcel(table3FileName, "D195", "D386", TRUE, FALSE)) break;
		if (!ExportToExcel(table4FileName, "D387", "D580", TRUE, TRUE)) break;
		if (!ExportToExcel(table4FileName, "D387", "D580", TRUE, FALSE)) break;
		if (!ExportToExcel(table5FileName, "E1", "G14", TRUE, TRUE)) break;
		if (!ExportToExcel(table5FileName, "E1", "G14", TRUE, FALSE)) break;
		isOK = TRUE;
		break;
	}
	m_StaticExportCtrl.SetWindowText("");
	m_ExportProgressCtrl.ShowWindow(SW_HIDE);

	if (isOK)
		AfxMessageBox("Excel文件已经输出到: "+exportDir);
}

void CPatientInputDlg::OnChangeFilter() 
{
	int cSel = m_CitySelCtrl.GetCurSel();
	int tSel = m_TownSelCtrl.GetCurSel();
	if (cSel == -1) return;
	if (tSel == -1) return;
	UINT cId = 0;
	UINT tId = 0;
	if (cSel == m_CitySelCtrl.GetCount()-1)
	{
		cId = 0;
		tId = 0;
	}
	else
	{
		 cId = gCTinfo[cSel].id;
		 if (tSel == m_TownSelCtrl.GetCount()-1)
		 {
			tId = CID(cId).GetId(TUI_ID_TOWN_TYPE);
		 }
		 else
		 {
			 tId = gCTinfo[cSel].pTown[tSel].id;
		 }
	}
//	CTown* pTown = (CTown*)CData::GetData(tId);
//	if( pTown == NULL || pTown->m_IList.GetSize() == 0) return;
	//Filter
	ClickOnePatient(-1);
	LoadPatientList(cId, tId);
}

void CPatientInputDlg::OnCheckStat() 
{
	int cSel = m_CitySelCtrl.GetCurSel();
	int tSel = m_TownSelCtrl.GetCurSel();
	if (cSel == -1) return;
	if (tSel == -1) return;
	UINT cId = gCTinfo[cSel].id;
	UINT tId = gCTinfo[cSel].pTown[tSel].id;
	CCity* pCity;
	CTown* pTown;
	CIndividual* pInd;
	int i,j,k;
	
	CString title;
	if (cSel == m_CitySelCtrl.GetCount()-1)
	{
		title = "全部地市县区";
	}
	else
	{
		title = gCTinfo[cSel].name;
		title = title + "_" + gCTinfo[cSel].pTown[tSel].name;
		title.Replace("(导出时使用)", "");
	}
		
	m_IExportList.RemoveAll();
	for(i=0; i<m_Data.m_CList.GetSize();i++)
	{
		pCity = m_Data.m_CList.GetAt(i);
		if( (cId != 0) && (cId != pCity->id))
			continue;
		for(j=0; j<pCity->m_TList.GetSize(); j++)
		{
			pTown = pCity->m_TList.GetAt(j);
			if (CID(pTown->id).GetCode(TUI_ID_TOWN_TYPE)>90) continue;
			if ((tId != CID(cId).GetId(TUI_ID_TOWN_TYPE)) && (tId!=pTown->id))
				continue;
			for(k=0; k<pTown->m_IList.GetSize(); k++)
			{
				pInd = pTown->m_IList.GetAt(k);
				m_IExportList.Add(pInd);
			}
		}
	}
	if (m_IExportList.GetSize() == 0)
	{
		AfxMessageBox("没有患者记录!");
		return;
	}
	
	CStatsDialog dlg;
	dlg.pIndList = &m_IExportList;
	dlg.title = title;
	dlg.DoModal();
}

void CPatientInputDlg::OnImportData() 
{
	UINT cId = 0, tId = 0;
	int cSel = m_CitySelCtrl.GetCurSel();
	int tSel = m_TownSelCtrl.GetCurSel();
	if (cSel != -1)
	{
		if (cSel == m_CitySelCtrl.GetCount()-1)
		{
			cId = 0;
			tId = 0;
		}
		else
		{
			cId = gCTinfo[cSel].id;
			if (tSel != -1)
			{
				if (tSel == m_TownSelCtrl.GetCount()-1)
					tId = CID(cId).GetId(TUI_ID_TOWN_TYPE);
				else
					tId = gCTinfo[cSel].pTown[tSel].id;
			}
		}
	}

	//Check excel file
	char szFilter[256];
	sprintf(szFilter,"Execl文件(*.xls)|*.xls||");
	CFileDialog dlg(true, "xls", "未命名", OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter);
	CString sFileName;
	if( dlg.DoModal() == IDOK)
	{
		sFileName = dlg.GetPathName();
	}else{
		return;
	}

	CString tempStr;
	if( sFileName.Find(".xls") > 0)
	{
		CFile file;
		if( file.Open(sFileName, CFile::modeRead) == FALSE )
		{
			AfxMessageBox("打不开文件或文件不存在："+g_ExeclFile);
			return;
		}
		file.Close();

		CSpreadSheet *pSS1 = new CSpreadSheet(sFileName,"Sheet1",false);
		
		int count = 0;
		count = pSS1->GetTotalRows();
		
		if( count == 0 )
		{
			AfxMessageBox("没有记录可导入,请确认!");
			delete pSS1;
			return;
		}

		tempStr.Format("%d", pSS1->GetTotalColumns());
		if(pSS1->GetTotalColumns()!=73)
		{
			AfxMessageBox("请确认记录格式，字段应该为73个!");
			return;
		}

		CStringArray sRecStrs;
		pSS1->ReadRow(sRecStrs,1);
		
		CString iId, name;
		iId = sRecStrs.GetAt(0);
		name = sRecStrs.GetAt(1);
		if( iId != "重大专项ID编号" || name != "结核病患者登记号")
		{
			AfxMessageBox("导入文件格式不匹配，请确认，前面两列是：“重大专项ID编号”与“结核病患者登记号”!");
			delete pSS1;
			return;
		}
		delete pSS1;

		if( m_CurDate == "")
		{
			CDateConfirmDlg dateDlg;
			if (dateDlg.DoModal() == IDCANCEL)
				return;
			m_CurDate = dateDlg.GetInputDate();
		}
		
		CImportDataDlg dlg;
		dlg.m_ExcelFile = sFileName;
		dlg.curDate = m_CurDate;
		dlg.strTownName = "";//CString(gCTinfo[cSel].name)+"-"+CString(gCTinfo[cSel].pTown[tSel].name);
		if (dlg.DoModal() == IDOK)
		{
			int count = dlg.m_IImportList.GetSize();
			CIndividual* pInd;
			CTown* pCurTown;
			UINT curTid;
			if(count>0)
			{
				for(int i=0; i<count; i++)
				{
					pInd = dlg.m_IImportList.GetAt(i);
					curTid = CID(pInd->id).GetId(TUI_ID_TOWN_TYPE);
					pCurTown = (CTown*)CData::GetData(curTid);
					if(!pCurTown)
					{
						pCurTown = (CTown*)m_Data.CreateData(curTid);
					}
					pInd->pTown = pCurTown;
					pCurTown->m_IList.Add(pInd);
				}
				m_CitySelCtrl.SetCurSel(m_CitySelCtrl.GetCount()-1);
				OnSelchangeCitySelCombo();
//				if (cId != -1 && tId != -1)
//					LoadPatientList(cId, tId);
			}
		}
	}
}

HBRUSH CPatientInputDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	int id = pWnd->GetDlgCtrlID();
	
	if( ( id == IDC_STATIC_PATIENT_LIST ) ||
		( id == IDC_STATIC_CT ) ||
		( id == IDC_STATIC_FILTER ) ||
		( id == IDC_STATIC_EXPORT))
	{
		pDC->SetTextColor(RGB(0,0,255));
#if 0
		font.CreateFont(
			12,                        // nHeight
			0,                         // nWidth
			0,                         // nEscapement
			0,                         // nOrientation
			FW_NORMAL,                 // nWeight
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
	return hbr;
}

int CALLBACK CPatientInputDlg::PatientListCtrlCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	return (int)(lParam1 - lParam2);
}

void CPatientInputDlg::UpdatePatient(int iSel, BOOL isSel, CString sText)
{
	if (iSel == -1) return;
	if (iSel >= m_PatientListCtrl.GetItemCount()) return;
	CIndividual *pInd = (CIndividual*)CData::GetData(m_PatientListCtrl.GetItemData(iSel));
	if (pInd == NULL) return;
	
	TCHAR szBuf[1024];
	LVITEM lvi;
	lvi.iSubItem = 0; 
	lvi.mask = LVIF_TEXT | LVIF_IMAGE; 
	lvi.pszText = szBuf;
	lvi.cchTextMax = 1024;
	lvi.iItem = iSel; 
	m_PatientListCtrl.GetItem(&lvi);
	lvi.iImage = pInd->UpdateStatus(isSel);
	m_PatientListCtrl.SetItem(&lvi);
	if (sText != "")
	{
		m_PatientListCtrl.SetItemText(iSel, 0, sText);
	}
}

void CPatientInputDlg::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == 1)
	{
		KillTimer(1);
		if (CData::cSel>=0)
		{
			m_CitySelCtrl.SetCurSel(CData::cSel);
			OnSelchangeCitySelCombo();
			if (CData::cSel != m_CitySelCtrl.GetCount()-1 && CData::tSel>=0)
			{
				m_TownSelCtrl.SetCurSel(CData::tSel);
				OnSelchangeTownSelCombo();
			}
		}
	}
	CDialog::OnTimer(nIDEvent);
}