// GRepartition.cpp: implementation of the CGRepartition class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright Gabriel Dimitriu
	2005 version 1.0
	2006 version 2.0

	This file is part of Generic Simulator.
	This file contains the implementation of a library of random distribution
	generator.
	
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
#include <iostream>
#include "stdafx.h"
#include "GRepartition.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
IMPLEMENT_SERIAL(CGRepartition,CObject,1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGRepartition::CGRepartition()
{
	m_a=NULL;
	m_p=NULL;
	m_t=NULL;
	m_type=0;
	m_Ndisc=0;
}

CGRepartition::CGRepartition(CGRepartition *rep)
{
	m_niu=rep->m_niu;
	m_Ndisc=rep->m_Ndisc;
	m_constant=rep->m_constant;
	m_l=rep->m_l;
	m_type=rep->m_type;
	if(m_Ndisc!=0)
	{
		m_a=(double *)calloc(m_Ndisc,sizeof(double));
		m_p=(double *)calloc(m_Ndisc,sizeof(double));
		m_t=(double *)calloc(m_Ndisc,sizeof(double));
		memcpy(m_a,rep->m_a,m_Ndisc*sizeof(double));
		memcpy(m_p,rep->m_p,m_Ndisc*sizeof(double));
		memcpy(m_t,rep->m_t,m_Ndisc*sizeof(double));
	}
}

CGRepartition::~CGRepartition()
{
	if(m_a!=NULL) free(m_a);
	if(m_p!=NULL) free(m_p);
	if(m_t!=NULL) free(m_t);
}

void CGRepartition::Set(long seed)
{
	srand( (unsigned)time( NULL )+seed );
}

double CGRepartition::Rexp_1()
{
	long N,k;
	double u1,u0,u;
	N=0;
	do
	{
		k=1;
		u=(double)rand()/(double)RAND_MAX;
		u1=(double)rand()/(double)RAND_MAX;
		u0=u;
		while(u0>u1 || fabs(u0-u1)<precision)
		{
			k++;
			u0=u1;
			u1=(double)rand()/(double)RAND_MAX;
		}
		if(k%2==0) N++;
	}
	while(k%2==0);
	return N+u;
}

double CGRepartition::Rexp(double l)
{
	return Rexp_1()/l;
}

double CGRepartition::Rgamma(double niu)
{
	if(niu<1)
	{
		double p1=gammainc(1.0,niu)/gammaln(niu);
		double u=rand()/(double)RAND_MAX;
		double z1,z0,z;
		int k;
		if(u<p1 || fabs(u-p1)<precision)
		{
			do
			{
				u=rand()/(double)RAND_MAX;
				z0=pow(u,1/niu);
				z1=rand()/(double)RAND_MAX;
				k=1;
				z=z0;
				while(z0>=z1)
				{
					z0=z1;
					z=rand()/(double)RAND_MAX;
					k++;
				}
			}
			while(k%2==0);
			return z;
		}
		else
		{
			do
			{
				u=rand()/(double)RAND_MAX;
				z=pow(u,1/(1-niu));
				z0=Rexp_1()+1;
			}
			while(z0>z || fabs(z0-z)<precision);
			return z0;
		}
	}
	else
	{
		double y,u1,u,t;
		do
		{
			do
			{
				u=rand()/(double)RAND_MAX;
				t=sqrt(2*niu-1)*tan(asin(1)*2*(u-0.5));
				y=niu-1+t;
			}
			while(y<0 || fabs(y)<precision);
			u1=rand()/(double)RAND_MAX;
		}
		while(u1>exp((niu-1)*log(y/(niu-1)))-t+log(1+t*t/(2*niu-1)));
		return y;
	}
}

double CGRepartition::gammaln(double xx)
{
	double x,y,tmp,ser;
	double coef[6]={76.18009172947146,-86.50532032941677,24.01409824083091,-1.231739572450155,0.120865097386179e-2,-0.5395239384953e-5};
	int j;
	y=x=xx;
	tmp=x+5.5;
	tmp-=(x+0.5)*log(tmp);
	ser=1.00000000190015;
	for(j=0;j<=5;j++) ser+=coef[j]/++y;
	return exp(-tmp+log(2.5066282746310005*ser/x));
}

double CGRepartition::gammaf_0_1(double niu)
{
	double h=1/1000.0;
	double suma=h*pow(1.0,niu-1.0)*exp(-1.0)/3.0;
	for(int i=1;i<1000;i++) suma+=2*(1.0+i%2)*h*pow(i*h,niu-1)*exp(-i*h)/3.0;
	return suma;
}

double CGRepartition::Rgamma(double alpha, double lambda, double niu)
{
	return alpha+Rgamma(niu)/lambda;
}

double CGRepartition::Rnorm(double m, double sigma)
{
	return m+sigma*Rnorm();
}

double CGRepartition::Rnorm()
{
	double u,y;
	do
	{
		u=rand()/(double)RAND_MAX;
		y=Rexp_1();
	}
	while(u>exp(-y*y/2+y-0.5));
	u=rand()/(double)RAND_MAX;
	if(u<0.5) return -y;
	else return y;
}

#define ITMAX 100
#define EPS 3.0e-7
#define FPMIN 1.0e-30

void CGRepartition::gcf(double *gammcf, double a, double x, double *gln)
{
	int i;
	double an,b,c,d,del,h;

	*gln=gammaln(a);
	b=x+1.0-a;
	c=1.0/FPMIN;
	d=1.0/b;
	h=d;
	for (i=1;i<=ITMAX;i++) {
		an = -i*(i-a);
		b += 2.0;
		d=an*d+b;
		if (fabs(d) < FPMIN) d=FPMIN;
		c=b+an/c;
		if (fabs(c) < FPMIN) c=FPMIN;
		d=1.0/d;
		del=d*c;
		h *= del;
		if (fabs(del-1.0) < EPS) break;
	}
	*gammcf=exp(-x+a*log(x)-(*gln))*h;
}

void CGRepartition::gser(double *gamser, double a, double x, double *gln)
{
	long n;
	double sum,del,ap;

	*gln=gammaln(a);
	if (x < 0.0 || fabs(x)<precision) {
		*gamser=0.0;
		return;
	} else {
		ap=a;
		del=sum=1.0/a;
		for (n=1;n<=ITMAX;n++) {
			++ap;
			del *= x/ap;
			sum += del;
			if (fabs(del) < fabs(sum)*EPS) {
				*gamser=sum*exp(-x+a*log(x)-(*gln));
				return;
			}
		}
		return;
	}
}

double CGRepartition::gammainc(double a, double x)
{
	double gamser,gammcf,gln;

	if (x < (a+1.0)) {
		gser(&gamser,a,x,&gln);
		return gamser;
	} else {
		gcf(&gammcf,a,x,&gln);
		return 1.0-gammcf;
	}
}
#undef ITMAX
#undef EPS
#undef FPMIN
//put discret coeficients
void CGRepartition::PutDisc(CString *a,CString *p)
{
	LPTSTR wstr;
	TCHAR wch;
	CString sworka,sworkp;
	int dim;
	int i,N,ja,jp;
	dim=a->GetLength();
	N=0;
	for(i=0;i<dim;i++)
		if(a->GetAt(i)==',') N++;
	N++;
	m_a=(double *)calloc(N,sizeof(double));
	m_p=(double *)calloc(N,sizeof(double));
	sworka.Empty();
	sworkp.Empty();
	ja=0;
	jp=0;
	dim=a->GetLength();
	for(i=0;i<dim;i++)
	{
		wch=a->GetAt(i);
		if(wch!=',') sworka.Insert(555,wch);
		else
		{
			wstr=sworka.GetBuffer(100);
			m_a[ja]=atof(wstr);
			sworka.ReleaseBuffer();
			ja++;
			sworka.Empty();
		}
	}
	wstr=sworka.GetBuffer(100);
	m_a[ja]=atof(wstr);
	sworka.ReleaseBuffer();
	dim=p->GetLength();
	for(i=0;i<dim;i++)
	{
		wch=p->GetAt(i);
		if(wch!=',') sworkp.Insert(555,wch);
		else
		{
			wstr=sworkp.GetBuffer(100);
			m_p[jp]=atof(wstr);
			sworkp.ReleaseBuffer();
			jp++;
			sworkp.Empty();
		}
	}
	wstr=sworkp.GetBuffer(100);
	m_p[jp]=atof(wstr);
	sworkp.ReleaseBuffer();
	m_Ndisc=N;
	m_t=(double *)calloc(N,sizeof(double));
	m_t[0]=m_p[0];
	for(i=1;i<N;i++) m_t[i]=m_t[i-1]+m_p[i];
}

double CGRepartition::Rdisc()
{
	double u=rand()/(double)RAND_MAX;
	int i=0;
	while(u>m_t[i]) i=i+1;
	return m_a[i];
}

double CGRepartition::generate()
{
	switch(m_type)
	{
	case -1:
		return m_constant;
	case 0:
		return Rdisc();
	case 1:
		return Rgamma(m_niu);
	case 2:
		return Rgamma(m_a[0],m_a[1],m_niu);
	case 3:
		return Rnorm();
	case 4:
		return Rnorm(m_a[0],m_a[1]);
	case 5:
		return Rexp_1();
	case 6:
		return Rexp(m_l);
	default:
		return 0.0;
	}
}


void CGRepartition::SetGen(CString *var)
{
//
//set the generator
//
	long N=var->GetLength();
	long i;
	CString ctemp;
	CString *a;
	LPTSTR wstr;
	switch(var->GetAt(0))
	{
	case 'D':
		m_type=0;
		if(var->GetAt(1)==':')
		{
			a=new CString[2];
			for(i=2;var->GetAt(i)!=';' && i<N;i++)
				a[0].Insert(555,var->GetAt(i));
			i++;
			for(;i<N;i++)
				a[1].Insert(555,var->GetAt(i));
			PutDisc(&a[0],&a[1]);
			delete[] a;
		}
		else if(var->GetAt(1)!='I')
		{
			double init,step;
			long n,j;
			char str[10];
			for(j=0;j<10;j++) str[j]='\0';
			j=0;
			for(i=3;var->GetAt(i)!=';';i++)
			{
				str[j]=var->GetAt(i);
				j++;
			}
			n=atol(str);
			for(j=0;j<10;j++) str[j]='\0';
			j=0;
			for(;var->GetAt(i)!=';';i++)
			{
				str[j]=var->GetAt(i);
				j++;
			}
			init=atof(str);
			for(j=0;j<10;j++) str[j]='\0';
			j=0;
			for(;i<N;i++)
			{
				str[j]=var->GetAt(i);
				j++;
			}
			step=atof(str);
			PutDisc(n,init,step);
		}
		break;
	case 'E':
		if(N==1) m_type=5;
		else
		{
			m_type=6;
			ctemp.Empty();
			for(i=2;i<N;i++) ctemp.Insert(555,var->GetAt(i));
			wstr=ctemp.GetBuffer(100);
			m_l=atof(wstr);
			ctemp.ReleaseBuffer();
			ctemp.Empty();
		}
		break;
	case 'N':
		if(N==1) m_type=3;
		else
		{
			m_type=4;
			m_a=(double *)calloc(2,sizeof(double));
			ctemp.Empty();
			for(i=2;var->GetAt(i)!=';' && i<N;i++)
				ctemp.Insert(555,var->GetAt(i));
			wstr=ctemp.GetBuffer(100);
			m_a[0]=atof(wstr);
			ctemp.ReleaseBuffer();
			ctemp.Empty();
			i++;
			for(;i<N;i++)
				ctemp.Insert(555,var->GetAt(i));
			wstr=ctemp.GetBuffer(100);
			m_a[1]=atof(wstr);
			ctemp.ReleaseBuffer();
			ctemp.Empty();
		}
		break;
	case 'G':
		ctemp.Empty();
		for(i=2;var->GetAt(i)!=';' && i<N;i++)
		ctemp.Insert(555,var->GetAt(i));
		wstr=ctemp.GetBuffer(100);
		m_niu=atof(wstr);
		ctemp.ReleaseBuffer();
		ctemp.Empty();
		if(i==N) m_type=1;
		else
		{
			m_type=2;
			m_a=(double *)calloc(2,sizeof(double));
			i++;
			for(;var->GetAt(i)!=';' && i<N;i++)
			ctemp.Insert(555,var->GetAt(i));
			wstr=ctemp.GetBuffer(100);
			m_a[0]=atof(wstr);
			ctemp.ReleaseBuffer();
			ctemp.Empty();
			i++;
			for(;i<N;i++)
			ctemp.Insert(555,var->GetAt(i));
			wstr=ctemp.GetBuffer(100);
			m_a[1]=atof(wstr);
			ctemp.ReleaseBuffer();
			ctemp.Empty();
		}
		break;
	default:
		m_type=-1;
		wstr=var->GetBuffer(100);
		m_constant=atof(wstr);
		var->ReleaseBuffer();
		break;
	}
}

void CGRepartition::PutDisc(long n,double init,double step)
{
	long i;
	m_a=(double *)calloc(n,sizeof(double));
	m_p=(double *)calloc(n,sizeof(double));
	m_Ndisc=n;
	m_t=(double *)calloc(n,sizeof(double));
	for(i=0;i<n;i++)
	{
		m_a[i]=init+step*i;
		m_p[i]=1.0/n;
	}
	m_t[0]=m_p[0];
	for(i=1;i<n;i++) m_t[i]=m_t[i-1]+m_p[i];
}

long CGRepartition::RetIndex(double val)
{
//
//return the relative index of the value in the repartition
//
	long i;
	if(m_type==0)
	{
		for(i=0;i<m_Ndisc;i++) 
			if(fabs(val-m_a[i])<precision) return i;
	}
	return 0;
}

void CGRepartition::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	long i;
	if(ar.IsStoring())
	{
		ar<<m_constant;
		ar<<m_l;
		ar<<m_Ndisc;
		ar<<m_type;
		ar<<m_niu;
		switch(m_type)
		{
			case 0:
				for(i=0;i<m_Ndisc;i++)
				{
					ar<<m_a[i];
					ar<<m_p[i];
					ar<<m_t[i];
				}
				break;
			case 3:
				ar<<m_a[0];
				ar<<m_a[1];
				break;
		}
	}
	else
	{
		ar>>m_constant;
		ar>>m_l;
		ar>>m_Ndisc;
		ar>>m_type;
		ar>>m_niu;
		switch(m_type)
		{
			case 0://discret
				m_a=(double *)calloc(m_Ndisc,sizeof(double));
				m_p=(double *)calloc(m_Ndisc,sizeof(double));
				m_t=(double *)calloc(m_Ndisc,sizeof(double));
				for(i=0;i<m_Ndisc;i++)
				{
					ar>>m_a[i];
					ar>>m_p[i];
					ar>>m_t[i];
				}
				break;
			case 3:
				m_a=(double *)calloc(2,sizeof(double));
				ar>>m_a[0];
				ar>>m_a[1];
				break;
		}
	}
}
