#if !defined(AFX_RESEARCHTABLEDLG2_H__663F2EF1_A5C3_4B00_B1BD_FCB5F2C05D88__INCLUDED_)
#define AFX_RESEARCHTABLEDLG2_H__663F2EF1_A5C3_4B00_B1BD_FCB5F2C05D88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResearchTableDlg2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResearchTableDlg2 dialog
#include "MyEdit.h"
class CResearchTableDlg2 : public CDialog
{
// Construction
public:
	CResearchTableDlg2(CWnd* pParent = NULL);   // standard constructor
	CIndividual* pInd;

// Dialog Data
	//{{AFX_DATA(CResearchTableDlg2)
	enum { IDD = IDD_RESEARCH_TABLE_2 };
	CComboBox	m_IsBloodTaken;
	CComboBox	m_IsFinished;
	CComboBox	m_IsAcked;
	CMyEdit	m_BloodCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResearchTableDlg2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CResearchTableDlg2)
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnConfirm();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeIsAcked();
	afx_msg void OnSelchangeIsQuestionairFinished();
	afx_msg void OnSelchangeIsBloodTaken();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESEARCHTABLEDLG2_H__663F2EF1_A5C3_4B00_B1BD_FCB5F2C05D88__INCLUDED_)
