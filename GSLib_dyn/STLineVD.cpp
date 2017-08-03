// STLineVD.cpp: implementation of the CSTLineVD class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the implementation of simulation transition line with variable 
	delay and noise class.
	
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
#include "STLineVD.h"
#include "GInput.h"
#include "GOutput.h"
IMPLEMENT_SERIAL(CSTLineVD,CSTLineSD,1);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSTLineVD::CSTLineVD()
{

}

CSTLineVD::CSTLineVD(CObject *net,long name,long dim,CString *delay) : CSTLineSD(net,name,NULL,false)
{
	CGInput *pin;
	CGOutput *pout;
	pin=new CGInput(0);
	pin->SetDim(dim);
	AddPort(pin,true);
	pout=new CGOutput(1);
	pout->SetDim(dim);
	AddPort(pout,false);
	m_delay.SetGen(delay);
	m_delay.Set(name);
	m_typenoise=0;
}

CSTLineVD::CSTLineVD(CObject *net,long name,long dim,CString *delay,CString *noise) : CSTLineSD(net,name,NULL,false)
{
	CGInput *pin;
	CGOutput *pout;
	pin=new CGInput(0);
	pin->SetDim(dim);
	AddPort(pin,true);
	pout=new CGOutput(1);
	pout->SetDim(dim);
	AddPort(pout,false);
	m_delay.SetGen(delay);
	m_delay.Set(name);
	m_noise.SetGen(noise);
	m_noise.Set(name);
	m_typenoise=1;
}

CSTLineVD::~CSTLineVD()
{

}

void CSTLineVD::Serialize(CArchive &ar)
{
	CSTLineSD::Serialize(ar);
	m_delay.Serialize(ar);
	m_noise.Serialize(ar);
	if(ar.IsStoring())
	{
		ar<<m_typenoise;
	}
	else
	{
		ar>>m_typenoise;
	}
}


int CSTLineVD::receive1(double time)
{
//
//we have internal transition
//
	bool m_run;
	long i;
	CGData *data;
	m_run=true;
//	cout<<"rec1 "<<time<<endl;cout.flush();
	if(((CGNetworkS *)m_parent)->GetCoordinator()!=NULL)
		if(((CGNetworkS *)m_parent)->GetWork(this)==true)
			m_run=false;
	((CGNetworkS *)m_parent)->ResetProc(this);
	if((fabs(time-m_tN)<precision || fabs(m_tN-time)<m_CLKP || fabs(m_tN)<precision) && m_run==true)
	{
		proc_lambda((element *)m_value[0]);
		if(m_queue.empty()==true)
			m_extern=false;
		else
		{
			m_extern=true;
			data=(CGData *)(m_queue.front());
			double *value;
			long dim;
			value=data->Get(&dim);
			for(i=0;i<dim;i++)
				switch(m_typenoise)
				{
					case 0:
						((element *)m_value[0])->data[i]=value[i];
						break;
					case 1:
						((element *)m_value[0])->data[i]=value[i]+m_noise.generate();
						break;
					default:
						((element *)m_value[0])->data[i]=value[i];
				}
			SettL(GetTime());
			SettN(data->GetTime());
			Put1(data->GetTime());
			delete data;
		}
	}
	else if(time<m_tN)
	{
		if(m_rtype==true)
			proc_lambda(NULL);
	}
	return 4;
}

int CSTLineVD::ExternN(CGData *input, double time)
{
	long i;
	long dim;
	double *value;
	CGInput *in;
	in=(CGInput *)input;
	value=in->Get(&dim);
	CGData *data;
	if(m_queue.empty()==false)
	{
		if(m_extern==true)
			proc_lambda((element *)m_value[0]);
		data=new CGData(in->m_name);
		data->SetDim(dim);
		data->Set(value);
		data->SetTime(in->GetTime()+m_delay.generate());
		data->SetSource(in->GetSource());
		data->SetSourceName(in->GetSourceName());
		m_queue.add((CObject *)data);
		data=(CGData *)(m_queue.front());
		if(data==NULL) cout<<"Error!\n";cout.flush();
		m_extern=true;
		value=data->Get(&dim);
		for(i=0;i<dim;i++)
			switch(m_typenoise)
			{
				case 0:
					((element *)m_value[0])->data[i]=value[i];
					break;
				case 1:
					((element *)m_value[0])->data[i]=value[i]+m_noise.generate();
					break;
				default:
					((element *)m_value[0])->data[i]=value[i];
			}
		SettL(GetTime());
		SettN(data->GetTime());
		Put1(data->GetTime());
		delete data;
	}
	else
	{
		if(m_extern==true)
			proc_lambda((element *)m_value[0]);
		m_extern=true;
		value=in->Get(&dim);
		switch(m_typenoise)
		{
			case 0:
				for(i=0;i<dim;i++)
					((element *)m_value[0])->data[i]=value[i];
				break;
			case 1:
				for(i=0;i<dim;i++)
					((element *)m_value[0])->data[i]=value[i]+m_noise.generate();
				break;
			default:
				for(i=0;i<dim;i++)
					((element *)m_value[0])->data[i]=value[i];
		}
		SettL(GetTime());
		double temp;
		temp=in->GetTime()+m_delay.generate();
		SettN(temp);
		return Put1(temp);
	}
	return 4;
}

int CSTLineVD::ExternS(CGData *input, double time)
{
	long dim;
	double *value;
	CGInput *in;
	in=(CGInput *)input;
	value=in->Get(&dim);
	CGData *data;
	data=new CGData(in->m_name);
	data->SetDim(dim);
	data->Set(value);
	data->SetTime(in->GetTime()+m_delay.generate());
	data->SetSource(in->GetSource());
	data->SetSourceName(in->GetSourceName());
	m_queue.add((CObject *)data);
	return 4;
}

int CSTLineVD::Put1(double time)
{
	CGCElem *elem=new CGCElem(this,1,time,NULL);
	CGCoordinator *coord;
	if(m_parent->IsKindOf(RUNTIME_CLASS(CGNetworkS))!=0)
		coord=((CGNetworkS *)m_parent)->GetCoordinator();
	else return -1;
	if(coord!=NULL)
	{
		coord->CoordinatorLock();
		coord->Add(elem);
		coord->CoordinatorUnlock();
		coord->Event_Add();
	}
//	cout<<"Put at "<<GetTime()<<" for "<<GetNextTime()<<endl;cout.flush();
	return 4;
}
