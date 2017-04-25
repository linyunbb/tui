#if !defined(AFX_TABLEDLG1301_H__B9BCF0BE_25E2_4CEC_BD7E_86724C3A35BF__INCLUDED_)
#define AFX_TABLEDLG1301_H__B9BCF0BE_25E2_4CEC_BD7E_86724C3A35BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TableDlg1301.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1301 dialog
#include "MyEdit.h"
class CTableDlg1301 : public CDialog
{
// Construction
public:
	CTableDlg1301(CWnd* pParent = NULL);   // standard constructor
	CIndividual* pInd;

// Dialog Data
	//{{AFX_DATA(CTableDlg1301)
	enum { IDD = IDD_TABLE_1301 };
	CComboBox	m_IsBloodTakenCtrl;
	CComboBox	m_InstitutionLevelCtrl;
	CComboBox	m_IsFinishedCtrl;
	CComboBox	m_IsAckedCtrl;
	CMyEdit	m_BloodMLCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableDlg1301)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTableDlg1301)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeIsAcked();
	afx_msg void OnSelchangeIsQuestionairFinished();
	afx_msg void OnSelchangeInstitutionLevel();
	afx_msg void OnSelchangeIsBloodTaken();
	afx_msg void OnConfirm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABLEDLG1301_H__B9BCF0BE_25E2_4CEC_BD7E_86724C3A35BF__INCLUDED_)
