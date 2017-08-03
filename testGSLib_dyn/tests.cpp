// tests.cpp: implementation of the Ctests class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "tests.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Ctests::Ctests()
{

}

Ctests::~Ctests()
{

}

void Ctests::SetFunc(CComboBox *func)
{
	func->AddString(_T("testGain"));
	func->AddString(_T("testGain_ND"));
	func->AddString(_T("testGSum"));
	func->AddString(_T("testSum"));
	func->AddString(_T("testSMult"));
	func->AddString(_T("testDotP"));
	func->AddString(_T("testNorm"));
	func->AddString(_T("testCSTLineSD"));
	func->AddString(_T("testCSTLineVD"));
}

void Ctests::run(CComboBox *func)
{
	int index=func->GetCurSel();
	switch(index)
	{
		case 0:
			testGain();
			break;
		case 1:
			testGain_ND();
			break;
		case 2:
			testGSum();
			break;
		case 3:
			testSum();
			break;
		case 4:
			testSMult();
			break;
		case 5:
			testDotP();
			break;
		case 6:
			testNorm();
			break;
		case 7:
			testCSTLineSD();
			break;
		case 8:
			testCSTLineVD();
			break;
		case CB_ERR:
			return;
	}
	//simulations
	CSCoordinator *coord;
	coord=new CSCoordinator();
	coord->setParent(net);
	coord->InputData();
	coord->Run();
	delete coord;
	delete net;
}

void Ctests::testGain()
{
	CSGain *proc;

	//network
	net=new CNetworkS(0);
	a=new CString("0.dat");
	pin=new CGInput(0,a);
	net->AddPort(pin,true);
	a=new CString("1.dat");
	pin=new CGInput(1,a);
	pin->SetDim(2);
	net->AddPort(pin,true);
	a=new CString("2.dat");
	pin=new CGInput(2,a);
	pin->SetDim(2);
	net->AddPort(pin,true);
	a=new CString("3.dat");
	pout=new CGOutput(3,a);
	net->AddPort(pout,false);
	a=new CString("4.dat");
	pout=new CGOutput(4,a);
	pout->SetDim(2);
	net->AddPort(pout,false);
	a=new CString("5.dat");
	pout=new CGOutput(5,a);
	pout->SetDim(2);
	net->AddPort(pout,false);

	//processors
	proc=new CSGain(net,0,1,1,2.0);
	proc->SetDelay(0.5);
	net->AddProc(proc);
	net->AddParentProc(0,0,0,0);
	net->AddParentProc(3,1,0,1);

	proc=new CSGain(net,1,2,2,2.0);
	proc->SetDelay(0.5);
	proc->SetDimPort(0,2);
	proc->SetDimPort(1,2);
	proc->SetDimPort(2,2);
	proc->SetDimPort(3,2);
	net->AddProc(proc);
	net->AddParentProc(1,0,1,0);
	net->AddParentProc(2,1,1,0);
	net->AddParentProc(4,2,1,1);
	net->AddParentProc(5,3,1,1);

}

void Ctests::testGain_ND()
{
	CSProcessor *proc;

	//network
	net=new CNetworkS(0);
	a=new CString("0.dat");
	pin=new CGInput(0,a);
	pin->SetDim(1);
	net->AddPort(pin,true);
	a=new CString("1.dat");
	pin=new CGInput(1,a);
	pin->SetDim(2);
	net->AddPort(pin,true);
	a=new CString("6.dat");
	pout=new CGOutput(6,a);
	pout->SetDim(1);
	net->AddPort(pout,false);
	a=new CString("7.dat");
	pout=new CGOutput(7,a);
	pout->SetDim(2);
	net->AddPort(pout,false);
	a=new CString("2.dat");
	pin=new CGInput(2,a);
	net->AddPort(pin,true);
	a=new CString("3.dat");
	pin=new CGInput(3,a);
	net->AddPort(pin,true);
	a=new CString("8.dat");
	pout=new CGOutput(8,a);
	net->AddPort(pout,false);
	a=new CString("9.dat");
	pout=new CGOutput(9,a);
	net->AddPort(pout,false);
	a=new CString("4.dat");
	pin=new CGInput(4,a);
	pin->SetDim(2);
	net->AddPort(pin,true);
	a=new CString("5.dat");
	pin=new CGInput(5,a);
	pin->SetDim(2);
	net->AddPort(pin,true);
	a=new CString("10.dat");
	pout=new CGOutput(10,a);
	pout->SetDim(2);
	net->AddPort(pout,false);
	a=new CString("11.dat");
	pout=new CGOutput(11,a);
	pout->SetDim(2);
	net->AddPort(pout,false);
	
	//processors
	proc=new CSGain(net,0,1,1,2.0);
	net->AddProc(proc);
	net->AddParentProc(0,0,0,0);
	net->AddParentProc(6,1,0,1);
	
	proc=new CSGain(net,1,1,1,2.0);
	proc->SetDimPort(0,2);
	proc->SetDimPort(1,2);
	net->AddProc(proc);
	net->AddParentProc(1,0,1,0);
	net->AddParentProc(7,1,1,1);

	proc=new CSGain(net,2,2,2,2.0);
	net->AddProc(proc);
	net->AddParentProc(2,0,2,0);
	net->AddParentProc(3,1,2,0);
	net->AddParentProc(8,2,2,1);
	net->AddParentProc(9,3,2,1);

	proc=new CSGain(net,3,2,2,2.0);
	proc->SetDimPort(0,2);
	proc->SetDimPort(1,2);
	proc->SetDimPort(2,2);
	proc->SetDimPort(3,2);
	net->AddProc(proc);
	net->AddParentProc(4,0,3,0);
	net->AddParentProc(5,1,3,0);
	net->AddParentProc(10,2,3,1);
	net->AddParentProc(11,3,3,1);
}

void Ctests::testGSum()
{
	CGSum *sum;

	net=new CNetworkS(0);
	a=new CString("0.dat");
	pin=new CGInput(0,a);
	pin->SetDim(3);
	net->AddPort(pin,true);
	a=new CString("1.dat");
	pin=new CGInput(1,a);
	pin->SetDim(3);
	net->AddPort(pin,true);
	a=new CString("2.dat");
	pin=new CGInput(2,a);
	pin->SetDim(3);
	net->AddPort(pin,true);
	a=new CString("3.dat");
	pout=new CGOutput(3,a);
	pout->SetDim(3);
	net->AddPort(pout,false);
	sum=new CGSum(net,0,3,3,true);
	net->AddProcP(sum);
	net->AddParentProc(0,0,0,0);
	net->AddParentProc(1,1,0,0);
	net->AddParentProc(2,2,0,0);
	net->AddParentProc(3,3,0,1);
}

void Ctests::testSum()
{
	CGSum *sum;

	net=new CNetworkS(0);
	a=new CString("in0.dat");
	pin=new CGInput(0,a);
	a=new CString("1.0");
	pin->SetDim(2);
	net->AddPort(pin,true);
	delete a;
	a=new CString("in1.dat");
	pin=new CGInput(1,a);
	a=new CString("1.0");
	pin->SetDim(3);
	net->AddPort(pin,true);
	delete a;
	a=new CString("out.dat");
	pout=new CGOutput(2,a);
	net->AddPort(pout,false);
	a=new CString("outd.dat");
	pout=new CGOutput(3,a);
	pout->SetDim(3);
	net->AddPort(pout,false);

	sum=new CGSum(net,0,false);
	net->AddProcP(sum);
	pin=new CGInput(1);
	pin->SetDim(2);
	sum->AddPort(pin,true);
	pin=new CGInput(2);
	pin->SetDim(3);
	sum->AddPort(pin,true);
	pout=new CGOutput(0);
	pout->SetDim(3);
	sum->AddPort(pout,false);
	net->AddParentProc(0,1,0,0);
	net->AddParentProc(1,2,0,0);
	net->AddParentProc(3,0,0,1);

	sum=new CGSum(net,1,false);
	net->AddProcP(sum);
	pin=new CGInput(1);
	pin->SetDim(2);
	sum->AddPort(pin,true);
	pin=new CGInput(2);
	pin->SetDim(3);
	sum->AddPort(pin,true);
	pout=new CGOutput(0);
	pout->SetDim(1);
	sum->AddPort(pout,false);

	net->AddParentProc(0,1,1,0);
	net->AddParentProc(1,2,1,0);
	net->AddParentProc(2,0,1,1);
}

void Ctests::testSMult()
{
	CSMult *proc;

	net=new CNetworkS(0);
	a=new CString("0.dat");
	pin=new CGInput(0,a);
	pin->SetDim(3);
	net->AddPort(pin,true);
	a=new CString("1.dat");
	pin=new CGInput(1,a);
	pin->SetDim(3);
	net->AddPort(pin,true);
	a=new CString("2.dat");
	pin=new CGInput(2,a);
	pin->SetDim(3);
	net->AddPort(pin,true);
	a=new CString("3.dat");
	pout=new CGOutput(3,a);
	pout->SetDim(3);
	net->AddPort(pout,false);
	proc=new CSMult(net,0,3,3,true);
	net->AddProc(proc);
	net->AddParentProc(0,0,0,0);
	net->AddParentProc(1,1,0,0);
	net->AddParentProc(2,2,0,0);
	net->AddParentProc(3,3,0,1);
}

void Ctests::testDotP()
{
	CSDotP *proc;

	net=new CNetworkS(0);
	a=new CString("0.dat");
	pin=new CGInput(0,a);
	pin->SetDim(3);
	net->AddPort(pin,true);
	a=new CString("1.dat");
	pin=new CGInput(1,a);
	pin->SetDim(3);
	net->AddPort(pin,true);
	a=new CString("2.dat");
	pout=new CGOutput(2,a);
	net->AddPort(pout,false);
	
	proc=new CSDotP(net,0,3);
	net->AddProc(proc);
	net->AddParentProc(0,0,0,0);
	net->AddParentProc(1,1,0,0);
	net->AddParentProc(2,2,0,1);
}

void Ctests::testNorm()
{
	CSNorm *proc;
	net=new CNetworkS(0);
	a=new CString("0.dat");
	pin=new CGInput(0,a);
	pin->SetDim(2);
	net->AddPort(pin,true);
	a=new CString("1.dat");
	pout=new CGOutput(1,a);
	net->AddPort(pout,false);
	a=new CString("2.dat");
	pout=new CGOutput(2,a);
	net->AddPort(pout,false);
	a=new CString("3.dat");
	pout=new CGOutput(3,a);
	net->AddPort(pout,false);
	a=new CString("4.dat");
	pout=new CGOutput(4,a);
	net->AddPort(pout,false);

	//processors
	proc=new CSNorm(net,0,2,2);
	net->AddProc(proc);
	net->AddParentProc(0,0,0,0);
	net->AddParentProc(1,1,0,1);
	proc=new CSNorm(net,1,2,-1);
	net->AddProc(proc);
	net->AddParentProc(0,0,1,0);
	net->AddParentProc(2,1,1,1);
	proc=new CSNorm(net,2,2,1);
	net->AddProc(proc);
	net->AddParentProc(0,0,2,0);
	net->AddParentProc(3,1,2,1);
	proc=new CSNorm(net,3,2,3);
	net->AddProc(proc);
	net->AddParentProc(0,0,3,0);
	net->AddParentProc(4,1,3,1);
}

void Ctests::testCSTLineSD()
{
	CSTLineSD *proc;
	net=new CNetworkS(0);
	a=new CString("0.dat");
	pin=new CGInput(0,a);
	net->AddPort(pin,true);
	a=new CString("1.dat");
	pout=new CGOutput(1,a);
	net->AddPort(pout,false);
	proc=new CSTLineSD(net,0,1.0,1,false);
	net->AddProc(proc);
	net->AddParentProc(0,0,0,0);
	net->AddParentProc(1,1,0,1);
}

void Ctests::testCSTLineVD()
{
	CSTLineVD *proc;
	net=new CNetworkS(0);
	a=new CString("0.dat");
	pin=new CGInput(0,a);
	net->AddPort(pin,true);
	a=new CString("1.dat");
	pout=new CGOutput(1,a);
	net->AddPort(pout,false);
	a=new CString("1.5");
	proc=new CSTLineVD(net,0,1,a);
	delete a;
	net->AddProc(proc);
	net->AddParentProc(0,0,0,0);
	net->AddParentProc(1,1,0,1);
}


