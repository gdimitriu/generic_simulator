// Transition1.cpp: implementation of the CTransition1 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Transition1.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
IMPLEMENT_SERIAL(CTransition1,CGTransition,1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTransition1::CTransition1()
{

}
CTransition1::CTransition1(CString *val):CGTransition(val)
{
	m_ememory=false;
}
CTransition1::~CTransition1()
{

}

void CTransition1::proc_deltaext(CGProcessor *proc, CGData *data, long *s, CObArray *value, CObArray *value_n, long nr)
{
	((element *)value->GetAt(0))->data[0]=((element *)value->GetAt(0))->data[0]+data->Get();
	proc->SettL(proc->GetTime());
	proc->SettN(proc->GetTime()+m_repartition->generate());
}

void CTransition1::proc_deltaint(CGProcessor *proc, long *s, CObArray *value, CObArray *value_n, long nr)
{
	((element *)value->GetAt(0))->data[0]=((element *)value->GetAt(0))->data[0]+0.5;
	proc->SettL(proc->GetTime());
	proc->SettN(proc->GetTime()+m_repartition->generate());
}

void CTransition1::proc_redone(CGProcessor *proc, long *s, long *sL, CObArray *value, CObArray *value_n)
{
	//cout<<"redone at time="<<proc->GetTime()<<endl;cout.flush(); 
	//redone the processor settings to previous ones
	proc->SettN(proc->GetPrevTime());
	proc->SettL(proc->GetLLTime());
	((element *)value->GetAt(0))->data[0]-=0.5;
	*s=*sL;
}

void CTransition1::Serialize(CArchive &ar)
{
	CGTransition::Serialize(ar);
}
