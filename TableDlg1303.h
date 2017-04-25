#if !defined(AFX_TABLEDLG1303_H__3C7FB622_2D6D_46C5_8504_8280A4B0B659__INCLUDED_)
#define AFX_TABLEDLG1303_H__3C7FB622_2D6D_46C5_8504_8280A4B0B659__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TableDlg1303.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1303 dialog

class CTableDlg1303 : public CDialog
{
// Construction
public:
	CTableDlg1303(CWnd* pParent = NULL);   // standard constructor
	CIndividual* pInd;

// Dialog Data
	//{{AFX_DATA(CTableDlg1303)
	enum { IDD = IDD_TABLE_1303 };
	CComboBox	m_IsToNationalCtrl;
	CComboBox	m_IsToProvinceCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableDlg1303)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTableDlg1303)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeIsToProvince();
	afx_msg void OnSelchangeIsToNational();
	afx_msg void OnConfirm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABLEDLG1303_H__3C7FB622_2D6D_46C5_8504_8280A4B0B659__INCLUDED_)
