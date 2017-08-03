// NetworkS.h: interface for the CNetworkS class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright 2005 Gabriel Dimitriu

	This file is part of Generic Simulator.
	This file contains the definition of network class. This clasa holds all 
	processors and connection, and with this class the user will interract.
	
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

#if !defined(AFX_NETWORKS_H__37D2134D_8743_4D1E_9EDD_A02E1B637380__INCLUDED_)
#define AFX_NETWORKS_H__37D2134D_8743_4D1E_9EDD_A02E1B637380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GNetworkS.h"
#include "Processor.h"
#include "Output.h"
#include "Input.h"

using namespace std ;

class DllExport CNetworkS : public CGNetworkS  
{
	DECLARE_SERIAL_DLL(CNetworkS)
public:
	virtual void Serialize(CArchive &ar);
	int AddProcP(CObject *ppr);
	int AddProc(CObject *ppr);
	CNetworkS();
	CNetworkS(CObject *parent,long i);
	CNetworkS(long i);
	virtual ~CNetworkS();
	int AddNetwork(CObject *pnet);
};

#endif // !defined(AFX_NETWORKS_H__37D2134D_8743_4D1E_9EDD_A02E1B637380__INCLUDED_)
