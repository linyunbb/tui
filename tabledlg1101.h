#if !defined(AFX_TABLE1DLG_H__14F6ED2F_268A_4E5C_A5EC_3A3B741FD3C7__INCLUDED_)
#define AFX_TABLE1DLG_H__14F6ED2F_268A_4E5C_A5EC_3A3B741FD3C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Table1Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTable1Dlg dialog
#include "MyEdit.h"
class CTableDlg1101 : public CDialog
{
// Construction
public:
	void GotoNextInput(CWnd* pCurWnd);
	CIndividual* pInd;
	CTableDlg1101(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTableDlg1101)
	enum { IDD = IDD_TABLE_1101 };
	CMyEdit	m_AgeCtrl;
	CMyEdit	m_BornAddressCtrl;
	CMyEdit	m_CurrentAddressCtrl;
	CMyEdit	m_ContactInfoCtrl;
	CMyEdit	m_NameCtrl;
	CMyEdit	m_RegisterNoCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableDlg1101)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTableDlg1101)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnConfirm();
	afx_msg void OnSetfocusSexCombo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABLE1DLG_H__14F6ED2F_268A_4E5C_A5EC_3A3B741FD3C7__INCLUDED_)
