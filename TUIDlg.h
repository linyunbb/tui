// TUIDlg.h : header file
//

#if !defined(AFX_TUIDLG_H__49A79EA7_36B3_4084_869D_BA5B1F581DFF__INCLUDED_)
#define AFX_TUIDLG_H__49A79EA7_36B3_4084_869D_BA5B1F581DFF__INCLUDED_

#include "Data.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTUIDlg dialog

class CTUIDlg : public CDialog
{
// Construction
public:
	CData m_Data;
	void SerializeFileInfo(BOOL isSaving);
	void InitGlobalData();
	CTUIDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTUIDlg)
	enum { IDD = IDD_TUI_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTUIDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTUIDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnPatientInput();
	afx_msg void OnHealthInfoButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TUIDLG_H__49A79EA7_36B3_4084_869D_BA5B1F581DFF__INCLUDED_)
