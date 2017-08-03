// GBus.cpp: implementation of the CGBus class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the implementation of a bus class, a class which
	divided the inputs buses into other buses of diferent dimensions.
	
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
#include "GBus.h"
#include "GInput.h"
#include "GOutput.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
IMPLEMENT_SERIAL(CGBus,CGProcessor,1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGBus::CGBus() : CGProcessor()
{
	m_exec=0;
	m_SyncType=true;
	m_delay=false;
	execute=NULL;
}

CGBus::CGBus(long val,bool type) : CGProcessor(NULL,val,NULL,type)
{
	m_exec=0;
	m_SyncType=true;
	m_delay=false;
	execute=NULL;
}
CGBus::~CGBus()
{
	if(execute!=NULL)
		free(execute);
}
int CGBus::receivemsg(int type, double time, CObject *in)
{
/*
	type is the receiving message: 0=start;1=int;2=ext;3=out;4=done;
	time is the time of the simulation
	in is the pointer to the input port
	it's return is 4=done or -1=error
*/
	m_time=time;
	m_e=time;
	CGData *input=(CGData *)in;
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

int CGBus::receive2(double time,CGData *input)
{
	long i;
	long nr;
	double *valt;
	long id;
	CGInput *in=(CGInput *)input;
	m_tN=time+1e+10;
	if(m_exec==0) ((CGNetworkS *)m_parent)->ResetProc(this);
	valt=in->Get(&nr);
	if(nr!=m_nout) return -1;
	id=in->m_name-m_nout;
	if(m_SyncType==false)
	{
		m_exec=0;
		for(i=0;i<m_nout;i++)
			((element *)m_value[i])->data[id]=valt[i];
		receive1(time);
	}
	else
	{
		if(execute[id]==true) return -2;
		execute[id]=true;
		m_exec++;
		for(i=0;i<m_nout;i++)
			((element *)m_value[i])->data[id]=valt[i];
		if(m_exec==m_nin)
		{
			((CGNetworkS *)m_parent)->SetProc(this);
			for(i=0;i<m_nout;i++)
				proc_lambda((element *)m_value[i],((CGOutput *)m_outputs.GetAt(i))->m_name);
			for(i=0;i<m_nin;i++)
				execute[i]=false;
			m_exec=0;
		}
	}
	return 0;
}
int CGBus::receive1(double time)
{
//
//we have send
//
	if(((CGNetworkS *)m_parent)->GetCoordinator()!=NULL)
		if(((CGNetworkS *)m_parent)->GetWork(this)==true)
			return -1;
	((CGNetworkS *)m_parent)->SetProc(this);
	long i;
	for(i=0;i<m_nout;i++)
		proc_lambda((element *)m_value[i],((CGOutput *)m_outputs.GetAt(i))->m_name);
	m_exec=0;
	for(i=0;i<m_nin;i++)
		execute[i]=false;
	return 0;
}
int CGBus::receive0(double time)
{
//
//we have start
//
	long i;
	m_tL=m_tN=time;
	m_s=0;
	m_nout=m_outputs.GetSize();
	m_nin=m_inputs.GetSize();
	//test existence conditions
	for(i=0;i<m_nin;i++)
		if(m_nout!=((CGData *)m_inputs.GetAt(i))->GetDim())
		{
			AfxMessageBox("Wrong dimensions in bus",MB_ICONSTOP|MB_OK);
			exit(-1);
		}
	element *el;
	if(m_value.GetUpperBound()!=-1)
	{
		for(i=0;i<m_value.GetSize();i++)
		{
			el=(element *)m_value[i];
			m_value.RemoveAt(i);
			delete el;
		}
		m_value.FreeExtra();
	}
	m_value.RemoveAll();
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
	execute=(bool *)calloc(m_nin,sizeof(bool));
	for(i=0;i<m_nin;i++)
		execute[i]=false;
	//reset the data
	for(i=0;i<m_nin;i++)
		((CGData *)m_inputs[i])->ResetG();
	for(i=0;i<m_nout;i++)
		((CGData *)m_outputs[i])->ResetG();
	return 0;
}

int CGBus::receive3(double time)
{
//
//we need output
//
	for(long i=0;i<m_nout;i++)
		proc_lambda((element *)m_value[i],((CGOutput *)m_outputs.GetAt(i))->m_name);
	return 4;
}

int CGBus::proc_lambda(element *val,long port)
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
		tout->Reset();
		if(m_mtype!=0)
			tout->RecvMsg(3,m_time,this);
	}
	else
	{
		tout->SetSource((CObject *)this);
		tout->SetTime(m_time);
		tout->SetWTime(m_time);
		tout->Set(val->data);
		if(m_mtype!=0)
			tout->RecvMsg(2,m_time,this);
	}
	return 0;
}

void CGBus::SetSync(bool type)
{
	m_SyncType=type;
}

void CGBus::Serialize(CArchive &ar)
{
	long i;
	CGProcessor::Serialize(ar);
	int temp;
	if(ar.IsStoring())
	{
		ar<<m_exec;
		ar<<m_SyncType;
		for(i=0;i<m_nout;i++)
		{
			temp=execute[i];
			ar<<temp;
		}
	}
	else 
	{
		ar>>m_exec;
		ar>>temp;
		m_SyncType=(bool)temp;
		if(execute!=NULL) free(execute);
		execute=(bool *)calloc(m_nout,sizeof(bool));
		for(i=0;i<m_nout;i++)
		{
			ar>>temp;
			execute[i]=(bool)temp;
		}
	}
}
