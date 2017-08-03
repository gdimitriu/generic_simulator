// SQueue.h: interface for the CSQueue class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the definition of simulation Queue for CSCoordinator.
	
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
#if !defined(AFX_SQUEUE_H__48AD6B41_724B_11DB_B910_865F0F4C675D__INCLUDED_)
#define AFX_SQUEUE_H__48AD6B41_724B_11DB_B910_865F0F4C675D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "stdafx.h"
#include "element.h"
using namespace std ;
#define precision 1e-12

class DllExport CSQueue : public CObject  
{
	DECLARE_SERIAL_DLL(CSQueue)
public:
	void RelinkUp();
	element * Get();
	void Get(CString &str);
	element * Prev();
	element * Next();
	void Reset();
	int Delete(element *el);
	int Add(element *el);
	void Serialize(CArchive &ar);
	CSQueue();
	virtual ~CSQueue();
protected:
	long m_nr;
	element *m_start;
	element *m_current;
	element *m_end;
	element *m_parc;
};

#endif // !defined(AFX_SQUEUE_H__48AD6B41_724B_11DB_B910_865F0F4C675D__INCLUDED_)
