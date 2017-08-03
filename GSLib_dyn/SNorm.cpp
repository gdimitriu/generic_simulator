// SNorm.cpp: implementation of the CSNorm class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the implementation of simulation norm class.
	
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
#include <iostream>
#include "SProcessor.h"
#include "GInput.h"
#include "GOutput.h"
#include "SNorm.h"
IMPLEMENT_SERIAL(CSNorm,CSProcessor,1);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSNorm::CSNorm() : CSProcessor()
{
	m_normtype=-1;
}
CSNorm::CSNorm(CObject *parent,long val,long dim,int type): CSProcessor(parent,val,1,1,true)
{
	SetDimPort(0,dim);
	m_normtype=type;
}
CSNorm::~CSNorm()
{

}

void CSNorm::Serialize(CArchive &ar)
{
	CSProcessor::Serialize(ar);
	if(ar.IsStoring())
	{
		ar<<m_normtype;
	}
	else
	{
		ar>>m_normtype;
	}
}

int CSNorm::local_receive0(double time)
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
	//reset the data
	((CGData *)m_inputs[0])->ResetG();
	((CGData *)m_outputs[0])->ResetG();
	return 0;
}
else return 1;
}

int CSNorm::local_receive2(double time,CGData *input)
{
//
//we have external
//
	CGInput *in;
	long i;
	double *data;
	double temp;
	element *val;
	in=(CGInput *)input;
	CGOutput *tout;
	long dim;
	data=in->Get(&dim);
	val=(element *)m_value[0];
	val->m_time=time;
	val->data[0]=0.0;
	switch(m_normtype)
	{
	case 1:
		for(i=0;i<dim;i++)
			val->data[0]+=fabs(data[i]);
		break;
	case 2:
		for(i=0;i<dim;i++)
			val->data[0]+=fabs(data[i])*fabs(data[i]);
		val->data[0]=sqrt(val->data[0]);
		break;
	case -1:
		temp=data[0];
		for(i=1;i<dim;i++)
			if(data[i]>temp) temp=data[i];
		val->data[0]=temp;
		break;
	default:
		for(i=0;i<dim;i++)
			val->data[0]+=pow(fabs(data[i]),m_normtype);
		val->data[0]=pow(val->data[0],1.0/m_normtype);
	}
	tout=(CGOutput *)m_outputs[0];
	tout->SetSource(this);
	tout->SetTime(GetTime());
	tout->SetWTime(GetTime());
	tout->Set(val->data);
	if(m_mtype!=0 && m_mtype!=3)
		tout->RecvMsg(2,GetTime(),this);
	return 0;
}

int CSNorm::local_receive1(double time)
{
//
//we have internal
//
	return 0;
}
