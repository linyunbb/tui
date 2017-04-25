#if !defined(AFX_PATIENTINPUTDLG_H__900ABAD0_D895_4D5C_9CF6_9FE81335B065__INCLUDED_)
#define AFX_PATIENTINPUTDLG_H__900ABAD0_D895_4D5C_9CF6_9FE81335B065__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PatientInputDlg.h : header file
//
#include "MyTabCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CPatientInputDlg dialog
class CPatientInputDlg : public CDialog
{
public:
// Construction
public:
	void ClickOnePatient(int iSel);
	static int CALLBACK PatientListCtrlCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	void UpdatePatient(int iSel, BOOL isSel = TRUE, CString sText = "");
	BOOL ExportToExcel(CString filename, CString sItem, CString eItem, BOOL bIncludeId, BOOL bIsIndex);
	void UpdateWindowRect(int iPatientSel);
	void LoadPatientList(UINT cId, UINT tId);
	void LoadTableList(UINT iId, UINT iSection, UINT iSubSection);
	void InitUI();
	int  m_WndBottomOffset;
	int  m_PatientSel;
	CRect orginalRect;
	CData &m_Data;
	CImageList* m_pPatientImageList;
	CImageList* m_pTableImageList;
	CPatientInputDlg(CData &data, CWnd* pParent = NULL);   // standard constructor
	CString m_CurDate;
	CTypedPtrArray<CObArray, CIndividual*>  m_IExportList;
// Dialog Data
	//{{AFX_DATA(CPatientInputDlg)
	enum { IDD = IDD_PATIENT_INPUT_DIALOG };
	CStatic	m_StaticExportCtrl;
	CProgressCtrl	m_ExportProgressCtrl;
	CEdit		m_FilterCtrl;
	CComboBox	m_TownSelCtrl;
	CComboBox	m_CitySelCtrl;
	CMyTabCtrl	m_SectionTabCtrl;
	CMyTabCtrl	m_SubSectionTabCtrl;
	CListCtrl	m_TableListCtrl;
	CListCtrl	m_PatientListCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPatientInputDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPatientInputDlg)
	afx_msg void OnOk();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancelMode();
	afx_msg void OnDblclkTableList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeCitySelCombo();
	afx_msg void OnSelchangeSectionTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNewPatient();
	afx_msg void OnClickPatientList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeTownSelCombo();
	afx_msg void OnSelchangeSubSectionTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	afx_msg void OnDeletePatient();
	afx_msg void OnExportData();
	afx_msg void OnChangeFilter();
	afx_msg void OnDblclkPatientList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckStat();
	afx_msg void OnImportData();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATIENTINPUTDLG_H__900ABAD0_D895_4D5C_9CF6_9FE81335B065__INCLUDED_)
