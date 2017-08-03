// SCoordinator.cpp: implementation of the CSCoordinator class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the implementation of Simulation Coordinator.
	
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
#include "SCoordinator.h"
#include "GInput.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CSCoordinator::CSCoordinator()
{
	AfxInitRichEdit();
	m_parent=NULL;
}
CSCoordinator::CSCoordinator(CGNetworkS *net)
{
	AfxInitRichEdit();
	m_parent=net;
}

CSCoordinator::~CSCoordinator()
{
	if(m_inputdata!=NULL) delete m_inputdata;
}

int CSCoordinator::Run()
{
	element *m_run;
	CGInput *tin;
	int type;
	m_parent->SetClockPrecision(m_inputdata->m_clkprec);
	m_parent->SetClockAdvance(m_inputdata->m_clkadvance);
	m_run=m_inputdata->queue.Get();
	while(m_run!=NULL)
	{
		if(m_run->type!=2)
			m_parent->receivemsg(m_run->type,m_run->m_time,NULL);
		else if(m_run->type!=4)
		{
			tin=(CGInput *)m_parent->GetPort(m_run->m_name,&type);
			tin->SetWTime(m_run->m_time);
			tin->SetTime(m_run->m_time);
			tin->Set(m_run->data);
			tin->RecvMsg(m_run->type,m_run->m_time,NULL);
			delete m_run;
		}
		else if(m_run->type==4)
		{
			
		}
		m_run=m_inputdata->queue.Get();
	}
	return 1;
}

int CSCoordinator::InputData(CGNetworkS *net)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
	m_inputdata=new CSInputCoordinator(NULL);
	m_inputdata->SetParent(net);
	return m_inputdata->DoModal();
}

int CSCoordinator::InputData()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
	m_inputdata=new CSInputCoordinator(NULL);
	m_inputdata->SetParent(m_parent);
	return m_inputdata->DoModal();
}

void CSCoordinator::setParent(CGNetworkS *net)
{
	m_parent=net;
}

int CSCoordinator::InputPart(CGNetworkS *net)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
	m_inputpart=new CSInputPartModification(NULL);
	m_inputpart->SetParent(net);
	m_inputpart->SetQueue(&(m_inputdata->queue));
	m_inputpart->Set(net->GetCoordinator());
	return m_inputpart->DoModal();
}
