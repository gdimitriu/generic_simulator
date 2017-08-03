// STLineSD.cpp: implementation of the CSTLineSD class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the implementation of simulation transition line class.
	
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
#include "STLineSD.h"
#include "GInput.h"
#include "GOutput.h"
IMPLEMENT_SERIAL(CSTLineSD,CGProcessor,1);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CSTLineSD::CSTLineSD()
{

}
CSTLineSD::CSTLineSD(CObject *net,long val,CGTransition *trans,bool type) : CGProcessor(net,val,trans,type)
{
}
CSTLineSD::CSTLineSD(CObject *net,long val,long dim,double time,bool type) : CGProcessor(net,val,NULL,type)
{
	CGInput *pin;
	CGOutput *pout;
	pin=new CGInput(0);
	pin->SetDim(dim);
	AddPort(pin,true);
	pout=new CGOutput(1);
	pout->SetDim(dim);
	AddPort(pout,false);
	m_delaytime=time;
}
CSTLineSD::~CSTLineSD()
{

}
int CSTLineSD::receive0(double time)
{
//
//we have start
//
if(m_reinit==true)
{
	m_reinit=false;
	CGData *data;
	long i;
	m_tL=m_tN=time;
	m_s=0;
	m_internal=false;
	m_extern=false;
	m_status=0;
	m_nout=1;
	element *el;
	while(m_queue.empty()==false)
	{
		data=(CGData *)(m_queue.front());
		delete data;
	}
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
	m_value.SetSize(1);
	el=new element();
	el->dim=(((CGData *)m_outputs.GetAt(0))->GetDim());
	el->data=(double *)calloc(el->dim,sizeof(double));
	el->m_name=((CGData *)m_outputs[0])->m_name;
	try
	{
		m_value.SetAt(0,(CObject *)el);	
	}
	catch (CMemoryException *err)
	{
		AfxMessageBox("Out of Memory m_value",MB_ICONSTOP|MB_OK);
		err->Delete();
	}
	proc_lambda(NULL);
	((CGData *)m_inputs[0])->ResetG();
	((CGData *)m_outputs[0])->ResetG();
	return 0;
}
else return 1;
}

int CSTLineSD::receive1(double time)
{
//
//we have internal transition
//
	bool m_run;
	long i;
	CGData *data;
	m_run=true;
	if(((CGNetworkS *)m_parent)->GetCoordinator()!=NULL)
		if(((CGNetworkS *)m_parent)->GetWork(this)==true)
			m_run=false;
	((CGNetworkS *)m_parent)->ResetProc(this);
	if((fabs(time-m_tN)<precision || fabs(m_tN-time)<m_CLKP || fabs(m_tN)<precision) && m_run==true)
	{
		proc_lambda((element *)m_value[0]);
		if(m_queue.empty()==true)
			m_extern=false;
		else
		{
			m_extern=true;
			data=(CGData *)(m_queue.front());
			double *dat;
			long dim;
			dat=data->Get(&dim);
			for(i=0;i<dim;i++)
				((element *)m_value[0])->data[i]=dat[i];
			SettL(GetTime());
			SettN(data->GetTime());
			delete data;
		}
	}
	else if(time<m_tN)
	{
		if(m_rtype==true)
			proc_lambda(NULL);
	}
	return 4;
}

int CSTLineSD::receive2(double time, CGData *input)
{
//
//we have external transition
//
	((CGNetworkS *)m_parent)->SetProc(this);
	if(input!=NULL)
	{
		if(fabs(time-m_tN)<precision || (fabs(time-m_tN)<m_CLKP && m_extern==true) || m_extern==false)
			return ExternN(input,time);
		else
			return ExternS(input,time);
	}
	else return -2;
	return 4;
}

int CSTLineSD::ExternN(CGData *input, double time)
{
	long i;
	long dim;
	double *value;
	CGInput *in;
	in=(CGInput *)input;
	value=in->Get(&dim);
	CGData *data;
	if(m_queue.empty()==false)
	{
		if(m_extern==true)
			proc_lambda((element *)m_value[0]);
		data=new CGData(in->m_name);
		data->SetDim(dim);
		data->Set(value);
		data->SetTime(in->GetTime()+m_delaytime);
		data->SetSource(in->GetSource());
		data->SetSourceName(in->GetSourceName());
		m_queue.add((CObject *)data);
		data=(CGData *)(m_queue.front());
		if(data==NULL) cout<<"Error!\n";cout.flush();
		m_extern=true;
		value=data->Get(&dim);
		for(i=0;i<dim;i++)
			((element *)m_value[0])->data[i]=value[i];
		SettL(GetTime());
		SettN(data->GetTime());
		delete data;
	}
	else
	{
		if(m_extern==true)
			proc_lambda((element *)m_value[0]);
		m_extern=true;
		value=in->Get(&dim);
		for(i=0;i<dim;i++)
			((element *)m_value[0])->data[i]=value[i];
		SettL(GetTime());
		SettN(in->GetTime()+m_delaytime);
	}
	return 4;
}
int CSTLineSD::ExternS(CGData *input, double time)
{
	long dim;
	double *value;
	CGInput *in;
	in=(CGInput *)input;
	value=in->Get(&dim);
	CGData *data;
	data=new CGData(in->m_name);
	data->SetDim(dim);
	data->Set(value);
	data->SetTime(in->GetTime()+m_delaytime);
	data->SetSource(in->GetSource());
	data->SetSourceName(in->GetSourceName());
	m_queue.add((CObject *)data);
	return 4;
}

int CSTLineSD::receive3(double time)
{
//
//we need output
//
	proc_lambda((element *)m_value[0]);
	return 4;
}

int CSTLineSD::proc_lambda(element *val)
{
	CGData *tout;
	tout=(CGData *)(m_outputs.GetAt(0));
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
void CSTLineSD::Serialize(CArchive &ar)
{
	CGProcessor::Serialize(ar);
	if(ar.IsStoring())
	{
		ar<<m_delaytime;
	}
	else
	{
		ar>>m_delaytime;
	}
}
