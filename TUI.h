// TUI.h : main header file for the TUI application
//

#if !defined(AFX_TUI_H__7191B9D2_A068_4571_AF8C_65F21ED7CF55__INCLUDED_)
#define AFX_TUI_H__7191B9D2_A068_4571_AF8C_65F21ED7CF55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTUIApp:
// See TUI.cpp for the implementation of this class
//

class CTUIApp : public CWinApp
{
public:
	CTUIApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTUIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTUIApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TUI_H__7191B9D2_A068_4571_AF8C_65F21ED7CF55__INCLUDED_)
