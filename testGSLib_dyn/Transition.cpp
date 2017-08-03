// Transition.cpp: implementation of the CTransition class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright 2005 Gabriel Dimitriu

	This file is part of Generic Simulator.
	This file contains the implementation of transition class. This class is the real 
	class who implement the real function of the active element. This is particularized
	for parallel machines.
	
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
#include "Transition.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
IMPLEMENT_SERIAL(CTransition,CGTransition,1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTransition::CTransition()
{
	m_freset=true;
}

CTransition::CTransition(CString *val):CGTransition(val)
{
	m_freset=true;
}

CTransition::~CTransition()
{

}

void CTransition::proc_deltaext(CGProcessor *proc,CGData *data,long *s,CObArray *value,CObArray *value_n,long nr)
{
//
//compute the value of the external transition
//
	double tmp=1.0;
//	cout<<"extern s="<<*s<<" at "<<proc->GetTime()<<endl;cout.flush();
	if(*s==1)
	{
		*s=1;
//		cout<<"finished but 1 at"<<proc->GetTime()<<endl;cout.flush();
		CGData *tout;
		long N=(proc->m_outputs).GetSize();
		for(int i=0;i<N;i++)
		{
			tout=(CGData *)((proc->m_outputs).GetAt(i));
			if(tout->m_name==1)	break;
		}
		tout->SetSource((CObject *)proc);
		tout->SetTime(proc->GetTime());
		tout->SetWTime(proc->GetTime());
		tout->Set(&tmp);
		tout->RecvMsg(2,proc->GetTime(),proc);
	}
	((element *)value_n->GetAt(1))->data[0]=((element *)value->GetAt(1))->data[0]+data->Get();
	proc->AddOutNow(((element *)value_n->GetAt(1))->m_name);
	*s=1;
	proc->SettL(proc->GetTime());
	proc->SettN(proc->GetTime()+3.0);
}

void CTransition::proc_deltaint(CGProcessor *proc,long *s,CObArray *value,CObArray *value_n,long nr)
{
//
//compute the value of the internal transition
//
	double tmp=1.0;
	proc->SettL(proc->GetTime());
	proc->SettN(proc->GetTime()+m_clk);
	((element *)value_n->GetAt(1))->data[0]=((element *)value->GetAt(1))->data[0];
	//proc->AddOutNow(((element *)value_n->GetAt(1))->m_name);
	if(m_freset==true)
	{
		CGData *tout;
//		cout<<"first "<<proc->GetPrevTime()<<endl;cout.flush();
		long N=(proc->m_outputs).GetSize();
		for(int i=0;i<N;i++)
		{
			tout=(CGData *)((proc->m_outputs).GetAt(i));
			if(tout->m_name==1)	break;
		}
		tout->SetSource((CObject *)proc);
		tout->SetTime(proc->GetPrevTime());
		tout->SetWTime(proc->GetPrevTime());
		tout->Set(&tmp);
		m_freset=false;
		tout->RecvMsg(2,proc->GetPrevTime(),proc);
	}
	if(*s==1)
	{
		CGData *tout;
		*s=0;
//		cout<<"finished but 0 at "<<proc->GetPrevTime()<<endl;cout.flush();
		long N=(proc->m_outputs).GetSize();
		for(int i=0;i<N;i++)
		{
			tout=(CGData *)((proc->m_outputs).GetAt(i));
			if(tout->m_name==1)	break;
		}
		tout->SetSource((CObject *)proc);
		tout->SetTime(proc->GetPrevTime());
		tout->SetWTime(proc->GetPrevTime());
		tout->Set(&tmp);
		tout->RecvMsg(2,proc->GetPrevTime(),proc);
	}
}

int CTransition::proc_lambda(CGProcessor *proc,element *val,long port)
{
//
//output function
//
	if(port!=1)
	{
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
			if(proc->GetMType()!=0)
				tout->RecvMsg(3,proc->GetTime(),proc);
		}
		else
		{
			tout->SetSource((CObject *)proc);
			tout->SetTime(proc->GetTime());
			tout->SetWTime(proc->GetTime());
			tout->Set(val->data);
			if(proc->GetMType()!=0)
				tout->RecvMsg(2,proc->GetTime(),proc);
		}
	}
	return 0;
}


void CTransition::Serialize(CArchive &ar)
{
	CGTransition::Serialize(ar);
}
