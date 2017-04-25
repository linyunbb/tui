#if !defined(AFX_TABLEDLG1206_H__121F4096_97F6_47BA_9BE9_96587E4926AA__INCLUDED_)
#define AFX_TABLEDLG1206_H__121F4096_97F6_47BA_9BE9_96587E4926AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TableDlg1206.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1206 dialog
#include "MyEdit.h"
class CTableDlg1206 : public CDialog
{
// Construction
public:
	CTableDlg1206(CWnd* pParent = NULL);   // standard constructor
	CIndividual* pInd;

// Dialog Data
	//{{AFX_DATA(CTableDlg1206)
	enum { IDD = IDD_TABLE_1206 };
	CComboBox	m_DiagResultCtrl;
	CComboBox	m_PatientInfoCtrl;
	CComboBox	m_IsWillingToBeSearched;
	CComboBox	m_IsSuitableCtrl;
	CMyEdit	m_NDYRegisterNoCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableDlg1206)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTableDlg1206)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnConfirm();
	afx_msg void OnSelchangeIsSuitable();
	afx_msg void OnSelchangeWillingToBeSearched();
	afx_msg void OnSelchangePatientSearchInfo();
	afx_msg void OnSelchangeDiagnosticResult();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABLEDLG1206_H__121F4096_97F6_47BA_9BE9_96587E4926AA__INCLUDED_)
