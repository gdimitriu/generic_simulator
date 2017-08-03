// GDistributionBus.h: interface for the CGDistributionBus class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the definition of a Distribution bus. In fact this is a 
	MUX/DEMUX system.
	
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

#if !defined(AFX_GDISTRIBUTIONBUS_H__20AE473E_63F3_474A_8F33_A165E73A654B__INCLUDED_)
#define AFX_GDISTRIBUTIONBUS_H__20AE473E_63F3_474A_8F33_A165E73A654B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GProcessor.h"
#include "GNetworkS.h"
#include "GWire.h"
#include "stdafx.h"

class DllExport CGDistributionBus : public CGProcessor  
{
	DECLARE_SERIAL_DLL(CGDistributionBus)
public:
	void SetBypass(bool type);
	void SetSN(bool type);
	virtual void Serialize(CArchive &ar);
	void SetType(bool type);
	CGDistributionBus(long val,bool type);
	CGDistributionBus();
	virtual ~CGDistributionBus();
	virtual double sigma(void);
protected:
	bool m_bypass;
	bool m_type;	//true for 1 to N; false for N to 1
	bool m_SN;		//true for source name for decision
	virtual int proc_lambda(element *val,long port);
	virtual int receive3(double time);
	virtual int receive2(double time,CGData *input);
	virtual int receive1(double time);
	virtual int receive0(double time);
	virtual int receivemsg(int type, double time, CObject *in);
};

#endif // !defined(AFX_GDISTRIBUTIONBUS_H__20AE473E_63F3_474A_8F33_A165E73A654B__INCLUDED_)
