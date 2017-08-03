// GCElem.cpp: implementation of the CGCElem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GCElem.h"
#include "GData.h"
#include "GNetworkS.h"
#include "GProcessor.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the implementation of storage element for CGCoordinator.
	
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
CGCElem::CGCElem()
{
	m_parent=NULL;
	m_sender=NULL;
	m_time=-1;
	m_type=-1;
}

CGCElem::CGCElem(CObject *parent,int type,double time,CObject *sender)
{
	m_parent=parent;
	m_type=type;
	m_time=time;
	m_sender=sender;
}

CGCElem::CGCElem(CObject *parent,int type,double time,CObject *sender,CObject *dead)
{
	m_parent=parent;
	m_type=type;
	m_time=time;
	m_sender=sender;
	m_dead=dead;
}

CGCElem::~CGCElem()
{

}

int CGCElem::Send()
{
	int ret;
	if(m_type<4)
	{
		if(m_parent->IsKindOf(RUNTIME_CLASS(CGData))!=0)
			return ((CGData *)m_parent)->receivemsg(m_type,m_time,m_sender);
		if(m_parent->IsKindOf(RUNTIME_CLASS(CGProcessor))!=0)
			if(m_type!=1)
				return ((CGProcessor *)m_parent)->receivemsg(m_type,m_time,m_sender);
			else
			{
				//((CGNetworkS *)((CGProcessor *)m_parent)->GetParent())->ResetProc(m_parent);
				return ((CGProcessor *)m_parent)->receivemsg(m_type,m_time,NULL);
			}
		if(m_parent->IsKindOf(RUNTIME_CLASS(CGNetworkS))!=0)
		{
			ret=((CGNetworkS *)m_parent)->receivemsg(m_type,m_time,m_sender);
			if(m_type==1) ((CGNetworkS *)m_parent)->ResetNet();
			return ret;
		}
	}
	else
	{
		if(m_type==4)
		{
			if(m_parent==m_dead)
			{
				if(m_parent->IsKindOf(RUNTIME_CLASS(CGProcessor))!=0)
					return ((CGProcessor *)m_parent)->kill();
				if(m_parent->IsKindOf(RUNTIME_CLASS(CGNetworkS))!=0)
					return ((CGNetworkS *)m_parent)->kill();
			}
		}
	}
	return -1;
}
