// MyEdit.cpp : implementation file
//

#include "stdafx.h"
#include "global.h"
#include "MyEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyEdit
CMyEdit::CMyEdit()
{
	m_nLen = 0;
	m_enType = DATA_TYPE_BUTT;
	m_ID.IsEmpty();
}

CMyEdit::~CMyEdit()
{
}


BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
	//{{AFX_MSG_MAP(CMyEdit)
//	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	ON_CONTROL_REFLECT(EN_SETFOCUS, OnSetfocus)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyEdit message handlers

#if 0
void CMyEdit::OnChange() 
{
	/* 不提示，只有检查过了才允许即时修改 */
	m_bMsgInform = FALSE;
	if( CheckInput() )
	{
		if( !m_ID.IsEmpty() )
		{
			CString szAnswer;
			GetWindowText(szAnswer);
			g_Tools.WriteInitData(g_sAnswerFileName, m_ID, "a", szAnswer);
		}
	}
	m_bMsgInform = TRUE;
}
#endif

void CMyEdit::OnSetfocus() 
{
	SetTimer(2,10,NULL); /*设置全选*/
}

void CMyEdit::OnTimer(UINT nIDEvent) 
{
	if( nIDEvent == 2 )
	{
		KillTimer(2);
		SetSel(0,-1);
		CString str;
		GetWindowText(str);
		m_DotPos = str.Find('.');
	}
	CEdit::OnTimer(nIDEvent);
}

void CMyEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	/* Called after OnChar */
	
	/* 如果在OnKeyUp中做判断，则如果有弹出对话框，则会触发OnKeyUp
	   用OnKeyDown时Style中一定要设为多行*/

	if( nChar == VK_RETURN && m_enType != DATA_TYPE_NO_CHINESE) /* 按下Enter键 */
	{
		if( CheckInput() == FALSE )
		{
			return;
		}

		if( !m_ID.IsEmpty() )
		{
//			CString curInput;
//			GetWindowText(curInput);
//			g_Tools.WriteInitData(g_sAnswerFileName, m_ID, "a", curInput);
		}

		/* 转到下一输入处, 到最后一个时向父窗口发送下一题消息 */
		CWnd *pWnd;
		pWnd = GetParent()->GetNextDlgTabItem(this);
		if( pWnd != NULL)
		{
			pWnd->SetFocus();
			if( pWnd->IsKindOf(RUNTIME_CLASS(CEdit) ) )
			{
				((CEdit*)pWnd)->SetSel(0,-1);
			}
			else if (pWnd->IsKindOf(RUNTIME_CLASS(CComboBox)))
			{
		//		((CComboBox*)pWnd)->ShowDropDown(TRUE);				
			}
			else
			{
				pWnd->SetFocus();
				//GetParent()->SendMessage(WM_NEXT_QUESTION);
				
				/* 按钮时设置为焦点并可以按Enter键激活*/
				/*
				((CButton*)pWnd)->SetFocus(); 
				((CButton*)pWnd)->SetButtonStyle(BS_DEFPUSHBUTTON);
				*/
			}
		}
		return;
	}

	if ( ( DATA_TYPE_DATE == m_enType) || (DATA_TYPE_SHORT_DATE == m_enType))
	{
		if ( nChar == VK_DELETE )/* 取消DEL功能 */
		{
			return;
		}
	}
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
	
}

void CMyEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CString str;
	int oldpos;
	int nStart, nEnd;

	switch(m_enType) 
	{
	case DATA_TYPE_NUMBER:
		if( !IsNum(nChar) && (nChar != VK_BACK) )	
		{
			return;
		}
		CEdit::OnChar(nChar, nRepCnt, nFlags);
		break;
	case DATA_TYPE_AGE:
		if(!IsNum(nChar) && (nChar != VK_BACK) && (nChar != '.'))
		{
			return;
		}
		GetWindowText(str);
		if (atoi(str+CString(nChar)) >= 200)
		{
			return;
		}
		oldpos = LOWORD(GetSel());
		GetSel(nStart, nEnd);
		//append 0
		if(str.IsEmpty() && nChar == '.')
		{
			SetWindowText("0.");
			SetSel(FormatPos(2,2));
			return;
		}
		//If Dot is in the selection, no limitation
		if(m_DotPos>=nStart && m_DotPos <nEnd)
		{
			if(nEnd-nStart==str.GetLength() && nChar == '.')
			{
				SetWindowText("0.");
				SetSel(FormatPos(2,2));
				return;
			}
			CEdit::OnChar(nChar, nRepCnt, nFlags);
			RemovePreZero();
			break;
		}
		m_DotPos = str.Find('.');
		if (m_DotPos != -1 )
		{
			//Not zero
			if (str == "0." && nChar == '0')
				return;
			//Only one dot
			if (nChar == '.')
				return;
			//Only one number after dot
			if (oldpos >m_DotPos)
			{
				if (str.GetLength() == m_DotPos+1+1 && nStart == nEnd && nChar != VK_BACK)
				{
					return;
				}
			}
		}
		CEdit::OnChar(nChar, nRepCnt, nFlags);
		RemovePreZero();
		break;
	case DATA_TYPE_MONEY:
		if(!IsNum(nChar) && (nChar != VK_BACK) && (nChar != '.'))
		{
			return;
		}
		GetWindowText(str);
		oldpos = LOWORD(GetSel());
		GetSel(nStart, nEnd);
		//append 0
		if(str.IsEmpty() && nChar == '.')
		{
			SetWindowText("0.");
			SetSel(FormatPos(2,2));
			return;
		}
		//If Dot is in the selection, no limitation
		if(m_DotPos>=nStart && m_DotPos <nEnd)
		{
			if(nEnd-nStart==str.GetLength() && nChar == '.')
			{
				SetWindowText("0.");
				SetSel(FormatPos(2,2));
				return;
			}
			CEdit::OnChar(nChar, nRepCnt, nFlags);
			RemovePreZero();
			break;
		}
		m_DotPos = str.Find('.');
		if (m_DotPos != -1 )
		{
			//Only one dot
			if (nChar == '.')
				return;
			//Only two number after dot
			if (oldpos >m_DotPos)
			{
				if (str.GetLength() == m_DotPos+1+2 && nStart == nEnd && nChar != VK_BACK)
				{
					return;
				}
			}
		}
		CEdit::OnChar(nChar, nRepCnt, nFlags);
		RemovePreZero();
		break;
	case DATA_TYPE_DATE:
	case DATA_TYPE_SHORT_DATE:
		if( !IsDate(nChar) )
		{
			return;
		}
		oldpos=LOWORD(GetSel());
		GetWindowText(str);
		
		if ( nChar>='0' && nChar<='9' )
		{	
			if ( oldpos<4 || ( oldpos>4 && oldpos<7) || oldpos>7)
			{
				str.Delete(oldpos,1);
				SetWindowText(str);
				SetSel(FormatPos(oldpos,oldpos));
				CEdit::OnChar(nChar, nRepCnt, nFlags);
				if ( LOWORD(GetSel())==4 || LOWORD(GetSel())==7)
				{
					oldpos=LOWORD(GetSel());
					SetSel(FormatPos(oldpos+1,oldpos+1));
				}
			}
			else
				if ( oldpos==4 || oldpos==7 )
				{
					oldpos+=1;
					SetSel(FormatPos(oldpos,oldpos));
					str.Delete(oldpos,1);
					SetWindowText(str);
					SetSel(FormatPos(oldpos,oldpos));
					CEdit::OnChar(nChar, nRepCnt, nFlags);
				}
		}
		else
		{
			if ( nChar==VK_BACK )
			{
				if ( (oldpos>0 && oldpos<5) || ( oldpos>5 && oldpos<8) || (oldpos>8 && oldpos<11) )
				{
					if( ( (DATA_TYPE_DATE == m_enType) && (oldpos == 10) )
					||  ( (DATA_TYPE_SHORT_DATE == m_enType) && (oldpos == 7) ) )
					{
						/* 直接删除 */
					}
					else
					{
						str.Insert(oldpos,' ');
					}
					SetWindowText(str);
					SetSel(FormatPos(oldpos,oldpos));
					CEdit::OnChar(nChar, nRepCnt, nFlags);
				}
				else
				{
					if ( oldpos==5 || oldpos==8)
					{	
						SetSel(FormatPos(oldpos-1,oldpos-1));
					}
					if( oldpos >= 11 )
					{
						CEdit::OnChar(nChar, nRepCnt, nFlags);
					}
				}
			}
		}
		return; //Date does not need to store at anytime!!!
	case DATA_TYPE_NO_CHINESE:
		if (nChar>=0x80)
		{
			return;
		}
		CEdit::OnChar(nChar, nRepCnt, nFlags);
		break;
	default:
		CEdit::OnChar(nChar, nRepCnt, nFlags);
		break;
	}
	
	if( !m_ID.IsEmpty() )
	{
//		CString curInput;
//		GetWindowText(curInput);
//		g_Tools.WriteInitData(g_sAnswerFileName, m_ID, "a", curInput);
	}

}


void CMyEdit::InitEdit(int type, int len, CString sRecVal)
{
	if( len == 0 || len >=1000)
	{
		len = 1000;
	}

	switch( type )
	{
	case DATA_TYPE_DATE:
		m_nLen = 10;
		break;
	case DATA_TYPE_SHORT_DATE:
		m_nLen = 7;
		break;
	case DATA_TYPE_NUMBER:
		m_nLen = len;
		break;
	case DATA_TYPE_NO_CHINESE:
		m_nLen = len;
		break;
	case DATA_TYPE_AGE:
		m_DotPos = -1;
		m_nLen = len+2; //Add .0
		if (m_nLen>5)
			m_nLen = 5;
		break;
	case DATA_TYPE_MONEY:
		m_DotPos = -1;
		m_nLen = len+3; //Add .00
		if (m_nLen>10)
			m_nLen = 10;
		break;
	default:
		type = DATA_TYPE_BUTT;
		m_nLen = len;
		break;
	}
	m_enType = type;

	SetLimitText(m_nLen);

	if( sRecVal.IsEmpty() ||
		((sRecVal == "-1") && (type == DATA_TYPE_NUMBER)) 
		)
	{
		sRecVal = GetBlankAnswer();
	}
	else
	{
		/* 由于空格不读入，所以默认值为"/"时要扩展，如“    /”读入时为“/”*/
		if(  (sRecVal.GetAt(0) == '-' ) && 
			( (DATA_TYPE_SHORT_DATE == m_enType) || (DATA_TYPE_DATE) ) )
		{
			sRecVal = GetBlankAnswer();
		}
	}
//	LogInfo(sRecVal);
	SetWindowText(sRecVal);//
}


void CMyEdit::InitEdit(CString sID)
{
#if 0
	ASSERT(!sID.IsEmpty());
	m_bMsgInform = TRUE;

	m_ID = sID;

	CString sInputType;
	g_Tools.ReadIniData(g_sELFileName, m_ID, "t", &sInputType);

	/* 初始化类型与长度 */
	if( sInputType == "date" )
	{
		m_enType = DATA_TYPE_DATE;
		m_nLen = 10;
	}
	else if( sInputType == "sdate")
	{
		m_enType = DATA_TYPE_SHORT_DATE;
		m_nLen = 7;
	}
	else if( sInputType == "num" )
	{
		g_Tools.ReadIniData(g_sELFileName, m_ID, "l", NULL, &m_nLen);
		m_enType = DATA_TYPE_NUMBER;
	}
	else
	{
		m_enType = DATA_TYPE_BUTT;
		m_nLen = 0;
	}
	
	if( m_nLen )
	{
		SetLimitText(m_nLen);
	}

	CString sRecVal;
	g_Tools.ReadIniData(g_sAnswerFileName,m_ID, "a", &sRecVal);

	if( sRecVal.IsEmpty() )
	{
		sRecVal = GetBlankAnswer();
	}
	else
	{
		/* 由于空格不读入，所以默认值为"/"时要扩展，如“    /”读入时为“/”*/
		if(  (sRecVal.GetAt(0) == '-' ) && 
			( (DATA_TYPE_SHORT_DATE == m_enType) || (DATA_TYPE_DATE) ) )
		{
			sRecVal = GetBlankAnswer();
		}
	}
	SetWindowText(sRecVal);
#endif
}

DWORD CMyEdit::FormatPos(int hPos, int lPos)
{
	DWORD dPos=hPos;
	dPos=dPos<<16;
	dPos+=lPos;
	return dPos;
}

BOOL CMyEdit::CheckInput()
{
	CString curInput;
	int i;

	GetWindowText(curInput);
	if( curInput.IsEmpty() ) /* 初步检查 */
	{
		MsgForInputValid("输入为空，请确认!");//如果缺失请输入："+GetDefaultAnswer());
		return FALSE;
	}

	switch(m_enType)
	{
	case DATA_TYPE_DATE:
	case DATA_TYPE_SHORT_DATE:
		for(i=0; i<curInput.GetLength(); i++)
		{
			if( curInput.GetAt(i) == ' ' )
			{
				MsgForInputValid("不能有空格，请确认!");//如果“年”缺失请填写“9999”，“月或日”缺失请填写“99”!");
				SetFocus();
				return FALSE;
			}
		}
		
		if( ( ( DATA_TYPE_DATE == m_enType ) && (curInput.GetLength() < 9 ) )
			||( ( DATA_TYPE_SHORT_DATE == m_enType ) && (curInput.GetLength() < 6 ) ) )
		{
			MsgForInputValid("没有输全信息，请确认!");//，如果“年”缺失请填写“9999”，“月或日”缺失请填写“99”");
			SetFocus();
			return FALSE;
		}
		break;
	case DATA_TYPE_NUMBER:
		break;
	}
	return TRUE;
}

CString CMyEdit::GetDefaultAnswer()
{
	int i;
	CString sDefault = "";

	switch(m_enType) 
	{
	case DATA_TYPE_DATE:
		return "9999-99-99";

	case DATA_TYPE_SHORT_DATE:
		return "9999-99";

	case DATA_TYPE_NUMBER:
		for(i=0; i<m_nLen; i++)
		{
			sDefault+="9";
		}
		return sDefault;

	default:
		return "9999";
	}
}

CString CMyEdit::GetBlankAnswer()
{
	switch(m_enType) 
	{
	case DATA_TYPE_DATE:
		return "    -  -";
	case DATA_TYPE_SHORT_DATE:
		return "    -";
	default:
		return "";
	}
}

BOOL CMyEdit::IsDate(UINT nChar)
{
	int oldpos=LOWORD(GetSel());
	CString str;
	GetWindowText(str);
	/* 日期中每一位的输入限制 */
	switch(oldpos)
	{
	case 0:
		if( (nChar != '1') && (nChar != '2')
			&& (nChar !='9') && (nChar != VK_BACK) )
		{
			return FALSE;
		}
		break;
	case 5:
		if( (nChar != '0') && (nChar != '1')
			&& (nChar !='9') && (nChar != VK_BACK) )
		{
			return FALSE;
		}
		break;
	case 6:
		if( str.GetAt(5) == '1' )
		{
			if( (nChar != '0') && (nChar != '1')
				&& (nChar != '2') && (nChar !='9')
				&& (nChar != VK_BACK))
			{
				return FALSE;
			}
		}
		else
		{
			if( str.GetAt(5) == '9' )
			{
				if( (nChar !='9') && (nChar != VK_BACK))
				{
					return FALSE;
				}
			}
		}
		break;
	case 9:
		if( str.GetAt(8) == '3' )
		{
			if( ( nChar != '0') &&(nChar != '1')
				&& (nChar !='9') && (nChar != VK_BACK))
			{
				return FALSE;
			}
		}
		else
		{
			if( (str.GetAt(8) >= '4') && (str.GetAt(8) <='9') )
			{
				if( (nChar != VK_BACK) && (nChar!='9') )
				{
					return FALSE;
				}
			}
		}
		break;
	}
	return TRUE;
}

void CMyEdit::MsgForInputValid(CString msg)
{
	if( m_bMsgInform )
	{
		AfxMessageBox(msg);
	}
}

void CMyEdit::RemovePreZero()
{
	CString str;
	CString dotStr;
	long strValue;
	int oldpos = LOWORD(GetSel());
	GetWindowText(str);
	if (str.IsEmpty()) return;
	
	int dotPos = str.Find('.');
	if (dotPos != -1)
	{
		dotStr = str.Mid(dotPos);
		str = str.Left(dotPos);
	}
	strValue = atoi(str);
	str.Format("%d", strValue);
	SetWindowText(str+dotStr);
	SetSel(FormatPos(oldpos,oldpos));
}
