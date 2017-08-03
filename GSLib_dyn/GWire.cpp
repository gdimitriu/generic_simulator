// GWire.cpp: implementation of the CGWire class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the implementation of wire class. This class makes the connection
	between diferent inputs and outputs ports.
	
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
#include "GWire.h"
#include "GInput.h"
#include "GOutput.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
IMPLEMENT_SERIAL(CGWire,CObject,1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGWire::CGWire()
{

	m_type=0;
	m_parent=NULL;
	m_nports=0;
	m_parent_wire=NULL;
	m_type_client=false;
	m_type_wire=false;
	m_type_queue=false;
	m_get=0;
}

CGWire::CGWire(CObject *ob,int type,CGNetworkS *parent)
{
	m_type=type;
	m_parent=(CGData *)ob;
	m_nports=0;
	m_parent_wire=parent;
	if(m_parent->m_parent->IsKindOf(RUNTIME_CLASS(CGNetworkS))!=0)
	{
		if(((CGNetworkS *)(m_parent->m_parent))==parent)
			m_parent->SetParentW((CObject *)this);
		else m_parent->SetParentEW((CObject *)this);
	}
	else m_parent->SetParentW((CObject *)this);
	m_type_wire=m_parent_wire->GetTypeWire();
	m_type_client=m_parent_wire->GetInType();
	m_type_queue=m_parent_wire->GetTypeQueue();
	m_get=0;
}

CGWire::~CGWire()
{
	m_ports.RemoveAll();
	m_selected.RemoveAll();
}

int CGWire::Add(CObject *ob)
{
//
//add a port to the wire
//
	try
	{
		m_ports.Add(ob);
		m_nports++;
	}
	catch (CMemoryException *err)
	{
		AfxMessageBox("Out of object memory at wire",MB_ICONSTOP|MB_OK);
		err->Delete();
		return -1;
	}
	if(((CGData *)ob)->m_parent->IsKindOf(RUNTIME_CLASS(CGNetworkS))!=0)
	{
		if((CGNetworkS *)(((CGData *)ob)->m_parent)==(CGNetworkS *)m_parent_wire)
			((CGData *)ob)->SetParentW((CObject *)this);
		else
		{
			((CGData *)ob)->SetParentEW((CObject *)this);
			((CGData *)ob)->m_dual=true;
		}
	}
	else ((CGData *)ob)->SetParentW((CObject *)this);
	return 0;
}

double CGWire::receivemsg(int type, double time,CGData *input)
{
/*
	type is the receiving message: 0=start;1=int;2=ext;3=out;4=done;
	time is the time of the simulation
	input is the pointer to the input or output portport
	it's return is 4=done or -1=error
*/
	long i;
	m_nports=m_ports.GetSize();
	CGData *in;
	long dim;
	double *valuesp;
	m_time=time;
/*
	if(m_type==1 && type!=3 && type!=0) //is output
	{
		if(m_parent_wire->GetWork(this)==true) return time;
		else m_parent_wire->SetWork(this);
	}
*/
	if(input!=NULL)
	{
		if(input->IsKind()==1 || (input->IsKind()==0 && (input->m_parent)->IsKindOf(RUNTIME_CLASS(CGNetworkS))!=0))
		{
			for(i=0;i<m_nports;i++)
			{
				in=(CGData *)(m_ports.GetAt(i));
				if(in!=input)
					in->SetWTime(time);
			}
			if(m_parent!=input)	m_parent->SetWTime(time);
		}
	}
	else
	{
		for(i=0;i<m_nports;i++)
		{
			in=(CGData *)(m_ports.GetAt(i));
			if(in!=input)
				in->SetWTime(time);
		}
		if(m_parent!=input)	m_parent->SetWTime(time);
	}
	//distribute data and time for init
	if(type==0)
	{
		for(i=0;i<m_nports;i++)
		{
			in=(CGData *)m_ports[i];
			if(in!=input)
			{
				in->Reset();
				in->SetTime(time);
			}
		}
		if(m_parent!=input)
		{
			m_parent->Reset();
			m_parent->SetTime(time);
		}
	}
	//send the data thru the wire
	if(input==NULL) return -1;
	dim=input->GetDim();
	valuesp=input->Get(&dim);
	if(m_parent!=input)
	{
		//m_parent->SetWTime(time);
		m_parent->SetTime(input->GetTime());//!
		m_parent->SetSource(input->GetSource());
		m_parent->SetSourceName(input->GetSourceName());
		m_parent->Set(valuesp);
	}
	for(i=0;i<m_nports;i++)
	{
		in=(CGData *)m_ports[i];
		if(in!=input)
		{
			//in->SetWTime(time);
			in->SetTime(input->GetTime());//!
			in->SetSource(input->GetSource());
			in->SetSourceName(input->GetSourceName());
			in->Set(valuesp);
		}
	}
	if(type==2)
	{
		input->ResetG(); //new !!!!
		//send the message to the modified port
		if(m_parent!=input)
		{
//			m_parent->RecvMsg(2,time,(CObject *)this);
			m_parent->receivemsg(2,time,(CObject *)this);
		}
		for(i=0;i<m_nports;i++)
		{
			in=(CGData *)m_ports[i];
			if(in!=input)
			{
//				in->RecvMsg(2,time,(CObject *)this);
				in->receivemsg(2,time,(CObject *)this);
			}
		}
	}
	if(type==3)
	{
		//send the message to all ports
		if(m_parent!=input)
//			m_parent->RecvMsg(3,time,(CObject *)this);
			m_parent->receivemsg(3,time,(CObject *)this);
		for(i=0;i<m_nports;i++)
		{
			in=(CGData *)m_ports[i];
			if(in!=input)
//				in->RecvMsg(3,time,(CObject *)this);
				in->receivemsg(3,time,(CObject *)this);
		}
	}
	return 1;
}

CGData * CGWire::select(void)
{
//
//select the device with the closest done time
//
	m_nports=m_ports.GetSize();
	N=m_selected.GetSize();
	if(N==m_nports && m_type_client==true) return NULL;
	if(N==0)
	{
		inparc=(CGData *)(m_ports.GetAt(0));
		if(inparc->m_type==1)
		{
			proc=NULL;
			proc=(CGProcessor *)(inparc->GetParent());
			if(proc!=NULL)
			{
				if(m_type_queue==false) m_time=proc->sigma();
				else m_time=proc->sigma(&dim_queue);
				in=inparc;
			}
		}
		else
		{
			if(inparc->m_type==2)
			{
				net=NULL;
				net=(CGNetworkS *)(inparc->GetParent());
				if(net!=NULL)
				{
					in=inparc;
					if(m_type_queue==false) m_time=net->sigma(in);
					else m_time=net->sigma(in,&dim_queue);
				}
			}
		}
		start=1;
	}
	else start=0;
	if(m_type_client==false)
	{
		return select_clientf();		
	}
	else
	{
		return select_clientt();	
	}
	return in;
}

double CGWire::sigma()
{
//
//return the closest done time
//
	CGData *inparc;
	CGNetworkS *net;
	CGProcessor *proc;
	double time;
	inparc=select();
	if(inparc->m_type==1)
	{
		proc=NULL;
		proc=(CGProcessor *)(inparc->GetParent());
		if(proc!=NULL) time=proc->sigma();
	}
	else
	{
		if(inparc->m_type==2)
		{
			net=NULL;
			net=(CGNetworkS *)(inparc->GetParent());
			if(net!=NULL) time=net->sigma(inparc);
		}
	}	
	return time;
}

double CGWire::sigma(long *queue)
{
//
//return the closest done time
//
	CGData *inparc;
	CGNetworkS *net;
	CGProcessor *proc;
	double time;
	inparc=select();
	if(inparc->m_type==1)
	{
		proc=NULL;
		proc=(CGProcessor *)(inparc->GetParent());
		if(proc!=NULL) time=proc->sigma(queue);
	}
	else
	{
		if(inparc->m_type==2)
		{
			net=NULL;
			net=(CGNetworkS *)(inparc->GetParent());
			if(net!=NULL) time=net->sigma(inparc,queue);
		}
	}	
	return time;
}

CGData * CGWire::select_clientf()
{
	long i,tempq,tempt;
	for(i=1;i<m_nports;i++)
	{
		inparc=(CGData *)(m_ports.GetAt(i));
		if(inparc->m_type==1)
		{
			proc=NULL;
			proc=(CGProcessor *)(inparc->GetParent());
			if(proc==NULL) return in;
			if(m_type_queue==false)
			{
				if(m_time>proc->sigma())
				{
					m_time=proc->sigma();
					in=inparc;
				}
			}
			else
			{
				tempt=proc->sigma(&tempq);
				if(tempq<dim_queue)
				{
					m_time=tempt;
					dim_queue=tempq;
					in=inparc;
				}
			}
		}
		else
		{
			if(inparc->m_type==2)
			{
				net=NULL;
				net=(CGNetworkS *)(inparc->GetParent());
				if(net==NULL) return in;
				if(m_type_queue==false)
				{
					if(m_time>net->sigma(inparc))
					{
						m_time=net->sigma(inparc);
						in=inparc;
					}
				}
				else
				{
					tempt=net->sigma(inparc,&tempq);
					if(tempq<dim_queue)
					{
						m_time=tempt;
						dim_queue=tempq;
						in=inparc;
					}
				}
			}
		}
	}
	return in;
}

CGData * CGWire::select_clientt()
{
	long i,j;
	if(start==0)
	{
		bool flag=false;
		start=1;
		while(flag==false)
		{
			inparc=(CGData *)(m_ports.GetAt(start));
			for(j=0;j<N;j++)
				if(((CGData *)m_selected.GetAt(j))==inparc) break;
			if(j==N)
			{
				if(inparc->m_type==1)
				{
					proc=NULL;
					proc=(CGProcessor *)(inparc->GetParent());
					if(proc!=NULL)
					{
						m_time=proc->sigma();
						in=inparc;
					}
				}
				else
				{
					if(inparc->m_type==2)
					{
						net=NULL;
						net=(CGNetworkS *)(inparc->GetParent());
						if(net!=NULL)
						{
							m_time=net->sigma(inparc);
							in=inparc;
						}
					}
				}
				flag=true;
			}
			else start++;
		}
	}
	else start=1;
	for(i=start;i<m_nports;i++)
	{
		inparc=(CGData *)(m_ports.GetAt(i));
		if(inparc->m_type==1)
		{
			proc=NULL;
			proc=(CGProcessor *)(inparc->GetParent());
			if(m_time>proc->sigma() && proc!=NULL)
			{
				m_time=proc->sigma();
				in=inparc;
			}
		}
		else
		{
			if(inparc->m_type==2)
			{
				net=NULL;
				net=(CGNetworkS *)(inparc->GetParent());
				if(m_time>net->sigma(inparc))
				{
					m_time=net->sigma(inparc);
					in=inparc;
				}
			}
		}
	}
	return in;
}

CObject * CGWire::GetSource()
{
	if(m_nports>1) return NULL;
	if(m_type==1) return ((CGData *)m_parent)->GetParent();
	else return ((CGData *)m_ports.GetAt(0))->GetParent();
}

bool CGWire::IsHere(CGData *in)
{
	if(m_type!=1)
	{
		if((CGData *)m_parent==in) return true;
		else return false;
	}
	else
	{
		m_nports=m_ports.GetSize();
		long i;
		for(i=0;i<m_nports;i++)
			if((CGData *)m_ports.GetAt(i)==in) return true;
	}
	return false;
}

int CGWire::Get(long &n1, long &p1, long &n2, long &p2)
{
	int type;
	if(m_get==m_nports) return -1;
	CGData *tmp;
	p1=m_parent->m_name;
	tmp=((CGData *)m_ports.GetAt(m_get));
	p2=tmp->m_name;
	if(m_parent->m_type==1)
	{
		n1=((CGProcessor *)m_parent->m_parent)->GetName();
		if(tmp->m_type==1)
		{
			n2=((CGProcessor *)tmp->m_parent)->GetName();
			type=2;
		}
		else if(tmp->m_type==2)
		{
			n2=((CGNetworkS *)tmp->m_parent)->GetName();
			type=5;
		}
		else return -1;
	}
	else if(m_parent->m_type==2)
	{
		n1=((CGNetworkS *)m_parent->m_parent)->GetName();
		if(tmp->m_type==1)
		{
			n2=((CGProcessor *)tmp->m_parent)->GetName();
			if(m_type==3) type=4;
			else
			{
				type=0;
				n1=m_parent->IsKind();
			}
		}
		else if(tmp->m_type==2)
		{
			n2=((CGNetworkS *)tmp->m_parent)->GetName();
			if(m_type==3) type=3;
			else
			{
				type=1;
				n1=m_parent->IsKind();
			}
		}
		else return -1;
	}
	else return -1;
	m_get++;
	return type;
}

void CGWire::reset()
{
	m_get=0;
}

long CGWire::GetNr()
{
	return m_nports;
}


int CGWire::kill(CGData *dead)
{
	m_nports=m_ports.GetSize();
	if(m_nports==1)
	{
		if(m_parent==dead)
		{
			if(((CGData *)m_ports[0])->m_parent->IsKindOf(RUNTIME_CLASS(CGNetworkS))!=0)
			{
				if(((CGData *)m_ports[0])->m_parent==m_parent_wire)
					((CGData *)m_ports[0])->m_parent_wire=NULL;
				else
					((CGData *)m_ports[0])->m_parent_ext_wire=NULL;
				((CGNetworkS *)((CGData*)m_ports[0])->m_parent)->DelPort((CGData *)m_ports[0]);
			}
			else
			{
				((CGData *)m_ports[0])->m_parent_wire=NULL;
				((CGProcessor *)((CGData*)m_ports[0])->m_parent)->DelPort((CGData *)m_ports[0]);
			}
		}
		else
		{
			if(m_parent->m_parent->IsKindOf(RUNTIME_CLASS(CGNetworkS))!=0)
			{
				if(m_parent->m_parent==m_parent_wire)
					m_parent->m_parent_wire=NULL;
				else
					m_parent->m_parent_ext_wire=NULL;
				((CGNetworkS *)m_parent->m_parent)->DelPort(m_parent);
			}
			else
			{
				m_parent->m_parent_wire=NULL;
				((CGProcessor *)m_parent->m_parent)->DelPort(m_parent);
			}
		}
		return 0;
	}
	else
	{
		if((dead->IsKind()==1 && dead->m_parent->IsKindOf(RUNTIME_CLASS(CGNetworkS))==0) 
			|| (dead->IsKind()==0 && dead->m_parent->IsKindOf(RUNTIME_CLASS(CGNetworkS))!=0 && dead->m_parent==m_parent_wire))
		{
			if(m_parent!=dead)
			{
				if(m_parent->m_parent->IsKindOf(RUNTIME_CLASS(CGNetworkS))!=0)
				{
					if(m_parent->m_parent==m_parent_wire)
						m_parent->m_parent_wire=NULL;
					else
						m_parent->m_parent_ext_wire=NULL;
					((CGNetworkS *)m_parent->m_parent)->DelPort(m_parent);
				}
				else
				{
					m_parent->m_parent_wire=NULL;
					((CGProcessor *)m_parent->m_parent)->DelPort(m_parent);
				}
			}
			for(long i=0;i<m_nports;i++)
			{
				if((CGData *)m_ports[i]!=dead)
				{
					((CGData *)m_ports[i])->m_parent_wire=NULL;
					if(((CGData *)m_ports[i])->IsKind()==0)
					{
						if(((CGData *)m_ports[i])->m_parent->IsKindOf(RUNTIME_CLASS(CGNetworkS))!=0)
						{
							if(((CGData *)m_ports[i])->m_parent==m_parent_wire)
								((CGData *)m_ports[i])->m_parent_wire=NULL;
							else
								((CGData *)m_ports[i])->m_parent_ext_wire=NULL;
							((CGNetworkS *)((CGData*)m_ports[i])->m_parent)->DelPort((CGData *)m_ports[i]);
						}
						else
						{
							((CGData *)m_ports[i])->m_parent_wire=NULL;
							((CGProcessor *)((CGData*)m_ports[i])->m_parent)->DelPort((CGData *)m_ports[i]);
						}
					}
				}
			}
			return 0;
		}
		else
		{
			if(m_parent==dead)
			{
				m_parent->m_parent_wire=NULL;
				m_parent=(CGData*)m_ports[m_nports-1];
				m_nports--;
				m_ports.RemoveAt(m_nports);
				m_ports.FreeExtra();
			}
			else
			{
				for(long i=0;i<m_nports;i++)
				{
					if(((CGData *)m_ports[i])==dead)
					{
						((CGData *)m_ports[i])->m_parent_wire=NULL;
						m_ports.RemoveAt(i);
						m_ports.FreeExtra();
						m_nports--;
					}
				}
			}
			return 1;
		}
	}
}

void CGWire::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	
	m_ports.Serialize(ar);
	if(ar.IsStoring())
	{
		ar<<m_nports;
		ar<<m_time;
		ar<<m_type;
		ar<<N;
		ar<<start;
		ar<<dim_queue;
	}
	else
	{
		ar>>m_nports;
		ar>>m_time;
		ar>>m_type;
		ar>>N;
		ar>>start;
		ar>>dim_queue;
	}
}
