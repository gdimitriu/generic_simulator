// GSum.cpp: implementation of the CGSum class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 version 1.0

	This file is part of Generic Simulator.
	This file contains the implementation of GSum class, this class is a pasive
	element in a simulation. It is a wire sumator.
	
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
#include "GSum.h"
#include "GInput.h"
#include "GOutput.h"

IMPLEMENT_SERIAL(CGSum,CGMesure,1);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGSum::CGSum() : CGMesure()
{
	m_delay=false;
	m_meminput=false;
	m_exec=NULL;
	m_vals=0;
	m_RInput=true;
}

CGSum::CGSum(CObject *parent,long val,bool type) : CGMesure(parent,val,type)
{
	m_meminput=false;
	m_delay=false;
	m_exec=NULL;
	m_vals=0;
	m_RInput=true;
}

CGSum::CGSum(CObject *parent,long name,long in,long dim,bool reset) : CGMesure(parent,name,false)
{
	m_RInput=reset;
	m_meminput=false;
	m_delay=false;
	m_exec=NULL;
	m_vals=0;
	CGInput *pin;
	CGOutput *pout;
	long i;
	for(i=0;i<in;i++)
	{
		pin=new CGInput(i);
		pin->SetDim(dim);
		AddPort(pin,true);
	}
	pout=new CGOutput(in);
	pout->SetDim(dim);
	AddPort(pout,false);
}

CGSum::~CGSum()
{
	if(m_exec!=NULL) free(m_exec);
}

void CGSum::Serialize(CArchive &ar)
{
	CGMesure::Serialize(ar);
	int temp;
	if(ar.IsStoring())
	{
		ar<<m_vals;
		temp=m_RInput;
		ar<<temp;
		for(long i=0;i<m_inputs.GetSize();i++)
		{
			temp=m_exec[i];
			ar<<temp;
		}
	}
	else
	{
		ar>>m_vals;
		ar>>temp;
		m_RInput=(bool)temp;
		if(m_exec!=NULL) free(m_exec);
		m_exec=(bool *)calloc(m_inputs.GetSize(),sizeof(bool));
		for(long i=0;i<m_inputs.GetSize();i++)
		{
			ar>>temp;
			m_exec[i]=(bool)temp;
		}
	}
}

int CGSum::receive2(double time,CGData *input)
{
	long i,N;
	N=m_inputs.GetSize();
	for(i=0;i<N;i++)
		if(m_inputs[i]==input) break;
	if(i==N) return -1;
	if(m_exec[i]==true) return 0; //it has been here
	m_exec[i]=true;
	((CGNetworkS *)m_parent)->ResetProc(this);
	((element *)m_value[0])->m_time=time;
	if(((element *)m_value[0])->dim!=1)
	{
		for(i=0;i<input->GetDim();i++)
			((element *)m_value[0])->data[i]+=input->m_value[i];
	}
	else
	{
		for(i=0;i<input->GetDim();i++)
			((element *)m_value[0])->data[0]+=input->m_value[i];
	}
	m_vals++;
	if(m_vals==N) receive1(time);
	return 2;
}
int CGSum::receive1(double time)
{
//
//we have send
//
	long i,j,k;
	if(((CGNetworkS *)m_parent)->GetCoordinator()!=NULL)
		if(((CGNetworkS *)m_parent)->GetWork(this)==true)
			return -1;
	((CGNetworkS *)m_parent)->SetProc(this);
	for(i=0;i<m_nout;i++)
		for(j=0;j<m_nin;j++)
		{
			if(m_exec[j]==false)
			{
				if(((element*)m_value[i])->dim!=1)
				{
					for(k=0;k<((CGData *)m_inputs[j])->GetDim();k++)
						((element *)m_value[i])->data[k]+=((CGData *)m_inputs[j])->m_value[k];
				}
				else
				{
					for(k=0;k<((element *)m_value[i])->dim;k++)
						((element *)m_value[i])->data[0]+=((CGData *)m_inputs[j])->m_value[k];
				}
			}
		}
	for(i=0;i<m_nin;i++)
		m_exec[i]=false;
	m_vals=0;
	for(i=0;i<m_nout;i++)
		proc_lambda((element *)m_value[i],((CGOutput *)m_outputs[i])->m_name);
	//reset the data
	for(i=0;i<m_nout;i++)
		for(k=0;k<((element *)m_value[i])->dim;k++)
			((element *)m_value[i])->data[k]=0.0;
	if(m_RInput==true)
		for(i=0;i<m_nin;i++)
			((CGData *)m_inputs[i])->ResetG();
	return 0;
}
void CGSum::other_init()
{
	long N;
	N=m_inputs.GetSize();
	if(m_exec!=NULL) free(m_exec);
	m_exec=(bool *)calloc(N,sizeof(bool));
	for(long i=0;i<N;i++)
		m_exec[i]=false;
	//reset the data
	for(int i=0;i<m_nout;i++)
		for(long j=0;j<((element *)m_value[i])->dim;j++)
			((element *)m_value[i])->data[j]=0.0;
}

int CGSum::receive3(double time)
{
	long i,j,k;
	element el;
	for(i=0;i<m_nout;i++)
	{
		el.dim=((element *)m_value[i])->dim;
		el.data=(double *)calloc(el.dim,sizeof(double));
		for(k=0;k<((element *)m_value[i])->dim;k++)
			el.data[k]=((element *)m_value[i])->data[k];
		for(j=0;j<m_nin;j++)
		{
			if(m_exec[j]==false)
				for(k=0;k<((element *)m_value[i])->dim;k++)
					el.data[k]+=((CGData *)m_inputs[j])->m_value[k];
		}
		proc_lambda(&el,((CGOutput *)m_outputs[i])->m_name);
		free(el.data);
		el.data=NULL;
	}
	return 0;
}

void CGSum::RInput(bool type)
{
	m_RInput=type;
}
