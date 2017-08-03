// GOutput.cpp: implementation of the CGOutput class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0

	This file is part of Generic Simulator.
	This file contains the implementation of an output generic port.
	
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
#include "GOutput.h"
#include <iostream>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
IMPLEMENT_SERIAL(CGOutput,CGData,1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGOutput::CGOutput() : CGData()
{

}

CGOutput::CGOutput(long i,CString *name) : CGData(i,0.0)
{
	m_file=true;
	LPTSTR wstr;
	wstr=name->GetBuffer(300);
	m_fname=*name;
	m_out.open(wstr,ios::out);
	name->ReleaseBuffer();
	delete name;
}

CGOutput::CGOutput(long i) : CGData(i,0.0)
{
	m_file=false;
}

void CGOutput::SetFName(CString *name)
{
	m_file=true;
	LPTSTR wstr;
	wstr=name->GetBuffer(300);
	m_fname=*name;
	m_out.open(wstr,ios::out);
	name->ReleaseBuffer();
	delete name;
}

CGOutput::~CGOutput()
{
	if(m_file==true) m_out.close();
}

void CGOutput::Set(double *val)
{
//
//set the value of the port
//
	long i;
	memcpy(m_value,val,m_nr*sizeof(double));
	if(m_file==true)
	{
		m_out<<m_wtime<<":"<<m_value[0];
		for(i=1;i<m_nr;i++)
			m_out<<":"<<m_value[i];
		m_out<<endl;
	}
}

void CGOutput::Serialize(CArchive &ar)
{
	CGData::Serialize(ar);
	if(ar.IsStoring())
	{
		ar<<m_file;
		if(m_file==true)
			ar<<m_fname;
	}
	else
	{
		int temp;
		ar>>temp;
		m_file=(bool)temp;
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
int CGOutput::IsKind()
{
	return 1;
}

void CGOutput::Reset()
{
//
//reset the value
//
	long i;
	for(i=0;i<m_nr;i++)
		m_value[i]=0.0;
	if(m_file==true)
	{
		m_out<<m_wtime<<":"<<m_value[0];
		for(i=1;i<m_nr;i++)
			m_out<<":"<<m_value[i];
		m_out<<endl;
	}
}

void CGOutput::ResetG()
{
//
//reset the value
//
	long i;
	for(i=0;i<m_nr;i++)
		m_value[i]=0.0;
}

