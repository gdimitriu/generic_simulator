// SNorm.h: interface for the CSNorm class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the definition of simulation norm class.
	
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
#if !defined(AFX_SNORM_H__CB27D901_66BD_11DB_B910_A891B4C15069__INCLUDED_)
#define AFX_SNORM_H__CB27D901_66BD_11DB_B910_A891B4C15069__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SProcessor.h"

class DllExport CSNorm : public CSProcessor  
{
	DECLARE_SERIAL(CSNorm)
public:
	void Serialize(CArchive &ar);
	CSNorm();
	CSNorm(CObject *parent,long val,long dim,int type);
	virtual ~CSNorm();
protected:
	virtual int local_receive2(double time,CGData *input);
	virtual int local_receive1(double time);
	virtual int local_receive0(double time);
	int m_normtype;

};

#endif // !defined(AFX_SNORM_H__CB27D901_66BD_11DB_B910_A891B4C15069__INCLUDED_)
