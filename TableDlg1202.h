#if !defined(AFX_TABLEDLG1202_H__A7BA7EA1_590E_4BCF_BEC7_AEA1AAA7FE8E__INCLUDED_)
#define AFX_TABLEDLG1202_H__A7BA7EA1_590E_4BCF_BEC7_AEA1AAA7FE8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TableDlg1202.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1202 dialog

class CTableDlg1202 : public CDialog
{
// Construction
public:
	CTableDlg1202(CWnd* pParent = NULL);   // standard constructor
	CIndividual* pInd;

// Dialog Data
	//{{AFX_DATA(CTableDlg1202)
	enum { IDD = IDD_TABLE_1202 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableDlg1202)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTableDlg1202)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnConfirm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABLEDLG1202_H__A7BA7EA1_590E_4BCF_BEC7_AEA1AAA7FE8E__INCLUDED_)
