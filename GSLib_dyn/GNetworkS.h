// GNetworkS.h: interface for the CGNetworkS class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0
	2006 version 2.0

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

#if !defined(AFX_GNETWORKS_H__C944D7E5_1024_4F49_8F59_6A7711AFD17F__INCLUDED_)
#define AFX_GNETWORKS_H__C944D7E5_1024_4F49_8F59_6A7711AFD17F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GProcessor.h"
#include "GCoordinator.h"
#include "GWire.h"
#include "GData.h"
#include <afxmt.h>
#include "stdafx.h"
#define precision 1e-12
using namespace std ;

class CGWire;
class CGData;
class CGCoordinator;
class CGProcessor;

class DllExport CGNetworkS : public CObject  
{
	DECLARE_SERIAL_DLL(CGNetworkS)
public:
	CGData * GetNOPort(CString &data);
	CGData * GetNIPort(CString &data);
	void ResetNOPort();
	void ResetNIPort();
	void ResetNProcP();
	void ResetNProc();
	CGProcessor * GetNProcP(CString &data);
	CGProcessor * GetNProc(CString &data);
	CGNetworkS *GetNNet(CString &data);
	int Add(CObject *ob);
	void ResetNNet();
	CGNetworkS * GetNet(long name);
	void Start();
	void SetManualStart(bool type);
	int GetDimPort(long port);
	double GetClockPrecision();
	void SetClockAdvance(double time);
	double GetClockAdvance();
	void WaitCoord();
	void SetWork(CObject *ob);
	bool GetWork(CObject *ob);
	void DisableCoord();
	CGCoordinator * GetCoordinator();
	//this functions could be derivate
	virtual int receivemsg(int type,double time,CObject *in);
	virtual void ResetProc(CObject *ob);
	virtual void SetProc(CObject *ob);
	virtual void SetNet(CObject *ob);
	virtual void ResetNet(void);
	virtual double sigma(CGData *in,long *queue);
	virtual double sigma(CGData *in);
	virtual void PrintData();
	//settings
	virtual void SetCoordinator(CGCoordinator *coord);
	virtual void SetClockPrecision(double val);
	virtual bool GetTypeQueue();
	virtual void SetTypeQueue(bool type);
	virtual bool GetInType();
	virtual void SetInType(bool type);
	virtual bool GetTypeWire();
	virtual void SetTypeWire(bool type);

	//to born and to die
	void SetName(long name);
	long GetName(void);
	CGNetworkS(CObject *parent,long i);
	CGNetworkS(long i);
	CGNetworkS();
	int kill();
	CObject * GetParent();
	void SetParent(CObject *parent);
	virtual void Serialize(CArchive &ar);
	CGNetworkS * copy(CObject *parent);
	CGNetworkS * copy(CObject *parent,long name);
	virtual ~CGNetworkS();

	//objects operations
	int AddNetwork(CObject *pnet);
	int AddProc(CObject *ppr);
	int AddProcP(CObject *ppr);
	int DelProc(CGProcessor *dead);
	int DelProc(long name);
	int DelNet(CGNetworkS *dead);
	int DelNet(long name);

	//connection operations
	int AddPort(CObject *port,bool type);
	int DelPort(CGData *dead);
	CObject * GetPort(long port,int *type);
	int DelWire(CGWire *dead);
	int AddNetworkNetwork(long n1, long in1,long n2, long in2);
	int AddProcNetwork(long p,long in1,long n,long in2);
	int AddNetworkProc(long n,long in1,long p,long in2);
	int AddParentNet(long in1,long in2, long n, int type);
	int AddParentProc(long in1, long in2, long p,int type);
	int AddProcProc(long p1,long in1,long p2,long in2);
protected:
	long m_netpos;
	long m_procpos;
	long m_procppos;
	long m_iportpos;
	long m_oportpos;
	virtual int receive0(double time);
	virtual int receive1(double time);
	virtual int receive2(double time,CObject *in);
	virtual int receive3(double time,CObject *in);

	bool m_disable_coord;
	bool m_manual_start;
	int m_type;
	bool m_sims;
	bool m_adds;
	double m_time_ext;
	double m_time;
	long m_nprocs;
	long m_nprocsp;
	long m_nnets;
	long m_nin;
	long m_nout;
	long m_name;
	bool m_qtype;
	bool m_btype;
	bool m_wtype;//true=unique,false=notunique
	bool m_intype;
	int * m_return;
	bool *m_procs;
	bool *m_nets;
	bool *m_procsp;
	bool *m_wout;
	CGCoordinator *m_coordinator;
	CObject *m_parent;
	CObArray m_processors;
	CObArray m_processorsp;
	CObArray m_networks;
	CObArray m_inputs;
	CObArray m_outputs;
	CObArray m_WIn;
	CObArray m_WOut;
	CObArray m_WInt;
	CObArray m_aprocs;
	CObArray m_anets;
	CObArray m_aports;
	double m_CLK;
	double m_CLKP;
};

#endif // !defined(AFX_GNETWORKS_H__C944D7E5_1024_4F49_8F59_6A7711AFD17F__INCLUDED_)
