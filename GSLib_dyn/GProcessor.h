// GProcessor.h: interface for the CGProcessor class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the definition of processor class, this class is the active
	element in a simulation. This class in used only with CGTransition and CGNetworkS
	classes and theirs derivate.
	
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
#if !defined(AFX_GPROCESSOR_H__13857F12_9EB7_4F9B_A0F6_0BDB71A54910__INCLUDED_)
#define AFX_GPROCESSOR_H__13857F12_9EB7_4F9B_A0F6_0BDB71A54910__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GTransition.h"
#include "GNetworkS.h"
#include "GData.h"
#include "Queues.h"
#include "element.h"
#include <list>
#include "stdafx.h"

#define precision 1e-12

using namespace std ;

class CGTransition;
class CGNetworkS;

class DllExport CGProcessor : public CObject  
{
	DECLARE_SERIAL_DLL(CGProcessor)
	friend class CGTransition;
public:
	void SetDelParent(CObject *parent);
	long GetOutputNrPorts();
	long GetInputNrPorts();
	CGData * GetNOPort(CString &data);
	CGData * GetNIPort(CString &data);
	void ResetNOPort();
	void ResetNIPort();
	int Add(CObject *ob);
	double GetNextTime();
	int SetDimPort(long port,long dim);
	int SetFilePort(long port,CString *name);
	void SetRealTime(double time);
	void AddOutNow(long val);
	void EnableOut(bool state);
	void SetStatus(int status);
	int GetStatus();
	void SetStatus(bool external,bool internal);
	void GetStatus(bool *external,bool *internal);
	double GetLLTime();
	void DisableCoord();
	CGCoordinator * GetCoordinator();
	void SetFirstI(bool type);
	void SetIgnore(bool type);
	int GetMType();
	void SetGeneral(bool type);
	void SetReinit(bool type);
	void SetRIType(bool type);
	void SetMemInput(bool type);
	void SetFirst2(bool type);
	void set_intfunc(char *func,long pos);
	void set_extfunc(char *func,long pos);
	void SetType(int type);
	void IsDelayed(bool type);
	void SetFirst(bool type);
	void SetRType(bool type);
	void EnableQ();
	void DisableQ();
	void SetClockPrecision(double val);
	int AddPort(CObject *port, bool type);
	CObject * GetPort(long port,int *type);
	virtual int DelPort(CGData *dead);
	void SetParent(CObject *parent);
	CObject * GetParent(void);
	long GetName(void);
	void SetName(long val);
	CGProcessor();
	CGProcessor(CObject *parent,long val,CGTransition *generator,bool type);	
	virtual ~CGProcessor();
	int kill();
	virtual CGProcessor * copy(CObject *parent,long val);
	virtual CGProcessor * copy(CObject *parent);
	virtual void Serialize(CArchive &ar);
	//these functions could be derivate
	virtual double sigma(long *dim);
	virtual double sigma(void);
	virtual int receivemsg(int type,double time,CObject *in);
	double GetTime();
	void SettN(double val);
	void SettL(double val);
	double GetPrevTime();
	CObArray m_inputs;
	CObArray m_outputs;
protected:
	long m_iportpos;
	long m_oportpos;
	virtual int InternalN(double time);
	virtual int ExternN(CGData *input,double time);
	virtual int ExternS(CGData *input,double time);
	double m_realtime;
	void OutputS();
	void OutputN();
	int m_status;
	int m_ltype;
	bool m_ignore;
	virtual void other_init();
	bool m_general;
	bool m_reinit;
	virtual int RInitP(CGData *port);
	virtual int restore1(double time);
	virtual int receive3(double time);
	virtual int receive2(double time,CGData *input);
	virtual int receive1(double time);
	virtual int receive0(double time);
	bool m_runs;
	bool m_first_alloc;
	bool m_memory;
	bool m_ritype;
	bool m_extern;
	bool m_internal;
	bool m_out;

	bool m_meminput;
	bool m_delay;
	bool m_first2;
	bool m_first; //first message 1
	bool m_firsti; //first message 1 but real mesage 2
	bool m_disableq;
	bool m_rtype;
	long m_name;
	double m_CLKP;
	double m_e;
	double m_tLL; //time of the last last event
	double m_tL;//time of the last event
	double m_tN; //time of the next event
	double m_time;
	long m_s;//internal state
	long m_sL;// internal last state
	int m_type;//0 active, 1 passive
	int m_mtype; //type of the message received
	long m_nin;
	long m_nout;
	CObject * m_parent;
	CObject *m_parent_del;
	CGTransition *m_compute;
	CQueues m_queue;
	CObArray m_value;
	CObArray m_value_n;
	CObArray m_oinputs;
	list<long> m_OutputList;
};

#endif // !defined(AFX_GPROCESSOR_H__13857F12_9EB7_4F9B_A0F6_0BDB71A54910__INCLUDED_)
