// GTransitionS.cpp: implementation of the CGTransitionS class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 version 1.0

	This file is part of Generic Simulator.
	This file contains the implementation of GTransitionS class, this class is a synchron 
	transition used with GProcessorS.
	
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
#include "GTransitionS.h"
IMPLEMENT_SERIAL(CGTransitionS,CGTransition,1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGTransitionS::CGTransitionS() : CGTransition()
{

}

CGTransitionS::CGTransitionS(CString *var) : CGTransition(var)
{

}
CGTransitionS::~CGTransitionS()
{

}

void CGTransitionS::Serialize(CArchive &ar)
{
	CGTransition::Serialize(ar);
}

//functions define must be derivate for a more specific application
void CGTransitionS::proc_deltaext(CGProcessor *proc1,CGData *data,long *s,CObArray *value,CObArray *value_n,long nr)
{
//
//compute the value of the external transition
//
	long i,j;
	CGProcessorS *proc=(CGProcessorS *)proc1;
	if(m_ememory==false)
	{
		cout<<"Error: you have to generate the memory for the transitions !!!\n";
		exit(-1);
	}
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
}
