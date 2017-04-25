// Data.cpp: implementation of the CData class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CData,CObject,1)
#define SERIALIZE(object) \
	for(int j=0; j<object.GetSize(); j++) \
		object.GetAt(j)->Serialize(ar); \

void CData::SerializeConfig(CArchive &ar)
{
	if(ar.IsLoading())
	{
        ar>>cSel>>tSel>>citySel>>typeSel;
    }
	else
	{
		ar<<cSel<<tSel<<citySel<<typeSel;
	}
}


void CData::Serialize(BOOL isSaving)
{
	int i=0 ,j=0;
	CArchive *pAr = NULL;
	CCity* pCity = NULL;
	CTown* pTown = NULL;
	CTown* pTown91 = NULL;
	CTown* pTown92 = NULL;
	CString filename;
	CString exportDir = g_Tools.GetRunPath()+"结核病发病模式研究数据录入软件-数据\\";

	//创建数据存放目录
	if (!g_Tools.IsDirExist(exportDir))
	{
		g_Tools.CreateDir(exportDir);
	}

	//保存数据: 按每个县区生成一个data.<id>文件
	if (isSaving)
	{
		for(i=0; i<m_CList.GetSize(); i++)
		{
			pCity = m_CList.GetAt(i);
			//健康对照表
			pTown91 = (CTown*)CData::GetData(CID(pCity->id, 91, 0).GetId(TUI_ID_TOWN_TYPE)); //pCity->id*100+91);
			pTown92 = (CTown*)CData::GetData(CID(pCity->id, 92, 0).GetId(TUI_ID_TOWN_TYPE)); //pCity->id*100+92);
			if(pTown91 || pTown92)
			{
				filename.Format("data.%d", CID(pCity->id, 0, 0).GetId(TUI_ID_TOWN_TYPE)); //pCity->id*100);
				filename = exportDir+filename;
				pAr = g_Tools.GetArchive(filename, TRUE, FALSE);
				if (pAr == NULL)
				{
					AfxMessageBox("无法保存“健康对照表”信息!");
					continue;
				}
				if (pTown91 && pTown92)
					g_bTown91or92 = TRUE;
				pCity->Serialize(*pAr);
				g_bTown91or92 = FALSE;
				if (pTown91)
				{
					pTown91->Serialize(*pAr);
					pProgress->StepIt();
				}
				if (pTown92)
				{
					pTown92->Serialize(*pAr);
					pProgress->StepIt();
				}
				g_Tools.CloseArchive();
			}

			for(j=0; j<pCity->m_TList.GetSize(); j++)
			{
				pTown = pCity->m_TList.GetAt(j);
				if( CID(pTown->id).GetCode(TUI_ID_TOWN_TYPE) >90) continue; //不包括健康对照表
				filename.Format("data.%d", pTown->id);
				filename = exportDir+filename;
				pAr = g_Tools.GetArchive(filename, TRUE, FALSE);
				if (pAr == NULL)
				{
					AfxMessageBox("无法保存“"+pTown->name+"”的信息!");
					continue;
				}
				pCity->Serialize(*pAr);
				pTown->Serialize(*pAr);
				g_Tools.CloseArchive();
				pProgress->StepIt();
			}
		}
		return;
	}
	
	//Load Data
	CStringArray dataFiles;
	dataFiles.RemoveAll();
	g_Tools.GetDirFiles(exportDir, dataFiles);

	int townNo = 0;
	CCity *pCityInData = NULL;
	for(i=0; i<dataFiles.GetSize(); i++)
	{
		filename = dataFiles.GetAt(i);
		pAr = g_Tools.GetArchive(filename, FALSE, FALSE);
		if (pAr == NULL)
		{
			AfxMessageBox("数据文件: "+dataFiles.GetAt(i)+" 无效!");
			continue;
		}
		pCity = new CCity();
		pCity->Serialize(*pAr);
		townNo = pCity->townNo;

		pCityInData = (CCity*)CData::GetData(pCity->id); //不能连续调用两次GetData
		if (pCityInData == NULL)
		{
			m_CList.Add(pCity);
			pCity->SetId(pCity->id); 
		}
		else
		{
			delete pCity;
			pCity = NULL;
			pCity = pCityInData;
			ASSERT(pCity);
		}
		for(j=0; j<townNo; j++)
		{
			pTown = new CTown();
			pTown->Serialize(*pAr);
			pTown->pCity = pCity;
			pCity->m_TList.Add(pTown);
		}
		g_Tools.CloseArchive();
		pProgress->StepIt();
	}
}

IMPLEMENT_SERIAL(CCity,CObject,1)

void CCity::Serialize(CArchive &ar)
{
	if(ar.IsLoading())
	{
		ar>>townNo>>id>>name;
	}
	else
	{
		int townNo = 1; //按一个县区保存一个文件，所以townNo=1;
		if (g_bTown91or92)
			townNo = 2;
		ar<<townNo<<id<<name;
	}
}


IMPLEMENT_SERIAL(CTown,CObject,1)

void CTown::Serialize(CArchive &ar)
{
	if(ar.IsLoading())
	{
		CIndividual *pInd;
		int size;
		ar>>size>>id>>name>>status;
		SetId(id);
		for(int i=0; i<size; i++)
		{
			pInd = new CIndividual();
			pInd->pTown = this;
			m_IList.Add(pInd);
		}
	}
	else
	{
		ar<<m_IList.GetSize()<<id<<name<<status;
	}

	SERIALIZE(m_IList)
}

IMPLEMENT_SERIAL(CIndividual,CObject,1)

void CIndividual::Serialize(CArchive &ar)
{
	int i=0;
	if(ar.IsLoading())
	{
		ar>>id>>name;
		ar>>createDate;
		for(i=0; i<750; i++)
		{
			ar>>items[i];
			ar>>itemStatus[i];
		}
		//Run the upgrade
		if(g_DataVer == 0 && g_SWVer == 1)
		{
			WORD wCity, wTown, wInd;
			wInd = id%1000;
			id = id/1000;
			wTown = id%100;
			wCity = id/100;
			id = CID(wCity,wTown, wInd).GetId(TUI_ID_IND_TYPE);
			CString sNewId;
			sNewId.Format("%d", id);
			items[0] = sNewId;
		}
		SetId(id);
		UpdateStatus(FALSE);
	}
	else
	{
		ar<<id<<name;
		ar<<createDate;
		for(i=0; i<750; i++)
		{
			ar<<items[i];
			ar<<itemStatus[i];
		}
	}
}

CTypedPtrMap<CMapPtrToPtr, void*, CDataCommon*> CData::m_Map;
CTypedPtrArray<CObArray, CCity*>  CData::m_CList;
int CData::cSel;
int CData::tSel;
int CData::typeSel;
int CData::citySel;

void CData::MapData(UINT id, CDataCommon* pData)
{
	CDataCommon *pOldData;
	if (!m_Map.Lookup((void*)id, pOldData))
	{
		m_Map.SetAt((void*)id, pData);
	}
	else
	{
		CString msg;
		msg.Format("CData::MapData: ReAdd Data, id=%d!", id);
		LogInfo(msg);
	}
}


CCity* CData::CreateCity(UINT id)
{
	ASSERT( (id>0) && (id<10) );

	CCity *pCity = NULL;
	for(UINT i=0; i<gCTinfoSize; i++)
	{
		if( id == gCTinfo[i].id)
		{
			pCity = new CCity();
			pCity->SetId(id);
			pCity->name = gCTinfo[i].name;
			m_CList.Add(pCity);
			pCity->tableIndex = i;
			break;
		}
	}
	
	ASSERT(pCity);
	return pCity;
}

CDataCommon* CCity::CreateSub(UINT tId)
{
	CTown *pTown = new CTown();
	pTown->SetId(tId);
	UINT cId = CID(tId).GetId(TUI_ID_CITY_TYPE);
	for(UINT j=0; j<gCTinfoSize; j++)
	{
        if( gCTinfo[j].id == cId )
		{
            for(UINT k=0; k<gCTinfo[j].townsize; k++)
            {
                if( gCTinfo[j].pTown[k].id == tId )
                {
                    pTown->name = gCTinfo[j].pTown[k].name;
                    break;
                }
            }
			break;
		}
	}
	pTown->pCity = this;
	m_TList.Add(pTown);
	return (CDataCommon*)pTown;
}

CDataCommon* CTown::CreateSub(UINT iId)
{
	CIndividual *pInd = new CIndividual();
	CString tempStr;
	pInd->SetId(iId);
	if(CID(iId).GetCode(TUI_ID_TOWN_TYPE) <90) //Ind ID
	{
		tempStr.Format("%d", iId);
		pInd->SaveData("A1", tempStr);
	}
	else //Research ID
	{
		tempStr.Format("%d", CIndividual::ConvertToResearchId(iId));
		pInd->SaveData("H1", tempStr);
	}
	tempStr.Format("%d", iId);
	pInd->items[0] = tempStr;
	pInd->pTown = this;
	m_IList.Add(pInd);
	return (CDataCommon*)pInd;	
}

void CData::RemoveTown(CTown *pTown)
{
    if( pTown == NULL )
    {
        LogInfo("RemoveTown: pTown == NULL");
        return;
    }
    
	CCity* pCity = pTown->pCity;
	CIndividual* pInd = NULL;

    int total_C = pCity->m_TList.GetSize();
	if( pCity )
	{
		//Remove from City
		for(int i=0; i<total_C; i++)
		{
			if( pCity->m_TList.GetAt(i)->id == pTown->id )
			{
				pCity->m_TList.RemoveAt(i);
				break;				
			}
		}
        if( i == total_C )
        {
            CString msg;
            msg.Format("RemoveTown: pTown(id=%d) not found!", pTown->id);
            LogInfo(msg);
            return;            
        }
        
		delete pTown;

		//No Site, remove city
		if( pCity->m_TList.GetSize() ==  0 )
		{
			for( i=0; i<m_CList.GetSize(); i++)
			{	
				if( m_CList.GetAt(i)->id == pCity->id )
				{
					m_CList.RemoveAt(i);
				}
			}	
		}
	}
    else
    {
        LogInfo("RemoveTown::pCity == NULL");
    }
}

void CData::RemoveInd(CIndividual* pInd)
{
    if( pInd == NULL )
    {
        LogInfo("RemoveInd: pInd == NULL");
        return;
    }
    
	CTown* pTown = pInd->pTown;
    int total_I = pTown->m_IList.GetSize();
    
	if(pTown)
	{
		for(int i=0; i<total_I; i++)
		{
			if( pTown->m_IList.GetAt(i)->id == pInd->id )
			{
				pTown->m_IList.RemoveAt(i);
				break;
			}
		}
        if( i == total_I )
        {
            CString msg;
            msg.Format("RemoveInd: pInd(id=%d) not found!", pInd->id);
            LogInfo(msg);
        }
        else
        {
    		delete pInd;
        }
	}
    else
    {
        LogInfo("RemoveInd: pTown=NULL!");
    }
}


void CData::DeleteAll()
{
	CCity* pCurC;
	CTown* pCurT;
	CIndividual* pCurI;
	int i;

	for(i=0; i<m_CList.GetSize(); i++)
	{
		pCurC = m_CList.GetAt(i);
		for(int j=0; j<pCurC->m_TList.GetSize(); j++)
		{
			pCurT = pCurC->m_TList.GetAt(j);
			for(int k=0; k<pCurT->m_IList.GetSize(); k++)
			{
				pCurI = pCurT->m_IList.GetAt(k);
				delete pCurI;
			}
			delete pCurT;
		}
		delete pCurC;
	}
}


void LogInfo(CString msg)
{
    CString outMsg = msg+"\n";
	TRACE(outMsg);
}


int CData::GetTotalTown()
{
	int i;
	int nTotal = 0;
	
	CCity* pCity;
	
	for(i=0; i<m_CList.GetSize(); i++)
	{
		pCity = m_CList.GetAt(i);
		nTotal+=pCity->m_TList.GetSize();
	}
	return nTotal;
}

int CData::GetTotoalInd()
{
	int i, j;
	int nTotal = 0;
	
	CCity* pCity;
	CTown* pTown;

	for(i=0; i<m_CList.GetSize(); i++)
	{
		pCity = m_CList.GetAt(i);
		for( j=0; j<pCity->m_TList.GetSize(); j++)
		{
			pTown = pCity->m_TList.GetAt(j);
			nTotal+=pTown->m_IList.GetSize();
		}
	}
	return nTotal;
}

CTown::~CTown()
{
}

void CData::RemoveMap(UINT id)
{
	CDataCommon *pOldData;
	if (m_Map.Lookup((void*)id, pOldData))
	{
		m_Map.RemoveKey((void*)id);
	}
	else
	{
		LogInfo("CData::RemoveMap: No Data to remove map!");
	}
}

CDataCommon* CData::GetData(UINT id)
{
	CDataCommon* pData = NULL;
	m_Map.Lookup((void*)id, pData);
	return pData;
}

CDataCommon* CData::CreateData(UINT id)
{
	//Can be removed when it's stable
	CDataCommon* pData = GetData(id);
	if(pData) 
	{
		LogInfo("Warning! Try to Create Data that already exists!");
		return pData;
	}

	CID sId(id);
	UINT cId, tId;

	CDataCommon* pParent = NULL;
	CDataCommon* pCity = NULL;
	switch(sId.GetIdType())
	{
	case TUI_ID_CITY_TYPE:
		return (CDataCommon*)CreateCity(id);
		break;
	case TUI_ID_TOWN_TYPE:
		cId=sId.GetId(TUI_ID_CITY_TYPE);
		pParent = GetData(cId);
		if (pParent == NULL)
		{
			pParent = (CDataCommon*)CreateCity(cId);
		}
		return pParent->CreateSub(id);
	case TUI_ID_IND_TYPE: //Ind & ResearchId
		cId=sId.GetId(TUI_ID_CITY_TYPE);
		tId=sId.GetId(TUI_ID_TOWN_TYPE);
		pCity = GetData(cId);
		if (pCity == NULL)
		{
			pCity = (CDataCommon*)CreateCity(cId);
		}
		pParent = GetData(tId);
		if (pParent == NULL)
		{
			pParent = (CDataCommon*)pCity->CreateSub(tId);
		}
		return pParent->CreateSub(id);
	default:
		ASSERT(0);
		break;
	}
	return NULL;
}

UINT CData::GetNewIndId(UINT tId)
{
	if (tId == 0) return 0;

	UINT iId;
	CID sId(tId);
	UINT nMaxIndCode = sId.GetMaxCode(TUI_ID_IND_TYPE);
	for(WORD i=1; i<nMaxIndCode; i++)
	{
		sId.SetCode(TUI_ID_IND_TYPE, i);
		iId = sId.GetId(TUI_ID_IND_TYPE);
		if (GetData(iId) == NULL)
		{
			return iId;
		}
	}
	return 0; //No Id left
}


UINT CData::GetNewResearchId(UINT tId)
{
	UINT iId;
	CID sId(tId);
	for(int i=1; i<100; i++)   //健康调查只有两位数
	{
		sId.SetCode(TUI_ID_IND_TYPE, i);
		iId = sId.GetId(TUI_ID_IND_TYPE);
		if (GetData(iId) == NULL)
		{
			return iId;
		}
	}
	return 0; //No Id left
}


int CIndividual::GetItemIndex(CString item)
{
	int tablesize[] = {
		22, 32, 19, 580, 17, 20, 14, 27
	};
	char tableNo = item.GetAt(0);
	int tableValue = tableNo-'A';
	CString itemNo = item.Mid(1);
	int itemValue = 0;
	sscanf(itemNo.GetBuffer(100), "%d", &itemValue);
	
	int itemIndex = 0;
	for(int i=0; i<tableValue; i++)
	{
		itemIndex+=tablesize[i];
	}
	itemIndex+=itemValue;
	return (itemIndex-1);
}

void CIndividual::SaveData(CString item, CString value)
{
	items[GetItemIndex(item)] = value;
	if( item == "A2")
	{
		registerNo = value;
	}else if (item == "A3" )
	{
		name = value;
	}
	if(value != "")
	{
		itemStatus[GetItemIndex(item)] = 1; //已填写
	}
	else
	{
		itemStatus[GetItemIndex(item)] = 0; //未填写
	}
}

CString CIndividual::LoadData(CString item)
{
	return items[GetItemIndex(item)];
}

CTime CIndividual::LoadDataDate(CString item, CString defaultDate)
{
	CString sDate = LoadData(item);
	if( sDate.IsEmpty() )
	{
		sDate = defaultDate;
	}
	if (sDate.IsEmpty() )
	{
#ifdef _DEBUG
		return CTime(); //For Debug 
#else
		return CTime(0,0,0,0,0,0); //For Release必须用全0来初始化，否则release版本会出现问题。
#endif
	}

	int nYear, nMonth, nDay;
	sscanf(sDate.GetBuffer(100), "%d/%d/%d", &nYear, &nMonth, &nDay);
	return CTime(nYear, nMonth, nDay, 0, 0, 0);
}

int CIndividual::LoadDataInt(CString item)
{
	CString sData = LoadData(item);
	if( sData.IsEmpty() ) 
	{
		return 0;
	}
	return atoi(sData.Left(1));
}

CString CIndividual::GetWndText()
{
	CString wndText;
	CString researchName;
	if( CID(id).GetCode(TUI_ID_TOWN_TYPE) < 90)
	{
		if( name.IsEmpty())
		{
			wndText.Format("重大专项ID: %d -- ", id);
		}
		else
		{
			wndText.Format("重大专项ID: %d (", id);
			wndText = wndText + name + ") -- ";
		}
	}
	else
	{
		researchName = items[CIndividual::GetItemIndex("H2")];
		if( researchName.IsEmpty())
		{
			wndText = "重大专项ID: "+items[CIndividual::GetItemIndex("H1")]+ " -- ";
		}
		else
		{
			wndText = "重大专项ID: "+items[CIndividual::GetItemIndex("H1")]+ "("+researchName+") -- ";
		}
	}
	return wndText;
}

CString CIndividual::GetItem(CString itemName)
{
	return items[GetItemIndex(itemName)];
}

void CIndividual::SetUnessaryData(CString sItem, CString eItem)
{
	int iStart = GetItemIndex(sItem);
	int iEnd = GetItemIndex(eItem);

	for(int i=iStart; i<=iEnd; i++)
	{
		//ToDo: Set to 8888
		items[i] = "";
		itemStatus[i] = 2; //不必要输入的值
	}
}

void CIndividual::SetNessaryData(CString sItem, CString eItem)
{
	int iStart = GetItemIndex(sItem);
	int iEnd = GetItemIndex(eItem);
	
	BOOL bHasInput = FALSE;
	for(int i=iStart; i<=iEnd; i++)
	{
		if (items[i] != "")
		{
			bHasInput = TRUE;
			break;
		}
	}
	
	if( !bHasInput)
	{
		for(int i=iStart; i<=iEnd; i++)
		{
			if( itemStatus[i] == 2)
				itemStatus[i] = 0; //原来不必要输入的变为要输入的
		}
	}
}

void CIndividual::SaveDataToEmpty(CString sItem, CString eItem)
{
	int iStart = GetItemIndex(sItem);
	int iEnd = GetItemIndex(eItem);
	
	for(int i=iStart; i<=iEnd; i++)
	{
		items[i]= "";
		itemStatus[i]=0;
	}
}

//痰培养结果阴性
BOOL CheckPhResult()
{
	GET_CUR_IND();
	CString itemText = pInd->GetItem("A22");
	if( itemText == "" || itemText == "6:阴性")
	{
		g_LockReason = "有痰培养结果并且不为“阴性”的才需要录入!";
		return FALSE;
	}
	return TRUE;
}


//结核分枝杆菌复合群鉴定结果
BOOL CheckAssertResult()
{
	GET_CUR_IND();
	if( pInd->items[CIndividual::GetItemIndex("B3")] != "1:结核分枝杆菌")
	{
		g_LockReason = "结核分枝杆菌复合群鉴定结果为: 结核分枝杆菌的才需要录入!";
		return FALSE;
	}
	return TRUE;
}

//天津用户
BOOL CheckIsTianJing()
{
	GET_CUR_IND();
	if (CID(pInd->id).GetId(TUI_ID_CITY_TYPE) != 4)
	{
		g_LockReason = "天津用户才需要录入!";
		return FALSE;
	}
	return TRUE;
}

//B29: 是否符合研究要求
BOOL CheckIsMatchedForResearch()
{
	GET_CUR_IND();
	if( pInd->items[CIndividual::GetItemIndex("B29")] != "2:符合")
	{
		g_LockReason = "患者纳入-符合研究要求的才需录入!";
		return FALSE;
	}
	return TRUE;	
}

//B30: 是否同意纳入
BOOL CheckIsAgreedForResearch()
{
	GET_CUR_IND();
	if( pInd->items[CIndividual::GetItemIndex("B30")] != "2:同意")
	{
		g_LockReason = "患者纳入-同意纳入研究的才需录入!";
		return FALSE;
	}
	return TRUE;	
}

//B31: 纳入情况不能为“未纳入”
BOOL CheckIsIncludedInResearch()
{
	GET_CUR_IND();
	CString B31Answer = pInd->items[CIndividual::GetItemIndex("B31")];
	if(  B31Answer != ""
	&& B31Answer != "5:未入组")
	{
		return TRUE;
	}
	g_LockReason = "患者纳入表-患者纳入情况不为空且不为“未入组”的才需录入!";
	return FALSE;	
}

//B31: 纳入情况为1=初治耐多药，2=复治耐多药的才录入D部份
BOOL CheckIsPatient()
{
	GET_CUR_IND();
	CString B31Answer = pInd->items[CIndividual::GetItemIndex("B31")];
	if(  B31Answer == "1:初治耐多药肺结核患者"
	||   B31Answer == "2:复治耐多药肺结核患者")
	{
		return TRUE;
	}
	g_LockReason = "患者纳入表-患者纳入情况为“初治耐多药肺结核患者”或者“复治耐多药肺结核患者”的才需录入!";
	return FALSE;	
}

//治疗月份中如果对治疗影响是中止治疗，则后继月份不用输入
BOOL CheckIsTerminated()
{
	GET_CUR_IND();
	//Find first month is terminated
	int itemIndex = 11;
	CString item; 
	for(int i=1; i<=24; i++)
	{
		itemIndex = 11+24*(i-1);
		item.Format("D%d", itemIndex);
		if( pInd->GetItem(item) == "5:中止治疗")
		{
			break;
		}
	}

	if(g_Month>i)
	{
		g_LockReason.Format("在第%d个治疗月已经终止治疗，后继的月份不用再录入!", i);
		return FALSE;
	}
	return TRUE;
}

BOOL CheckTable1201()
{
	if (CheckPhResult())
		return TRUE;
	return FALSE;
}


BOOL CheckTable1202()
{
	if (CheckPhResult())
		return TRUE;
	return FALSE;
}

BOOL CheckTable1203()
{
	//只要是天津的就可以
	if( CheckPhResult()
		&& CheckIsTianJing() )
		return TRUE;
	return FALSE;
}

BOOL CheckTable1204()
{
	return CheckTable1203();
}

BOOL CheckTable1205()
{
	return CheckTable1203();
}

BOOL CheckTable1206()
{
	if( CheckPhResult()
		&& CheckAssertResult() )
		return TRUE;
	return FALSE;
}

BOOL CheckTable1301()
{
	if( CheckPhResult()
		&& CheckAssertResult() 
	 && CheckIsMatchedForResearch()
	 && CheckIsAgreedForResearch()
	 && CheckIsIncludedInResearch()
	 )
		return TRUE;
	return FALSE;

}

BOOL CheckIsBloodTaken()
{
	GET_CUR_IND();
	CString C5Answer = pInd->GetItem("C5");
	if (C5Answer == "2:是")
	{
		return TRUE;
	}
	g_LockReason = "已采血的才需录入!";
	return FALSE;	
}

BOOL CheckTable1302()
{
	if( CheckPhResult()
		&& CheckAssertResult() 
		&& CheckIsMatchedForResearch()
		&& CheckIsAgreedForResearch()
		&& CheckIsIncludedInResearch()
		&& CheckIsBloodTaken()
		)
		return TRUE;
	return FALSE;
}

BOOL CheckIsBlood2Province()
{
	GET_CUR_IND();
	CString C10Answer = pInd->GetItem("C10");
	if (C10Answer == "1:省级")
	{
		return TRUE;
	}
	g_LockReason = "目前菌株保存在省级机构的才需录入!";
	return FALSE;	
}

BOOL CheckTable1303()
{
	if( CheckPhResult()
		&& CheckAssertResult() 
	 && CheckIsMatchedForResearch()
	 && CheckIsAgreedForResearch()
	 && CheckIsIncludedInResearch()
	 && CheckIsBlood2Province()
	 )
	 return TRUE;
	return FALSE;
}

BOOL CheckTable1401()
{
	if( CheckPhResult()
		&& CheckAssertResult() 
	 && CheckIsMatchedForResearch()
	 && CheckIsAgreedForResearch()
	 && CheckIsIncludedInResearch()
	 && CheckIsPatient()
	 )
	 return TRUE;
	return FALSE;

}

BOOL CheckTable1402_25()
{
	if( CheckPhResult()
		&& CheckAssertResult() 
	 && CheckIsMatchedForResearch()
	 && CheckIsAgreedForResearch()
	 && CheckIsIncludedInResearch()
	 && CheckIsPatient()
	 && CheckIsTerminated()
	 )
	 return TRUE;
	return FALSE;

}

BOOL CheckTable1426()
{
/*
	if( CheckPhResult()
		&& CheckAssertResult() 
		&& CheckIsMatchedForResearch()
		&& CheckIsAgreedForResearch()
		&& CheckIsIncludedInResearch()
		&& CheckIsPatient()
		)
	 return TRUE;
	 return FALSE;
*/
	//12-17, 改为都不用锁
	return TRUE;

}

BOOL CheckTable2100()
{
	if( CheckPhResult()
		&& CheckAssertResult() 
		&& CheckIsMatchedForResearch()
		&& CheckIsAgreedForResearch()
		&& CheckIsIncludedInResearch()
		&& CheckIsPatient()
		)
	 return TRUE;
	return FALSE;

}

BOOL CheckTable2200()
{
	if( CheckPhResult()
		&& CheckAssertResult() 
		&& CheckIsMatchedForResearch()
		&& CheckIsAgreedForResearch()
		&& CheckIsIncludedInResearch()
		&& CheckIsPatient()
		)
	 return TRUE;
	return FALSE;

}

BOOL CheckTable2300()
{
	if( CheckPhResult()
		&& CheckAssertResult() 
		&& CheckIsMatchedForResearch()
		&& CheckIsAgreedForResearch()
		&& CheckIsIncludedInResearch()
		&& CheckIsPatient()
		)
	 return TRUE;
	return FALSE;
}


BOOL CheckTable1Valid()
{
	GET_CUR_IND();
	//H6-H12
	CString itemText;
	itemText = pInd->GetItem("H6");
	if( itemText == "" || atoi(itemText) == 0)
	{
		g_LockReason = "本地居住年限大于等于1年的，才需录入!";
		return FALSE;
	}
	if( pInd->GetItem("H7") != "1:无")
	{
		g_LockReason = "无结核病史的，才需录入!";
		return FALSE;
	}
	
	if( pInd->GetItem("H8") != "2:是")
	{
		g_LockReason = "X光检查排除结核的，才需录入!";
		return FALSE;
	}

	if( pInd->GetItem("H9") != "1:无")
	{
		g_LockReason = "无慢性病史的，才需录入!";
			return FALSE;
	}

	if( pInd->GetItem("H10") != "1:无")
	{
		g_LockReason = "无呼吸系统疾病的，才需录入!";
		return FALSE;
	}

	if( pInd->GetItem("H11") != "2:是")
	{
		g_LockReason = "同意参加本研究的，才需录入!";
		return FALSE;
	}
	
	if( pInd->GetItem("H12") != "2:是")
	{
		g_LockReason = "纳入的，才需录入!";
		return FALSE;
	}
	return TRUE;
}

BOOL CheckTable2Valid()
{
	GET_CUR_IND();
	if( pInd->GetItem("H15") != "2:是")
	{
		g_LockReason = "完成调查知情同意书的，才需录入!";
		return FALSE;
	}
	
	if( pInd->GetItem("H16") != "2:是")
	{
		g_LockReason = "完成问卷调查的， 才需录入!";
		return FALSE;
	}

	if( pInd->GetItem("H19") != "2:是")
	{
		g_LockReason = "已采血的， 才需录入!";
		return FALSE;
	}
	return TRUE;
}

BOOL CheckTable3Valid()
{
	return FALSE;
}

BOOL CheckResearchTable2()
{
	if( CheckTable1Valid() )
		return TRUE;
	return FALSE;
}

BOOL CheckResearchTable3()
{
	if( CheckTable1Valid() 
		&&CheckTable2Valid())
		return TRUE;
	return FALSE;
}

BOOL CIndividual::CheckIsComplete(CString sItem, CString eItem)
{
	BOOL isFinished = TRUE;
	BOOL hasInput = FALSE;
	int iStart = GetItemIndex(sItem);
	int iEnd = GetItemIndex(eItem);
	ASSERT(iStart<=iEnd);
	int m;
	for(m=iStart; m<=iEnd; m++)
	{
		if( items[m] != "")
		{
			hasInput = TRUE;
		}
	}
	
	if(hasInput)
	{
		for(m=iStart; m<=iEnd; m++)
		{
			if(items[m] == "" && itemStatus[m] != 2)
			{
				if( hasInput)
				{
					CString msg;
					msg.Format("start = %d, itemIndex = %d, status = %d", iStart, m, itemStatus[m]);
					//						AfxMessageBox(msg);
					isFinished = FALSE;
					break;
				}
			}
		}
	}
	else
	{
		isFinished = FALSE;
	}

	return isFinished;
}

/* Check if All Items is nessary or not */
void CIndividual::CheckAllTableItems()
{
	UINT gCurIId_bk = g_CurIId;
	g_CurIId = id;
	for(UINT i=0; i<gSectionNameSize; i++)
	{
		for(UINT j=0; j<gTableSize[i]; j++)
		{
			g_Month = gTable[i][j].param;
			if (gTable[i][j].checkFun)
			{
				if (!gTable[i][j].checkFun())
					SetUnessaryData(gTable[i][j].itemStart, gTable[i][j].itemEnd);
				else
					SetNessaryData(gTable[i][j].itemStart, gTable[i][j].itemEnd);
				
			}
			for(UINT k=0; k<gTable[i][j].subsize; k++)
			{
				g_Month = gTable[i][j].sub[k].param;
				if (gTable[i][j].sub[k].checkFun) 
				{
					if(!gTable[i][j].sub[k].checkFun())
						SetUnessaryData(gTable[i][j].sub[k].itemStart, gTable[i][j].sub[k].itemEnd);
					else
						SetNessaryData(gTable[i][j].sub[k].itemStart, gTable[i][j].sub[k].itemEnd);
				}
			}
		}
	}
	g_CurIId = gCurIId_bk;
}

//Special Handler for 健康对照表
UINT CIndividual::ConvertToResearchId(UINT iId)
{
	CID sId(iId);
	UINT cId = sId.GetCode(TUI_ID_CITY_TYPE);
	UINT tId = sId.GetCode(TUI_ID_TOWN_TYPE)-90;
	UINT iIndex = sId.GetCode(TUI_ID_IND_TYPE); //iId%100;
	return cId*1000+tId*100+iIndex;
}

BOOL CIndividual::IsFinished()
{
	int iEnd = GetItemIndex("G14");
	for(int i=0; i<=iEnd; i++)
	{
		if(itemStatus[i] == 0) //有缺失的则为未完成
		{
			return FALSE;
		}
	}
	//Sepcial Check
	if (GetItem("C4") != "2:是" || GetItem("C10") != "1:省级")
	{
		return FALSE;
	}
	for(i=1; i<=24; i++)
	{
		if(	  (i == 1) ||(i == 2) ||(i == 3)
			||(i == 4) ||(i == 5) ||(i == 6)
			||(i == 8) ||(i == 10) ||(i == 12)
			||(i == 14) ||(i == 16) ||(i == 18)
			||(i == 20) ||(i == 22) ||(i == 24))
		{
			//Check: “涂片结果”和“培养结果”不能为"不需查"
			CString item1, item2;
			item1.Format("D%d", (i-1)*24+3);
			item2.Format("D%d", (i-1)*24+4);
			if (GetItem(item1) == "7:不需查" || GetItem(item1) == "8:未查" 
				|| GetItem(item2) == "8:不需查" || GetItem(item2) == "9:未查" )
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}

int CIndividual::UpdateStatus(BOOL isSel)
{
	status = IND_STATUS_PATIENT;
	//是否是耐多药
	CString itemText = GetItem("B26");
	if ( (itemText == "4:耐多药")
		|| (itemText == "5:广泛耐药") )
	{
		status = IND_STATUS_LYD_PATINET;
	}
	
	if (isSel)
	{
		status = status | IND_STATUS_SEL;
	}
	if (IsFinished())
	{
		status = status | IND_STATUS_FINISHED;
	}
	return status;
}

BOOL CIndividual::IsTableFinished(int iSection, int iSubSection, int iIndex)
{
    TABLE_STRUCT* pTable = gTable[iSection];
    ASSERT(pTable);
    
	//Setup SubSection Tab
    if (pTable[iSubSection].sub != NULL)
    {
        pTable = &pTable[iSubSection].sub[iIndex];
    }
	else
	{
		pTable = &pTable[iIndex];
	}
	ASSERT(pTable);

	int iStart = GetItemIndex(pTable->itemStart);
	int iEnd = GetItemIndex(pTable->itemEnd);
	for(int i=iStart; i<=iEnd; i++)
	{
		if(itemStatus[i] == 0) //有缺失的则为未完成
		{
			return FALSE;
		}
	}

	//Special Check
	if (pTable->name == "问卷调查及标本保存")
	{
		if (GetItem("C4") != "2:是" || GetItem("C10") != "1:省级")
		{
			return FALSE;
		}
	}

	//Special Check
	CString tableName = pTable->name;
	if (tableName.Find("治疗第") != -1)
	{
		if(	  (pTable->param == 1)
			||(pTable->param == 2)
			||(pTable->param == 3)
			||(pTable->param == 4)
			||(pTable->param == 5)
			||(pTable->param == 6)
			||(pTable->param == 8)
			||(pTable->param == 10)
			||(pTable->param == 12)
			||(pTable->param == 14)
			||(pTable->param == 16)
			||(pTable->param == 18)
			||(pTable->param == 20)
			||(pTable->param == 22)
			||(pTable->param == 24))
		{
			//Check: “涂片结果”和“培养结果”不能为"不需查"
			CString item1, item2;
			item1.Format("D%d", (pTable->param-1)*24+3);
			item2.Format("D%d", (pTable->param-1)*24+4);
			if (GetItem(item1) == "7:不需查" || GetItem(item1) == "8:未查" 
				|| GetItem(item2) == "8:不需查" || GetItem(item2) == "9:未查" )
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}

BOOL CIndividual::IsIDValid(int iID)
{
	UINT cId, tId;
	CID sId(iID);
	cId = sId.GetId(TUI_ID_CITY_TYPE);
	tId = sId.GetId(TUI_ID_TOWN_TYPE);
	for(UINT i=0; i<gCTinfoSize; i++)
	{
		if(gCTinfo[i].id == cId)
		{
			break;
		}
	}	
	if (i== gCTinfoSize)
		return FALSE;

	for(UINT j=0; j<gCTinfo[i].townsize; j++){
		if(gCTinfo[i].pTown[j].id == tId)
		{
			break;
		}
	}
	if (j==gCTinfo[i].townsize)
		return FALSE;

	if (sId.GetCode(TUI_ID_IND_TYPE) == 0)
		return FALSE;

	return TRUE;
}

//ID: 1 CityCode + 2 TownCode + 3 IndCode;
const BYTE CID::bCodeLen[TUI_ID_MAX] = {1, 2, 4
};
CID::CID()
{
	for(int i=0; i<TUI_ID_MAX; i++)
	{
		wCode[i] = 0;
	}
}

CID::CID(WORD nCityCode, WORD nTownCode, WORD nIndCode)
{
	wCode[TUI_ID_CITY_TYPE] = nCityCode;
	wCode[TUI_ID_TOWN_TYPE] = nTownCode;
	wCode[TUI_ID_IND_TYPE]	= nIndCode;
}

CID::CID(UINT id)
{
	UINT nMaxLen = 0;
	int i;
	UINT j;
	UINT nBase;
	for(i=0; i<TUI_ID_MAX; i++)
	{
		wCode[i] = 0;
		nMaxLen+=bCodeLen[i];
	}
//	nMaxLen -= 1;

	//Get Codes
	UINT pId = id;
	for(i=TUI_ID_MAX-1; i>0; i--)
	{
		for(nBase = 1,j=0; j<nMaxLen-bCodeLen[i]; j++) //1 -> -bCodeLen[i], changed at 2012/7/18
		{
			nBase = nBase*10;
		}
		if (pId/nBase)
		{
			for(nBase = 1,j=0; j<bCodeLen[i]; j++)
			{
				nBase = nBase*10;
			}
			wCode[i] = pId%nBase;
			pId = pId / nBase;
		}
		nMaxLen -=bCodeLen[i];
		if (nMaxLen == bCodeLen[0]) break;
	}
	wCode[0] = pId;
	//Check the last code len
	nBase = 1;
	for(j=0; j<bCodeLen[0]; j++)
	{
		nBase = nBase*10;
	}

	if (wCode[0] > nBase)
	{
		LogInfo("Error ID to create!");
		//Error Id, Reset all code
		for(i=0; i<TUI_ID_MAX; i++)
		{
			wCode[i] = 0;
		}	
	}
}


UINT CID::GetId(TUI_ID_TYPE eType)
{
	UINT pId = 0;
	UINT nBase;
	int i, j, k, nLen;
	
	TUI_ID_TYPE eMyType = GetIdType();
	if (eType > eMyType)
	{
		//Can not get smaller type
//		LogInfo("Error get ID!");
//		return 0;
	}

	pId = wCode[eType];

	//Set for wCode[eType-1] -> wCode[0]
	for(j=eType-1; j>=0; j--)
	{
		nLen = 0;
		for(k=j+1; k<=eType;k++)
		{
			nLen = nLen+bCodeLen[k];
		}
		nBase = 1;
		for(i=0; i<nLen; i++)
		{
			nBase = nBase*10;
		}
		pId = pId+wCode[j]*nBase;
	}
	return pId;
}

TUI_ID_TYPE CID::GetIdType()
{
	if(wCode[TUI_ID_IND_TYPE] + wCode[TUI_ID_TOWN_TYPE] == 0)
	{
		return TUI_ID_CITY_TYPE;
	}

	if(wCode[TUI_ID_IND_TYPE] == 0)
	{
		return TUI_ID_TOWN_TYPE;
	}

	return TUI_ID_IND_TYPE;
}

WORD CID::GetCode(TUI_ID_TYPE eType)
{
	return wCode[eType];
}

void CID::SetCode(TUI_ID_TYPE eType, WORD wCode)
{
	this->wCode[eType] = wCode;
}


UINT CID::GetMaxCode(TUI_ID_TYPE eType)
{
	UINT nBase = 1;
	for(int i=0; i<bCodeLen[eType]; i++)
	{
		nBase = nBase*10;
	}
	return nBase;
}
