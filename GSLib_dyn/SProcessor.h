// SProcessor.h: interface for the CSProcessor class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the definition of simulation processor class, this class is the active
	element in a simulation. This class in used only with CGTransition and CGNetworkS
	classes and theirs derivate.
	
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
#if !defined(AFX_SPROCESSOR_H__06641A61_6470_11DB_B910_845346E6F719__INCLUDED_)
#define AFX_SPROCESSOR_H__06641A61_6470_11DB_B910_845346E6F719__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GProcessor.h"
#include "stdafx.h"

class DllExport CSProcessor : public CGProcessor  
{
	DECLARE_SERIAL_DLL(CSProcessor)
public:
	void Serialize(CArchive &ar);
	CSProcessor();
	CSProcessor(CObject *parent,long val,CGTransition *generator,bool type);
	CSProcessor(CObject *parent,long val,long in,long out,CGTransition *generator,bool type);
	CSProcessor(CObject *parent,long val,long in,long out,bool type);
	virtual int receivemsg(int type, double time, CObject *in);
	virtual ~CSProcessor();
protected:
	virtual int local_receive3(double time);
	virtual int local_receive2(double time,CGData *input);
	virtual int local_receive1(double time);
	virtual int local_receive0(double time);
	virtual int proc_lambda(element *val,long port);


};

#endif // !defined(AFX_SPROCESSOR_H__06641A61_6470_11DB_B910_845346E6F719__INCLUDED_)
