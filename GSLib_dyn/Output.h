// Output.h: interface for the COutput class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright 2005 Gabriel Dimitriu

	This file is part of Generic Simulator.
	This file contains the definition of an output port.
	
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
#if !defined(AFX_OUTPUT_H__180CFD64_30A5_4D8A_88B8_2D049EF76381__INCLUDED_)
#define AFX_OUTPUT_H__180CFD64_30A5_4D8A_88B8_2D049EF76381__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GOutput.h"
using namespace std ;

class DllExport COutput : public CGOutput  
{
	DECLARE_SERIAL_DLL(COutput)
public:
	virtual void Serialize(CArchive &ar);
	COutput();
	COutput(long i,CString *name) : CGOutput(i,name) {};
	COutput(long i) : CGOutput(i) {};
	virtual ~COutput();

};

#endif // !defined(AFX_OUTPUT_H__180CFD64_30A5_4D8A_88B8_2D049EF76381__INCLUDED_)
