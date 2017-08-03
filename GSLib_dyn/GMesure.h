// GMesure.h: interface for the CGMesure class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 version 1.0

	This file is part of Generic Simulator.
	This file contains the definition of Mesure class, this class is a pasive
	element in a simulation.
	
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
#if !defined(AFX_GMESURE_H__B59766E1_2898_11DB_B910_CB869ABB5B04__INCLUDED_)
#define AFX_GMESURE_H__B59766E1_2898_11DB_B910_CB869ABB5B04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GProcessor.h"
#include "stdafx.h"

class DllExport CGMesure : public CGProcessor  
{
public:
	DECLARE_SERIAL_DLL(CGMesure)
	CGMesure(CObject *parent,long val,bool type);
	CGMesure();
	virtual ~CGMesure();
	virtual void Serialize(CArchive& ar);
	virtual int receivemsg(int type,double time,CObject *in);
protected:
	virtual int receive3(double time);
	virtual int receive2(double time,CGData *input);
	virtual int receive1(double time);
	virtual int receive0(double time);
	virtual int proc_lambda(element *val,long port);
};

#endif // !defined(AFX_GMESURE_H__B59766E1_2898_11DB_B910_CB869ABB5B04__INCLUDED_)
