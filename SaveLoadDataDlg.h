#if !defined(AFX_SAVELOADDATADLG_H__3A8B3B1E_C513_4D54_84AD_22DDB047A408__INCLUDED_)
#define AFX_SAVELOADDATADLG_H__3A8B3B1E_C513_4D54_84AD_22DDB047A408__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SaveLoadDataDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSaveLoadDataDlg dialog

class CSaveLoadDataDlg : public CDialog
{
// Construction
public:
	BOOL isSaving;
	CSaveLoadDataDlg(CData &data, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSaveLoadDataDlg)
	enum { IDD = IDD_SAVE_LOAD_DATA_DLG };
	CProgressCtrl	m_SaveLoadDataCtrl;
	CData &m_Data;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaveLoadDataDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSaveLoadDataDlg)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVELOADDATADLG_H__3A8B3B1E_C513_4D54_84AD_22DDB047A408__INCLUDED_)
