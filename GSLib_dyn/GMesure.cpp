// GMesure.cpp: implementation of the CGMesure class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 version 1.0

	This file is part of Generic Simulator.
	This file contains the implementation of Mesure class, this class is a pasive
	element in a simulation.
	
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
#include "GMesure.h"
#include "GInput.h"
#include "GOutput.h"

IMPLEMENT_SERIAL(CGMesure,CGProcessor,1);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGMesure::CGMesure() : CGProcessor()
{
	m_memory=true;
	m_meminput=true;
	m_delay=true;
	m_compute=NULL;
}

CGMesure::CGMesure(CObject *parent,long val,bool type) : CGProcessor(parent,val,NULL,type)
{
	m_memory=true;
	m_meminput=true;
	m_delay=true;
	m_compute=NULL;
}

CGMesure::~CGMesure()
{

}

void CGMesure::Serialize(CArchive &ar)
{
	CGProcessor::Serialize(ar);
}
int CGMesure::proc_lambda(element *val,long port)
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
		tout->SetSource(this);
		tout->SetTime(GetTime());
		tout->SetWTime(GetTime());
		tout->Reset();
		if(m_mtype!=0)
			tout->RecvMsg(3,GetTime(),this);
	}
	else
	{
		tout->SetSource(this);
		tout->SetTime(GetTime());
		tout->SetWTime(GetTime());
		tout->Set(val->data);
		if(m_mtype!=0 && m_mtype!=3)
			tout->RecvMsg(2,GetTime(),this);
		else if(m_mtype==3)
			tout->RecvMsg(3,GetTime(),this);
	}
	return 0;
}

int CGMesure::receivemsg(int type, double time, CObject *in)
{
/*
	type is the receiving message: 0=start;1=int;2=ext;3=out;4=done;
	time is the time of the simulation
	in is the pointer to the input port
	it's return is 4=done or -1=error
*/
	m_time=time;
	m_e=time;
	m_mtype=type;
	CGInput *input=(CGInput *)in;
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

int CGMesure::receive0(double time)
{
//
//we have start
//
if(m_reinit==true)
{
	m_reinit=false;
	long i;
	m_tL=m_tN=time;
	m_s=0;
	m_internal=false;
	m_extern=false;
	m_nout=m_outputs.GetSize();
	element *el;
	if(m_memory==true)
	{
		if(m_value.GetUpperBound()!=-1)
		{
			for(i=0;i<m_value.GetSize();i++)
			{
				el=(element *)m_value[0];
				m_value.RemoveAt(0);
				delete el;
			}
		}
		m_value.RemoveAll();
		m_value.FreeExtra();
		if(m_meminput==true)
		{
			if(m_oinputs.GetUpperBound()!=-1)
			{
				for(i=0;i<m_oinputs.GetSize();i++)
				{
					el=(element *)m_oinputs[0];
					m_oinputs.RemoveAt(0);
					delete el;
				}
			}
			m_oinputs.RemoveAll();
			m_oinputs.FreeExtra();
			m_oinputs.SetSize(m_nin);
			for(i=0;i<m_nin;i++)
			{
				el=new element();
				el->dim=((CGData *)m_inputs.GetAt(i))->GetDim();
				el->data=(double *)calloc(el->dim,sizeof(double));
				el->m_name=((CGData *)m_inputs.GetAt(i))->m_name;
				try
				{
					m_oinputs.SetAt(i,(CObject *)el);	
				}
				catch (CMemoryException *err)
				{
					AfxMessageBox("Out of Memory m_oinputs",MB_ICONSTOP|MB_OK);
					err->Delete();
				}
			}
		}
		if(m_delay==true)
		{
			if(m_value_n.GetUpperBound()!=-1)
			{
				for(i=0;i<m_value_n.GetSize();i++)
				{
					el=(element *)m_value_n[0];
					m_value_n.RemoveAt(0);
					delete el;
				}
			}
			m_value_n.RemoveAll();
			m_value_n.FreeExtra();
			m_value_n.SetSize(m_nout);
			for(i=0;i<m_nout;i++)
			{
				el=new element();
				el->dim=(((CGData *)m_outputs.GetAt(i))->GetDim());
				el->data=(double *)calloc(el->dim,sizeof(double));
				el->m_name=((CGData *)m_outputs[i])->m_name;
				try
				{
					m_value_n.SetAt(i,(CObject *)el);	
				}
				catch (CMemoryException *err)
				{
					AfxMessageBox("Out of Memory m_value_n",MB_ICONSTOP|MB_OK);
					err->Delete();
				}
			}
		}
		m_value.SetSize(m_nout);
		for(i=0;i<m_nout;i++)
		{
			el=new element();
			el->dim=(((CGData *)m_outputs.GetAt(i))->GetDim());
			el->data=(double *)calloc(el->dim,sizeof(double));
			el->m_name=((CGData *)m_outputs[i])->m_name;
			try
			{
					m_value.SetAt(i,(CObject *)el);	
			}
			catch (CMemoryException *err)
			{
				AfxMessageBox("Out of Memory m_value",MB_ICONSTOP|MB_OK);
				err->Delete();
			}
			proc_lambda(NULL,((CGOutput *)m_outputs[i])->m_name);
		}
	}
	other_init();
	//reset the data
	for(i=0;i<m_nin;i++)
		((CGData *)m_inputs[i])->ResetG();
	for(i=0;i<m_nout;i++)
		((CGData *)m_outputs[i])->ResetG();
	return 0;
}
else return 1;
}

int CGMesure::receive2(double time,CGData *input)
{
	AfxMessageBox("You must implement this virtual function",MB_OK);
	return -1;
}

int CGMesure::receive1(double time)
{
//
//we have send
//
	long i;
	for(i=0;i<m_nout;i++)
		proc_lambda((element *)m_value[i],((CGOutput *)m_outputs[i])->m_name);
	return 0;
}

int CGMesure::receive3(double time)
{
//
//we need output
//
	for(long i=0;i<m_nout;i++)
		proc_lambda((element *)m_value[i],((CGOutput *)m_outputs[i])->m_name);
	return 4;
}