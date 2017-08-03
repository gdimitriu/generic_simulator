// SMult.h: interface for the CSMult class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the definition of simulation multiplication class.
	
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
#if !defined(AFX_SMULT_H__66F4BEC1_68D5_11DB_B910_92FBC260DE79__INCLUDED_)
#define AFX_SMULT_H__66F4BEC1_68D5_11DB_B910_92FBC260DE79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GSum.h"

class DllExport CSMult : public CGSum  
{
	DECLARE_SERIAL(CSMult)
public:
	CSMult();
	CSMult(CObject *parent,long name,long in,long dim,bool type);
	virtual ~CSMult();
	virtual void Serialize(CArchive &ar);
protected:
	virtual int receive2(double time,CGData *input);
	virtual int receive1(double time);
};

#endif // !defined(AFX_SMULT_H__66F4BEC1_68D5_11DB_B910_92FBC260DE79__INCLUDED_)
