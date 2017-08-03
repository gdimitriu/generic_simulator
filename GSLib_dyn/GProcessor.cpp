// GProcessor.cpp: implementation of the CGProcessor class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the implementation of processor class, this class is the active
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
#include "GProcessor.h"
#include "GNetworkS.h"
#include "GInput.h"
#include "GOutput.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
IMPLEMENT_SERIAL(CGProcessor,CObject,1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGProcessor::CGProcessor()
{
	m_rtype=false;
	m_s=0;
	m_tLL=0.0;
	m_tL=0.0;
	m_tN=0.0;
	m_name=0;
	m_nin=0;
	m_nout=0;
	m_compute=NULL;
	m_time=0.0;
	m_extern=false;
	m_internal=false;
	m_CLKP=0.0;
	m_disableq=false;
	m_time=-1.0;
	m_type=0;
	m_parent_del=NULL;
	m_mtype=0;
	m_ltype=0;
	m_first=false;
	m_firsti=false;
	m_first2=true;
	m_runs=false;
	m_delay=true;
	m_memory=true;
	m_meminput=true;
	m_ritype=true;
	m_reinit=true;
	m_general=true;
	m_ignore=false;
	m_status=-1; //-1=not initialized,0=initialized, 1=internal, 2=external, 3=external-internal
	m_out=true; //has output permision
	m_realtime=0.0;
	m_iportpos=0;
	m_oportpos=0;
}

CGProcessor::CGProcessor(CObject *parent,long val,CGTransition *generator,bool type)
{
	m_parent=parent;
	m_rtype=type;
	m_s=0;
	m_tLL=0.0;
	m_tL=0.0;
	m_tN=0.0;
	m_name=val;
	m_nin=0;
	m_nout=0;
	m_compute=generator;
	if(m_compute!=NULL) m_compute->SetParent(this);
	m_time=0.0;
	m_extern=false;
	m_internal=false;
	m_CLKP=0.0;
	m_disableq=false;
	m_time=-1.0;
	m_type=0;
	m_parent_del=NULL;
	m_mtype=0;
	m_ltype=0;
	m_first=false;
	m_firsti=false;
	m_first2=true;
	m_runs=false;
	m_delay=true;
	m_memory=true;
	m_meminput=true;
	m_ritype=true;
	m_reinit=true;
	m_general=true;
	m_ignore=false;
	m_status=-1; //-1=not initialized,0=initialized, 1=internal, 2=external, 3=external-internal
	m_out=true; //has output permision
	m_realtime=0.0;
	m_iportpos=0;
	m_oportpos=0;
}

CGProcessor * CGProcessor::copy(CObject *parent, long val)
{
	//create a brother of this processor
	CFile f;
	char buf[512];
	CArchive *ar;
	CString fname("testp.dat");
	char temp[100];
	srand(val);
	sprintf(temp,"%ld",rand());
	fname.Insert(5,temp);
	f.Open( fname, CFile::modeCreate | CFile::modeWrite );
	ar=new CArchive(&f, CArchive::store, 512, buf );
	*ar<<this;
	ar->Close();
	f.Close();
	delete ar;
	CObject *tmp;
	f.Open( fname,CFile::modeRead );
	ar=new CArchive(&f, CArchive::load, 512, buf );
	*ar>>tmp;
	ar->Close();
	f.Close();
	((CGProcessor *)tmp)->SetParent(parent);
	((CGProcessor *)tmp)->SetName(val);
	TRY
	{
		CFile::Remove(fname);
	}
	CATCH( CFileException, e )
	{
		#ifdef _DEBUG
			afxDump << "File " << fname << " cannot be removed\n";
		#endif
	}
	END_CATCH
	return (CGProcessor *)tmp;
}

CGProcessor * CGProcessor::copy(CObject *parent)
{
	//create a clone processor
	CFile f;
	char buf[512];
	CArchive *ar;
	CString fname("testp.dat");
	char temp[100];
	srand(m_name);
	sprintf(temp,"%ld",rand());
	fname.Insert(5,temp);
	f.Open( fname, CFile::modeCreate | CFile::modeWrite );
	ar=new CArchive(&f, CArchive::store, 512, buf );
	*ar<<this;
	ar->Close();
	f.Close();
	delete ar;
	CObject *tmp;
	f.Open( fname,CFile::modeRead );
	CArchive ar1(&f, CArchive::load, 512, buf );
	ar1>>tmp;
	ar1.Close();
	f.Close();
	((CGProcessor *)tmp)->SetParent(parent);
	if(m_time!=-1.0) ((CGProcessor *)tmp)->receive0(m_time);
	TRY
	{
		CFile::Remove(fname);
	}
	CATCH( CFileException, e )
	{
		#ifdef _DEBUG
			afxDump << "File " << fname << " cannot be removed\n";
		#endif
	}
	END_CATCH
	return (CGProcessor *)tmp;
}

CGProcessor::~CGProcessor()
{
	int i,nr;
	nr=m_inputs.GetSize();
	for(i=0;i<nr;i++)
	{
		CGInput *tin;
		tin=(CGInput *)(m_inputs.GetAt(i));
		delete tin;
	}
	m_inputs.RemoveAll();
	nr=m_outputs.GetSize();
	for(i=0;i<nr;i++)
	{
		CGOutput *tout;
		tout=(CGOutput *)(m_outputs.GetAt(i));
		delete tout;
	}
	m_outputs.RemoveAll();
	if(m_compute!=NULL)  delete m_compute;
	CGData *data;
	while(m_queue.empty()==false)
	{
		data=(CGData *)(m_queue.front());
		delete data;
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
		m_value.RemoveAll();
		m_value.FreeExtra();
	}
	if(m_value_n.GetUpperBound()!=-1)
	{
		for(i=0;i<m_value_n.GetSize();i++)
		{
			el=(element *)m_value_n[i];
			m_value_n.RemoveAt(i);
			delete el;
		}
		m_value.RemoveAll();
		m_value_n.FreeExtra();
	}
	if(m_oinputs.GetUpperBound()!=-1)
	{
		for(i=0;i<m_oinputs.GetSize();i++)
		{
			el=(element *)m_oinputs[i];
			m_oinputs.RemoveAt(i);
			delete el;
		}
		m_oinputs.RemoveAll();
		m_oinputs.FreeExtra();
	}
}

int CGProcessor::AddPort(CObject *port, bool type)
{
//
//add a port to the processor
//
	if(type==true)
	{
		try
		{
			((CGInput *)port)->SetParent((CObject *)this,1);
			m_inputs.Add(port);
		}
		catch (CMemoryException *err)
		{
			AfxMessageBox("Out of Memory input port",MB_ICONSTOP|MB_OK);
			err->Delete();
			return -1;
		}
		m_nin++;
		if(m_runs==true) RInitP((CGData *)port);
	}
	else
	{
		try
		{
			((CGOutput *)port)->SetParent((CObject *)this,1);
			m_outputs.Add(port);
		}
		catch (CMemoryException *err)
		{
			AfxMessageBox("Out of Memory output port",MB_ICONSTOP|MB_OK);
			err->Delete();
			return -1;
		}
		m_nout++;
		if(m_runs==true) RInitP((CGData *)port);
	}
	return 0;
}

int CGProcessor::RInitP(CGData *port)
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
				if(m_compute!=NULL) m_compute->assign_memory(this,i,true);
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

CObject * CGProcessor::GetPort(long port,int *type)
{
//
//return the port given by it's name
//return type=1 if it is an input port and type=2 if it is an output port
//return type=0 if the port isn't here and also return NULL
//
	long i;
	long N;
	N=m_inputs.GetSize();
	for(i=0;i<N;i++)
		if(((CGInput *)m_inputs.GetAt(i))->m_name==port)
		{
			*type=1;
			return m_inputs.GetAt(i);
		}
	N=m_outputs.GetSize();
	for(i=0;i<N;i++)
		if(((CGOutput *)m_outputs.GetAt(i))->m_name==port)
		{
			*type=2;
			return m_outputs.GetAt(i);
		}
	*type=0;
	return NULL;
}

int CGProcessor::DelPort(CGData *dead)
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
				m_outputs.RemoveAt(i);
				if(m_value.GetSize()!=0)
					for(j=0;j<m_value.GetSize();j++)
					{
						if(((element *)m_value[j])->m_name==dead->m_name)
						{
							el=(element *)m_value[j];
							m_value.RemoveAt(j);
							delete el;
							break;
						}
					}
				if(m_delay==true)
				{
					if(m_value_n.GetSize()!=0)
						for(j=0;j<m_value.GetSize();j++)
						{
							if(((element *)m_value_n[j])->m_name==dead->m_name)
							{
								el=(element *)m_value_n[j];
								m_value_n.RemoveAt(j);
								delete el;
								break;
							}
						}
				}
				m_value.FreeExtra();
				m_value_n.FreeExtra();
				m_outputs.FreeExtra();
				m_nout--;
				if(m_compute!=NULL)
					m_compute->DelPort(dead->m_name,true);
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
				m_inputs.RemoveAt(i);
				m_inputs.FreeExtra();
				m_oinputs.FreeExtra();
				m_nin--;
				if(m_compute!=NULL)
					m_compute->DelPort(dead->m_name,false);
				delete dead;
				return 0;
			}
		if(i==m_inputs.GetSize()) return -2;
	}
	return -3;
}	

int CGProcessor::receivemsg(int type, double time, CObject *in)
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
	if(type!=3)
		m_runs=true;
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

int CGProcessor::receive0(double time)
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
	m_nout=m_outputs.GetSize();
	element *el;
	while(m_queue.empty()==false)
	{
		data=(CGData *)(m_queue.front());
		delete data;
	}
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
			if(m_compute!=NULL)
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

int CGProcessor::InternalN(double time)
{
	long i,j;
	CGData *data;
	if(m_delay==true)
	{
		for(i=0;i<m_nout;i++)
		{
			for(j=0;j<((element *)m_value_n[i])->dim;j++)
				((element *)m_value[i])->data[j]=((element *)m_value_n[i])->data[j];
			((element *)m_value[i])->source=((element *)m_value_n[i])->source;
			((element *)m_value[i])->sourcename=((element *)m_value_n[i])->sourcename;
		}
		OutputN();
	}
	if(m_queue.empty()==true)
	{
		m_internal=true;
		m_extern=false;
		m_status=1;
		if(m_delay==true)
			m_compute->proc_deltaint(this,&m_s,&m_value,&m_value_n,m_nout);
		else
		{
			m_compute->proc_deltaint(this,&m_s,&m_value,&m_value,m_nout);
			OutputN();
		}
	}
	else
	{
//		cout<<"get from queue in proc="<<m_name<<" at "<<time<<endl;cout.flush();
		m_extern=true;
		m_internal=false;
		m_status=2;
		data=(CGData *)(m_queue.front());
		if(m_delay==true)
			m_compute->proc_deltaext(this,data,&m_s,&m_value,&m_value_n,m_nout);
		else
		{
			m_compute->proc_deltaext(this,data,&m_s,&m_value,&m_value,m_nout);
			OutputN();
		}
		delete data;
	}
	return 4;
}

int CGProcessor::receive1(double time)
{
//
//we have internal transition
//
	bool m_run;
	long i,j;
	if(!(m_internal==false && m_extern==false))
		m_run=true;
	else
	{
		if(m_first==true) m_run=true;
		else m_run=false;
	}
	if(((CGNetworkS *)m_parent)->GetCoordinator()!=NULL)
		if(((CGNetworkS *)m_parent)->GetWork(this)==true)
			m_run=false;
	((CGNetworkS *)m_parent)->ResetProc(this);
	if(m_internal==true && m_extern==true)
	{
		if(fabs(time-m_realtime)<precision && m_run==true)
			InternalN(time);
		else
		{
			if(m_delay==true)
			{
				for(i=0;i<m_nout;i++)
				{
					for(j=0;j<((element *)m_value_n[i])->dim;j++)
						((element *)m_value[i])->data[j]=((element *)m_value_n[i])->data[j];
					((element *)m_value[i])->source=((element *)m_value_n[i])->source;
					((element *)m_value[i])->sourcename=((element *)m_value_n[i])->sourcename;
				}
				OutputN();
			}
			m_internal=true;
			m_extern=false;
			m_status=1;
			if(m_delay==true)
				m_compute->proc_deltaint(this,&m_s,&m_value,&m_value_n,m_nout);
			else
			{
				m_compute->proc_deltaint(this,&m_s,&m_value,&m_value,m_nout);
				OutputN();
			}
		}
	}
	else
	{
		if((fabs(time-m_tN)<precision || fabs(m_tN-time)<m_CLKP || fabs(m_tN)<precision) && m_run==true)
			InternalN(time);
		else if(time<m_tN)
		{
			if(m_rtype==true)
			{
				for(long i=0;i<m_outputs.GetSize();i++)
					m_compute->proc_lambda(this,NULL,((CGOutput *)m_outputs.GetAt(i))->m_name);
			}
		}
	}
	return 4;
}

int CGProcessor::restore1(double time)
{
	long i,j;
	if(m_firsti==true && m_ltype==1 && m_delay==true && m_extern==false)
	{
//		cout<<"special "<<time<<" vs "<<m_tL<<" "<<m_sL<<endl;cout.flush();
		if(fabs(m_tL-time)<precision || fabs(m_tL-time)<m_CLKP)
		{
			m_tN=m_tL;
			m_tL=m_tLL;
			m_s=m_sL;
			m_extern=true;
			m_internal=false;
			for(i=0;i<m_nout;i++)
			{
				for(j=0;j<((element *)m_value_n[i])->dim;j++)
					((element *)m_value_n[i])->data[j]=((element *)m_value[i])->data[j];
				((element *)m_value_n[i])->source=((element *)m_value[i])->source;
				((element *)m_value_n[i])->sourcename=((element *)m_value[i])->sourcename;
			}
		}
	}
	else if(m_firsti==true && m_ltype==1 && m_delay==false && m_extern==false)
	{
		if(fabs(m_tL-time)<precision || fabs(m_tL-time)<m_CLKP)
		{
			m_extern=true;
			m_internal=false;
			m_compute->proc_redone(this,&m_s,&m_sL,&m_value,&m_value);
		}
	}
	return 0;
}

int CGProcessor::ExternN(CGData *input, double time)
{
	long i,j;
	long dim;
	double *value;
	CGInput *in;
	in=(CGInput *)input;
	value=in->Get(&dim);
	CGData *data;
	if(m_queue.empty()==false)
	{
		if(m_delay==true)
		{
			for(i=0;i<m_nout;i++)
			{
				for(j=0;j<((element *)m_value_n[i])->dim;j++)
					((element *)m_value[i])->data[j]=((element *)m_value_n[i])->data[j];
				((element *)m_value[i])->source=((element *)m_value_n[i])->source;
				((element *)m_value[i])->sourcename=((element *)m_value_n[i])->sourcename;
			}
			OutputS();
		}
		if(m_first2==true) m_first2=false;
		data=new CGData(in->m_name);
		data->SetDim(dim);
		data->Set(value);
		data->SetTime(in->GetTime());
		data->SetSource(in->GetSource());
		data->SetSourceName(in->GetSourceName());
		m_queue.add((CObject *)data);
		data=(CGData *)(m_queue.front());
		if(data==NULL) cout<<"Error!\n";cout.flush();
		m_extern=true;
		m_internal=false;
		if(m_delay==true)
			m_compute->proc_deltaext(this,data,&m_s,&m_value,&m_value_n,m_nout);
		else
		{
			m_compute->proc_deltaext(this,data,&m_s,&m_value,&m_value,m_nout);
			OutputN();
		}
		delete data;
	}
	else
	{
		m_extern=true;
		m_internal=false;
		if(m_delay==true)
			{
			for(i=0;i<m_nout;i++)
			{
				for(j=0;j<((element *)m_value_n[i])->dim;j++)
					((element *)m_value[i])->data[j]=((element *)m_value_n[i])->data[j];
				((element *)m_value[i])->source=((element *)m_value_n[i])->source;
				((element *)m_value[i])->sourcename=((element *)m_value_n[i])->sourcename;
			}
			OutputS();
			m_compute->proc_deltaext(this,in,&m_s,&m_value,&m_value_n,m_nout);
		}
		else
		{
			m_compute->proc_deltaext(this,in,&m_s,&m_value,&m_value,m_nout);
			OutputN();
		}
	}
	return 4;
}
int CGProcessor::ExternS(CGData *input, double time)
{
	long i,j;
	long dim;
	double *value;
	CGInput *in;
	in=(CGInput *)input;
	value=in->Get(&dim);
	CGData *data;
	if(m_extern==true && m_internal==true)
		((CGNetworkS *)m_parent)->ResetProc(this);
	if(m_disableq==false)
	{
//		cout<<"put in queue in proc="<<m_name<<" at "<<time<<endl;cout.flush();
		data=new CGData(in->m_name);
		data->SetDim(dim);
		data->Set(value);
		data->SetTime(in->GetTime());
		data->SetSource(in->GetSource());
		data->SetSourceName(in->GetSourceName());
		m_queue.add((CObject *)data);
		if(m_rtype==true)
		{
			m_nout=m_outputs.GetSize();
			for(i=0;i<m_nout;i++)
				m_compute->proc_lambda(this,NULL,((CGOutput *)m_outputs.GetAt(i))->m_name);
		}
	}
	else
	{
		if(m_ignore==false)
		{
			m_extern=true;
			m_internal=false;
			if(m_delay==true)
			{
				m_compute->proc_deltaint(this,&m_s,&m_value,&m_value_n,m_nout);
				for(i=0;i<m_nout;i++)
				{
					for(j=0;j<((element *)m_value_n[i])->dim;j++)
						((element *)m_value[i])->data[j]=((element *)m_value_n[i])->data[j];
					((element *)m_value[i])->source=((element *)m_value_n[i])->source;
					((element *)m_value[i])->sourcename=((element *)m_value_n[i])->sourcename;
				}
				OutputS();
				m_compute->proc_deltaext(this,in,&m_s,&m_value,&m_value_n,m_nout);
			}
			else
			{
				m_compute->proc_deltaint(this,&m_s,&m_value,&m_value,m_nout);
				OutputN(); //???
				m_compute->proc_deltaext(this,in,&m_s,&m_value,&m_value,m_nout);
				OutputN();
			}
		}
	}
	return 4;
}
int CGProcessor::receive2(double time, CGData *input)
{
//
//we have external transition
//
	((CGNetworkS *)m_parent)->SetProc(this);
	restore1(time);
	if(input!=NULL)
	{
		if(m_extern==true && m_internal==true)
		{
			if(fabs(time-m_realtime)<precision)
				return ExternN(input,time);
			else
				return ExternS(input,time);
		}
		else 
		{
			if(fabs(time-m_tN)<precision || (fabs(time-m_tN)<m_CLKP && m_extern==true) || (m_internal==false && m_extern==false))
				return ExternN(input,time);
			else
				return ExternS(input,time);
		}
	}
	else return -2;
	return 4;
}

int CGProcessor::receive3(double time)
{
//
//we need output
//
	m_nout=m_outputs.GetSize();
	for(long i=0;i<m_nout;i++)
		if(m_delay==true)
			m_compute->proc_lambda(this,(element *)m_value_n[i],((CGOutput *)m_outputs.GetAt(i))->m_name);
		else
			m_compute->proc_lambda(this,(element *)m_value[i],((CGOutput *)m_outputs.GetAt(i))->m_name);
	return 4;
}


long CGProcessor::GetName()
{
//
//return the name of the processor
//
	return m_name;
}

CObject *CGProcessor::GetParent(void)
{
//
//return the parent pointer
//
	return m_parent;
}

void CGProcessor::SetParent(CObject *parent)
{
//
//set the parent of the processor
//
	m_parent=parent;
}

double CGProcessor::sigma(void)
{
//
//return the done time
//
	return m_tN;
}

double CGProcessor::sigma(long *dim)
{
//
//return the done time and dimension of queue
//
	*dim=m_queue.GetDim();
	return m_tN;
}

void CGProcessor::SetClockPrecision(double val)
{
	m_CLKP=val/2;
	if(m_compute!=NULL)
		m_compute->SetClk(val);
}



void CGProcessor::DisableQ()
{
	//disable the queue
	m_disableq=true;
}

void CGProcessor::EnableQ()
{
	//enable the queue
	m_disableq=false;
}

void CGProcessor::SettL(double val)
{
	//set the last event time
	m_tLL=m_tL;
	m_tL=val;
}

void CGProcessor::SettN(double val)
{
	//set the new event time
	m_tN=val;
}

double CGProcessor::GetTime()
{
//
//return the curent time
//
	return m_time;
}


double CGProcessor::GetPrevTime()
{
//
//return the previous time
//
	return m_tL;
}


double CGProcessor::GetLLTime()
{
//
// return the last previous time
//
	return m_tLL;
}

void CGProcessor::IsDelayed(bool type)
{
	m_delay=type;
}

void CGProcessor::set_extfunc(char *func, long pos)
{
	m_compute->set_extfunc(func,pos);
}

void CGProcessor::set_intfunc(char *func, long pos)
{
	m_compute->set_intfunc(func,pos);
}

void CGProcessor::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	long i;
	int temp;
	m_inputs.Serialize(ar);
	m_outputs.Serialize(ar);
	m_oinputs.Serialize(ar);
	m_value.Serialize(ar);
	m_value_n.Serialize(ar);
	m_queue.Serialize(ar);
	if(ar.IsStoring())
	{
		//data
		temp=(int)m_delay;
		ar<<temp;
		temp=(int)m_disableq;
		ar<<temp;
		temp=(int)m_extern;
		ar<<temp;
		temp=(int)m_first;
		ar<<temp;
		temp=(int)m_first2;
		ar<<temp;
		temp=m_first_alloc;
		ar<<temp;
		temp=(int)m_internal;
		ar<<temp;
		temp=(int)m_meminput;
		ar<<temp;
		temp=(int)m_memory;
		ar<<temp;
		temp=(int)m_ritype;
		ar<<temp;
		temp=(int)m_rtype;
		ar<<temp;
		temp=(int)m_runs;
		ar<<temp;
		temp=(int)m_reinit;
		ar<<temp;
		temp=(int)m_general;
		ar<<temp;
		temp=(int)m_ignore;
		ar<<temp;
		temp=m_firsti;
		ar<<temp;
		temp=m_out;
		ar<<temp;

		ar<<m_oportpos;
		ar<<m_iportpos;
		ar<<m_CLKP;
		ar<<m_e;
		ar<<m_mtype;
		ar<<m_ltype;
		ar<<m_type;
		ar<<m_name;
		ar<<m_nin;
		ar<<m_nout;
		ar<<m_s;
		ar<<m_sL;
		ar<<m_time;
		ar<<m_tL;
		ar<<m_tLL;
		ar<<m_tN;
		ar<<m_status;
		ar<<m_realtime;
		//objects
		ar<<m_compute;
	}
	else
	{
		for(i=0;i<m_inputs.GetSize();i++)
			((CGData *)m_inputs.GetAt(i))->SetParent(this,1);
		for(i=0;i<m_outputs.GetSize();i++)
			((CGData *)m_outputs.GetAt(i))->SetParent(this,1);
		//data
		ar>>temp;
		m_delay=(bool)temp;
		ar>>temp;
		m_disableq=(bool)temp;
		ar>>temp;
		m_extern=(bool)temp;
		ar>>temp;
		m_first=(bool)temp;
		ar>>temp;
		m_first2=(bool)temp;
		ar>>temp;
		m_first_alloc=(bool)temp;
		ar>>temp;
		m_internal=(bool)temp;
		ar>>temp;
		m_meminput=(bool)temp;
		ar>>temp;
		m_memory=(bool)temp;
		ar>>temp;
		m_ritype=(bool)temp;
		ar>>temp;
		m_rtype=(bool)temp;
		ar>>temp;
		m_runs=(bool)temp;
		ar>>temp;
		m_reinit=(bool)temp;
		ar>>temp;
		m_general=(bool)temp;
		ar>>temp;
		m_ignore=(bool)temp;
		ar>>temp;
		m_firsti=(bool)temp;
		ar>>temp;
		m_out=(bool)temp;

		ar>>m_oportpos;
		ar>>m_iportpos;
		ar>>m_CLKP;
		ar>>m_e;
		ar>>m_mtype;
		ar>>m_ltype;
		ar>>m_type;
		ar>>m_name;
		ar>>m_nin;
		ar>>m_nout;
		ar>>m_s;
		ar>>m_sL;
		ar>>m_time;
		ar>>m_tL;
		ar>>m_tLL;
		ar>>m_tN;
		ar>>m_status;
		ar>>m_realtime;
		//objects;
		CObject *otmp;
		ar>>otmp;
		m_compute=(CGTransition *)otmp;
		m_compute->SetParent(this);
		if(m_runs==true)
			m_compute->assign_memory(this);
	}
}

void CGProcessor::SetName(long val)
{
	m_name=val;	
}

void CGProcessor::SetType(int type)
{
	m_type=type;
}

int CGProcessor::kill()
{
	CGNetworkS *net;
	long i;
	long loop;
	loop=m_inputs.GetSize();
	for(i=0;i<loop;i++)
		DelPort((CGData *)m_inputs[0]);
	loop=m_outputs.GetSize();
	for(i=0;i<loop;i++)
		DelPort((CGData *)m_outputs[0]);
	if(m_parent!=NULL) //self decided
	{
		net=(CGNetworkS *)m_parent;
		m_parent=NULL;
		net->DelProc(this);
		return 0;
	}
	return 1;
}

void CGProcessor::SetDelParent(CObject *parent)
{
	m_parent_del=parent;
}

void CGProcessor::SetRType(bool type)
{
	//it has reset for data
	m_rtype=type;
}

void CGProcessor::SetFirst2(bool type)
{
	m_first2=type;
}

void CGProcessor::SetMemInput(bool type)
{
	//it has memory for last input
	m_meminput=type;
}

void CGProcessor::SetRIType(bool type)
{
	m_ritype=type;
}

void CGProcessor::SetReinit(bool type)
{
	m_reinit=type;
}

void CGProcessor::SetGeneral(bool type)
{
	//set the general type for processor so it has the CGTransition with function parser
	m_general=type;
}

void CGProcessor::other_init()
{
	return;
}

int CGProcessor::GetMType()
{
	return m_mtype;
}

void CGProcessor::SetIgnore(bool type)
{
	//ignore other inputs of 2 is is not correct in time
	m_ignore=type;
}

void CGProcessor::SetFirst(bool type)
{
	//set the first which can be executed is internal transition
	m_first=type;
}

void CGProcessor::SetFirstI(bool type)
{
	// first message 1 but real is message 2
	//first is message 1 but in the same time message 2 came and calcel the 1
	m_firsti=type;
/*
	old functionality
	if(m_delay==false && m_first==false)
		AfxMessageBox("It must have delay memory and first execution is internal",MB_OK);
*/
}

CGCoordinator * CGProcessor::GetCoordinator()
{
	return ((CGNetworkS *)m_parent)->GetCoordinator();
}

void CGProcessor::DisableCoord()
{
	//disable the threaded coordinator
	long i;
	for(i=0;i<m_inputs.GetSize();i++)
		((CGData *)m_inputs[i])->DisableCoord();
	for(i=0;i<m_outputs.GetSize();i++)
		((CGData *)m_outputs[i])->DisableCoord();
}

void CGProcessor::GetStatus(bool *external, bool *internal)
{
	*external=m_extern;
	*internal=m_internal;
}

void CGProcessor::SetStatus(bool external, bool internal)
{
	m_extern=external;
	m_internal=internal;
}

int CGProcessor::GetStatus()
{
	return m_status;
}

void CGProcessor::SetStatus(int status)
{
	m_status=status;
}

void CGProcessor::EnableOut(bool state)
{
	m_out=state;
}

void CGProcessor::OutputN()
{
	long i;
	if(m_out==true)
	{
		for(i=0;i<m_nout;i++)
			m_compute->proc_lambda(this,(element *)m_value[i],((CGOutput *)m_outputs.GetAt(i))->m_name);
	}
	else
	{
		m_OutputList.sort();
		while(m_OutputList.empty()==false)
		{
			for(i=0;i<m_nout;i++)
				if(m_OutputList.front()==((CGOutput *)m_outputs.GetAt(i))->m_name)
				{
					m_compute->proc_lambda(this,(element *)m_value[i],((CGOutput *)m_outputs.GetAt(i))->m_name);
					m_OutputList.pop_front();
				}
		}
	}
		
}

void CGProcessor::OutputS()
{
	long i;
	if(m_first2==false)
		OutputN();
	else
		for(i=0;i<m_nout;i++)
			m_compute->proc_lambda(this,NULL,((CGOutput *)m_outputs.GetAt(i))->m_name);
	m_first2=false;
}
					

void CGProcessor::AddOutNow(long val)
{
	m_OutputList.push_back(val);
}

void CGProcessor::SetRealTime(double time)
{
	m_realtime=time;
}


int CGProcessor::SetFilePort(long port, CString *name)
{
	CGOutput *out;
	CGInput *in;
	long i;
	for(i=0;i<m_inputs.GetSize();i++)
	{
		in=(CGInput *)m_inputs.GetAt(i);
		if(in->GetName()==port)
		{
			in->SetFName(name);
			return 1;
		}
	}
	for(i=0;i<m_outputs.GetSize();i++)
	{
		out=(CGOutput *)m_outputs.GetAt(i);
		if(out->GetName()==port)
		{
			out->SetFName(name);
			return 2;
		}
	}
	return -1;
}

int CGProcessor::SetDimPort(long port, long dim)
{
	CGOutput *out;
	CGInput *in;
	long i;
	for(i=0;i<m_inputs.GetSize();i++)
	{
		in=(CGInput *)m_inputs.GetAt(i);
		if(in->GetName()==port)
		{
			in->SetDim(dim);
			return 1;
		}
	}
	for(i=0;i<m_outputs.GetSize();i++)
	{
		out=(CGOutput *)m_outputs.GetAt(i);
		if(out->GetName()==port)
		{
			out->SetDim(dim);
			return 2;
		}
	}
	return -1;
}

double CGProcessor::GetNextTime()
{
	return m_tN;
}

int CGProcessor::Add(CObject *ob)
{
	if(ob->IsKindOf(RUNTIME_CLASS(CGInput))!=0)
	{
		try
		{
			((CGInput *)ob)->SetParent((CObject *)this,1);
			m_inputs.Add(ob);
		}
		catch (CMemoryException *err)
		{
			AfxMessageBox("Out of Memory input port",MB_ICONSTOP|MB_OK);
			err->Delete();
			return -1;
		}
		m_nin++;
		if(m_runs==true) RInitP((CGData *)ob);
	}
	else if(ob->IsKindOf(RUNTIME_CLASS(CGOutput))!=0)
	{
		try
		{
			((CGOutput *)ob)->SetParent((CObject *)this,1);
			m_outputs.Add(ob);
		}
		catch (CMemoryException *err)
		{
			AfxMessageBox("Out of Memory output port",MB_ICONSTOP|MB_OK);
			err->Delete();
			return -1;
		}
		m_nout++;
		if(m_runs==true) RInitP((CGData *)ob);
	}
	return 0;
}

void CGProcessor::ResetNIPort()
{
	m_iportpos=0;
}

void CGProcessor::ResetNOPort()
{
	m_oportpos=0;
}

CGData * CGProcessor::GetNIPort(CString &data)
{
	CGData *in;
	if(m_iportpos<m_nin)
	{
		in=(CGData *)m_inputs[m_iportpos];
		data.Empty();
		data.Format("%ld",in->GetName());
		m_iportpos++;
		return in;
	}
	return NULL;
}

CGData * CGProcessor::GetNOPort(CString &data)
{
	CGData *out;
	if(m_oportpos<m_nout)
	{
		out=(CGData *)m_outputs[m_oportpos];
		data.Empty();
		data.Format("%ld",out->GetName());
		m_oportpos++;
		return out;
	}
	return NULL;
}

long CGProcessor::GetInputNrPorts()
{
	return m_nin;
}

long CGProcessor::GetOutputNrPorts()
{
	return m_nout;
}
