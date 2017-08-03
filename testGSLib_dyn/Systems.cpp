// Systems.cpp: implementation of the CSystems class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Systems.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSystems::CSystems()
{

}

CSystems::~CSystems()
{

}

void CSystems::SetFunc(CComboBox *func)
{
	func->AddString(_T("testS_1"));
	func->AddString(_T("testS_2"));
}

void CSystems::run(CComboBox *func)
{
	int index=func->GetCurSel();
	switch(index)
	{
		case 0:
			testS_1();
			break;
		case 1:
			testS_2();
			break;
		case CB_ERR:
			break;
	}
}

void CSystems::testS_1()
{
	CGNetworkS *net,*net0,*net1;
	CGProcessor *proc;
	CGOutput *pout;
	CGInput *pin;
	CGInput **ppin;
	CGTransition *trans;

	CString *a;
	ppin=(CGInput **)calloc(2,sizeof(CGInput *));
	
	//master network
	net=new CGNetworkS(0);
	
	a=new CString("o2.dat");
	pout=new CGOutput(2,a);
	pout->SetDim(1);
	net->AddPort(pout,false);
	a=new CString("o3.dat");
	pout=new CGOutput(3,a);
	pout->SetDim(1);
	net->AddPort(pout,false);

	a=new CString("i0.dat");
	pin=new CGInput(0,a);
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	pin->SetDim(1);
	ppin[0]=pin;
	net->AddPort(pin,true);

	a=new CString("i1.dat");
	pin=new CGInput(1,a);
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	pin->SetDim(1);
	ppin[1]=pin;
	net->AddPort(pin,true);
	
	//second network
	net1=new CGNetworkS(1);
	net->AddNetwork(net1);
	pout=new CGOutput(1);
	pout->SetDim(1);
	net1->AddPort(pout,false);
	pout=new CGOutput(2);
	pout->SetDim(1);
	net1->AddPort(pout,false);
	a=new CString("int.dat");
	pin=new CGInput(0);
	pin->SetDim(1);
	net1->AddPort(pin,true);
	//wires
	net->AddParentNet(2,1,1,1);
	net->AddParentNet(3,2,1,1);

	CGDistributionSecv *dsecv;
	dsecv=new CGDistributionSecv(0,false);
	pin=new CGInput(0);
	pin->SetDim(1);
	dsecv->AddPort(pin,true);
	pout=new CGOutput(1);
	pout->SetDim(1);
	dsecv->AddPort(pout,false);
	pout=new CGOutput(2);
	pout->SetDim(1);
	dsecv->AddPort(pout,false);
	
	net1->AddProcP(dsecv);

	//first processor
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(1,trans);
	proc->SetRType(false);
	pin=new CInput(0);
	proc->AddPort(pin,true);
	pout=new COutput(1);
	proc->AddPort(pout,false);
	trans->Set(1);
	trans->set_extfunc("x0[0]+y1[0]",1);
	trans->set_intfunc("y1[0]+0.5",1);
	net1->AddProc(proc);

	//second processor
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(2,trans);
	proc->SetRType(false);
	pin=new CInput(0);
	proc->AddPort(pin,true);
	pout=new COutput(1);
	proc->AddPort(pout,false);
	trans->Set(1);
	trans->set_extfunc("x0[0]+y1[0]",1);
	trans->set_intfunc("y1[0]+0.5",1);
	net1->AddProc(proc);

	//add wires at second network
	net1->AddParentProc(0,0,0,0);
	net1->AddProcProc(0,1,1,0);
	net1->AddProcProc(0,2,2,0);
	net1->AddParentProc(1,1,1,1);
	net1->AddParentProc(2,1,2,1);
	
	//first network
	net0=new CGNetworkS(0);
	net->AddNetwork(net0);
	pin=new CInput(1);
	net0->AddPort(pin,true);
	pin=new CInput(2);
	net0->AddPort(pin,true);
	pout=new COutput(0);
	net0->AddPort(pout,false);

	CGDistributionBus *bus;
	bus=new CGDistributionBus(0,true); // M to 1
	bus->SetType(false);
	bus->SetSN(true);
	pout=new CGOutput(0);
	pout->SetDim(1);
	bus->AddPort(pout,false);
	pin=new CGInput(1);
	bus->AddPort(pin,true);
	pin=new CGInput(2);
	bus->AddPort(pin,true);
	net0->AddProcP(bus);
	//wire from at first network
	net0->AddParentProc(0,0,0,1);
	net0->AddParentProc(1,1,0,0);
	net0->AddParentProc(2,2,0,0);
	net->AddParentNet(0,1,0,0);
	net->AddParentNet(1,2,0,0);
	net->AddNetworkNetwork(0,0,1,0);
	//test vectors
	//net->DisableCoord();
	net0->DisableCoord();
	net1->DisableCoord();
	net->receivemsg(0,0,NULL);

	ppin[0]->SetTime(0);
	ppin[0]->SetWTime(0);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,0,NULL);
	net->receivemsg(1,0,NULL);
	net->receivemsg(1,1,NULL);
	ppin[1]->SetTime(2);
	ppin[1]->SetWTime(2);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,2,NULL);
	net->receivemsg(1,2,NULL);
	net->receivemsg(1,3,NULL);
	ppin[0]->SetTime(4);
	ppin[0]->SetWTime(4);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,4,NULL);
	net->receivemsg(1,4,NULL);
	net->receivemsg(1,5,NULL);
	ppin[1]->SetTime(6);
	ppin[1]->SetWTime(6);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,6,NULL);
	net->receivemsg(1,6,NULL);
	net->receivemsg(1,7,NULL);
	ppin[0]->SetTime(8);
	ppin[0]->SetWTime(8);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,8,NULL);
	net->receivemsg(1,8,NULL);
	net->receivemsg(1,9,NULL);
	net->PrintData();
	delete net;
}

void CSystems::testS_2()
{
	CGNetworkS *net,*net0,*net1;
	CGProcessor *proc;
	CGOutput *pout;
	CGInput *pin;
	CGInput **ppin;
	CGTransition *trans;
	CGDistributionBus *bus;

	CString *a;
	ppin=(CGInput **)calloc(2,sizeof(CGInput *));
	
	//master network
	net=new CGNetworkS(0);
	
	a=new CString("o3.dat");
	pout=new CGOutput(3,a);
	pout->SetDim(1);
	net->AddPort(pout,false);
	a=new CString("o4.dat");
	pout=new CGOutput(4,a);
	pout->SetDim(1);
	net->AddPort(pout,false);

	a=new CString("i0.dat");
	pin=new CGInput(0,a);
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	pin->SetDim(1);
	ppin[0]=pin;
	net->AddPort(pin,true);

	a=new CString("i1.dat");
	pin=new CGInput(1,a);
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	pin->SetDim(1);
	ppin[1]=pin;
	net->AddPort(pin,true);

	a=new CString("i2.dat");
	pin=new CGInput(2,a);
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	pin->SetDim(1);
	ppin[2]=pin;
	net->AddPort(pin,true);
	
	//second network
	net1=new CGNetworkS(1);
	net->AddNetwork(net1);
	pout=new CGOutput(1);
	pout->SetDim(1);
	net1->AddPort(pout,false);
	pout=new CGOutput(2);
	pout->SetDim(1);
	net1->AddPort(pout,false);
	a=new CString("int.dat");
	pin=new CGInput(0);
	pin->SetDim(1);
	net1->AddPort(pin,true);
	//wires
	net->AddParentNet(3,1,1,1);
	net->AddParentNet(4,2,1,1);
	
	bus=new CGDistributionBus(0,true); //1 to M
	bus->SetType(true);
	bus->SetSN(true);
	a=new CString("int.dat");
	pin=new CGInput(0,a);
	pin->SetDim(1);
	bus->AddPort(pin,true);
	a=new CString("IO1.dat");
	pout=new CGOutput(1,a);
	bus->AddPort(pout,false);
	a=new CString("IO2.dat");
	pout=new CGOutput(2,a);
	bus->AddPort(pout,false);
	net1->AddProcP(bus);

	//first processor
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(1,trans);
	proc->SetRType(false);
	pin=new CInput(0);
	proc->AddPort(pin,true);
	pout=new COutput(1);
	proc->AddPort(pout,false);
	trans->Set(1);
	trans->set_extfunc("x0[0]+y1[0]",1);
	trans->set_intfunc("y1[0]+0.5",1);
	net1->AddProc(proc);

	//second processor
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(2,trans);
	proc->SetRType(false);
	pin=new CInput(0);
	proc->AddPort(pin,true);
	pout=new COutput(1);
	proc->AddPort(pout,false);
	trans->Set(1);
	trans->set_extfunc("x0[0]+y1[0]",1);
	trans->set_intfunc("y1[0]+0.5",1);
	net1->AddProc(proc);

	//add wires at second network
	net1->AddParentProc(0,0,0,0);
	net1->AddProcProc(0,1,1,0);
	net1->AddProcProc(0,2,2,0);
	net1->AddParentProc(1,1,1,1);
	net1->AddParentProc(2,1,2,1);
	
	//first network
	net0=new CGNetworkS(0);
	net->AddNetwork(net0);
	pin=new CInput(1);
	net0->AddPort(pin,true);
	pin=new CInput(2);
	net0->AddPort(pin,true);
	pin=new CInput(3);
	net0->AddPort(pin,true);
	pout=new COutput(0);
	net0->AddPort(pout,false);

	bus=new CGDistributionBus(0,true); // M to 1
	bus->SetType(false);
	bus->SetSN(true);
	bus->SetBypass(true);
	pout=new CGOutput(0);
	pout->SetDim(1);
	bus->AddPort(pout,false);
	pin=new CGInput(1);
	bus->AddPort(pin,true);
	pin=new CGInput(2);
	bus->AddPort(pin,true);
	pin=new CInput(3);
	bus->AddPort(pin,true);
	net0->AddProcP(bus);
	//wire from at first network
	net0->AddParentProc(0,0,0,1);
	net0->AddParentProc(1,1,0,0);
	net0->AddParentProc(2,2,0,0);
	net0->AddParentProc(3,3,0,0);
	net->AddParentNet(0,1,0,0);
	net->AddParentNet(1,2,0,0);
	net->AddParentNet(2,3,0,0);
	net->AddNetworkNetwork(0,0,1,0);
	//test vectors
	//net->DisableCoord();
	net0->DisableCoord();
	net1->DisableCoord();
	net->receivemsg(0,0,NULL);

	ppin[1]->SetTime(0);
	ppin[1]->SetWTime(0);
	ppin[1]->SetSourceName(1);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,0,NULL);
	net->receivemsg(1,0,NULL);
	net->receivemsg(1,1,NULL);
	ppin[2]->SetTime(2);
	ppin[2]->SetWTime(2);
	ppin[2]->SetSourceName(2);
	ppin[2]->Set();
	ppin[2]->RecvMsg(2,2,NULL);
	net->receivemsg(1,2,NULL);
	net->receivemsg(1,3,NULL);
	ppin[0]->SetTime(4);
	ppin[0]->SetWTime(4);
	ppin[0]->SetSourceName(1);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,4,NULL);
	net->receivemsg(1,4,NULL);
	net->receivemsg(1,5,NULL);
	ppin[1]->SetTime(6);
	ppin[1]->SetWTime(6);
	ppin[1]->SetSourceName(2);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,6,NULL);
	net->receivemsg(1,6,NULL);
	net->receivemsg(1,7,NULL);
	ppin[1]->SetTime(8);
	ppin[1]->SetWTime(8);
	ppin[1]->SetSourceName(1);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,8,NULL);
	net->receivemsg(1,8,NULL);
	net->receivemsg(1,9,NULL);
	net->PrintData();
	delete net;
}

