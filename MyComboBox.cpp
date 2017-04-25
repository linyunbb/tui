// MyComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "TUI.h"
#include "MyComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyComboBox

CMyComboBox::CMyComboBox()
{
}

CMyComboBox::~CMyComboBox()
{
}


BEGIN_MESSAGE_MAP(CMyComboBox, CComboBox)
	//{{AFX_MSG_MAP(CMyComboBox)
	ON_WM_KEYDOWN()
	ON_CONTROL_REFLECT(CBN_SETFOCUS, OnSetfocus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyComboBox message handlers

void CMyComboBox::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if( nChar == VK_RETURN ) /* ����Enter�� */
	{
		/* ת����һ���봦, �����һ��ʱ�򸸴��ڷ�����һ����Ϣ */
		CWnd *pWnd;
		pWnd = GetParent()->GetNextDlgTabItem(this);
		if( pWnd != NULL)
		{
			if( pWnd->IsKindOf(RUNTIME_CLASS(CEdit) ) )
			{
				pWnd->SetFocus();
				((CEdit*)pWnd)->SetSel(0,-1);
			}
			else
			{
				pWnd->SetFocus();
				//GetParent()->SendMessage(WM_NEXT_QUESTION);
				
				/* ��ťʱ����Ϊ���㲢���԰�Enter������*/
				/*
				((CButton*)pWnd)->SetFocus(); 
				((CButton*)pWnd)->SetButtonStyle(BS_DEFPUSHBUTTON);
				*/
			}
		}
		return;
	}
	CComboBox::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMyComboBox::OnSetfocus() 
{
	ShowDropDown(TRUE);		
}
