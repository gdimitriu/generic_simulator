#if !defined(AFX_FUNCTIONS_H__DAA6B5A1_9E5C_11DB_B910_D46369C2E1C9__INCLUDED_)
#define AFX_FUNCTIONS_H__DAA6B5A1_9E5C_11DB_B910_D46369C2E1C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Functions.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CFunctions dialog
#include "resource.h"
#include "dynamic.h"
#include "functionality.h"
#include "specialf.h"
#include "Systems.h"
#include "oldTests.h"
#include "tests.h"

class CFunctions : public CDialog
{
// Construction
public:
	CFunctions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFunctions)
	enum { IDD = IDD_functions };
	CComboBox	m_tests;
	CComboBox	m_functions;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFunctions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	Cdynamic *dyn;
	Cfunctionality *func;
	Cspecialf *spec;
	CSystems *syst;
	Ctests *tests;
	ColdTests *oldtests;
	// Generated message map functions
	//{{AFX_MSG(CFunctions)
	afx_msg void OnRun();
	afx_msg void OnSelendokfunctions();
	virtual void OnCancel();
	afx_msg void Onfuncinit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FUNCTIONS_H__DAA6B5A1_9E5C_11DB_B910_D46369C2E1C9__INCLUDED_)
