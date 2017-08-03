// GTransitionS.h: interface for the CGTransitionS class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 version 1.0

	This file is part of Generic Simulator.
	This file contains the definition of GTransitionS class, this class is a synchron 
	transition used with GProcessorS.
	
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
#if !defined(AFX_GTRANSITIONS_H__48A22262_2243_11DB_B910_88BB7D45D50C__INCLUDED_)
#define AFX_GTRANSITIONS_H__48A22262_2243_11DB_B910_88BB7D45D50C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GTransition.h"
#include "GProcessorS.h"
#include "stdafx.h"

class DllExport CGTransitionS : public CGTransition  
{
	friend class CGProcessorS;
	DECLARE_SERIAL_DLL(CGTransitionS)
public:
	virtual void Serialize(CArchive &ar);
	CGTransitionS();
	CGTransitionS(CString *var);
	virtual ~CGTransitionS();
	//these functions must be derivate for a specific application
	virtual void proc_deltaext(CGProcessor *proc1,CGData *data,long *s,CObArray *value,CObArray *value_n,long nr);
	CGProcessorS *m_parent;

};

#endif // !defined(AFX_GTRANSITIONS_H__48A22262_2243_11DB_B910_88BB7D45D50C__INCLUDED_)
