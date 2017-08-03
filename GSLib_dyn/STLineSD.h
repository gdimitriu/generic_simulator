// STLineSD.h: interface for the CSTLineSD class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the definition of simulation transition line class.
	
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
#if !defined(AFX_STLINESD_H__9B373E01_6CB9_11DB_B910_B38E6A80DE28__INCLUDED_)
#define AFX_STLINESD_H__9B373E01_6CB9_11DB_B910_B38E6A80DE28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GProcessor.h"

class DllExport CSTLineSD : public CGProcessor  
{
	DECLARE_SERIAL(CSTLineSD)
public:
	CSTLineSD();
	CSTLineSD(CObject *net,long val,CGTransition *trans,bool type);
	virtual void Serialize(CArchive &ar);
	CSTLineSD(CObject *net,long val,long dim,double time,bool type);
	virtual ~CSTLineSD();
protected:
	int proc_lambda(element *val);
	double m_delaytime;
	virtual int receive3(double time);
	virtual int receive2(double time,CGData *input);
	virtual int receive0(double time);
	virtual int receive1(double time);
	virtual int ExternN(CGData *input,double time);
	virtual int ExternS(CGData *input,double time);
};

#endif // !defined(AFX_STLINESD_H__9B373E01_6CB9_11DB_B910_B38E6A80DE28__INCLUDED_)
