// SProcessor.cpp: implementation of the CSProcessor class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the implementation of simulation processor class, this class is the active
	element in a simulation. This class in used only with CGTransition and CGNetworkS
	classes and theirs derivate.
	
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

IMPLEMENT_SERIAL(CSProcessor,CGProcessor,1);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSProcessor::CSProcessor()
{

}

CSProcessor::CSProcessor(CObject *parent,long val,CGTransition *generator,bool type) : CGProcessor(parent,val,generator,type)
{

}

CSProcessor::CSProcessor(CObject *parent,long val,long in,long out,CGTransition *generator,bool type) : CGProcessor(parent,val,generator,type)
{
	CGInput *pin;
	CGOutput *pout;
	long i;
	for(i=0;i<in;i++)
	{
		pin=new CGInput(i);
		AddPort(pin,true);
	}
	for(i=in;i<in+out;i++)
	{
		pout=new CGOutput(i);
		AddPort(pout,false);
	}
}

CSProcessor::CSProcessor(CObject *parent,long val,long in,long out,bool type) : CGProcessor(parent,val,NULL,type)
{
	CGInput *pin;
	CGOutput *pout;
	long i;
	for(i=0;i<in;i++)
	{
		pin=new CGInput(i);
		AddPort(pin,true);
	}
	for(i=in;i<in+out;i++)
	{
		pout=new CGOutput(i);
		AddPort(pout,false);
	}
	m_compute=NULL;
}


CSProcessor::~CSProcessor()
{

}

void CSProcessor::Serialize(CArchive &ar)
{
	CGProcessor::Serialize(ar);
}

int CSProcessor::receivemsg(int type, double time, CObject *in)
{
/*
	type is the receiving message: 0=start;1=int;2=ext;3=out;4=done;
	time is the time of the simulation
	in is the pointer to the input port
	it's return is 4=done or -1=error
*/
	m_time=time;
	m_e=time;
	if(type!=0 && type!=3)
	{
		m_sL=m_s;
		m_ltype=m_mtype;
	}
	m_mtype=type;
	CGData *input=(CGData *)in;
	if(type!=3)
		m_runs=true;
	switch(type)
	{
	case 0:
		if(m_compute!=NULL)
			return receive0(time);
		else
			return local_receive0(time);
	case 1:
		if(m_compute!=NULL)
			return receive1(time);
		else
			return local_receive1(time);
	case 2:
		if(m_compute!=NULL)
			return receive2(time,input);
		else
			return local_receive2(time,input);
	case 3:
		if(m_compute!=NULL)
			return receive3(time);
		else
			return local_receive3(time);
	default:
		return 0;
	}
}
int CSProcessor::proc_lambda(element *val,long port)
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

int CSProcessor::local_receive0(double time)
{
//
//we have start
//
	AfxMessageBox("You must implement this virtual function",MB_OK);
	return -1;
}

int CSProcessor::local_receive2(double time,CGData *input)
{
//
//we have external
//
	AfxMessageBox("You must implement this virtual function",MB_OK);
	return -1;
}

int CSProcessor::local_receive1(double time)
{
//
//we have internal
//
	AfxMessageBox("You must implement this virtual function",MB_OK);
	return -1;
}

int CSProcessor::local_receive3(double time)
{
//
//we need output
//
	for(long i=0;i<m_nout;i++)
		proc_lambda((element *)m_value[i],((CGOutput *)m_outputs[i])->m_name);
	return 4;
}
