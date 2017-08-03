// element.cpp: implementation of the element class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the implementation of an element. This element is used in processor
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

#include "stdafx.h"
#include "element.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
IMPLEMENT_SERIAL(element,CObject,1);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

element::element()
{
	dim=1;
	data=NULL;
	source=NULL;
	sourcename=-1;
	m_time=-1;
	m_name=-1;
	type=-1;
	manual=1;
	next=prev=NULL;
}

element::~element()
{
	if(data!=NULL)
		free(data);
}

void element::Serialize(CArchive &ar)
{
	long i;
	CObject::Serialize(ar);
	if(ar.IsStoring())
	{
		ar<<dim;
		ar<<m_name;
		ar<<m_time;
		ar<<sourcename;
		ar<<type;
		ar<<manual;
		for(i=0;i<dim;i++)
			ar<<data[i];
	}
	else
	{
		ar>>dim;
		ar>>m_name;
		ar>>m_time;
		ar>>sourcename;
		ar>>type;
		ar>>manual;
		data=(double *)calloc(dim,sizeof(double));
		for(i=0;i<dim;i++)
			ar>>data[i];
	}
}
