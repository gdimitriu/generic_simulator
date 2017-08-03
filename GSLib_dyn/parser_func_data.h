// parser_func_data.h: interface for the Cparser_func_data class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0
	2006 version 2.0

	This file is part of parser functions.
	This file contains the definition of multidimensional variable.
	
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
#if !defined(AFX_PARSER_FUNC_DATA_H__FBE7C726_4C21_4B3F_BAE9_9B6B86C002B7__INCLUDED_)
#define AFX_PARSER_FUNC_DATA_H__FBE7C726_4C21_4B3F_BAE9_9B6B86C002B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <iostream>
using namespace std ;
class Cparser_func_data  
{
private:
	struct nod 
	{
		double info;
		long pos;
		struct nod *next;
	};
public:
	void assign_memory(double *memory,long dim);
	void display();
	long getdim();
	void setdim(long dim);
	double get(long pos);
	Cparser_func_data();
	void deletedata();
	void set(double val,long pos);
	virtual ~Cparser_func_data();
private:
	bool m_type; //true for static
	double *m_data;
	struct nod *head;
	long m_dim;
protected:
	bool m_extern;
};

#endif // !defined(AFX_PARSER_FUNC_DATA_H__FBE7C726_4C21_4B3F_BAE9_9B6B86C002B7__INCLUDED_)
