// specialf.cpp: implementation of the Cspecialf class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright 2005 Gabriel Dimitriu

	This file is part of Generic Simulator.
	This class implements special functionality examples.
	
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
#include "specialf.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cspecialf::Cspecialf()
{

}

Cspecialf::~Cspecialf()
{

}

void Cspecialf::SetFunc(CComboBox *func)
{
	func->AddString(_T("test2_01"));
	func->AddString(_T("test2_02"));
	func->AddString(_T("test3_01"));
	func->AddString(_T("test4_01"));
	func->AddString(_T("testd1_01"));
	func->AddString(_T("run1"));
}

void Cspecialf::run(CComboBox *func)
{
	int index=func->GetCurSel();
	switch(index)
	{
		case 0:
			test2_01();
			break;
		case 1:
			test2_02();
			break;
		case 2:
			test3_01();
			break;
		case 3:
			test4_01();
			break;
		case 4:
			testd1_01();
			break;
		case 5:
			run1();
			break;
		case CB_ERR:
			break;
	}
}

void Cspecialf::test2_01()
{
	CNetworkS *net;
	CInput *pin;
	COutput *pout;
	CProcessor *proc;
	CString *a;
	CGTransition *trans;
	CGInput **ppin;
	ppin=(CGInput **)calloc(2,sizeof(CGInput *));

	//input ports and sources for third network
	net=new CNetworkS(0);
	net->SetTypeWire(true);
	pin=new CInput(0);
	ppin[0]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net->AddPort(pin,true);
	pin=new CInput(1);
	ppin[1]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net->AddPort(pin,true);
	//output ports and files
	a=new CString("out2.dat");
	pout=new COutput(2,a);
	net->AddPort(pout,false);
	a=new CString("out3.dat");
	pout=new COutput(3,a);
	net->AddPort(pout,false);
	a=new CString("out4.dat");
	pout=new COutput(4,a);
	net->AddPort(pout,false);

	//first processor from network
	a=new CString("2.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(0,trans);
	net->AddProc(proc);
	pin=new CInput(0);
	proc->AddPort(pin,true);
	pout=new COutput(1);
	proc->AddPort(pout,false);
	trans->Set(1);
	trans->set_extfunc("t0[0]+x0[0]",0);
	trans->set_intfunc("t0[0]+0.5",0);

	//second processor from network
	a=new CString("3.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(1,trans);
	pin=new CInput(0);
	proc->AddPort(pin,true);
	pout=new COutput(1);
	proc->AddPort(pout,false);
	trans->Set(2);
	trans->set_extfunc("t0[0]+x0[0]",0);
	trans->set_intfunc("t0[0]+0.5",0);

	net->AddProc(proc);

	//third processor
	a=new CString("2.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(2,trans);
	pin=new CInput(0);
	proc->AddPort(pin,true);
	pout=new COutput(1);
	proc->AddPort(pout,false);
	trans->Set(3);
	trans->set_extfunc("t0[0]+x0[0]",0);
	trans->set_intfunc("t0[0]+0.5",0);

	net->AddProc(proc);

	//add wires
	net->AddParentProc(0,0,0,0);
	net->AddParentProc(0,0,1,0);
	net->AddParentProc(1,0,2,0);
	net->AddParentProc(4,1,0,1);
	net->AddParentProc(3,1,1,1);
	net->AddParentProc(2,1,2,1);
	//test vectors
	net->receivemsg(0,0,NULL);
	ppin[0]->SetTime(1);
	ppin[0]->SetWTime(1);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,1,NULL);
	ppin[1]->SetTime(1);
	ppin[1]->SetWTime(1);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,1,NULL);
	net->receivemsg(1,1,NULL);
	net->receivemsg(1,2,NULL);
	ppin[0]->SetTime(3);
	ppin[0]->SetWTime(3);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,3,NULL);
	net->receivemsg(1,3,NULL);
	ppin[0]->SetTime(4);
	ppin[0]->SetWTime(4);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,4,NULL);
	ppin[1]->SetTime(4);
	ppin[1]->SetWTime(4);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,4,NULL);
	net->receivemsg(1,4,NULL);
	net->receivemsg(1,5,NULL);
	net->receivemsg(1,6,NULL);
	net->receivemsg(1,7,NULL);
	net->receivemsg(1,8,NULL);
	net->receivemsg(1,9,NULL);
	net->receivemsg(1,10,NULL);
	net->receivemsg(1,11,NULL);
	net->receivemsg(1,12,NULL);
	net->PrintData();
	delete net;
}

void Cspecialf::test2_02()
{
	CNetworkS *net;
	CInput *pin;
	COutput *pout;
	CProcessor *proc;
	CString *a;
	CGTransition *trans;
	net=new CNetworkS(0);
	net->SetTypeWire(true);
	net->SetInType(true);
	CGInput **ppin;
	ppin=(CGInput **)calloc(2,sizeof(CGInput *));
	//input ports and sources for third network
	pin=new CInput(0);
	ppin[0]=pin;
	a=new CString("2.0");
	pin->SetGenerator(a);
	delete a;
	net->AddPort(pin,true);
	pin=new CInput(1);
	ppin[1]=pin;
	a=new CString("2.0");
	pin->SetGenerator(a);
	delete a;
	net->AddPort(pin,true);
	//output ports and files
	a=new CString("out2.dat");
	pout=new COutput(2,a);
	net->AddPort(pout,false);
	a=new CString("out3.dat");
	pout=new COutput(3,a);
	net->AddPort(pout,false);
	a=new CString("out4.dat");
	pout=new COutput(4,a);
	net->AddPort(pout,false);

	//first processor from network
	a=new CString("2.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(0,trans);
	pin=new CInput(0);
	proc->AddPort(pin,true);
	pout=new COutput(1);
	proc->AddPort(pout,false);
	trans->Set(1);
	trans->set_extfunc("t0[0]+x0[0]",0);
	trans->set_intfunc("t0[0]+0.5",0);

	net->AddProc(proc);

	//second processor from network
	a=new CString("3.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(1,trans);
	net->AddProc(proc);
	pin=new CInput(0);
	proc->AddPort(pin,true);
	pout=new COutput(1);
	proc->AddPort(pout,false);
	trans->Set(2);
	trans->set_extfunc("t0[0]+x0[0]",0);
	trans->set_intfunc("t0[0]+0.5",0);

	net->AddProc(proc);

	//third processor form network
	a=new CString("2.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(2,trans);
	net->AddProc(proc);
	pin=new CInput(0);
	proc->AddPort(pin,true);
	pout=new COutput(1);
	proc->AddPort(pout,false);
	trans->Set(2);
	trans->set_extfunc("t0[0]+x0[0]",0);
	trans->set_intfunc("t0[0]+0.5",0);

	net->AddProc(proc);

	//add wires
	net->AddParentProc(0,0,0,0);
	net->AddParentProc(0,0,1,0);
	net->AddParentProc(1,0,2,0);
	net->AddParentProc(4,1,0,1);
	net->AddParentProc(3,1,1,1);
	net->AddParentProc(2,1,2,1);
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
		time=time+0.01;
	}
	net->PrintData();
	delete net;
}

void Cspecialf::test3_01()
{
	CNetworkS *net;
	CInput *pin;
	COutput *pout;
	CProcessor *proc;
	CString *a;
	CGTransition *trans;
	net=new CNetworkS(0);
	net->SetTypeWire(true);
	CGInput **ppin;
	ppin=(CGInput **)calloc(2,sizeof(CGInput *));

	//input ports and sources for third network
	pin=new CInput(0);
	ppin[0]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net->AddPort(pin,true);
	pin=new CInput(1);
	ppin[1]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net->AddPort(pin,true);
	//output ports and files
	a=new CString("out2.dat");
	pout=new COutput(2,a);
	net->AddPort(pout,false);
	a=new CString("out3.dat");
	pout=new COutput(3,a);
	net->AddPort(pout,false);

	//first processor from network
	a=new CString("2.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(0,trans,false);
//	proc=new CProcessor(0,trans,true);
	proc->EnableQ();
//	proc->SetFirst(true);
	net->AddProc(proc);
	pin=new CInput(0);
	proc->AddPort(pin,true);
	a=new CString("test0.dat");
	pout=new COutput(1,a);
	proc->AddPort(pout,false);
	trans->Set(1);
	trans->set_extfunc("t0[0]+x0[0]",0);
	trans->set_intfunc("t0[0]+0.5",0);

	//second processor from network
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(1,trans,false);
//	proc=new CProcessor(1,trans,true);
	proc->EnableQ();
//	proc->SetFirst(true);
	net->AddProc(proc);
	pin=new CInput(0);
	proc->AddPort(pin,true);
	a=new CString("test1.dat");
	pout=new COutput(1,a);
	proc->AddPort(pout,false);
	trans->Set(2);
	trans->set_extfunc("t0[0]+x0[0]",0);
	trans->set_intfunc("t0[0]+0.5",0);

	//third processor from network
	a=new CString("2.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(2,trans,false);
//	proc=new CProcessor(2,trans,true);
	net->AddProc(proc);
	pin=new CInput(0);
	proc->AddPort(pin,true);
	pout=new COutput(1);
	proc->AddPort(pout,false);
	trans->Set(3);
	trans->set_extfunc("t0[0]+x0[0]",0);
	trans->set_intfunc("t0[0]+0.5",0);

	//add wires
	net->AddParentProc(0,0,0,0);
	net->AddParentProc(0,0,1,0);
	net->AddParentProc(1,0,2,0);
	net->AddParentProc(3,1,0,1);
	net->AddParentProc(3,1,1,1);
	net->AddParentProc(2,1,2,1);
	//test vectors
	//test 01
	net->receivemsg(0,0,NULL);
	ppin[0]->SetTime(1);
	ppin[0]->SetWTime(1);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,1,NULL);
	ppin[1]->SetTime(1);
	ppin[1]->SetWTime(1);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,1,NULL);
	net->receivemsg(1,1,NULL);
	net->receivemsg(1,2,NULL);
	ppin[0]->SetTime(3);
	ppin[0]->SetWTime(3);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,3,NULL);
	ppin[1]->SetTime(3);
	ppin[1]->SetWTime(3);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,3,NULL);
	net->receivemsg(1,3,NULL);
	ppin[0]->SetTime(4);
	ppin[0]->SetWTime(4);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,4,NULL);
	ppin[1]->SetTime(4);
	ppin[1]->SetWTime(4);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,4,NULL);
	net->receivemsg(1,4,NULL);
	net->receivemsg(1,5,NULL);
	net->receivemsg(1,6,NULL);
	net->receivemsg(1,7,NULL);
	net->receivemsg(1,8,NULL);
	net->receivemsg(1,9,NULL);
	net->receivemsg(1,10,NULL);
	net->receivemsg(1,11,NULL);
	net->receivemsg(1,12,NULL);
	net->PrintData();
	delete net;
}


void Cspecialf::test4_01()
{
	CNetworkS *net,*net1;
	CInput *pin;
	COutput *pout;
	CProcessor *proc;
	CString *a;
	CGTransition *trans;
	//first network
	net=new CNetworkS(0);
	net->SetTypeWire(true);
//	net->SetInType(true);
	CGInput **ppin;
	ppin=(CGInput **)calloc(1,sizeof(CGInput *));
	//input ports and sources for network
	a=new CString("out0.dat");
	pin=new CInput(0,a);
	ppin[0]=pin;
	pin->SetDim(2);
	a=new CString("1.0");
	pin->SetGenerator(a,0);
	delete a;
	a=new CString("1.0");
	pin->SetGenerator(a,1);
	delete a;
	net->AddPort(pin,true);
	//output ports and files
	a=new CString("out1.dat");
	pout=new COutput(1,a);
	pout->SetDim(2);
	net->AddPort(pout,false);
	a=new CString("out2.dat");
	pout=new COutput(2,a);
	pout->SetDim(2);
	net->AddPort(pout,false);

	net1=new CNetworkS(1);
	net1->SetTypeWire(true);
//	net1->SetInType(true);
	pin=new CInput(0);
	pin->SetDim(2);
	net1->AddPort(pin,true);
	pout=new COutput(1);
	pout->SetDim(2);
	net1->AddPort(pout,false);
	pout=new COutput(2);
	pout->SetDim(2);
	net1->AddPort(pout,false);
	
	//first processor from network
	a=new CString("2.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(0,trans);
	pin=new CInput(0);
	pin->SetDim(2);
	proc->AddPort(pin,true);
	pout=new COutput(1);
	pout->SetDim(2);
	proc->AddPort(pout,false);
	pout=new COutput(2);
	pout->SetDim(2);
	proc->AddPort(pout,false);
	trans->Set(2);
	trans->set_extfunc("t0[0]+x0[0]",0);
	trans->set_extfunc("t1[0]+x1[0]",1);
	trans->set_intfunc("t0[0]+0.5",0);
	trans->set_intfunc("t1[0]+0.5",1);
	//add proc
	net1->AddProc(proc);
	//add wires
	net1->AddParentProc(0,0,0,0);
	net1->AddParentProc(1,1,0,1);
	net1->AddParentProc(2,2,0,1);
	//add net
	net->AddNetwork(net1);
	//add wires
	net->AddParentNet(0,0,1,0);
	net->AddParentNet(1,1,1,1);
	net->AddParentNet(2,2,1,1);
	//run
	net->receivemsg(0,0,NULL);
	ppin[0]->SetTime(1);
	ppin[0]->SetWTime(1);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,1,NULL);
	net->receivemsg(1,2,NULL);
	ppin[0]->SetTime(3);
	ppin[0]->SetWTime(3);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,3,NULL);
	net->receivemsg(1,3,NULL);
	for(int i=4;i<12;i=i++)
	{
		net->receivemsg(1,i,NULL);
	}
	net->PrintData();
	delete net;
}

void Cspecialf::testd1_01()
{
	CNetworkS *net;
	CInput *pin;
	COutput *pout;
	CProcessor *proc;
	CString *a;
	CGTransition *trans;
	net=new CNetworkS(0);
	net->SetTypeWire(true);
	CGInput **ppin;
	ppin=(CGInput **)calloc(2,sizeof(CGInput *));
	//ports for network
	pin=new CInput(0);
	ppin[0]=pin;
	a=new CString("2.0");
	pin->SetGenerator(a);
	delete a;
	net->AddPort(pin,true);
	pin=new CInput(1);
	ppin[1]=pin;
	a=new CString("2.0");
	pin->SetGenerator(a);
	delete a;
	net->AddPort(pin,true);
	//output ports and files
	a=new CString("out2.dat");
	pout=new COutput(2,a);
	net->AddPort(pout,false);
	a=new CString("out3.dat");
	pout=new COutput(3,a);
	net->AddPort(pout,false);
	a=new CString("out4.dat");
	pout=new COutput(4,a);
	net->AddPort(pout,false);

	//first processor from network
	a=new CString("2.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(0,trans);
	net->AddProc(proc);
	pin=new CInput(0);
	proc->AddPort(pin,true);
	pout=new COutput(1);
	proc->AddPort(pout,false);
	trans->Set(1);
	trans->set_extfunc("t0[0]+x0[0]",0);
	trans->set_intfunc("t0[0]+0.5",0);
	//second processor from network
	a=new CString("3.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(1,trans);
	net->AddProc(proc);
	pin=new CInput(0);
	proc->AddPort(pin,true);
	pout=new COutput(1);
	proc->AddPort(pout,false);
	trans->Set(2);
	trans->set_extfunc("t0[0]+x0[0]",0);
	trans->set_intfunc("t0[0]+0.5",0);

	a=new CString("2.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(2,trans);
	net->AddProc(proc);
	pin=new CInput(0);
	proc->AddPort(pin,true);
	pout=new COutput(1);
	proc->AddPort(pout,false);
	trans->Set(2);
	trans->set_extfunc("t0[0]+x0[0]",0);
	trans->set_intfunc("t0[0]+0.5",0);
	//add wires
	net->AddParentProc(0,0,0,0);
	net->AddParentProc(0,0,1,0);
	net->AddParentProc(1,0,2,0);
	net->AddParentProc(4,1,0,1);
	net->AddParentProc(3,1,1,1);
	net->AddParentProc(2,1,2,1);
	//test vectors
	//test 01
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
		time=time+0.01;
	}
	net->PrintData();
	delete net;
}


void Cspecialf::run1()
{
	CString *a;
	CTransition1 *tran;
	CGNetworkS *net;
	CProcessor *proc;
	CInput **ppin;
	CInput *pin;
	COutput *pout;
	ppin=(CInput **)calloc(1,sizeof(CInput *));
	net=new CGNetworkS(0);
	a=new CString("in.dat");
	pin=new CInput(0,a);
	a=new CString("1.0");
	pin->SetGenerator(a);
	ppin[0]=pin;
	net->AddPort(pin,true);
	a=new CString("out.dat");
	pout=new COutput(1,a);
	net->AddPort(pout,false);
	a=new CString("1.0");
	tran=new CTransition1(a);
	delete a;
	proc=new CProcessor(0,tran,false);
	proc->SetFirstI(true);
	proc->IsDelayed(false);
	proc->SetFirst(true);
	pin=new CInput(0);
	proc->AddPort(pin,true);
	pout=new COutput(1);
	proc->AddPort(pout,false);
	tran->Set(1);
	net->AddProc(proc);
	net->AddParentProc(0,0,0,0);
	net->AddParentProc(1,1,0,1);
	long i;
	//net->DisableCoord();
	//tests
	net->SetClockPrecision(1);
	net->receivemsg(0,0,NULL);
	ppin[0]->SetTime(0);
	ppin[0]->SetWTime(0);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,0,NULL);
	net->receivemsg(1,0,NULL);
	net->receivemsg(1,1,NULL);
	ppin[0]->SetTime(1);
	ppin[0]->SetWTime(1);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,1,NULL);
	//net->receivemsg(1,1,NULL);
	for(i=2;i<5;i++)
		net->receivemsg(1,i,NULL);
	net->PrintData();
	delete net;
}

