// GDistributionSecv.cpp: implementation of the CDistributionSecv class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the implementation of a distribution class, a class which
	distributes the data in a queue among other processors.
	
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
#include "stdafx.h"
#include "GDistributionSecv.h"
#include "GInput.h"
 
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CGDistributionSecv,CGProcessor,1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGDistributionSecv::CGDistributionSecv() : CGProcessor()
{
	m_delay=false;
	m_memory=false;
	m_first=true;
}

CGDistributionSecv::~CGDistributionSecv()
{

}
CGDistributionSecv::CGDistributionSecv(long val,bool type) : CGProcessor(NULL,val,NULL,type)
{
	m_first=true;
	m_delay=false;
	m_memory=false;
}

int CGDistributionSecv::receive2(double time,CGData *input)
{
//
// we have receive
//
	CGData *tout;
	double *val;
	long dim;
	CGInput *in=(CGInput *)input;
	m_tN=time+1e+10;
	val=in->Get(&dim);
	tout=(CGData *)(m_outputs.GetAt(port));
	port++;
	if(port==m_nout) port=0;
	tout->SetSource(in->GetSource());
	tout->SetSourceName(in->GetSourceName());
	tout->SetTime(in->GetTime());
	tout->SetWTime(m_time);
	tout->Set(val); 
	tout->RecvMsg(2,m_time,this);
	return 0;
}
int CGDistributionSecv::receive1(double time)
{
//
//we have internal
//
	return 0;
}
int CGDistributionSecv::receive0(double time)
{
//
//we have start
//
	m_tL=m_tN=time;
	m_s=0;
	port=0;
	m_nout=m_outputs.GetSize();
	m_nin=m_inputs.GetSize();
	return 0;
}

int CGDistributionSecv::receive3(double time)
{
//
//we need output
//
	return 4;
}

void CGDistributionSecv::Serialize(CArchive &ar)
{
	CGProcessor::Serialize(ar);
	if(ar.IsStoring())
		ar<<port;
	else
		ar>>port;
}
