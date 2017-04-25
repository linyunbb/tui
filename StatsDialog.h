#if !defined(AFX_STATSDIALOG_H__C7328CAC_57E7_4826_94A7_76B564DFF507__INCLUDED_)
#define AFX_STATSDIALOG_H__C7328CAC_57E7_4826_94A7_76B564DFF507__INCLUDED_

#include "Data.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StatsDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStatsDialog dialog

#include "CSpreadSheet.h"
class CStatsDialog : public CDialog
{
// Construction
public:
	CStringArray itemsTotalValue;
	CStringArray itemsCurrentMonthValue;
	CStringArray itemsHead;
	int m_StatsOneCount;
	int m_StatsTwoCount;
	void UpdateStatsTwo();
	void UpdateStats();
	CTypedPtrArray<CObArray, CIndividual*>  *pIndList;
	CString title;
	CStatsDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStatsDialog)
	enum { IDD = IDD_STATS_DIALOG };
	CDateTimeCtrl	m_MonthCtrl;
	CListCtrl	m_StatsTwo;
	CListCtrl	m_StatsOne;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStatsDialog)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnDatetimechangeCurrentMonth(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnExport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATSDIALOG_H__C7328CAC_57E7_4826_94A7_76B564DFF507__INCLUDED_)
