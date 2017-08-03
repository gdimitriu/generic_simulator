// GSum.h: interface for the CGSum class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 version 1.0

	This file is part of Generic Simulator.
	This file contains the definition of GSum class, this class is a pasive
	element in a simulation. It is a wire sumator.
	
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
#if !defined(AFX_GSUM_H__B59766E2_2898_11DB_B910_CB869ABB5B04__INCLUDED_)
#define AFX_GSUM_H__B59766E2_2898_11DB_B910_CB869ABB5B04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include "GMesure.h"

class DllExport CGSum : public CGMesure  
{
	DECLARE_SERIAL_DLL(CGSum);
public:
	void RInput(bool type);
	virtual void Serialize(CArchive& ar);
	CGSum();
	CGSum(CObject *parent,long val,bool type);
	CGSum(CObject *parent,long name,long in,long dim,bool reset);
	virtual ~CGSum();
protected:
	bool m_RInput;
	long m_vals;
	virtual void other_init();
	virtual int receive3(double time);
	virtual int receive2(double time,CGData *input);
	virtual int receive1(double time);
	bool *m_exec;
};

#endif // !defined(AFX_GSUM_H__B59766E2_2898_11DB_B910_CB869ABB5B04__INCLUDED_)
