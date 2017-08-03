// parser_func_memory.cpp: implementation of the Cparser_func_memory class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright 2005 Gabriel Dimitriu

	This file is part of parser functions.
	This file contains the implementation of memory variables.
	
    Parser functions is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Parser functions is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Parser functions; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  
*/
#include "stdafx.h"
#include "parser_func_memory.h"
#include <stdlib.h>
#include<iostream>
#include<string.h>
IMPLEMENT_SERIAL(Cparser_func_memory,CObject,1);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cparser_func_memory::Cparser_func_memory()
{
	head=NULL;
	m_dim=0;
	parcget=head;
}

Cparser_func_memory::~Cparser_func_memory()
{
	deletedata();
}
void Cparser_func_memory::set(double val,long pos,char *name)
{
	struct nod *parc;
	struct nod *aux,*p1;
	if(head==NULL)
	{
		head=new (struct nod);
		strcpy(head->name,name);
		head->data.set(val,pos);
		head->next=NULL;
		m_dim++;
		return;
	}
	if(strcmp(head->name,name)==0)
	{
		head->data.set(val,pos);
		return;
	}
	if(strcmp(head->name,name)>0)
	{
		aux=new (struct nod);
		strcpy(aux->name,name);
		aux->data.set(val,pos);
		aux->next=head;
		head=aux;
		m_dim++;
		return;
	}
	p1=head;
	parc=head;
	while(strcmp(parc->name,name)<=0)
	{
		p1=parc;
		parc=parc->next;
		if(parc==NULL) break;
	}
	if(parc!=NULL)
	{
		if(strcmp(p1->name,name)==0)
			p1->data.set(val,pos);
		else
		{
			aux=new (struct nod);
			strcpy_s(aux->name,name);
			aux->data.set(val,pos);
			aux->next=p1->next;
			p1->next=aux;
			m_dim++;
		}
	}
	else
	{
		if(strcmp(p1->name,name)==0)
			p1->data.set(val,pos);
		else
		{
			aux=new (struct nod);
			strcpy_s(aux->name,name);
			aux->data.set(val,pos);
			aux->next=NULL;
			p1->next=aux;
			m_dim++;
		}
	}
}
void Cparser_func_memory::deletedata()
{
	struct nod *aux,*parc;
	parc=head;
	while(parc!=NULL)
	{
		aux=parc;
		parc=parc->next;
		delete aux;
	}
	head=NULL;
	m_dim=0;
}

double Cparser_func_memory::get(long pos,char *name)
{
	struct nod *parc;
	parc=head;
	while(parc!=NULL && strcmp(parc->name,name)!=0)
	{
		parc=parc->next;
	}
	if(parc!=NULL) return (parc->data).get(pos);
	else return 0.0;
}

long Cparser_func_memory::getdim()
{
	return m_dim;
}

void Cparser_func_memory::display()
{
	struct nod *parc;
	parc=head;
	while(parc!=NULL)
	{
		cout<<"name="<<parc->name<<endl;
		parc->data.display();
		parc=parc->next;
		cout.flush();
	}
}

int Cparser_func_memory::getVal(double *val, char *name)
{
	if(parcget!=NULL)
	{
		strcpy(name,parcget->name);
		*val=(parcget->data).get(0);
		parcget=parcget->next;
		return 0;
	}
	else
	{
		name="\0";
		return -1;
	}
}


void Cparser_func_memory::setdim(char *name, long dim)
{
	struct nod *parc;
	struct nod *aux,*p1;
	if(head==NULL)
	{
		head=new (struct nod);
		strcpy_s(head->name,name);
		head->data.setdim(dim);
		head->next=NULL;
		m_dim++;
		return;
	}
	if(strcmp(head->name,name)==0)
	{
		head->data.setdim(dim);
		return;
	}
	if(strcmp(head->name,name)>0)
	{
		aux=new (struct nod);
		strcpy_s(aux->name,name);
		aux->data.setdim(dim);
		aux->next=head;
		head=aux;
		m_dim++;
		return;
	}
	p1=head;
	parc=head;
	while(strcmp(parc->name,name)<=0)
	{
		p1=parc;
		parc=parc->next;
		if(parc==NULL) break;
	}
	if(parc!=NULL)
	{
		if(strcmp(p1->name,name)==0)
			p1->data.setdim(dim);
		else
		{
			aux=new (struct nod);
			strcpy_s(aux->name,name);
			aux->data.setdim(dim);
			aux->next=p1->next;
			p1->next=aux;
			m_dim++;
		}
	}
	else
	{
		if(strcmp(p1->name,name)==0)
			p1->data.setdim(dim);
		else
		{
			aux=new (struct nod);
			strcpy_s(aux->name,name);
			aux->data.setdim(dim);
			aux->next=NULL;
			p1->next=aux;
			m_dim++;
		}
	}
}

void Cparser_func_memory::assign_memory(char *name, double *mem, long dim)
{
	struct nod *parc;
	struct nod *aux,*p1;
	if(head==NULL)
	{
		head=new (struct nod);
		strcpy(head->name,name);
		head->data.assign_memory(mem,dim);
		head->next=NULL;
		m_dim++;
		return;
	}
	if(strcmp(head->name,name)==0)
	{
		head->data.assign_memory(mem,dim);
		return;
	}
	if(strcmp(head->name,name)>0)
	{
		aux=new (struct nod);
		strcpy(aux->name,name);
		aux->data.assign_memory(mem,dim);
		aux->next=head;
		head=aux;
		m_dim++;
		return;
	}
	p1=head;
	parc=head;
	while(strcmp(parc->name,name)<=0)
	{
		p1=parc;
		parc=parc->next;
		if(parc==NULL) break;
	}
	if(parc!=NULL)
	{
		if(strcmp(p1->name,name)==0)
			p1->data.assign_memory(mem,dim);
		else
		{
			aux=new (struct nod);
			strcpy(aux->name,name);
			aux->data.assign_memory(mem,dim);
			aux->next=p1->next;
			p1->next=aux;
			m_dim++;
		}
	}
	else
	{
		if(strcmp(p1->name,name)==0)
			p1->data.assign_memory(mem,dim);
		else
		{
			aux=new (struct nod);
			strcpy(aux->name,name);
			aux->data.assign_memory(mem,dim);
			aux->next=NULL;
			p1->next=aux;
			m_dim++;
		}
	}
}

void Cparser_func_memory::resetGet()
{
	parcget=head;
}


void Cparser_func_memory::deletedata(char *name)
{
	struct nod *parc;
	struct nod *aux,*p1;
	if(head==NULL) return;
	if(strcmp(name,head->name)==0)
	{
		aux=head;
		head=head->next;
		delete aux;
		return;
	}
	parc=head->next;
	p1=head;
	while(parc!=NULL)
	{
		if(strcmp(parc->name,name)==0)
		{
			p1->next=parc->next;
			delete parc;
			return;
		}
		p1=parc;
		parc=parc->next;
	}
}

void Cparser_func_memory::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	if(ar.IsStoring())
	{

	}
	else
	{

	}
}
