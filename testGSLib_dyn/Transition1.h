// Transition1.h: interface for the CTransition1 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSITION1_H__8E768461_3FF9_11DB_B910_B9EE1346D908__INCLUDED_)
#define AFX_TRANSITION1_H__8E768461_3FF9_11DB_B910_B9EE1346D908__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <GTransition.h>

using namespace std ;

class CTransition1 : public CGTransition  
{
	DECLARE_SERIAL(CTransition1);
public:
	virtual void Serialize(CArchive &ar);
	CTransition1();
	CTransition1(CString *val);
	virtual ~CTransition1();
	virtual void proc_deltaext(CGProcessor *proc,CGData *data,long *s,CObArray *value,CObArray *value_n,long nr);
	virtual void proc_redone(CGProcessor *proc,long *s,long *sL,CObArray *value,CObArray *value_n);
	virtual void proc_deltaint(CGProcessor *proc,long *s,CObArray *value,CObArray *value_n,long nr);
};

#endif // !defined(AFX_TRANSITION1_H__8E768461_3FF9_11DB_B910_B9EE1346D908__INCLUDED_)
