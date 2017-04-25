#if !defined(AFX_TABLEDLG1401_H__A9599D0D_AEE4_4452_872A_92F9DF522D91__INCLUDED_)
#define AFX_TABLEDLG1401_H__A9599D0D_AEE4_4452_872A_92F9DF522D91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TableDlg1401.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1401 dialog
#include "MyEdit.h"
class CTableDlg1401 : public CDialog
{
// Construction
public:
	CTableDlg1401(CWnd* pParent = NULL);   // standard constructor
	CIndividual* pInd;

// Dialog Data
	//{{AFX_DATA(CTableDlg1401)
	enum { IDD = IDD_TABLE_1401 };
	CComboBox	m_ProjectSelCtrl;
	CMyEdit	m_FirstTreatProjectCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableDlg1401)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTableDlg1401)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnConfirm();
	afx_msg void OnSelchangeProjectSel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABLEDLG1401_H__A9599D0D_AEE4_4452_872A_92F9DF522D91__INCLUDED_)
