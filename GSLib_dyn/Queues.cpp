// Queues.cpp: implementation of the CQuelles class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the implementation of a queue for processor use.
	
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
#include "Queues.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
IMPLEMENT_SERIAL(CQueues,CObject,1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQueues::CQueues()
{
	head=tail=NULL;
	m_type=0;
}

CQueues::~CQueues()
{
	parc=head;
	while(parc!=NULL)
	{
		p1=parc;
		parc=parc->next;
		delete p1;
	}
}
int CQueues::add(CObject *x)
{
	if(m_type!=0) return -1;
	if(head==NULL)
	{
		head=new struct nod;
		head->info=x;
		head->next=NULL;
		tail=head;
		return 0;
	}
	aux=new struct nod;
	aux->next=NULL;
	aux->info=x;
	tail->next=aux;
	tail=aux;
	return 0;
}

CObject * CQueues::front(void)
{
	if(head==NULL)
	{
		return NULL;
	}
	parc=head;
	head=head->next;
	if(head==NULL) tail=NULL;
	CObject *tempob;
	tempob=parc->info;
	delete parc;
	return tempob;
}

int CQueues::add(CObject *x,long p)
{
	if(m_type!=1)
	{
		add(x);
		return -1;
	}
	if(head==NULL) 
	{
		//if the queue is empty
		head=new struct nod;
		head->info=x;
		head->prioritate=p;
		head->next=NULL;
		tail=head;
		return 0;
	}
	aux=new struct nod;
	aux->info=x;
	aux->prioritate=p;
	if(head->prioritate>p)
	{
		aux->next=head;
		head=aux;
		return 0;
	}
	if(tail->prioritate==p)
	{
		//if the last element in the queue has the right priority
		aux->next=NULL;
		tail->next=aux;
		tail=aux;
		return 0;
	}
	//find the right priority
	parc=head;
	while((parc->next!=NULL) && (parc->prioritate<p)) parc=parc->next;
	if(parc->next==NULL)
	{
		//I didn't find one
		aux->next=NULL; 
		tail->next=aux;
		tail=aux;
	}
	else 
	{	//if the priority isn't find but the queue is not over
		if(parc->next->prioritate>p)
		{
			aux->next=parc->next;
			parc->next=aux;
		}
		else
		{
			//find the end of the queue with desired priority
			p1=parc->next;
			while(p1->next->prioritate==p) p1=p1->next;
			aux->next=p1->next;
			p1->next=aux;
		}
	}
	return 0;
}

CObject *CQueues::remove_priority(CObject *x,long p)
{
	if(m_type!=1) return NULL;
	if(head==NULL)
	{
		return NULL;
	}
	else if((head==tail) &&(head->prioritate==p) && (head->info==x))
	{
		head=tail=NULL;
		CObject *tempob=head->info;
		delete head;
		return tempob;
	}
	else if(head==tail) return NULL;
	else
	{
		if(tail->prioritate<p) return NULL;
		else
		{
			parc=head;
			while((parc->next!=NULL)&& (parc->prioritate!=p)) parc=parc->next;
			if(parc->next==NULL) return NULL;
			else
			{
				while((parc->next->info!=x) && (parc->next->prioritate==p)) parc=parc->next;
				if(parc->next->prioritate!=p) return NULL;
				else
				{
					aux=parc->next;
					if(parc->next!=tail) parc->next=aux->next;
					else
					{
						parc=parc->next;
						tail=parc;
					}
					delete aux;
					CObject *tempob=aux->info;
					return tempob;
				}
			}
		}
	}
}

CObject * CQueues::front(long *p)
{
	if(m_type!=1) return NULL;
	if(head==NULL)
	{
		*p=-1;
		return NULL;
	}
	parc=head;
	head=head->next;
	if(head==NULL) tail=NULL;
	CObject *tempob;
	*p=parc->prioritate;
	tempob=parc->info;
	delete parc;
	return tempob;
}

void CQueues::SetType(long type)
{
	m_type=type;
}

bool CQueues::empty()
{
 if(head==NULL) return true;
 else return false;
}

bool CQueues::empty(long p)
{
	if(head==NULL)
	{
		return true;
	}
	else
	{
		if(m_type!=1) return false;
		if((head==tail) &&(head->prioritate==p))
		{
			return false;
		}
		else if(head==tail) return true;
		else
		{
			if(tail->prioritate<p) return true;
			else
			{
				parc=head;
				while((parc->next!=NULL)&& (parc->prioritate!=p)) parc=parc->next;
				if(parc->next==NULL) return true;
				else return false;
			}
		}
	}
}

long CQueues::GetDim()
{
	long dim=0;
	parc=head;
	while(parc!=NULL)
	{
		p1=parc;
		parc=parc->next;
		dim++;
	}
	return dim;
}

void CQueues::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	if(ar.IsStoring())
	{
		ar<<m_type;
	}
	else
	{
		ar>>m_type;
	}
}

CObject * CQueues::viewfront()
{
	if(head==NULL)
	{
		return NULL;
	}
	return head->info;
}
