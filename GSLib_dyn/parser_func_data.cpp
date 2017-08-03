// parser_func_data.cpp: implementation of the Cparser_func_data class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0
	2006 version 2.0

	This file is part of parser functions.
	This file contains the implementation multidimensional varible.
	
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
#include "parser_func_data.h"
#include <stdlib.h>
#include<iostream>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cparser_func_data::Cparser_func_data()
{

	head=NULL;
	m_data=NULL;
	m_type=false;
	m_extern=false;
	m_dim=0;
}

Cparser_func_data::~Cparser_func_data()
{
	deletedata();
}
void Cparser_func_data::set(double val,long pos)
{
	if(m_type==false)
	{
		struct nod *parc;
		struct nod *aux,*p1;
		aux=new (struct nod);
		aux->info=val;
		aux->pos=pos;
		aux->next=NULL;
		if(head==NULL)
		{
			head=aux;
			m_dim++;
			return;
		}
		if(head->pos==pos)
		{
			head->info=val;
			delete aux;
			return;
		}
		if(head->pos>pos)
		{
			aux->next=head;
			head=aux;
			m_dim++;
			return;
		}
		p1=head;
		parc=head;
		while(parc->pos<=pos)
		{
			p1=parc;
			parc=parc->next;
			if(parc==NULL) break;
		}
		if(parc!=NULL)
		{
			if(p1->pos==pos)
			{
				p1->info=val;
				delete aux;
			}
			else
			{
				aux->next=p1->next;
				p1->next=aux;
				m_dim++;
			}
		}
		else
		{
			if(p1->pos==pos)
			{
				p1->info=val;
				delete aux;
			}
			else
			{
				p1->next=aux;
				m_dim++;
			}
		}
	}
	else
	{
		if(pos>=m_dim)
		{
			cout<<"Error overhead at variable";
			return;
		}
		else m_data[pos]=val;
	}
}
void Cparser_func_data::deletedata()
{
	if(m_type==false)
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
	else
	{
		if(m_extern==false)
		{
			free(m_data);
			m_dim=0;
		}
	}
}

double Cparser_func_data::get(long pos)
{
	if(m_type==false)
	{
		struct nod *parc;
		parc=head;
		while(parc!=NULL && (parc->pos!=pos))
		{
			parc=parc->next;
		}
		if(parc!=NULL) return parc->info;
		else return 0.0;
	}
	else
	{
		if(pos>=m_dim)
		{
			cout<<"Error overhead at variable";
			return 0.0;
		}
		else return m_data[pos];
	}
}

void Cparser_func_data::setdim(long dim)
{
	m_dim=dim;
	m_type=true;
	m_extern=false;
	m_data=(double *)calloc(dim,sizeof(double));
}

long Cparser_func_data::getdim()
{
	return m_dim;
}

void Cparser_func_data::display()
{
	struct nod *parc;
	if(m_type==false)
	{
		parc=head;
		while(parc!=NULL)
		{
			cout<<"pos="<<parc->pos<<endl;
			cout<<"info="<<parc->info<<endl;
			cout.flush();
			parc=parc->next;
		}
	}
	else
	{
		for(long i=0;i<m_dim;i++)
		{
			cout<<"mem["<<i<<"]="<<m_data[i]<<endl;
			cout.flush();
		}
	}
}

void Cparser_func_data::assign_memory(double *memory, long dim)
{
	m_dim=dim;
	m_data=memory;
	m_type=true;
	m_extern=true;
}
