// GCoordinator.cpp: implementation of the CGCoordinator class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the implementation of Threaded Coordinator.
	
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
#include "GCoordinator.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CGCoordinator, CWinThread)

CGCoordinator::CGCoordinator()
{
	m_parent=NULL;
	m_elem=NULL;
}

CGCoordinator::CGCoordinator(CGNetworkS *parent)
{
	m_parent=parent;
	m_elem=NULL;
}

CGCoordinator::~CGCoordinator()
{
	CloseHandle(event_net);
	CloseHandle(event_end);
	CloseHandle(event_add);
	delete lock;
	while(m_queue.empty()==false)
	{
		m_elem=m_queue.Get();
		delete m_elem;
	}
}

BOOL CGCoordinator::InitInstance()
{
	event_add=CreateEvent(FALSE,TRUE,FALSE,NULL);
	event_end=CreateEvent(FALSE,TRUE,FALSE,NULL);
	event_net=CreateEvent(FALSE,TRUE,FALSE,NULL);
	lock=new CCriticalSection();
	return TRUE;
}

int CGCoordinator::ExitInstance()
{
	return CWinThread::ExitInstance();
}

int CGCoordinator::Run()
{
	bool nr1;
	bool nr2;
	bool end_prog;
	m_lasttime=0.0;
	while(1)
	{

		lock->Lock(INFINITE);
		nr2=m_queue.empty2(m_lasttime);
		nr1=m_queue.empty1(m_lasttime);
		end_prog=m_queue.empty();
		lock->Unlock();
		ResetEvent(event_end);
		if(end_prog==true)
			SetEvent(event_end);
		if(nr1==true && nr2==true)
		{
			SetEvent(event_net);
			WaitForSingleObject(event_add,INFINITE); //wait for event
		}

		lock->Lock(INFINITE);
		m_elem=m_queue.Get(m_lasttime);
		lock->Unlock();

		if(m_elem!=NULL)
		{
			if(m_elem->m_type==1) m_lasttime=m_elem->m_time+m_parent->GetClockAdvance();
			//else m_lasttime=m_elem->m_time+m_parent->GetClockPrecision();
			m_elem->Send();
			delete m_elem;
			m_elem=NULL;
		}
	}
	return 0;
}


int CGCoordinator::CoordinatorLock()
{
	return lock->Lock(INFINITE);
}

int CGCoordinator::CoordinatorUnlock()
{
	return lock->Unlock();
}

void CGCoordinator::Add(CGCElem *elem)
{
	m_queue.Add(elem);
}

void CGCoordinator::Event_Add()
{
	PulseEvent(event_add);
}
