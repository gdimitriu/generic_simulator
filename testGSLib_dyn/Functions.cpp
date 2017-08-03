// Functions.cpp : implementation file
//

#include "stdafx.h"
#include "Functions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFunctions dialog


CFunctions::CFunctions(CWnd* pParent /*=NULL*/)
	: CDialog(CFunctions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFunctions)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	dyn=NULL;
	func=NULL;
	spec=NULL;
	syst=NULL;
	tests=NULL;
	oldtests=NULL;
}


void CFunctions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFunctions)
	DDX_Control(pDX, IDC_tests, m_tests);
	DDX_Control(pDX, IDC_functions, m_functions);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFunctions, CDialog)
	//{{AFX_MSG_MAP(CFunctions)
	ON_BN_CLICKED(IDC_RUN, OnRun)
	ON_CBN_SELENDOK(IDC_functions, OnSelendokfunctions)
	ON_BN_CLICKED(IDC_funcinit, Onfuncinit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFunctions message handlers

void CFunctions::OnRun() 
{
	UpdateData(TRUE);
	int index=m_functions.GetCurSel();
	switch(index)
	{
	case 0: //dynamic
		dyn->run(&m_tests);	
		break;
	case 1: //functionality
		func->run(&m_tests);
		break;
	case 2: //specialf
		spec->run(&m_tests);
		break;
	case 3: //systems
		syst->run(&m_tests);
		break;
	case 4: //tests
		tests->run(&m_tests);
		break;
	case 5://oldtests
		oldtests->run(&m_tests);
		break;
	case CB_ERR:
		break;
	}
	UpdateData(FALSE);
}

void CFunctions::OnSelendokfunctions() 
{
	UpdateData(TRUE);
	m_tests.ResetContent();
	UpdateData(FALSE);
	int index=m_functions.GetCurSel();
	switch(index)
	{
	case 0: //dynamic
		dyn=new Cdynamic();
		dyn->SetFunc(&m_tests);
		break;
	case 1: //functionality
		func=new Cfunctionality();
		func->SetFunc(&m_tests);
		break;
	case 2: //specialf
		spec=new Cspecialf();
		spec->SetFunc(&m_tests);
		break;
	case 3: //systems
		syst=new CSystems();
		syst->SetFunc(&m_tests);
		break;
	case 4: //tests
		tests=new Ctests();
		tests->SetFunc(&m_tests);
		break;
	case 5://oldtests
		oldtests=new ColdTests();
		oldtests->SetFunc(&m_tests);
		break;
	case CB_ERR:
		break;
	}
	UpdateData(FALSE);
}

void CFunctions::OnCancel() 
{
	if(dyn!=NULL) delete dyn;
	if(func!=NULL) delete func;
	if(spec!=NULL) delete spec;
	if(syst!=NULL) delete syst;
	if(tests!=NULL) delete tests;
	if(oldtests!=NULL) delete oldtests;
	CDialog::OnCancel();
}

void CFunctions::Onfuncinit() 
{
	m_functions.ResetContent();
	m_tests.ResetContent();
	UpdateData(FALSE);
	m_functions.AddString(_T("dynamic"));
	m_functions.AddString(_T("functionality"));
	m_functions.AddString(_T("specialf"));
	m_functions.AddString(_T("systems"));
	m_functions.AddString(_T("tests"));
	m_functions.AddString(_T("oldtests"));
	UpdateData(FALSE);
}
