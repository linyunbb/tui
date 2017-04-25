// MyTabCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "TUI.h"
#include "MyTabCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyTabCtrl

CMyTabCtrl::CMyTabCtrl()
{
}

CMyTabCtrl::~CMyTabCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CMyTabCtrl)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTabCtrl message handlers

void CMyTabCtrl::OnPaint() 
{
//	CPaintDC dc(this); // device context for painting
	
	CTabCtrl::OnPaint();
	int index = GetCurSel();
	if( index < 0 )
	{
		return;
	}
	CClientDC dc(this); //必须是客户区
	CRect rect;
	GetItemRect(index,rect);
	dc.SetBkMode(TRANSPARENT);
	dc.FillSolidRect(rect,RGB(237,225,251));
	dc.SetTextCharacterExtra(-1);
	dc.TextOut(rect.left,rect.top,caption.GetAt(index));	
	// Do not call CTabCtrl::OnPaint() for painting messages
}
