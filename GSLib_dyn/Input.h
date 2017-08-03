// Input.h: interface for the CInput class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright 2005 Gabriel Dimitriu

	This file is part of Generic Simulator.
	This file contains the definition of an input port.
	
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
#if !defined(AFX_INPUT_H__74B14731_FFEF_42F9_8EAC_4F17CFAA1DBA__INCLUDED_)
#define AFX_INPUT_H__74B14731_FFEF_42F9_8EAC_4F17CFAA1DBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GInput.h"

using namespace std ;

class DllExport CInput : public CGInput  
{
	DECLARE_SERIAL_DLL(CInput)
public:
	virtual void Serialize(CArchive &ar);
	CInput();
	CInput(long i) : CGInput(i) {};
	CInput(long i,CString *name) : CGInput(i,name) {};
	virtual ~CInput();

};

#endif // !defined(AFX_INPUT_H__74B14731_FFEF_42F9_8EAC_4F17CFAA1DBA__INCLUDED_)
