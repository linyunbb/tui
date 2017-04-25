#if !defined(AFX_TABLEDLG1201_H__946D840C_D6D7_42A3_ADCB_BDBE6B95630A__INCLUDED_)
#define AFX_TABLEDLG1201_H__946D840C_D6D7_42A3_ADCB_BDBE6B95630A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TableDlg1201.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTableDlg1201 dialog

class CTableDlg1201 : public CDialog
{
// Construction
public:
	CTableDlg1201(CWnd* pParent = NULL);   // standard constructor
	CIndividual* pInd;
// Dialog Data
	//{{AFX_DATA(CTableDlg1201)
	enum { IDD = IDD_TABLE_1201 };
	CComboBox	m_ExamineResultCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableDlg1201)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTableDlg1201)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnConfirm();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABLEDLG1201_H__946D840C_D6D7_42A3_ADCB_BDBE6B95630A__INCLUDED_)
