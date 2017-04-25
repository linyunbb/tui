#if !defined(AFX_TABLEDLG1102_H__A4A1B326_A330_40EA_8589_E15E72FBCDB8__INCLUDED_)
#define AFX_TABLEDLG1102_H__A4A1B326_A330_40EA_8589_E15E72FBCDB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TableDlg1102.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1102 dialog

class CTableDlg1102 : public CDialog
{
// Construction
public:
	CTableDlg1102(CWnd* pParent = NULL);   // standard constructor
	CIndividual* pInd;

// Dialog Data
	//{{AFX_DATA(CTableDlg1102)
	enum { IDD = IDD_TABLE_1102 };
	CComboBox	m_CultivateResultCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableDlg1102)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTableDlg1102)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnConfirm();
	afx_msg void OnSelchangeCultivateResult();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABLEDLG1102_H__A4A1B326_A330_40EA_8589_E15E72FBCDB8__INCLUDED_)
