// GCQueue.cpp: implementation of the CGCQueue class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the implementation of Queue for CGCoordinator.
	
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
#include "GCQueue.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGCQueue::CGCQueue()
{
	queue=new CObArray[3];
}

CGCQueue::~CGCQueue()
{
	if(queue!=NULL) delete[] queue;
}

void CGCQueue::Add(CGCElem *elem)
{
	long i;
	CObArray *temp;
	if(elem->m_type==1) temp=&queue[0];
	if(elem->m_type==2) temp=&queue[1];
	if(elem->m_type==3) temp=&queue[2];
	for(i=0;i<temp->GetSize();i++)
	{
		if(((CGCElem *)temp->GetAt(i))->m_time>elem->m_time)
		{
			temp->InsertAt(i,elem);
			return ;
		}
	}
	temp->InsertAt(i,elem);
//	cout<<"Add at "<<elem->m_time<<" of type "<<elem->m_type<<endl;cout.flush();
}

CGCElem* CGCQueue::Get()
{
	if(queue[0].GetSize()==0 && queue[1].GetSize()==0 && queue[2].GetSize()==0)
		return NULL;
	
	//last message 3 from simulation
	if(queue[0].GetSize()==0 && queue[1].GetSize()==0 && queue[2].GetSize()!=0)
	{
		m_elem=(CGCElem *)queue[2].GetAt(0);
		queue[2].RemoveAt(0);
		return m_elem;
	}
	//a message 3 in time of simulation
	if(queue[0].GetSize()!=0 && queue[1].GetSize()!=0 && queue[2].GetSize()!=0)
		if(((CGCElem *)queue[2].GetAt(0))->m_time<((CGCElem *)queue[0].GetAt(0))->m_time
			&& ((CGCElem *)queue[2].GetAt(0))->m_time<((CGCElem *)queue[1].GetAt(0))->m_time)
		{
			m_elem=(CGCElem *)queue[2].GetAt(0);
			queue[2].RemoveAt(0);
			return m_elem;
		}

	//only internal
	if(queue[1].GetSize()==0 && queue[0].GetSize()!=0)
	{
		m_elem=(CGCElem *)queue[0].GetAt(0);
		queue[0].RemoveAt(0);
		return m_elem;
	}

	//internal and external
	if(queue[1].GetSize()!=0 && queue[0].GetSize()!=0)
	{
		if(((CGCElem *)queue[1].GetAt(0))->m_time<=((CGCElem *)queue[0].GetAt(0))->m_time)
		{
			m_elem=(CGCElem *)queue[1].GetAt(0);
			queue[1].RemoveAt(0);
			return m_elem;
		}
		else
		{
			m_elem=(CGCElem *)queue[0].GetAt(0);
			queue[0].RemoveAt(0);
			return m_elem;
		}
	}
	else if(queue[1].GetSize()!=0)
	{
		m_elem=(CGCElem *)queue[1].GetAt(0);
		queue[1].RemoveAt(0);
		return m_elem;
	}
	return NULL;
}

bool CGCQueue::empty()
{
	if(queue[0].GetSize()==0 && queue[1].GetSize()==0 && queue[2].GetSize()==0) return true;
	else return false;
}

long CGCQueue::GetDim()
{
	return queue[0].GetSize()+queue[1].GetSize()+queue[2].GetSize();
}

bool CGCQueue::empty2()
{
	if(queue[1].GetSize()==0) return true;
	else return false;
}

bool CGCQueue::empty1()
{
	if(queue[0].GetSize()==0) return true;
	else return false;
}

CGCElem* CGCQueue::Get(double time)
{
	long i;
//	cout<<queue[0].GetSize()<<" "<<queue[1].GetSize()<<" "<<queue[2].GetSize()<<endl;cout.flush();
	if(queue[0].GetSize()==0 && queue[1].GetSize()==0 && queue[2].GetSize()==0)
		return NULL;
	
	//last message 3 from simulation
	if(queue[0].GetSize()==0 && queue[1].GetSize()==0 && queue[2].GetSize()!=0)
	{
		for(i=0;i<queue[2].GetSize();i++)
		{
			m_elem=(CGCElem *)queue[2].GetAt(i);
			if(m_elem->m_time<time || fabs(m_elem->m_time-time)<precision)
			{
				queue[2].RemoveAt(i);
				return m_elem;
			}
		}
		return NULL;
	}
	//a message 3 in time of simulation
	if(queue[0].GetSize()!=0 && queue[1].GetSize()!=0 && queue[2].GetSize()!=0)
		if(((CGCElem *)queue[2].GetAt(0))->m_time<((CGCElem *)queue[0].GetAt(0))->m_time
			&& ((CGCElem *)queue[2].GetAt(0))->m_time<((CGCElem *)queue[1].GetAt(0))->m_time)
		{
			for(i=0;i<queue[2].GetSize();i++)
			{
				m_elem=(CGCElem *)queue[2].GetAt(i);
				if(m_elem->m_time<time || fabs(m_elem->m_time-time)<precision)
				{
					queue[2].RemoveAt(i);
					return m_elem;
				}
			}
			return NULL;
		}

	//only internal
	if(queue[1].GetSize()==0 && queue[0].GetSize()!=0)
	{
		for(i=0;i<queue[0].GetSize();i++)
		{
			m_elem=(CGCElem *)queue[0].GetAt(i);
			if(m_elem->m_time<time ||fabs(m_elem->m_time-time)<precision)
			{
				queue[0].RemoveAt(i);
//				cout<<"return "<<m_elem->m_type<<" at "<<m_elem->m_time<<endl;cout.flush();
				return m_elem;
			}
		}
		return NULL;
	}

	//internal and external
	if(queue[1].GetSize()!=0 && queue[0].GetSize()!=0)
	{
		if(((CGCElem *)queue[1].GetAt(0))->m_time<=((CGCElem *)queue[0].GetAt(0))->m_time)
		{
			for(i=0;i<queue[1].GetSize();i++)
			{
				m_elem=(CGCElem *)queue[1].GetAt(i);
				if(m_elem->m_time<time ||fabs(m_elem->m_time-time)<precision)
				{
					queue[1].RemoveAt(i);
//					cout<<"return "<<m_elem->m_type<<" at "<<m_elem->m_time<<endl;cout.flush();
					return m_elem;
				}
			}
			return NULL;
		}
		else
		{
			for(i=0;i<queue[0].GetSize();i++)
			{
				m_elem=(CGCElem *)queue[0].GetAt(i);
				if(m_elem->m_time<time ||fabs(m_elem->m_time-time)<precision)
				{
					queue[0].RemoveAt(i);
//					cout<<"return "<<m_elem->m_type<<" at "<<m_elem->m_time<<endl;cout.flush();
					return m_elem;
				}
			}
			return NULL;
		}
	}
	else if(queue[1].GetSize()!=0)
	{
		for(i=0;i<queue[1].GetSize();i++)
		{
			m_elem=(CGCElem *)queue[1].GetAt(i);
			if(m_elem->m_time<time ||fabs(m_elem->m_time-time)<precision)
			{
				queue[1].RemoveAt(i);
//				cout<<"return "<<m_elem->m_type<<" at "<<m_elem->m_time<<endl;cout.flush();
				return m_elem;
			}
		}
		return NULL;
	}
	return NULL;
}

bool CGCQueue::empty1(double time)
{
	long i;
	for(i=0;i<queue[0].GetSize();i++)
	{
		m_elem=(CGCElem *)queue[0].GetAt(i);
		if(m_elem->m_time<time ||fabs(m_elem->m_time-time)<precision)
			return false;
	}
	return true;
}	

bool CGCQueue::empty2(double time)
{
	long i;
	for(i=0;i<queue[1].GetSize();i++)
	{
		m_elem=(CGCElem *)queue[1].GetAt(i);
		if(m_elem->m_time<time ||fabs(m_elem->m_time-time)<precision)
			return false;
	}
	return true;
}
