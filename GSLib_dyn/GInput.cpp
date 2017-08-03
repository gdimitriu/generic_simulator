// GInput.cpp: implementation of the CGInput class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0

	This file is part of Generic Simulator.
	This file contains the implementation of an input generic port.
	
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
#include "GInput.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
IMPLEMENT_SERIAL(CGInput,CGData,1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGInput::CGInput() : CGData()
{

}

CGInput::CGInput(long i) : CGData(i,0.0)
{
	m_generator=NULL;
	m_gen=false;
	m_file=false;
}

CGInput::CGInput(long i,CString *name) : CGData(i,0.0)
{
	m_generator=NULL;
	m_gen=false;
	m_file=true;
	LPTSTR wstr;
	wstr=name->GetBuffer(300);
	m_fname=*name;
	m_out.open(wstr,ios::out);
	name->ReleaseBuffer();
	delete name;
}

void CGInput::SetFName(CString *name)
{
	m_file=true;
	LPTSTR wstr;
	wstr=name->GetBuffer(300);
	m_fname=*name;
	m_out.open(wstr,ios::out);
	name->ReleaseBuffer();
	delete name;
}

CGInput::~CGInput()
{
	if(m_file==true) m_out.close();
	if(m_gen==true) delete[] m_generator;
}

void CGInput::Set(double *val)
{
	long i;
	memcpy(m_value,val,m_nr*sizeof(double));
	if(m_gen==true)
	{
		for(i=0;i<m_nr;i++)
			m_value[i]=val[i]+m_generator[i].generate();
	}
	if(m_file==true)
	{
		m_out<<m_wtime<<":"<<m_value[0]<<":";
		for(i=1;i<m_nr;i++)
			m_out<<m_value[i]<<":";
		m_out<<endl;
	}
}

void CGInput::Set()
{
	long i;
	for(i=0;i<m_nr;i++)
		m_value[i]=m_generator[i].generate();
	if(m_file==true)
	{
		m_out<<m_wtime<<":"<<m_value[0]<<":";
		for(i=1;i<m_nr;i++)
			m_out<<m_value[i]<<":";
		m_out<<endl;
	}
}

void CGInput::SetGenerator(CString *var,long i)
{
	if(i>m_nr && m_gen==true)
	{
		cout<<"error at "<<var<<":"<<i<<endl;
		return;
	}
	if(m_gen==false) m_generator=new CGRepartition[m_nr];
	m_gen=true;
	m_generator[i].SetGen(var);
	m_generator[i].Set(m_name);
}

void CGInput::SetGenerator(CString *var)
{
	SetGenerator(var,0);
}

void CGInput::Serialize(CArchive &ar)
{
	CGData::Serialize(ar);
	if(ar.IsStoring())
	{
		ar<<m_file;
		ar<<m_generator;
		if(m_file==true) ar<<m_fname;
	}
	else
	{
		CObject *tmp;
		int temp;
		ar>>temp;
		m_file=(bool)temp;
		ar>>tmp;
		m_generator=(CGRepartition *)tmp;
		if(m_file==true)
		{
			ar>>m_fname;
			LPTSTR wstr;
			wstr=m_fname.GetBuffer(300);
			m_out.open(wstr,ios::out);
			m_fname.ReleaseBuffer();
		}
	}
}

int CGInput::IsKind()
{
	return 0;
}

