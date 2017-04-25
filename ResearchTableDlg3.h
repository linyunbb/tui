#if !defined(AFX_RESEARCHTABLEDLG3_H__F70DEAB1_7CBE_4A15_B277_652AFF81ECB0__INCLUDED_)
#define AFX_RESEARCHTABLEDLG3_H__F70DEAB1_7CBE_4A15_B277_652AFF81ECB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResearchTableDlg3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResearchTableDlg3 dialog

class CResearchTableDlg3 : public CDialog
{
// Construction
public:
	CResearchTableDlg3(CWnd* pParent = NULL);   // standard constructor
	CIndividual* pInd;

// Dialog Data
	//{{AFX_DATA(CResearchTableDlg3)
	enum { IDD = IDD_RESEARCH_TABLE_3 };
	CComboBox	m_IsToNational;
	CComboBox	m_IsToProvince;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResearchTableDlg3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CResearchTableDlg3)
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnConfirm();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeIsToProvince();
	afx_msg void OnSelchangeIsToNational();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESEARCHTABLEDLG3_H__F70DEAB1_7CBE_4A15_B277_652AFF81ECB0__INCLUDED_)
