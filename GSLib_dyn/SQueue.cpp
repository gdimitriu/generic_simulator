// SQueue.cpp: implementation of the CSQueue class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the implementation of simulation Queue for CSCoordinator.
	
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
#include "SQueue.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
IMPLEMENT_SERIAL(CSQueue,CObject,1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSQueue::CSQueue()
{
	m_start=m_current=m_parc=m_end=NULL;
	m_nr=0;
}

CSQueue::~CSQueue()
{

}

void CSQueue::Serialize(CArchive &ar)
{
	long i;
	CObject *ob;
	CObject::Serialize(ar);
	if(ar.IsStoring())
	{
		ar<<m_nr;
		ar<<m_start;
		m_parc=m_start->next;
		for(i=1;i<m_nr;i++)
		{
			ar<<m_parc;
			m_parc=m_parc->next;
		}
	}
	else
	{
		ar>>m_nr;
		ar>>ob;
		m_start=(element *)ob;
		m_start->prev=NULL;
		m_parc=m_start;
		for(i=1;i<m_nr;i++)
		{
			ar>>ob;
			m_parc->next=(element *)ob;
			m_parc->next->prev=m_parc;
			m_parc=m_parc->next;
		}
		m_end=m_parc;
		m_parc->next=NULL;
		m_current=m_start;
	}	
}

element * CSQueue::Get()
{
	if(m_start==NULL)
		return NULL;
	m_parc=m_start;
	m_start=m_start->next;
	if(m_start!=NULL)
		m_start->prev=NULL;
	else m_end=NULL;
	m_nr--;
	return m_parc;
}

int CSQueue::Add(element *el)
{
	if(m_start==NULL)
	{
		m_start=el;
		m_start->next=m_start->prev=NULL;
		m_nr++;
		m_current=m_start;
		m_end=m_start;
		return 0;
	}
	if(m_start->m_time>el->m_time)
	{
		m_parc=m_start;
		m_start=el;
		m_start->next=m_parc;
		m_start->prev=NULL;
		m_parc->prev=m_start;
		m_current=m_start;
		m_nr++;
		return 0;
	}
	if(m_end->m_time<el->m_time)
	{
		m_end->next=el;
		el->prev=m_end;
		el->next=NULL;
		if(m_current==m_end)
			m_current=el;
		m_end=el;
		m_nr++;
		return 0;
	}
	m_parc=m_start;
	while(m_parc!=NULL)
	{
		if(m_parc->next!=NULL)
		{
			if(m_parc->m_time<el->m_time && m_parc->next->m_time>el->m_time)
			{
				m_parc->next->prev=el;
				el->next=m_parc->next;
				el->prev=m_parc;
				m_parc->next=el;
				m_nr++;
				return 1;
			}
			if(m_parc->next->m_time>el->m_time && fabs(m_parc->m_time-el->m_time)<precision)
			{
				el->next=m_parc->next;
				el->prev=m_parc;
				el->next->prev=el;
				m_parc->next=el;
				m_nr++;
				return 1;
			}

		}
		if(fabs(m_parc->m_time-el->m_time)<precision)
		{
			if(m_parc->type==el->type)
			{
				if(el->type==0 || el->type==1 || el->type==3) return -1;
				if(m_parc->next!=NULL)
				{
					el->prev=m_parc;
					el->next=m_parc->next;
					m_parc->next->prev=el;
					m_parc->next=el;
				}
				else
				{
					el->prev=m_parc;
					el->next=NULL;
					m_parc->next=el;
					m_end=el;
				}
				m_nr++;
				return 1;
			}
			else
			{
				if(el->type==4 || el->type==0 || (el->type==2 && m_parc->type!=0) || (el->type==1 && m_parc->type==3))
				{
					el->next=m_parc;
					el->prev=m_parc->prev;
					m_parc->prev=el;
					if(el->prev!=NULL)
					{
						if(el->prev->next!=NULL)
							el->prev->next=el;
					}
					else
					{
						m_start=el;
						m_current=el;
					}
					m_nr++;
					return 1;
				}
				if(el->type==1 || el->type==3)
				{
					if(m_parc->next!=NULL)
					{
						if(m_parc->next->m_time>el->m_time)
						{
							m_parc->next->prev=el;
							el->next=m_parc->next;
							el->prev=m_parc;
							m_parc->next=el;
							m_nr++;
							return 1;
						}
					}
					else
					{
						m_parc->next=el;
						el->next=NULL;
						el->prev=m_parc;
						m_end=el;
						m_nr++;
						return 1;
					}
				}
			}
		}
		m_parc=m_parc->next;
	}
	return 0;
}

element * CSQueue::Next()
{
	if(m_current!=NULL)
		m_parc=m_current=m_current->next;
	return m_parc;
}

element * CSQueue::Prev()
{
	if(m_current!=NULL)
		m_parc=m_current=m_current->prev;
	return m_parc;
}

void CSQueue::Reset()
{
	m_current=m_start;
}

int CSQueue::Delete(element *el)
{
	if(el==m_start)
	{
		m_parc=m_start;
		m_start=m_start->next;
		m_start->prev=NULL;
		m_nr--;
		delete m_parc;
		return 0;
	}
	if(el==m_end)
	{
		m_parc=m_end;
		m_end->prev->next=NULL;
		m_end=m_end->prev;
		m_nr--;
		delete m_parc;
		return 0;
	}
	if(m_start!=NULL)
	{
		m_parc=m_start;
		while(m_parc!=el && m_parc!=NULL)
			m_parc=m_parc->next;
		if(m_parc==NULL) return -1;
		m_parc->prev->next=m_parc->next;
		m_parc->next->prev=m_parc->prev;
		m_nr--;
		delete m_parc;
		return 0;
	}
	return -1;
}

void CSQueue::Get(CString &str)
{
	CString tmp;
	m_parc=m_start;
	while(m_parc!=NULL)
	{
		tmp.Empty();
		if(m_parc->type!=2)
			tmp.Format("%d at %lf\n",m_parc->type,m_parc->m_time);
		else
			tmp.Format("%d at %lf at port %ld\n",m_parc->type,m_parc->m_time,m_parc->m_name);
		str.Insert(str.GetLength(),tmp);
		m_parc=m_parc->next;
	}
}

void CSQueue::RelinkUp()
{
	m_parc=m_start;
	element *m_parc1;
	m_parc1=NULL;
	for(int i=0;i<m_nr;i++)
	{
		m_parc->prev=m_parc1;
		m_parc1=m_parc;
		m_parc=m_parc->next;
	}
	m_end=m_parc1;
	m_end->next=NULL;
}
