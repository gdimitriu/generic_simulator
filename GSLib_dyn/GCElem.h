// GCElem.h: interface for the CGCElem class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the definition of storage element for CGCoordinator.
	
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

#if !defined(AFX_GCELEM_H__F423DFE6_2B88_11DB_B910_FE47FC09D509__INCLUDED_)
#define AFX_GCELEM_H__F423DFE6_2B88_11DB_B910_FE47FC09D509__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "stdafx.h"

class CGCElem : public CObject  
{
public:
	int Send();
	CGCElem();
	CGCElem(CObject *parent,int type,double time,CObject *sender);
	CGCElem(CObject *parent,int type,double time,CObject *sender,CObject *dead);
	virtual ~CGCElem();
	CObject *m_parent;
	CObject *m_sender;
	CObject *m_dead;
	int m_type;
	double m_time;
};

#endif // !defined(AFX_GCELEM_H__F423DFE6_2B88_11DB_B910_FE47FC09D509__INCLUDED_)
