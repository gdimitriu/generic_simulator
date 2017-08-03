// GWire.h: interface for the CGWire class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the definition of wire class. This class makes the connection
	between diferent inputs and outputs ports.
	
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
#if !defined(AFX_GWIRE_H__AB09F3B7_EC50_4BE9_8B14_16A69DAE811E__INCLUDED_)
#define AFX_GWIRE_H__AB09F3B7_EC50_4BE9_8B14_16A69DAE811E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GProcessor.h"
#include "GNetworkS.h"
#include "GData.h"
#include "stdafx.h"
using namespace std ;
#define precision 1e-12
class CGNetworkS;
class CGProcessor;
class CGData;

class DllExport CGWire : public CObject  
{
	DECLARE_SERIAL_DLL(CGWire)
public:
	void Serialize(CArchive &ar);
	int kill(CGData *dead);
	long GetNr();
	void reset();
	int Get(long &n1,long &p1,long &n2,long &p2);
	bool IsHere(CGData *in);
	CObject * GetSource();
	double sigma(long *queue);
	double sigma();
	double receivemsg(int type, double time,CGData *input);
	int Add(CObject *ob);
	CGWire();
	CGWire(CObject *ob,int type,CGNetworkS *parent);
	virtual ~CGWire();
	int m_type; //0=input; 1=output ;3=internal
	CGData * m_parent;
	CGNetworkS *m_parent_wire;
	long m_nports;
protected:
	long m_get;
	bool m_type_queue;
	CGData * select_clientt();
	CGData * select_clientf();
	bool m_type_client;
	CGData * select(void);
	CObArray m_ports;
	CObArray m_selected;
	bool m_type_wire;
private:
	long dim_queue;
	CGProcessor * proc;
	CGNetworkS* net;
	CGData* inparc;
	CGData* in;
	long N;
	double m_time;
	long start;
};

#endif // !defined(AFX_GWIRE_H__AB09F3B7_EC50_4BE9_8B14_16A69DAE811E__INCLUDED_)
