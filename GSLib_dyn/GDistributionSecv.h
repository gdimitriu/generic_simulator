// GDistributionSecv.h: interface for the CDistributionSecv class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the definition of a distribution class, a class which 
	distributes the data in a queue among other	processors.
	
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

#if !defined(AFX_GDISTRIBUTIONSECV_H__6AA65AC4_E0A1_4E3F_B75B_661FF434AF6E__INCLUDED_)
#define AFX_GDISTRIBUTIONSECV_H__6AA65AC4_E0A1_4E3F_B75B_661FF434AF6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GProcessor.h"
#include "stdafx.h"

class DllExport CGDistributionSecv : public CGProcessor  
{
	DECLARE_SERIAL_DLL(CGDistributionSecv)
public:
	virtual void Serialize(CArchive &ar);
	CGDistributionSecv(long val,bool type);
	CGDistributionSecv();
	virtual ~CGDistributionSecv();
protected:
	long port;
	virtual int receive3(double time);
	virtual int receive2(double time,CGData *input);
	virtual int receive1(double time);
	virtual int receive0(double time);
};

#endif // !defined(AFX_GDISTRIBUTIONSECV_H__6AA65AC4_E0A1_4E3F_B75B_661FF434AF6E__INCLUDED_)
