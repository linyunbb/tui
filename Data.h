// Data.h: interface for the CData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATA_H__D20F653E_66CE_4268_AEC0_271382DB8F64__INCLUDED_)
#define AFX_DATA_H__D20F653E_66CE_4268_AEC0_271382DB8F64__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct TOWNINFO_STRUCT
{
	char *name;
	UINT id;
};

struct CITYINFO_STRUCT
{
	char * name;
	UINT id;
	TOWNINFO_STRUCT *pTown;
    UINT townsize;
};

typedef BOOL (*CHECKFUNCTION)();

struct TABLE_STRUCT
{
	char * name;
	char * itemStart;
	char * itemEnd;
	CDialog* pDlg;
	CHECKFUNCTION checkFun;
	TABLE_STRUCT* sub;
    UINT subsize;
	DWORD param;
};

struct OUTPUT_ITEM_INFO
{
	char * name;
	int type;  //0-Edit, 1-Sel, 2-Date
	int offset; //For Combobox and Value
};

extern CITYINFO_STRUCT gCTinfo[];
extern UINT gCTinfoSize;
extern char *gSectionName[];
extern UINT gSectionNameSize;
extern TABLE_STRUCT *gTable[];
extern UINT gTableSize[];
extern TABLE_STRUCT gResearchTable[];
extern UINT	gResearchTableSize;
extern UINT g_CurIId;
extern OUTPUT_ITEM_INFO gAItemInfo[];
extern UINT gAItemInfoSize;

//extern TABLE_STRUCT gTable1[];
//extern TABLE_STRUCT gTable2[];
//extern UINT gTable1Size;
//extern UINT gTable2Size;

extern void LogInfo(CString msg);


struct OUTPUTITEM
{
	char* name;
	CString value;
};

class OUTPUT
{
public:
	int size;
	OUTPUTITEM *items;
public:
	OUTPUT(char** itemNames, int itemSize)
	{
 		size = itemSize;
		items = new OUTPUTITEM[size];
		
		for(int i=0; i<size; i++)
		{
			items[i].name = itemNames[i];
			items[i].value = "未输入";
		}
	}
	~OUTPUT()
	{
		delete[] items;
	}
};


enum TUI_ID_TYPE{
	TUI_ID_CITY_TYPE = 0,
	TUI_ID_TOWN_TYPE	,
	TUI_ID_IND_TYPE		,
	TUI_ID_MAX
};

class CID
{
public:
	CID();
	CID(UINT id);
	CID(WORD nCityCode, WORD nTownCode, WORD nIndCode);
	UINT GetId(TUI_ID_TYPE eType);
	WORD GetCode(TUI_ID_TYPE eType);
	UINT GetMaxCode(TUI_ID_TYPE eType);
	TUI_ID_TYPE GetIdType();

	void SetCode(TUI_ID_TYPE eType, WORD wCode);
public:
	static const BYTE bCodeLen[TUI_ID_MAX];
	//0-City, 1-Town, 2-Ind
	WORD wCode[TUI_ID_MAX];
};


class CMySite;
class CCity;
class CTown;
class CFamily;
class CIndividual;
class CDataCommon;

class CData : public CObject  
{
private:
	static CCity* CreateCity(UINT id);
public:
	static CTypedPtrMap<CMapPtrToPtr, void*, CDataCommon*> m_Map;
	static CTypedPtrArray<CObArray, CCity*>  m_CList;
    static int cSel; //City
    static int tSel; //Town
	static int citySel; //City for Research input
	static int typeSel; //Type: 1: urban, 2: rural
public:
	CProgressCtrl* pProgress;
	int GetTotalTown();
	void Serialize(BOOL isSaving);
	void SerializeConfig(CArchive &ar);
	static UINT GetNewResearchId(UINT tId);
	static UINT GetNewIndId(UINT tId);
	static CDataCommon* CreateData(UINT id);
	static void MapData(UINT id, CDataCommon* pData);
	static CDataCommon* GetData(UINT id);
	static void RemoveMap(UINT id);
	static int GetTotoalInd();
	static void RemoveInd(CIndividual* pInd);
	static void RemoveTown(CTown *pSite);
	static void DeleteAll();

    CData() { cSel =-1; tSel=-1; citySel=-1; typeSel=-1;}
	virtual ~CData() {}
	DECLARE_SERIAL(CData)
};

class CDataCommon : public CObject
{
public:
	virtual void Serialize(CArchive &ar) =0;
	virtual CDataCommon* CreateSub(UINT id) {ASSERT(0); return NULL;} //Like Site->Family, Family->Ind

public:
	CString name;
	UINT id;
	int nListItem;//-1=Not Showed in List, >=0, the pos

public:
	CDataCommon()
	{
		id = 0;
		name = "";
		nListItem = -1;
	};
	void SetId(UINT id)
	{
		this->id = id;
		CData::MapData(id, this);
	}

	~CDataCommon()
	{
		if(id !=0)
		{
			CData::RemoveMap(id);
		}
	}
};

#define IND_STATUS_PATIENT		0
#define IND_STATUS_LYD_PATINET  1
#define IND_STATUS_SEL			2
#define IND_STATUS_FINISHED		4


class CIndividual : public CDataCommon  
{
public:
	virtual void Serialize(CArchive &ar);
public:
	CString registerNo;
	CString createDate;
	CString items[750]; //All Item is 730
	BYTE    itemStatus[750]; //0-缺失, 1-已输入, 2-不必要录入
	BYTE    status;
public:
	CTown *pTown;
public:
	static BOOL IsIDValid(int iID);
	void SaveDataToEmpty(CString sItem, CString eItem);
	BOOL IsTableFinished(int iSection, int iSubSection, int iIndex);
	int UpdateStatus(BOOL isSel);
	BOOL IsFinished();
	static UINT ConvertToResearchId(UINT iId);
	void CheckAllTableItems();
	BOOL CheckIsComplete(CString sItem, CString eItem);
	void SetNessaryData(CString sItem, CString eItem);
	CString GetItem(CString itemName);
	void SetUnessaryData(CString sItem, CString eItem);
	CString GetWndText();
	int LoadDataInt(CString item);
	CTime LoadDataDate(CString item, CString defaultDate = "");
	static int GetItemIndex(CString item);
	void SaveData(CString item, CString value);
	CString LoadData(CString item);
	CIndividual()
	{
		id = 0;
		name = "";
		registerNo = "";
		status = IND_STATUS_PATIENT;
		int i = 0;
		for(i=0; i<(int)gAItemInfoSize; i++)
		{
			switch(gAItemInfo[i].type)
			{
			case 0: //Edit
				items[i].Empty();
				break;
			case 1: //Sel
				items[i].Empty();
				break;
			case 2: //Date
				items[i].Empty();
				break;
			}
			itemStatus[i] = 0;
		}
	}
	virtual ~CIndividual() {}
	DECLARE_SERIAL(CIndividual)
};

struct StatInfo
{
	UINT totalP[3][3];
	UINT totalO[16];
};

class CTown : public CDataCommon  
{
public:
	CTown(){};
	virtual ~CTown();

public:
	CTypedPtrArray<CObArray, CIndividual*>  m_IList;
	UINT status; //0-未输入基本信息, 1-已输入基本信息
	CCity* pCity;
	static OUTPUT output;
	static OUTPUT output_export;
public:
	DECLARE_SERIAL(CTown)
	void GetExportInfo(BOOL isSecondInput);
	void GetTotal(StatInfo &siteStat, BOOL isCompareMode);
	virtual void Serialize(CArchive &ar);
	void GetOutputInfo();
	CDataCommon* CTown::CreateSub(UINT fId);

};


class CCity : public CDataCommon  
{
public:
	virtual void Serialize(CArchive &ar);
public:
	CTypedPtrArray<CObArray, CTown*>  m_TList;
	UINT tableIndex;
	int townNo;
public:
	CDataCommon* CreateSub(UINT sId);
	CCity(){townNo =0;}

	virtual ~CCity() {}
	DECLARE_SERIAL(CCity)
};

extern BOOL CheckTable1201();
extern BOOL CheckTable1202();
extern BOOL CheckTable1203();
extern BOOL CheckTable1204();
extern BOOL CheckTable1205();
extern BOOL CheckTable1206();

extern BOOL CheckTable1301();
extern BOOL CheckTable1302();
extern BOOL CheckTable1303();

extern BOOL CheckTable1401();
extern BOOL CheckTable1402_25();
extern BOOL CheckTable1426();

extern BOOL CheckTable2100();
extern BOOL CheckTable2200();
extern BOOL CheckTable2300();

extern BOOL CheckResearchTable2();
extern BOOL CheckResearchTable3();

#endif // !defined(AFX_DATA_H__D20F653E_66CE_4268_AEC0_271382DB8F64__INCLUDED_)
