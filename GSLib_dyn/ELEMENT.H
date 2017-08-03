// element.h: interface for the element class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the definition of an element. This element is used in processor
	for storing information and for simulation queue.
	
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

#if !defined(AFX_ELEMENT_H__FA5A5AFB_5A60_4738_9F02_627D3B310D48__INCLUDED_)
#define AFX_ELEMENT_H__FA5A5AFB_5A60_4738_9F02_627D3B310D48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
using namespace std ;

class element : public CObject 
{
	DECLARE_SERIAL(element);
public:
	virtual void Serialize(CArchive& ar);
	long m_name;
	double m_time;
	element();
	virtual ~element();
	double *data;
	long dim;
	CObject *source;
	CObject *dead;
	CObject *parent;
	long sourcename;
	int type;
	int manual;
	element *next;
	element *prev;
};

#endif // !defined(AFX_ELEMENT_H__FA5A5AFB_5A60_4738_9F02_627D3B310D48__INCLUDED_)
