#if !defined(AFX_TABLEDLG1402TO1425_H__FF6F172F_4406_4FEC_8246_5BDA0D7AE5CC__INCLUDED_)
#define AFX_TABLEDLG1402TO1425_H__FF6F172F_4406_4FEC_8246_5BDA0D7AE5CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TableDlg1402TO1425.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1402TO1425 dialog
#include "MyEdit.h"
class CTableDlg1402TO1425 : public CDialog
{
// Construction
public:
	CString items[24];
	int m_Month;
	CTableDlg1402TO1425(CWnd* pParent = NULL);   // standard constructor
	CIndividual* pInd;

// Dialog Data
	//{{AFX_DATA(CTableDlg1402TO1425)
	enum { IDD = IDD_TABLE_1402_1425 };
	CComboBox	m_IsInHospitalCtrl;
	CMyEdit	m_TakeOthersCtrl;
	CMyEdit	m_WeightCtrl;
	CMyEdit	m_InHispitalDaysCtrl;
	CComboBox	m_IsProjectChangedCtrl;
	CComboBox	m_AbnormalCategoryCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableDlg1402TO1425)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTableDlg1402TO1425)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnConfirm();
	afx_msg void OnSelchangeAbnormalType();
	afx_msg void OnSelchangeIsProjectChanged();
	afx_msg void OnSelchangeIsInHospital();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABLEDLG1402TO1425_H__FF6F172F_4406_4FEC_8246_5BDA0D7AE5CC__INCLUDED_)
