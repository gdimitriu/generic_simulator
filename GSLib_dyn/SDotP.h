// SDotP.h: interface for the CSDotP class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the definition of simulation dot product class.
	
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
#if !defined(AFX_SDOTP_H__D137EF21_6775_11DB_B910_8BB993003769__INCLUDED_)
#define AFX_SDOTP_H__D137EF21_6775_11DB_B910_8BB993003769__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SProcessor.h"

class DllExport CSDotP : public CSProcessor  
{
	DECLARE_SERIAL_DLL(CSDotP)
public:
	void Serialize(CArchive &ar);
	CSDotP();
	CSDotP(CObject *parent,long name,long dim);
	virtual ~CSDotP();
protected:
	virtual int local_receive2(double time,CGData *input);
	virtual int local_receive1(double time);
	virtual int local_receive0(double time);
	bool m_realiz[2];
};

#endif // !defined(AFX_SDOTP_H__D137EF21_6775_11DB_B910_8BB993003769__INCLUDED_)