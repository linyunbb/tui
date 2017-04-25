#if !defined(AFX_TABLEDLG1204_H__D078B6D6_1D5F_4871_990F_B55F629C85A3__INCLUDED_)
#define AFX_TABLEDLG1204_H__D078B6D6_1D5F_4871_990F_B55F629C85A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TableDlg1204.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1204 dialog

class CTableDlg1204 : public CDialog
{
// Construction
public:
	CTableDlg1204(CWnd* pParent = NULL);   // standard constructor
	CIndividual* pInd;

// Dialog Data
	//{{AFX_DATA(CTableDlg1204)
	enum { IDD = IDD_TABLE_1204 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableDlg1204)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTableDlg1204)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnConfirm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABLEDLG1204_H__D078B6D6_1D5F_4871_990F_B55F629C85A3__INCLUDED_)
