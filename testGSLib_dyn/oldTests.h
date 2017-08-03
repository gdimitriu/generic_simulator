// oldTests.h: interface for the ColdTests class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OLDTESTS_H__06D7A261_23A6_11DB_B910_A6069677060D__INCLUDED_)
#define AFX_OLDTESTS_H__06D7A261_23A6_11DB_B910_A6069677060D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <GSLib.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std ;

class ColdTests  
{
public:
	void run(CComboBox *func);
	void SetFunc(CComboBox *func);
	ColdTests();
	virtual ~ColdTests();
private:
	//tests for dynamic comportament
	void testan();
	void testap(); //test dynamic add processor
	void testdelap(); //test dynamic del and add processor
	void testdeln(); //test dynamic del network
	void test_copy_del_net_ref();
	void test_copy_del_net();
	void test_copy_proc();
	void test_copy_proc_ref();
};

#endif // !defined(AFX_OLDTESTS_H__06D7A261_23A6_11DB_B910_A6069677060D__INCLUDED_)
