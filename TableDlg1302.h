#if !defined(AFX_TABLEDLG1302_H__2161C63A_90F9_415F_9BCC_DBA30CC61D90__INCLUDED_)
#define AFX_TABLEDLG1302_H__2161C63A_90F9_415F_9BCC_DBA30CC61D90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TableDlg1302.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1302 dialog

class CTableDlg1302 : public CDialog
{
// Construction
public:
	CTableDlg1302(CWnd* pParent = NULL);   // standard constructor
	CIndividual* pInd;

// Dialog Data
	//{{AFX_DATA(CTableDlg1302)
	enum { IDD = IDD_TABLE_1302 };
	CComboBox	m_IsToNationalCtrl;
	CComboBox	m_IsToProvinceCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableDlg1302)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTableDlg1302)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeIsToProvince();
	afx_msg void OnSelchangeIsToNational();
	afx_msg void OnConfirm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABLEDLG1302_H__2161C63A_90F9_415F_9BCC_DBA30CC61D90__INCLUDED_)
