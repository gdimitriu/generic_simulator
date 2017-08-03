// Systems.h: interface for the CSystems class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMS_H__86ED7901_3E74_11DB_B910_F64D92BE2672__INCLUDED_)
#define AFX_SYSTEMS_H__86ED7901_3E74_11DB_B910_F64D92BE2672__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <GSLib.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std ;

class CSystems : public CObject  
{
public:
	void SetFunc(CComboBox *func);
	void run(CComboBox *func);
	CSystems();
	virtual ~CSystems();

private:
	void testS_2();
	void testS_1();
};

#endif // !defined(AFX_SYSTEMS_H__86ED7901_3E74_11DB_B910_F64D92BE2672__INCLUDED_)
