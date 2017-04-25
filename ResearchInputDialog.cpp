// ResearchInputDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TUI.h"
#include "ResearchInputDialog.h"
#include "CSpreadSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResearchInputDialog dialog


CResearchInputDialog::CResearchInputDialog(CData &data, CWnd* pParent /*=NULL*/)
	: CDialog(CResearchInputDialog::IDD, pParent), m_Data(data)
{
	//{{AFX_DATA_INIT(CResearchInputDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CResearchInputDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResearchInputDialog)
	DDX_Control(pDX, IDC_STATIC_EXPORT, m_StaticExport);
	DDX_Control(pDX, IDC_EXPORT_PROGRESS, m_ExportProgress);
	DDX_Control(pDX, IDC_FILTER, m_FilterCtrl);
	DDX_Control(pDX, IDC_TOWN_SEL_COMBO, m_TownSel);
	DDX_Control(pDX, IDC_CITY_SEL_COMBO, m_CitySel);
	DDX_Control(pDX, IDC_TABLE_LIST, m_TableList);
	DDX_Control(pDX, IDC_PATIENT_LIST, m_PatientList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResearchInputDialog, CDialog)
	//{{AFX_MSG_MAP(CResearchInputDialog)
	ON_CBN_SELCHANGE(IDC_CITY_SEL_COMBO, OnSelchangeCitySelCombo)
	ON_CBN_SELCHANGE(IDC_TOWN_SEL_COMBO, OnSelchangeTownSelCombo)
	ON_BN_CLICKED(IDC_NEW_PATIENT, OnNewPatient)
	ON_EN_CHANGE(IDC_FILTER, OnChangeFilter)
	ON_BN_CLICKED(IDC_DELETE_PATIENT, OnDeletePatient)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_CLICK, IDC_PATIENT_LIST, OnClickPatientList)
	ON_NOTIFY(NM_DBLCLK, IDC_TABLE_LIST, OnDblclkTableList)
	ON_NOTIFY(NM_DBLCLK, IDC_PATIENT_LIST, OnDblclkPatientList)
	ON_BN_CLICKED(IDC_EXPORT_DATA, OnExportData)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResearchInputDialog message handlers

void CResearchInputDialog::OnCancel() 
{
	g_CurIId = 0;
	CDialog::OnCancel();
}

BOOL CResearchInputDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	InitUI();
	g_CurIId = 0;
	m_WndBottomOffset = 123;
    //Set Current City and Type Selection
    if (CData::citySel>=0)
    {
        m_CitySel.SetCurSel(CData::citySel);
        OnSelchangeCitySelCombo();
        if (CData::typeSel>=0)
        {
            m_TownSel.SetCurSel(CData::typeSel);
            OnSelchangeTownSelCombo();
        }
    }
	CenterWindow();
	GetWindowRect(orginalRect);
	CRect rect = orginalRect;
	rect.bottom -=m_WndBottomOffset;
	MoveWindow(rect);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CResearchInputDialog::InitUI()
{
	UINT i=0;
	for(i=0; i<gCTinfoSize-1; i++)
	{
		m_CitySel.AddString(gCTinfo[i].name);
	}
	
	m_pSectionOneImageList = new CImageList();
	m_pSectionOneImageList->Create(48, 48, ILC_COLORDDB, 8, 8);
	m_TableList.SetExtendedStyle(LVS_EX_TRACKSELECT|m_TableList.GetExtendedStyle());
	m_TableList.SetImageList(m_pSectionOneImageList, LVSIL_NORMAL);
	m_pSectionOneImageList->Add(AfxGetApp()->LoadIcon(IDI_TABLE_1));
	m_pSectionOneImageList->Add(AfxGetApp()->LoadIcon(IDI_TABLE_LOCK));

	m_pPatientImageList = new CImageList();
	m_pPatientImageList->Create(32, 32, ILC_COLORDDB, 8, 8);
	m_PatientList.SetImageList(m_pPatientImageList, LVSIL_NORMAL);
	m_pPatientImageList->Add(AfxGetApp()->LoadIcon(IDI_PATIENT));
	m_pPatientImageList->Add(AfxGetApp()->LoadIcon(IDI_PATIENT_SEL));
}

void CResearchInputDialog::OnSelchangeCitySelCombo() 
{
    m_TownSel.SetCurSel(-1);
	m_PatientList.DeleteAllItems();
	if (g_CurIId != 0)
	{
		g_CurIId = 0;
		m_PatientSel = -1;
		UpdateWindowRect(-1);
	}
}

void CResearchInputDialog::OnSelchangeTownSelCombo() 
{
	int nCity = m_CitySel.GetCurSel();
	int nTown = m_TownSel.GetCurSel();
    UINT cId = gCTinfo[nCity].id;
    UINT tId = CID(cId).GetId(TUI_ID_TOWN_TYPE)+nTown+91;
    LoadPatientList(cId, tId);
    CData::citySel=nCity;
    CData::typeSel=nTown;
	
	if( g_CurIId != 0)
	{
		g_CurIId = 0;
		m_PatientSel = -1;
		UpdateWindowRect(-1);
	}	
}

void CResearchInputDialog::UpdateWindowRect(int iPatientSel)
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
		m_TableList.DeleteAllItems();	
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

void CResearchInputDialog::LoadPatientList(UINT cId, UINT tId)
{
	m_PatientList.DeleteAllItems();	
	
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

	CString researchName;

	for(int k=0; k<m_Data.m_CList.GetSize(); k++)
	{
		pCity = m_Data.m_CList.GetAt(k);	
		if ((cId != 0) && (pCity->id != cId))
			continue;
		for(int i=0; i<pCity->m_TList.GetSize(); i++)
		{
			pTown = pCity->m_TList.GetAt(i);
			//Only for type
			if( CID(pTown->id).GetCode(TUI_ID_TOWN_TYPE)<90 ) 
				continue;
			if ((tId!=CID(cId).GetId(TUI_ID_TOWN_TYPE)) && (pTown->id != tId))
				continue;
			for (int j=0; j<pTown->m_IList.GetSize(); j++)
			{
				pInd = pTown->m_IList.GetAt(j);
				researchName = pInd->items[CIndividual::GetItemIndex("H2")];
				curIndId.Format("%d", CID(pInd->id).GetCode(TUI_ID_IND_TYPE));
				//Filter pInd
				if( nameOrId != "")
				{
					if( (pInd->name.Find(nameOrId) == -1)
						&& (curIndId.Find(nameOrId) == -1))
						continue;
				}
				if (researchName  != "")
				{
					name.Format("%d\n(", CID(pInd->id).GetCode(TUI_ID_IND_TYPE));
					name = name+researchName+")";
				}
				else
				{
					name.Format("%d", CID(pInd->id).GetCode(TUI_ID_IND_TYPE));
				}
				nPreIndex = m_PatientList.InsertItem(nPreIndex, name, 0);
				m_PatientList.SetItemData(nPreIndex, pInd->id);
				nTotal++;
			}
		}
	}
	CString itemText;
	itemText.Format("健康对照列表：(总数%d)", nTotal);
	SetDlgItemText(IDC_STATIC_LIST, itemText);
}

void CResearchInputDialog::OnNewPatient() 
{
	int nCity = m_CitySel.GetCurSel();
	if (nCity == -1)
	{
		AfxMessageBox("请选择所在城市和城乡类型，再新建!");
		return;
	}
	int nTown = m_TownSel.GetCurSel();
	if (nTown == -1)
	{
		AfxMessageBox("请选择所在城市和城乡类型，再新建!");
		return;
	}
	
	int iTownId = CID(gCTinfo[nCity].id).GetId(TUI_ID_TOWN_TYPE)+(nTown+91);
	UINT iId = CData::GetNewResearchId(iTownId);
	if ( iId == 0)
	{
		AfxMessageBox("该地区重大编号已使用完!");
		return;
	}
	
	CData::CreateData(iId);
	CString name;
	name.Format("%d", CID(iId).GetCode(TUI_ID_IND_TYPE)); 
	int curPos = m_PatientList.InsertItem(0, name, 0);
	m_PatientList.EnsureVisible(curPos, TRUE);
	m_PatientList.SetItemData(curPos, iId);
	UpdateWindowRect(-1);

	m_FilterCtrl.SetWindowText("");
	OnChangeFilter();

	m_PatientList.EnsureVisible(curPos, TRUE);
}

void CResearchInputDialog::OnChangeFilter() 
{
	int cSel = m_CitySel.GetCurSel();
	int tSel = m_TownSel.GetCurSel();
	if (cSel == -1) return;
	if (tSel == -1) return;
	UINT cId = gCTinfo[cSel].id;
	UINT tId = CID(cId).GetId(TUI_ID_TOWN_TYPE)+tSel+91;
	CTown* pTown = (CTown*)CData::GetData(tId);
	if( pTown == NULL || pTown->m_IList.GetSize() == 0) return;
	
	//Filter
	LoadPatientList(cId, tId);
}

void CResearchInputDialog::OnDeletePatient() 
{
	if (g_CurIId == 0)
		return;
	POSITION pos = m_PatientList.GetFirstSelectedItemPosition();
	if (pos) 
	{ 
		int nIndex = m_PatientList.GetNextSelectedItem(pos);
		ASSERT(g_CurIId == m_PatientList.GetItemData(nIndex));
		CString msg;
		msg.Format("确定删除重大专项ID: “%d” ?", CIndividual::ConvertToResearchId(g_CurIId));
		if( MessageBox(msg,"提示",MB_YESNO|MB_ICONQUESTION|MB_SYSTEMMODAL) == IDNO )
		{
			return;
		}
		CData::RemoveInd((CIndividual*)CData::GetData(g_CurIId));
		m_PatientList.DeleteItem(nIndex);
		UpdateWindowRect(-1);
		g_CurIId = 0;

		m_FilterCtrl.SetWindowText("");
		OnChangeFilter();
	}	
}

void CResearchInputDialog::OnDestroy() 
{
	CDialog::OnDestroy();
	
	if (m_pSectionOneImageList)
	{
		delete m_pSectionOneImageList;
	}
	
	if (m_pPatientImageList)
	{
		delete m_pPatientImageList;
	}	
}

void CResearchInputDialog::OnClickPatientList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMLISTVIEW pNMListView = (NM_LISTVIEW *)pNMHDR;
	int iSel = pNMListView->iItem;
	UpdateWindowRect(iSel);
	if ( iSel == -1) 
	{
		m_TableList.DeleteAllItems();	
		g_CurIId = 0;
	}
	
	//Update Image:
	TCHAR szBuf[1024];
	LVITEM lvi;
	lvi.iSubItem = 0; 
	lvi.mask = LVIF_TEXT | LVIF_IMAGE; 
	lvi.pszText = szBuf;
	lvi.cchTextMax = 1024;
	CString curText;
	if( m_PatientSel != -1)
	{
		lvi.iItem = m_PatientSel; 
		m_PatientList.GetItem(&lvi);
		//curText = m_PatientList.GetItemText(m_PatientSel, 0);
		lvi.iImage = 0;
		m_PatientList.SetItem(&lvi);
	}
	
	if (iSel == -1)
	{
		return;
	}
	
	lvi.iItem = iSel; 
	m_PatientList.GetItem(&lvi);
	lvi.iImage = 1;
	m_PatientList.SetItem(&lvi);
	
	m_PatientSel = iSel;	
	g_CurIId = m_PatientList.GetItemData(iSel);
	
	LoadTableList(g_CurIId);
	g_CurIId = m_PatientList.GetItemData(iSel);
	*pResult = 0;
}

void CResearchInputDialog::LoadTableList(UINT iId)
{
    m_TableList.DeleteAllItems();	
    UINT i = 0;
    if( iId == 0)
    {
        return;
    }
    
	CIndividual* pInd = (CIndividual*)CData::GetData(iId);
	ASSERT(pInd);
	
    UINT tableSize = gResearchTableSize;
    TABLE_STRUCT* pTable = gResearchTable;
    ASSERT(pTable);
    
    //Setup Tables
	int iItem = 0;
    for (i = 0; i < tableSize; i++) {
        if( pTable[i].checkFun && !pTable[i].checkFun())
		{
			m_TableList.InsertItem(iItem, pTable[i].name, 1);
			pInd->SetUnessaryData(pTable[i].itemStart, pTable[i].itemEnd);
		}
		else
		{
			m_TableList.InsertItem(iItem, pTable[i].name, 0);
			pInd->SetNessaryData(pTable[i].itemStart, pTable[i].itemEnd);
		}
        m_TableList.SetItemData(iItem, (DWORD)&pTable[i]);
		iItem++;
    }
}

void CResearchInputDialog::OnDblclkTableList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMLISTVIEW pNMListView = (NM_LISTVIEW *)pNMHDR;
	
	//是否点击了有效的项目。
    if (pNMListView->iItem == -1) return;
	
	CIndividual* pInd = (CIndividual*)CData::GetData(g_CurIId);
	CString oldName = pInd->items[CIndividual::GetItemIndex("H2")];
	CString newName;
	CString itemText;
	
	TABLE_STRUCT* pTable = (TABLE_STRUCT*)m_TableList.GetItemData(pNMListView->iItem);
	CDialog* pDlg = pTable->pDlg;
	if (pDlg)
	{
		if( pTable->checkFun)
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
		newName = pInd->items[CIndividual::GetItemIndex("H2")];
		CString strId = pInd->items[CIndividual::GetItemIndex("H1")];
		strId = strId.Mid(2);
		if( strId[0] == '0')
			strId = strId.Mid(1);
		if( newName != oldName)
		{
			//Update Current Patient
			if( newName == "")
			{
				itemText = strId;
			}else
			{
				itemText = strId + "\n("+newName+")";
			}
			m_PatientList.SetItemText(m_PatientSel, 0, itemText);
		}
		//BBQ: TODO temp solution.
		LoadTableList(g_CurIId);
	}
	*pResult = 0;
}

void CResearchInputDialog::OnDblclkPatientList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if( g_CurIId == 0)
		return;
	CIndividual* pInd = (CIndividual*)CData::GetData(g_CurIId);
	CString oldName = pInd->items[CIndividual::GetItemIndex("H2")];
	CString newName;
	CString itemText;
	
	gResearchTable[0].pDlg->DoModal();
	//Name is modified
	newName = pInd->items[CIndividual::GetItemIndex("H2")];
	CString strId = pInd->items[CIndividual::GetItemIndex("H1")];
	strId = strId.Mid(2);
	if( strId[0] == '0')
		strId = strId.Mid(1);
	if( newName != oldName)
	{
		//Update Current Patient
		if( newName == "")
		{
			itemText = strId;
		}else
		{
			itemText = strId + "\n("+newName+")";
		}
		m_PatientList.SetItemText(m_PatientSel, 0, itemText);
	}
	*pResult = 0;
}

void CResearchInputDialog::OnExportData() 
{
	CWaitCursor cursorWait;
	//默认导出全部
	m_IExportList.RemoveAll();
	UINT cId;
	UINT tId1;
	UINT tId2;
	CCity* pCity;
	CTown* pTown1;
	CTown* pTown2;
	int i;
	UINT j;
	for(j=0; j<gCTinfoSize-1; j++)
	{
		cId = gCTinfo[j].id;
		tId1 = CID(cId).GetId(TUI_ID_TOWN_TYPE)+91;
		tId2 = CID(cId).GetId(TUI_ID_TOWN_TYPE)+92;
		
		pCity = (CCity*)CData::GetData(cId);
		pTown1 = (CTown*)CData::GetData(tId1);
		pTown2 = (CTown*)CData::GetData(tId2);
		
		if( (pTown1 != NULL) && (pTown1->m_IList.GetSize() > 0))
		{
			for(i=0; i<pTown1->m_IList.GetSize(); i++)
			{
				m_IExportList.Add(pTown1->m_IList.GetAt(i));
			}
		}
		if( (pTown2 != NULL) && (pTown2->m_IList.GetSize() > 0))
		{
			for(i=0; i<pTown2->m_IList.GetSize(); i++)
			{
				m_IExportList.Add(pTown2->m_IList.GetAt(i));
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

	CString exportFileName = g_Tools.GetRunPath()+"健康对照表.xls";
	CString table1FileName = exportFileName;
	m_ExportProgress.ShowWindow(SW_SHOW);
	m_StaticExport.SetWindowText("导出中，请等待...");
	m_ExportProgress.SetRange(0, m_IExportList.GetSize()*2);
	m_ExportProgress.SetStep(1);
	m_ExportProgress.SetPos(0);
	BOOL bOK = FALSE;
	for(;;)
	{
		if (!ExportToExcel(table1FileName, "H1", "H27", FALSE, TRUE)) break;
		if (!ExportToExcel(table1FileName, "H1", "H27", FALSE, FALSE)) break;
		bOK = TRUE;
		break;
	}
	m_StaticExport.SetWindowText("");
	m_ExportProgress.ShowWindow(SW_HIDE);
	if( bOK)
		AfxMessageBox("健康对照表.xls, 已经输出到: "+g_Tools.GetRunPath());
}

BOOL CResearchInputDialog::ExportToExcel(CString filename, CString sItem, CString eItem, BOOL bIncludeId, BOOL bIsIndex)
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
					//Special value
					if( (text2 == "不清楚")
						||(text2 == "不详")
						||(text2 == "未查")
						)
					{
						text = "9";
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
		m_ExportProgress.StepIt();
	}
	SS1.Commit();	
	return TRUE;
}

HBRUSH CResearchInputDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	int id = pWnd->GetDlgCtrlID();
	
	if( ( id == IDC_STATIC_LIST ) ||
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

void CResearchInputDialog::OnOK() 
{
	return;	
	CDialog::OnOK();
}
