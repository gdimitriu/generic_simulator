// InputPartModification.cpp : implementation file
//
/*
	Copyright Gabriel Dimitriu
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the implementation of Input Parts for Simulation Coordinator.
	
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
#include "GSLib_dyn.h"
#include "SInputPartModification.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputPartModification dialog


CSInputPartModification::CSInputPartModification(CWnd* pParent /*=NULL*/)
	: CDialog(CSInputPartModification::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSInputPartModification)
	m_errors = _T("");
	m_time = 0.0;
	m_wireshist = _T("");
	m_levels = _T("");
	m_copy_levels = _T("");
	m_copy_from = 0;
	m_copy_element = 0;
	m_copy_level = 0;
	m_element = 0;
	m_level = 0;
	m_fromtoport = 0;
	m_toport = 0;
	m_topart = 0;
	m_passive = FALSE;
	m_new = FALSE;
	m_all = FALSE;
	//}}AFX_DATA_INIT
	m_parent=NULL;
	m_coordinator=NULL;
}


void CSInputPartModification::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSInputPartModification)
	DDX_Control(pDX, IDC_up_levels, m_up_levels);
	DDX_Control(pDX, IDC_oldelem, m_oldelem);
	DDX_Control(pDX, IDC_from, m_from);
	DDX_Text(pDX, IDC_errors_messages, m_errors);
	DDX_Text(pDX, IDC_time, m_time);
	DDX_Text(pDX, IDC_wireshist, m_wireshist);
	DDX_Text(pDX, IDC_levels, m_levels);
	DDX_Text(pDX, IDC_copy_levels, m_copy_levels);
	DDX_Text(pDX, IDC_copy_from, m_copy_from);
	DDX_Text(pDX, IDC_copy_element, m_copy_element);
	DDX_Text(pDX, IDC_copy_level, m_copy_level);
	DDX_Text(pDX, IDC_element, m_element);
	DDX_Text(pDX, IDC_level, m_level);
	DDX_Text(pDX, IDC_fromtoport, m_fromtoport);
	DDX_Text(pDX, IDC_toport, m_toport);
	DDX_Text(pDX, IDC_topart, m_topart);
	DDX_Check(pDX, IDC_pas_act, m_passive);
	DDX_Check(pDX, IDC_new_old, m_new);
	DDX_Check(pDX, IDC_all, m_all);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSInputPartModification, CDialog)
	//{{AFX_MSG_MAP(CSInputPartModification)
	ON_BN_CLICKED(IDC_addelem, Onaddelem)
	ON_BN_CLICKED(IDC_addwire, Onaddwire)
	ON_BN_CLICKED(IDC_del, Ondel)
	ON_BN_CLICKED(IDC_copy_down, Oncopydown)
	ON_BN_CLICKED(IDC_copy_reset, Oncopyreset)
	ON_BN_CLICKED(IDC_copy_up, Oncopyup)
	ON_BN_CLICKED(IDC_level_down, Onleveldown)
	ON_BN_CLICKED(IDC_level_reset, Onlevelreset)
	ON_BN_CLICKED(IDC_level_up, Onlevelup)
	ON_BN_CLICKED(IDC_fromnet, Onfromnet)
	ON_BN_CLICKED(IDC_fromproc, Onfromproc)
	ON_BN_CLICKED(IDC_wantnet, Onwantnet)
	ON_BN_CLICKED(IDC_standalone, Onstandalone)
	ON_CBN_SELENDOK(IDC_from, OnSelendokfrom)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSInputPartModification message handlers

void CSInputPartModification::Onleveldown() 
{
	CGNetworkS *net1;
	CString net;
	if(m_cLevel!=m_parent)
	{
		m_cLevel=(CGNetworkS *)m_cLevel->GetParent();
		m_level=m_cLevel->GetName();
		m_cLevel->ResetNNet();
		m_up_levels.ResetContent();
		networks.RemoveAll();
		net.Empty();
		net1=m_cLevel->GetNNet(net);
		while(net1!=NULL)
		{
			m_up_levels.AddString(net);
			networks.Add(net1);
			net.Empty();
			net1=m_cLevel->GetNNet(net);
		}
		
		long size=str_levels.GetSize();
		if(size!=1)
		{
			long i;
			CString *str;
			str=(CString *)str_levels.GetAt(size-1);
			str_levels.RemoveAt(size-1);
			str_levels.FreeExtra();
			delete str;
			m_levels.Empty();
			for(i=0;i<(size-1);i++)
				m_levels+=(*((CString *)str_levels.GetAt(i)));
		}
	}
	UpdateData(FALSE);
}

void CSInputPartModification::Onlevelreset() 
{
	UpdateData(TRUE);
	CGNetworkS *net1;
	CString net;
	m_cLevel=m_parent;
	m_level=m_parent->GetName();
	m_cLevel->ResetNNet();
	m_up_levels.ResetContent();
	networks.RemoveAll();
	net.Empty();
	net1=m_cLevel->GetNNet(net);
	while(net1!=NULL)
	{
		m_up_levels.AddString(net);
		networks.Add(net1);
		net.Empty();
		net1=m_cLevel->GetNNet(net);
	}
	long size=str_levels.GetSize();
	CString *str;
	if(size==0)
	{
		str=new CString();
		str->Format("Parent net=%ld\n",m_parent->GetName());
		str_levels.Add(str);
		m_levels.Empty();
		m_levels+=*str;
		UpdateData(FALSE);
		return;
	}
	if(size!=1)
	{
		long i;
		for(i=1;i<size;i++)
		{
			str=(CString *)str_levels.GetAt(i);
			str_levels.RemoveAt(i);
			str_levels.FreeExtra();
			delete str;
		}
		m_levels.Empty();
		for(i=0;i<size-1;i++)
			m_levels+=(*((CString *)str_levels.GetAt(i)));
		UpdateData(FALSE);
		return;
	}
	UpdateData(FALSE);
}

void CSInputPartModification::Onlevelup() 
{
	UpdateData(TRUE);
	CGNetworkS *net1;
	CString net;
	int index=m_up_levels.GetCurSel();
	if(index!=CB_ERR)
	{
		m_up_levels.GetLBText(index,net);
		m_level=atoi(net);
		net1=m_cLevel->GetNet(m_level);
		if(net1!=NULL)
		{
			m_cLevel=net1;
			m_cLevel->ResetNNet();
			m_up_levels.ResetContent();
			networks.RemoveAll();
			net.Empty();
			net1=m_cLevel->GetNNet(net);
			while(net1!=NULL)
			{
				m_up_levels.AddString(net);
				networks.Add(net1);
				net.Empty();
				net1=m_cLevel->GetNNet(net);
			}
			CString *str;
			str=new CString();
			str->Format("in net=%ld\n",m_level);
			str_levels.Add(str);
			m_levels+=*str;
		}
	}
	UpdateData(FALSE);
}

void CSInputPartModification::Onfromnet() 
{
	UpdateData(TRUE);
	int id;
	id=GetCheckedRadioButton(IDC_wantport,IDC_wantnet);
	if(id==IDC_wantnet)
	{
		CheckRadioButton(IDC_standalone,IDC_fromnet,IDC_standalone);
		return;
	}
	CGNetworkS *net1;
	CString net;
	m_from.ResetContent();
	from_element.RemoveAll();
	net.Empty();
	m_cLevel->ResetNNet();
	net1=m_cLevel->GetNNet(net);
	while(net1!=NULL)
	{
		m_from.AddString(net);
		from_element.Add(net1);
		net.Empty();
		net1=m_cLevel->GetNNet(net);
	}
	UpdateData(FALSE);
}

void CSInputPartModification::Onfromproc() 
{
	UpdateData(TRUE);
	int id;
	id=GetCheckedRadioButton(IDC_wantport,IDC_wantnet);
	if(id==IDC_wantnet)
	{
		CheckRadioButton(IDC_standalone,IDC_fromnet,IDC_standalone);
		return;
	}
	CGProcessor *proc1;
	CString proc;
	m_from.ResetContent();
	from_element.RemoveAll();
	proc.Empty();
	if(m_all==TRUE)
	{
		m_cLevel->ResetNProc();
		proc1=m_cLevel->GetNProc(proc);
		while(proc1!=NULL)
		{
			m_from.AddString(proc);
			from_element.Add(proc1);
			proc.Empty();
			proc1=m_cLevel->GetNProc(proc);
		}
		m_cLevel->ResetNProcP();
		proc1=m_cLevel->GetNProcP(proc);
		while(proc1!=NULL)
		{
			m_from.AddString(proc);
			from_element.Add(proc1);
			proc.Empty();
			proc1=m_cLevel->GetNProcP(proc);
		}
	}
	else if(m_passive==FALSE)
	{
		m_cLevel->ResetNProc();
		proc1=m_cLevel->GetNProc(proc);
		while(proc1!=NULL)
		{
			m_from.AddString(proc);
			from_element.Add(proc1);
			proc.Empty();
			proc1=m_cLevel->GetNProc(proc);
		}
	}
	else
	{
		m_cLevel->ResetNProcP();
		proc1=m_cLevel->GetNProcP(proc);
		while(proc1!=NULL)
		{
			m_from.AddString(proc);
			from_element.Add(proc1);
			proc.Empty();
			proc1=m_cLevel->GetNProcP(proc);
		}
	}
	UpdateData(FALSE);
}

void CSInputPartModification::Onstandalone() 
{
	UpdateData(TRUE);
	CString net1;
	m_from.ResetContent();
	m_oldelem.ResetContent();
	from_element.RemoveAll();
	want_element.RemoveAll();
	int id;
	CGNetworkS *net;
	id=GetCheckedRadioButton(IDC_wantport,IDC_wantnet);
	if(id==IDC_wantport)
	{
		net=m_cLevel;
		id=GetCheckedRadioButton(IDC_input,IDC_output);
		CGData *port1;
		CString port;
		if(net!=NULL)
		{
			if(id==IDC_input)
			{
				port.Empty();
				net->ResetNIPort();
				port1=net->GetNIPort(port);
				while(port1!=NULL)
				{
					m_oldelem.AddString(port);
					want_element.Add(port1);
					port.Empty();
					port1=net->GetNIPort(port);
				}
			}
			else if(id==IDC_output)
			{
				port.Empty();
				net->ResetNOPort();
				port1=net->GetNOPort(port);
				while(port1!=NULL)
				{
					m_oldelem.AddString(port);
					want_element.Add(port1);
					port.Empty();
					port1=net->GetNOPort(port);
				}
			}
		}
	}
	else if(id==IDC_wantproc)
	{
		net=m_cLevel;
		if(net!=NULL)
		{
			CGProcessor *proc1;
			CString proc;
			if(m_all==TRUE)
			{
				proc.Empty();
				net->ResetNProc();
				proc1=net->GetNProc(proc);
				while(proc1!=NULL)
				{
					m_oldelem.AddString(proc);
					want_element.Add(proc1);
					proc.Empty();
					proc1=net->GetNProc(proc);
				}
				proc.Empty();
				net->ResetNProcP();
				proc1=net->GetNProcP(proc);
				while(proc1!=NULL)
				{
					m_oldelem.AddString(proc);
					want_element.Add(proc1);
					proc.Empty();
					proc1=net->GetNProcP(proc);
				}
			}
			else if(m_passive==FALSE)
			{
				proc.Empty();
				net->ResetNProc();
				proc1=net->GetNProc(proc);
				while(proc1!=NULL)
				{
					m_oldelem.AddString(proc);
					want_element.Add(proc1);
					proc.Empty();
					proc1=net->GetNProc(proc);
				}
			}
			else
			{
				proc.Empty();
				net->ResetNProcP();
				proc1=net->GetNProcP(proc);
				while(proc1!=NULL)
				{
					m_oldelem.AddString(proc);
					want_element.Add(proc1);
					proc.Empty();
					proc1=net->GetNProcP(proc);
				}
			}
		}
	}
	else if(id==IDC_wantnet)
	{
		net1.Empty();
		m_cLevel->ResetNNet();
		net=m_cLevel->GetNNet(net1);
		while(net!=NULL)
		{
			m_oldelem.AddString(net1);
			want_element.Add(net);
			net1.Empty();
			net=m_cLevel->GetNNet(net1);
		}
	}
	UpdateData(FALSE);	
}

void CSInputPartModification::Onwantnet() 
{
	UpdateData(TRUE);
	from_element.RemoveAll();
	want_element.RemoveAll();
	m_oldelem.ResetContent();
	CheckRadioButton(IDC_standalone,IDC_fromnet,IDC_standalone);
	CGNetworkS *net1;
	CString net;
	net.Empty();
	m_cLevel->ResetNNet();
	net1=m_cLevel->GetNNet(net);
	while(net1!=NULL)
	{
		m_oldelem.AddString(net);
		want_element.Add(net1);
		net.Empty();
		net1=m_cLevel->GetNNet(net);
	}
	UpdateData(FALSE);
}

void CSInputPartModification::OnSelendokfrom() 
{
	UpdateData(TRUE);
	int id;
	m_oldelem.ResetContent();
	want_element.RemoveAll();
	id=GetCheckedRadioButton(IDC_wantport,IDC_wantnet);
	if(id==IDC_wantproc)
		wantproc();
	else if(id==IDC_wantport)
		wantport();
	UpdateData(FALSE);
}

void CSInputPartModification::wantproc()
{
	int id;
	int index;
	CString temp;
	id=GetCheckedRadioButton(IDC_standalone,IDC_fromnet);
	CGNetworkS *net=NULL;
	if(id==IDC_fromnet)
	{
		index=m_from.GetCurSel();
		if(index!=CB_ERR)
		{
			net=(CGNetworkS *)from_element[index];
		}
	}
	else if(id==IDC_standalone)
		net=m_cLevel;
	if(net!=NULL)
	{
		CGProcessor *proc1;
		CString proc;
		if(m_all==TRUE)
		{
			proc.Empty();
			net->ResetNProc();
			proc1=net->GetNProc(proc);
			while(proc1!=NULL)
			{
				m_oldelem.AddString(proc);
				want_element.Add(proc1);
				proc.Empty();
				proc1=net->GetNProc(proc);
			}
			proc.Empty();
			net->ResetNProcP();
			proc1=net->GetNProcP(proc);
			while(proc1!=NULL)
			{
				m_oldelem.AddString(proc);
				want_element.Add(proc1);
				proc.Empty();
				proc1=net->GetNProcP(proc);
			}
		}
		else if(m_passive==FALSE)
		{
			proc.Empty();
			net->ResetNProc();
			proc1=net->GetNProc(proc);
			while(proc1!=NULL)
			{
				m_oldelem.AddString(proc);
				want_element.Add(proc1);
				proc.Empty();
				proc1=net->GetNProc(proc);
			}
		}
		else
		{
			proc.Empty();
			net->ResetNProcP();
			proc1=net->GetNProcP(proc);
			while(proc1!=NULL)
			{
				m_oldelem.AddString(proc);
				want_element.Add(proc1);
				proc.Empty();
				proc1=net->GetNProcP(proc);
			}
		}
	}
}

void CSInputPartModification::wantport()
{
	int id;
	int index;
	CString temp;
	id=GetCheckedRadioButton(IDC_standalone,IDC_fromnet);
	CGNetworkS *net=NULL;
	CGProcessor *proc=NULL;
	if(id==IDC_fromnet)
	{
		index=m_from.GetCurSel();
		if(index!=CB_ERR)
		{
			net=(CGNetworkS *)from_element[index];
		}
	}
	else if(id==IDC_standalone)
		net=m_cLevel;
	else if(id==IDC_fromproc)
	{
		index=m_from.GetCurSel();
		if(index!=CB_ERR)
		{
			proc=(CGProcessor *)from_element[index];
		}
	}
	id=GetCheckedRadioButton(IDC_input,IDC_output);
	CGData *port1;
	CString port;
	if(net!=NULL)
	{
		if(id==IDC_input)
		{
			port.Empty();
			net->ResetNIPort();
			port1=net->GetNIPort(port);
			while(port1!=NULL)
			{
				m_oldelem.AddString(port);
				want_element.Add(port1);
				port.Empty();
				port1=net->GetNIPort(port);
			}
		}
		else if(id==IDC_output)
		{
			port.Empty();
			net->ResetNOPort();
			port1=net->GetNOPort(port);
			while(port1!=NULL)
			{
				m_oldelem.AddString(port);
				want_element.Add(port1);
				port.Empty();
				port1=net->GetNOPort(port);
			}
		}

	}
	else if(proc!=NULL)
	{
		if(id==IDC_input)
		{
			port.Empty();
			proc->ResetNIPort();
			port1=proc->GetNIPort(port);
			while(port1!=NULL)
			{
				m_oldelem.AddString(port);
				want_element.Add(port1);
				port.Empty();
				port1=proc->GetNIPort(port);
			}
		}
		else if(id==IDC_output)
		{
			port.Empty();
			proc->ResetNOPort();
			port1=proc->GetNOPort(port);
			while(port1!=NULL)
			{
				m_oldelem.AddString(port);
				want_element.Add(port1);
				port.Empty();
				port1=proc->GetNOPort(port);
			}
		}
	}
}

void CSInputPartModification::Ondel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	long ifrom,index;
	ifrom=m_from.GetCurSel();
	index=m_oldelem.GetCurSel();
	m_elem=new element();
	m_elem->dead=(CObject *)want_element.GetAt(index);
	if(ifrom!=CB_ERR)
		m_elem->parent=(CObject *)from_element.GetAt(ifrom);
	else m_elem->parent=(CObject *)m_cLevel;
	m_elem->m_time=m_time;
	m_elem->type=4;
	m_queue->Add(m_elem);
	UpdateData(FALSE);
}

void CSInputPartModification::Onaddelem() 
{
	// TODO: Add your control notification handler code here
	
}

void CSInputPartModification::Onaddwire() 
{
	// TODO: Add your control notification handler code here
	
}

void CSInputPartModification::Oncopydown() 
{
	// TODO: Add your control notification handler code here
	
}

void CSInputPartModification::Oncopyreset() 
{
	// TODO: Add your control notification handler code here
	
}

void CSInputPartModification::Oncopyup() 
{
	// TODO: Add your control notification handler code here
	
}


void CSInputPartModification::Set(CGCoordinator *coord)
{
	m_coordinator=coord;
}

void CSInputPartModification::SetParent(CGNetworkS *net)
{
	m_parent=net;
	m_cLevel=net;
}

void CSInputPartModification::SetQueue(CSQueue *qu)
{
	m_queue=qu;
}
