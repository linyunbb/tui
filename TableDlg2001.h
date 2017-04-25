#if !defined(AFX_TABLEDLG2001_H__8BBAE249_C5DE_43AF_9FD4_3623CC571B24__INCLUDED_)
#define AFX_TABLEDLG2001_H__8BBAE249_C5DE_43AF_9FD4_3623CC571B24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TableDlg2001.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTableDlg2001 dialog
#include "MyEdit.h"
class CTableDlg2001 : public CDialog
{
// Construction
public:
	CTableDlg2001(CWnd* pParent = NULL);   // standard constructor
	CIndividual* pInd;

// Dialog Data
	//{{AFX_DATA(CTableDlg2001)
	enum { IDD = IDD_TABLE_2001 };
	CMyEdit	m_DoctorName;
	CMyEdit	m_FeeForMealsACtrl;
	CMyEdit	m_HowManyMealsACtrl;
	CMyEdit	m_FeeForStayOutSideACtrl;
	CMyEdit	m_FeeForVehicleACtrl;
	CMyEdit	m_HowManyAccomanyCtrl;
	CMyEdit	m_FeeForMealCtrl;
	CMyEdit	m_HowManyMealsCtrl;
	CMyEdit	m_FeeForStayOutsideCtrl;
	CMyEdit	m_FeeForVehicleCtrl;
	CMyEdit	m_HowFarCtrl;
	CComboBox	m_IsCompanyStayOutSide;
	CComboBox	m_HasCompanyCtrl;
	CComboBox	m_IsStayOutside;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTableDlg2001)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTableDlg2001)
	virtual void OnCancel();
	afx_msg void OnConfirm();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeIsStayOutside();
	afx_msg void OnSelchangeIsAccompany();
	afx_msg void OnSelchangeIsStayOutsideAccompany();
	afx_msg void OnChangeHowManyDinners();
	afx_msg void OnChangeHowManyDinnersAccompany();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABLEDLG2001_H__8BBAE249_C5DE_43AF_9FD4_3623CC571B24__INCLUDED_)
