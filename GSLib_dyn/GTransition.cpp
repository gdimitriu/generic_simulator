// GTransition.cpp: implementation of the CGTransition class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the implementation of transition class. This class is the real 
	class who implement the real function of the active element.
	
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

#include <iostream>
#include "stdafx.h"
#include "GTransition.h"
#include "GNetworkS.h"
#include "GOutput.h"
#include "GInput.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
IMPLEMENT_SERIAL(CGTransition,CObject,1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGTransition::CGTransition()
{
	m_repartition=NULL;
	m_ttrans=NULL;
	m_clk=1.0;
	m_first=false;
	m_ememory=false;
	m_memory=NULL;
	m_amemory=false;
}

CGTransition::CGTransition(CString *var)
{
	m_repartition=new CGRepartition;
	m_repartition->SetGen(var);
	m_ttrans=m_repartition;
	m_clk=1.0;
	m_first=false;
	m_ememory=true;
	m_memory=NULL;
	m_amemory=false;
}

CGTransition::~CGTransition()
{
	if(m_repartition!=NULL) delete m_repartition;
	if(m_memory!=NULL && m_ememory==true) delete m_memory;
	Cparser_func *f;
	long i;
	if(m_extfunc.GetUpperBound()!=-1)
	{
		for(i=0;i<m_extfunc.GetSize();i++)
		{
			f=(Cparser_func *)m_extfunc[i];
			delete f;
			m_extfunc.RemoveAt(i);
		}
	}
	m_extfunc.RemoveAll();
	m_extfunc.FreeExtra();
	if(m_intfunc.GetUpperBound()!=-1)
	{
		for(i=0;i<m_intfunc.GetSize();i++)
		{
			f=(Cparser_func *)m_intfunc[i];
			delete f;
			m_intfunc.RemoveAt(i);
		}
	}
	m_intfunc.RemoveAll();
	m_intfunc.FreeExtra();
}

void CGTransition::SetParent(CGProcessor *parent)
{
//
//set the parent of the transition
//
	m_parent=(CGProcessor *)parent;
}
void CGTransition::Set(long seed)
{
//
//set the seed of the random number generator
//
	m_repartition->Set(seed);
	m_seed=seed;
	m_nrout=m_parent->m_nout;
}

void CGTransition::assign_memory(CGProcessor *proc)
{
	long i,j;
	long nrin,nrout;
	if(m_ememory==true)
	{
		if(m_memory!=NULL) delete m_memory;
		m_memory=new Cparser_func_memory;
		m_amemory=true;
		nrin=proc->m_nin;
		nrout=proc->m_nout;
		m_nrout=nrout;
		for(i=0;i<nrout;i++)
		{
			((Cparser_func *)m_extfunc[i])->assign_memory(m_memory);
			((Cparser_func *)m_intfunc[i])->assign_memory(m_memory);
		}
		char names[1000];
		char temp[1000];
		for(i=0;i<nrout;i++)
		{
			for(j=0;j<1000;j++)
			{
				temp[j]='\0';
				names[j]='\0';
			}
			_itoa(((element *)proc->m_value[i])->m_name,temp,10);
			strcpy(&names[1],temp);
			names[0]='y';
			m_memory->assign_memory(names,((element *)proc->m_value[i])->data,((element *)proc->m_value[i])->dim);
		}
		for(i=0;i<nrin;i++)
		{
			CGData *data;
			data=(CGData *)(proc->m_inputs).GetAt(i);
			for(j=0;j<1000;j++)
			{
				temp[j]='\0';
				names[j]='\0';
			}
			_itoa(data->m_name,temp,10);
			names[0]='x';
			strcpy(&names[1],temp);
			m_memory->assign_memory(names,data->m_value,data->GetDim());
		}
		if(proc->m_meminput==true)
		{
			for(i=0;i<nrin;i++)
			{
				for(j=0;j<1000;j++)
				{
					temp[j]='\0';
					names[j]='\0';
				}
				_itoa(((element *)proc->m_oinputs[i])->m_name,temp,10);
				strcpy(&names[1],temp);
				names[0]='t';
				m_memory->assign_memory(names,((element *)proc->m_oinputs[i])->data,((element *)proc->m_oinputs[i])->dim);
			}
		}
	}
}

void CGTransition::assign_memory(CGProcessor *proc,long pos,bool type)
{
	char names[1000];
	char temp[1000];
	long i;
	if(m_ememory==true && m_amemory==true)
	{
		_itoa(pos,temp,10);
		strcpy(&names[1],temp);
		if(type==true) //is output
		{
			Cparser_func *func;
			func=new Cparser_func;
			func->SetName(pos);
			m_extfunc.Add(func);
			((Cparser_func *)m_extfunc[m_extfunc.GetSize()-1])->assign_memory(m_memory);
			func=new Cparser_func();
			func->SetName(pos);
			m_intfunc.Add(func);
			((Cparser_func *)m_intfunc[m_intfunc.GetSize()-1])->assign_memory(m_memory);
			names[0]='y';
			for(i=0;i<proc->m_value.GetSize();i++)
			{
				if(((element *)proc->m_value[i])->m_name==pos)
				{
					m_memory->assign_memory(names,((element *)proc->m_value[i])->data,((element *)proc->m_value[i])->dim);
					break;
				}
			}
		}
		else
		{
			CGData *data;
			for(i=0;i<proc->m_inputs.GetSize();i++)
			{
				data=(CGData *)(proc->m_inputs).GetAt(i);
				if(data->m_name==pos)
				{
					names[0]='x';
					m_memory->assign_memory(names,data->m_value,data->GetDim());
					if(proc->m_meminput==true)
					{
						names[0]='t';
						m_memory->assign_memory(names,((element *)proc->m_oinputs[i])->data,((element *)proc->m_oinputs[i])->dim);
					}
				}
			}
		}
	}
}

void CGTransition::set_extfunc(char *func, long pos)
{
	Cparser_func *f;
	long i;
	if(m_first==false)
	{
		if(m_extfunc.GetUpperBound()!=-1)
		{
			for(i=0;i<m_extfunc.GetSize();i++)
			{
				f=(Cparser_func *)m_extfunc[i];
				delete f;
				m_extfunc.RemoveAt(i);
			}
		}
		m_extfunc.RemoveAll();
		m_extfunc.FreeExtra();
		m_extfunc.SetSize(m_parent->m_nout);
		for(i=0;i<m_parent->m_nout;i++)
		{
			try
			{
				f=new Cparser_func();
				f->SetName(((CGData *)m_parent->m_outputs[i])->GetName());
				m_extfunc.SetAt(i,(CObject *)f);
			}
			catch (CMemoryException *err)
			{
				AfxMessageBox("Out of Memory external function",MB_ICONSTOP|MB_OK);
				err->Delete();
			}
		}
		if(m_intfunc.GetUpperBound()!=-1)
		{
			for(i=0;i<m_intfunc.GetSize();i++)
			{
				f=(Cparser_func *)m_intfunc[i];
				delete f;
				m_intfunc.RemoveAt(i);
			}
		}
		m_intfunc.RemoveAll();
		m_intfunc.FreeExtra();
		m_intfunc.SetSize(m_parent->m_nout);
		for(i=0;i<m_parent->m_nout;i++)
		{
			try
			{
				f=new Cparser_func();
				f->SetName(((CGData *)m_parent->m_outputs[i])->GetName());
				m_intfunc.SetAt(i,(CObject *)f);	
			}
			catch (CMemoryException *err)
			{
				AfxMessageBox("Out of Memory internal function",MB_ICONSTOP|MB_OK);
				err->Delete();
			}
		}
		m_first=true;
	}
	for(i=0;i<m_extfunc.GetSize();i++)
		if(((Cparser_func *)m_extfunc[i])->m_name==pos)
		{
			((Cparser_func *)m_extfunc[i])->set_function(func);
			break;
		}
	m_nrout=m_parent->m_nout;
}

void CGTransition::set_intfunc(char *func, long pos)
{
	Cparser_func *f;
	long i;
	if(m_first==false)
	{
		if(m_extfunc.GetUpperBound()!=-1)
		{
			for(i=0;i<m_extfunc.GetSize();i++)
			{
				f=(Cparser_func *)m_extfunc[i];
				delete f;
				m_extfunc.RemoveAt(i);
			}
		}
		m_extfunc.RemoveAll();
		m_extfunc.FreeExtra();
		m_extfunc.SetSize(m_parent->m_nout);
		for(i=0;i<m_parent->m_nout;i++)
		{
			try
			{
				f=new Cparser_func();
				f->SetName(((CGData *)m_parent->m_outputs[i])->GetName());
				m_extfunc.SetAt(i,(CObject *)f);	
			}
			catch (CMemoryException *err)
			{
				AfxMessageBox("Out of Memory external function",MB_ICONSTOP|MB_OK);
				err->Delete();
			}
		}
		if(m_intfunc.GetUpperBound()!=-1)
		{
			for(i=0;i<m_intfunc.GetSize();i++)
			{
				f=(Cparser_func *)m_intfunc[i];
				delete f;
				m_intfunc.RemoveAt(i);
			}
		}
		m_intfunc.RemoveAll();
		m_intfunc.FreeExtra();
		m_intfunc.SetSize(m_parent->m_nout);
		for(i=0;i<m_parent->m_nout;i++)
		{
			try
			{
				f=new Cparser_func();
				f->SetName(((CGData *)m_parent->m_outputs[i])->GetName());
				m_intfunc.SetAt(i,(CObject *)f);	
			}
			catch (CMemoryException *err)
			{
				AfxMessageBox("Out of Memory internal function",MB_ICONSTOP|MB_OK);
				err->Delete();
			}
		}
		m_first=true;
	}
	for(i=0;i<m_intfunc.GetSize();i++)
	{
		if(((Cparser_func *)m_intfunc[i])->m_name==pos)
		{
			((Cparser_func *)m_intfunc[i])->set_function(func);
			break;
		}
	}
	m_nrout=m_parent->m_nout;
}

//functions define must be derivate for a more specific application
void CGTransition::proc_deltaext(CGProcessor *proc,CGData *data,long *s,CObArray *value,CObArray *value_n,long nr)
{
//
//compute the value of the external transition
//
	long i,j;
	for(i=0;i<nr;i++)
	{
		((Cparser_func *)m_extfunc[i])->reset_func();
		for(j=0;j<value_n->GetSize();j++)
		{
			if(((element *)(value_n->GetAt(j)))->m_name==((Cparser_func *)m_extfunc[i])->m_name)
			{
				((Cparser_func *)m_extfunc[i])->eval_func(&((element *)(value_n->GetAt(j)))->data[0]);
				break;
			}
		}
	}
	proc->SettL(proc->GetTime());
	proc->SettN(proc->GetTime()+m_repartition->generate());
	if(proc->m_meminput==true)
	{
		for(i=0;i<proc->m_nin;i++)
		{
			if(((CGData *)(proc->m_inputs[i]))->m_name==data->m_name)
			{
				((element *)proc->m_oinputs[i])->dim=data->GetDim();
				((element *)proc->m_oinputs[i])->source=data->GetSource();
				((element *)proc->m_oinputs[i])->sourcename=data->GetSourceName();
				memcpy(((element *)proc->m_oinputs[i])->data,data->m_value,data->GetDim());
			}
		}
	}
}

void CGTransition::proc_deltaint(CGProcessor *proc,long *s,CObArray *value,CObArray *value_n,long nr)
{
//
//compute the value of the internal transition
//
	long i,j;
	for(i=0;i<nr;i++)
	{
		((Cparser_func *)m_intfunc[i])->reset_func();
		for(j=0;j<value_n->GetSize();j++)
		{
			if(((element *)(value_n->GetAt(j)))->m_name==((Cparser_func *)m_intfunc[i])->m_name)
			{
				((Cparser_func *)m_intfunc[i])->eval_func(&((element *)(value_n->GetAt(j)))->data[0]);
				break;
			}
		}
	}
	proc->SettL(proc->GetTime());
	proc->SettN(proc->GetTime()+m_repartition->generate());
}

void CGTransition::proc_redone(CGProcessor *proc, long *s,long *sL, CObArray *value, CObArray *value_n)
{
	//redone the processor settings to previous ones
	proc->SettN(proc->GetPrevTime());
	proc->SettL(proc->GetLLTime());
	*s=*sL;
}

int CGTransition::proc_lambda(CGProcessor *proc,element *val,long port)
{
//
//output function
//
	CGData *tout;
	long N=(proc->m_outputs).GetSize();
	for(int i=0;i<N;i++)
	{
		tout=(CGData *)((proc->m_outputs).GetAt(i));
		if(tout->m_name==port)	break;
	}
	if(val==NULL)
	{
		tout->SetSource((CObject *)proc);
		tout->SetTime(proc->GetTime());
		tout->SetWTime(proc->GetTime());
		tout->Reset();
//		cout<<"3proc "<<proc->m_name<<" at "<<proc->GetTime()<<endl;cout.flush();
		if(proc->m_mtype!=0)
			tout->RecvMsg(3,proc->GetTime(),proc);
	}
	else
	{
		tout->SetSource((CObject *)proc);
		tout->SetTime(proc->GetTime());
		tout->SetWTime(proc->GetTime());
		tout->Set(val->data);
//		cout<<"2proc "<<proc->m_name<<" at "<<proc->GetTime()<<endl;cout.flush();
		if(proc->m_mtype!=0)
			tout->RecvMsg(2,proc->GetTime(),proc);
	}
	return 0;
}

void CGTransition::SetClk(double time)
{
	m_clk=time;
}

long CGTransition::GetIndexR(double val)
{
//
//get the relative index of the value in the repartition
//
	return m_repartition->RetIndex(val);
}

void CGTransition::SetRepartionT(CGRepartition *ob)
{
//
//set the repartition for translation table
//
	m_ttrans=ob;
}

long CGTransition::GetIndexT(double val)
{
//
//return the relative index of value in the translation table
//
	return m_ttrans->RetIndex(val);
}

void CGTransition::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	m_extfunc.Serialize(ar);
	m_intfunc.Serialize(ar);
	m_nrout=m_extfunc.GetSize();
	if(ar.IsStoring())
	{
		ar<<m_first;
		ar<<m_clk;
		ar<<m_repartition;
		ar<<m_seed;
		ar<<m_ememory;
		ar<<m_amemory;
//		if(m_ememory==true && m_amemory==true)
//			ar<<m_memory;
	}
	else
	{
		int temp;
		ar>>temp;
		m_first=(bool)temp;
		ar>>m_clk;
		CObject *tmp;
		ar>>tmp;
		m_repartition=(CGRepartition *)tmp;
		m_ttrans=m_repartition;
		ar>>m_seed;
		m_repartition->Set(m_seed);
		ar>>temp;
		m_ememory=(bool)temp;
		ar>>temp;
		m_amemory=(bool)temp;
/*		if(m_ememory==true && m_amemory==true)
		{
			ar>>tmp;
			m_memory=(Cparser_func_memory *)tmp;
			long i;
			for(i=0;i<m_extfunc.GetSize();i++)
				((Cparser_func *)m_extfunc[i])->assign_memory(m_memory);
			for(i=0;i<m_intfunc.GetSize();i++)
				((Cparser_func *)m_intfunc[i])->assign_memory(m_memory);

		} */
	}
}

int CGTransition::DelPort(long ind,bool type)
{
	char names[1000];
	char temp[1000];
	long i;
	Cparser_func *f;
	if(type==true) //output
	{
		_itoa(((CGData *)m_parent->m_outputs[ind])->m_name,temp,10);
		strcpy(&names[1],temp);

		names[0]='y';
		for(i=0;i<m_extfunc.GetSize();i++)
			((Cparser_func *)m_extfunc[i])->delvarfunc(names);
		for(i=0;i<m_intfunc.GetSize();i++)
			((Cparser_func *)m_intfunc[i])->delvarfunc(names);
		if(m_memory!=NULL)	m_memory->deletedata(names);

		f=(Cparser_func *)m_extfunc[ind];
		m_extfunc.RemoveAt(ind);
		delete f;
		f=(Cparser_func *)m_intfunc[ind];
		m_intfunc.RemoveAt(ind);
		delete f;
		m_extfunc.FreeExtra();
		m_intfunc.FreeExtra();
	}
	else
	{
		_itoa(((CGData *)m_parent->m_inputs[ind])->m_name,temp,10);
		strcpy(&names[1],temp);

		names[0]='x';
		for(i=0;i<m_extfunc.GetSize();i++)
			((Cparser_func *)m_extfunc[i])->delvarfunc(names);
		for(i=0;i<m_intfunc.GetSize();i++)
			((Cparser_func *)m_intfunc[i])->delvarfunc(names);
		if(m_memory!=NULL) m_memory->deletedata(names);
		if(m_parent->m_meminput==true)
		{
			names[0]='t';
			for(i=0;i<m_extfunc.GetSize();i++)
				((Cparser_func *)m_extfunc[i])->delvarfunc(names);
			for(i=0;i<m_intfunc.GetSize();i++)
				((Cparser_func *)m_intfunc[i])->delvarfunc(names);
			if(m_memory!=NULL) m_memory->deletedata(names);
		}
	}
	return 0;
}

void CGTransition::SetMemory(bool type)
{
	m_ememory=type;
}

