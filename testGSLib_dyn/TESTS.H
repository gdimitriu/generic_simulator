// tests.h: interface for the Ctests class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTS_H__8719DB21_7C78_11DB_B910_C76199F8344C__INCLUDED_)
#define AFX_TESTS_H__8719DB21_7C78_11DB_B910_C76199F8344C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <GSLib.h>
#include "Transition.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std ;

class Ctests : public CObject  
{
public:
	void SetFunc(CComboBox *func);
	void run(CComboBox *func);
	Ctests();
	virtual ~Ctests();

private:
	void testCSTLineVD();
	void testCSTLineSD();
	CNetworkS *net;
	CGInput *pin;
	CGOutput *pout;
	CString *a;

	void testNorm();
	void testDotP();
	void testSMult();
	void testSum();
	void testGSum();
	void testGain_ND();
	void testGain();
};

#endif // !defined(AFX_TESTS_H__8719DB21_7C78_11DB_B910_C76199F8344C__INCLUDED_)
