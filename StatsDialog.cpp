// StatsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TUI.h"
#include "StatsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatsDialog dialog


CStatsDialog::CStatsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CStatsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStatsDialog)
	//}}AFX_DATA_INIT
}


void CStatsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatsDialog)
	DDX_Control(pDX, IDC_MONTH_SEL, m_MonthCtrl);
	DDX_Control(pDX, IDC_STATS_TWO, m_StatsTwo);
	DDX_Control(pDX, IDC_STATS_ONE, m_StatsOne);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStatsDialog, CDialog)
	//{{AFX_MSG_MAP(CStatsDialog)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_CURRENT_MONTH, OnDatetimechangeCurrentMonth)
	ON_BN_CLICKED(IDC_EXPORT, OnExport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatsDialog message handlers

void CStatsDialog::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CStatsDialog::OnOK() 
{
	// TODO: Add extra validation here
	return;
	CDialog::OnOK();
}

BOOL CStatsDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_StatsOneCount = 0;
	m_StatsTwoCount = 0;

	CString wndText;
	GetWindowText(wndText);
	SetWindowText(title+"-"+wndText);
	
	int count = pIndList->GetSize();
	
	//Setup Month Combo
	m_MonthCtrl.SetFormat("yyyy/M");
	CTime curTime = CTime::GetCurrentTime();
/*
	int nYear, nMonth, nDay;
	nYear = curTime.GetYear();
	nMonth = curTime.GetMonth();
	int nLastDay[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if(nYear%4 == 0)
	{
		nLastDay[1] = 29;
	}
	nDay = nLastDay[nMonth-1];
	CTime configTime(nYear, nMonth, nDay, 0, 0, 0);
*/
	m_MonthCtrl.SetTime(&curTime);

	char* items[] = {"",   "患者登记总数",		"进行痰培养数",			"痰培养结果报告数", "培养阳性数",			"菌种鉴定数", 
						   "进行药敏试验数",	"药敏试验结果报告数",	"诊断MDR-TB患者数", "诊断广泛耐药患者数",	"纳入研究的MDR-TB患者数", 
						   "纳入研究的非MDR-TB患者数"};
	m_StatsOneCount = sizeof(items)/sizeof(char*);
	int i=0;
	for(i=1; i<m_StatsOneCount; i++)
	{
		itemsHead.Add(items[i]);
	}

	m_StatsOne.SetExtendedStyle (LVS_AUTOARRANGE|LVS_EX_TRACKSELECT|LVS_EX_FLATSB|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_REGIONAL);
	i=0;
	m_StatsOne.InsertColumn (1,items[i++],LVCFMT_LEFT,100,1);
	m_StatsOne.InsertColumn (2,items[i++],LVCFMT_LEFT,120,1);
	m_StatsOne.InsertColumn	(3,items[i++],LVCFMT_LEFT,120,1);
	m_StatsOne.InsertColumn (4,items[i++],LVCFMT_LEFT,160,1);
	m_StatsOne.InsertColumn	(5,items[i++],LVCFMT_LEFT,100,1);
	m_StatsOne.InsertColumn (6,items[i++],LVCFMT_LEFT,100,1);
	m_StatsOne.InsertColumn	(7,items[i++],LVCFMT_LEFT,140,1);
	m_StatsOne.InsertColumn (8,items[i++],LVCFMT_LEFT,180,1);
	m_StatsOne.InsertColumn	(9,items[i++],LVCFMT_LEFT,160,1);
	m_StatsOne.InsertColumn	(10,items[i++],LVCFMT_LEFT,160,1);
	m_StatsOne.InsertColumn (11,items[i++],LVCFMT_LEFT,200,1);
	m_StatsOne.InsertColumn (12,items[i++],LVCFMT_LEFT,200,1);
	
	char* items2[] = {"", "完成问卷调查数", "血标本采集数", 
						 "治疗的MDR-TB患者数", "菌株运往国家级的数量", "血标本运往国家级的数量", 
						 "首次就诊前支出", "住院阶段支出", "门诊治疗支出"};

	m_StatsTwoCount = sizeof(items2)/sizeof(char*);
	for(i=1; i<m_StatsTwoCount; i++)
	{
		itemsHead.Add(items2[i]);
	}

	m_StatsTwo.SetExtendedStyle (LVS_AUTOARRANGE|LVS_EX_TRACKSELECT|LVS_EX_FLATSB|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_REGIONAL);
	i=0;
	m_StatsTwo.InsertColumn (1,items2[i++],LVCFMT_LEFT,100,1);
	m_StatsTwo.InsertColumn (2,items2[i++],LVCFMT_LEFT,140,1);
	m_StatsTwo.InsertColumn (3,items2[i++],LVCFMT_LEFT,120,1);
	m_StatsTwo.InsertColumn	(4,items2[i++],LVCFMT_LEFT,180,1);
	m_StatsTwo.InsertColumn (5,items2[i++],LVCFMT_LEFT,200,1);
	m_StatsTwo.InsertColumn (6,items2[i++],LVCFMT_LEFT,200,1);
	m_StatsTwo.InsertColumn	(7,items2[i++],LVCFMT_LEFT,140,1);
	m_StatsTwo.InsertColumn (8,items2[i++],LVCFMT_LEFT,120,1);
	m_StatsTwo.InsertColumn (9,items2[i++],LVCFMT_LEFT,120,1);

	UpdateStats();
	UpdateStatsTwo();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

#define UPDATE_COUNTER(item) \
	curItem = pInd->GetItem(item);\
	TRACE(item);\
	TRACE("="+curItem+", curMonth="+curMonth+"\n");\
	if(  curItem != "")\
		totalNumber[j++]++;\
	else j++;\
	if( curItem.Find(curMonth) != -1)\
		curMonthNumber[k++]++;\
	else k++;

void CStatsDialog::OnDatetimechangeCurrentMonth(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_StatsOne.DeleteAllItems();
	m_StatsTwo.DeleteAllItems();
	itemsTotalValue.RemoveAll();
	itemsCurrentMonthValue.RemoveAll();
	UpdateStats();
	UpdateStatsTwo();
}

void CStatsDialog::UpdateStats()
{
	CString curMonth;
	CTime curTime;
	m_MonthCtrl.GetTime(curTime);
	curMonth = curTime.Format("%Y/%m");//Format: 2010/01/01
	
	int count = pIndList->GetSize();
	CIndividual* pInd = NULL;
	int *totalNumber = new int[m_StatsOneCount];
	int *curMonthNumber = new int[m_StatsOneCount];
	int i=0, j=0, k=0;
	
	for(i=0; i<m_StatsOneCount; i++)
	{
		totalNumber[i] = 0;
		curMonthNumber[i] = 0;
	}
	CString curItem;
	CString tempItem;
	int curValue;
	for(i=0; i<count; i++)
	{
		j=0; k=0;
		pInd = pIndList->GetAt(i);
		//患者登记总数
		totalNumber[j++] = count;
		if( pInd->createDate.Find(curMonth) != -1)
		{
			curMonthNumber[k++]++;			
		}else k++;

		//进行痰培养数
		UPDATE_COUNTER("A20");
		//痰培养结果报告数
		UPDATE_COUNTER("A21");
		//培养阳性数
		curItem = pInd->GetItem("A21");
		tempItem = pInd->GetItem("A22");
		if( tempItem == "")
			curValue = 0;
		else
			curValue = atoi(tempItem.Left(1));
		if( curItem != "" && (curValue >=1 && curValue <=5))
			totalNumber[j++]++;
		else j++;
		if( curItem.Find(curMonth) != -1 && (curValue >=1 && curValue <=5))
			curMonthNumber[k++]++;
		else k++;
		//菌型鉴定数
		UPDATE_COUNTER("B1");
		//进行药敏试验数
		UPDATE_COUNTER("B4");
		//药敏试验结果报告数
		UPDATE_COUNTER("B5");
		//诊断MDR-TB患者数
		curItem = pInd->GetItem("B5");
		tempItem = pInd->GetItem("B26");
		if( tempItem == "")
			curValue = 0;
		else
			curValue = atoi(tempItem.Left(1));
		if( curItem != "" && (curValue == 4))
			totalNumber[j++]++;
		else j++;
		if( curItem.Find(curMonth) != -1 && (curValue ==4))
			curMonthNumber[k++]++;
		else k++;
		//诊断广泛耐药患者数
		curItem = pInd->GetItem("B5");
		tempItem = pInd->GetItem("B26");
		if( tempItem == "")
			curValue = 0;
		else
			curValue = atoi(tempItem.Left(1));
		if( curItem != "" && (curValue == 5))
			totalNumber[j++]++;
		else j++;
		if( curItem.Find(curMonth) != -1 && (curValue == 5))
			curMonthNumber[k++]++;
		else k++;
		//纳入研究的MDR-TB患者数
		curItem = pInd->GetItem("B32");
		tempItem = pInd->GetItem("B31");
		if( tempItem == "")
			curValue = 0;
		else
			curValue = atoi(tempItem.Left(1));
		if( curItem != "" && (curValue == 1 || curValue ==2))
			totalNumber[j++]++;
		else j++;
		if( curItem.Find(curMonth) != -1 && (curValue == 1|| curValue ==2))
			curMonthNumber[k++]++;
		else k++;
		//纳入研究的非MDR-TB患者数
		curItem = pInd->GetItem("B32");
		tempItem = pInd->GetItem("B31");
		if( tempItem == "")
			curValue = 0;
		else
			curValue = atoi(tempItem.Left(1));
		if( curItem != "" && (curValue == 3 || curValue ==4))
			totalNumber[j++]++;
		else j++;
		if( curItem.Find(curMonth) != -1 && (curValue == 3|| curValue == 4))
			curMonthNumber[k++]++;
		else k++;
	}
	
	m_StatsOne.InsertItem(0, "累计");
	m_StatsOne.InsertItem(1, curMonth+"新增");
	CString itemText;
	for(i=1; i<m_StatsOneCount; i++)
	{
		itemText.Format("%d", totalNumber[i-1]);
		m_StatsOne.SetItemText(0, i, itemText);
		itemsTotalValue.Add(itemText);
		itemText.Format("%d", curMonthNumber[i-1]);
		m_StatsOne.SetItemText(1, i, itemText);
		itemsCurrentMonthValue.Add(itemText);
	}
	delete[] totalNumber;
	delete[] curMonthNumber;
}

void CStatsDialog::UpdateStatsTwo()
{
	CString curMonth;
	CTime curTime;
	m_MonthCtrl.GetTime(curTime);
	curMonth = curTime.Format("%Y/%m");//Format: 2010/01/01
	
	int count = pIndList->GetSize();
	CIndividual* pInd;
	int totalNumber[10];
	int curMonthNumber[10];
	int i=0, j=0, k=0, m=0;
	
	for(i=0; i<8; i++)
	{
		totalNumber[i] = 0;
		curMonthNumber[i] = 0;
	}
	CString curItem;
	CString tempItem;
	int curValue;
	BOOL isFinished;
//	BOOL hasInput;
	for(i=0; i<count; i++)
	{
		j=0; k=0;
		pInd = pIndList->GetAt(i);
		//完成问卷调查数
		curItem = pInd->GetItem("C3");
		tempItem = pInd->GetItem("C2");
		if( tempItem == "")
			curValue = 0;
		else
			curValue = atoi(tempItem.Left(1));
		if( curItem != "" && (curValue ==2))
			totalNumber[j++]++;
		else j++;
		if( curItem.Find(curMonth) != -1 && (curValue ==2))
			curMonthNumber[k++]++;
		else k++;

		//血标本采集数
		curItem = pInd->GetItem("C6");
		tempItem = pInd->GetItem("C5");
		if( tempItem == "")
			curValue = 0;
		else
			curValue = atoi(tempItem.Left(1));
		if( curItem != "" && (curValue ==2))
			totalNumber[j++]++;
		else j++;
		if( curItem.Find(curMonth) != -1 && (curValue ==2))
			curMonthNumber[k++]++;
		else k++;
		
		//治疗的MDR-TB患者数
		UPDATE_COUNTER("D2");
		
		//菌株运往国家级的数量
		curItem = pInd->GetItem("C19");
		tempItem = pInd->GetItem("C18");
		if( tempItem == "")
			curValue = 0;
		else
			curValue = atoi(tempItem.Left(1));
		if( curItem != "" && (curValue ==2))
			totalNumber[j++]++;
		else j++;
		if( curItem.Find(curMonth) != -1 && (curValue ==2))
			curMonthNumber[k++]++;
		else k++;
		
		//血标本运往国家级的数量
		curItem = pInd->GetItem("C15");
		tempItem = pInd->GetItem("C14");
		if( tempItem == "")
			curValue = 0;
		else
			curValue = atoi(tempItem.Left(1));
		if( curItem != "" && (curValue ==2))
			totalNumber[j++]++;
		else j++;
		if( curItem.Find(curMonth) != -1 && (curValue ==2))
			curMonthNumber[k++]++;
		else k++;
		
		//首次就诊前支出记录表完成数
		isFinished = pInd->CheckIsComplete("E1", "E15");
		if(!isFinished)
		{
			j++;
			k++;
		}
		else
		{
			totalNumber[j++]++;
			curItem = pInd->GetItem("E17");
			if( curItem.Find(curMonth) != -1)
				curMonthNumber[k++]++;
			else
				k++;
		}

		//住院阶段费用支出记录表完成数
		isFinished = pInd->CheckIsComplete("F1", "F18");
		if(!isFinished)
		{
			j++;
			k++;
		}
		else
		{
			totalNumber[j++]++;
			curItem = pInd->GetItem("F20");
			if( curItem.Find(curMonth) != -1)
				curMonthNumber[k++]++;
			else
				k++;
		}
		//门诊治疗支出费用记录表完成数
		isFinished = pInd->CheckIsComplete("G1", "G12");
		if(!isFinished)
		{
			j++;
			k++;
		}
		else
		{
			totalNumber[j++]++;
			curItem = pInd->GetItem("G14");
			if( curItem.Find(curMonth) != -1)
				curMonthNumber[k++]++;
			else
				k++;
		}
	}
	
	m_StatsTwo.InsertItem(0, "累计");
	m_StatsTwo.InsertItem(1, curMonth+"新增");
	CString itemText;
	for(i=1; i<m_StatsTwoCount; i++)
	{
		itemText.Format("%d", totalNumber[i-1]);
		m_StatsTwo.SetItemText(0, i, itemText);
		itemsTotalValue.Add(itemText);
		itemText.Format("%d", curMonthNumber[i-1]);
		m_StatsTwo.SetItemText(1, i, itemText);
		itemsCurrentMonthValue.Add(itemText);
	}		

}

void CStatsDialog::OnExport() 
{
	if( MessageBox("确定导出数据到Excel?","提示",MB_YESNO|MB_ICONQUESTION|MB_SYSTEMMODAL) == IDNO )
	{
		return;
	}
	
	CWaitCursor cursorWait;

	CString sOutputFile = g_Tools.GetRunPath()+title+".xls";
	CFile filetry;
	if( filetry.Open(sOutputFile,CFile::modeReadWrite|CFile::modeCreate) == FALSE )
	{
		AfxMessageBox("无法打开文件："+sOutputFile+"，如该文件已打开，请先关闭!");
		return;
	}
	else
	{
		filetry.Close();
		CFile::Remove(sOutputFile);
	}

	CSpreadSheet SS1(sOutputFile,"Sheet1",false);
	SS1.BeginTransaction();
	SS1.AddHeaders(itemsHead);
	SS1.AddRow(itemsTotalValue);
	SS1.AddRow(itemsCurrentMonthValue);
	SS1.Commit();
	AfxMessageBox(" 已经导出到: "+sOutputFile);
}
