// oldTests.cpp: implementation of the ColdTests class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "oldTests.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ColdTests::ColdTests()
{

}

ColdTests::~ColdTests()
{

}

void ColdTests::SetFunc(CComboBox *func)
{
	func->AddString(_T("test_copy_del_net"));
	func->AddString(_T("test_copy_del_net_ref"));
	func->AddString(_T("test_copy_proc"));
	func->AddString(_T("test_copy_proc_ref"));
	func->AddString(_T("testan"));
	func->AddString(_T("testap"));
	func->AddString(_T("testdelap"));
	func->AddString(_T("testdeln"));
}

void ColdTests::run(CComboBox *func)
{
	int index=func->GetCurSel();
	switch(index)
	{
		case 0:
			test_copy_del_net();
			break;
		case 1:
			test_copy_del_net_ref();
			break;
		case 2:
			test_copy_proc();
			break;
		case 3:
			test_copy_proc_ref();
			break;
		case 4:
			testan();
			break;
		case 5:
			testap();
			break;
		case 6:
			testdelap();
			break;
		case 7:
			testdeln();
			break;
		case CB_ERR:
			break;
	}
}

void ColdTests::testdelap()
{
	CGNetworkS *net;
	CGInput *pin;
	CGOutput *pout;
	CGData *pdel1;
	CGProcessor *proc;
	CGProcessor *procd;
	CString *a;
	CGTransition *trans;
	CGInput **ppin;

	//master network
	net=new CGNetworkS(0);
	net->SetTypeWire(false);
	ppin=(CGInput **)calloc(2,sizeof(CGInput *));
	//ports for network
	pin=new CGInput(0);
	ppin[0]=pin;
	a=new CString("2.0");
	pin->SetGenerator(a);
	delete a;
	net->AddPort(pin,true);
	pin=new CGInput(1);
	ppin[1]=pin;
	a=new CString("2.0");
	pin->SetGenerator(a);
	delete a;
	net->AddPort(pin,true);
	//output ports and files
	a=new CString("out2dap.dat");
	pout=new CGOutput(2,a);
	net->AddPort(pout,false);
	a=new CString("out3dap.dat");
	pout=new CGOutput(3,a);
	net->AddPort(pout,false);

	//first processor from network
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(0,trans);
	proc->SetFirst2(false);
	procd=proc;
	net->AddProc(proc);
	pin=new CGInput(0);
	proc->AddPort(pin,true);
	pin=new CGInput(1);
	pdel1=pin;
	proc->AddPort(pin,true);
	a=new CString("intdap.dat");
	pout=new CGOutput(2,a);
	proc->AddPort(pout,false);
	pout=new CGOutput(3);
	proc->AddPort(pout,false);
	trans->Set(1);
	trans->set_extfunc("y0[0]+x0[0]",0);
	trans->set_intfunc("y0[0]+0.5",0);
	trans->set_extfunc("y1[0]+x1[0]",1);
	trans->set_intfunc("y1[0]+0.5",1);

	//second processor from network
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(1,trans);
	proc->SetFirst2(false);
	net->AddProc(proc);
	pin=new CGInput(0);
	proc->AddPort(pin,true);
	pin=new CGInput(1);
	proc->AddPort(pin,true);
	pout=new CGOutput(2);
	proc->AddPort(pout,false);
	trans->Set(2);
	trans->set_extfunc("x0[0]+x1[0]+1",0);
	trans->set_intfunc("y0[0]+0.5",0);

	//add wires
	net->AddParentProc(0,0,0,0);
	net->AddParentProc(1,1,1,0);
	net->AddParentProc(1,1,0,0);
	net->AddParentProc(2,2,1,1);
	net->AddParentProc(3,3,0,1);
	net->AddProcProc(0,2,1,0);
	
	//test vectors
 	net->receivemsg(0,0.0,NULL);
	ppin[0]->SetTime(1.5);
	ppin[0]->SetWTime(1.5);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,1.5,NULL);
	ppin[1]->SetTime(1.5);
	ppin[1]->SetWTime(1.5);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,1.5,NULL);

	double time=1.5;
	while(time<8.0)
	{
		net->receivemsg(1,time,NULL);
		time=time+1;
	}

	procd->DelPort(pdel1);

	pin=new CGInput(1);
	procd->AddPort(pin,true);
	procd->set_extfunc("y1[0]+x1[0]",1);
	procd->set_intfunc("y1[0]+0.5",1);
	net->AddParentProc(1,1,0,0);

	ppin[0]->SetTime(8.0);
	ppin[0]->SetWTime(8.0);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,8.0,NULL);
	ppin[1]->SetTime(8.0);
	ppin[1]->SetWTime(8.0);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,8.0,NULL);

	while(time<16.0)
	{
		net->receivemsg(1,time,NULL);
		time=time+1;
	}
	net->PrintData();
	delete net;
}

void ColdTests::testap()
{
	CGNetworkS *net;
	CGInput *pin;
	CGOutput *pout;
	CGProcessor *proc;
	CString *a;
	CGTransition *trans;
	CGInput **ppin;

	//master network
	net=new CGNetworkS(0);
	net->SetTypeWire(false);
	ppin=(CGInput **)calloc(2,sizeof(CGInput *));
	//ports for network
	pin=new CGInput(0);
	ppin[0]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net->AddPort(pin,true);
	pin=new CGInput(1);
	ppin[1]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net->AddPort(pin,true);
	//output ports and files
	a=new CString("out3ap.dat");
	pout=new CGOutput(3,a);
	net->AddPort(pout,false);

	//first processor from network
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(0,trans);
	net->AddProc(proc);
	pin=new CGInput(0);
	proc->AddPort(pin,true);
	pin=new CGInput(1);
	proc->AddPort(pin,true);
	a=new CString("intap.dat");
	pout=new CGOutput(2,a);
	proc->AddPort(pout,false);
	pout=new CGOutput(3);
	proc->AddPort(pout,false);
	trans->Set(1);
	trans->set_extfunc("y0[0]+x0[0]",0);
	trans->set_intfunc("y0[0]+0.5",0);
	trans->set_extfunc("y1[0]+x1[0]",1);
	trans->set_intfunc("y1[0]+0.5",1);
	//add wires first proc
	net->AddParentProc(0,0,0,0);
	net->AddParentProc(1,1,0,0);
	net->AddParentProc(3,3,0,1);
	
	//new port for network
	a=new CString("out2ap.dat");
	pout=new CGOutput(2,a);
	net->AddPort(pout,false);

	//second processor from network
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(1,trans);
	a=new CString("in0ap.dat");
	pin=new CGInput(0,a);
	proc->AddPort(pin,true);
	a=new CString("in1ap.dat");
	pin=new CGInput(1,a);
	proc->AddPort(pin,true);
	pout=new CGOutput(2);
	proc->AddPort(pout,false);
	trans->Set(1);
	trans->set_extfunc("x0[0]+x1[0]+1",0);
	trans->set_intfunc("y0[0]+0.5",0);
	net->AddProc(proc);
	//add wires second proc
	net->AddParentProc(1,1,1,0);
	net->AddParentProc(2,2,1,1);
	net->AddProcProc(0,2,1,0);

	//test vectors
 	net->receivemsg(0,0.0,NULL);
	ppin[0]->SetTime(1);
	ppin[0]->SetWTime(1);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,1,NULL);
	ppin[1]->SetTime(1);
	ppin[1]->SetWTime(1);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,1,NULL);

	double time=1;
	while(time<4.0)
	{
		net->receivemsg(1,time,NULL);
		time=time+1;
	}

	while(time<9.0)
	{
		net->receivemsg(1,time,NULL);
		time=time+1;
	}
	net->PrintData();
	delete net;
}
void ColdTests::test_copy_proc()
{
	CNetworkS *net1,*net2,*net3;
	CInput *pin;
	COutput *pout;
	CProcessor *proc1,*proc2;
	CGProcessor *proc3,*proc4;
	CString *a;
	CGTransition *trans;
	//first network
	net1=new CNetworkS(1);
	pin=new CInput(0);
	net1->AddPort(pin,true);
	pin=new CInput(1);
	net1->AddPort(pin,true);
	pout=new COutput(2);
	net1->AddPort(pout,false);
	pout=new COutput(3);
	net1->AddPort(pout,false);
	//first processor from first network
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc1=new CProcessor(0,trans);
	net1->AddProc(proc1);
	pin=new CInput(0);
	proc1->AddPort(pin,true);
	pout=new COutput(1);
	proc1->AddPort(pout,false);
	proc1->SetFirst(true);
	trans->Set(1);
	trans->set_extfunc("y0[0]+x0[0]",0);
	trans->set_intfunc("y0[0]+0.5",0);

	//second processor from first network
	a=new CString("2.0");
	trans=new CGTransition(a);
	delete a;
	proc2=new CProcessor(1,trans);
	net1->AddProc(proc2);
	pin=new CInput(0);
	proc2->AddPort(pin,true);
	pout=new COutput(1);
	proc2->AddPort(pout,false);
	trans->Set(2);
	trans->set_extfunc("y0[0]+x0[0]",0);
	trans->set_intfunc("y0[0]+0.5",0);

	//add wires
	net1->AddParentProc(0,0,0,0);
	net1->AddParentProc(3,1,0,1);
	net1->AddParentProc(1,0,1,0);
	net1->AddParentProc(2,1,1,1);

	//second network
	net2=new CNetworkS(2);
	pin=new CInput(0);
	net2->AddPort(pin,true);
	pin=new CInput(1);
	net2->AddPort(pin,true);
	pout=new COutput(2);
	net2->AddPort(pout,false);
	pout=new COutput(3);
	net2->AddPort(pout,false);

	//first copy processor from second network
	proc3=proc1->copy(net2);
	net2->AddProc(proc3);

	//second copy processor from second network
	proc4=proc2->copy(net2);
	net2->AddProc(proc4);

	//add wires
	net2->AddParentProc(0,0,0,0);
	net2->AddParentProc(3,1,0,1);
	net2->AddParentProc(1,0,1,0);
	net2->AddParentProc(2,1,1,1);

	//third network
	net3=new CNetworkS(3);
	CGInput **ppin;
	ppin=(CGInput **)calloc(4,sizeof(CGInput *));
	//input ports and sources for third network
	pin=new CInput(0);
	ppin[0]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net3->AddPort(pin,true);
	pin=new CInput(1);
	ppin[1]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net3->AddPort(pin,true);
	pin=new CInput(2);
	ppin[2]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net3->AddPort(pin,true);
	pin=new CInput(3);
	ppin[3]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net3->AddPort(pin,true);
	//output ports and files
	a=new CString("out4cp.dat");
	pout=new COutput(4,a);
	net3->AddPort(pout,false);
	a=new CString("out5cp.dat");
	pout=new COutput(5,a);
	net3->AddPort(pout,false);
	a=new CString("out6cp.dat");
	pout=new COutput(6,a);
	net3->AddPort(pout,false);
	a=new CString("out7cp.dat");
	pout=new COutput(7,a);
	net3->AddPort(pout,false);
	//wires for third network
	net3->AddNetwork(net1);
	net3->AddNetwork(net2);
	net3->AddParentNet(0,0,2,0);
	net3->AddParentNet(1,1,2,0);
	net3->AddParentNet(6,2,2,1);
	net3->AddParentNet(7,3,2,1);
	net3->AddParentNet(2,0,1,0);
	net3->AddParentNet(3,1,1,0);
	net3->AddParentNet(4,2,1,1);
	net3->AddParentNet(5,3,1,1);

	//test vectors
	net3->receivemsg(0,0,NULL);
	ppin[0]->SetTime(1);
	ppin[0]->SetWTime(1);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,1,NULL);
	ppin[1]->SetTime(1);
	ppin[1]->SetWTime(1);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,1,NULL);
	ppin[2]->SetTime(1);
	ppin[2]->SetWTime(1);
	ppin[2]->Set();
	ppin[2]->RecvMsg(2,1,NULL);
	ppin[3]->SetTime(1);
	ppin[3]->SetWTime(1);
	ppin[3]->Set();
	ppin[3]->RecvMsg(2,1,NULL);
	net3->receivemsg(1,1,NULL);
	net3->receivemsg(1,2,NULL);
	net3->receivemsg(1,3,NULL);
	net3->receivemsg(1,4,NULL);
	net3->receivemsg(1,5,NULL);
	net3->receivemsg(1,6,NULL);
	ppin[0]->SetTime(7);
	ppin[0]->SetWTime(7);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,7,NULL);
	ppin[1]->SetTime(7);
	ppin[1]->SetWTime(7);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,7,NULL);
	ppin[2]->SetTime(7);
	ppin[2]->SetWTime(7);
	ppin[2]->Set();
	ppin[2]->RecvMsg(2,7,NULL);
	ppin[3]->SetTime(7);
	ppin[3]->SetWTime(7);
	ppin[3]->Set();
	ppin[3]->RecvMsg(2,7,NULL);
	net3->receivemsg(1,7,NULL);
	net3->receivemsg(1,8,NULL);
	net3->receivemsg(1,9,NULL);
	net3->receivemsg(1,10,NULL);
	net3->receivemsg(1,11,NULL);
	net3->receivemsg(1,12,NULL);
	net3->receivemsg(3,12,NULL);
	net3->PrintData();
	delete net3;
}

void ColdTests::test_copy_proc_ref()
{
	CNetworkS *net1,*net2,*net3;
	CInput *pin;
	COutput *pout;
	CProcessor *proc1,*proc2;
	CString *a;
	CGTransition *trans;
	//first network
	net1=new CNetworkS(1);
	pin=new CInput(0);
	net1->AddPort(pin,true);
	pin=new CInput(1);
	net1->AddPort(pin,true);
	pout=new COutput(2);
	net1->AddPort(pout,false);
	pout=new COutput(3);
	net1->AddPort(pout,false);
	//first processor from first network
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc1=new CProcessor(0,trans);
	net1->AddProc(proc1);
	pin=new CInput(0);
	proc1->AddPort(pin,true);
	pout=new COutput(1);
	proc1->AddPort(pout,false);
	proc1->SetFirst(true);
	trans->Set(1);
	trans->set_extfunc("y0[0]+x0[0]",0);
	trans->set_intfunc("y0[0]+0.5",0);

	//second processor from first network
	a=new CString("2.0");
	trans=new CGTransition(a);
	delete a;
	proc2=new CProcessor(1,trans);
	net1->AddProc(proc2);
	pin=new CInput(0);
	proc2->AddPort(pin,true);
	pout=new COutput(1);
	proc2->AddPort(pout,false);
	trans->Set(2);
	trans->set_extfunc("y0[0]+x0[0]",0);
	trans->set_intfunc("y0[0]+0.5",0);

	//add wires
	net1->AddParentProc(0,0,0,0);
	net1->AddParentProc(3,1,0,1);
	net1->AddParentProc(1,0,1,0);
	net1->AddParentProc(2,1,1,1);

	//second network
	net2=new CNetworkS(2);
	pin=new CInput(0);
	net2->AddPort(pin,true);
	pin=new CInput(1);
	net2->AddPort(pin,true);
	pout=new COutput(2);
	net2->AddPort(pout,false);
	pout=new COutput(3);
	net2->AddPort(pout,false);

	//first processor from second network
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc1=new CProcessor(0,trans);
	pin=new CInput(0);
	proc1->AddPort(pin,true);
	pout=new COutput(1);
	proc1->AddPort(pout,false);
	trans->Set(1);
	trans->set_extfunc("y0[0]+x0[0]",0);
	trans->set_intfunc("y0[0]+0.5",0);

	net2->AddProc(proc1);

	//second processor from second network
	a=new CString("2.0");
	trans=new CGTransition(a);
	delete a;
	proc2=new CProcessor(1,trans);
	pin=new CInput(0);
	proc2->AddPort(pin,true);
	pout=new COutput(1);
	proc2->AddPort(pout,false);
	trans->Set(2);
	trans->set_extfunc("y0[0]+x0[0]",0);
	trans->set_intfunc("y0[0]+0.5",0);

	net2->AddProc(proc2);

	//add wires
	net2->AddParentProc(0,0,0,0);
	net2->AddParentProc(3,1,0,1);
	net2->AddParentProc(1,0,1,0);
	net2->AddParentProc(2,1,1,1);

	//third network
	net3=new CNetworkS(3);
	CGInput **ppin;
	ppin=(CGInput **)calloc(4,sizeof(CGInput *));
	//input ports and sources for third network
	pin=new CInput(0);
	ppin[0]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net3->AddPort(pin,true);
	pin=new CInput(1);
	ppin[1]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net3->AddPort(pin,true);
	pin=new CInput(2);
	ppin[2]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net3->AddPort(pin,true);
	pin=new CInput(3);
	ppin[3]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net3->AddPort(pin,true);
	//output ports and files
	a=new CString("out4cpr.dat");
	pout=new COutput(4,a);
	net3->AddPort(pout,false);
	a=new CString("out5cpr.dat");
	pout=new COutput(5,a);
	net3->AddPort(pout,false);
	a=new CString("out6cpr.dat");
	pout=new COutput(6,a);
	net3->AddPort(pout,false);
	a=new CString("out7cpr.dat");
	pout=new COutput(7,a);
	net3->AddPort(pout,false);
	//wires for third network
	net3->AddNetwork(net1);
	net3->AddNetwork(net2);
	net3->AddParentNet(0,0,2,0);
	net3->AddParentNet(1,1,2,0);
	net3->AddParentNet(6,2,2,1);
	net3->AddParentNet(7,3,2,1);
	net3->AddParentNet(2,0,1,0);
	net3->AddParentNet(3,1,1,0);
	net3->AddParentNet(4,2,1,1);
	net3->AddParentNet(5,3,1,1);

	//test vectors
	net3->receivemsg(0,0,NULL);
	ppin[0]->SetTime(1);
	ppin[0]->SetWTime(1);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,1,NULL);
	ppin[1]->SetTime(1);
	ppin[1]->SetWTime(1);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,1,NULL);
	ppin[2]->SetTime(1);
	ppin[2]->SetWTime(1);
	ppin[2]->Set();
	ppin[2]->RecvMsg(2,1,NULL);
	ppin[3]->SetTime(1);
	ppin[3]->SetWTime(1);
	ppin[3]->Set();
	ppin[3]->RecvMsg(2,1,NULL);
	net3->receivemsg(1,1,NULL);
	net3->receivemsg(1,2,NULL);
	net3->receivemsg(1,3,NULL);
	net3->receivemsg(1,4,NULL);
	net3->receivemsg(1,5,NULL);
	net3->receivemsg(1,6,NULL);
	ppin[0]->SetTime(7);
	ppin[0]->SetWTime(7);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,7,NULL);
	ppin[1]->SetTime(7);
	ppin[1]->SetWTime(7);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,7,NULL);
	ppin[2]->SetTime(7);
	ppin[2]->SetWTime(7);
	ppin[2]->Set();
	ppin[2]->RecvMsg(2,7,NULL);
	ppin[3]->SetTime(7);
	ppin[3]->SetWTime(7);
	ppin[3]->Set();
	ppin[3]->RecvMsg(2,7,NULL);
	net3->receivemsg(1,7,NULL);
	net3->receivemsg(1,8,NULL);
	net3->receivemsg(1,9,NULL);
	net3->receivemsg(1,10,NULL);
	net3->receivemsg(1,11,NULL);
	net3->receivemsg(1,12,NULL);
	net3->receivemsg(3,12,NULL);
	net3->PrintData();
	delete net3;
}

//from here we test networks
void ColdTests::testdeln()
{
	CGNetworkS *net,*net1;
	CGInput *pin;
	CGOutput *pout;
	CGData *pdel1,*pdel2,*pdel3;
	CGProcessor *proc;
	CGProcessor *procd;
	CString *a;
	CGTransition *trans;
	CGInput **ppin;

	//master network
	net=new CGNetworkS(0);
	net->SetTypeWire(false);
	ppin=(CGInput **)calloc(2,sizeof(CGInput *));
	//ports for network
	pin=new CGInput(0);
	ppin[0]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net->AddPort(pin,true);
	pin=new CGInput(1);
	ppin[1]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net->AddPort(pin,true);
	//output ports and files
	a=new CString("out2n.dat");
	pout=new CGOutput(2,a);
	net->AddPort(pout,false);
	a=new CString("out3n.dat");
	pout=new CGOutput(3,a);
	net->AddPort(pout,false);

	//processor from master network
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(0,trans);
	procd=proc;
	net->AddProc(proc);
	pin=new CGInput(0);
	proc->AddPort(pin,true);
	pin=new CGInput(1);
	pdel1=pin;
	proc->AddPort(pin,true);
	a=new CString("intn.dat");
	pout=new CGOutput(2,a);
	pdel2=pout;
	proc->AddPort(pout,false);
	pout=new CGOutput(3);
	pdel3=pout;
	proc->AddPort(pout,false);
	trans->Set(1);
	trans->set_extfunc("y0[0]+x0[0]",0);
	trans->set_intfunc("y0[0]+0.5",0);
	trans->set_extfunc("y1[0]+x1[0]",1);
	trans->set_intfunc("y1[0]+0.5",1);

	//slave network
	net1=new CGNetworkS(1);
	net1->SetTypeWire(false);
	//ports for network
	pin=new CGInput(0);
	net1->AddPort(pin,true);
	pin=new CGInput(1);
	net1->AddPort(pin,true);
	//output ports and files
	pout=new CGOutput(2);
	net1->AddPort(pout,false);
	
	net->AddNetwork(net1);

	//processor from slave network
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(0,trans);
	net1->AddProc(proc);
	pin=new CGInput(0);
	proc->AddPort(pin,true);
	pin=new CGInput(1);
	proc->AddPort(pin,true);
	pout=new CGOutput(2);
	proc->AddPort(pout,false);
	trans->Set(2);
	trans->set_extfunc("x0[0]+x1[0]+1",0);
	trans->set_intfunc("y0[0]+0.5",0);

	//add slave wire
	net1->AddParentProc(0,0,0,0);
	net1->AddParentProc(1,1,0,0);
	net1->AddParentProc(2,2,0,1);
	//add master wires
	net->AddParentProc(0,0,0,0);
	net->AddParentProc(1,1,0,0);
	net->AddParentProc(3,3,0,1);
	net->AddParentNet(1,1,1,0);
	net->AddParentNet(2,2,1,1);
	net->AddProcNetwork(0,2,1,0);
	
	//test vectors
 	net->receivemsg(0,0.0,NULL);
	ppin[0]->SetTime(1);
	ppin[0]->SetWTime(1);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,1,NULL);
	ppin[1]->SetTime(1);
	ppin[1]->SetWTime(1);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,1,NULL);

	double time=1;
	while(time<4.0)
	{
		net->receivemsg(1,time,NULL);
		time=time+1;
	}
	
//	net->DelNet(net1);
//	procd->DelPort(pdel1);

	while(time<9.0)
	{
		net->receivemsg(1,time,NULL);
		time=time+1;
	}
	net->PrintData();
	delete net;
}

void ColdTests::testan()
{
	CGNetworkS *net,*net1;
	CGInput *pin;
	CGOutput *pout;
	CGProcessor *proc;
	CString *a;
	CGTransition *trans;
	CGInput **ppin;

	//master network
	net=new CGNetworkS(0);
	net->SetTypeWire(false);
	ppin=(CGInput **)calloc(2,sizeof(CGInput *));
	//ports for network
	pin=new CGInput(0);
	ppin[0]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net->AddPort(pin,true);
	pin=new CGInput(1);
	ppin[1]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net->AddPort(pin,true);
	//output ports and files
	a=new CString("out3an.dat");
	pout=new CGOutput(3,a);
	net->AddPort(pout,false);

	//first processor from network
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(0,trans);
	net->AddProc(proc);
	pin=new CGInput(0);
	proc->AddPort(pin,true);
	pin=new CGInput(1);
	proc->AddPort(pin,true);
	a=new CString("intan.dat");
	pout=new CGOutput(2,a);
	proc->AddPort(pout,false);
	pout=new CGOutput(3);
	proc->AddPort(pout,false);
	trans->Set(1);
	trans->set_extfunc("y0[0]+x0[0]",0);
	trans->set_intfunc("y0[0]+0.5",0);
	trans->set_extfunc("y1[0]+x1[0]",1);
	trans->set_intfunc("y1[0]+0.5",1);
	//add wires first proc
	net->AddParentProc(0,0,0,0);
	net->AddParentProc(1,1,0,0);
	net->AddParentProc(3,3,0,1);
	
	//new port for network
	a=new CString("out2an.dat");
	pout=new CGOutput(2,a);
	net->AddPort(pout,false);

	//slave network
	net1=new CGNetworkS(1);
	net1->SetTypeWire(false);
	//ports for network
	pin=new CGInput(0);
	net1->AddPort(pin,true);
	pin=new CGInput(1);
	net1->AddPort(pin,true);
	//output ports and files
	pout=new CGOutput(2);
	net1->AddPort(pout,false);
	
	//processor from slave network
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(0,trans);
	a=new CString("in0an.dat");
	pin=new CGInput(0,a);
	proc->AddPort(pin,true);
	a=new CString("in1an.dat");
	pin=new CGInput(1,a);
	proc->AddPort(pin,true);
	pout=new CGOutput(2);
	proc->AddPort(pout,false);
	trans->Set(1);
	trans->set_extfunc("x0[0]+x1[0]+1",0);
	trans->set_intfunc("y0[0]+0.5",0);
	net1->AddProc(proc);

	//add slave wire
	net1->AddParentProc(0,0,0,0);
	net1->AddParentProc(1,1,0,0);
	net1->AddParentProc(2,2,0,1);
	
	net->AddNetwork(net1);
	//wire for second network
	net->AddParentNet(1,1,1,0);
	net->AddParentNet(2,2,1,1);
	net->AddProcNetwork(0,2,1,0);

	//test vectors
 	net->receivemsg(0,0.0,NULL);
	ppin[0]->SetTime(1);
	ppin[0]->SetWTime(1);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,1,NULL);
	ppin[1]->SetTime(1);
	ppin[1]->SetWTime(1);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,1,NULL);

	double time=1;
	while(time<4.0)
	{
		net->receivemsg(1,time,NULL);
		time=time+1;
	}

	while(time<9.0)
	{
		net->receivemsg(1,time,NULL);
		time=time+1;
	}
	net->PrintData();
	delete net;
}

void ColdTests::test_copy_del_net()
{
	CGNetworkS *net1,*net2,*net3;
	CGInput *pin;
	CGOutput *pout;
	CGProcessor *proc;
	CString *a;
	CGTransition *trans;
	//third network (master network)
	net3=new CGNetworkS(3);
	CGInput **ppin;
	ppin=(CGInput **)calloc(4,sizeof(CGInput *));
	//input ports and sources for third network
	pin=new CGInput(0);
	ppin[0]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net3->AddPort(pin,true);
	pin=new CGInput(1);
	ppin[1]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net3->AddPort(pin,true);
	pin=new CGInput(2);
	ppin[2]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net3->AddPort(pin,true);
	pin=new CGInput(3);
	ppin[3]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net3->AddPort(pin,true);
	//output ports and files
	a=new CString("out4cn.dat");
	pout=new CGOutput(4,a);
	net3->AddPort(pout,false);
	a=new CString("out5cn.dat");
	pout=new CGOutput(5,a);
	net3->AddPort(pout,false);
	a=new CString("out6cn.dat");
	pout=new CGOutput(6,a);
	net3->AddPort(pout,false);
	a=new CString("out7cn.dat");
	pout=new CGOutput(7,a);
	net3->AddPort(pout,false);

	//first network
	net1=new CGNetworkS(1);
	pin=new CGInput(0);
	net1->AddPort(pin,true);
	pin=new CGInput(1);
	net1->AddPort(pin,true);
	pout=new CGOutput(2);
	net1->AddPort(pout,false);
	pout=new CGOutput(3);
	net1->AddPort(pout,false);
	//first processor from first network
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(0,trans);
	net1->AddProc(proc);
	pin=new CGInput(0);
	proc->AddPort(pin,true);
	pout=new CGOutput(1);
	proc->AddPort(pout,false);
	proc->SetFirst(true);
	trans->Set(1);
	trans->set_extfunc("y0[0]+x0[0]",0);
	trans->set_intfunc("y0[0]+0.5",0);

	//second processor from first network
	a=new CString("2.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(1,trans);
	net1->AddProc(proc);
	pin=new CGInput(0);
	proc->AddPort(pin,true);
	pout=new CGOutput(1);
	proc->AddPort(pout,false);
	proc->SetFirst(true);
	trans->Set(2);
	trans->set_extfunc("y0[0]+x0[0]",0);
	trans->set_intfunc("y0[0]+0.5",0);

	//add wires
	net1->AddParentProc(0,0,0,0);
	net1->AddParentProc(3,1,0,1);
	net1->AddParentProc(1,0,1,0);
	net1->AddParentProc(2,1,1,1);
	
	net2=net1->copy(net3,2);

	
	//wires for third network
	net3->AddNetwork(net1);
	net3->AddNetwork(net2);
	net3->AddParentNet(0,0,2,0);
	net3->AddParentNet(1,1,2,0);
	net3->AddParentNet(6,2,2,1);
	net3->AddParentNet(7,3,2,1);
	net3->AddParentNet(2,0,1,0);
	net3->AddParentNet(3,1,1,0);
	net3->AddParentNet(4,2,1,1);
	net3->AddParentNet(5,3,1,1);

	//test vectors
	net3->receivemsg(0,0,NULL);
	ppin[0]->SetTime(1);
	ppin[0]->SetWTime(1);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,1,NULL);
	ppin[1]->SetTime(1);
	ppin[1]->SetWTime(1);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,1,NULL);
	ppin[2]->SetTime(1);
	ppin[2]->SetWTime(1);
	ppin[2]->Set();
	ppin[2]->RecvMsg(2,1,NULL);
	ppin[3]->SetTime(1);
	ppin[3]->SetWTime(1);
	ppin[3]->Set();
	ppin[3]->RecvMsg(2,1,NULL);
	net3->receivemsg(1,1,NULL);
	net3->receivemsg(1,2,NULL);
	net3->receivemsg(1,3,NULL);
	net3->receivemsg(1,4,NULL);
	net3->receivemsg(1,5,NULL);
	net3->receivemsg(1,6,NULL);
	ppin[0]->SetTime(7);
	ppin[0]->SetWTime(7);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,7,NULL);
	ppin[1]->SetTime(7);
	ppin[1]->SetWTime(7);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,7,NULL);
	ppin[2]->SetTime(7);
	ppin[2]->SetWTime(7);
	ppin[2]->Set();
	ppin[2]->RecvMsg(2,7,NULL);
	ppin[3]->SetTime(7);
	ppin[3]->SetWTime(7);
	ppin[3]->Set();
	ppin[3]->RecvMsg(2,7,NULL);
	net3->receivemsg(1,7,NULL);
	net3->receivemsg(1,8,NULL);
	net3->receivemsg(1,9,NULL);
	net3->receivemsg(1,10,NULL);
	net3->receivemsg(1,11,NULL);
	net3->receivemsg(1,12,NULL);
	net3->receivemsg(3,12,NULL);
	net3->PrintData();
	delete net3;
}

void ColdTests::test_copy_del_net_ref()
{
	CGNetworkS *net1,*net2,*net3;
	CGInput *pin;
	CGOutput *pout;
	CGProcessor *proc;
	CString *a;
	CGTransition *trans;
	//first network
	net1=new CGNetworkS(1);
	pin=new CGInput(0);
	net1->AddPort(pin,true);
	pin=new CGInput(1);
	net1->AddPort(pin,true);
	pout=new CGOutput(2);
	net1->AddPort(pout,false);
	pout=new CGOutput(3);
	net1->AddPort(pout,false);
	//first processor from first network
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(0,trans);
	net1->AddProc(proc);
	pin=new CGInput(0);
	proc->AddPort(pin,true);
	pout=new CGOutput(1);
	proc->AddPort(pout,false);
	proc->SetFirst(true);
	trans->Set(1);
	trans->set_extfunc("y0[0]+x0[0]",0);
	trans->set_intfunc("y0[0]+0.5",0);

	//second processor from first network
	a=new CString("2.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(1,trans);
	net1->AddProc(proc);
	pin=new CGInput(0);
	proc->AddPort(pin,true);
	pout=new CGOutput(1);
	proc->AddPort(pout,false);
	proc->SetFirst(true);
	trans->Set(2);
	trans->set_extfunc("y0[0]+x0[0]",0);
	trans->set_intfunc("y0[0]+0.5",0);

	//add wires
	net1->AddParentProc(0,0,0,0);
	net1->AddParentProc(3,1,0,1);
	net1->AddParentProc(1,0,1,0);
	net1->AddParentProc(2,1,1,1);
	
	//second network
	net2=new CGNetworkS(2);
	pin=new CGInput(0);
	net2->AddPort(pin,true);
	pin=new CGInput(1);
	net2->AddPort(pin,true);
	pout=new CGOutput(2);
	net2->AddPort(pout,false);
	pout=new CGOutput(3);
	net2->AddPort(pout,false);
	//first processor from first network
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(0,trans);
	net2->AddProc(proc);
	pin=new CGInput(0);
	proc->AddPort(pin,true);
	pout=new CGOutput(1);
	proc->AddPort(pout,false);
	proc->SetFirst(true);
	trans->Set(1);
	trans->set_extfunc("y0[0]+x0[0]",0);
	trans->set_intfunc("y0[0]+0.5",0);

	//second processor from first network
	a=new CString("2.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(1,trans);
	net2->AddProc(proc);
	pin=new CGInput(0);
	proc->AddPort(pin,true);
	pout=new CGOutput(1);
	proc->AddPort(pout,false);
	proc->SetFirst(true);
	trans->Set(2);
	trans->set_extfunc("y0[0]+x[0]",0);
	trans->set_intfunc("y0[0]+0.5",0);

	//add wires
	net2->AddParentProc(0,0,0,0);
	net2->AddParentProc(3,1,0,1);
	net2->AddParentProc(1,0,1,0);
	net2->AddParentProc(2,1,1,1);

	//third network
	net3=new CGNetworkS(3);
	CGInput **ppin;
	ppin=(CGInput **)calloc(4,sizeof(CGInput *));
	//input ports and sources for third network
	pin=new CGInput(0);
	ppin[0]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net3->AddPort(pin,true);
	pin=new CGInput(1);
	ppin[1]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net3->AddPort(pin,true);
	pin=new CGInput(2);
	ppin[2]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net3->AddPort(pin,true);
	pin=new CGInput(3);
	ppin[3]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net3->AddPort(pin,true);
	//output ports and files
	a=new CString("out4cnr.dat");
	pout=new CGOutput(4,a);
	net3->AddPort(pout,false);
	a=new CString("out5cnr.dat");
	pout=new CGOutput(5,a);
	net3->AddPort(pout,false);
	a=new CString("out6cnr.dat");
	pout=new CGOutput(6,a);
	net3->AddPort(pout,false);
	a=new CString("out7cnr.dat");
	pout=new CGOutput(7,a);
	net3->AddPort(pout,false);

	//wires for third network
	net3->AddNetwork(net1);
	net3->AddNetwork(net2);
	net3->AddParentNet(0,0,2,0);
	net3->AddParentNet(1,1,2,0);
	net3->AddParentNet(6,2,2,1);
	net3->AddParentNet(7,3,2,1);
	net3->AddParentNet(2,0,1,0);
	net3->AddParentNet(3,1,1,0);
	net3->AddParentNet(4,2,1,1);
	net3->AddParentNet(5,3,1,1);

	//test vectors
	net3->receivemsg(0,0,NULL);
	ppin[0]->SetTime(1);
	ppin[0]->SetWTime(1);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,1,NULL);
	ppin[1]->SetTime(1);
	ppin[1]->SetWTime(1);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,1,NULL);
	ppin[2]->SetTime(1);
	ppin[2]->SetWTime(1);
	ppin[2]->Set();
	ppin[2]->RecvMsg(2,1,NULL);
	ppin[3]->SetTime(1);
	ppin[3]->SetWTime(1);
	ppin[3]->Set();
	ppin[3]->RecvMsg(2,1,NULL);
	net3->receivemsg(1,1,NULL);
	net3->receivemsg(1,2,NULL);
	net3->receivemsg(1,3,NULL);
	net3->receivemsg(1,4,NULL);
	net3->receivemsg(1,5,NULL);
	net3->receivemsg(1,6,NULL);
	ppin[0]->SetTime(7);
	ppin[0]->SetWTime(7);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,7,NULL);
	ppin[1]->SetTime(7);
	ppin[1]->SetWTime(7);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,7,NULL);
	ppin[2]->SetTime(7);
	ppin[2]->SetWTime(7);
	ppin[2]->Set();
	ppin[2]->RecvMsg(2,7,NULL);
	ppin[3]->SetTime(7);
	ppin[3]->SetWTime(7);
	ppin[3]->Set();
	ppin[3]->RecvMsg(2,7,NULL);
	net3->receivemsg(1,7,NULL);
	net3->receivemsg(1,8,NULL);
	net3->receivemsg(1,9,NULL);
	net3->receivemsg(1,10,NULL);
	net3->receivemsg(1,11,NULL);
	net3->receivemsg(1,12,NULL);
	net3->receivemsg(3,12,NULL);
	net3->PrintData();
	delete net3;
}

