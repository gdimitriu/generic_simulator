// SDotP.cpp: implementation of the CSDotP class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the implementation of simulation dot product class.
	
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
#include "SDotP.h"
#include "SProcessor.h"
#include "GInput.h"
#include "GOutput.h"

IMPLEMENT_SERIAL(CSDotP,CSProcessor,1);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSDotP::CSDotP()
{

}
CSDotP::CSDotP(CObject *parent,long name,long dim) : CSProcessor(parent,name,2,1,true)
{
	SetDimPort(0,dim);
	SetDimPort(1,dim);
	m_realiz[0]=false;
	m_realiz[1]=false;
}
CSDotP::~CSDotP()
{

}

void CSDotP::Serialize(CArchive &ar)
{
	int tmp;
	CSProcessor::Serialize(ar);
	if(ar.IsStoring())
	{
		tmp=m_realiz[0];
		ar<<tmp;
		tmp=m_realiz[1];
		ar<<tmp;
	}
	else
	{
		ar>>tmp;
		m_realiz[0]=(bool)tmp;
		ar>>tmp;
		m_realiz[1]=(bool)tmp;
	}
}

int CSDotP::local_receive0(double time)
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
	((CGData *)m_inputs[1])->ResetG();
	((CGData *)m_outputs[0])->ResetG();
	m_realiz[0]=false;
	m_realiz[1]=false;
	return 0;
}
else return 1;
}

int CSDotP::local_receive2(double time,CGData *input)
{
//
//we have external
//
	CGInput *in;
	long i;
	double *data1,*data2;
	element *val;
	in=(CGInput *)input;
	CGOutput *tout;
	long dim;
	if(m_realiz[in->GetName()]==false)
		m_realiz[in->GetName()]=true;
	if(m_realiz[0]==true && m_realiz[1]==true)
	{
		data1=((CGInput *)m_inputs[0])->Get(&dim);
		data2=((CGInput *)m_inputs[1])->Get(&dim);
		val=(element *)m_value[0];
		val->m_time=time;
		val->data[0]=0.0;
		for(i=0;i<dim;i++)
			val->data[0]+=data1[i]*data2[i];
		tout=(CGOutput *)m_outputs[0];
		tout->SetSource(this);
		tout->SetTime(GetTime());
		tout->SetWTime(GetTime());
		tout->Set(val->data);
		m_realiz[0]=false;
		m_realiz[1]=false;
		if(m_mtype!=0 && m_mtype!=3)
			tout->RecvMsg(2,GetTime(),this);
	}
	return 0;
}

int CSDotP::local_receive1(double time)
{
//
//we have internal
//
	double *data1,*data2;
	CGOutput *tout;
	long dim;
	long i;
	element *val;
	if(m_realiz[0]==true || m_realiz[1]==true)
	{
		data1=((CGInput *)m_inputs[0])->Get(&dim);
		data2=((CGInput *)m_inputs[1])->Get(&dim);
		val=(element *)m_value[0];
		val->m_time=time;
		val->data[0]=0.0;
		for(i=0;i<dim;i++)
			val->data[0]+=data1[i]*data2[i];
		tout=(CGOutput *)m_outputs[0];
		tout->SetSource(this);
		tout->SetTime(GetTime());
		tout->SetWTime(GetTime());
		tout->Set(val->data);
		m_realiz[0]=false;
		m_realiz[1]=false;
		if(m_mtype!=0 && m_mtype!=3)
			tout->RecvMsg(2,GetTime(),this);
	}
	return 0;
}
