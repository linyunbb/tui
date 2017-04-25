#if !defined(AFX_TABLEDLG2200_H__1BB11C5D_475A_458A_81AB_5D1D58FFCB04__INCLUDED_)
#define AFX_TABLEDLG2200_H__1BB11C5D_475A_458A_81AB_5D1D58FFCB04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TableDlg2200.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTableDlg2200 dialog
#include "MyEdit.h"
class CTableDlg2200 : public CDialog
{
// Construction
public:
	CTableDlg2200(CWnd* pParent = NULL);   // standard constructor
	CIndividual* pInd;

// Dialog Data
	//{{AFX_DATA(CTableDlg2200)
	enum { IDD = IDD_TABLE_2200 };
	CMyEdit	m_DoctorNameCtrl;
	CMyEdit	m_F18;
	CMyEdit	m_F17;
	CMyEdit	m_F16;
	CMyEdit	m_F15;
	CMyEdit	m_F14;
	CMyEdit	m_F12;
	CMyEdit	m_F11;
	CMyEdit	m_F10;
	CMyEdit	m_F9;
	CMyEdit	m_F8;
	CMyEdit	m_F7;
	CMyEdit	m_F6;
	CMyEdit	m_F5;
	CMyEdit	m_F4;
	CMyEdit	m_F3;
	CMyEdit	m_F2;
	CMyEdit	m_F1;
	CComboBox	m_MedicareCategoryCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableDlg2200)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTableDlg2200)
	virtual void OnCancel();
	afx_msg void OnConfirm();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeMedicalCareCategory();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABLEDLG2200_H__1BB11C5D_475A_458A_81AB_5D1D58FFCB04__INCLUDED_)
