// functionality.h: interface for the Cfunctionality class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright 2005 Gabriel Dimitriu

	This file is part of Generic Simulator.
	This class implements basic functionality examples.
	
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
#if !defined(AFX_FUNCTIONALITY_H__14255D22_1FBB_11DB_B910_E5C9589B8F0A__INCLUDED_)
#define AFX_FUNCTIONALITY_H__14255D22_1FBB_11DB_B910_E5C9589B8F0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <GSLib.h>
#include "Transition.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std ;

class Cfunctionality : public CObject  
{
public:
	void SetFunc(CComboBox *func);
	void run(CComboBox *func);
	Cfunctionality();
	virtual ~Cfunctionality();
private:
	void testDQL();
	void testDQL_2();
	void testDQL_2_S();
	void testDistributions_2();
	void testSum();
	void testmprocsn();
	void testcps();
	void testmprocs();
	void testMDM();
	void testDistributions();
	//tests for functionality
	void test1_01();
	void test1_02();
	void testBuses();
};

#endif // !defined(AFX_FUNCTIONALITY_H__14255D22_1FBB_11DB_B910_E5C9589B8F0A__INCLUDED_)
