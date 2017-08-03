// SInputCoordinator.cpp : implementation file
//
/*
	Copyright Gabriel Dimitriu
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the implementation of Input data for Simulation Coordinator.
	
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
#include "SInputCoordinator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSInputCoordinator dialog


CSInputCoordinator::CSInputCoordinator(CWnd* pParent /*=NULL*/)
	: CDialog(CSInputCoordinator::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSInputCoordinator)
	m_filename = _T("");
	m_timetable = _T("");
	m_dim = 0;
	m_portname = 0;
	m_time = 0.0;
	m_InputData = _T("");
	m_repartition = _T("");
	m_error = _T("");
	m_clkadvance = 1.0;
	m_clkprec = 0.5;
	//}}AFX_DATA_INIT
}


void CSInputCoordinator::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSInputCoordinator)
	DDX_Text(pDX, IDC_fileName, m_filename);
	DDX_Text(pDX, IDC_timetable, m_timetable);
	DDX_Text(pDX, IDC_dim, m_dim);
	DDX_Text(pDX, IDC_portname, m_portname);
	DDX_Text(pDX, IDC_time, m_time);
	DDX_Text(pDX, IDC_InputData, m_InputData);
	DDX_Text(pDX, IDC_rep, m_repartition);
	DDX_Text(pDX, IDC_error, m_error);
	DDX_Text(pDX, IDC_clkadvance, m_clkadvance);
	DDX_Text(pDX, IDC_clkprec, m_clkprec);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSInputCoordinator, CDialog)
	//{{AFX_MSG_MAP(CSInputCoordinator)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_check, Oncheck)
	ON_BN_CLICKED(IDC_Delete, OnDelete)
	ON_BN_CLICKED(IDC_Load, OnLoad)
	ON_BN_CLICKED(IDC_Save, OnSave)
	ON_BN_CLICKED(IDC_modify, Onmodify)
	ON_BN_CLICKED(IDC_next, Onnext)
	ON_BN_CLICKED(IDC_prev, Onprev)
	ON_BN_CLICKED(IDC_gDim, OngDim)
	ON_BN_CLICKED(IDC_reset, Onreset)
	ON_BN_CLICKED(IDC_relinkup, Onrelinkup)
	ON_BN_CLICKED(IDC_relinkdown, Onrelinkdown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSInputCoordinator message handlers

void CSInputCoordinator::SetParent(CGNetworkS *net)
{
	m_parent=net;
}

void CSInputCoordinator::OnAdd() 
{
	UpdateData(TRUE);
	m_elem=new element();
	m_elem->dim=m_dim;
	m_elem->m_name=m_portname;
	m_elem->m_time=m_time;
	m_elem->data=(double *)calloc(m_dim,sizeof(double));
	int type;
	type=GetCheckedRadioButton(IDC_init,IDC_print);
	switch(type)
	{
	case IDC_init:
		m_elem->type=0;
		break;
	case IDC_internal:
		m_elem->type=1;
		break;
	case IDC_external:
		m_elem->type=2;
		break;
	default:
		m_elem->type=3;
	}
	int manual;
	CString tmp;
	manual=GetCheckedRadioButton(IDC_dmanual,IDC_automatic);
	if(manual==IDC_dmanual)
	{
		if(m_elem->type==2)
		{
			int pos;
			long i;
			int type1;
			pos=0;
			i=0;
			while(pos!=-1)
			{
				pos=m_InputData.Find(';',pos);
				if(pos!=-1)
				{
					pos++;
					i++;
				}
			}
			if(i!=m_dim)
			{
				m_error.Empty();
				m_error.Insert(0,"Dimensions do't agree !");
				UpdateData(FALSE);
				return;
			}
			else
			{
				m_error.Empty();
				m_error.Insert(0,"OK!");
			}
			type1=0;
			for(i=0;i<m_dim;i++)
			{
				type=m_InputData.Find(';',type1);
				tmp.Empty();
				tmp=m_InputData.Mid(type1,type-type1);
				type1=type+1;
				LPSTR tmp1;
				tmp1=tmp.GetBuffer(100);
				m_elem->data[i]=atof(tmp1);
				tmp.ReleaseBuffer(100);
			}
		}
		m_elem->manual=1;
	}
	else
		m_elem->manual=0;
	queue.Add(m_elem);
	m_timetable.Empty();
	queue.Get(m_timetable);
	UpdateData(FALSE);
}

void CSInputCoordinator::OnDelete() 
{
	if(m_elem!=NULL)
		queue.Delete(m_elem);
	m_timetable.Empty();
	queue.Get(m_timetable);
	UpdateData(FALSE);
}

void CSInputCoordinator::OnLoad() 
{
	CFile f;
	UpdateData(TRUE);
	f.Open(m_filename,CFile::modeRead );
	CArchive ar(&f, CArchive::load);
	Serialize(ar);
	ar.Close();
	f.Close();
}

void CSInputCoordinator::OnSave() 
{
	CFile f;
	UpdateData(TRUE);
	f.Open( m_filename, CFile::modeCreate | CFile::modeWrite );
	CArchive ar(&f, CArchive::store);
	Serialize(ar);
	ar.Close();
	f.Close();
}

void CSInputCoordinator::Onmodify() 
{
	UpdateData(TRUE);
	m_elem->dim=m_dim;
	m_elem->m_name=m_portname;
	m_elem->m_time=m_time;
	int type;
	type=GetCheckedRadioButton(IDC_init,IDC_print);
	switch(type)
	{
	case IDC_init:
		if(m_elem->type==2)
		{
			free(m_elem->data);
			m_elem->data=NULL;
		}
		m_elem->type=0;
		break;
	case IDC_internal:
		if(m_elem->type==2)
		{
			free(m_elem->data);
			m_elem->data=NULL;
		}
		m_elem->type=1;
		break;
	case IDC_external:
		m_elem->type=2;
		break;
	default:
		if(m_elem->type==2)
		{
			free(m_elem->data);
			m_elem->data=NULL;
		}
		m_elem->type=3;
	}
	int manual;
	CString tmp;
	manual=GetCheckedRadioButton(IDC_dmanual,IDC_automatic);
	if(manual==IDC_dmanual)
	{
		if(m_elem->type==2)
		{
			int pos;
			long i;
			int type1;
			pos=0;
			i=0;
			while(pos!=-1)
			{
				pos=m_InputData.Find(';',pos);
				if(pos!=-1)
				{
					pos++;
					i++;
				}
			}
			if(i!=m_dim)
			{
				m_error.Empty();
				m_error.Insert(0,"Dimensions do't agree !");
				UpdateData(FALSE);
				return;
			}
			else
			{
				m_error.Empty();
				m_error.Insert(0,"OK!");
			}
			type1=0;
			for(i=0;i<m_dim;i++)
			{
				type=m_InputData.Find(';',type1);
				tmp.Empty();
				tmp=m_InputData.Mid(type1,type-type1);
				type1=type+1;
				LPSTR tmp1;
				tmp1=tmp.GetBuffer(100);
				m_elem->data[i]=atof(tmp1);
				tmp.ReleaseBuffer(100);
			}
		}
		m_elem->manual=1;
	}
	else
		m_elem->manual=0;
}

void CSInputCoordinator::Onnext() 
{
	m_elem=queue.Next();
	if(m_elem==NULL) return;
	m_portname=m_elem->m_name;
	m_time=m_elem->m_time;
	m_dim=m_elem->dim;
	CString temp;
	long i;
	m_InputData.Empty();
	if(m_elem->type==2)
	{
		for(i=0;i<m_dim;i++)
		{
			temp.Empty();
			temp.Format("%lf;\n",m_elem->data[i]);
			m_InputData.Insert(m_InputData.GetLength(),temp);
		}
		if(m_elem->manual==1)
			CheckRadioButton(IDC_dmanual,IDC_automatic,IDC_dmanual);
		else
			CheckRadioButton(IDC_dmanual,IDC_automatic,IDC_automatic);
	}
	switch(m_elem->type)
	{
	case 0:
		CheckRadioButton(IDC_init,IDC_print,IDC_init);
		break;
	case 1:
		CheckRadioButton(IDC_init,IDC_print,IDC_internal);
		break;
	case 2:
		CheckRadioButton(IDC_init,IDC_print,IDC_external);
		break;
	case 3:
		CheckRadioButton(IDC_init,IDC_print,IDC_print);
		break;
	}
	UpdateData(FALSE);
}

void CSInputCoordinator::Onprev() 
{
	m_elem=queue.Prev();
	if(m_elem==NULL) return;
	m_portname=m_elem->m_name;
	m_time=m_elem->m_time;
	m_dim=m_elem->dim;
	CString temp;
	long i;
	m_InputData.Empty();
	if(m_elem->type==2)
	{
		for(i=0;i<m_dim;i++)
		{
			temp.Empty();
			temp.Format("%lf;\n",m_elem->data[i]);
			m_InputData.Insert(m_InputData.GetLength(),temp);
		}
		if(m_elem->manual==1)
			CheckRadioButton(IDC_dmanual,IDC_automatic,IDC_dmanual);
		else
			CheckRadioButton(IDC_dmanual,IDC_automatic,IDC_automatic);
	}
	switch(m_elem->type)
	{
	case 0:
		CheckRadioButton(IDC_init,IDC_print,IDC_init);
		break;
	case 1:
		CheckRadioButton(IDC_init,IDC_print,IDC_internal);
		break;
	case 2:
		CheckRadioButton(IDC_init,IDC_print,IDC_external);
		break;
	case 3:
		CheckRadioButton(IDC_init,IDC_print,IDC_print);
		break;
	}
	UpdateData(FALSE);	
}

void CSInputCoordinator::Oncheck() 
{
	UpdateData(TRUE);
	long i;
	int pos;
	pos=0;
	i=0;
	while(pos!=-1)
	{
		pos=m_InputData.Find(';',pos);
		if(pos!=-1)
		{
			pos++;
			i++;
		}
	}
	if(i!=m_dim)
	{
		m_error.Empty();
		m_error.Insert(0,"Dimensions do't agree !");
	}
	else
	{
		m_error.Empty();
		m_error.Insert(0,"OK!");
	}
	UpdateData(FALSE);
}

void CSInputCoordinator::OngDim() 
{
	UpdateData(TRUE);
	m_dim=m_parent->GetDimPort(m_portname);
	UpdateData(FALSE);	
}

BOOL CSInputCoordinator::OnInitDialog()
{
	CDialog::OnInitDialog();
	CheckRadioButton(IDC_init,IDC_print,IDC_init);
	CheckRadioButton(IDC_dmanual,IDC_automatic,IDC_dmanual);
	return TRUE;
}

void CSInputCoordinator::Serialize(CArchive &ar)
{
	CDialog::Serialize(ar);
	queue.Serialize(ar);
	if(ar.IsStoring())
	{
		UpdateData(TRUE);
		ar<<m_dim;
		ar<<m_clkadvance;
		ar<<m_clkprec;
		ar<<m_portname;
		ar<<m_InputData;
		ar<<m_time;
		ar<<m_timetable;
		ar<<m_error;
	}
	else
	{
		ar>>m_dim;
		ar>>m_clkadvance;
		ar>>m_clkprec;
		ar>>m_portname;
		ar>>m_InputData;
		ar>>m_time;
		ar>>m_timetable;
		ar>>m_error;
		UpdateData(FALSE);
	}
}

void CSInputCoordinator::Onreset() 
{
	queue.Reset();
}

void CSInputCoordinator::Onrelinkup() 
{
	queue.RelinkUp();
	m_timetable.Empty();
	queue.Get(m_timetable);
	UpdateData(FALSE);
}

void CSInputCoordinator::Onrelinkdown() 
{
	// TODO: Add your control notification handler code here
	
}
