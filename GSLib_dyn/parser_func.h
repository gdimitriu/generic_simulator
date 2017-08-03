// parser_func.h: interface for the parser_func class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0
	2006 version 2.0

	This file is part of Parser Functions.
	This file contains the definition of parser for functions.
	
    Parser Functions is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Parser Functions is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Parser Functions; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  
*/
#if !defined(AFX_PARSER_FUNC_H__13461D80_C4F7_4B2D_8163_7774087898F5__INCLUDED_)
#define AFX_PARSER_FUNC_H__13461D80_C4F7_4B2D_8163_7774087898F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include"parser_func_memory.h"
#define DELIMITATOR 1
#define VARIABILA 2
#define NUMAR 3
#define FUNCTION 4
#define VARIABILA_MD 5
using namespace std ;

class Cparser_func : public CObject 
{
	DECLARE_SERIAL(Cparser_func);
public:
	virtual void Serialize(CArchive& ar);
	void SetName(long name);
	int delvarfunc(char *dead);
	void reset_func();
	char * get_function();
	void assign_memory(Cparser_func_memory *mem);
	void delete_memory();
	void alocate_memory();
	void setdim(char *s,long dim);
	double get_var(char *var);
	double get_var(char *var,long pos);
	void unset_var(char *var);
	void unset_var(char *var,long pos);
	void set_var(char *var,double val);
	void set_var(char *var,double val,long pos);
	void empty_vars();
	Cparser_func();
	virtual ~Cparser_func();
	void set_function(char *func);
	int eval_func(double *rez);
	Cparser_func_memory *memory;
	char *function;
	long m_name;
protected:
	bool error;
	double eval_varmd(char *s);
	char * get_argument(char *work);
	char * get_argument_var(char *work);
	double eval_math(char *s);
	double find_var(char *s);
	long isdelim(char c);
	void serror(long error);
	void putback();
	void get_token(void);
	void atom(double *rez);
	void eval_func6(double *rez);
	void eval_func5(double *rez);
	void eval_func4(double *rez);
	void eval_func3(double *rez);
	void eval_func2(double *rez);
	void eval_func1(double *rez);
	char simb[80];
	char tip_simb;
	bool m_aloc;
	char *prog;
	double (*math_f[13])(double arg);
};

#endif // !defined(AFX_PARSER_FUNC_H__13461D80_C4F7_4B2D_8163_7774087898F5__INCLUDED_)
