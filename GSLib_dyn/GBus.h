// GBus.h: interface for the CGBus class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the definition of a bus class, a class which
	divided the inputs buses into other buses of diferent dimensions.
	
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
#if !defined(AFX_GBUS_H__F2CC06A7_DB29_4478_850E_BB22F2735174__INCLUDED_)
#define AFX_GBUS_H__F2CC06A7_DB29_4478_850E_BB22F2735174__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GProcessor.h"
#include "stdafx.h"
#define precision 1e-12

using namespace std ;

class DllExport CGBus : public CGProcessor  
{
	DECLARE_SERIAL_DLL(CGBus)
public:
	virtual void Serialize(CArchive &ar);
	CGBus(long val,bool type);
	void SetSync(bool type);
	CGBus();
	virtual ~CGBus();
protected:
	bool m_SyncType;//true=the input are synchronized
	long m_exec;
	virtual int proc_lambda(element *val,long port);
	virtual int receivemsg(int type, double time, CObject *in);
	virtual int receive3(double time);
	virtual int receive2(double time,CGData *input);
	virtual int receive1(double time);
	virtual int receive0(double time);
	bool *execute;
};

#endif // !defined(AFX_GBUS_H__F2CC06A7_DB29_4478_850E_BB22F2735174__INCLUDED_)
