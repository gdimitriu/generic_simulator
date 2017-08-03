// SCoordinator.h: interface for the CSCoordinator class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the definition of Simulation Coordinator.
	
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
#if !defined(AFX_SCOORDINATOR_H__15CE3DA1_6E48_11DB_B910_9AF8DBB1D53D__INCLUDED_)
#define AFX_SCOORDINATOR_H__15CE3DA1_6E48_11DB_B910_9AF8DBB1D53D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GNetworkS.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "stdafx.h"
#include "SInputCoordinator.h"
#include "SInputPartModification.h"
#include "element.h"

using namespace std ;

class DllExport CSCoordinator : public CObject  
{
public:
	int InputPart(CGNetworkS *net);
	void setParent(CGNetworkS *net);
	int InputData();
	int InputData(CGNetworkS *net);
	int Run();
	CSCoordinator();
	CSCoordinator(CGNetworkS *net);
	virtual ~CSCoordinator();
protected:
	CSInputCoordinator *m_inputdata;
	CSInputPartModification *m_inputpart;
	CGNetworkS *m_parent;
	element *m_run;
};

#endif // !defined(AFX_SCOORDINATOR_H__15CE3DA1_6E48_11DB_B910_9AF8DBB1D53D__INCLUDED_)

