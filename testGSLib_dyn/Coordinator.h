// Coordonator.h: interface for the CCoordonator class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright 2005 Gabriel Dimitriu

	This file is part of Generic Simulator.
	This file contains the definition of coordinator class. This class implements
	three examples.
	
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
#if !defined(AFX_COORDINATOR_H__AE08F665_A6D4_4E64_8238_2F48B6E434DD__INCLUDED_)
#define AFX_COORDINATOR_H__AE08F665_A6D4_4E64_8238_2F48B6E434DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

using namespace std ;

class CCoordinator : public CObject  
{
public:
	void Run();
	CCoordinator();
	virtual ~CCoordinator();
};

#endif // !defined(AFX_COORDONATOR_H__AE08F665_A6D4_4E64_8238_2F48B6E434DD__INCLUDED_)
