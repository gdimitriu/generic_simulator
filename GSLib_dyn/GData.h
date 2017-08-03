// GData.h: interface for the CGData class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the definition of basic data structures. This is the base
	for all communication systems.
	
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
#if !defined(AFX_GDATA_H__A00EEE98_282D_4737_8B37_FB0A8328C495__INCLUDED_)
#define AFX_GDATA_H__A00EEE98_282D_4737_8B37_FB0A8328C495__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GWire.h"
#include "GNetworkS.h"
#include "GProcessor.h"
#include "stdafx.h"

using namespace std ;
class CGWire;
class CGNetworkS;
class CGProcessor;

class DllExport CGData : public CObject  
{
	DECLARE_SERIAL_DLL(CGData)
	friend class CGWire;
	friend class CGNetworkS;
	friend class CGProcessor;
	friend class CGProcessorS;
	friend class CGCoordinator;
public:
	void DisableCoord();
	long GetSourceName();
	void SetSourceName(long source);
	bool m_dual;
	void SetName(long name);
	virtual int IsKind();
	virtual void Serialize(CArchive &ar);
	double GetWTime();
	long GetName();

	void SetParent(CObject *parent,int type);
	void SetParent(CObject *parent);
	void SetParentEW(CObject *parent);
	void SetParentW(CObject *ob);
	CObject * GetParent();
	CObject * GetParentEW();
	CObject * GetParentW();

	CObject * GetSource();
	void SetSource(CObject *ob);
	long GetDim();
	void SetDim(long nr);
	double GetClientExt();
	void SetClientExt(double val);
	virtual int RecvMsg(int type,double time,CObject *sender);
	virtual int receivemsg(int type,double time,CObject *sender);
	void SetWTime(double time);
	double GetTime();
	void SetTime(double time);
	
	CGData();
	CGData(long name,double value);
	CGData(long name);
	virtual CGData * copy(CObject *parent,long name);
	virtual CGData * copy(CObject *parent);
	virtual ~CGData();
	virtual double * Get(long *nr);
	virtual void Set(double *val);
	virtual double Get();
	virtual void Reset();
	virtual void ResetG();
	double *m_value;
	long m_name;
	int m_type; //0=unknown 1=processor 2=network
	bool m_gen;
protected:
	bool m_disable_coord;
	double m_wtime;
	double m_time;
	double m_client_ext;
	long m_nr;
	long m_sourcename; //use by CGDistributionBus
	CObject *m_source;
	CObject *m_parent;
	CGWire *m_parent_wire;
	CGWire *m_parent_ext_wire;
};

#endif // !defined(AFX_GDATA_H__A00EEE98_282D_4737_8B37_FB0A8328C495__INCLUDED_)
