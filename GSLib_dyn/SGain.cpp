// SGain.cpp: implementation of the CSGain class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the implementation of simulation gain class.
	
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
#include "SGain.h"
#include <iostream>
#include "SProcessor.h"
#include "GInput.h"
#include "GOutput.h"

IMPLEMENT_SERIAL(CSGain,CSProcessor,1);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSGain::CSGain() : CSProcessor()
{
	m_gain=1.0;
	m_extern=false;
	m_delay=false;
	m_artime=NULL;
}

CSGain::CSGain(CObject *parent,long val,long in,long out,double gain): CSProcessor(parent,val,in,out,true)
{
	m_gain=gain;
	m_delay=false;
	m_extern=false;
	m_artime=NULL;
	if(in!=out)
		AfxMessageBox("The number of input and output ports must be same",MB_OK);
}

CSGain::~CSGain()
{
	if(m_artime!=NULL)
		free(m_artime);
}

void CSGain::Serialize(CArchive &ar)
{
	long i;
	CSProcessor::Serialize(ar);
	if(ar.IsStoring())
	{
		ar<<m_gain;
		ar<<m_vdelay;
		if(m_nin>1)
			for(i=0;i<m_nin;i++)
				ar<<m_artime[i];
	}
	else
	{
		ar>>m_gain;
		ar>>m_vdelay;
		if(m_nin>1)
		{
			if(m_artime!=NULL) free(m_artime);
			m_artime=(double *)calloc(m_nin,sizeof(double));
			for(i=0;i<m_nin;i++)
				ar>>m_artime[i];
		}
	}
}

int CSGain::local_receive0(double time)
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
	if(m_nin>1)
		m_artime=(double *)calloc(m_nin,sizeof(double));
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

int CSGain::local_receive2(double time,CGData *input)
{
//
//we have external
//
	CGInput *in;
	long i,j;
	double *data;
	element *val;
	in=(CGInput *)input;
	CGOutput *tout;
	long iname=in->GetName();
	long dim;
	data=in->Get(&dim);
	for(i=0;i<m_nin;i++)
		if(((CGInput *)m_inputs.GetAt(i))->GetName()==iname) break;
	tout=(CGOutput *)m_outputs.GetAt(i);
	if(m_nin>1)
	{
		if(fabs(m_artime[i]-time)>precision)
		{
			m_artime[i]=time;
			val=(element *)m_value[i];
			val->m_time=time;
			if(m_delay==false)
			{
				for(j=0;j<((element *)m_value[i])->dim;j++)
					((element *)m_value[i])->data[j]=m_gain*data[j];
				for(j=0;j<m_nin;j++)
					if(fabs(m_artime[j]-time)>precision) break;
				if(j==m_nin)
				{
					for(j=0;j<m_nout;j++)
						proc_lambda((element *)m_value[j],((CGOutput *)m_outputs[j])->m_name);
				}
			}
			else
			{
				if(m_extern==false)
				{
					for(j=0;j<((element *)m_value[i])->dim;j++)
						((element *)m_value[i])->data[j]=data[j]*m_gain;
					for(j=0;j<m_nin;j++)
						if(fabs(m_artime[j]-time)>precision) break;
					if(j==m_nin)
					{
						m_tL=time;
						m_tN=time+m_vdelay;
						m_extern=true;
						for(i=0;i<m_nout;i++)
							for(j=0;j<((element *)m_value_n[i])->dim;j++)
								((element *)m_value_n[i])->data[j]=((element *)m_value[i])->data[j];
					}
				}
				else if(m_extern==true && fabs(m_tN-time)<precision)
				{
					for(j=0;j<m_nout;j++)
						proc_lambda((element *)m_value_n[j],((CGOutput *)m_outputs[j])->m_name);
					m_extern=false;
					for(j=0;j<((element *)m_value[i])->dim;j++)
						((element *)m_value[i])->data[j]=data[j]*m_gain;
				}
			}
			return 0;
		}
		else return -1;
	}
	else
	{
		val=(element *)m_value[i];
		val->m_time=time;
		if(m_delay==false)
		{
			for(j=0;j<((element *)m_value[i])->dim;j++)
				((element *)m_value[i])->data[j]=m_gain*data[j];
			tout->SetSource(this);
			tout->SetTime(GetTime());
			tout->SetWTime(GetTime());
			tout->Set(val->data);
			if(m_mtype!=0 && m_mtype!=3)
				tout->RecvMsg(2,GetTime(),this);
		}
		else
		{
			if(m_extern==false)
			{
				m_tL=time;
				m_tN=time+m_vdelay;
				m_extern=true;
				for(j=0;j<((element *)m_value_n[i])->dim;j++)
					((element *)m_value_n[i])->data[j]=data[j]*m_gain;
			}
			else if(m_extern==true && fabs(m_tN-time)<precision)
			{
				for(j=0;j<m_nout;j++)
					proc_lambda((element *)m_value_n[j],((CGOutput *)m_outputs[j])->m_name);
				m_tL=time;
				m_tN=time+m_vdelay;
				m_extern=true;
				for(j=0;j<((element *)m_value_n[i])->dim;j++)
					((element *)m_value_n[i])->data[j]=data[j]*m_gain;
			}
		}
		return 0;
	}
	return -1;
}

int CSGain::local_receive1(double time)
{
//
//we have internal
//
	if(m_delay==true)
	{
		if(fabs(m_tN-time)<precision && m_extern==true)
		{
			for(long i=0;i<m_nout;i++)
				proc_lambda((element *)m_value_n[i],((CGOutput *)m_outputs[i])->m_name);
			m_extern=false;
		}
	}
	return 0;
}

void CSGain::SetDelay(double delay)
{
	m_delay=true;
	m_vdelay=delay;
}
