// GRepartition.h: interface for the CGRepartition class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the definition of a library of random distribution generator.
	
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

#if !defined(AFX_GREPARTITION_H__47B291BC_F925_4229_9025_EBEB259D9E52__INCLUDED_)
#define AFX_GREPARTITION_H__47B291BC_F925_4229_9025_EBEB259D9E52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afx.h>
#include <math.h>
#include <stdlib.h>
#include "stdafx.h"
#define precision 1e-12

using namespace std ;

class DllExport CGRepartition : public CObject
{
	DECLARE_SERIAL_DLL(CGRepartition)
public:
	virtual void Serialize(CArchive &ar);
	long RetIndex(double val);
	void SetGen(CString *var);
	void Set(long seed);
	double generate(void);
	CGRepartition();
	CGRepartition(CGRepartition *rep);
	virtual ~CGRepartition();
protected:
	void PutDisc(long n,double init,double step);
	void PutDisc(CString *a,CString *p);
	double Rdisc();
	double Rnorm(void);
	double Rnorm(double m,double sigma);
	double Rgamma(double alpha,double lambda,double niu);
	double Rgamma(double niu);
	double Rexp(double l);
	double Rexp_1();
	double gammaf_0_1(double niu);
	double gammaln(double xx);
	double gammainc(double a, double x);
	void gser(double *gamser, double a, double x, double *gln);
	void gcf(double *gammcf, double a, double x, double *gln);
	long m_Ndisc;
	double m_constant;
	double *m_a;
	double *m_p;
	double *m_t;
	double m_l;
	double m_niu;
	long m_type;
	//-1=constant
	//0=discret
	//1=gamma(0,1,a)
	//2=gamma(a,b,c)
	//3=norm(0,1)
	//4=norm(a,b)
	//5=exp(1)
	//6=exp(a)
};

#endif // !defined(AFX_GREPARTITION_H__47B291BC_F925_4229_9025_EBEB259D9E52__INCLUDED_)
