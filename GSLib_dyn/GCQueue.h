// GCQueue.h: interface for the CGCQueue class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the definition of Queue for CGCoordinator.
	
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
#if !defined(AFX_GCQUEUE_H__843FC203_2C48_11DB_B910_D385680B1D0C__INCLUDED_)
#define AFX_GCQUEUE_H__843FC203_2C48_11DB_B910_D385680B1D0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GCElem.h"
#include "stdafx.h"

using namespace std ;
#define precision 1e-12

class CGCElem;
class CGCQueue;

class CGCQueue : public CObject  
{
public:
	bool empty2(double time);
	bool empty1(double time);
	bool empty1();
	bool empty2();
	long GetDim();
	bool empty();
	CGCElem *Get();
	CGCElem *Get(double time);
	void Add(CGCElem *elem);
	CGCQueue();
	virtual ~CGCQueue();
protected:
	CGCElem *m_elem;
	CObArray *queue;
};

#endif // !defined(AFX_GCQUEUE_H__843FC203_2C48_11DB_B910_D385680B1D0C__INCLUDED_)
