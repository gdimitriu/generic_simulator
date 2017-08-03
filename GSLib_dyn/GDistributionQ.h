// GDistributionQ.h: interface for the CGDistributionQ class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the definition of a Distribution queue. The diferencies 
	between this class and the CDistributionSecv is that this class hold the queue.
	
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

#if !defined(AFX_GDISTRIBUTIONQ_H__200C868E_B3A2_47D0_A045_689BC0463551__INCLUDED_)
#define AFX_GDISTRIBUTIONQ_H__200C868E_B3A2_47D0_A045_689BC0463551__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GProcessor.h"
#include "GInput.h"
#include "GRepartition.h"
#include "Queues.h"
#include "stdafx.h"

class DllExport CGDistributionQ : public CGProcessor  
{
	DECLARE_SERIAL_DLL(CGDistributionQ)
public:
	void SetSources(long sr);
	void DisableS();
	void SetRep(CString *var,long seed);
	void SetTypeQ(long type);
	virtual void Serialize(CArchive &ar);
	CGDistributionQ(long val,bool type);
	CGDistributionQ();
	virtual ~CGDistributionQ();
protected:
	bool m_nosource;
	double *m_nc;
	virtual int receive3(double time);
	virtual int receive2(double time,CGData *input);
	virtual int receive1(double time);
	virtual int receive0(double time);
	virtual int receivemsg(int type, double time, CObject *in);
	CQueues m_lazy;
	long m_typeq;
	CGRepartition *m_ttrans;
	long m_seed;
	long m_nrsources;
};

#endif // !defined(AFX_GDISTRIBUTIONQ_H__200C868E_B3A2_47D0_A045_689BC0463551__INCLUDED_)
