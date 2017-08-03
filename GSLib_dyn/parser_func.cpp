// parser_func.cpp: implementation of the parser_func class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0
	2006 version 2.0

	This file is part of Parser Functions.
	This file contains the implementation of parser for functions.
	
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

#include "stdafx.h"
#include "parser_func.h"
#include <iostream>
#include<stdio.h>
IMPLEMENT_SERIAL(Cparser_func,CObject,1);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Cparser_func::Cparser_func()
{
	prog=NULL;
	function=NULL;
	math_f[0]=cos;
	math_f[1]=acos;
	math_f[2]=sin;
	math_f[3]=asin;
	math_f[4]=tan;
	math_f[5]=atan;
	math_f[6]=cosh;
	math_f[7]=sinh;
	math_f[8]=tanh;
	math_f[9]=exp;
	math_f[10]=log;
	math_f[11]=log10;
	math_f[12]=fabs;
	error=false;
	m_aloc=false;
	m_name=-1;
}

Cparser_func::~Cparser_func()
{
	if(prog!=NULL) free(function);
	if(m_aloc==true) delete memory;
}

int Cparser_func::eval_func(double *rez)
//input point
{
	get_token();
	if(!*simb)
	{
		serror(2);
		return -1;
	}
	eval_func1(rez);
	if(*simb) serror(0); //last simbol is null
	if(error==true) return -1;
	else return 0;
}

void Cparser_func::eval_func1(double *rez)
//processing a atribution
{
	char temp_simb[80],sseg_tip;
	
	if(tip_simb==VARIABILA)
	{
		//save the old simbol;
		strcpy(temp_simb,simb);
		sseg_tip=tip_simb;
		//computing the index of the variable
		//fanta=toupper(*simb)-'A';
		char simbol_name[10];
		strcpy(simbol_name,simb);
		get_token();
		if(*simb!='=')
		{
			putback();//return the curent segment
			//restore the old simbol without atributs
			strcpy(simb,temp_simb);
			tip_simb=sseg_tip;
		}
		else
		{
			get_token(); //get the next part of the expresion
			eval_func2(rez);
			memory->set(*rez,0,simbol_name);
			return;
		}
	}
	if(tip_simb==VARIABILA_MD)
	{
		char *prog_old;
		//save the old simbol;
		strcpy(temp_simb,simb);
		sseg_tip=tip_simb;
		//computing the index of the variable
		char simbol_name[10];
		strcpy(simbol_name,simb);
		char *argument;
		char *work;
		double pos;
		prog_old=prog;
		work=(char *)calloc(80,sizeof(char));
		argument=get_argument_var(work);
		eval_func(&pos);
		free(work);
		prog=argument;
		get_token();
		if(*simb!='=')
		{
			prog=prog_old;
			//restore the old simbol without atributs
			strcpy(simb,temp_simb);
			tip_simb=sseg_tip;
		}
		else
		{
			get_token(); //get the next part of the expresion
			eval_func2(rez);
			memory->set(*rez,(long)pos,simbol_name);
			return;
		}
	}
	eval_func2(rez);
}

void Cparser_func::eval_func2(double *rez)
//add or difference of two elements
{
	char op;
	double temp;
	
	eval_func3(rez);
	op=*simb;
	while(op=='+' || op=='-')
	{
		get_token();
		eval_func3(&temp);
		switch(op)
		{
		case '-':
			*rez=*rez-temp;
			break;
		case '+':
			*rez=*rez+temp;
			break;
		}
		op=*simb;
	}
}

void Cparser_func::eval_func3(double *rez)
//product or division of two elements
{
	char op;
	double temp;
	
	eval_func4(rez);
	while((op=*simb)=='*' || op=='/' || op=='%')
	{
		get_token();
		eval_func4(&temp);
		switch(op)
		{
		case '*':
			*rez=(*rez)*temp;
			break;
		case '/':
			*rez=(*rez)/temp;
			break;
		case '%':
			*rez=(long)*rez%(long)temp;
			break;
		}
	}
}

void Cparser_func::eval_func4(double *rez)
//process an exponent
{
	double temp;
	eval_func5(rez);
	if(*simb=='^')
	{
		get_token();
		eval_func4(&temp);
		*rez=pow(*rez,temp);
	}
}

void Cparser_func::eval_func5(double *rez)
//eval + or - unary
{
	char op;
	op=0;
	if((tip_simb==DELIMITATOR) && *simb=='+' || *simb=='-')
	{
		op=*simb;
		get_token();
	}
	eval_func6(rez);
	if(op=='-') *rez=-(*rez);
}
 
void Cparser_func::eval_func6(double *rez)
//process parantheses expresion
{
	if(*simb=='(')
	{
		get_token();
		eval_func2(rez);
		if(*simb!=')')
			serror(1);
		get_token();
	}
	else atom(rez);
}

double Cparser_func::eval_math(char *s)
//evaluate a mathematical predefinite function
{
	double rez;
	int findex;
	if(strcmp(s,"cos")==0) //we have cos
		 findex=0;
	else if(strcmp(s,"acos")==0) //we have arccos
		findex=1;
	else if(strcmp(s,"sin")==0) //we have sin
		findex=2;
	else if(strcmp(s,"asin")==0) //we have arcsin
		findex=3;
	else if(strcmp(s,"tan")==0) //we have tangent
		findex=4;
	else if(strcmp(s,"atan")==0) //we have arctangent
		findex=5;
	else if(strcmp(s,"cosh")==0) //we have hiperbolic cosinus 
		findex=6;
	else if(strcmp(s,"sinh")==0) //we have hyperbolic sinus 
		findex=7;
	else if(strcmp(s,"tanh")==0) //we have hyperbolic tangent
		findex=8;
	else if(strcmp(s,"exp")==0) //we have exponential
		findex=9;
	else if(strcmp(s,"log")==0) //we have natural logarithm
		findex=10;
	else if(strcmp(s,"log10")==0) //we have 10 base logarithm
		findex=11;
	else if(strcmp(s,"fabs")==0) //we have absolute value
		findex=12;
	else findex=-1;
	//compute the argument of the function in rez
	char *argument;
	char *work;
	work=(char *)calloc(80,sizeof(char));
	argument=get_argument(work);
	eval_func(&rez);
	free(work);
	prog=argument;
	if(findex==-1)
		return 0.0;
	else return math_f[findex](rez);
}

double Cparser_func::eval_varmd(char *s)
{
	char *argument;
	char *work;
	double pos;
	char simbol_name[10];
	strcpy(simbol_name,simb);
	work=(char *)calloc(80,sizeof(char));
	argument=get_argument_var(work);
	eval_func(&pos);
	free(work);
	prog=argument;
	return memory->get((long)pos,simbol_name);
}
void Cparser_func::atom(double *rez)
//read the value of the number or a variable
{
	switch(tip_simb)
	{
	case VARIABILA:
		*rez=find_var(simb);
		get_token();
		return;
	case NUMAR:
		*rez=atof(simb);
		get_token();
		return;
	case FUNCTION:
		*rez=eval_math(simb);
		get_token();
		return;
	case VARIABILA_MD:
		*rez=eval_varmd(simb);
		get_token();
		return;
	default:
		serror(0);
	}
}

void Cparser_func::get_token()
//return the next simbol
{
	char *temp;
	tip_simb=0;
	temp=simb;
	*temp='\0';

	if(!prog) return; //end of expresion
	while(isspace(*prog)) ++prog;
	if(strchr("+-*/%^=()[]",*prog))
	{
		tip_simb=DELIMITATOR;
		*temp++=*prog++;
	}
	else if(isalpha(*prog) && *(prog+1)=='[')
	{
		while(!isdelim(*prog)) *temp++=*prog++;
		tip_simb=VARIABILA_MD;
	}
	else if(isalpha(*prog) && isalpha(*(prog+1)))
	{
		while(!isdelim(*prog)) *temp++=*prog++;
		if(*prog=='(')	tip_simb=FUNCTION;
		else if(*prog=='[') tip_simb=VARIABILA_MD;
		else tip_simb=VARIABILA;
	}
	else if(isalpha(*prog))
	{
		while(!isdelim(*prog)) *temp++=*prog++;
		if(*prog=='(')	tip_simb=FUNCTION;
		else if(*prog=='[') tip_simb=VARIABILA_MD;
		else tip_simb=VARIABILA;
	}
	else if(isdigit(*prog))
	{
		while(!isdelim(*prog)) *temp++=*prog++;
		tip_simb=NUMAR;
	}
	*temp='\0';
}

void Cparser_func::putback()
//return one simbol from the input flux
{
	char *s;
	s=simb;
	for(;*s;s++) prog--;
}

void Cparser_func::serror(long error)
//print a sintax error
{
	static char *e[]={
		"Sintax error",
		"Unbalance bracket",
		"Not an expresion"
	};
	cout<<e[error]<<endl;
	error=true;
}

double Cparser_func::find_var(char *s)
//return the value of a variable
{
	if(!isalpha(*s))
	{
		serror(1);
		return 0.0;
	}
	return memory->get(0,s);
}

long Cparser_func::isdelim(char c)
//return 1 if c is a delimitator
{
	if(strchr(" +-/*%^=()[]",c) || c==9 || c=='\r' || c==0)
		return 1;
	return 0;
}

void Cparser_func::empty_vars()
//empty the variable memory
{
	memory->deletedata();
}

void Cparser_func::set_var(char *var, double val)
//set a variable to a value
{
	memory->set(val,0,var);
}

void Cparser_func::set_var(char *var, double val,long pos)
//set a multidimensional variable to a value
{
	memory->set(val,pos,var);
}

void Cparser_func::unset_var(char *var)
//unset a variable
{
	memory->set(0,0,var);
}

void Cparser_func::unset_var(char *var,long pos)
//unset a multidimensional variable
{
	memory->set(0.0,pos,var);
}

double Cparser_func::get_var(char *var)
//get a variable
{
	return memory->get(0,var);
}

double Cparser_func::get_var(char *var,long pos)
//get a multidimensional variable
{
	return memory->get(pos,var);
}

void Cparser_func::set_function(char *func)
//set the function to the system
{
	if(function!=NULL) free(function);
	function=(char *)calloc(strlen(func)+1,sizeof(char));
	strcpy(function,func);
	prog=function;
}

char * Cparser_func::get_argument(char *work)
//get the argument of a predefined function
{
	char *temp;
	prog++;
	long i=0;
	long parantheses=1;
	while(parantheses!=0)
	{
		if(*prog=='(') parantheses++;
		if(*prog==')') parantheses--;
		if(parantheses==0) break;
		work[i]=*prog;
		i++;
		prog++;
	}
	work[i]='\0';
	prog++;
	temp=prog;
	prog=work;
	return temp;
}

char * Cparser_func::get_argument_var(char *work)
//get the argument of a multidimensional variable
{
	char *temp;
	prog++;
	long i=0;
	long parantheses=1;
	while(parantheses!=0)
	{
		if(*prog=='[') parantheses++;
		if(*prog==']') parantheses--;
		if(parantheses==0) break;
		work[i]=*prog;
		i++;
		prog++;
	}
	work[i]='\0';
	prog++;
	temp=prog;
	prog=work;
	return temp;
}

void Cparser_func::setdim(char *s, long dim)
{
	memory->setdim(s,dim);
}

void Cparser_func::alocate_memory()
{
	memory=new Cparser_func_memory();
	m_aloc=true;
}

void Cparser_func::delete_memory()
{
	memory->deletedata();
	delete memory;
	memory=NULL;
	m_aloc=false;
}

void Cparser_func::assign_memory(Cparser_func_memory *mem)
{
	memory=mem;
	m_aloc=false;
}

char * Cparser_func::get_function()
{
	return function;
}

void Cparser_func::reset_func()
{
	prog=function;
}

int Cparser_func::delvarfunc(char *dead)
{
	CString func(function);
	int index,index1,index2;
	int i,j,l;
	index=func.Find(dead,0);
	if(index==-1) return 1;
	CString tfunc;
	l=0;
	index2=index;
	//left operations
	while(index2>l && func[index2]!='-' && func[index2]!='+') index2--;
	for(i=l,j=0;i<index2;i++)
		tfunc.Insert(j,func[i]);
	while(index!=-1)
	{
		index=index+strlen(dead)+1;
		//find dimension
		while(func[index]!=']') index++;
		index++;
		index1=index;
		//right operations
		if(index1<func.GetLength()) while(index1<=func.GetLength() && func[index1]!='-' && func[index1]!='+')
		{
			index1++;
			if(func.GetLength()<index1) break;
		}
		if(func.GetLength()>index1) if(tfunc.GetLength()==0 && func[index1]!='-') index1++;
		index=func.Find(dead,index1);
		l=index1;
		//left operations
		index2=index;
		while(index2>l && func[index2]!='-' && func[index2]!='+')
		{
			index2--;
			if(index2<0) break;
		}
		for(i=l,j=0;i<index2;i++)
			tfunc.Insert(j,func[i]);
	}
	j=tfunc.GetLength();
	for(i=index1;i<func.GetLength();i++,j++)
		tfunc.Insert(j,func[i]);
	tfunc.FreeExtra();
	free(function);
	if(tfunc.GetLength()==0)
	{
		tfunc.Empty();
		tfunc.Format("%f",0.0);
	}
	function=(char *)calloc(tfunc.GetLength()+1,sizeof(char));
	LPSTR tmp=tfunc.GetBuffer(tfunc.GetLength());
	strcpy(function,tmp);
	return 0;
}

void Cparser_func::SetName(long name)
{
	m_name=name;
}

void Cparser_func::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	CString *a;
	int temp;
	if(ar.IsStoring())
	{
		a=new CString(function);
		ar<<*a;
		ar<<m_aloc;
		ar<<m_name;
		ar<<error;
		if(m_aloc==true)
			ar<<memory;
	}
	else
	{
		a=new CString();
		ar>>*a;
		function=(char *)calloc(a->GetLength()+1,sizeof(char));
		LPSTR tmp=a->GetBuffer(a->GetLength());
		strcpy(function,tmp);
		ar>>temp;
		m_aloc=(bool)temp;
		ar>>m_name;
		ar>>temp;
		error=(bool)temp;
		if(m_aloc==true)
		{
			CObject *otmp;
			ar>>otmp;
			memory=(Cparser_func_memory *)otmp;
		}
	}
}
