// parser_func_memory.h: interface for the Cparser_func_memory class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0
	2006 version 2.0

	This parser functions is a modified version of the parser from Schild "C The
	Complete Reference" Copyright 1995 McGraw-Hill Cook Company International.

	This file is part of Parser Functions.
	This file contains the definition of memory variables.
	
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
#if !defined(AFX_PARSER_FUNC_MEMORY_H__D30EB65B_2D12_4D40_9834_FB1A441CE8AA__INCLUDED_)
#define AFX_PARSER_FUNC_MEMORY_H__D30EB65B_2D12_4D40_9834_FB1A441CE8AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include"parser_func_data.h"
using namespace std ;
class Cparser_func_memory : public CObject 
{
private:
	struct nod 
	{
		Cparser_func_data data;
		char name[10];
		struct nod *next;
	};
	DECLARE_SERIAL(Cparser_func_memory);
public:
	virtual void Serialize(CArchive& ar);
	void deletedata(char *name);
	int getVal(double *val,char *name);
	void resetGet();
	void assign_memory(char *name,double *mem,long dim);
	void setdim(char *name,long dim);
	void display(void);
	long getdim();
	double get(long pos,char *name);
	void deletedata();
	void set(double val,long pos,char *name);
	Cparser_func_memory();
	virtual ~Cparser_func_memory();
private:
	struct nod *head;
	struct nod *parcget;
	long m_dim;
};

#endif // !defined(AFX_PARSER_FUNC_MEMORY_H__D30EB65B_2D12_4D40_9834_FB1A441CE8AA__INCLUDED_)
