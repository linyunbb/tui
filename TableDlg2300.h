#if !defined(AFX_TABLEDLG2300_H__8EBFE36E_8636_4CF7_8411_C83F5CE12699__INCLUDED_)
#define AFX_TABLEDLG2300_H__8EBFE36E_8636_4CF7_8411_C83F5CE12699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TableDlg2300.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTableDlg2300 dialog
#include "MyEdit.h"
class CTableDlg2300 : public CDialog
{
// Construction
public:
	CTableDlg2300(CWnd* pParent = NULL);   // standard constructor
	CIndividual* pInd;

// Dialog Data
	//{{AFX_DATA(CTableDlg2300)
	enum { IDD = IDD_TABLE_2300 };
	CMyEdit	m_DoctorNameCtrl;
	CMyEdit	m_G12;
	CMyEdit	m_G11;
	CMyEdit	m_G10;
	CMyEdit	m_G9;
	CMyEdit	m_G8;
	CMyEdit	m_G6;
	CMyEdit	m_G5;
	CMyEdit	m_G4;
	CMyEdit	m_G3;
	CMyEdit	m_G2;
	CMyEdit	m_G1;
	CComboBox	m_MedicareCategoryCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableDlg2300)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTableDlg2300)
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

#endif // !defined(AFX_TABLEDLG2300_H__8EBFE36E_8636_4CF7_8411_C83F5CE12699__INCLUDED_)
