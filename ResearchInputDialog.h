#if !defined(AFX_RESEARCHINPUTDIALOG_H__D0B77C87_D580_4817_909A_C4527B8F4606__INCLUDED_)
#define AFX_RESEARCHINPUTDIALOG_H__D0B77C87_D580_4817_909A_C4527B8F4606__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResearchInputDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResearchInputDialog dialog
class CResearchInputDialog : public CDialog
{
// Construction
public:
	int m_WndBottomOffset;
	BOOL ExportToExcel(CString filename, CString sItem, CString eItem, BOOL bIncludeId, BOOL bIsIndex);
	void LoadTableList(UINT iId);
	void LoadPatientList(UINT cId, UINT tId);
	void UpdateWindowRect(int iPatientSel);
	void InitUI();
	CResearchInputDialog(CData &data, CWnd* pParent = NULL);   // standard constructor
	CData &m_Data;
	CImageList* m_pPatientImageList;
	CImageList* m_pSectionOneImageList;
	CRect orginalRect;
	int m_PatientSel;
	CTypedPtrArray<CObArray, CIndividual*>  m_IExportList;

// Dialog Data
	//{{AFX_DATA(CResearchInputDialog)
	enum { IDD = IDD_RESEARCH_INPUT_DIAGLOG };
	CStatic	m_StaticExport;
	CProgressCtrl	m_ExportProgress;
	CEdit	m_FilterCtrl;
	CComboBox	m_TownSel;
	CComboBox	m_CitySel;
	CListCtrl	m_TableList;
	CListCtrl	m_PatientList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResearchInputDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CResearchInputDialog)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCitySelCombo();
	afx_msg void OnSelchangeTownSelCombo();
	afx_msg void OnNewPatient();
	afx_msg void OnChangeFilter();
	afx_msg void OnDeletePatient();
	afx_msg void OnDestroy();
	afx_msg void OnClickPatientList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkTableList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkPatientList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnExportData();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESEARCHINPUTDIALOG_H__D0B77C87_D580_4817_909A_C4527B8F4606__INCLUDED_)
