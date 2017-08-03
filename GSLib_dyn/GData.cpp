// GData.cpp: implementation of the CGData class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the implementations of basic data structures. This is the base
	for all communication systems.
	
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
#include "GData.h"
#include "GCElem.h"
#include <stdlib.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
IMPLEMENT_SERIAL(CGData,CObject,1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGData::CGData()
{
	m_nr=1;
	m_value=(double *)calloc(1,sizeof(double));
	m_sourcename=-1;
	m_disable_coord=false;
}

CGData::~CGData()
{
	free(m_value);
}

CGData::CGData(long name,double value)
{
	m_name=name;
	m_nr=1;
	m_value=(double *)calloc(1,sizeof(double));
	m_value[0]=value;
	m_parent=NULL;
	m_type=0;
	m_gen=false;
	m_time=0.0;
	m_wtime=0.0;
	m_client_ext=1.0;
	m_parent_ext_wire=NULL;
	m_parent_wire=NULL;
	m_dual=false;
	m_sourcename=-1;
	m_source=NULL;
	m_disable_coord=false;
}

CGData::CGData(long name)
{
	m_name=name;
	m_nr=1;
	m_parent=NULL;
	m_type=0;
	m_gen=false;
	m_time=0.0;
	m_wtime=0.0;
	m_client_ext=1.0;
	m_value=(double *)calloc(1,sizeof(double));
	m_parent_wire=NULL;
	m_parent_ext_wire=NULL;
	m_dual=false;
	m_sourcename=-1;
	m_source=NULL;
	m_disable_coord=false;
}

double CGData::Get()
{
//
//return the value
//
	return m_value[0];
}

void CGData::SetDim(long nr)
{
//
//set the dimension of elements
//
	m_nr=nr;
	if(m_value!=NULL) free(m_value);
	m_value=(double *)calloc(m_nr,sizeof(double));
}

void CGData::Set(double *val)
{
//
//set the value
//
	memcpy(m_value,val,m_nr*sizeof(double));
}

void CGData::Reset()
{
//
//reset the value
//
	for(long i=0;i<m_nr;i++)
		m_value[i]=0.0;
}

void CGData::ResetG()
{
//
//reset the value for Get from Wire
//
	for(long i=0;i<m_nr;i++)
		m_value[i]=0.0;
}


void CGData::SetParent(CObject *parent,int type)
{
//
//set the parent of the port
//
	m_parent=parent;
	m_type=type;
}

void CGData::SetParent(CObject *parent)
{
	m_parent=parent;
}


CObject * CGData::GetParent()
{
//
//return the parent of the port
//
	return m_parent;
}

void CGData::SetTime(double time)
{
//
//set the curent time
//
	m_time=time;
}

double CGData::GetTime()
{
	return m_time;
}

void CGData::SetWTime(double time)
{
	m_wtime=time;
}

void CGData::SetClientExt(double val)
{
//
//set the client constant
//
	m_client_ext=val;
}

double CGData::GetClientExt()
{
//
//return the client constant
//
	return m_client_ext;
}


double * CGData::Get(long *nr)
{
//
//get the value
//
	*nr=m_nr;
	return m_value;
}

long CGData::GetDim()
{
//
//get the dim of input
//
	return m_nr;
}

void CGData::SetSource(CObject *ob)
{
	m_source=ob;
}

CObject * CGData::GetSource()
{
	return m_source;
}

long CGData::GetName()
{
	return m_name;
}

double CGData::GetWTime()
{
	return m_wtime;
}

void CGData::Serialize(CArchive &ar)
{
	long i;
	int temp;
	CObject::Serialize(ar);
	if(ar.IsStoring())
	{
		ar<<m_nr;
		for(i=0;i<m_nr;i++)
			ar<<m_value[i];
		ar<<m_name;
		ar<<m_type;
		temp=(int)m_gen;
		ar<<temp;
		ar<<m_client_ext;
		ar<<m_sourcename;
		ar<<m_time;
		ar<<m_type;
		ar<<m_wtime;
		temp=(int)m_dual;
		ar<<temp;
		temp=(int)m_disable_coord;
		ar<<temp;
	}
	else
	{
		ar>>m_nr;
		m_value=(double *)calloc(m_nr,sizeof(double));
		for(i=0;i<m_nr;i++)
			ar>>m_value[i];
		ar>>m_name;
		ar>>m_type;
		ar>>temp;
		m_gen=(bool)temp;
		ar>>m_client_ext;
		ar>>m_sourcename;
		ar>>m_time;
		ar>>m_type;
		ar>>m_wtime;
		ar>>temp;
		m_dual=(bool)temp;
		ar>>temp;
		m_disable_coord=(bool)temp;
	}
}


int CGData::IsKind()
{
	return -1;
}

CGData * CGData::copy(CObject *parent)
{
	//create a clone of this port
	CFile f;
	char buf[512];
	CArchive *ar;
	CString fname("testd.dat");
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
	((CGData *)tmp)->SetParent(parent);
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
	return (CGData *)tmp;
}

CGData * CGData::copy(CObject *parent, long name)
{
	//create a brother of this port
	CFile f;
	char buf[512];
	CArchive *ar;
	CString fname("testd.dat");
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
	((CGData *)tmp)->SetParent(parent);
	((CGData *)tmp)->SetName(name);
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
	return (CGData *)tmp;
}

void CGData::SetName(long name)
{
	m_name=name;
}

void CGData::SetParentW(CObject *ob)
{
	m_parent_wire=(CGWire *)ob;
}

CObject * CGData::GetParentW()
{
	return (CGWire *)m_parent_wire;
}
void CGData::SetParentEW(CObject *parent)
{
	m_parent_ext_wire=(CGWire *)parent;
}

CObject * CGData::GetParentEW()
{
	return (CGWire *)m_parent_ext_wire;
}

int CGData::RecvMsg(int type, double time,CObject *sender)
{
	if(m_disable_coord==false)
	{
		if(type!=0 && type!=3)
		{
			CGCElem *elem=new CGCElem(this,type,time,sender);
			CGCoordinator *coord;
			if(m_parent->IsKindOf(RUNTIME_CLASS(CGNetworkS))!=0)
			{
				coord=((CGNetworkS *)m_parent)->GetCoordinator();
				coord->lock->Lock(INFINITE);
				coord->m_queue.Add(elem);
				coord->lock->Unlock();
			}
			else if(m_parent->IsKindOf(RUNTIME_CLASS(CGProcessor))!=0)
			{
				coord=((CGProcessor *)m_parent)->GetCoordinator();
				coord->lock->Lock(INFINITE);
				coord->m_queue.Add(elem);
				coord->lock->Unlock();
			}
			else return -1;
			PulseEvent(coord->event_add);
		}
		else
			receivemsg(type,time,sender);
	}
	else 
		receivemsg(type,time,sender);
	return 0;
}
int CGData::receivemsg(int type, double time,CObject *sender)
{
	if(sender!=NULL)
	{
		if(sender->IsKindOf(RUNTIME_CLASS(CGWire))!=0 && type!=3) //sender is a wire
		{
			if(m_parent->IsKindOf(RUNTIME_CLASS(CGNetworkS))!=0)
			{
				if(m_parent_wire!=sender)
					((CGNetworkS *)m_parent)->receivemsg(type,time,(CObject *)this);
				else
					if(m_parent_ext_wire!=NULL)
						((CGNetworkS *)m_parent_ext_wire->m_parent_wire)->receivemsg(type,time,(CObject *)this);
			}
			else ((CGProcessor *)m_parent)->receivemsg(type,time,(CObject *)this);
		}
		else if(sender->IsKindOf(RUNTIME_CLASS(CGWire))!=0 && type==3)
		{
			if(m_parent->IsKindOf(RUNTIME_CLASS(CGNetworkS))!=0)
			{
				if(m_parent_wire!=sender)
					((CGNetworkS *)m_parent)->receivemsg(type,time,(CObject *)this);
				else
					if(m_parent_ext_wire!=NULL)
						((CGNetworkS *)m_parent_ext_wire->m_parent_wire)->receivemsg(type,time,(CObject *)this);
			}
		}
		else
		{
			if(sender->IsKindOf(RUNTIME_CLASS(CGProcessor))!=0) //sender is a proc
			{
				if(m_parent->IsKindOf(RUNTIME_CLASS(CGProcessor))!=0)//parent is a proc
				{
					if(m_parent!=sender)
						((CGProcessor *)m_parent)->receivemsg(type,time,(CObject *)this);
					else
					{
						if(m_parent_wire!=NULL)
							m_parent_wire->receivemsg(type,time,this);
					}
				}
			}
			else
			{
				if(m_parent->IsKindOf(RUNTIME_CLASS(CGNetworkS))!=0)
					((CGNetworkS *)m_parent)->receivemsg(type,time,(CObject *)this);
				else return -1;
			}
		}
	}
	else
	{
		if(m_parent->IsKindOf(RUNTIME_CLASS(CGNetworkS))!=0)
			((CGNetworkS *)m_parent)->receivemsg(type,time,(CObject *)this);
		else return -1;
	}
	return 0;
}

void CGData::SetSourceName(long source)
{
	m_sourcename=source;
}

long CGData::GetSourceName()
{
	return m_sourcename;
}

void CGData::DisableCoord()
{
	//disable the threaded coordinator
	m_disable_coord=true;
}
