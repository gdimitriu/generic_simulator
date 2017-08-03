// NetworkS.cpp: implementation of the CNetworkS class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright 2005 Gabriel Dimitriu

	This file is part of Generic Simulator.
	This file contains the implementation of network class. This clasa holds all 
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

#include "stdafx.h"
#include "NetworkS.h"
#include <iostream>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
IMPLEMENT_SERIAL(CNetworkS,CGNetworkS,1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CNetworkS::CNetworkS()
{

}

CNetworkS::CNetworkS(long i) : CGNetworkS(i)
{

}

CNetworkS::CNetworkS(CObject *parent,long i) : CGNetworkS(parent,i)
{

}


CNetworkS::~CNetworkS()
{

}
int CNetworkS::AddNetwork(CObject *pnet)
{
//
//add a subnetwork
//
	return CGNetworkS::AddNetwork(pnet);
}

int CNetworkS::AddProc(CObject *ppr)
{
//
//add a processor to the network
//
	return CGNetworkS::AddProc(ppr);
}

int CNetworkS::AddProcP(CObject *ppr)
{
//
//add a Passive processor to the network
//
	return CGNetworkS::AddProcP(ppr);
}

void CNetworkS::Serialize(CArchive &ar)
{
	CGNetworkS::Serialize(ar);
}
