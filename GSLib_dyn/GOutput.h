// GOutput.h: interface for the CGOutput class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0

	This file is part of Generic Simulator.
	This file contains the definition of an output generic port.
	
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
#if !defined(AFX_GOUTPUT_H__1CDD5FE1_97C8_4863_98C6_65C482FE7523__INCLUDED_)
#define AFX_GOUTPUT_H__1CDD5FE1_97C8_4863_98C6_65C482FE7523__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GData.h"
#include <iostream>
#include <fstream>
#include "stdafx.h"

using namespace std ;

class DllExport CGOutput : public CGData  
{
	DECLARE_SERIAL_DLL(CGOutput)
public:
	virtual int IsKind();
	virtual void Serialize(CArchive &ar);
	void SetFName(CString *name);
	CGOutput(long i,CString *name);
	CGOutput(long i);
	CGOutput();
	virtual void Set(double *val);
	virtual void Reset();
	virtual void ResetG();
	virtual ~CGOutput();
protected:
	CString m_fname;
	ofstream m_out;
	bool m_file;
};

#endif // !defined(AFX_GOUTPUT_H__1CDD5FE1_97C8_4863_98C6_65C482FE7523__INCLUDED_)
