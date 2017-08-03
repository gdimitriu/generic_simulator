// dinamic.cpp: implementation of the Cdinamic class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright 2005 Gabriel Dimitriu

	This file is part of Generic Simulator.
	This class implements dynamic examples.
	
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
#include "stdafx.h"
#include "dynamic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cdynamic::Cdynamic()
{

}

Cdynamic::~Cdynamic()
{

}

void Cdynamic::SetFunc(CComboBox *func)
{
	func->AddString(_T("testacpd"));
	func->AddString(_T("testapd"));
	func->AddString(_T("testdelp"));
	func->AddString(_T("testmdelpn"));
	func->AddString(_T("testParts"));
}

void Cdynamic::run(CComboBox *func)
{
	int index=func->GetCurSel();
	switch(index)
	{
	case 0:
		testacpd();
		break;
	case 1:
		testapd();
		break;
	case 2:
		testdelp();
		break;
	case 3:	
		testmdelpn();
		break;
	case 4:
		testParts();
		break;
	}
}

void Cdynamic::testdelp()
{
	CGNetworkS *net;
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
	a=new CString("out2p.dat");
	pout=new CGOutput(2,a);
	net->AddPort(pout,false);
	a=new CString("out3p.dat");
	pout=new CGOutput(3,a);
	net->AddPort(pout,false);

	//first processor from network
	a=new CString("1.0");
	trans=new CGTransitionS(a);
	delete a;
	proc=new CGProcessorS(NULL,0,trans,true);
	proc->SetRIType(true);
	procd=proc;
	pin=new CGInput(0);
	proc->AddPort(pin,true);
	pin=new CGInput(1);
	pdel1=pin;
	proc->AddPort(pin,true);
	a=new CString("intp.dat");
	pout=new CGOutput(2,a);
	pdel2=pout;
	proc->AddPort(pout,false);
	pout=new CGOutput(3);
	pdel3=pout;
	proc->AddPort(pout,false);
	trans->Set(1);
	trans->set_extfunc("y2[0]+x1[0]",2);
	trans->set_intfunc("y2[0]+0.5",2);
	trans->set_extfunc("y3[0]+x0[0]",3);
	trans->set_intfunc("y3[0]+0.5",3);
	net->AddProc(proc);

	//second processor from network
	a=new CString("1.0");
	trans=new CGTransitionS(a);
	delete a;
	proc=new CGProcessorS(NULL,1,trans,true);
	proc->SetRIType(true);
//	procd=proc;
	pin=new CGInput(0);
	proc->AddPort(pin,true);
	pin=new CGInput(1);
	proc->AddPort(pin,true);
	pout=new CGOutput(2);
	proc->AddPort(pout,false);
	trans->Set(2);
	trans->set_extfunc("x0[0]+x1[0]+1",2);
	trans->set_intfunc("y2[0]+0.5",2);
	net->AddProc(proc);

	//add wires
	net->AddParentProc(0,0,0,0);
	net->AddParentProc(1,1,1,0);
	net->AddParentProc(1,1,0,0);
	net->AddParentProc(2,2,1,1);
	net->AddParentProc(3,3,0,1);
	net->AddProcProc(0,2,1,0);
	
	//test vectors
	//net->DisableCoord();
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

	net->WaitCoord(); //wait for the coordinator to end it's work

//	procd->DelPort(pdel1);

//	procd->DelPort(pdel2);

//	procd->DelPort(pdel3);

//	procd->kill();
//	delete procd;

//	net->DelProc(procd);

	ppin[1]->SetTime(4.0);
	ppin[1]->SetWTime(4.0);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,4.0,NULL);

	while(time<9.0)
	{
		net->receivemsg(1,time,NULL);
		time=time+1;
	}
	net->PrintData();
	delete net;
}

void Cdynamic::testapd()
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
	a=new CString("out3apd.dat");
	pout=new CGOutput(3,a);
	net->AddPort(pout,false);

	//first processor from network
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CGProcessor(NULL,0,trans,true);
	proc->SetRIType(true);
	pin=new CGInput(0);
	proc->AddPort(pin,true);
	pout=new CGOutput(1);
	proc->AddPort(pout,false);
	trans->Set(1);
	trans->set_extfunc("y1[0]+x0[0]",1);
	trans->set_intfunc("y1[0]+0.5",1);

	net->AddProc(proc);


	//add wires 
	net->AddParentProc(0,0,0,0);
	net->AddParentProc(3,1,0,1);
	
	//test vectors 
	//net->DisableCoord();
 	net->receivemsg(0,0.0,NULL);
	ppin[0]->SetTime(1);
	ppin[0]->SetWTime(1);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,1,NULL);

	double time=1;
	while(time<4.0)
	{
		net->receivemsg(1,time,NULL);
		time=time+1;
	}
	net->WaitCoord();
	//add ports to network
	pin=new CGInput(1);
	ppin[1]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net->AddPort(pin,true);
	a=new CString("out2apd.dat");
	pout=new CGOutput(2,a);
	net->AddPort(pout,false);

	//add the processor
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CGProcessor(NULL,1,trans,true);
	proc->SetRIType(true);
	pin=new CGInput(0);
	proc->AddPort(pin,true);
	pout=new CGOutput(1);
	proc->AddPort(pout,false);
	trans->Set(1);
	trans->set_extfunc("y1[0]+x0[0]",1);
	trans->set_intfunc("y1[0]+0.5",1);
	net->AddProc(proc);
	net->AddParentProc(1,0,1,0);
	net->AddParentProc(2,1,1,1);

	ppin[0]->SetTime(4.0);
	ppin[0]->SetWTime(4.0);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,4.0,NULL);
	ppin[1]->SetTime(4.0);
	ppin[1]->SetWTime(4.0);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,4.0,NULL);

	while(time<9.0)
	{
		net->receivemsg(1,time,NULL);
		time=time+1;
	}
	net->PrintData();
	delete net;
}

void Cdynamic::testacpd()
{
	CGNetworkS *net;
	CGInput *pin;
	CGOutput *pout;
	CGProcessor *proc,*proc1;
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
	a=new CString("out3acpd.dat");
	pout=new CGOutput(3,a);
	net->AddPort(pout,false);

	//first processor from network
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CGProcessor(NULL,0,trans,true);
	proc->SetRIType(true);
	pin=new CGInput(0);
	proc->AddPort(pin,true);
	pout=new CGOutput(1);
	proc->AddPort(pout,false);
	trans->Set(1);
	trans->set_extfunc("y1[0]+x0[0]",1);
	trans->set_intfunc("y1[0]+0.5",1);

	net->AddProc(proc);

	//add wires 
	net->AddParentProc(0,0,0,0);
	net->AddParentProc(3,1,0,1);
	
	//test vectors
	//net->DisableCoord();
 	net->receivemsg(0,0.0,NULL);
	ppin[0]->SetTime(1);
	ppin[0]->SetWTime(1);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,1,NULL);

	double time=1;
	while(time<4.0)
	{
		net->receivemsg(1,time,NULL);
		time=time+1;
	}
	net->WaitCoord();
	//add ports to network
	pin=new CGInput(1);
	ppin[1]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net->AddPort(pin,true);
	a=new CString("out2acpd.dat");
	pout=new CGOutput(2,a);
	net->AddPort(pout,false);
	
	proc1=proc->copy(net,1);
	net->AddProc(proc1);
	net->AddParentProc(1,0,1,0);
	net->AddParentProc(2,1,1,1);

	ppin[0]->SetTime(4.0);
	ppin[0]->SetWTime(4.0);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,4.0,NULL);
	ppin[1]->SetTime(4.0);
	ppin[1]->SetWTime(4.0);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,4.0,NULL);

	while(time<9.0)
	{
		net->receivemsg(1,time,NULL);
		time=time+1;
	}
	net->PrintData();
	delete net;

}

void Cdynamic::testmdelpn()
{
	CGNetworkS *net,*net1;
	CGInput *pin;
	CGOutput *pout;
	CGProcessor *proc;
	CString *a;
	CGTransition *trans;
	CGInput **ppin;
	CGProcessor *procd;
	CGData *pdel1;
	CGData *pdel2;
	CGNetworkS *netd;

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
	a=new CString("out2pn.dat");
	pout=new CGOutput(2,a);
	net->AddPort(pout,false);
	a=new CString("out3pn.dat");
	pout=new CGOutput(3,a);
	net->AddPort(pout,false);

	//first processor from network
	a=new CString("1.0");
	trans=new CGTransitionS(a);
	delete a;
	proc=new CGProcessorS(NULL,0,trans,true);
	procd=proc;
	proc->SetRIType(true);
	net->AddProc(proc);
	pin=new CGInput(0);
	proc->AddPort(pin,true);
	pin=new CGInput(1);
	proc->AddPort(pin,true);
	a=new CString("intp0n.dat");
	pout=new CGOutput(2,a);
	pdel2=pout;
	proc->AddPort(pout,false);
	pout=new CGOutput(3);
	proc->AddPort(pout,false);
	trans->Set(1);
	trans->set_extfunc("y2[0]+x1[0]",2);
	trans->set_intfunc("y2[0]+0.5",2);
	trans->set_extfunc("y3[0]+x0[0]",3);
	trans->set_intfunc("y3[0]+0.5",3);

	//slave network
	net1=new CGNetworkS(1);
	net1->SetTypeWire(false);
	netd=net1;
	//ports for network
	pin=new CGInput(0);
	net1->AddPort(pin,true);
	pin=new CGInput(1);
	net1->AddPort(pin,true);
	//output ports and files
	pout=new CGOutput(2);
	net1->AddPort(pout,false);
	
	net->AddNetwork(net1);

	//second processor from network
	a=new CString("1.0");
	trans=new CGTransitionS(a);
	delete a;
	proc=new CGProcessorS(NULL,1,trans,true);
	proc->SetRIType(true);
	net1->AddProc(proc);
	pin=new CGInput(0);
	proc->AddPort(pin,true);
	pin=new CGInput(1);
	proc->AddPort(pin,true);
	pout=new CGOutput(2);
	proc->AddPort(pout,false);
	trans->Set(2);
	trans->set_extfunc("x0[0]+x1[0]+1",2);
	trans->set_intfunc("y2[0]+0.5",2);

	//add slave wire
	net1->AddParentProc(0,0,1,0);
	net1->AddParentProc(1,1,1,0);
	net1->AddParentProc(2,2,1,1);
	//add master wires 
	net->AddParentProc(0,0,0,0);
	net->AddParentProc(1,1,0,0);
	net->AddParentProc(3,3,0,1);
	net->AddParentNet(1,1,1,0);
	net->AddParentNet(2,2,1,1);
	net->AddProcNetwork(0,2,1,0);
	
	//test vectors 
	//net->DisableCoord();
 	net->receivemsg(0,0.0,NULL);
	ppin[0]->SetTime(1);
	ppin[0]->SetWTime(1);
	ppin[0]->Set();
	ppin[1]->SetTime(1);
	ppin[1]->SetWTime(1);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,1,NULL);
	ppin[0]->RecvMsg(2,1,NULL);

	double time=1;
	while(time<4.0)
	{
		net->receivemsg(1,time,NULL);
		time=time+1;
	}
	net->WaitCoord();

//	procd->DelPort(pdel2);
//	net->DelNet(netd);

//	netd->kill();
//	delete netd;

	ppin[1]->SetTime(4.0);
	ppin[1]->SetWTime(4.0);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,4.0,NULL);

	while(time<9.0)
	{
		net->receivemsg(1,time,NULL);
		time=time+1;
	}
	net->PrintData();
	delete net;
}

void Cdynamic::testParts()
{
	CGNetworkS *net,*wnet,*wnet1;
	CObject *ob;
	CGInput **ppin;
	ppin=(CGInput **)calloc(3,sizeof(CGInput *));
	CString *a;
	CProcessor *proc;
	CGTransition *trans;

	net=new CGNetworkS(0);
	
	a=new CString("in0.dat");
	ob=new CGInput(0,a);
	ppin[0]=(CGInput *)ob;
	net->Add(ob);
	a=new CString("in1.dat");
	ob=new CGInput(1,a);
	ppin[1]=(CGInput *)ob;
	net->Add(ob);
	a=new CString("in2.dat");
	ob=new CGInput(2,a);
	ppin[2]=(CGInput *)ob;
	net->Add(ob);

	a=new CString("out3.dat");
	ob=new CGOutput(3,a);
	net->Add(ob);
	a=new CString("out4.dat");
	ob=new CGOutput(4,a);
	net->Add(ob);
	a=new CString("out5.dat");
	ob=new CGOutput(5,a);
	net->Add(ob);
	a=new CString("out6.dat");
	ob=new CGOutput(6,a);
	net->Add(ob);
	a=new CString("out7.dat");
	ob=new CGOutput(7,a);
	net->Add(ob);

	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(1,trans);
	ob=new CGInput(0);
	proc->Add(ob);
	ob=new CGOutput(1);
	proc->Add(ob);
	trans->Set(1);
	trans->set_extfunc("x0[0]+y1[0]",1);
	trans->set_intfunc("y1[0]+0.5",1);
	net->AddProc(proc);
//first working net
	wnet=new CGNetworkS(0);
	wnet->DisableCoord();
	ob=new CGInput(0);
	wnet->Add(ob);
	ob=new CGInput(1);
	wnet->Add(ob);
	ob=new CGOutput(2);
	wnet->Add(ob);
	ob=new CGOutput(3);
	wnet->Add(ob);
	ob=new CGOutput(4);
	wnet->Add(ob);
	ob=new CGOutput(5);
	wnet->Add(ob);
	ob=new CGOutput(6);
	wnet->Add(ob);
	net->Add(wnet);
	//wires for parent
	net->AddParentProc(2,0,1,0);
	net->AddParentProc(7,1,1,1);
	net->AddParentNet(0,0,0,0);
	net->AddParentNet(1,1,0,0);
	net->AddParentNet(3,2,0,1);
	net->AddParentNet(4,3,0,1);
	net->AddParentNet(5,4,0,1);
	net->AddParentNet(6,5,0,1);
	//for internal network 1
	wnet1=new CGNetworkS(0);
	wnet1->DisableCoord();
	ob=new CGInput(0);
	wnet1->Add(ob);
	ob=new CGOutput(1);
	wnet1->Add(ob);
	ob=new CGOutput(2);
	wnet1->Add(ob);
	wnet->Add(wnet1);

	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(0,trans);
	ob=new CGInput(0);
	proc->Add(ob);
	ob=new CGOutput(1);
	proc->Add(ob);
	trans->Set(1);
	trans->set_extfunc("x0[0]+y1[0]",1);
	trans->set_intfunc("y1[0]+0.5",1);
	wnet1->AddProc(proc);
	
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(1,trans);
	ob=new CGInput(0);
	proc->Add(ob);
	ob=new CGOutput(1);
	proc->Add(ob);
	trans->Set(1);
	trans->set_extfunc("x0[0]+y1[0]",1);
	trans->set_intfunc("y1[0]+0.5",1);
	wnet1->AddProc(proc);
	//wires
	wnet->AddParentNet(1,0,0,0);
	wnet->AddParentNet(5,1,0,1);
	wnet->AddParentNet(4,2,0,1);
	wnet1->AddParentProc(0,0,0,0);
	wnet1->AddParentProc(0,0,1,0);
	wnet1->AddParentProc(1,1,0,1);
	wnet1->AddParentProc(2,1,1,1);
	//internal network
	wnet1=new CGNetworkS(1);
	wnet1->DisableCoord();
	ob=new CGInput(0);
	wnet1->Add(ob);
	ob=new CGOutput(1);
	wnet1->Add(ob);
	ob=new CGOutput(2);
	wnet1->Add(ob);
	wnet->Add(wnet1);
	
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(0,trans);
	ob=new CGInput(0);
	proc->Add(ob);
	ob=new CGOutput(1);
	proc->Add(ob);
	trans->Set(1);
	trans->set_extfunc("x0[0]+y1[0]",1);
	trans->set_intfunc("y1[0]+0.5",1);
	wnet1->AddProc(proc);
	//wires
	wnet->AddParentNet(0,0,1,0);
	wnet->AddParentNet(2,2,1,1);
	wnet->AddParentNet(3,1,1,1);
	wnet1->AddParentProc(0,0,0,0);
	wnet1->AddParentProc(1,1,0,1);
	//new network
	wnet=new CGNetworkS(1);
	wnet->DisableCoord();
	ob=new CGInput(0);
	wnet->Add(ob);
	ob=new CGOutput(1);
	wnet->Add(ob);
	wnet1->Add(wnet);
	
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(0,trans);
	ob=new CGInput(0);
	proc->Add(ob);
	ob=new CGOutput(1);
	proc->Add(ob);
	trans->Set(1);
	trans->set_extfunc("x0[0]+y1[0]",1);
	trans->set_intfunc("y1[0]+0.5",1);
	wnet->AddProc(proc);
	//wires
	wnet1->AddParentNet(0,0,1,0);
	wnet1->AddParentNet(2,1,1,1);
	wnet->AddParentProc(0,0,0,0);
	wnet->AddParentProc(1,1,0,1);
//////////////////////////////////////////////////////////
	CSCoordinator *coord;
	coord=new CSCoordinator();
	coord->setParent(net);
	coord->InputData();
	coord->InputPart(net);
	coord->Run();
	delete coord;
	delete net;
}
