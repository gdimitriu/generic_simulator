// GDistributionBus.cpp: implementation of the CGDistributionBus class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the implementation of a Distribution bus. In fact this is a 
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

#include "stdafx.h"
#include "GDistributionBus.h"
#include "GInput.h"
#include "GOutput.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
IMPLEMENT_SERIAL(CGDistributionBus,CGProcessor,1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGDistributionBus::CGDistributionBus() : CGProcessor()
{
	m_SN=false;
	m_type=true;
	m_first=true;
	m_delay=false;
	m_bypass=false;
}

CGDistributionBus::~CGDistributionBus()
{

}
CGDistributionBus::CGDistributionBus(long val,bool type) : CGProcessor(NULL,val,NULL,type)
{
	m_type=true;
	m_first=true;
	m_delay=false;
	m_SN=false;
	m_bypass=false;
}

int CGDistributionBus::receive2(double time,CGData *input)
{
//
// we have receive
//
	long i;
	CGInput *in=(CGInput *)input;
	double *val;
	m_tN=time+1e+10;
	val=in->Get(&(((element *)m_value[0])->dim));
	if(fabs(val[0])<precision) return 0;
	((element *)m_value[0])->source=in->GetSource();
	if(m_bypass==true)
		((element *)m_value[0])->sourcename=in->GetSourceName();
	for(i=0;i<((element *)m_value[0])->dim;i++)
		((element *)m_value[0])->data[i]=val[i];
	((element *)m_value[0])->m_time=in->GetTime();
	if(m_type==true)//1 to N
	{
		CGWire *pw;
		for(i=0;i<m_nout;i++)
		{
			if(m_SN==false)
			{
				pw=((CGWire *)((CGData *)m_outputs.GetAt(i))->GetParentW());
				if(pw->GetSource()==in->GetSource()) break;
			}
			else
				if(((CGData *)m_outputs.GetAt(i))->GetName()==in->GetSourceName()) break;
		}
		if(i!=m_nout) proc_lambda((element *)m_value[0],((CGOutput *)m_outputs.GetAt(i))->m_name);
	}
	else //N to 1
	{
		if(m_bypass==false)
			((element *)m_value[0])->sourcename=in->GetName();
		proc_lambda((element *)m_value[0],((CGOutput *)m_outputs.GetAt(0))->m_name);
	}
	return 0;
}
int CGDistributionBus::receive1(double time)
{
//
//we have send
//
	return 0;
}
int CGDistributionBus::receive0(double time)
{
//
//we have start
//
	long i;
	m_tL=m_tN=time;
	m_s=0;
	m_nout=m_outputs.GetSize();
	m_nin=m_inputs.GetSize();
/*	//test existence conditions not avaible yet
	for(i=0;i<m_nin;i++)
		if(m_nout!=((CGData *)m_inputs.GetAt(i))->GetDim())
		{
			CString a;
			a.Format("Wrong dimensions in bus %d",m_name);
			AfxMessageBox(a,MB_ICONSTOP|MB_OK);
			exit(-1);
		}*/
	element *el;
	if(m_value.GetUpperBound()!=-1)
	{
		for(i=0;i<m_value.GetSize();i++)
		{
			el=(element *)m_value[i];
			m_value.RemoveAt(i);
			delete el;
		}
	}
	m_value.RemoveAll();
	m_value.FreeExtra();
	m_value.SetSize(m_nout);
	for(i=0;i<m_nout;i++)
	{
		el=new element();
		el->dim=(((CGOutput *)m_outputs.GetAt(i))->GetDim());
		el->data=(double *)calloc(el->dim,sizeof(double));
		try
		{
			m_value.SetAt(i,(CObject *)el);	
		}
		catch (CMemoryException *err)
		{
			AfxMessageBox("Out of Memory m_value_n",MB_ICONSTOP|MB_OK);
			err->Delete();
		}
		proc_lambda(NULL,((CGOutput *)m_outputs.GetAt(i))->m_name);
	}
	return 0;
}

int CGDistributionBus::receive3(double time)
{
//
//we need output
//
	for(long i=0;i<m_nout;i++)
		proc_lambda((element *)m_value[i],((CGOutput *)m_outputs.GetAt(i))->m_name);
	return 4;
}

int CGDistributionBus::proc_lambda(element *val,long port)
{
//
//output function
//
	CGData *tout;
	long N=m_outputs.GetSize();
	for(int i=0;i<N;i++)
	{
		tout=(CGData *)(m_outputs.GetAt(i));
		if(tout->m_name==port)	break;
	}
	if(val==NULL)
	{
		tout->SetTime(m_time);
		tout->SetWTime(m_time);
		if(m_SN==true && m_type==false) tout->SetSourceName(tout->m_name);
		tout->Reset();
		if(m_mtype!=0)
			tout->RecvMsg(3,m_time,this);
	}
	else
	{
		tout->SetSource(val->source);
		if(m_SN==true && m_type==false) tout->SetSourceName(val->sourcename);
		tout->SetTime(val->m_time);
		tout->SetWTime(m_time);
		tout->Set(val->data);
		if(m_mtype!=0)
			tout->RecvMsg(2,m_time,this);
	}
	return 0;
}

void CGDistributionBus::SetType(bool type)
{
	m_type=type;
}

double CGDistributionBus::sigma(void)
{
	return m_tN;
}

int CGDistributionBus::receivemsg(int type, double time, CObject *in)
{
/*
	type is the receiving message: 0=start;1=int;2=ext;3=out;4=done;
	time is the time of the simulation
	in is the pointer to the input port
	it's return is 4=done or -1=error
*/
	m_time=time;
	m_e=time;
	CGInput *input=(CGInput *)in;
	m_mtype=type;
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

void CGDistributionBus::Serialize(CArchive &ar)
{
	CGProcessor::Serialize(ar);
	if(ar.IsStoring())
	{
		ar<<m_type;
		ar<<m_SN;
	}
	else
	{
		int temp;
		ar>>temp;
		m_type=(bool)temp;
		ar>>temp;
		m_SN=(bool)temp;
	}
}

void CGDistributionBus::SetSN(bool type)
{
	m_SN=type;
}

void CGDistributionBus::SetBypass(bool type)
{
	m_bypass=type;
}
