#if !defined(AFX_SINPUTPARTMODIFICATION_H__D23E9EA1_7D4B_11DB_B910_8DCF064CC214__INCLUDED_)
#define AFX_SINPUTPARTMODIFICATION_H__D23E9EA1_7D4B_11DB_B910_8DCF064CC214__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SInputPartModification.h : header file
//
/*
	Copyright Gabriel Dimitriu
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the definition of Input Parts for Simulation Coordinator.
	
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
// CSInputPartModification dialog
#include "GCElem.h"
#include "GCoordinator.h"
#include "GNetworkS.h"
#include "stdafx.h"
#include "element.h"
#include "SQueue.h"

class CSInputPartModification : public CDialog
{
// Construction
public:
	void SetQueue(CSQueue *qu);
	void SetParent(CGNetworkS *net);
	void Set(CGCoordinator *coord);
	CSInputPartModification(CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CSInputPartModification)
	enum { IDD = IDD_InputPartModification };
	CComboBox	m_up_levels;
	CComboBox	m_oldelem;
	CComboBox	m_from;
	CString	m_errors;
	double	m_time;
	CString	m_wireshist;
	CString	m_levels;
	CString	m_copy_levels;
	long	m_copy_from;
	long	m_copy_element;
	long	m_copy_level;
	long	m_element;
	long	m_level;
	long	m_fromtoport;
	long	m_toport;
	long	m_topart;
	BOOL	m_passive;
	BOOL	m_new;
	BOOL	m_all;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSInputPartModification)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CGNetworkS *m_cLevel;
	CPtrArray networks;
	CPtrArray from_element;
	CPtrArray want_element;
	CPtrArray str_levels;
	CGCoordinator *m_coordinator;
	CGNetworkS *m_parent;
	CObject *m_cPart;
	element *m_elem;
	CSQueue *m_queue;
	// Generated message map functions
	//{{AFX_MSG(CSInputPartModification)
	afx_msg void Onaddelem();
	afx_msg void Onaddwire();
	afx_msg void Ondel();
	afx_msg void Oncopydown();
	afx_msg void Oncopyreset();
	afx_msg void Oncopyup();
	afx_msg void Onleveldown();
	afx_msg void Onlevelreset();
	afx_msg void Onlevelup();
	afx_msg void Onfromnet();
	afx_msg void Onfromproc();
	afx_msg void Onwantnet();
	afx_msg void Onstandalone();
	afx_msg void OnSelendokfrom();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void wantport();
	void wantproc();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SINPUTPARTMODIFICATION_H__D23E9EA1_7D4B_11DB_B910_8DCF064CC214__INCLUDED_)
