// functionality.cpp: implementation of the Cfunctionality class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright 2005 Gabriel Dimitriu

	This file is part of Generic Simulator.
	This class implements basic functionality examples.
	
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
#include "functionality.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cfunctionality::Cfunctionality()
{

}

Cfunctionality::~Cfunctionality()
{

}

void Cfunctionality::SetFunc(CComboBox *func)
{
	func->AddString(_T("test1_01"));
	func->AddString(_T("test1_02"));
	func->AddString(_T("testBuses"));
	func->AddString(_T("testcps"));
	func->AddString(_T("testDistributions"));
	func->AddString(_T("testDistributions_2"));
	func->AddString(_T("testDQL"));
	func->AddString(_T("testDQL_2"));
	func->AddString(_T("testDQL_2_S"));
	func->AddString(_T("testMDM"));
	func->AddString(_T("testmprocs"));
	func->AddString(_T("testmprocsn"));
	func->AddString(_T("testSum"));
}

void Cfunctionality::run(CComboBox *func)
{
	int index=func->GetCurSel();
	switch(index)
	{
		case 0:
			test1_01();
			break;
		case 1:
			test1_02();
			break;
		case 2:
			testBuses();
			break;
		case 3:
			testcps();
			break;
		case 4:
			testDistributions();
			break;
		case 5:
			testDistributions_2();
			break;
		case 6:
			testDQL();
			break;
		case 7:
			testDQL_2();
			break;
		case 8:
			testDQL_2_S();
			break;
		case 9:
			testMDM();
			break;
		case 10:
			testmprocs();
			break;
		case 11:
			testmprocsn();
			break;
		case 12:
			testSum();
			break;
		case CB_ERR:
			break;
	}
}

void Cfunctionality::test1_01()
{
	CNetworkS *net1,*net2,*net3;
	CInput *pin;
	COutput *pout;
	CProcessor *proc;
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
	proc=new CProcessor(0,trans);
	pin=new CInput(0);
	proc->AddPort(pin,true);
	pout=new COutput(1);
	proc->AddPort(pout,false);
	trans->Set(1);
	trans->set_extfunc("x0[0]+y1[0]",1);
	trans->set_intfunc("y1[0]+0.5",1);
	
	net1->AddProc(proc);

	//second processor from first network
	a=new CString("2.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(1,trans);
	pin=new CInput(0);
	proc->AddPort(pin,true);
	a=new CString("out1_2.dat");
	pout=new COutput(1,a);
	proc->AddPort(pout,false);
	trans->Set(2);
	trans->set_extfunc("x0[0]+y1[0]",1);
	trans->set_intfunc("y1[0]+0.5",1);

	net1->AddProc(proc);

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
	proc=new CProcessor(0,trans);
	pin=new CInput(0);
	proc->AddPort(pin,true);
	pout=new COutput(1);
	proc->AddPort(pout,false);
	trans->Set(1);
	trans->set_extfunc("x0[0]+y1[0]",1);
	trans->set_intfunc("y1[0]+0.5",1);

	net2->AddProc(proc);

	//second processor from second network
	a=new CString("2.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(1,trans);
	pin=new CInput(0);
	proc->AddPort(pin,true);
	a=new CString("outint.dat");
	pout=new COutput(1,a);
	proc->AddPort(pout,false);
	trans->Set(2);
	trans->set_extfunc("x0[0]+y1[0]",1);
	trans->set_intfunc("y1[0]+0.5",1);

	net2->AddProc(proc);

	//third processor form second network
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(2,trans);
	a=new CString("1_1inint.dat");
	pin=new CInput(0,a);
	proc->AddPort(pin,true);
	pout=new COutput(1);
	proc->AddPort(pout,false);
	trans->Set(3);
	trans->set_extfunc("x0[0]+y1[0]",1);
	trans->set_intfunc("y1[0]+0.5",1);

	net2->AddProc(proc);

	//wire for second network
	net2->AddParentProc(0,0,0,0);
	net2->AddParentProc(3,1,0,1);
	net2->AddParentProc(1,0,1,0);
	net2->AddParentProc(2,1,2,1);
	net2->AddProcProc(1,1,2,0);

	//third network
	net3=new CNetworkS(3);
	CGInput **ppin;
	ppin=(CGInput **)calloc(4,sizeof(CGInput *));
	//input ports and sources for third network
	a=new CString("1_1in0.dat");
	pin=new CInput(0,a);
	ppin[0]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net3->AddPort(pin,true);
	a=new CString("1_1in1.dat");
	pin=new CInput(1,a);
	ppin[1]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net3->AddPort(pin,true);
	a=new CString("1_1in2.dat");
	pin=new CInput(2,a);
	ppin[2]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net3->AddPort(pin,true);
	a=new CString("1_1in3.dat");
	pin=new CInput(3,a);
	ppin[3]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net3->AddPort(pin,true);
	//output ports and files
	a=new CString("1_1out4.dat");
	pout=new COutput(4,a);
	net3->AddPort(pout,false);
	a=new CString("1_1out5.dat");
	pout=new COutput(5,a);
	net3->AddPort(pout,false);
	a=new CString("1_1out6.dat");
	pout=new COutput(6,a);
	net3->AddPort(pout,false);
	a=new CString("1_1out7.dat");
	pout=new COutput(7,a);
	net3->AddPort(pout,false);

	net3->AddNetwork(net1);
	net3->AddNetwork(net2);

	//wires for third network
	net3->AddParentNet(0,0,2,0);
	net3->AddParentNet(1,1,2,0);
	net3->AddParentNet(6,2,2,1);
	net3->AddParentNet(7,3,2,1);
	net3->AddParentNet(2,0,1,0);
	net3->AddParentNet(3,1,1,0);
	net3->AddParentNet(4,2,1,1);
	net3->AddParentNet(5,3,1,1);

	//test vectors
	net3->DisableCoord();
	net2->DisableCoord();
	net1->DisableCoord();
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
	net3->PrintData();
	delete net3;
}

void Cfunctionality::test1_02()
{
	CNetworkS *net1,*net2,*net3;
	CInput *pin;
	COutput *pout;
	CProcessor *proc;
	CString *a;
	CGTransition *trans;

	//first network
	net1=new CNetworkS(1);
	pin=new CInput(0);
	pin->SetDim(1);
	net1->AddPort(pin,true);
	pin=new CInput(1);
	pin->SetDim(1);
	net1->AddPort(pin,true);
	pout=new COutput(2);
	pout->SetDim(1);
	net1->AddPort(pout,false);
	pout=new COutput(3);
	pout->SetDim(1);
	net1->AddPort(pout,false);

	//first processor from first network
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(0,trans);
	pin=new CInput(0);
	proc->AddPort(pin,true);
	pout=new COutput(1);
	proc->AddPort(pout,false);
	trans->Set(1);
	trans->set_extfunc("y1[0]+x0[0]",1);
	trans->set_intfunc("y1[0]+0.5",1);

	net1->AddProc(proc);

	//second processor from first network
	a=new CString("2.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(1,trans);
	pin=new CInput(0);
	proc->AddPort(pin,true);
	pout=new COutput(1);
	proc->AddPort(pout,false);
	trans->Set(2);
	trans->set_extfunc("y1[0]+x0[0]",1);
	trans->set_intfunc("y1[0]+0.5",1);

	net1->AddProc(proc);

	//add wires
	net1->AddParentProc(0,0,0,0);
	net1->AddParentProc(3,1,0,1);
	net1->AddParentProc(1,0,1,0);
	net1->AddParentProc(2,1,1,1);

	//second network
	net2=new CNetworkS(2);
	pin=new CInput(0);
	pin->SetDim(1);
	net2->AddPort(pin,true);
	pin=new CInput(1);
	pin->SetDim(1);
	net2->AddPort(pin,true);
	pout=new COutput(2);
	pout->SetDim(1);
	net2->AddPort(pout,false);
	pout=new COutput(3);
	pout->SetDim(1);
	net2->AddPort(pout,false);

	//first processor from second network
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(0,trans);
	pin=new CInput(0);
	proc->AddPort(pin,true);
	pout=new COutput(1);
	proc->AddPort(pout,false);
	trans->Set(1);
	trans->set_extfunc("y1[0]+x0[0]",1);
	trans->set_intfunc("y1[0]+0.5",1);

	net2->AddProc(proc);

	//second processor from second network
	a=new CString("2.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(1,trans);
	pin=new CInput(0);
	proc->AddPort(pin,true);
	a=new CString("outint.dat");
	pout=new COutput(1,a);
	proc->AddPort(pout,false);
	trans->Set(2);
	trans->set_extfunc("y1[0]+x0[0]",1);
	trans->set_intfunc("y1[0]+0.5",1);

	net2->AddProc(proc);

	//third processor form second network
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(2,trans);
	a=new CString("1_2inint.dat");
	pin=new CInput(0,a);
	proc->AddPort(pin,true);
	pout=new COutput(1);
	proc->AddPort(pout,false);
	trans->Set(3);
	trans->set_extfunc("y1[0]+x0[0]",1);
	trans->set_intfunc("y1[0]+0.5",1);

	net2->AddProc(proc);

	//wire for second network
	net2->AddParentProc(0,0,0,0);
	net2->AddParentProc(3,1,0,1);
	net2->AddParentProc(1,0,1,0);
	net2->AddParentProc(2,1,2,1);
	net2->AddProcProc(1,1,2,0);

	//third network
	net3=new CNetworkS(3);
	CGInput **ppin;
	ppin=(CGInput **)calloc(4,sizeof(CGInput *));
	//input ports and sources for third network
	pin=new CInput(0);
	pin->SetDim(1);
	ppin[0]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net3->AddPort(pin,true);
	pin=new CInput(1);
	pin->SetDim(1);
	ppin[1]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net3->AddPort(pin,true);
	pin=new CInput(2);
	pin->SetDim(1);
	ppin[2]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net3->AddPort(pin,true);
	pin=new CInput(3);
	pin->SetDim(1);
	ppin[3]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net3->AddPort(pin,true);
	//output ports and files
	a=new CString("1_2out4.dat");
	pout=new COutput(4,a);
	pout->SetDim(1);
	net3->AddPort(pout,false);
	a=new CString("1_2out5.dat");
	pout=new COutput(5,a);
	pout->SetDim(1);
	net3->AddPort(pout,false);
	a=new CString("1_2out6.dat");
	pout=new COutput(6,a);
	pout->SetDim(1);
	net3->AddPort(pout,false);
	a=new CString("1_2out7.dat");
	pout=new COutput(7,a);
	pout->SetDim(1);
	net3->AddPort(pout,false);

	net3->AddNetwork(net1);
	net3->AddNetwork(net2);

	//wires for third network
	net3->AddParentNet(0,0,2,0);
	net3->AddParentNet(1,1,2,0);
	net3->AddParentNet(6,2,2,1);
	net3->AddParentNet(7,3,2,1);
	net3->AddParentNet(2,0,1,0);
	net3->AddParentNet(3,1,1,0);
	net3->AddParentNet(4,2,1,1);
	net3->AddParentNet(5,3,1,1);
	//test vectors

	net3->DisableCoord();
	net2->DisableCoord();
	net1->DisableCoord();
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
	ppin[2]->SetTime(2);
	ppin[2]->SetWTime(2);
	ppin[2]->Set();
	ppin[2]->RecvMsg(2,2,NULL);
	net3->receivemsg(1,2,NULL);
	net3->receivemsg(1,3,NULL);
	ppin[0]->SetTime(4);
	ppin[0]->SetWTime(4);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,4,NULL);
	ppin[3]->SetTime(4);
	ppin[3]->SetWTime(4);
	ppin[3]->Set();
	ppin[3]->RecvMsg(2,4,NULL);
	net3->receivemsg(1,4,NULL);
	ppin[0]->SetTime(5);
	ppin[0]->SetWTime(5);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,5,NULL);
	ppin[1]->SetTime(5);
	ppin[1]->SetWTime(5);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,5,NULL);
	ppin[2]->SetTime(5);
	ppin[2]->SetWTime(5);
	ppin[2]->Set();
	ppin[2]->RecvMsg(2,5,NULL);
	ppin[3]->SetTime(5);
	ppin[3]->SetWTime(5);
	ppin[3]->Set();
	ppin[3]->RecvMsg(2,5,NULL);
	net3->receivemsg(1,5,NULL);
	ppin[0]->SetTime(6);
	ppin[0]->SetWTime(6);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,6,NULL);
	ppin[2]->SetTime(6);
	ppin[2]->SetWTime(6);
	ppin[2]->Set();
	ppin[2]->RecvMsg(2,6,NULL);
	net3->receivemsg(1,6,NULL);
	net3->receivemsg(1,7,NULL);
	net3->receivemsg(1,8,NULL);
	ppin[3]->SetTime(9);
	ppin[3]->SetWTime(9);
	ppin[3]->Set();
	ppin[3]->RecvMsg(2,9,NULL);
	net3->receivemsg(1,9,NULL);
	net3->receivemsg(1,10,NULL);
	net3->receivemsg(1,11,NULL);
	net3->receivemsg(1,12,NULL);
	net3->PrintData();
	delete net3;
}

void Cfunctionality::testBuses()
{
	CGNetworkS *net;
	CGOutput *pout;
	CGInput *pin;
	CGInput **ppin;
	long M=3;
	long i;
	CString *a;
	ppin=(CGInput **)calloc(M,sizeof(CGInput *));
	net=new CGNetworkS(0);
	for(i=0;i<M;i++)
	{
		pin=new CGInput(i);
		a=new CString("1.0");
		pin->SetGenerator(a);
		delete a;
		ppin[i]=pin;
		pin->SetDim(1);
		net->AddPort(pin,true);
	}
	a=new CString("output.dat");
	pout=new CGOutput(M,a);
	pout->SetDim(M);
	net->AddPort(pout,false);

	CGBus *bus;
	bus=new CGBus(0,false);
	bus->SetSync(true);
	pout=new CGOutput(0);
	pout->SetDim(M);
	bus->AddPort(pout,false);
	for(i=0;i<M;i++)
	{
		pin=new CGInput(i+1);
		pin->SetDim(1);
		bus->AddPort(pin,true);
	}
	
	net->AddProcP(bus);
	//add wires
	for(i=0;i<M;i++)
		net->AddParentProc(i,i+1,0,0);
	net->AddParentProc(M,0,0,1);
	//test vectors
	net->DisableCoord();
	net->receivemsg(0,0,NULL);
	for(i=0;i<10;i++)
	{
		if((i%2)==0)
		{
			for(long j=0;j<M;j++)
			{
				ppin[j]->SetTime(i);
				ppin[j]->SetWTime(i);
				ppin[j]->Set();
				ppin[j]->RecvMsg(2,i,NULL);
			}
		}
//		else net->receivemsg(1,i,NULL);
	}
	net->PrintData();
	delete net;
}

void Cfunctionality::testDistributions()
{
	CGNetworkS *net;
	CGOutput *pout;
	CGInput *pin;
	CGInput **ppin;
	long M=4;
	long i;
	CString *a;
	ppin=(CGInput **)calloc(1,sizeof(CGInput *));
	net=new CGNetworkS(0);
	for(i=0;i<M;i++)
	{
		pout=new CGOutput(i+1);
		pout->SetDim(1);
		net->AddPort(pout,false);
	}
	a=new CString("input.dat");
	pin=new CGInput(0,a);
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	pin->SetDim(1);
	ppin[0]=pin;
	net->AddPort(pin,true);

	CGDistributionSecv *dsecv;
	dsecv=new CGDistributionSecv(0,false);
	pin=new CGInput(0);
	pin->SetDim(1);
	dsecv->AddPort(pin,true);
	for(i=0;i<M;i++)
	{
		a=new CString();
		a->Format(_T("out%d.dat"),i+1);
		pout=new CGOutput(i+1,a);
		pout->SetDim(1);
		dsecv->AddPort(pout,false);
	}
	
	net->AddProcP(dsecv);
	//add wires
	for(i=0;i<M;i++)
		net->AddParentProc(i+1,i+1,0,1);
	net->AddParentProc(0,0,0,0);
	//test vectors
	//net->DisableCoord();
	net->receivemsg(0,0,NULL);
	for(i=0;i<10;i++)
	{
		if((i%2)==0)
		{
			ppin[0]->SetTime(i);
			ppin[0]->SetWTime(i);
			ppin[0]->Set();
			ppin[0]->RecvMsg(2,i,NULL);
		}
//		else net->receivemsg(3,i,NULL);
	}
	net->PrintData();
	delete net;

}

void Cfunctionality::testMDM()
{
	CGNetworkS *net;
	CGInput *pin;
	CGOutput *pout;
	CGInput **ppin;
	CString *a;
	long M=4;
	long i,j;
	ppin=(CGInput **)calloc(M,sizeof(CGInput *));
	//master network
	net=new CGNetworkS(0);
	for(i=0;i<M;i++)
	{
		a=new CString();
		a->Format(_T("in%d.dat"),i);
		pin=new CGInput(i,a);
		a=new CString("1.0");
		pin->SetGenerator(a);
		delete a;
		pin->SetDim(1);
		ppin[i]=pin;
		net->AddPort(pin,true);
	}
	for(i=M;i<2*M;i++)
	{
		a=new CString();
		a->Format(_T("out%d.dat"),i);
		pout=new CGOutput(i,a);
		pout->SetDim(1);
		net->AddPort(pout,false);
	}
	CGDistributionBus *bus;
	bus=new CGDistributionBus(0,true); // M to 1
	bus->SetType(false);
	bus->SetSN(true);
	pout=new CGOutput(0);
	pout->SetDim(1);
	bus->AddPort(pout,false);
	for(i=1;i<M+1;i++)
	{
		pin=new CGInput(i);
		bus->AddPort(pin,true);
	}
	net->AddProcP(bus);

	bus=new CGDistributionBus(1,true); //1 to M
	bus->SetType(true);
	bus->SetSN(true);
	a=new CString("int.dat");
	pin=new CGInput(0,a);
	pin->SetDim(1);
	bus->AddPort(pin,true);
	for(i=1;i<M+1;i++)
	{
		pout=new CGOutput(i);
		bus->AddPort(pout,false);
	}
	net->AddProcP(bus);
	//wires
	for(i=0,j=1;i<M;i++,j++)
		net->AddParentProc(i,j,0,0);
	for(i=M,j=1;i<2*M;i++,j++)
		net->AddParentProc(i,j,1,1);
	net->AddProcProc(0,0,1,0);
	//test vectors
	//net->DisableCoord();
	net->receivemsg(0,0,NULL);
	for(i=0;i<M;i++)
	{
			ppin[i]->SetTime(i);
			ppin[i]->SetWTime(i);
			ppin[i]->Set();
			ppin[i]->RecvMsg(2,i,NULL);
	}
	net->receivemsg(3,i,NULL);
	net->PrintData();
	delete net;
}

void Cfunctionality::testmprocs()
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
	net->AddProc(proc);
	a=new CString("in0.dat");
	pin=new CGInput(0,a);
	proc->AddPort(pin,true);
	a=new CString("in1.dat");
	pin=new CGInput(1,a);
	proc->AddPort(pin,true);
	a=new CString("intp0.dat");
	pout=new CGOutput(2,a);
	proc->AddPort(pout,false);
	a=new CString("intp1.dat");
	pout=new CGOutput(3,a);
	proc->AddPort(pout,false);
	trans->Set(1);
	trans->set_extfunc("y2[0]+x1[0]",2);
	trans->set_intfunc("y2[0]+0.5",2);
	trans->set_extfunc("y3[0]+x0[0]",3);
	trans->set_intfunc("y3[0]+0.5",3);

	//second processor from network
	a=new CString("1.0");
	trans=new CGTransitionS(a);
	delete a;
	proc=new CGProcessorS(NULL,1,trans,true);
	proc->SetRIType(true);
	net->AddProc(proc);
	pin=new CGInput(0);
	proc->AddPort(pin,true);
	pin=new CGInput(1);
	proc->AddPort(pin,true);
	pout=new CGOutput(2);
	proc->AddPort(pout,false);
	trans->Set(2);
	trans->set_extfunc("x0[0]+x1[0]+1",2);
	trans->set_intfunc("y2[0]+0.5",2);

	//add wires 
	net->AddParentProc(0,0,0,0);
	net->AddParentProc(1,1,0,0);
	net->AddParentProc(3,3,0,1);
	net->AddParentProc(1,1,1,0);
	net->AddParentProc(2,2,1,1);
	net->AddProcProc(0,2,1,0);
	
	//test vectors
//	net->DisableCoord();
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

void Cfunctionality::testcps()
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
	pin=new CGInput(1);
	ppin[1]=pin;
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	net->AddPort(pin,true);
	//output ports and files
	a=new CString("out2cps.dat");
	pout=new CGOutput(2,a);
	net->AddPort(pout,false);
	a=new CString("out3cps.dat");
	pout=new CGOutput(3,a);
	net->AddPort(pout,false);

	//first processor from network
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CGProcessor(NULL,0,trans,false);
	proc->SetRIType(true);
	pin=new CGInput(0);
	proc->AddPort(pin,true);
	pout=new CGOutput(1);
	proc->AddPort(pout,false);
	trans->Set(1);
	trans->set_extfunc("y1[0]+x0[0]",1);
	trans->set_intfunc("y1[0]+0.5",1);

	net->AddProc(proc);
/*
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

*/
	proc1=proc->copy(net,1);
	net->AddProc(proc1);

//	net->AddProc(proc);

	//add wires 
	net->AddParentProc(0,0,0,0);
	net->AddParentProc(3,1,0,1);
	net->AddParentProc(1,0,1,0);
	net->AddParentProc(2,1,1,1);
	
	//test vectors   
//	net->DisableCoord();
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
//	net->receivemsg(3,time-1,NULL);
	net->PrintData();
	delete net;
}

void Cfunctionality::testmprocsn()
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
	proc->SetRIType(true);
	net->AddProc(proc);
	a=new CString("in0n.dat");
	pin=new CGInput(0,a);
	proc->AddPort(pin,true);
	a=new CString("in1n.dat");
	pin=new CGInput(1,a);
	proc->AddPort(pin,true);
	a=new CString("intp0n.dat");
	pout=new CGOutput(2,a);
	proc->AddPort(pout,false);
	a=new CString("intp1n.dat");
	pout=new CGOutput(3,a);
	proc->AddPort(pout,false);
	trans->Set(1);
	trans->set_extfunc("y2[0]+x1[0]",2);
	trans->set_intfunc("y2[0]+0.5",2);
	trans->set_extfunc("y3[0]+x0[0]",3);
	trans->set_intfunc("y3[0]+0.5",3);

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

void Cfunctionality::testDQL()
{
	const double CLK=0.5;
	long i;
	CGNetworkS *net;
	CProcessor *proc;
	CString *a;
	CGOutput *pout;
	CGInput *pin;
	CGInput **ppin;
	CTransition *trans;
	CGDistributionQ *qdistrib;
	ppin=(CGInput **)calloc(1,sizeof(CGInput *));

	net=new CGNetworkS(0);

	net->SetTypeQueue(false);
	//nr of input clients
	a=new CString("in.dat");
	pin=new CGInput(0,a);
	ppin[0]=pin;
	net->AddPort(pin,true);
	//wait time
	a=new CString("out.dat");
	pout=new CGOutput(1,a);
	net->AddPort(pout,false);
	//processors from network
//distribtution queue
	qdistrib=new CGDistributionQ(0,false);
	qdistrib->DisableS();
	qdistrib->SetSources(2);
	net->AddProcP(qdistrib);
	pin=new CGInput(0);
	qdistrib->AddPort(pin,true);
	pin=new CGInput(1);
	qdistrib->AddPort(pin,true);
	a=new CString("02.dat");
	pout=new CGOutput(2,a);
	qdistrib->AddPort(pout,false);
	net->AddParentProc(0,0,0,0);
	//active processor
	a=new CString("3.0");
	trans=new CTransition(a);
	delete a;
	proc=new CProcessor(1,trans,false);
	proc->SetMemInput(false);
	proc->SetGeneral(false);
	proc->EnableOut(false);
	trans->Set(1);
	proc->DisableQ();
	proc->SetRType(false);
	proc->SetIgnore(true);
	proc->SetFirst(true);
	proc->SetFirstI(true);
	net->AddProc(proc);
	pin=new CGInput(0);
	proc->AddPort(pin,true);
	a=new CString("11.dat");
	pout=new CGOutput(1,a);
	proc->AddPort(pout,false);
	a=new CString("test.dat");
	pout=new CGOutput(2,a);
	proc->AddPort(pout,false);
	net->AddParentProc(1,2,1,1);
	net->AddProcProc(0,2,1,0);
	net->AddProcProc(1,1,0,1);

	//test vectors
//	net->DisableCoord();
	net->SetClockPrecision(CLK);
	net->receivemsg(0,0,NULL);
	double val=0.0;
	double vals;
	vals=1.0;
	net->receivemsg(1,0,NULL);
	net->receivemsg(1,0.5,NULL);
	val=1.0;
	cout<<val<<endl;
	ppin[0]->SetTime(val);
	ppin[0]->SetWTime(val);
	ppin[0]->Set(&vals);
	ppin[0]->RecvMsg(2,val,NULL);
	net->receivemsg(1,val,NULL);
	val+=CLK;
	net->receivemsg(1,val,NULL);
	val+=CLK;
	cout<<val<<endl;
	ppin[0]->SetTime(val);
	ppin[0]->SetWTime(val);
	ppin[0]->Set(&vals);
	ppin[0]->RecvMsg(2,val,NULL);
	net->receivemsg(1,val,NULL);
	val+=CLK;
	net->receivemsg(1,val,NULL);
	val+=CLK;
	cout<<val<<endl;
	ppin[0]->SetTime(val);
	ppin[0]->SetWTime(val);
	ppin[0]->Set(&vals);
	ppin[0]->RecvMsg(2,val,NULL);
	net->receivemsg(1,val,NULL);
	val+=CLK;
	for(i=0;i<20;i++)
	{
		net->receivemsg(1,val,NULL);
		val+=CLK;
	}
	net->receivemsg(3,val-CLK,NULL);
	net->PrintData();
	delete net;
}

void Cfunctionality::testSum()
{
	CGNetworkS *net;
	CGSum *sum;
	CGInput *pin;
	CGOutput *pout;
	CString *a;
	CGInput **ppin;
	ppin=(CGInput **)calloc(2,sizeof(CGInput *));

	net=new CGNetworkS(0);

	a=new CString("in0.dat");
	pin=new CGInput(0,a);
	a=new CString("1.0");
	pin->SetDim(2);
	pin->SetGenerator(a,0);
	pin->SetGenerator(a,1);
	net->AddPort(pin,true);
	ppin[0]=pin;
	delete a;
	a=new CString("in1.dat");
	pin=new CGInput(1,a);
	a=new CString("1.0");
	pin->SetDim(3);
	pin->SetGenerator(a,0);
	pin->SetGenerator(a,1);
	pin->SetGenerator(a,2);
	net->AddPort(pin,true);
	ppin[1]=pin;
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

	//net->DisableCoord();
	double CLK=0.5;
	net->SetClockPrecision(CLK);
	double time=0.0;
	net->receivemsg(0,time,NULL);
	net->receivemsg(1,time,NULL);
	time=0.5;
	ppin[0]->SetTime(time);
	ppin[0]->SetWTime(time);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,time,NULL);
	net->receivemsg(1,time,NULL);
	time=1.0;
	ppin[0]->SetTime(time);
	ppin[0]->SetWTime(time);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,time,NULL);
	ppin[1]->SetTime(time);
	ppin[1]->SetWTime(time);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,time,NULL);
	net->receivemsg(1,time,NULL);
	time=1.5;
	ppin[0]->SetTime(time);
	ppin[0]->SetWTime(time);
	ppin[0]->Set();
	ppin[0]->RecvMsg(2,time,NULL);
	net->receivemsg(1,time,NULL);
	time=2.0;
	ppin[1]->SetTime(time);
	ppin[1]->SetWTime(time);
	ppin[1]->Set();
	ppin[1]->RecvMsg(2,time,NULL);
	net->receivemsg(1,time,NULL);
	time=2.5;
	net->receivemsg(1,time,NULL);
	net->PrintData();
	delete net;
}	

void Cfunctionality::testDistributions_2()
{
	CGNetworkS *net;
	CGProcessor *proc;
	CGOutput *pout;
	CGInput *pin;
	CGInput **ppin;
	CGTransition *trans;
	long i;
	CString *a;
	ppin=(CGInput **)calloc(1,sizeof(CGInput *));
	
	net=new CGNetworkS(0);
	
	a=new CString("output1.dat");
	pout=new CGOutput(1,a);
	pout->SetDim(1);
	net->AddPort(pout,false);
	a=new CString("output2.dat");
	pout=new CGOutput(2,a);
	pout->SetDim(1);
	net->AddPort(pout,false);

	a=new CString("input.dat");
	pin=new CGInput(0,a);
	a=new CString("1.0");
	pin->SetGenerator(a);
	delete a;
	pin->SetDim(1);
	ppin[0]=pin;
	net->AddPort(pin,true);

	CGDistributionSecv *dsecv;
	dsecv=new CGDistributionSecv(0,false);
	pin=new CGInput(0);
	pin->SetDim(1);
	dsecv->AddPort(pin,true);
	a=new CString("out1.dat");
	pout=new CGOutput(1,a);
	pout->SetDim(1);
	dsecv->AddPort(pout,false);
	a=new CString("out2.dat");
	pout=new CGOutput(2,a);
	pout->SetDim(1);
	dsecv->AddPort(pout,false);
	
	net->AddProcP(dsecv);

	//first processor
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(1,trans);
	proc->SetRType(false);
	a=new CString("ini1.dat");
	pin=new CInput(0,a);
	proc->AddPort(pin,true);
	a=new CString("outi1.dat");
	pout=new COutput(1,a);
	proc->AddPort(pout,false);
	trans->Set(1);
	trans->set_extfunc("x0[0]+y1[0]",1);
	trans->set_intfunc("y1[0]+0.5",1);
	net->AddProc(proc);

	//second processor
	a=new CString("1.0");
	trans=new CGTransition(a);
	delete a;
	proc=new CProcessor(2,trans);
	proc->SetRType(false);
	a=new CString("ini2.dat");
	pin=new CInput(0,a);
	proc->AddPort(pin,true);
	a=new CString("outi2.dat");
	pout=new COutput(1,a);
	proc->AddPort(pout,false);
	trans->Set(1);
	trans->set_extfunc("x0[0]+y1[0]",1);
	trans->set_intfunc("y1[0]+0.5",1);
	net->AddProc(proc);

	//add wires
	net->AddParentProc(0,0,0,0);
	net->AddProcProc(0,1,1,0);
	net->AddProcProc(0,2,2,0);
	net->AddParentProc(1,1,1,1);
	net->AddParentProc(2,1,2,1);
	//test vectors
	//net->DisableCoord();
	net->receivemsg(0,0,NULL);
	for(i=0;i<10;i++)
	{
		if((i%2)==0)
		{
			ppin[0]->SetTime(i);
			ppin[0]->SetWTime(i);
			ppin[0]->Set();
			ppin[0]->RecvMsg(2,i,NULL);
		}
		net->receivemsg(1,i,NULL);
	}
	net->PrintData();
	delete net;
}

void Cfunctionality::testDQL_2()
{
	const double CLK=0.5;
	long i;
	CGNetworkS *net;
	CProcessor *proc;
	CString *a;
	CGOutput *pout;
	CGInput *pin;
	CGInput **ppin;
	CTransition *trans;
	CGDistributionQ *qdistrib;
	ppin=(CGInput **)calloc(1,sizeof(CGInput *));

	net=new CGNetworkS(0);

	net->SetTypeQueue(false);
	//nr of input clients
	a=new CString("in.dat");
	pin=new CGInput(0,a);
	ppin[0]=pin;
	net->AddPort(pin,true);
	//wait time
	a=new CString("out1.dat");
	pout=new CGOutput(1,a);
	net->AddPort(pout,false);
	a=new CString("out2.dat");
	pout=new CGOutput(2,a);
	net->AddPort(pout,false);
	//processors from network
//distribtution queue
	qdistrib=new CGDistributionQ(0,false);
	qdistrib->DisableS();
	qdistrib->SetSources(1);
	net->AddProcP(qdistrib);
	pin=new CGInput(0);
	qdistrib->AddPort(pin,true);
	pin=new CGInput(1);
	qdistrib->AddPort(pin,true);
	a=new CString("02.dat");
	pout=new CGOutput(2,a);
	qdistrib->AddPort(pout,false);
	pin=new CGInput(3);
	qdistrib->AddPort(pin,true);
	a=new CString("04.dat");
	pout=new CGOutput(4,a);
	qdistrib->AddPort(pout,false);
	net->AddParentProc(0,0,0,0);
	//first active processor
	a=new CString("3.0");
	trans=new CTransition(a);
	delete a;
	proc=new CProcessor(1,trans,false);
	proc->SetMemInput(false);
	proc->SetGeneral(false);
	proc->EnableOut(false);
	trans->Set(1);
	proc->DisableQ();
	proc->SetRType(false);
	proc->SetIgnore(true);
	proc->SetFirst(true);
	proc->SetFirstI(true);
	net->AddProc(proc);
	pin=new CGInput(0);
	proc->AddPort(pin,true);
	a=new CString("p1_1.dat");
	pout=new CGOutput(1,a);
	proc->AddPort(pout,false);
	pout=new CGOutput(2);
	proc->AddPort(pout,false);
	//second active processor
	a=new CString("3.0");
	trans=new CTransition(a);
	delete a;
	proc=new CProcessor(2,trans,false);
	proc->SetMemInput(false);
	proc->SetGeneral(false);
	proc->EnableOut(false);
	trans->Set(1);
	proc->DisableQ();
	proc->SetRType(false);
	proc->SetIgnore(true);
	proc->SetFirst(true);
	proc->SetFirstI(true);
	net->AddProc(proc);
	pin=new CGInput(0);
	proc->AddPort(pin,true);
	a=new CString("p2_1.dat");
	pout=new CGOutput(1,a);
	proc->AddPort(pout,false);
	pout=new CGOutput(2);
	proc->AddPort(pout,false);

	net->AddParentProc(1,2,1,1);
	net->AddProcProc(0,2,1,0);
	net->AddProcProc(1,1,0,1);
	net->AddParentProc(2,2,2,1);
	net->AddProcProc(0,4,2,0);
	net->AddProcProc(2,1,0,3);
	//test vectors
	//net->DisableCoord();
	net->SetClockPrecision(CLK);
	net->receivemsg(0,0,NULL);
	double val=0.0;
	double vals;
	vals=1.0;
	net->receivemsg(1,0,NULL);
	net->receivemsg(1,0.5,NULL);
	val=1.0;
	cout<<val<<endl;
	ppin[0]->SetTime(val);
	ppin[0]->SetWTime(val);
	ppin[0]->Set(&vals);
	ppin[0]->RecvMsg(2,val,NULL);
	net->receivemsg(1,val,NULL);
	val+=CLK;
	net->receivemsg(1,val,NULL);
	val+=CLK;
	cout<<val<<endl;
	ppin[0]->SetTime(val);
	ppin[0]->SetWTime(val);
	ppin[0]->Set(&vals);
	ppin[0]->RecvMsg(2,val,NULL);
	net->receivemsg(1,val,NULL);
	val+=CLK;
	net->receivemsg(1,val,NULL);
	val+=CLK;
	cout<<val<<endl;
	ppin[0]->SetTime(val);
	ppin[0]->SetWTime(val);
	ppin[0]->Set(&vals);
	ppin[0]->RecvMsg(2,val,NULL);
	net->receivemsg(1,val,NULL);
	val+=CLK;
	for(i=0;i<20;i++)
	{
		net->receivemsg(1,val,NULL);
		val+=CLK;
	}
	net->receivemsg(3,val-CLK,NULL);
	net->PrintData();
	delete net;
}
void Cfunctionality::testDQL_2_S()
{
	const double CLK=0.5;
	long i;
	CGNetworkS *net;
	CSProcessor *proc;
	CString *a;
	CGOutput *pout;
	CGInput *pin;
	CGInput **ppin;
	CTransition *trans;
	CGDistributionQ *qdistrib;
	ppin=(CGInput **)calloc(1,sizeof(CGInput *));

	net=new CGNetworkS(0);

	net->SetTypeQueue(false);
	//nr of input clients
	a=new CString("in.dat");
	pin=new CGInput(0,a);
	ppin[0]=pin;
	net->AddPort(pin,true);
	//wait time
	a=new CString("out1.dat");
	pout=new CGOutput(1,a);
	net->AddPort(pout,false);
	a=new CString("out2.dat");
	pout=new CGOutput(2,a);
	net->AddPort(pout,false);
	//processors from network
//distribtution queue
	qdistrib=new CGDistributionQ(0,false);
	qdistrib->DisableS();
	qdistrib->SetSources(1);
	net->AddProcP(qdistrib);
	pin=new CGInput(0);
	qdistrib->AddPort(pin,true);
	pin=new CGInput(1);
	qdistrib->AddPort(pin,true);
	a=new CString("02.dat");
	pout=new CGOutput(2,a);
	qdistrib->AddPort(pout,false);
	pin=new CGInput(3);
	qdistrib->AddPort(pin,true);
	a=new CString("04.dat");
	pout=new CGOutput(4,a);
	qdistrib->AddPort(pout,false);
	net->AddParentProc(0,0,0,0);

	//first active processor
	a=new CString("3.0");
	trans=new CTransition(a);
	delete a;
	proc=new CSProcessor(net,1,1,2,trans,false);
	proc->SetMemInput(false);
	proc->SetGeneral(false);
	proc->EnableOut(false);
	trans->Set(1);
	proc->DisableQ();
	proc->SetRType(false);
	proc->SetIgnore(true);
	proc->SetFirst(true);
	proc->SetFirstI(true);
	net->AddProc(proc);
	a=new CString("p1_1.dat");
	proc->SetFilePort(1,a);

	//second active processor
	a=new CString("3.0");
	trans=new CTransition(a);
	delete a;
	proc=new CSProcessor(net,2,1,2,trans,false);
	proc->SetMemInput(false);
	proc->SetGeneral(false);
	proc->EnableOut(false);
	trans->Set(1);
	proc->DisableQ();
	proc->SetRType(false);
	proc->SetIgnore(true);
	proc->SetFirst(true);
	proc->SetFirstI(true);
	net->AddProc(proc);
	a=new CString("p2_1.dat");
	proc->SetFilePort(1,a);

	net->AddParentProc(1,2,1,1);
	net->AddProcProc(0,2,1,0);
	net->AddProcProc(1,1,0,1);
	net->AddParentProc(2,2,2,1);
	net->AddProcProc(0,4,2,0);
	net->AddProcProc(2,1,0,3);
	//test vectors
	//net->DisableCoord();
	net->SetClockPrecision(CLK);
	net->receivemsg(0,0,NULL);
	double val=0.0;
	double vals;
	vals=1.0;
	net->receivemsg(1,0,NULL);
	net->receivemsg(1,0.5,NULL);
	val=1.0;
	cout<<val<<endl;
	ppin[0]->SetTime(val);
	ppin[0]->SetWTime(val);
	ppin[0]->Set(&vals);
	ppin[0]->RecvMsg(2,val,NULL);
	net->receivemsg(1,val,NULL);
	val+=CLK;
	net->receivemsg(1,val,NULL);
	val+=CLK;
	cout<<val<<endl;
	ppin[0]->SetTime(val);
	ppin[0]->SetWTime(val);
	ppin[0]->Set(&vals);
	ppin[0]->RecvMsg(2,val,NULL);
	net->receivemsg(1,val,NULL);
	val+=CLK;
	net->receivemsg(1,val,NULL);
	val+=CLK;
	cout<<val<<endl;
	ppin[0]->SetTime(val);
	ppin[0]->SetWTime(val);
	ppin[0]->Set(&vals);
	ppin[0]->RecvMsg(2,val,NULL);
	net->receivemsg(1,val,NULL);
	val+=CLK;
	for(i=0;i<20;i++)
	{
		net->receivemsg(1,val,NULL);
		val+=CLK;
	}
	net->receivemsg(3,val-CLK,NULL);
	net->PrintData();
	delete net;
}
