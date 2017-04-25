#if !defined(AFX_IMPORTDATADLG_H__9B941546_5761_4939_8FA9_104FBA246D1D__INCLUDED_)
#define AFX_IMPORTDATADLG_H__9B941546_5761_4939_8FA9_104FBA246D1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImportDataDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImportDataDlg dialog

class CImportDataDlg : public CDialog
{
// Construction
public:
	BOOL VerifyInput(UINT nIndex, CStringArray &recStrs);
	CIndividual* pInd;
	CString curDate;
	int conflictCount;
	void LoadExcelRecs();
	CString strTownName;
	CString m_ExcelFile;
	CStringArray ConflictInfo[1000];
	UINT iIndex;
	CImportDataDlg(CWnd* pParent = NULL);   // standard constructor
	CTypedPtrMap<CMapPtrToPtr, void*, void*> m_IdMap;
	CTypedPtrArray<CObArray, CIndividual*>  m_IImportList;
// Dialog Data
	//{{AFX_DATA(CImportDataDlg)
	enum { IDD = IDD_IMPORT_DATA };
	CListBox	m_IndOKListCtrl;
	CProgressCtrl	m_LoadDataProcess;
	CListBox	m_ConflictList;
	CListBox	m_IndList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImportDataDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImportDataDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnConfirm();
	afx_msg void OnSelchangeIndList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPORTDATADLG_H__9B941546_5761_4939_8FA9_104FBA246D1D__INCLUDED_)
