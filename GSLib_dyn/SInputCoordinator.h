#if !defined(AFX_SINPUTCOORDINATOR_H__622F0D23_70AF_11DB_B910_EF7FCB55F268__INCLUDED_)
#define AFX_SINPUTCOORDINATOR_H__622F0D23_70AF_11DB_B910_EF7FCB55F268__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SInputCoordinator.h : header file
//
/*
	Copyright Gabriel Dimitriu
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the definition of Input data for Simulation Coordinator.
	
    Generic Simulator is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Generic Simulator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Generic Simulator; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  
*/

/////////////////////////////////////////////////////////////////////////////
// CSInputCoordinator dialog
#include "resource.h"
#include "GNetworkS.h"
#include "stdafx.h"
#include "element.h"
#include "SQueue.h"

class CSInputCoordinator : public CDialog
{
// Construction
public:
	void Serialize(CArchive &ar);
	virtual BOOL OnInitDialog();
	void SetParent(CGNetworkS *net);
	CSInputCoordinator(CWnd* pParent = NULL);   // standard constructor
	CSQueue queue;
// Dialog Data
	//{{AFX_DATA(CSInputCoordinator)
	enum { IDD = IDD_InputCoordinator };
	CString	m_filename;
	CString	m_timetable;
	long	m_dim;
	long	m_portname;
	double	m_time;
	CString	m_InputData;
	CString	m_repartition;
	CString	m_error;
	double	m_clkadvance;
	double	m_clkprec;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSInputCoordinator)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CGNetworkS *m_parent;
	element *m_elem;
	element *m_temp;
	// Generated message map functions
	//{{AFX_MSG(CSInputCoordinator)
	afx_msg void OnAdd();
	afx_msg void Oncheck();
	afx_msg void OnDelete();
	afx_msg void OnLoad();
	afx_msg void OnSave();
	afx_msg void Onmodify();
	afx_msg void Onnext();
	afx_msg void Onprev();
	afx_msg void OngDim();
	afx_msg void Onreset();
	afx_msg void Onrelinkup();
	afx_msg void Onrelinkdown();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SINPUTCOORDINATOR_H__622F0D23_70AF_11DB_B910_EF7FCB55F268__INCLUDED_)
