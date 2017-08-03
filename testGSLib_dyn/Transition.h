// Transition.h: interface for the CTransition class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright 2005 Gabriel Dimitriu

	This file is part of Generic Simulator.
	This file contains the definition of transition class. This class is the real 
	class who implement the real function of the active element. This is particularized
	to parallel machines.
	
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

#if !defined(AFX_TRANSITION_H__30C13E7A_C92C_47CD_AC11_6C00746B4AD4__INCLUDED_)
#define AFX_TRANSITION_H__30C13E7A_C92C_47CD_AC11_6C00746B4AD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <GTransition.h>

using namespace std ;

class CTransition : public CGTransition  
{
	DECLARE_SERIAL(CTransition)
public:
	virtual void Serialize(CArchive &ar);
	CTransition();
	virtual ~CTransition();
	CTransition(CString *val);
	virtual void proc_deltaext(CGProcessor *proc,CGData *data,long *s,CObArray *value,CObArray *value_n,long nr);
	virtual void proc_deltaint(CGProcessor *proc,long *s,CObArray *value,CObArray *value_n,long nr);
	virtual int proc_lambda(CGProcessor *proc,element *val,long port);
protected:
	bool m_freset;
};

#endif // !defined(AFX_TRANSITION_H__30C13E7A_C92C_47CD_AC11_6C00746B4AD4__INCLUDED_)
