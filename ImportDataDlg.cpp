// ImportDataDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TUI.h"
#include "ImportDataDlg.h"
#include "CSpreadSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImportDataDlg dialog


CImportDataDlg::CImportDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImportDataDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImportDataDlg)
	//}}AFX_DATA_INIT
}


void CImportDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImportDataDlg)
	DDX_Control(pDX, IDC_IND_OK_LIST, m_IndOKListCtrl);
	DDX_Control(pDX, IDC_IMPORT_PROGRESS, m_LoadDataProcess);
	DDX_Control(pDX, IDC_CONFLICT_INFO_LIST, m_ConflictList);
	DDX_Control(pDX, IDC_IND_LIST, m_IndList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImportDataDlg, CDialog)
	//{{AFX_MSG_MAP(CImportDataDlg)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CONFIRM, OnConfirm)
	ON_LBN_SELCHANGE(IDC_IND_LIST, OnSelchangeIndList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportDataDlg message handlers

void CImportDataDlg::OnOK() 
{
	// TODO: Add extra validation here
	return;
	CDialog::OnOK();
}

void CImportDataDlg::OnCancel() 
{
	int count = m_IImportList.GetSize();
	for(int i=0; i<count; i++)
		delete m_IImportList.GetAt(i);
	m_IImportList.RemoveAll();
	CDialog::OnCancel();
}

BOOL CImportDataDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetWindowText("导入“"+strTownName+"”数据, Excel文件为："+m_ExcelFile);
	SetTimer(1, 100, NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CImportDataDlg::LoadExcelRecs()
{
	CStringArray sRecStrs;
	int nIndTatal = 0;
	BOOL isCheckOK = TRUE;

	CWaitCursor cursorWait;
	
	m_IndList.ResetContent();
	m_IdMap.RemoveAll();
	
	GetDlgItem(IDC_STATIC_TIP)->ShowWindow(SW_SHOW);
	m_LoadDataProcess.ShowWindow(SW_SHOW);
	
	CSpreadSheet SS1(m_ExcelFile,"Sheet1",false);
	nIndTatal = SS1.GetTotalRows();
	
	CString tip;
	SetDlgItemText(IDC_STATIC_TIP, "导入数据中..");
	m_LoadDataProcess.ShowWindow(SW_SHOW);
	m_LoadDataProcess.SetRange(0,nIndTatal); //Row 1 is the header
	m_LoadDataProcess.SetStep(1);
	m_LoadDataProcess.SetPos(1);
	
	int i=0,j=0;
	UINT iId=0;
	CString strId="";
	CString strName="";
	CString tempStr;
	BOOL isEmpty;
	iIndex = 0;
	int itemCount;
	CString errorStr;
	for(i=2; i<=nIndTatal; i++)
	{
		isEmpty = TRUE;
		SS1.ReadRow(sRecStrs,i);
		itemCount = sRecStrs.GetSize();
		if ( itemCount != 73)
		{
			errorStr.Format("第%d行: ", i);
			m_IndList.AddString(errorStr+"无法导入");
			errorStr.Format("(%c)", (itemCount-1+'A'));
			errorStr = CString(gAItemInfo[itemCount-1].name) +errorStr + "格式有错误!";
			ConflictInfo[iIndex].Add(errorStr);
			iIndex++;
			continue;
		}
		for(j=0; j<sRecStrs.GetSize(); j++)
		{
			tempStr = sRecStrs[j];
			tempStr.Replace(".0", "");
			tempStr.Replace(" 00:00:00", "");
			tempStr.Replace("\n", "");
			tempStr.TrimLeft(" ");
			tempStr.TrimRight(" ");
			if (tempStr != "") isEmpty = FALSE;
			if (tempStr.GetLength() >100) tempStr = tempStr.Left(100);
			sRecStrs[j] = tempStr;
		}
		if (isEmpty) {m_LoadDataProcess.StepIt(); continue;}

		strId = sRecStrs[0];
		strName = sRecStrs[2];

		pInd = new CIndividual;
		if(!VerifyInput(i, sRecStrs))
		{
			errorStr.Format("第%d行: ", i);
			m_IndList.AddString(errorStr+ strId+"("+strName+")......有冲突!");
			iIndex++;
			isCheckOK = FALSE;
			delete pInd;
			pInd = NULL;
			continue;
		}
		m_IndOKListCtrl.AddString(strId+"("+strName+")......检查成功!");
		pInd->createDate = curDate;
		iId = atoi(sRecStrs[0]);
		m_IdMap.SetAt((void*)iId, (void*)pInd);
		m_IImportList.Add(pInd);
		tip.Format("检查记录: %d...",iId);
		SetDlgItemText(IDC_STATIC_TIP, tip);
		GetDlgItem(IDC_STATIC_TIP)->UpdateWindow();
		m_LoadDataProcess.StepIt();
	}
	GetDlgItem(IDC_STATIC_TIP)->ShowWindow(SW_HIDE);
	m_LoadDataProcess.ShowWindow(SW_HIDE);
	if( isCheckOK == TRUE)
	{
		GetDlgItem(IDC_CONFIRM)->EnableWindow(TRUE);	
	}
}

void CImportDataDlg::OnTimer(UINT nIDEvent) 
{
	if( nIDEvent == 1 )
	{
		KillTimer(1);
		LoadExcelRecs();
	}
	CDialog::OnTimer(nIDEvent);
}


void CImportDataDlg::OnConfirm() 
{
	CDialog::OnOK();
}

void CImportDataDlg::OnSelchangeIndList() 
{
	m_ConflictList.ResetContent();
	int iSel = m_IndList.GetCurSel();
	for(int i=0; i<ConflictInfo[iSel].GetSize(); i++)
	{
		m_ConflictList.AddString(ConflictInfo[iSel].GetAt(i));
	}
}

#define IMPORT_DATA(item)\
	if(recStrs[i] == "9999"){\
		pInd->SaveData(item, ""); \
		i++;\
	}else if (recStrs[i] == "8888"){\
		pInd->SetUnessaryData(item, item);\
		i++;\
	}else\
		pInd->SaveData(item, recStrs[i++]);

#define IMPORT_DATA_COMBO(item, selItems)\
	if(recStrs[i] == "不清楚" || recStrs[i] == "不详" || recStrs[i] == "9999" || recStrs[i] == "8888"){\
		j=0;\
	}else{\
		count = sizeof(selItems)/sizeof(char*);\
		for(j=0; j<count; j++){\
			if(recStrs[i] == selItems[j])\
				break;\
		}\
	}\
	if (j==count){\
		if(i>=26)\
			errorStr.Format("%c%c", ((i/26)-1+'A'),(i%26+'A'));\
		else\
			errorStr.Format("%c", (i%26+'A'));\
		errorStr = CString(gAItemInfo[i].name)+ "(" +errorStr+")"+" 输入的内容: “"+recStrs[i]+"”没有相应的选项!";\
		pInfo->Add(errorStr);\
		errorStr =  "正确的选项有: ";\
		for(j=1; j<count; j++){\
			if (j!=count-1)\
				errorStr = errorStr + selItems[j] + "，";\
			else\
				errorStr = errorStr + selItems[j] + "。";\
		}\
		pInfo->Add(errorStr);\
		pInd->SaveData(item, "");\
		i++;\
	}else{\
		if(j==0){\
			if (recStrs[i] == "8888")\
				pInd->SetUnessaryData(item, item);\
			else\
				pInd->SaveData(item, "");\
			i++;\
		}else{\
			itemText.Format("%d:",j);\
			pInd->SaveData(item, itemText+recStrs[i++]);\
		}\
	}

#define IMPORT_DATA_DATE(item)\
	if (recStrs[i] == ""){\
		pInd->SaveData(item, "");\
		i++;\
	}else if (recStrs[i].Find("9999") >=0 ){\
		pInd->SaveData(item, "");\
		i++;\
	}else if (recStrs[i].Find("8888") >=0 ){\
		pInd->SetUnessaryData(item, item);\
		i++;\
	}else{\
		nYear = -1; nMonth = -1; nDay = -1;\
		recStrs[i].Replace("-", "/");\
		sscanf(recStrs[i].GetBuffer(100), "%d/%d/%d", &nYear, &nMonth, &nDay);\
		if ( (nYear<=1900 || nYear >= 2100) || (nMonth<=0 || nMonth >12) || (nDay<=0 || nDay >31)) {\
			if(i>=26)\
				errorStr.Format("%c%c", ((i/26)-1+'A'),(i%26+'A'));\
			else\
				errorStr.Format("%c", (i%26+'A'));\
			errorStr = CString(gAItemInfo[i].name)+ "(" +errorStr+")"+" 日期:" + recStrs[i] + "不正确";\
			pInfo->Add(errorStr);\
			i++;\
		}else{\
			pInd->SaveData(item, recStrs[i++]);\
		}\
	}

#define CHECK_DATE(start, end, msg)\
	dateA = pInd->GetItem(start);\
	dateB = pInd->GetItem(end);\
	if (dateA != "" && dateB != ""){\
		sscanf(dateA.GetBuffer(100), "%d/%d/%d", &nYear, &nMonth, &nDay);\
		sDateA = CTime(nYear, nMonth, nDay, 0, 0, 0);\
		sscanf(dateB.GetBuffer(100), "%d/%d/%d", &nYear, &nMonth, &nDay);\
		sDateB = CTime(nYear, nMonth, nDay, 0, 0, 0);\
		if (sDateA > sDateB){\
			errorStr = CString(msg)+"结果报告日期("+dateB+")不应早于开始日期("+dateA+")!";\
			pInfo->Add(errorStr);\
		}\
	}


//Check All Item Valid
BOOL CImportDataDlg::VerifyInput(UINT nIndex, CStringArray &recStrs)
{
	int nItem = nIndex-2;
	CStringArray* pInfo = &ConflictInfo[iIndex];
	CString errorStr;
	CString itemText;
	void *pData;
	int i, j, count;
	i=0;
	int nYear, nMonth, nDay;
	CString dateA, dateB;
	CTime sDateA, sDateB;
	for(;;)
	{
		UINT bkID;
		//A1: ID
		int iId = atoi(recStrs[i]);
		if (!CIndividual::IsIDValid(iId)) 
		{
			itemText.Format("ID: %d无效!", iId);
			pInfo->Add(itemText);
			break;
		}
		if (CData::GetData(iId) != NULL)
		{
			errorStr.Format("ID:%d在原数据库中已存在", iId);
			pInfo->Add(errorStr);
			break;
		}
		pData = NULL;
		m_IdMap.Lookup((void*)iId, pData);
		if ( pData != NULL)
		{
			errorStr.Format("ID:%d在导入的数据中已存在", iId);
			pInfo->Add(errorStr);
			break;
		}
		itemText.Format("%d", iId);
		recStrs[i] = itemText;
		pInd->SetId(iId);

		IMPORT_DATA("A1");
		IMPORT_DATA("A2");
		IMPORT_DATA("A3");
		//A4: 姓别
		char* A4[]  = {"", "男", "女", "不详"};
		IMPORT_DATA_COMBO("A4", A4);
		IMPORT_DATA("A5");
		IMPORT_DATA("A6");
		IMPORT_DATA("A7");
		IMPORT_DATA("A8");
		IMPORT_DATA_DATE("A9");
		IMPORT_DATA_DATE("A10");
		IMPORT_DATA_DATE("A11");
		IMPORT_DATA_DATE("A12");
		//A12“开始一线药治疗日期”为可选项
		if (pInd->GetItem("A12") == "")
		{
			pInd->itemStatus[CIndividual::GetItemIndex("A12")] = 2;
		}
		char* A13[] = {"", "高危人群", "非高危人群涂阳", "涂阴"};
		IMPORT_DATA_COMBO("A13", A13);
		char *A14[] = {"", "初治","复治", "不清楚"};
		IMPORT_DATA_COMBO("A14", A14);
		char *A15[] = {"","新患者", "复发", "返回", "初治失败", "复治失败", "初治3月末阳性", "其他", "涂阴", "不清楚"};
		IMPORT_DATA_COMBO("A15", A15);
		char *A16[] = {"","新患者", "既往仅使用一线药", "既往使用过一线和二线抗结核药", "不清楚"};
		if (recStrs[i] == "既往使用过一线和二线药")
		{
			recStrs[i] = "既往使用过一线和二线抗结核药";
		}
		IMPORT_DATA_COMBO("A16", A16);
		IMPORT_DATA_DATE("A17");
		IMPORT_DATA_DATE("A18");
		CHECK_DATE("A17", "A18", "涂片");

		char *A19[] = {"", "小于1+", "1+", "2+", "3+", "4+", "阴性"};
		IMPORT_DATA_COMBO("A19", A19);

		//1102:
		IMPORT_DATA_DATE("A20");
		IMPORT_DATA_DATE("A21");
		CHECK_DATE("A20", "A21", "痰培养");

		char *A22[] = {"", "小于1+", "1+", "2+", "3+", "4+", "阴性", "污染"};
		IMPORT_DATA_COMBO("A22", A22);
		
		//1201:
		bkID = g_CurIId;
		g_CurIId = iId;
		if(CheckTable1201())
		{
			IMPORT_DATA_DATE("B1");
			IMPORT_DATA_DATE("B2");
			CHECK_DATE("B1", "B2", "菌型鉴定");
			char *B3[] = {"", "结核分枝杆菌", "非结核分枝杆菌"};
			IMPORT_DATA_COMBO("B3", B3);
		}
		else
		{
			pInd->SetUnessaryData("B1", "B3");
			i=i+3;
		}

		//1202:
		char *B6_25[] = {"", "敏感", "耐药", "污染", "无法判读"};
		if(CheckTable1202())
		{
			IMPORT_DATA_DATE("B4");
			IMPORT_DATA_DATE("B5");
			CHECK_DATE("B4", "B5", "药敏");
			IMPORT_DATA_COMBO("B6", B6_25);
			IMPORT_DATA_COMBO("B7", B6_25);
			IMPORT_DATA_COMBO("B8", B6_25);
			IMPORT_DATA_COMBO("B9", B6_25);
			IMPORT_DATA_COMBO("B10", B6_25);
			IMPORT_DATA_COMBO("B11", B6_25);
		}
		else
		{
			pInd->SetUnessaryData("B4", "B11");
			i=i+8;
		}

		//1203:
		if(CheckTable1203())
		{
			IMPORT_DATA_DATE("B12");
			IMPORT_DATA_DATE("B13");
			CHECK_DATE("B12", "B13", "HAIN");
			IMPORT_DATA_COMBO("B14", B6_25);
			IMPORT_DATA_COMBO("B15", B6_25);
		}
		else
		{
			pInd->SetUnessaryData("B12", "B15");
			i=i+4;
		}

		//1204
		if(CheckTable1204())
		{
			IMPORT_DATA_DATE("B16");
			IMPORT_DATA_DATE("B17");
			CHECK_DATE("B16", "B17", "博奥生物芯片");
			IMPORT_DATA_COMBO("B18", B6_25);
			IMPORT_DATA_COMBO("B19", B6_25);
		}
		else
		{
			pInd->SetUnessaryData("B16", "B19");
			i=i+4;
		}
		//1205
		if(CheckTable1205())
		{
			IMPORT_DATA_DATE("B20");
			IMPORT_DATA_DATE("B21");
			CHECK_DATE("B20", "B21", "BACTECH960快培");
			IMPORT_DATA_COMBO("B22", B6_25);
			IMPORT_DATA_COMBO("B23", B6_25);
			IMPORT_DATA_COMBO("B24", B6_25);
			IMPORT_DATA_COMBO("B25", B6_25);
		}
		else
		{
			pInd->SetUnessaryData("B20", "B25");
			i=i+6;
		}
		
		//1206: 患者纳入
		if(CheckTable1206())
		{
			char* B26[] = {"", "非耐药", "单耐药", "多耐药", "耐多药", "广泛耐药"};
			IMPORT_DATA_COMBO("B26", B26);
			if( j == 4 || j == 5)
			{
				IMPORT_DATA_DATE("B27");
				IMPORT_DATA("B28");
			}
			else
			{
				pInd->SetUnessaryData("B27", "B28");
				i=i+2;
			}
			
			//翻译不同输入
			if (recStrs[i] == "是")
			{
				recStrs[i] = "符合";
			}
			if (recStrs[i] == "否")
			{
				recStrs[i] = "不符合";
			}
			char* B29[] = {"", "不符合", "符合"};
			IMPORT_DATA_COMBO("B29", B29);
			if( j == 0 || j == 1)
			{
				pInd->SetUnessaryData("B30", "B32");
				i=i+3;
			}
			else if(j == 2)
			{
				if (recStrs[i] == "是")
				{
					recStrs[i] = "同意";
				}
				if (recStrs[i] == "否")
				{
					recStrs[i] = "不同意";
				}
				char* B30[] = {"", "不同意", "同意"};
				IMPORT_DATA_COMBO("B30", B30);
				if( j == 2)
				{
					//初治非耐多药肺结核患者
					char* B31[] = {"", "初治耐多药肺结核患者", "复治耐多药肺结核患者", "初治非耐多药肺结核患者", "复治非耐多药肺结核患者", "未入组"};
					IMPORT_DATA_COMBO("B31", B31);
					if( j >=1 && j <=4)
					{
						IMPORT_DATA_DATE("B32");
					}
					else
					{
						pInd->SetUnessaryData("B32", "B32");
						i=i+1;
					}
				}
				else
				{
					pInd->SetUnessaryData("B31", "B32");
					i=i+2;
				}
			}
		}
		else
		{
			pInd->SetUnessaryData("B26", "B32");
			i=i+7;
		}

		//1301
		if(CheckTable1301())
		{
			char* C1_11[] = {"", "否", "是"};
			IMPORT_DATA_COMBO("C1", C1_11);
			if( j != 2) //非"是", C2-C9 DISABLED
			{
				pInd->SaveDataToEmpty("C2", "C9");
				i=i+8;
			}
			else
			{
				IMPORT_DATA_COMBO("C2", C1_11);
				if(j == 2)
				{
					IMPORT_DATA_DATE("C3");
					IMPORT_DATA_COMBO("C4", C1_11);
				}
				else
				{
					pInd->SaveDataToEmpty("C3", "C4");
					i=i+2;
				}
				IMPORT_DATA_COMBO("C5", C1_11);
				if( j == 2)
				{
					IMPORT_DATA_DATE("C6");
					char* C7[] = {"", "1", "2"};
					IMPORT_DATA_COMBO("C7", C7);
					IMPORT_DATA("C8");
					IMPORT_DATA_COMBO("C9", C1_11);
				}
				else
				{
					pInd->SaveDataToEmpty("C6", "C9");
					i=i+4;
				}
			}
			char* C10[] = {"", "省级", "地市级"};
			IMPORT_DATA_COMBO("C10", C10);
			if( j != 1)//省级
			{
				pInd->SetUnessaryData("C16", "C19");
			}
			else
			{
				pInd->SetNessaryData("C16", "C19");
			}
			IMPORT_DATA_COMBO("C11", C1_11);
		}
		else
		{
			pInd->SetUnessaryData("C1", "C11");
			i=i+11;
		}
		
		//1302:
		char* C12_19[] = {"", "否", "是"};
		if(CheckTable1302())
		{
			IMPORT_DATA_COMBO("C12", C12_19);
			if (j == 2) //是
			{
				IMPORT_DATA_DATE("C13");
			}
			else//否或尚未确定
			{
				pInd->SaveData("C13", "");
				i=i+1;
			}
			IMPORT_DATA_COMBO("C14", C12_19);
			if (j == 2)//是
			{
				IMPORT_DATA_DATE("C15");
			}
			else//否或尚未确定
			{
				pInd->SaveData("C15", "");
				i=i+1;
			}
		}
		else
		{
			pInd->SetUnessaryData("C12", "C15");
			i=i+4;
		}

		//1303:
		if(CheckTable1303())
		{
			IMPORT_DATA_COMBO("C16", C12_19);
			if (j == 2) //是
			{
				IMPORT_DATA_DATE("C17");
			}
			else//否或尚未确定
			{
				pInd->SaveData("C17", "");
				i=i+1;
			}
			IMPORT_DATA_COMBO("C18", C12_19);
			if (j == 2)//是
			{
				IMPORT_DATA_DATE("C19");
			}
			else//否或尚未确定
			{
				pInd->SaveData("C19", "");
				i=i+1;
			}
		}
		else
		{
			pInd->SetUnessaryData("C16", "C19");
			i=i+4;
		}
		ASSERT(i==pInd->GetItemIndex("C19")+1);

		//No Data Imported from Here, but should check if data are necessary
		if(!CheckTable1401())
		{
			pInd->SetUnessaryData("D1", "D5");	
		}

		if(!CheckTable1402_25())
		{
			pInd->SetUnessaryData("D6", "D587");
		}

		if(!CheckTable1426())
		{
			pInd->SetUnessaryData("D588", "D589");
		}
		
		if(!CheckTable2100())
		{
			pInd->SetUnessaryData("E1", "E17");
		}
		
		if(!CheckTable2200())
		{
			pInd->SetUnessaryData("F1", "F20");
		}

		if(!CheckTable2300())
		{
			pInd->SetUnessaryData("G1", "G14");
		}
		g_CurIId = bkID;
		break;
	}
	if(pInfo->GetSize()>0)
		return FALSE;

	pInd->UpdateStatus(FALSE);
	return TRUE;
}