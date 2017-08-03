// GDistributionQ.cpp: implementation of the CGDistributionQ class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the implementation of a Distribution queue. The diferencies 
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

#include "stdafx.h"
#include "GDistributionQ.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
IMPLEMENT_SERIAL(CGDistributionQ,CGProcessor,1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGDistributionQ::CGDistributionQ() : CGProcessor()
{
	m_memory=false;
	m_typeq=0;
	m_nc=NULL;
	m_ttrans=NULL;
	m_nosource=false;
	m_nrsources=1;
}

CGDistributionQ::~CGDistributionQ()
{
	CGData *data;
	while(m_queue.empty()==false)
	{
		data=(CGData *)(m_queue.front());
		delete data;
	}
	if(m_ttrans!=NULL)
	{
		delete m_ttrans;
		if(m_nc!=NULL) free(m_nc);
	}
}
CGDistributionQ::CGDistributionQ(long val,bool type) : CGProcessor(NULL,val,NULL,type)
{
	m_first=true;
	m_delay=false;
	m_memory=false;
	m_typeq=0;
	m_nc=NULL;
	m_ttrans=NULL;
	m_nosource=false;
	m_nrsources=1;
}

int CGDistributionQ::receive2(double time,CGData *input)
{
//
// we have receive
//
	CGData *tout,*data;
	CGInput *in=(CGInput *)input;
	long i;
	double *val;
	long dim;
	m_time=time;
	m_tN=time+1e+10;
	val=in->Get(&dim);
	if(in->GetName()>=m_nrsources)
	{
		if(m_queue.empty()==false)
		{
			if(m_lazy.empty()==true)
			{
				for(i=0;i<m_nout;i++)
				{
					tout=(CGData *)(m_outputs.GetAt(i));
					if(in->GetName()+1==tout->GetName()) break;
				}
			}
			else
			{
				m_lazy.add((CObject *)in);
				data=(CGData *)m_lazy.front();
				for(i=0;i<m_nout;i++)
				{
					tout=(CGData *)(m_outputs.GetAt(i));
					if(data->GetName()+1==tout->GetName()) break;
				}
			}
			data=(CGData *)(m_queue.front());
			if(m_nosource==false)
			{
				tout->SetSource(data->GetSource());
				tout->SetSourceName(data->GetSourceName());
			}
			tout->SetTime(data->GetTime());
			tout->SetWTime(m_time);
			tout->Set(data->m_value); 
			delete data;
			tout->RecvMsg(2,m_time,this);
		}
		else
			m_lazy.add((CObject *)in);
	}
	else
	{
		if(m_ttrans!=NULL)
		{
			long index;
			tout=(CGData *)(m_outputs.GetAt(0));
			index=m_ttrans->RetIndex(val[0]);
			m_nc[index]++;
			tout->SetTime(m_time);
			tout->SetWTime(m_time);
			tout->Set(&m_nc[0]); 
			tout->RecvMsg(2,m_time,this);
		}
		data=new CGData(in->m_name);
		data->SetDim(dim);
		data->SetTime(in->GetTime());
		data->SetWTime(m_time);
		data->Set(val);
		if(m_nosource==false)
		{
			data->SetSource(in->GetSource());
			data->SetSourceName(in->GetSourceName());
		}
		m_queue.add((CObject *)data,(long)val[0]);
		if(m_lazy.empty()==false)
		{
			data=(CGInput *)(m_lazy.front());
			for(i=0;i<m_nout;i++)
			{
				tout=(CGData *)(m_outputs.GetAt(i));
				if(data->GetName()+1==tout->GetName()) break;
			}
			data=(CGData *)(m_queue.front());
			if(m_nosource==false)
			{
				tout->SetSource(data->GetSource());
				data->SetSourceName(data->GetSourceName());
			}
			tout->SetTime(data->GetTime());
			tout->SetWTime(m_time);
			tout->Set(data->m_value); 
			delete data;
			tout->RecvMsg(2,m_time,this);
		}
	}
	return 0;
}
int CGDistributionQ::receive1(double time)
{
//
//we have internal
//
	return 0;
}
int CGDistributionQ::receive0(double time)
{
//
//we have start
//
	CGData *data;
	m_tL=m_tN=time;
	m_s=0;
	m_nout=m_outputs.GetSize();
	m_nin=m_inputs.GetSize();
	while(m_queue.empty()==false)
	{
		data=(CGData *)(m_queue.front());
		delete data;
	}
	m_queue.SetType(m_typeq);
	CGData *tout;
	if(m_ttrans!=NULL)
	{
		long dim;
		double *temp;
		tout=(CGData *)(m_outputs.GetAt(0));
		temp=tout->Get(&dim);
		m_nc=(double *)calloc(dim,sizeof(double));
	}
	return 0;
}

int CGDistributionQ::receive3(double time)
{
//
//we need output
//
	return 4;
}
int CGDistributionQ::receivemsg(int type, double time, CObject *in)
{
/*
	type is the receiving message: 0=start;1=int;2=ext;3=out;4=done;
	time is the time of the simulation
	in is the pointer to the input port
	it's return is 4=done or -1=error
*/
	m_time=time;
	m_e=time;
	m_time=time;
	CGData *input=(CGData *)in;
	if(type!=3) m_runs=true;
	switch(type)
	{
	case 0:
		return receive0(time);
	case 1:
		return receive1(time);
	case 2:
		return receive2(time,input);
	case 3:
		return receive3(time);
	default:
		return 0;
	}
}

void CGDistributionQ::Serialize(CArchive &ar)
{
	CGProcessor::Serialize(ar);
	m_lazy.Serialize(ar);
	int temp;
	if(ar.IsStoring())
	{
		temp=m_nosource;
		ar<<temp;
		ar<<m_nrsources;
		ar<<m_typeq;
		ar<<m_ttrans;
		ar<<m_seed;
	}
	else
	{
		ar>>temp;
		m_nosource=(bool)temp;
		ar>>m_nrsources;
		ar>>m_typeq;
		CObject *tmp;
		ar>>tmp;
		m_ttrans=(CGRepartition *)tmp;
		ar>>m_seed;
		m_ttrans->Set(m_seed);

	}
}

void CGDistributionQ::SetTypeQ(long type)
{
	m_typeq=type;
}

void CGDistributionQ::SetRep(CString *var,long seed)
{
	m_ttrans=new CGRepartition;
	m_ttrans->SetGen(var);
	m_ttrans->Set(seed);
	m_seed=seed;
}

void CGDistributionQ::DisableS()
{
	m_nosource=true;
}

void CGDistributionQ::SetSources(long sr)
{
	m_nrsources=sr;
}
