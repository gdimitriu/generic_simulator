// Processor.h: interface for the CProcessor class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright 2005 Gabriel Dimitriu

	This file is part of Generic Simulator.
	This file contains the specification of a Processor.
	
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
#if !defined(AFX_PROCESSOR_H__E7B05192_0A3D_4431_9C99_08DF9C434694__INCLUDED_)
#define AFX_PROCESSOR_H__E7B05192_0A3D_4431_9C99_08DF9C434694__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GProcessor.h"

class DllExport CProcessor : public CGProcessor 
{
	DECLARE_SERIAL_DLL(CProcessor)
public:
	virtual void Serialize(CArchive &ar);
	CProcessor();
	CProcessor(long val,CGTransition *generator);
	CProcessor(long val,CGTransition *generator,bool type);
	CProcessor(CObject *parent,long val,CGTransition *generator);
	CProcessor(CObject *parent,long val,CGTransition *generator,bool type);
	virtual ~CProcessor();
};

#endif // !defined(AFX_PROCESSOR_H__E7B05192_0A3D_4431_9C99_08DF9C434694__INCLUDED_)
