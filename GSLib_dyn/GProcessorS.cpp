// GProcessorS.cpp: implementation of the CGProcessorS class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 Version 1.0

	This file is part of Generic Simulator.
	This file contains the implementation of synchron processor class, this class is the active
	element in a simulation. This class in used only with CGTransitionS and CGNetworkS
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
#include "GProcessorS.h"
#include <iostream>
#include "GNetworkS.h"
#include "GInput.h"
#include "GOutput.h"

IMPLEMENT_SERIAL(CGProcessorS,CGProcessor,1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGProcessorS::CGProcessorS() : CGProcessor()
{
	m_win=NULL;
	m_runS=false;
	m_disableq=true;
	m_ev=0;
	m_first3=true;
	m_general=true;
}

CGProcessorS::CGProcessorS(CObject *parent,long val,CGTransition *generator,bool type) : CGProcessor(parent,val,generator,type)
{
	m_win=NULL;
	m_runS=false;
	m_disableq=true;
	m_ev=0;
	m_first3=true;
	m_general=true;
}

CGProcessorS::~CGProcessorS()
{
	if(m_win!=NULL) free(m_win);
}

void CGProcessorS::Set2atInput(CGData *input)
{
	for(long i=0;i<m_nin;i++)
		if(((CGData *)m_inputs[i])->m_name==input->m_name)
		{
			m_win[i]=true;
			return;
		}
}

bool CGProcessorS::Get2atInput(CGData *input)
{
	for(long i=0;i<m_nin;i++)
		if(((CGData *)m_inputs[i])->m_name==input->m_name)
			return m_win[i];
	return false;
}

int CGProcessorS::receivemsg(int type, double time, CObject *in)
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
	if(type!=3) m_runs=true;
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

int CGProcessorS::receive0(double time)
{
//
//we have start
//
if(m_reinit==true)
{
	m_reinit=false;
	element *el;
	long i;
	m_tL=m_tN=time;
	m_s=0;
	m_internal=false;
	m_extern=false;
	m_nout=m_outputs.GetSize();
	m_nin=m_inputs.GetSize();
	if(m_win!=NULL) free(m_win);
	m_win=(bool *)calloc(m_nin,sizeof(bool));
	for(i=0;i<m_nin;i++)
		m_win[i]=false;
	if(m_memory==true)
	{
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
		if(m_meminput==true)
		{
			if(m_oinputs.GetUpperBound()!=-1)
			{
				for(i=0;i<m_oinputs.GetSize();i++)
				{
					el=(element *)m_oinputs[i];
					m_oinputs.RemoveAt(i);
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
					el=(element *)m_value_n[i];
					m_value_n.RemoveAt(i);
					delete el;
				}
			}
			m_value_n.RemoveAll();
			m_value_n.FreeExtra();
			m_value_n.SetSize(m_nout);
			for(i=0;i<m_nout;i++)
			{
				el=new element();
				el->dim=((CGData *)m_outputs.GetAt(i))->GetDim();
				el->data=(double *)calloc(el->dim,sizeof(double));
				el->m_name=((CGData *)m_outputs.GetAt(i))->m_name;
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
			el->m_name=((CGData *)m_outputs.GetAt(i))->m_name;
			try
			{
					m_value.SetAt(i,(CObject *)el);	
			}
			catch (CMemoryException *err)
			{
				AfxMessageBox("Out of Memory m_value_n",MB_ICONSTOP|MB_OK);
				err->Delete();
			}
			m_compute->proc_lambda(this,NULL,((CGOutput *)m_outputs.GetAt(i))->m_name);
		}
	}
	if(m_general==true) m_compute->assign_memory(this);
	for(i=0;i<m_nin;i++)
		((CGData *)m_inputs[i])->ResetG();
	for(i=0;i<m_nout;i++)
		((CGData *)m_outputs[i])->ResetG();
	other_init();
	return 0;
}
else return 1;
}

int CGProcessorS::receive1(double time)
{
//
//we have internal transition
//
	bool m_run;
	long i;
	if(m_runS==true)
	{
		if(m_ev<m_nin)
		{
			if(m_delay==true)
				m_compute->proc_deltaext(this,NULL,&m_s,&m_value,&m_value_n,m_nout);
			else
				m_compute->proc_deltaext(this,NULL,&m_s,&m_value,&m_value,m_nout);
		}
		//copy the input for the next transition
		if(m_meminput==true)
		{
			for(i=0;i<m_nin;i++)
			{
				((element *)m_oinputs[i])->source=((CGData *)m_inputs[i])->GetSource();
				((element *)m_oinputs[i])->sourcename=((CGData *)m_inputs[i])->GetSourceName();
				memcpy(((element *)m_oinputs[i])->data,((CGData *)m_inputs[i])->m_value,((CGData *)m_inputs[i])->GetDim());
			}
		}
		//reset the input
		if(m_ritype==true)
			for(i=0;i<m_nin;i++)
				((CGData *)m_inputs[i])->Reset();
		//reset the synchro
		m_runS=false;
		for(i=0;i<m_nin;i++)
			m_win[i]=false;
		m_ev=0;
		m_first3=true;
		//set the it's executed the recevice 1 message
		((CGNetworkS *)m_parent)->SetProc(this);
		return 2;
	}
	//from here we have the normal use of receive 1
	((CGNetworkS *)m_parent)->SetProc(this);
	if(!(m_internal==false && m_extern==false))  m_run=true;
	else
	{
		if(m_first==true) m_run=true;
		else m_run=false;
	}
	if((fabs(time-m_tN)<precision || fabs(m_tN-time)<m_CLKP) && m_run==true)
	{
		long i,j;
		if(m_delay==true)
		{
			for(i=0;i<m_nout;i++)
			{
				for(j=0;j<((element *)m_value_n[i])->dim;j++)
					((element *)m_value[i])->data[j]=((element *)m_value_n[i])->data[j];
				((element *)m_value[i])->source=((element *)m_value_n[i])->source;
			}
		}
		for(i=0;i<m_nout;i++)
			m_compute->proc_lambda(this,(element *)m_value[i],((CGOutput *)m_outputs.GetAt(i))->m_name);
		if(m_delay==true)
			m_compute->proc_deltaint(this,&m_s,&m_value,&m_value_n,m_nout);
		else
			m_compute->proc_deltaint(this,&m_s,&m_value,&m_value,m_nout);
		//copy the input for the next transition
		m_internal=true;
		m_extern=false;
	}
	else if(time<m_tN)
	{
		if(m_rtype==true)
		{
			m_nout=m_outputs.GetSize();
			for(long i=0;i<m_nout;i++)
				m_compute->proc_lambda(this,NULL,((CGOutput *)m_outputs.GetAt(i))->m_name);
		}
	}
	return 4;
}

int CGProcessorS::receive2(double time, CGData *input)
{
//
//we have external transition
//
	CGInput *in;
	in=(CGInput *)input;
	if(in!=NULL)
	{
		//it was internal
		if(m_internal==true) if(fabs(time-m_tN)<precision || fabs(time-m_tN)<m_CLKP)
		{
			long i,j;
			if(m_delay==true)
			{
				for(i=0;i<m_nout;i++)
				{
					for(j=0;j<((element *)m_value_n[i])->dim;j++)
						((element *)m_value[i])->data[j]=((element *)m_value_n[i])->data[j];
					((element *)m_value[i])->source=((element *)m_value_n[i])->source;
				}
				m_first3=false;
			}
			for(i=0;i<m_nout;i++)
				m_compute->proc_lambda(this,(element *)m_value[i],((CGOutput *)m_outputs.GetAt(i))->m_name);
		}
		//run external
		if(fabs(time-m_tN)<precision || fabs(time-m_tN)<m_CLKP ||(m_internal==false && m_extern==false))
		{
			if(Get2atInput(in)==false) //it wasn't
			{
				m_runS=true;
				m_ev++;
				Set2atInput(in);
				
				if(m_first3==true)
				{
					long i,j;
					if(m_delay==true)
					{
						for(i=0;i<m_nout;i++)
						{
							for(j=0;j<((element *)m_value_n[i])->dim;j++)
								((element *)m_value[i])->data[j]=((element *)m_value_n[i])->data[j];
							((element *)m_value[i])->source=((element *)m_value_n[i])->source;
						}						
					}
					for(i=0;i<m_nout;i++)
						m_compute->proc_lambda(this,(element *)m_value[i],((CGOutput *)m_outputs.GetAt(i))->m_name);
					m_first3=false;
				}
			}
			else return -3;
			if(m_ev==m_nin)
			{
				if(m_delay==true)
					m_compute->proc_deltaext(this,in,&m_s,&m_value,&m_value_n,m_nout);
				else
					m_compute->proc_deltaext(this,in,&m_s,&m_value,&m_value,m_nout);
			}
			m_extern=true;
			m_internal=false;
			return 4;
		}
	}
	else return -2;
	return 4;
}

int CGProcessorS::receive3(double time)
{
//
//we need output
//
	for(long i=0;i<m_nout;i++)
		m_compute->proc_lambda(this,(element *)m_value[i],((CGOutput *)m_outputs.GetAt(i))->m_name);
	return 4;
}

int CGProcessorS::RInitP(CGData *port)
{
	long i;
	element *el;
	if(port->IsKind()==1) //output port
	{
		long tst=m_outputs.GetSize();
		for(i=0;i<tst;i++)
			if((CGData *)m_outputs[i]==port)
			{
				if(m_memory==true)
				{
					if(m_value.GetSize()!=0)
					{
						el=new element();
						el->dim=((CGOutput *)m_outputs.GetAt(i))->GetDim();
						el->data=(double *)calloc(el->dim,sizeof(double));
						el->m_name=((CGOutput *)m_outputs.GetAt(i))->m_name;
						try
						{
							m_value.Add((CObject *)el);	
						}
						catch (CMemoryException *err)
						{
							AfxMessageBox("Out of Memory m_value",MB_ICONSTOP|MB_OK);
							err->Delete();
						}
					}
				}
				if(m_delay==true && m_memory==true)
				{
					if(m_value_n.GetSize()!=0)
					{
						el=new element();
						el->dim=((CGOutput *)m_outputs.GetAt(i))->GetDim();
						el->data=(double *)calloc(el->dim,sizeof(double));
						el->m_name=((CGOutput *)m_outputs.GetAt(i))->m_name;
						try
						{
							m_value_n.Add((CObject *)el);	
						}
						catch (CMemoryException *err)
						{
							AfxMessageBox("Out of Memory m_value_n",MB_ICONSTOP|MB_OK);
							err->Delete();
						}
					}
				}
				if(m_compute!=NULL) m_compute->assign_memory(this,((CGOutput *)m_outputs.GetAt(i))->m_name,true);
				return 0;
			}
		if(i==tst) return -1;
	}
	else
	{
		long tst=m_inputs.GetSize();
		for(i=0;i<tst;i++)
			if((CGData *)m_inputs[i]==port)
			{
				if(m_compute!=NULL) m_compute->assign_memory(this,i,false);
				bool *temp=(bool *)calloc(tst,sizeof(bool));
				long k,j;
				for(j=0,k=0;j<tst;j++)
				{
					if(j!=i)
					{
						temp[j]=m_win[k];
						k++;
					}
					else temp[j]=false;
				}
				if(m_win!=NULL) free(m_win);
				m_win=temp;
				if(m_meminput==true)
				{
					if(m_oinputs.GetSize()!=0)
					{
						el=new element();
						el->dim=((CGInput *)m_inputs.GetAt(i))->GetDim();
						el->data=(double *)calloc(el->dim,sizeof(double));
						el->m_name=((CGInput *)m_inputs.GetAt(i))->m_name;
						try
						{
							m_oinputs.Add((CObject *)el);	
						}
						catch (CMemoryException *err)
						{
							AfxMessageBox("Out of Memory m_oinputs",MB_ICONSTOP|MB_OK);
							err->Delete();
						}
					}
				}
				return 0;
			}
		if(i==tst) return -2;
	}
	return -3;
}

int CGProcessorS::DelPort(CGData *dead)
{
	long i,j;
	element *el;
	if(dead->m_parent_wire!=NULL) //self decided
	{
		CGWire *wire=(CGWire *)dead->m_parent_wire;
		if(wire->kill(dead)==0)
		{
			if(m_parent!=NULL)
				((CGNetworkS *)m_parent)->DelWire(wire);
			else
				((CGNetworkS *)m_parent_del)->DelWire(wire);
		}
	}
	if(dead->IsKind()==1) //output port
	{
		long tst=m_outputs.GetSize();
		for(i=0;i<tst;i++)
			if((CGData *)m_outputs[i]==dead)
			{
				m_compute->DelPort(i,true);
				m_outputs.RemoveAt(i);
				if(m_value.GetSize()!=0)
				{
					for(j=0;j<m_value.GetSize();j++)
					{
						el=(element *)m_value[j];
						if(el->m_name==dead->m_name)
						{
							m_value.RemoveAt(j);
							delete el;
							break;
						}
					}
				}
				if(m_delay==true)
				{
					if(m_value_n.GetSize()!=0)
					{
						for(j=0;j<m_value_n.GetSize();j++)
						{
							el=(element *)m_value_n[j];
							if(el->m_name==dead->m_name)
							{
								m_value_n.RemoveAt(j);
								delete el;
								break;
							}
						}
					}
				}
				m_value.FreeExtra();
				m_value_n.FreeExtra();
				m_outputs.FreeExtra();
				m_nout--;
				delete dead;
				return 0;
			}
		if(i==tst) return -1;
	}
	else
	{
		long tst=m_inputs.GetSize();
		for(i=0;i<tst;i++)
			if((CGData *)m_inputs[i]==dead)
			{
				m_compute->DelPort(i,false);
				if(m_meminput==true)
				{
					if(m_oinputs.GetSize()!=0)
					{
						for(j=0;j<m_oinputs.GetSize();j++)
						{
							el=(element *)m_oinputs[j];
							if(el->m_name==dead->m_name)
							{
								m_oinputs.RemoveAt(j);
								delete el;
								break;
							}
						}
					}
				}
				bool *temp=(bool *)calloc(tst-1,sizeof(bool));
				long k,j;
				for(j=0,k=0;j<tst-1;j++)
				{
					if(j!=i)
					{
						temp[j]=m_win[k];
						k++;
					}
				}
				if(m_win!=NULL) free(m_win);
				m_win=temp;
				m_oinputs.FreeExtra();
				m_inputs.RemoveAt(i);
				m_inputs.FreeExtra();
				m_nin--;
				delete dead;
				return 0;
			}
		if(i==m_inputs.GetSize()) return -2;
	}
	return -3;
}	

void CGProcessorS::Serialize(CArchive &ar)
{
	CGProcessor::Serialize(ar);
	long i;
	int temp;
	if(ar.IsStoring())
	{
		ar<<m_ev;
		temp=(int)m_first3;
		ar<<temp;
		temp=(int)m_runS;
		ar<<temp;
		for(i=0;i<m_nin;i++)
		{
			temp=(int)m_win[i];
			ar<<temp;
		}
	}
	else
	{
		ar>>m_ev;
		ar>>temp;
		m_first3=(bool)temp;
		ar>>temp;
		m_runS=(bool)temp;
		m_win=(bool *)calloc(m_nin,sizeof(bool));
		for(i=0;i<m_nin;i++)
		{
			ar>>temp;
			m_win[i]=(bool)temp;
		}
	}
}
