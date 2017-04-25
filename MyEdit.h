#if !defined(AFX_MYEDIT_H__20257A3C_4879_4D0C_B932_AECC584E0AD7__INCLUDED_)
#define AFX_MYEDIT_H__20257A3C_4879_4D0C_B932_AECC584E0AD7__INCLUDED_

#include "Tools.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyEdit window

typedef enum tagDATA_TYPE_EN
{
	DATA_TYPE_DATE,
	DATA_TYPE_SHORT_DATE,
	DATA_TYPE_NUMBER,
	DATA_TYPE_NO_CHINESE,
	DATA_TYPE_MONEY,
	DATA_TYPE_AGE,
	DATA_TYPE_BUTT
}DATA_TYPE_EN;

class CMyEdit : public CEdit
{
// Construction
public:
	CMyEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	void RemovePreZero();
	void InitEdit(int type, int len,  CString sRecVal);
	void MsgForInputValid(CString msg);
	BOOL IsDate(UINT nChar);
	CString GetBlankAnswer();
	CString GetDefaultAnswer();
	BOOL CheckInput();
	DWORD FormatPos(int hPos,int lPos);
	void InitEdit(CString sID="");
	CString sDefault;
	CString m_ID;
	BOOL m_bMsgInform;
	int m_enType;
	int m_nLen;
	int m_DotPos;

	inline BOOL IsNum(char ch)
	{
		if( (ch>='0') && (ch<='9') )
		{
			return TRUE;
		}
		return FALSE;
	}
	inline BOOL IsLetter(char ch)
	{
		if( ( (ch>='a') && (ch<='z') )
		||  ( (ch>='A') && (ch<='Z') ) )
		{
			return TRUE;
		}
		return FALSE;
	}
	virtual ~CMyEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyEdit)
	//afx_msg void OnChange();
	afx_msg void OnSetfocus();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYEDIT_H__20257A3C_4879_4D0C_B932_AECC584E0AD7__INCLUDED_)
