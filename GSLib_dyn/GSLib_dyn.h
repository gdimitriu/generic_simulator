// GSLib_dyn.h : main header file for the GSLIB_DYN DLL
//

#if !defined(AFX_GSLIB_DYN_H__89AE72D1_6F11_11DB_B910_BE3FED94C247__INCLUDED_)
#define AFX_GSLIB_DYN_H__89AE72D1_6F11_11DB_B910_BE3FED94C247__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif
#include "GSLib.h"
#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGSLib_dynApp
// See GSLib_dyn.cpp for the implementation of this class
//

class CGSLib_dynApp : public CWinApp
{
public:
	CGSLib_dynApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGSLib_dynApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CGSLib_dynApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GSLIB_DYN_H__89AE72D1_6F11_11DB_B910_BE3FED94C247__INCLUDED_)
