// Processor.cpp: implementation of the CProcessor class.
//
//////////////////////////////////////////////////////////////////////
/*
	Copyright 2005 Gabriel Dimitriu

	This file is part of Generic Simulator.
	This file contains the implementation of a Processor.
	
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
#include "Processor.h"
#include <iostream>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
IMPLEMENT_SERIAL(CProcessor,CGProcessor,1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProcessor::CProcessor() : CGProcessor()
{

}

CProcessor::~CProcessor()
{
	
}

CProcessor::CProcessor(CObject *parent,long val,CGTransition *generator) : CGProcessor(parent,val,generator,true)
{

}

CProcessor::CProcessor(long val,CGTransition *generator) : CGProcessor(NULL,val,generator,true)
{

}

CProcessor::CProcessor(CObject *parent,long val,CGTransition *generator,bool type) : CGProcessor(parent,val,generator,type)
{

}

CProcessor::CProcessor(long val,CGTransition *generator,bool type) : CGProcessor(NULL,val,generator,type)
{

}

void CProcessor::Serialize(CArchive &ar)
{
	CGProcessor::Serialize(ar);
}
