// GTransition.h: interface for the CGTransition class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the definition of transition class. This class is the real 
	class who implement the real function of the active element.
	
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

#if !defined(AFX_GTRANSITION_H__24461DB7_7EE6_4449_949E_F181D63C2C4E__INCLUDED_)
#define AFX_GTRANSITION_H__24461DB7_7EE6_4449_949E_F181D63C2C4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GProcessor.h"
#include "GRepartition.h"
#include "GData.h"
#include "element.h"
#include "parser_func.h"
#include "stdafx.h"
#define precision 1e-12

using namespace std ;

class CGProcessor;
class CGData;

class DllExport CGTransition : public CObject  
{
	DECLARE_SERIAL_DLL(CGTransition)
	friend class CGProcessor;
public:
	void SetMemory(bool type);
	virtual int DelPort(long ind,bool type);
	virtual void Serialize(CArchive &ar);
	virtual void assign_memory(CGProcessor *proc,long pos,bool type);
	virtual void assign_memory(CGProcessor *proc);
	virtual void set_intfunc(char *func,long pos);
	virtual void set_extfunc(char *func,long pos);
	virtual void SetRepartionT(CGRepartition *ob);
	virtual long GetIndexR(double val);
	virtual long GetIndexT(double val);
	virtual void SetClk(double time);
	virtual void Set(long seed);
	virtual void SetParent(CGProcessor *parent);
	CGTransition();
	CGTransition(CString *var);
	virtual ~CGTransition();
	//these functions must be derivate for a specific application
	virtual void proc_redone(CGProcessor *proc,long *s,long *sL,CObArray *value,CObArray *value_n);
	virtual void proc_deltaext(CGProcessor *proc,CGData *data,long *s,CObArray *value,CObArray *value_n,long nr);
	virtual void proc_deltaint(CGProcessor *proc,long *s,CObArray *value,CObArray *value_n,long nr);
	virtual int proc_lambda(CGProcessor *proc,element *val,long port);
	CGProcessor *m_parent;
protected:
	long m_nrout;
	long m_seed;
	bool m_first;
	bool m_amemory;
	bool m_ememory;
	double m_clk;
	CGRepartition *m_repartition;
	CGRepartition *m_ttrans;
	CObArray m_extfunc;
	CObArray m_intfunc;
	Cparser_func_memory *m_memory;
};

#endif // !defined(AFX_GTRANSITION_H__24461DB7_7EE6_4449_949E_F181D63C2C4E__INCLUDED_)
