// STLineVD.h: interface for the CSTLineVD class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the definition of simulation transition line with variable 
	delay and noise class.
	
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
#if !defined(AFX_STLINEVD_H__08E9A421_6D81_11DB_B910_AE828DD98E5B__INCLUDED_)
#define AFX_STLINEVD_H__08E9A421_6D81_11DB_B910_AE828DD98E5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "STLineSD.h"

class DllExport CSTLineVD : public CSTLineSD  
{
	DECLARE_SERIAL(CSTLineVD)
public:
	virtual void Serialize(CArchive &ar);
	CSTLineVD();
	CSTLineVD(CObject *net,long name,long dim,CString *delay);
	CSTLineVD(CObject *net,long name,long dim,CString *delay,CString *noise);
	virtual ~CSTLineVD();
protected:
	virtual int receive1(double time);
	virtual int ExternN(CGData *input,double time);
	virtual int ExternS(CGData *input,double time);
	int Put1(double time);
	CGRepartition m_delay;
	CGRepartition m_noise;
	int m_typenoise;
};

#endif // !defined(AFX_STLINEVD_H__08E9A421_6D81_11DB_B910_AE828DD98E5B__INCLUDED_)
