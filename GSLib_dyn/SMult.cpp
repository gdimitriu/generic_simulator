// SMult.cpp: implementation of the CSMult class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the implementation of simulation multiplication class.
	
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
#include "SMult.h"
#include <iostream>
#include "GInput.h"
#include "GOutput.h"

IMPLEMENT_SERIAL(CSMult,CGSum,1);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSMult::CSMult() : CGSum()
{

}

CSMult::CSMult(CObject *parent,long name,long in,long dim,bool type) : CGSum(parent,name,in,dim,type)
{

}

CSMult::~CSMult()
{

}

void CSMult::Serialize(CArchive &ar)
{
	CGSum::Serialize(ar);
	if(ar.IsStoring())
	{
	}
	else
	{
	}
}

int CSMult::receive2(double time,CGData *input)
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
	for(i=0;i<input->GetDim();i++)
		((element *)m_value[0])->data[i]*=input->m_value[i];
	m_vals++;
	if(m_vals==N) receive1(time);
	return 2;
}
int CSMult::receive1(double time)
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
				for(k=0;k<((CGData *)m_inputs[j])->GetDim();k++)
					((element *)m_value[i])->data[k]*=((CGData *)m_inputs[j])->m_value[k];
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
			((element *)m_value[i])->data[k]=1.0;
	if(m_RInput==true)
		for(i=0;i<m_nin;i++)
			((CGData *)m_inputs[i])->ResetG();
	return 0;
}