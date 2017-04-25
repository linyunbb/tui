#if !defined(AFX_TABLEDLG1426_H__03862EB1_2EA6_4307_B60A_B60A54C646C1__INCLUDED_)
#define AFX_TABLEDLG1426_H__03862EB1_2EA6_4307_B60A_B60A54C646C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TableDlg1426.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1426 dialog

class CTableDlg1426 : public CDialog
{
// Construction
public:
	CTableDlg1426(CWnd* pParent = NULL);   // standard constructor
	CIndividual* pInd;

// Dialog Data
	//{{AFX_DATA(CTableDlg1426)
	enum { IDD = IDD_TABLE_1426 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableDlg1426)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTableDlg1426)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnConfirm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABLEDLG1426_H__03862EB1_2EA6_4307_B60A_B60A54C646C1__INCLUDED_)
