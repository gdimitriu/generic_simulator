// GNetworkS.cpp: implementation of the CGNetworkS class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the implementation of network class. This clasa holds all 
	processors and connection, and with this class the user will interract.
	
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
#include <iostream>
#include <stdlib.h>
#include "GNetworkS.h"
#include "GInput.h"
#include "GOutput.h"
#include "GCElem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
IMPLEMENT_SERIAL(CGNetworkS,CObject,1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGNetworkS::CGNetworkS()
{
	m_return=NULL;
	m_nin=0;
	m_nout=0;
	m_btype=true;
	m_time=0.0;
	m_time_ext=0.0;
	m_wtype=false;
	m_intype=false;
	m_qtype=false;
	m_procs=NULL;
	m_nets=NULL;
	m_wout=NULL;
	m_procsp=NULL;
	m_nnets=0;
	m_nprocs=0;
	m_nprocsp=0;
	m_time=-1.0;
	m_parent=NULL;
	m_name=0;
	m_sims=false;
	m_adds=false;
	m_coordinator=NULL;
	m_disable_coord=false;
	m_CLKP=0.01;
	m_CLK=1.0;
	m_manual_start=false;
	m_netpos=m_procpos=m_procppos=0;
	m_iportpos=m_oportpos=0;
}

CGNetworkS::CGNetworkS(CObject *parent,long i)
{
	m_parent=parent;
	m_name=i;
	m_return=NULL;
	m_nin=0;
	m_nout=0;
	m_btype=true;
	m_time=0.0;
	m_time_ext=0.0;
	m_wtype=false;
	m_intype=false;
	m_qtype=false;
	m_procs=NULL;
	m_nets=NULL;
	m_wout=NULL;
	m_procsp=NULL;
	m_nnets=0;
	m_nprocs=0;
	m_nprocsp=0;
	m_time=-1.0;
	m_sims=false;
	m_adds=false;
	m_coordinator=NULL;
	m_disable_coord=false;
	m_CLKP=0.01;
	m_CLK=1.0;
	m_manual_start=false;
	m_netpos=m_procpos=m_procppos=0;
	m_iportpos=m_oportpos=0;
}

CGNetworkS::CGNetworkS(long i)
{
	m_return=NULL;
	m_nin=0;
	m_nout=0;
	m_btype=true;
	m_time=0.0;
	m_time_ext=0.0;
	m_wtype=false;
	m_intype=false;
	m_qtype=false;
	m_procs=NULL;
	m_nets=NULL;
	m_wout=NULL;
	m_procsp=NULL;
	m_nnets=0;
	m_nprocs=0;
	m_nprocsp=0;
	m_time=-1.0;
	m_name=i;
	m_parent=NULL;
	m_sims=false;
	m_adds=false;
	m_coordinator=NULL;
	m_disable_coord=false;
	m_CLKP=0.01;
	m_CLK=1.0;
	m_manual_start=false;
	m_netpos=m_procpos=m_procppos=0;
	m_iportpos=m_oportpos=0;
}



void CGNetworkS::SetName(long name)
{
	m_name=name;
}

CGNetworkS::~CGNetworkS()
{
	int i;
	int nr;
	if(m_procs!=NULL) free(m_procs);
	if(m_nets!=NULL) free(m_nets);
	if(m_wout!=NULL) free(m_wout);
	if(m_procsp!=NULL) free(m_procsp);

	nr=m_inputs.GetSize();
	for(i=0;i<nr;i++)
	{
		CGInput *tin;
		tin=(CGInput *)(m_inputs.GetAt(i));
		delete tin;
	}
	m_inputs.RemoveAll();

	nr=m_WIn.GetSize();
	for(i=0;i<nr;i++)
	{
		CGWire *tmp;
		tmp=(CGWire *)m_WIn.GetAt(i);
		delete tmp;
	}
	m_WIn.RemoveAll();

	nr=m_outputs.GetSize();
	for(i=0;i<nr;i++)
	{
		CGOutput *tout;
		tout=(CGOutput *)(m_outputs.GetAt(i));
		delete tout;
	}
	m_outputs.RemoveAll();

	nr=m_WOut.GetSize();
	for(i=0;i<nr;i++)
	{
		CGWire *tmp;
		tmp=(CGWire *)m_WOut.GetAt(i);
		delete tmp;
	}
	m_WOut.RemoveAll();
	
	nr=m_WInt.GetSize();
	for(i=0;i<nr;i++)
	{
		CGWire *tmp;
		tmp=(CGWire *)m_WInt.GetAt(i);
		delete tmp;
	}
	m_WInt.RemoveAll();

	nr=m_processors.GetSize();
	for(i=0;i<nr;i++)
	{
		CGProcessor *tmp;
		tmp=(CGProcessor *)(m_processors.GetAt(i));
		delete tmp;
	}
	m_processors.RemoveAll();

	nr=m_processorsp.GetSize();
	for(i=0;i<nr;i++)
	{
		CGProcessor *tmp;
		tmp=(CGProcessor *)(m_processorsp.GetAt(i));
		delete tmp;
	}
	m_processorsp.RemoveAll();

	nr=m_networks.GetSize();
	for(i=0;i<nr;i++)
	{
		CGNetworkS *tmp;
		tmp=(CGNetworkS *)(m_networks.GetAt(i));
		delete tmp;
	}
	m_networks.RemoveAll();
	m_aprocs.RemoveAll();
	m_anets.RemoveAll();
	m_aprocs.FreeExtra();
	m_anets.FreeExtra();
	if(m_coordinator!=NULL) delete m_coordinator;
}
long CGNetworkS::GetName()
{
//
//return the name of the network
//
	return m_name;
}

void CGNetworkS::SetParent(CObject *parent)
{
//
//set the parent of the network
//
	m_parent=parent;
}

int CGNetworkS::Add(CObject *ob)
{
	int i;
	if(ob->IsKindOf(RUNTIME_CLASS(CGInput))!=0)
	{
		try
		{
			((CGInput *)ob)->SetParent((CObject *)this,2);
			m_inputs.Add(ob);
		}
		catch (CMemoryException *err)
		{
			AfxMessageBox("Out of Memory input port",MB_ICONSTOP|MB_OK);
			err->Delete();
			return -1;
		}
		m_nin++;
		if(m_sims==true) m_aports.Add(ob);
	}
	else if(ob->IsKindOf(RUNTIME_CLASS(CGOutput))!=0)
	{
		try
		{
			((CGOutput *)ob)->SetParent((CObject *)this,2);
			m_outputs.Add(ob);
		}
		catch (CMemoryException *err)
		{
			AfxMessageBox("Out of Memory output port",MB_ICONSTOP|MB_OK);
			err->Delete();
			return -1;
		}
		m_nout++;
		if(m_sims==true) m_aports.Add(ob);
	}
	else if(ob->IsKindOf(RUNTIME_CLASS(CGNetworkS))!=0)
	{
		((CGNetworkS *)ob)->SetParent(this);
		try
		{
			i=0;
			if(m_networks.GetSize()>0)
			{
				CGNetworkS *parc;
				parc=(CGNetworkS *)m_networks.GetAt(0);
				while(parc->GetName()<((CGNetworkS *)ob)->GetName())
				{
					i++;
					if(i>=m_networks.GetSize()) break;
					parc=(CGNetworkS *)m_networks.GetAt(i);
				}
				m_networks.InsertAt(i,ob,1);
			}
			else m_networks.Add(ob);
		}
		catch (CMemoryException *err)
		{
			AfxMessageBox("Out of Memory Network",MB_ICONSTOP|MB_OK);
			err->Delete();
			return -1;
		}
		m_nnets++;
		if(m_sims==true)
		{
			bool *temp=(bool *)calloc(m_networks.GetSize(),sizeof(bool));
			free(m_nets);
			m_nets=temp;
			m_adds=true;
			m_anets.Add(ob);
		}
	}
	return 0;
}

int CGNetworkS::AddPort(CObject *port, bool type)
{
//
//add a port given by it's pointer
//
	if(type==true)
	{
		try
		{
			((CGInput *)port)->SetParent((CObject *)this,2);
			m_inputs.Add(port);
		}
		catch (CMemoryException *err)
		{
			AfxMessageBox("Out of Memory input port",MB_ICONSTOP|MB_OK);
			err->Delete();
			return -1;
		}
		m_nin++;
		if(m_sims==true) m_aports.Add(port);
	}
	else
	{
		try
		{
			((CGOutput *)port)->SetParent((CObject *)this,2);
			m_outputs.Add(port);
		}
		catch (CMemoryException *err)
		{
			AfxMessageBox("Out of Memory output port",MB_ICONSTOP|MB_OK);
			err->Delete();
			return -1;
		}
		m_nout++;
		if(m_sims==true) m_aports.Add(port);
	}
	return 0;
}

CObject *CGNetworkS::GetParent()
{
//
//return the parent pointer
//
	return m_parent;
}
int CGNetworkS::GetDimPort(long port)
{
	long i;
	long N;
	N=m_inputs.GetSize();
	for(i=0;i<N;i++)
		if(((CGInput *)m_inputs.GetAt(i))->m_name==port)
		{
			return ((CGInput *)m_inputs.GetAt(i))->GetDim();
		}
	return -1;
}

CObject * CGNetworkS::GetPort(long port,int *type)
{
//
//return the a port given by it's name
//return type=1 if it is an input port and type=2 if it is an output port
//return type=0 if the port isn't here and also return NULL
//
	long i;
	long N;
	N=m_inputs.GetSize();
	for(i=0;i<N;i++)
		if(((CGInput *)m_inputs.GetAt(i))->m_name==port)
		{
			*type=1;
			return m_inputs.GetAt(i);
		}
	N=m_outputs.GetSize();
	for(i=0;i<N;i++)
		if(((CGOutput *)m_outputs.GetAt(i))->m_name==port)
		{
			*type=2;
			return m_outputs.GetAt(i);
		}
	*type=0;
	return NULL;
}

int CGNetworkS::AddNetwork(CObject *pnet)
{
//
//add a network given by it's pointer
//
	((CGNetworkS *)pnet)->SetParent(this);
	try
	{
		int i=0;
		if(m_networks.GetSize()>0)
		{
			CGNetworkS *parc;
			parc=(CGNetworkS *)m_networks.GetAt(0);
			while(parc->GetName()<((CGNetworkS *)pnet)->GetName())
			{
				i++;
				if(i>=m_networks.GetSize()) break;
				parc=(CGNetworkS *)m_networks.GetAt(i);
			}
			m_networks.InsertAt(i,pnet,1);
		}
		else m_networks.Add(pnet);
	}
	catch (CMemoryException *err)
	{
		AfxMessageBox("Out of Memory Network",MB_ICONSTOP|MB_OK);
		err->Delete();
		return -1;
	}
	m_nnets++;
	if(m_sims==true)
	{
		bool *temp=(bool *)calloc(m_networks.GetSize(),sizeof(bool));
		free(m_nets);
		m_nets=temp;
		m_adds=true;
		m_anets.Add(pnet);
	}
	return 0;
}

int CGNetworkS::AddProcP(CObject *ppr)
{
//
//add a passive processor given by his pointer
//
	((CGProcessor *)ppr)->SetParent(this);
	((CGProcessor *)ppr)->SetType(1);
	try
	{
		int i=0;
		if(m_processorsp.GetSize()>0)
		{
			CGProcessor *parc;
			parc=(CGProcessor *)(m_processorsp.GetAt(0));

			while(parc->GetName()<((CGProcessor *)ppr)->GetName())
			{
				i++;
				if(i>=m_processorsp.GetSize()) break;
				parc=(CGProcessor *)(m_processorsp.GetAt(i));
			}
			m_processorsp.InsertAt(i,ppr,1);
		}
		else m_processorsp.Add(ppr);
	}
	catch (CMemoryException *err)
	{
		AfxMessageBox("Out of Memory Pasive Processor",MB_ICONSTOP|MB_OK);
		err->Delete();
		return -1;
	}
	m_nprocsp++;
	if(m_sims==true)
	{
		bool *temp=(bool *)calloc(m_processorsp.GetSize(),sizeof(bool));
		free(m_procsp);
		m_procsp=temp;
		m_adds=true;
		m_aprocs.Add(ppr);
	}
	return 0;
}


int CGNetworkS::AddProc(CObject *ppr)
{
//
//add a processor given by his pointer
//
	((CGProcessor *)ppr)->SetParent(this);
	((CGProcessor *)ppr)->SetType(0);
	try
	{
		int i=0;
		if(m_processors.GetSize()>0)
		{
			CGProcessor *parc;
			parc=(CGProcessor *)(m_processors.GetAt(0));
			while(parc->GetName()<((CGProcessor *)ppr)->GetName())
			{
				i++;
				if(i>=m_processors.GetSize()) break;
				parc=(CGProcessor *)(m_processors.GetAt(i));
			}
			m_processors.InsertAt(i,ppr,1);
		}
		else m_processors.Add(ppr);
	}
	catch (CMemoryException *err)
	{
		AfxMessageBox("Out of Memory Processor",MB_ICONSTOP|MB_OK);
		err->Delete();
		return -1;
	}
	m_nprocs++;
	if(m_sims==true)
	{
		bool *temp=(bool *)calloc(m_processors.GetSize(),sizeof(bool));
		free(m_procs);
		m_procs=temp;
		m_adds=true;
		m_aprocs.Add(ppr);
	}
	return 0;
}

int CGNetworkS::AddParentProc(long in1, long in2, long p,int type)
{
//
//	if type=0 add a wire between input in1 from network to input in2 from processor p
//	if type=1 add a wire between output in1 from network to output in2 from processor p
//
	long N,i;
	CObject *tob;
	//we seek for the real processor
	CGProcessor *pproc;
	CGWire *pwire;
	N=m_processors.GetSize();
	for(i=0;i<N;i++)
	{
		pproc=(CGProcessor *)(m_processors.GetAt(i));
		if(pproc->GetName()==p) break;
	}
	if(i==N)
	{
		N=m_processorsp.GetSize();
		for(i=0;i<N;i++)
		{
			pproc=(CGProcessor *)(m_processorsp.GetAt(i));
			if(pproc->GetName()==p) break;
		}
		if(i==N)
		{
			AfxMessageBox("Wrong processor name at parent to processor",MB_ICONSTOP|MB_OK);
			return -1;
		}
	}
	if(type==0) //we have type input
	{
		//find the index in input array
		N=m_inputs.GetSize();
		for(i=0;i<N;i++)
		{
			tob=m_inputs.GetAt(i);
			if(((CGInput *)tob)->m_name==in1) break;
		}
		if(i==N)
		{
			AfxMessageBox("Wrong parent input at parent to processor",MB_ICONSTOP|MB_OK);
			return -1;
		}
		N=m_WIn.GetSize();
		for(i=0;i<N;i++)
		{
			pwire=(CGWire *)m_WIn.GetAt(i);
			if(pwire->m_parent==tob && pwire->m_type==type) break;
		}
		if(i==N) //we haven't found a previous wire
		{
			pwire=NULL;
			pwire=new CGWire(tob,type,this);
			try
			{
				m_WIn.Add(pwire);
			}
			catch (CMemoryException *err)
			{
				AfxMessageBox("Out of wire memory at parent to processor",MB_ICONSTOP|MB_OK);
				if(pwire!=NULL)
				{
					delete pwire;
					pwire=NULL;
				}
				err->Delete();
				return -1;
			}
		}
		//find the processor input
		N=pproc->GetInputNrPorts();
		for(i=0;i<N;i++)
		{
			tob=(pproc->m_inputs).GetAt(i);
			if(((CGInput *)tob)->m_name==in2) break;
		}
		if(i==N)
		{
			AfxMessageBox("Wrong processor input at parent to processor",MB_ICONSTOP|MB_OK);
			return -1;
		}
		pwire->Add(tob);
	}
	if(type==1) //we have type output
	{
		//find the index in input array
		N=m_outputs.GetSize();
		for(i=0;i<N;i++)
		{
			tob=m_outputs.GetAt(i);
			if(((CGOutput *)tob)->m_name==in1) break;
		}
		if(i==N)
		{
			AfxMessageBox("Wrong parent output at parent to processor",MB_ICONSTOP|MB_OK);
			return -1;
		}
		N=m_WOut.GetSize();
		for(i=0;i<N;i++)
		{
			pwire=(CGWire *)m_WOut.GetAt(i);
			if(pwire->m_parent==tob && pwire->m_type==type)
			{
				if(m_sims==true) m_wout[i]=false;
				break;
			}
		}
		if(i==N) //we haven't found a previous wire
		{
			pwire=NULL;
			pwire=new CGWire(tob,type,this);
			try
			{
				m_WOut.Add(pwire);
				if(m_sims==true)
				{
					N=m_WOut.GetSize();
					bool *tmp=(bool *)calloc(N,sizeof(bool));
					for(i=0;i<N-1;i++)
						tmp[i]=m_wout[i];
					tmp[N-1]=false;
					free(m_wout);
					m_wout=tmp;
				}
			}
			catch (CMemoryException *err)
			{
				AfxMessageBox("Out of Memory Processor",MB_ICONSTOP|MB_OK);
				if(pwire!=NULL)
				{
					delete pwire;
					pwire=NULL;
				}
				err->Delete();
				return -1;
			}
		}
		//find the processor output
		N=pproc->GetOutputNrPorts();
		for(i=0;i<N;i++)
		{
			tob=(pproc->m_outputs).GetAt(i);
			if(((CGOutput *)tob)->m_name==in2) break;
		}
		if(i==N)
		{
			AfxMessageBox("Wrong processor output at parent to processor",MB_ICONSTOP|MB_OK);
			return -1;
		}
		pwire->Add(tob);
	}
	return N;
}

int CGNetworkS::AddParentNet(long in1, long in2, long n, int type)
{
//
//	if type=0 add a wire between input in1 from network to input in2 from network n
//	if type=1 add a wire between output in1 from network to output in2 from network n
//
	long N,i;
	//we seek for the real network
	CGNetworkS *pnet;
	CGWire *pwire;
	N=m_networks.GetSize();
	for(i=0;i<N;i++)
	{
		pnet=(CGNetworkS *)(m_networks.GetAt(i));
		if(pnet->m_name==n) break;
	}
	if(i==N)
	{
		AfxMessageBox("Wrong network name at network to network",MB_ICONSTOP|MB_OK);
		return -1;
	}
	CObject *tob;
	if(type==0) //we have type input
	{
		//find the index in input array
		N=m_inputs.GetSize();
		for(i=0;i<N;i++)
		{
			tob=m_inputs.GetAt(i);
			if(((CGInput *)tob)->m_name==in1) break;
		}
		if(i==N)
		{
			AfxMessageBox("Wrong parent input at parent to network",MB_ICONSTOP|MB_OK);
			return -1;
		}
		N=m_WIn.GetSize();
		for(i=0;i<N;i++)
		{
			pwire=(CGWire *)m_WIn.GetAt(i);
			if(pwire->m_parent==tob && pwire->m_type==type) break;
		}
		if(i==N) //we haven't found a previous wire
		{
			pwire=NULL;
			pwire=new CGWire(tob,type,this);
			try
			{
				m_WIn.Add(pwire);
			}
			catch (CMemoryException *err)
			{
				AfxMessageBox("Out of wire Memory at parent to network",MB_ICONSTOP|MB_OK);
				if(pwire!=NULL)
				{
					delete pwire;
					pwire=NULL;
				}
				err->Delete();
				return -1;
			}
		}
		//find the network input
		N=pnet->m_nin;
		for(i=0;i<N;i++)
		{
			tob=(pnet->m_inputs).GetAt(i);
			if(((CGInput *)tob)->m_name==in2) break;
		}
		if(i==N)
		{
			AfxMessageBox("Wrong network input at parent to network",MB_ICONSTOP|MB_OK);
			return -1;
		}

		pwire->Add(tob);
	}
	if(type==1) //we have type output
	{
		//find the index in output array
		N=m_outputs.GetSize();
		for(i=0;i<N;i++)
		{
			tob=m_outputs.GetAt(i);
			if(((CGOutput *)tob)->m_name==in1) break;
		}
		if(i==N)
		{
			AfxMessageBox("Wrong parent output at parent to network",MB_ICONSTOP|MB_OK);
			return -1;
		}
		N=m_WOut.GetSize();
		for(i=0;i<N;i++)
		{
			pwire=(CGWire *)m_WOut.GetAt(i);
			if(pwire->m_parent==tob && pwire->m_type==type)
			{
				//m_wout[i]=false;
				AfxMessageBox("We not support yet the connection of two output wires");
				//break;
				return -2;
			}
		}
		if(i==N) //we haven't found a previous wire
		{
			pwire=NULL;
			pwire=new CGWire(tob,type,this);
			try
			{
				m_WOut.Add(pwire);
				if(m_sims==true)
				{
					N=m_WOut.GetSize();
					bool *tmp=(bool *)calloc(N,sizeof(bool));
					for(i=0;i<N-1;i++)
						tmp[i]=m_wout[i];
					tmp[N-1]=false;
					free(m_wout);
					m_wout=tmp;
				}
			}
			catch (CMemoryException *err)
			{
				AfxMessageBox("Out of wire memory at parent to network",MB_ICONSTOP|MB_OK);
				if(pwire!=NULL)
				{
					delete pwire;
					pwire=NULL;
				}
				err->Delete();
				return -1;
			}
		}
		//find the network output
		N=pnet->m_nout;
		for(i=0;i<N;i++)
		{
			tob=(pnet->m_outputs).GetAt(i);
			if(((CGOutput *)tob)->m_name==in2) break;
		}
		if(i==N)
		{
			AfxMessageBox("Wrong network output at parent to network",MB_ICONSTOP|MB_OK);
			return -1;
		}
		pwire->Add(tob);
	}
	return N;
}

int CGNetworkS::AddProcProc(long p1, long in1, long p2, long in2)
{
//
//	Add a wire between output in1 from processor p1 to input in2 from processor p2
//
	long N,i;
	CObject *tob;
	CGWire *pwire;
	//search the first processor
	CGProcessor *pproc1;
	N=m_processors.GetSize();
	for(i=0;i<N;i++)
	{
		pproc1=(CGProcessor *)(m_processors.GetAt(i));
		if(pproc1->GetName()==p1) break;
	}
	if(i==N)
	{
		N=m_processorsp.GetSize();
		for(i=0;i<N;i++)
		{
			pproc1=(CGProcessor *)(m_processorsp.GetAt(i));
			if(pproc1->GetName()==p1) break;
		}
	}
	if(i==N)
	{
		AfxMessageBox("Wrong processor name at processor to processor",MB_ICONSTOP|MB_OK);
		return -1;
	}
	//search the second processor
	CGProcessor *pproc2;
	N=m_processors.GetSize();
	for(i=0;i<N;i++)
	{
		pproc2=(CGProcessor *)(m_processors.GetAt(i));
		if(pproc2->GetName()==p2) break;
	}
	if(i==N)
	{
		N=m_processorsp.GetSize();
		for(i=0;i<N;i++)
		{
			pproc2=(CGProcessor *)(m_processorsp.GetAt(i));
			if(pproc2->GetName()==p2) break;
		}
	}
	if(i==N)
	{
		AfxMessageBox("Wrong processor name at processor to processor",MB_ICONSTOP|MB_OK);
		return -1;
	}
	//find the processor output
	N=pproc1->GetOutputNrPorts();
	for(i=0;i<N;i++)
	{
		tob=(pproc1->m_outputs).GetAt(i);
		if(((CGOutput *)tob)->m_name==in1) break;
	}
	if(i==N)
	{
		AfxMessageBox("Wrong processor output at processor to processor",MB_ICONSTOP|MB_OK);
		return -1;
	}
	N=m_WInt.GetSize();
	for(i=0;i<N;i++)
	{
		pwire=(CGWire *)m_WInt.GetAt(i);
		if(pwire->m_parent==tob && pwire->m_type==3) break;
	}
	if(i==N) //we haven't found a previous wire
	{
		pwire=NULL;
		pwire=new CGWire(tob,3,this);
		try
		{
			m_WInt.Add(pwire);
		}
		catch (CMemoryException *err)
		{
			AfxMessageBox("Out of wire memory at processor to processor",MB_ICONSTOP|MB_OK);
			if(pwire!=NULL)
			{
				delete pwire;
				pwire=NULL;
			}
			err->Delete();
			return -1;
		}
	}
	//find the processor input
	N=pproc2->GetInputNrPorts();
	for(i=0;i<N;i++)
	{
		tob=(pproc2->m_inputs).GetAt(i);
		if(((CGInput *)tob)->m_name==in2) break;
	}
	if(i==N)
	{
		AfxMessageBox("Wrong processor input at processor to processor",MB_ICONSTOP|MB_OK);
		return -1;
	}
	pwire->Add(tob);
	return 0;
}

int CGNetworkS::AddNetworkNetwork(long n1, long in1, long n2, long in2)
{
//
//	Add a wire between output in1 from internal network n1 to input in2 from internal network n2.
//
	long N,i;
	//search the first network
	CGNetworkS *pnet1,*pnet2;
	CObject *tob;
	CGWire *pwire;
	N=m_networks.GetSize();
	for(i=0;i<N;i++)
	{
		pnet1=(CGNetworkS *)(m_networks.GetAt(i));
		if(pnet1->m_name==n1) break;
	}
	if(i==N)
	{
		AfxMessageBox("Wrong network name at internal network to internal network",MB_ICONSTOP|MB_OK);
		return -1;
	}
	//search the second network
	N=m_networks.GetSize();
	for(i=0;i<N;i++)
	{
		pnet2=(CGNetworkS *)(m_networks.GetAt(i));
		if(pnet2->m_name==n2) break;
	}
	if(i==N)
	{
		AfxMessageBox("Wrong network name at internal network to internal network",MB_ICONSTOP|MB_OK);
		return -1;
	}
	//find the network output
	N=(pnet1->m_outputs).GetSize();
	for(i=0;i<N;i++)
	{
		tob=(pnet1->m_outputs).GetAt(i);
		if(((CGInput *)tob)->m_name==in1) break;
	}
	if(i==N)
	{
		AfxMessageBox("Wrong output at network to network",MB_ICONSTOP|MB_OK);
		return -1;
	}
	N=m_WInt.GetSize();
	for(i=0;i<N;i++)
	{
		pwire=(CGWire *)m_WInt.GetAt(i);
		if(pwire->m_parent==tob && pwire->m_type==3) break;
	}
	if(i==N) //we haven't found a previous wire
	{
		pwire=NULL;
		pwire=new CGWire(tob,3,this);
		try
		{
			m_WInt.Add(pwire);
		}
		catch (CMemoryException *err)
		{
			AfxMessageBox("Out of wire memory at network to network",MB_ICONSTOP|MB_OK);
			if(pwire!=NULL)
			{
				delete pwire;
				pwire=NULL;
			}
			err->Delete();
			return -1;
		}
	}
	//find the network input
	N=(pnet2->m_inputs).GetSize();
	for(i=0;i<N;i++)
	{
		tob=(pnet2->m_inputs).GetAt(i);
		if(((CGOutput *)tob)->m_name==in2) break;
	}
	if(i==N)
	{
		AfxMessageBox("Wrong input at network to network",MB_ICONSTOP|MB_OK);
		return -1;
	}
	pwire->Add(tob);
	return 0;
}

int CGNetworkS::AddNetworkProc(long n, long in1, long p, long in2)
{
//
//	Add a wire between output in1 from internal network n to input in2 from processor p.
//
	long N,i;
	CGProcessor *pproc;
	CGNetworkS *pnet;
	CObject *tob;
	CGWire *pwire;
	//search the processor
	N=m_processors.GetSize();
	for(i=0;i<N;i++)
	{
		pproc=(CGProcessor *)(m_processors.GetAt(i));
		if(pproc->GetName()==p) break;
	}
	if(i==N)
	{
		//search the passive processor
		N=m_processorsp.GetSize();
		for(i=0;i<N;i++)
		{
			pproc=(CGProcessor *)(m_processorsp.GetAt(i));
			if(pproc->GetName()==p) break;
		}
	}
	if(i==N)
	{
		AfxMessageBox("Wrong processor name at internal network to processor",MB_ICONSTOP|MB_OK);
		return -1;
	}
	//search the network
	N=m_networks.GetSize();
	for(i=0;i<N;i++)
	{
		pnet=(CGNetworkS *)(m_networks.GetAt(i));
		if(pnet->m_name==n) break;
	}
	if(i==N)
	{
		AfxMessageBox("Wrong network name at internal network to processor",MB_ICONSTOP|MB_OK);
		return -1;
	}
	//find the network output
	N=pnet->m_nout;
	for(i=0;i<N;i++)
	{
		tob=(pnet->m_outputs).GetAt(i);
		if(((CGOutput *)tob)->m_name==in1) break;
	}
	if(i==N)
	{
		AfxMessageBox("Wrong processor output at network to processor",MB_ICONSTOP|MB_OK);
		return -1;
	}
	N=m_WInt.GetSize();
	for(i=0;i<N;i++)
	{
		pwire=(CGWire *)m_WInt.GetAt(i);
		if(pwire->m_parent==tob && pwire->m_type==3) break;
	}
	if(i==N) //we haven't found a previous wire
	{
		pwire=NULL;
		pwire=new CGWire(tob,3,this);
		try
		{
			m_WInt.Add(pwire);
		}
		catch (CMemoryException *err)
		{
			AfxMessageBox("Out of wire memory at network to processor",MB_ICONSTOP|MB_OK);
			if(pwire!=NULL)
			{
				delete pwire;
				pwire=NULL;
			}
			err->Delete();
			return -1;
		}
	}
	//find the processor input
	N=pproc->GetInputNrPorts();
	for(i=0;i<N;i++)
	{
		tob=(pproc->m_inputs).GetAt(i);
		if(((CGInput *)tob)->m_name==in2) break;
	}
	if(i==N)
	{
		AfxMessageBox("Wrong processor input at network to processor",MB_ICONSTOP|MB_OK);
		return -1;
	}

	pwire->Add(tob);
	return 0;
}

int CGNetworkS::AddProcNetwork(long p, long in1, long n, long in2)
{
//
//	Add a wire between output in1 from internal processor p to input in2 from network n.
//
	long N,i;
	CGProcessor *pproc;
	CGNetworkS *pnet;
	CObject *tob;
	CGWire *pwire;
	//search the processor
	N=m_processors.GetSize();
	for(i=0;i<N;i++)
	{
		pproc=(CGProcessor *)(m_processors.GetAt(i));
		if(pproc->GetName()==p) break;
	}
	if(i==N)
	{
		N=m_processorsp.GetSize();
		for(i=0;i<N;i++)
		{
			pproc=(CGProcessor *)(m_processorsp.GetAt(i));
			if(pproc->GetName()==p) break;
		}
	}
	if(i==N)
	{
		AfxMessageBox("Wrong processor name at internal processor to network",MB_ICONSTOP|MB_OK);
		return -1;
	}
	//search the network
	N=m_networks.GetSize();
	for(i=0;i<N;i++)
	{
		pnet=(CGNetworkS *)(m_networks.GetAt(i));
		if(pnet->m_name==n) break;
	}
	if(i==N)
	{
		AfxMessageBox("Wrong network name at internal processor to network",MB_ICONSTOP|MB_OK);
		return -1;
	}
	//find the processor output
	N=pproc->GetOutputNrPorts();
	for(i=0;i<N;i++)
	{
		tob=(pproc->m_outputs).GetAt(i);
		if(((CGOutput *)tob)->m_name==in1) break;
	}
	if(i==N)
	{
		AfxMessageBox("Wrong processor output at processor to network",MB_ICONSTOP|MB_OK);
		return -1;
	}
	N=m_WInt.GetSize();
	for(i=0;i<N;i++)
	{
		pwire=(CGWire *)m_WInt.GetAt(i);
		if(pwire->m_parent==tob && pwire->m_type==3) break;
	}
	if(i==N) //we haven't found a previous wire
	{
		pwire=NULL;
		pwire=new CGWire(tob,3,this);
		try
		{
			m_WInt.Add(pwire);
		}
		catch (CMemoryException *err)
		{
			AfxMessageBox("Out of wire memory at processor to network",MB_ICONSTOP|MB_OK);
			if(pwire!=NULL)
			{
				delete pwire;
				pwire=NULL;
			}
			err->Delete();
			return -1;
		}
	}
	//find the network input
	N=pnet->m_nin;
	for(i=0;i<N;i++)
	{
		tob=(pnet->m_inputs).GetAt(i);
		if(((CGInput *)tob)->m_name==in2) break;
	}
	if(i==N)
	{
		AfxMessageBox("Wrong processor output at processor to network",MB_ICONSTOP|MB_OK);
		return -1;
	}
	pwire->Add(tob);
	return 0;
}

void CGNetworkS::WaitCoord()
{
	//this function is called by any who want to dynamical modification of this network
	if(m_disable_coord==false)
		WaitForSingleObject(m_coordinator->event_net,INFINITE);
}
//these functions could be derivate if you want a specific simulation
int CGNetworkS::receivemsg(int type, double time, CObject *in)
{
/*
	type is the receiving message: 0=start;1=int;2=ext;3=out;4=done;
	time is the time of the simulation
	in is the pointer to the input port
	it's return is 4=done or -1=error
*/
	long N;
	long i;
	m_type=type;
	if(type!=3) m_time=time;
	if(m_sims==true && m_adds==true)
	{
		if(m_disable_coord==true)
		{
			for(i=0;i<m_aprocs.GetSize();i++)
				((CGProcessor *)m_aprocs[i])->DisableCoord();
			for(i=0;i<m_anets.GetSize();i++)
				((CGNetworkS *)m_anets[i])->DisableCoord();
			for(i=0;i<m_aports.GetSize();i++)
				((CGData *)m_aports[i])->DisableCoord();
		}
		N=m_aprocs.GetSize();
		for(i=0;i<N;i++)
			((CGProcessor *)m_aprocs[i])->receivemsg(0,time,NULL);
		N=m_anets.GetSize();
		for(i=0;i<N;i++)
			((CGNetworkS *)m_anets[i])->receivemsg(0,time,NULL);
		N=m_aports.GetSize();
		for(i=0;i<N;i++)
		{
			((CGData *)m_aports.GetAt(i))->SetTime(time);
			((CGData *)m_aports.GetAt(i))->SetWTime(time);
			((CGData *)m_aports.GetAt(i))->Reset();
		}
		m_anets.RemoveAll();
		m_aprocs.RemoveAll();
		m_aports.RemoveAll();
		m_anets.FreeExtra();
		m_aprocs.FreeExtra();
		m_aports.FreeExtra();
		m_adds=false;
	}
	switch(m_type)
	{
	case 0:
	{
		if(m_coordinator==NULL && m_disable_coord==false && m_manual_start==false)
		{
			m_coordinator=new CGCoordinator(this);
			m_coordinator->InitInstance();
			m_coordinator->CreateThread(0,0,NULL);
			m_coordinator->SetThreadPriority(THREAD_PRIORITY_ABOVE_NORMAL);
		}
		else if(m_coordinator==NULL && m_disable_coord==false && m_manual_start==true)
		{
			m_coordinator=new CGCoordinator(this);
			m_coordinator->InitInstance();
		}
		receive0(time);
		break;
	}
	case 1:
	{
		receive1(time);
		break;
	}
	case 2:
	{
		receive2(time,in);
		break;
	}
	case 3:
	{
		receive3(time,in);
		break;
	}
	default:
		return -2;
	}
	return 4;
}
int CGNetworkS::receive0(double time)
{
	long i;
	long N;
	m_sims=true;
	if(m_procs!=NULL) free(m_procs);
	if(m_nets!=NULL) free(m_nets);
	if(m_wout!=NULL) free(m_wout);
	if(m_procsp!=NULL) free(m_procsp);
	N=m_processors.GetSize();
	m_procs=(bool *)calloc(N,sizeof(bool));
	for(i=0;i<N;i++) m_procs[i]=false;
	N=m_processorsp.GetSize();
	m_procsp=(bool *)calloc(N,sizeof(bool));
	for(i=0;i<N;i++) m_procsp[i]=false;
	N=m_networks.GetSize();
	m_nets=(bool *)calloc(N,sizeof(bool));
	for(i=0;i<N;i++) m_nets[i]=false;
	N=m_WOut.GetSize();
	m_wout=(bool *)calloc(N,sizeof(bool));
	for(i=0;i<N;i++) m_wout[i]=false;
	//reset time and value
	N=m_inputs.GetSize();
	for(i=0;i<N;i++) 
	{
		((CGData *)m_inputs.GetAt(i))->SetTime(time);
		((CGData *)m_inputs.GetAt(i))->SetWTime(time);
		((CGData *)m_inputs.GetAt(i))->Reset();
	}
	N=m_outputs.GetSize();
	for(i=0;i<N;i++) 
	{
		((CGData *)m_outputs.GetAt(i))->SetTime(time);
		((CGData *)m_outputs.GetAt(i))->SetWTime(time);
		((CGData *)m_outputs.GetAt(i))->Reset();
	}
	N=m_processors.GetSize();
	for(i=0;i<N;i++)
		((CGProcessor *)m_processors[i])->receivemsg(0,time,NULL);
	N=m_processorsp.GetSize();
	for(i=0;i<N;i++)
		((CGProcessor *)m_processorsp[i])->receivemsg(0,time,NULL);
	N=m_networks.GetSize();
	for(i=0;i<N;i++)
		((CGNetworkS *)m_networks[i])->receivemsg(0,time,NULL);
	m_time_ext=0.0;
	for(i=0;i<m_nin;i++)
		((CGData *)m_inputs[i])->Reset();
	for(i=0;i<m_nout;i++)
		((CGData *)m_outputs[i])->Reset();
	return 0;
}

int CGNetworkS::receive1(double time)
{
	long i;
	if(fabs(m_time_ext-m_time)>precision)
	{
			for(i=0;i<m_processors.GetSize();i++) m_procs[i]=false;
			for(i=0;i<m_processorsp.GetSize();i++) m_procsp[i]=false;
			for(i=0;i<m_networks.GetSize();i++) m_nets[i]=false;
			for(i=0;i<m_WOut.GetSize();i++) m_wout[i]=false;
	}
	if(m_disable_coord==true)
	{
		if(fabs(m_time_ext-m_time)>precision)
		{
			for(i=0;i<m_WIn.GetSize();i++) ((CGWire *)m_WIn[i])->receivemsg(1,time,NULL);
		}
		if(m_parent!=NULL) ((CGNetworkS *)m_parent)->SetNet((CObject *)this);
		//active processors receive
		for(i=0;i<m_processors.GetSize();i++)
		{
			if(m_procs[i]==false)
				((CGProcessor *)m_processors[i])->receivemsg(1,time,NULL);
		}
		//networks receive
		for(i=0;i<m_networks.GetSize();i++)
		{
			if(m_nets[i]==false)
				((CGNetworkS *)m_networks[i])->receivemsg(1,time,NULL);
		}
		//pasive processors receive
		for(i=0;i<m_processorsp.GetSize();i++)
		{
			if(m_procsp[i]==false)
				((CGProcessor *)m_processorsp[i])->receivemsg(1,time,NULL);
		}
	
		for(i=0;i<m_processors.GetSize();i++) m_procs[i]=false;
		for(i=0;i<m_processorsp.GetSize();i++) m_procsp[i]=false;
		for(i=0;i<m_networks.GetSize();i++) m_nets[i]=false;
		for(i=0;i<m_WOut.GetSize();i++) m_wout[i]=false;
	}
	else
	{

		WaitForSingleObject(m_coordinator->event_net,INFINITE);
		ResetEvent(m_coordinator->event_net);

		for(i=0;i<m_networks.GetSize();i++)
		{
			CGCElem *elem=new CGCElem(m_networks[i],1,time,NULL);
			m_coordinator->lock->Lock(INFINITE);
			m_coordinator->m_queue.Add(elem);
			m_coordinator->lock->Unlock();
		}
		for(i=0;i<m_processors.GetSize();i++)
		{
			CGCElem *elem=new CGCElem(m_processors[i],1,time,NULL);
			m_coordinator->lock->Lock(INFINITE);
			m_coordinator->m_queue.Add(elem);
			m_coordinator->lock->Unlock();
		}
		for(i=0;i<m_processorsp.GetSize();i++)
		{
			CGCElem *elem=new CGCElem(m_processorsp[i],1,time,NULL);
			m_coordinator->lock->Lock(INFINITE);
			m_coordinator->m_queue.Add(elem);
			m_coordinator->lock->Unlock();
		}
		if(m_parent!=NULL) ((CGNetworkS *)m_parent)->SetNet((CObject *)this); //set this has work
		PulseEvent(m_coordinator->event_add); //we have put all instances from this net
	}
	return 0;
}

int CGNetworkS::receive2(double time,CObject *in)
{
	long i,N;
	CGWire *pwire;
	N=m_WIn.GetSize();
	for(i=0;i<N;i++)
	{
		pwire=(CGWire *)m_WIn.GetAt(i);
		if(pwire->IsHere((CGData *)in)==true)
		{
			pwire->receivemsg(2,time,(CGData *)in);
			break;
		}
	}
	if(i==N)
	{
		N=m_WInt.GetSize();
		for(i=0;i<N;i++)
		{
			pwire=(CGWire *)m_WInt.GetAt(i);
			if(pwire->IsHere((CGData *)in)==true)
			{
				pwire->receivemsg(2,time,(CGData *)in);
				break;
			}
		}
	}
	if(i==N)
	{
		N=m_WOut.GetSize();
		for(i=0;i<N;i++)
		{
			pwire=(CGWire *)m_WOut.GetAt(i);
			if(pwire->IsHere((CGData *)in)==true)
			{
				if(m_wout[i]==false)
				{
					pwire->receivemsg(2,time,(CGData *)in);
					break;
				}
			}
		}
	}
	m_time_ext=time;
	return 0;
}

int CGNetworkS::receive3(double time,CObject *in)
{
	long i,N;
	if(m_disable_coord==true)
	{
		if(in==NULL)
		{
			N=m_processors.GetSize();
			for(i=0;i<N;i++)
				((CGProcessor *)m_processors[i])->receivemsg(3,time,NULL);
			N=m_processorsp.GetSize();
			for(i=0;i<N;i++)
				((CGProcessor *)m_processorsp[i])->receivemsg(3,time,NULL);
			N=m_networks.GetSize();
			for(i=0;i<N;i++)
				((CGNetworkS *)m_networks[i])->receivemsg(3,time,NULL);
		}
		else
		{
			CGWire *pwire;
			N=m_WIn.GetSize();
			for(i=0;i<N;i++)
			{
				pwire=(CGWire *)m_WIn.GetAt(i);
				if(pwire->IsHere((CGData *)in)==true)
				{
					pwire->receivemsg(3,time,(CGData *)in);
					break;
				}
			}
			if(i==N)
			{
				N=m_WInt.GetSize();
				for(i=0;i<N;i++)
				{
					pwire=(CGWire *)m_WInt.GetAt(i);
					if(pwire->IsHere((CGData *)in)==true)
					{
						pwire->receivemsg(3,time,(CGData *)in);
						break;
					}
				}
			}
			if(i==N)
			{
				N=m_WOut.GetSize();
				for(i=0;i<N;i++)
				{
					pwire=(CGWire *)m_WOut.GetAt(i);
					if(pwire->IsHere((CGData *)in)==true)
					{
						pwire->receivemsg(3,time,(CGData *)in);
						break;
					}
				}
			}
		}
	}
	return 0;
}

void CGNetworkS::SetTypeQueue(bool type)
{
//
//set the type of the queue (if it is centralized or descentralized)
//
	m_qtype=type;
}

bool CGNetworkS::GetTypeQueue()
{
	return m_qtype;
}

void CGNetworkS::SetTypeWire(bool type)
{
//
//set the type of the wire unique or notunique
//
	m_wtype=type;
}

bool CGNetworkS::GetTypeWire()
{
//
//return the type of the wire
//
	return m_wtype;
}

void CGNetworkS::SetInType(bool type)
{
	m_intype=type;
}

bool CGNetworkS::GetInType()
{
	return m_intype;
}

double CGNetworkS::sigma(CGData *in)
{
//
//return the closest done time
//
	long N,i;
	N=m_WIn.GetSize();
	CGWire *wire;
	for(i=0;i<N;i++)
	{
		wire=(CGWire *)m_WIn.GetAt(i);
		if(wire->m_parent==in) return wire->sigma();
	}
	return -1.0;
}

double CGNetworkS::sigma(CGData *in, long *queue)
{
//
//return the closest done time with the smoll queue
//
	long N,i;
	N=m_WIn.GetSize();
	CGWire *wire;
	for(i=0;i<N;i++)
	{
		wire=(CGWire *)m_WIn.GetAt(i);
		if(wire->m_parent==in) return wire->sigma(queue);
	}
	return -1.0;
}
void CGNetworkS::PrintData()
{
	if(m_disable_coord==false)
	{
		WaitForSingleObject(m_coordinator->event_end,INFINITE);
		ResetEvent(m_coordinator->event_end);
	}
	long i;
	for(i=0;i<m_outputs.GetSize();i++)
		cout<<"out["<<((CGOutput*)m_outputs.GetAt(i))->m_name<<"]="<<((CGOutput*)m_outputs.GetAt(i))->Get()<<endl;
}

void CGNetworkS::SetClockPrecision(double val)
{
	long N,i;
	N=m_networks.GetSize();
	for(i=0;i<N;i++)
		((CGNetworkS *)m_networks.GetAt(i))->SetClockPrecision(val);
	N=m_processors.GetSize();
	for(i=0;i<N;i++)
		((CGProcessor *)m_processors.GetAt(i))->SetClockPrecision(val);
	m_CLKP=val;
}


void CGNetworkS::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	m_inputs.Serialize(ar);
	m_outputs.Serialize(ar);
	m_processors.Serialize(ar);
	m_processorsp.Serialize(ar);
	m_networks.Serialize(ar);
	m_anets.Serialize(ar);
	m_aprocs.Serialize(ar);
	int type;
	long n1,n2,p1,p2;
	long i,j;
	int tmp;
	long nr,nr1;
	CGWire *pwire;
	if(ar.IsStoring())
	{
		ar<<m_btype;
		ar<<m_intype;
		ar<<m_name;
		ar<<m_nin;
		ar<<m_nout;
		ar<<m_nprocs;
		ar<<m_nprocsp;
		ar<<m_nnets;
		ar<<m_qtype;
		ar<<m_wtype;
		ar<<m_sims;
		ar<<m_adds;
		ar<<m_manual_start;
		nr=m_WIn.GetSize();
		ar<<nr;
		for(i=0;i<nr;i++)
		{
			pwire=(CGWire *)(m_WIn.GetAt(i));
			nr1=pwire->GetNr();
			ar<<nr1;
			for(j=0;j<nr1;j++)
			{
				type=pwire->Get(n1,p1,n2,p2);
				ar<<type;
				ar<<n1;
				ar<<p1;
				ar<<n2;
				ar<<p2;
			}
		}
		nr=m_WOut.GetSize();
		ar<<nr;
		for(i=0;i<nr;i++)
		{
			pwire=(CGWire *)(m_WOut.GetAt(i));
			nr1=pwire->GetNr();
			ar<<nr1;
			for(j=0;j<nr1;j++)
			{
				type=pwire->Get(n1,p1,n2,p2);
				ar<<type;
				ar<<n1;
				ar<<p1;
				ar<<n2;
				ar<<p2;
			}
		}
		nr=m_WInt.GetSize();
		ar<<nr;
		for(i=0;i<nr;i++)
		{
			pwire=(CGWire *)(m_WInt.GetAt(i));
			nr1=pwire->GetNr();
			ar<<nr1;
			for(j=0;j<nr1;j++)
			{
				type=pwire->Get(n1,p1,n2,p2);
				ar<<type;
				ar<<n1;
				ar<<p1;
				ar<<n2;
				ar<<p2;
			}
		}
	}
	else
	{
		ar>>tmp;
		m_btype=(bool)m_btype;
		ar>>tmp;
		m_intype=(bool)m_intype;
		ar>>m_name;
		ar>>m_nin;
		ar>>m_nout;
		ar>>m_nprocs;
		ar>>m_nprocsp;
		ar>>m_nnets;
		ar>>tmp;
		m_qtype=(bool)tmp;
		ar>>tmp;
		m_wtype=(bool)tmp;
		ar>>tmp;
		m_sims=(bool)tmp;
		ar>>tmp;
		m_adds=(bool)tmp;
		ar>>tmp;
		m_manual_start=(bool)tmp;
		for(i=0;i<m_nin;i++)
			((CGData *)m_inputs.GetAt(i))->SetParent(this,2);
		for(i=0;i<m_nout;i++)
			((CGData *)m_outputs.GetAt(i))->SetParent(this,2);
		for(i=0;i<m_nprocs;i++)
			((CGProcessor *)m_processors.GetAt(i))->SetParent(this);
		for(i=0;i<m_nprocsp;i++)
			((CGProcessor *)m_processorsp.GetAt(i))->SetParent(this);
		for(i=0;i<m_nnets;i++)
			((CGNetworkS *)m_networks.GetAt(i))->SetParent(this);
		ar>>nr;
		for(i=0;i<nr;i++)
		{
			ar>>nr1;
			for(j=0;j<nr1;j++)
			{
				ar>>type;
				ar>>n1;
				ar>>p1;
				ar>>n2;
				ar>>p2;
				switch(type)
				{
					case 0:
						AddParentProc(p1,p2,n2,n1);
						break;
					case 1:
						AddParentNet(p1,p2,n2,n1);
						break;
					case 2:
						AddProcProc(n1,p1,n2,p2);
						break;
					case 3:
						AddNetworkNetwork(n1,p1,n2,p2);
						break;
					case 4:
						AddNetworkProc(n1,p1,n2,p2);
						break;
					case 5:
						AddProcNetwork(n1,p1,n2,p2);
						break;
				}
			}
		}
		ar>>nr;
		for(i=0;i<nr;i++)
		{
			ar>>nr1;
			for(j=0;j<nr1;j++)
			{
				ar>>type;
				ar>>n1;
				ar>>p1;
				ar>>n2;
				ar>>p2;
				switch(type)
				{
					case 0:
						AddParentProc(p1,p2,n2,n1);
						break;
					case 1:
						AddParentNet(p1,p2,n2,n1);
						break;
					case 2:
						AddProcProc(n1,p1,n2,p2);
						break;
					case 3:
						AddNetworkNetwork(n1,p1,n2,p2);
						break;
					case 4:
						AddNetworkProc(n1,p1,n2,p2);
						break;
					case 5:
						AddProcNetwork(n1,p1,n2,p2);
						break;
				}
			}
		}
		ar>>nr;
		for(i=0;i<nr;i++)
		{
			ar>>nr1;
			for(j=0;j<nr1;j++)
			{
				ar>>type;
				ar>>n1;
				ar>>p1;
				ar>>n2;
				ar>>p2;
				switch(type)
				{
					case 0:
						AddParentProc(p1,p2,n2,n1);
						break;
					case 1:
						AddParentNet(p1,p2,n2,n1);
						break;
					case 2:
						AddProcProc(n1,p1,n2,p2);
						break;
					case 3:
						AddNetworkNetwork(n1,p1,n2,p2);
						break;
					case 4:
						AddNetworkProc(n1,p1,n2,p2);
						break;
					case 5:
						AddProcNetwork(n1,p1,n2,p2);
						break;
				}
			}
		}
	}
}

CGNetworkS * CGNetworkS::copy(CObject *parent,long name)
{
	//create a brother of this network
	CFile f;
	char buf[512];
	CArchive *ar;
	CString fname("testn.dat");
	char temp[100];
	srand(name);
	sprintf(temp,"%ld",rand());
	fname.Insert(5,temp);
	f.Open( fname, CFile::modeCreate | CFile::modeWrite );
	ar=new CArchive(&f, CArchive::store, 512, buf );
	*ar<<this;
	ar->Close();
	f.Close();
	delete ar;
	CObject *tmp;
	f.Open( fname,CFile::modeRead );
	CArchive ar1(&f, CArchive::load, 512, buf );
	ar1>>tmp;
	ar1.Close();
	f.Close();
	((CGNetworkS *)tmp)->SetParent(parent);
	((CGNetworkS *)tmp)->SetName(name);
	if(m_time!=-1.0) ((CGNetworkS *)tmp)->receivemsg(0,m_time,NULL);
	TRY
	{
		CFile::Remove(fname);
	}
	CATCH( CFileException, e )
	{
		#ifdef _DEBUG
			afxDump << "File " << fname << " cannot be removed\n";
		#endif
	}
	END_CATCH
	return (CGNetworkS *)tmp;
}

CGNetworkS * CGNetworkS::copy(CObject *parent)
{
	//create a clone of this network
	CFile f;
	char buf[512];
	CArchive *ar;
	CString fname("testn.dat");
	char temp[100];
	srand(m_name);
	sprintf(temp,"%ld",rand());
	fname.Insert(5,temp);
	f.Open( fname, CFile::modeCreate | CFile::modeWrite );
	ar=new CArchive(&f, CArchive::store, 512, buf );
	*ar<<this;
	ar->Close();
	f.Close();
	delete ar;
	CObject *tmp;
	f.Open( fname,CFile::modeRead );
	CArchive ar1(&f, CArchive::load, 512, buf );
	ar1>>tmp;
	ar1.Close();
	f.Close();
	((CGNetworkS *)tmp)->SetParent(parent);
	if(m_time!=-1.0) ((CGNetworkS *)tmp)->receivemsg(0,m_time,NULL);
	TRY
	{
		CFile::Remove(fname);
	}
	CATCH( CFileException, e )
	{
		#ifdef _DEBUG
			afxDump << "File " << fname << " cannot be removed\n";
		#endif
	}
	END_CATCH
	return (CGNetworkS *)tmp;
}

int CGNetworkS::DelPort(CGData *dead)
{
	long i;
	CGWire *wire;
	if(dead->m_parent_wire==NULL) //came from wire
	{
		if(dead->IsKind()==1) //is output
		{
			for(i=0;i<m_nout;i++)
				if(((CGData *)m_outputs[i])==dead)
				{
					m_outputs.RemoveAt(i);
					m_outputs.FreeExtra();
					m_nout--;
					if(dead->m_parent_ext_wire==NULL)
					{
						delete dead;
						return 0;
					}
					else goto external_wire;
				}
			return -1;
		}
		else //is input
		{
			for(i=0;i<m_nin;i++)
				if(((CGData *)m_inputs[i])==dead)
				{
					m_inputs.RemoveAt(i);
					m_inputs.FreeExtra();
					m_nin--;
					if(dead->m_parent_ext_wire==NULL)
					{
						delete dead;
						return 0;
					}
					else goto external_wire;
				}
			return -1;
		}
	}
	else //self decided or came from extern of the network in dual case
	{
		wire=(CGWire *)dead->m_parent_wire;
		if(dead->IsKind()==1) //is output
		{
			for(i=0;i<m_nout;i++)
				if(((CGData *)m_outputs[i])==dead)
				{
					if(wire->kill(dead)==0)
						DelWire(wire);
					m_outputs.RemoveAt(i);
					m_outputs.FreeExtra();
					m_nout--;
					if(dead->m_parent_ext_wire==NULL)
					{
						delete dead;
						return 1;
					}
					else goto external_wire;
				}
			return -1;
		}
		else //is input
		{
			for(i=0;i<m_nin;i++)
				if(((CGData *)m_inputs[i])==dead)
				{
					wire->kill(dead);
					DelWire(wire);
					m_inputs.RemoveAt(i);
					m_inputs.FreeExtra();
					m_nin--;
					if(dead->m_parent_ext_wire==NULL)
					{
						delete dead;
						return 1;
					}
					else goto external_wire;
				}
			return -1;
		}
	}
	external_wire:
	wire=(CGWire *)(dead->m_parent_ext_wire);
	if(wire->kill(dead)==0)
		((CGNetworkS *)(wire->m_parent_wire))->DelWire(wire);
	delete dead;
	return 2;
}

int CGNetworkS::DelWire(CGWire *dead)
{
	//find in internal 
	long i;
	for(i=0;i<m_WInt.GetSize();i++)
	{
		if(((CGWire *)m_WInt.GetAt(i))==dead)
		{
			m_WInt.RemoveAt(i);
			m_WInt.FreeExtra();
			delete dead;
			return 0;
		}
	}
	//find in input
	for(i=0;i<m_WIn.GetSize();i++)
	{
		if(((CGWire *)m_WIn.GetAt(i))==dead)
		{
			m_WIn.RemoveAt(i);
			m_WIn.FreeExtra();
			delete dead;
			return 1;
		}
	}
	//find in output
	for(i=0;i<m_WOut.GetSize();i++)
	{
		if(((CGWire *)m_WOut.GetAt(i))==dead)
		{
			bool *temp=(bool *)calloc(m_WOut.GetSize()-1,sizeof(bool));
			long j;
			long k;
			for(j=0,k=0;j<m_WOut.GetSize();j++)
			{
				if(j!=i)
				{
					temp[k]=m_wout[j];
					k++;
				}
			}
			free(m_wout);
			m_wout=temp;
			m_WOut.RemoveAt(i);
			m_WOut.FreeExtra();
			delete dead;
			return 2;
		}
	}
	return -1;
}

int CGNetworkS::DelProc(long name)
{
	CGProcessor *dead=NULL;
	long i,j;
	j=-1;
	for(i=0;i<m_nprocs;i++)
		if(((CGProcessor *)m_processors[i])->GetName()==name)
		{
			dead=(CGProcessor *)m_processors[i];
			break;
		}
	if(i==m_nprocs)
	{
		for(j=0;j<m_nprocsp;j++)
			if(((CGProcessor *)m_processorsp[j])->GetName()==name)
			{
				dead=(CGProcessor *)m_processorsp[j];
				break;
			}
		if(j==m_nprocsp) return -1;
	}
	long l,k;
	if(j!=-1)
	{
		bool *temp=(bool *)calloc(m_processorsp.GetSize()-1,sizeof(bool));
		for(l=0,k=0;l<m_processorsp.GetSize();l++)
		{
			if(j!=l)
			{
				temp[k]=m_procsp[l];
				k++;
			}
		}
		free(m_procsp);
		m_procsp=temp;
		m_processorsp.RemoveAt(j);
		m_processorsp.FreeExtra();
		m_nprocsp--;
	}
	else
	{
		bool *temp=(bool *)calloc(m_processors.GetSize()-1,sizeof(bool));
		for(l=0,k=0;l<m_processors.GetSize();l++)
		{
			if(i!=l)
			{
				temp[k]=m_procsp[l];
				k++;
			}
		}
		free(m_procsp);
		m_procsp=temp;
		m_processors.RemoveAt(i);
		m_processors.FreeExtra();
		m_nprocs--;
	}
	if(dead->GetParent()!=NULL) //decided by net
	{
		dead->SetParent(NULL);
		dead->SetDelParent(this);
		dead->kill();
		delete dead;
	}
	return 0;
}

int CGNetworkS::DelProc(CGProcessor *dead)
{
	long i,j;
	j=-1;
	for(i=0;i<m_nprocs;i++)
		if((CGProcessor *)m_processors[i]==dead) break;
	if(i==m_nprocs)
	{
		for(j=0;j<m_nprocsp;j++)
			if((CGProcessor *)m_processorsp[j]==dead) break;
		if(j==m_nprocsp) return -1;
	}
	long l,k;
	if(j!=-1)
	{
		bool *temp=(bool *)calloc(m_processorsp.GetSize()-1,sizeof(bool));
		for(l=0,k=0;l<m_processorsp.GetSize();l++)
		{
			if(j!=l)
			{
				temp[k]=m_procsp[l];
				k++;
			}
		}
		free(m_procsp);
		m_procsp=temp;
		m_processorsp.RemoveAt(j);
		m_processorsp.FreeExtra();
		m_nprocsp--;
	}
	else
	{
		bool *temp=(bool *)calloc(m_processors.GetSize()-1,sizeof(bool));
		for(l=0,k=0;l<m_processors.GetSize();l++)
		{
			if(i!=l)
			{
				temp[k]=m_procs[l];
				k++;
			}
		}
		free(m_procs);
		m_procs=temp;
		m_processors.RemoveAt(i);
		m_processors.FreeExtra();
		m_nprocs--;
	}
	if(dead->GetParent()!=NULL) //decided by net
	{
		dead->SetParent(NULL);
		dead->SetDelParent(this);
		dead->kill();
		delete dead;
	}
	return 0;
}

int CGNetworkS::DelNet(CGNetworkS *dead)
{
	long i,l,k;
	for(i=0;i<m_nnets;i++)
		if((CGNetworkS *)m_networks[i]==dead) break;
	if(i==m_nnets) return -1;
	bool *temp=(bool *)calloc(m_networks.GetSize()-1,sizeof(bool));
	for(l=0,k=0;l<m_networks.GetSize();l++)
	{
		if(i!=l)
		{
			temp[k]=m_nets[l];
			k++;
		}
	}
	free(m_nets);
	m_nets=temp;
	m_networks.RemoveAt(i);
	m_networks.FreeExtra();
	m_nnets--;
	if(dead->m_parent!=NULL) //decided by net
	{
		dead->m_parent=NULL;
		dead->kill();
		delete dead;
	}
	return 0;
}

int CGNetworkS::DelNet(long name)
{
	CGNetworkS *dead;
	long i,l,k;
	for(i=0;i<m_nnets;i++)
		if(((CGNetworkS *)m_networks[i])->m_name==name)
		{
			dead=(CGNetworkS *)m_networks[i];
			break;
		}
	if(i==m_nprocs) return -1;
	bool *temp=(bool *)calloc(m_networks.GetSize()-1,sizeof(bool));
	for(l=0,k=0;l<m_networks.GetSize();l++)
	{
		if(i!=l)
		{
			temp[k]=m_nets[l];
			k++;
		}
	}
	free(m_nets);
	m_nets=temp;
	m_networks.RemoveAt(i);
	m_networks.FreeExtra();
	m_nnets--;
	if(dead->m_parent!=NULL) //decided by net
	{
		dead->m_parent=NULL;
		dead->kill();
		delete dead;
	}
	return 0;
}

int CGNetworkS::kill()
{
	long i;
	long nr;
	nr=m_inputs.GetSize();
	for(i=0;i<nr;i++)
		DelPort((CGData *)m_inputs[0]);
	nr=m_outputs.GetSize();
	for(i=0;i<nr;i++)
		DelPort((CGData *)m_outputs[0]);
	return 0;
}

void CGNetworkS::SetCoordinator(CGCoordinator *coord)
{
	m_coordinator=coord;
}

CGCoordinator * CGNetworkS::GetCoordinator()
{
	if(m_disable_coord==false)
		return m_coordinator;
	else return NULL;
}

void CGNetworkS::DisableCoord()
{
	//disable the threaded coordinator
	m_disable_coord=true;
	long i;
	for(i=0;i<m_inputs.GetSize();i++)
		((CGData *)m_inputs[i])->DisableCoord();
	for(i=0;i<m_outputs.GetSize();i++)
		((CGData *)m_outputs[i])->DisableCoord();
	for(i=0;i<m_processors.GetSize();i++)
		((CGProcessor *)m_processors[i])->DisableCoord();
	for(i=0;i<m_processorsp.GetSize();i++)
		((CGProcessor *)m_processorsp[i])->DisableCoord();
	for(i=0;i<m_networks.GetSize();i++)
		((CGNetworkS *)m_networks[i])->DisableCoord();
}

bool CGNetworkS::GetWork(CObject *ob)
{
	//return if the instance has worked
	long i;
	if(ob->IsKindOf(RUNTIME_CLASS(CGProcessor))!=0)
	{
		for(i=0;i<m_processors.GetSize();i++)
			if(m_processors[i]==ob)
				return m_procs[i];
		for(i=0;i<m_processorsp.GetSize();i++)
			if(m_processorsp[i]==ob)
				return m_procsp[i];
	}
	else if(ob->IsKindOf(RUNTIME_CLASS(CGNetworkS))!=0)
	{
		for(i=0;i<m_networks.GetSize();i++)
			if(m_networks[i]==ob)
				return m_nets[i];
	}
	else
	{
		for(i=0;i<m_WOut.GetSize();i++)
			if(m_WOut[i]==ob)
				return m_wout[i];
	}
	return false;
}

void CGNetworkS::SetWork(CObject *ob)
{
	//set if the instance has worked
	long i;
	if(ob->IsKindOf(RUNTIME_CLASS(CGProcessor))!=0)
	{
		for(i=0;i<m_processors.GetSize();i++)
			if(m_processors[i]==ob)
			{
				m_procs[i]=true;
				return;
			}
		for(i=0;i<m_processorsp.GetSize();i++)
			if(m_processorsp[i]==ob)
			{
				m_procsp[i]=true;
				return;
			}
	}
	else if(ob->IsKindOf(RUNTIME_CLASS(CGNetworkS))!=0)
	{
		for(i=0;i<m_networks.GetSize();i++)
			if(m_networks[i]==ob)
			{
				m_nets[i]=true;
				return;
			}
	}
	else
	{
		for(i=0;i<m_WOut.GetSize();i++)
			if(m_WOut[i]==ob)
			{
				m_wout[i]=true;
				return;
			}
	}
}

void CGNetworkS::ResetNet()
{
//
//reset the runed procs ,subnetworks and output wire
//
	long i;
	for(i=0;i<m_processors.GetSize();i++) m_procs[i]=false;
	for(i=0;i<m_processorsp.GetSize();i++) m_procsp[i]=false;
	for(i=0;i<m_networks.GetSize();i++)
	{
		m_nets[i]=false;
		((CGNetworkS *)m_networks[i])->ResetNet();
	}
	for(i=0;i<m_WOut.GetSize();i++) m_wout[i]=false;
}

void CGNetworkS::SetNet(CObject *ob)
{
//
//set a runed network
//
	long N=m_networks.GetSize();
	long i;
	for(i=0;i<N;i++)
		if(m_networks.GetAt(i)==ob)
		{
			m_nets[i]=true;
			break;
		}
}

void CGNetworkS::SetProc(CObject *ob)
{
//
//set a runed porcessor
//
	long N=m_processors.GetSize();
	long i;
	for(i=0;i<N;i++)
		if(m_processors.GetAt(i)==ob)
		{
			m_procs[i]=true;
			break;
		}
	if(i==N)
	{
		N=m_processorsp.GetSize();
		for(i=0;i<N;i++)
			if(m_processorsp.GetAt(i)==ob)
			{
				m_procsp[i]=true;
				break;
			}
	}
}

void CGNetworkS::ResetProc(CObject *ob)
{
//
//reset a runed porcessor
//
	long N=m_processors.GetSize();
	long i;
	for(i=0;i<N;i++)
		if(m_processors.GetAt(i)==ob)
		{
			m_procs[i]=false;
			break;
		}
	if(i==N)
	{
		N=m_processorsp.GetSize();
		for(i=0;i<N;i++)
			if(m_processorsp.GetAt(i)==ob)
			{
				m_procsp[i]=false;
				break;
			}
	}
}

double CGNetworkS::GetClockAdvance()
{
	return m_CLK;
}

void CGNetworkS::SetClockAdvance(double time)
{
	m_CLK=time;
}

double CGNetworkS::GetClockPrecision()
{
	return m_CLKP;
}


void CGNetworkS::SetManualStart(bool type)
{
	m_manual_start=type;
}

void CGNetworkS::Start()
{
	m_coordinator->CreateThread(0,0,NULL);
	m_coordinator->SetThreadPriority(THREAD_PRIORITY_ABOVE_NORMAL);
}

CGNetworkS * CGNetworkS::GetNet(long name)
{
	CGNetworkS *net;
	for(int i=0;i<m_nnets;i++)
	{
		net=(CGNetworkS *)m_networks[i];
		if(net->GetName()==name) return net;
	}
	return NULL;
}

CGNetworkS *CGNetworkS::GetNNet(CString &data)
{
	CGNetworkS *net;
	if(m_netpos<m_nnets)
	{
		net=(CGNetworkS *)m_networks[m_netpos];
		data.Empty();
		data.Format("%ld",net->GetName());
		m_netpos++;
		return net;
	}
	return NULL;
}

CGProcessor * CGNetworkS::GetNProc(CString &data)
{
	CGProcessor *proc;
	if(m_procpos<m_nprocs)
	{
		proc=(CGProcessor *)m_processors[m_procpos];
		data.Empty();
		data.Format("%ld",proc->GetName());
		m_procpos++;
		return proc;
	}
	return NULL;
}

CGProcessor * CGNetworkS::GetNProcP(CString &data)
{
	CGProcessor *proc;
	if(m_procppos<m_nprocsp)
	{
		proc=(CGProcessor *)m_processorsp[m_procppos];
		data.Empty();
		data.Format("%ld",proc->GetName());
		m_procppos++;
		return proc;
	}
	return NULL;
}

CGData * CGNetworkS::GetNIPort(CString &data)
{
	CGData *in;
	if(m_iportpos<m_nin)
	{
		in=(CGData *)m_inputs[m_iportpos];
		data.Empty();
		data.Format("%ld",in->GetName());
		m_iportpos++;
		return in;
	}
	return NULL;
}

CGData * CGNetworkS::GetNOPort(CString &data)
{
	CGData *out;
	if(m_oportpos<m_nout)
	{
		out=(CGData *)m_outputs[m_oportpos];
		data.Empty();
		data.Format("%ld",out->GetName());
		m_oportpos++;
		return out;
	}
	return NULL;
}

void CGNetworkS::ResetNNet()
{
	m_netpos=0;
}

void CGNetworkS::ResetNProc()
{
	m_procpos=0;
}


void CGNetworkS::ResetNProcP()
{
	m_procppos=0;
}

void CGNetworkS::ResetNIPort()
{
	m_iportpos=0;
}

void CGNetworkS::ResetNOPort()
{
	m_oportpos=0;
}

