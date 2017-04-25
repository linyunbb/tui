#if !defined(AFX_DATECONFIRMDLG_H__7D92C85E_889B_4265_8186_AABB2BF56F97__INCLUDED_)
#define AFX_DATECONFIRMDLG_H__7D92C85E_889B_4265_8186_AABB2BF56F97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DateConfirmDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDateConfirmDlg dialog

class CDateConfirmDlg : public CDialog
{
// Construction
public:
	CString GetInputDate();
	CString m_CurDate;
	CDateConfirmDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDateConfirmDlg)
	enum { IDD = IDD_DATE_CONFIRM_DIALOG };
	CMonthCalCtrl	m_DateCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDateConfirmDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDateConfirmDlg)
	virtual void OnCancel();
	afx_msg void OnConfirm();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeDateInput(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATECONFIRMDLG_H__7D92C85E_889B_4265_8186_AABB2BF56F97__INCLUDED_)
