# Microsoft Developer Studio Project File - Name="GSLib_dyn" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=GSLib_dyn - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GSLib_dyn.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GSLib_dyn.mak" CFG="GSLib_dyn - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GSLib_dyn - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "GSLib_dyn - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GSLib_dyn - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "e:\my-data\work\projects\generic_simulator\Lib\Release"
# PROP Intermediate_Dir "e:\my-data\work\projects\generic_simulator\Lib\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /D "_GSLIB" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "GSLib_dyn - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "e:\my-data\work\projects\generic_simulator\Lib\Debug"
# PROP Intermediate_Dir "e:\my-data\work\projects\generic_simulator\Lib\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_GSLIB" /D "_AFXEXT" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL" /d "_AFXEXT" /d "_GSLIB"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /map /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "GSLib_dyn - Win32 Release"
# Name "GSLib_dyn - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\element.cpp
# End Source File
# Begin Source File

SOURCE=.\GBus.cpp
# End Source File
# Begin Source File

SOURCE=.\GCElem.cpp
# End Source File
# Begin Source File

SOURCE=.\GCoordinator.cpp
# End Source File
# Begin Source File

SOURCE=.\GCQueue.cpp
# End Source File
# Begin Source File

SOURCE=.\GData.cpp
# End Source File
# Begin Source File

SOURCE=.\GDistributionBus.cpp
# End Source File
# Begin Source File

SOURCE=.\GDistributionQ.cpp
# End Source File
# Begin Source File

SOURCE=.\GDistributionSecv.cpp
# End Source File
# Begin Source File

SOURCE=.\GInput.cpp
# End Source File
# Begin Source File

SOURCE=.\GMesure.cpp
# End Source File
# Begin Source File

SOURCE=.\GNetworkS.cpp
# End Source File
# Begin Source File

SOURCE=.\GOutput.cpp
# End Source File
# Begin Source File

SOURCE=.\GProcessor.cpp
# End Source File
# Begin Source File

SOURCE=.\GProcessorS.cpp
# End Source File
# Begin Source File

SOURCE=.\GRepartition.cpp
# End Source File
# Begin Source File

SOURCE=.\GSLib_dyn.cpp
# End Source File
# Begin Source File

SOURCE=.\GSLib_dyn.def
# End Source File
# Begin Source File

SOURCE=.\GSLib_dyn.odl
# End Source File
# Begin Source File

SOURCE=.\GSLib_dyn.rc
# End Source File
# Begin Source File

SOURCE=.\GSum.cpp
# End Source File
# Begin Source File

SOURCE=.\GTransition.cpp
# End Source File
# Begin Source File

SOURCE=.\GTransitionS.cpp
# End Source File
# Begin Source File

SOURCE=.\GWire.cpp
# End Source File
# Begin Source File

SOURCE=.\Input.cpp
# End Source File
# Begin Source File

SOURCE=.\NetworkS.cpp
# End Source File
# Begin Source File

SOURCE=.\Output.cpp
# End Source File
# Begin Source File

SOURCE=.\parser_func.cpp
# End Source File
# Begin Source File

SOURCE=.\parser_func_data.cpp
# End Source File
# Begin Source File

SOURCE=.\parser_func_memory.cpp
# End Source File
# Begin Source File

SOURCE=.\Processor.cpp
# End Source File
# Begin Source File

SOURCE=.\Queues.cpp
# End Source File
# Begin Source File

SOURCE=.\SCoordinator.cpp
# End Source File
# Begin Source File

SOURCE=.\SDotP.cpp
# End Source File
# Begin Source File

SOURCE=.\SGain.cpp
# End Source File
# Begin Source File

SOURCE=.\SInputCoordinator.cpp
# End Source File
# Begin Source File

SOURCE=.\SInputPartModification.cpp
# End Source File
# Begin Source File

SOURCE=.\SMult.cpp
# End Source File
# Begin Source File

SOURCE=.\SNorm.cpp
# End Source File
# Begin Source File

SOURCE=.\SProcessor.cpp
# End Source File
# Begin Source File

SOURCE=.\SQueue.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\STLineSD.cpp
# End Source File
# Begin Source File

SOURCE=.\STLineVD.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\element.h
# End Source File
# Begin Source File

SOURCE=.\GBus.h
# End Source File
# Begin Source File

SOURCE=.\GCElem.h
# End Source File
# Begin Source File

SOURCE=.\GCoordinator.h
# End Source File
# Begin Source File

SOURCE=.\GCQueue.h
# End Source File
# Begin Source File

SOURCE=.\GData.h
# End Source File
# Begin Source File

SOURCE=.\GDistributionBus.h
# End Source File
# Begin Source File

SOURCE=.\GDistributionQ.h
# End Source File
# Begin Source File

SOURCE=.\GDistributionSecv.h
# End Source File
# Begin Source File

SOURCE=.\GInput.h
# End Source File
# Begin Source File

SOURCE=.\GMesure.h
# End Source File
# Begin Source File

SOURCE=.\GNetworkS.h
# End Source File
# Begin Source File

SOURCE=.\GOutput.h
# End Source File
# Begin Source File

SOURCE=.\GProcessor.h
# End Source File
# Begin Source File

SOURCE=.\GProcessorS.h
# End Source File
# Begin Source File

SOURCE=.\GRepartition.h
# End Source File
# Begin Source File

SOURCE=.\GSLib.h
# End Source File
# Begin Source File

SOURCE=.\GSLib_dyn.h
# End Source File
# Begin Source File

SOURCE=.\GSum.h
# End Source File
# Begin Source File

SOURCE=.\GTransition.h
# End Source File
# Begin Source File

SOURCE=.\GTransitionS.h
# End Source File
# Begin Source File

SOURCE=.\GWire.h
# End Source File
# Begin Source File

SOURCE=.\Input.h
# End Source File
# Begin Source File

SOURCE=.\NetworkS.h
# End Source File
# Begin Source File

SOURCE=.\Output.h
# End Source File
# Begin Source File

SOURCE=.\parser_func.h
# End Source File
# Begin Source File

SOURCE=.\parser_func_data.h
# End Source File
# Begin Source File

SOURCE=.\parser_func_memory.h
# End Source File
# Begin Source File

SOURCE=.\Processor.h
# End Source File
# Begin Source File

SOURCE=.\Queues.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SCoordinator.h
# End Source File
# Begin Source File

SOURCE=.\SDotP.h
# End Source File
# Begin Source File

SOURCE=.\SGain.h
# End Source File
# Begin Source File

SOURCE=.\SInputCoordinator.h
# End Source File
# Begin Source File

SOURCE=.\SInputPartModification.h
# End Source File
# Begin Source File

SOURCE=.\SMult.h
# End Source File
# Begin Source File

SOURCE=.\SNorm.h
# End Source File
# Begin Source File

SOURCE=.\SProcessor.h
# End Source File
# Begin Source File

SOURCE=.\SQueue.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\STLineSD.h
# End Source File
# Begin Source File

SOURCE=.\STLineVD.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\GSLib_dyn.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
