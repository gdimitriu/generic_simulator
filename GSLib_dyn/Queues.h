// Queues.h: interface for the CQuelles class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the definition of a queue for processor use.
	
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

#if !defined(AFX_QUEUES_H__29414A08_DF7A_420F_B62F_B76247133F94__INCLUDED_)
#define AFX_QUEUES_H__29414A08_DF7A_420F_B62F_B76247133F94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
using namespace std ;

class CQueues  : public CObject
{
	DECLARE_SERIAL(CQueues)
public:
	CObject * viewfront();
	virtual void Serialize(CArchive &ar);
	long GetDim();
	bool empty(long p);
	bool empty(void);
	CObject *front(void);
	int add(CObject *x);
	void SetType(long type);
	CObject * front(long *p);
	CQueues();
	virtual ~CQueues();
	int add(CObject *x,long p);
	CObject *remove_priority(CObject *x,long p);
protected:
	long m_type;//0=no priority,1=priority
private:
	struct nod
	{
		long prioritate;
		struct nod * next;
		CObject *info;
	};
	struct nod * head, *tail, *parc,*p1,*aux;

};

#endif // !defined(AFX_QUELLES_H__29414A08_DF7A_420F_B62F_B76247133F94__INCLUDED_)
