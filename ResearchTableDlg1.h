#if !defined(AFX_RESEARCHTABLEDLG1_H__A28D3F6B_195C_446F_81E0_4FFD01A33493__INCLUDED_)
#define AFX_RESEARCHTABLEDLG1_H__A28D3F6B_195C_446F_81E0_4FFD01A33493__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResearchTableDlg1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResearchTableDlg1 dialog
#include "MyEdit.h"
class CResearchTableDlg1 : public CDialog
{
// Construction
public:
	CResearchTableDlg1(CWnd* pParent = NULL);   // standard constructor
	CIndividual* pInd;

// Dialog Data
	//{{AFX_DATA(CResearchTableDlg1)
	enum { IDD = IDD_RESEARCH_TABLE_1 };
	CComboBox	m_IsWillingCtrl;
	CComboBox	m_HasRespitatoryCtrl;
	CComboBox	m_HasChronicCtrl;
	CComboBox	m_IsExcludedCtrl;
	CComboBox	m_HasHistoryCtrl;
	CMyEdit	m_DoctorNameCtrl;
	CMyEdit	m_ContactInfo;
	CMyEdit m_LivingYearsCtrl;
	CMyEdit	m_AgeCtrl;
	CMyEdit	m_NameCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResearchTableDlg1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CResearchTableDlg1)
	afx_msg void OnConfirm();
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeLocalLivingYear();
	afx_msg void OnSelchangeTubHistoryYesno();
	afx_msg void OnSelchangeIsExcludedByX();
	afx_msg void OnSelchangeChronicDiseaseHistory();
	afx_msg void OnSelchangeRespiratorySystemDiseaseYesno();
	afx_msg void OnSelchangeIsAgreed();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESEARCHTABLEDLG1_H__A28D3F6B_195C_446F_81E0_4FFD01A33493__INCLUDED_)
