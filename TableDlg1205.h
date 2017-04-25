#if !defined(AFX_TABLEDLG1205_H__AAFEAF65_285D_42FC_B75B_EE52F039CFA5__INCLUDED_)
#define AFX_TABLEDLG1205_H__AAFEAF65_285D_42FC_B75B_EE52F039CFA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TableDlg1205.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1205 dialog

class CTableDlg1205 : public CDialog
{
// Construction
public:
	CTableDlg1205(CWnd* pParent = NULL);   // standard constructor
	CIndividual* pInd;

// Dialog Data
	//{{AFX_DATA(CTableDlg1205)
	enum { IDD = IDD_TABLE_1205 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableDlg1205)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTableDlg1205)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnConfirm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABLEDLG1205_H__AAFEAF65_285D_42FC_B75B_EE52F039CFA5__INCLUDED_)
