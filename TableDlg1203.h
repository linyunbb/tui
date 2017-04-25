#if !defined(AFX_TABLEDLG1203_H__4E64B2CF_7E24_4999_8AE3_65B484D137CF__INCLUDED_)
#define AFX_TABLEDLG1203_H__4E64B2CF_7E24_4999_8AE3_65B484D137CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TableDlg1203.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1203 dialog

class CTableDlg1203 : public CDialog
{
// Construction
public:
	CTableDlg1203(CWnd* pParent = NULL);   // standard constructor
	CIndividual* pInd;

// Dialog Data
	//{{AFX_DATA(CTableDlg1203)
	enum { IDD = IDD_TABLE_1203 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableDlg1203)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTableDlg1203)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnConfirm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABLEDLG1203_H__4E64B2CF_7E24_4999_8AE3_65B484D137CF__INCLUDED_)
