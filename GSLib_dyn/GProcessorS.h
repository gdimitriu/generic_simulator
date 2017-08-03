// GProcessorS.h: interface for the CGProcessorS class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 Version 1.0

	This file is part of Generic Simulator.
	This file contains the definition of synchron processor class, this class is the active
	element in a simulation. This class in used only with CGTransitionS and CGNetworkS
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
#if !defined(AFX_GPROCESSORS_H__48A22261_2243_11DB_B910_88BB7D45D50C__INCLUDED_)
#define AFX_GPROCESSORS_H__48A22261_2243_11DB_B910_88BB7D45D50C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GProcessor.h"
#include "stdafx.h"

class DllExport CGProcessorS : public CGProcessor  
{
	DECLARE_SERIAL_DLL(CGProcessorS)
	friend class CGTransitionS;
public:
	virtual void Serialize(CArchive &ar);
	virtual int DelPort(CGData *dead);
	CGProcessorS(CObject *parent,long val,CGTransition *generator,bool type);	
	CGProcessorS();
	virtual ~CGProcessorS();
	virtual int receivemsg(int type,double time,CObject *in);
protected:
	bool m_first3;
	long m_ev;
	bool m_runS;
	void Set2atInput(CGData *input);
	bool Get2atInput(CGData *input);
	virtual int RInitP(CGData *port);
	virtual int receive3(double time);
	virtual int receive2(double time,CGData *input);
	virtual int receive1(double time);
	virtual int receive0(double time);
	bool *m_win;
};

#endif // !defined(AFX_GPROCESSORS_H__48A22261_2243_11DB_B910_88BB7D45D50C__INCLUDED_)
