// GInput.h: interface for the CGInput class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0

	This file is part of Generic Simulator.
	This file contains the definition of an input generic port.
	
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

#if !defined(AFX_GINPUT_H__12F44664_691E_486D_8F83_DF2B64C7525B__INCLUDED_)
#define AFX_GINPUT_H__12F44664_691E_486D_8F83_DF2B64C7525B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afx.h>
#include <fstream>
#include "GRepartition.h"
#include "GData.h"
#include "stdafx.h"

class CGRepartition;

using namespace std ;

class DllExport CGInput : public CGData  
{
	DECLARE_SERIAL_DLL(CGInput)
public:
	void SetFName(CString *name);
	virtual int IsKind();
	virtual void Serialize(CArchive &ar);
	void SetGenerator(CString *var);
	void SetGenerator(CString *var,long i);
	virtual void Set(double *x);
	virtual void Set();
	CGInput();
	CGInput(long i);
	CGInput(long i,CString *name);
	virtual ~CGInput();
protected:
	CString m_fname;
	ofstream m_out;
	bool m_file;
	CGRepartition *m_generator;
};

#endif // !defined(AFX_GINPUT_H__12F44664_691E_486D_8F83_DF2B64C7525B__INCLUDED_)
