; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ODLFile=GSLib_dyn.odl
ClassCount=3
Class1=CGSLib_dynApp
LastClass=CSInputPartModification
NewFileInclude2=#include "GSLib_dyn.h"
ResourceCount=2
NewFileInclude1=#include "stdafx.h"
Class2=CSInputCoordinator
LastTemplate=CDialog
Resource1=IDD_InputCoordinator
Class3=CSInputPartModification
Resource2=IDD_InputPartModification

[CLS:CGSLib_dynApp]
Type=0
HeaderFile=GSLib_dyn.h
ImplementationFile=GSLib_dyn.cpp
Filter=N
LastObject=CGSLib_dynApp

[DLG:IDD_InputCoordinator]
Type=1
Class=CSInputCoordinator
ControlCount=39
Control1=IDC_ADD,button,1342242816
Control2=IDC_check,button,1342242816
Control3=IDC_gDim,button,1342242816
Control4=IDC_prev,button,1342242816
Control5=IDC_next,button,1342242816
Control6=IDC_modify,button,1342242816
Control7=IDCANCEL,button,1342242816
Control8=IDC_STATIC,static,1342308352
Control9=IDC_fileName,edit,1350631552
Control10=IDC_timetable,RICHEDIT,1353779396
Control11=IDC_STATIC,static,1342308352
Control12=IDC_portname,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_dim,edit,1350633600
Control15=IDC_STATIC,static,1342308352
Control16=IDC_time,edit,1350631552
Control17=IDC_STATIC,button,1342177287
Control18=IDC_init,button,1342177289
Control19=IDC_internal,button,1342177289
Control20=IDC_external,button,1342177289
Control21=IDC_print,button,1342177289
Control22=IDC_Delete,button,1342242816
Control23=IDC_Load,button,1342242816
Control24=IDC_Save,button,1342242816
Control25=IDC_InputData,RICHEDIT,1353777348
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,button,1342177287
Control28=IDC_dmanual,button,1342177289
Control29=IDC_automatic,button,1342177289
Control30=IDC_STATIC,static,1342308352
Control31=IDC_rep,edit,1350631552
Control32=IDC_error,edit,1350633600
Control33=IDC_STATIC,static,1342308352
Control34=IDC_clkprec,edit,1350631552
Control35=IDC_STATIC,static,1342308352
Control36=IDC_clkadvance,edit,1350631552
Control37=IDC_reset,button,1342242816
Control38=IDC_relinkup,button,1342242816
Control39=IDC_relinkdown,button,1342242816

[CLS:CSInputCoordinator]
Type=0
HeaderFile=SInputCoordinator.h
ImplementationFile=SInputCoordinator.cpp
BaseClass=CDialog
Filter=D
LastObject=CSInputCoordinator
VirtualFilter=dWC

[DLG:IDD_InputPartModification]
Type=1
Class=CSInputPartModification
ControlCount=72
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC,button,1342308359
Control3=IDC_wantport,button,1342177289
Control4=IDC_wantproc,button,1342177289
Control5=IDC_wantnet,button,1342177289
Control6=IDC_STATIC,button,1342308359
Control7=IDC_standalone,button,1342177289
Control8=IDC_fromproc,button,1342177289
Control9=IDC_fromnet,button,1342177289
Control10=IDC_element,edit,1350631552
Control11=IDC_level_reset,button,1342242816
Control12=IDC_level_up,button,1342242816
Control13=IDC_level_down,button,1342242816
Control14=IDC_level,edit,1350633600
Control15=IDC_STATIC,static,1342308352
Control16=IDC_del,button,1342242816
Control17=IDC_levels,RICHEDIT,1353779396
Control18=IDC_STATIC,static,1342308352
Control19=IDC_time,edit,1350631552
Control20=IDC_STATIC,button,1342308359
Control21=IDC_brother,button,1342177289
Control22=IDC_copy,button,1342177289
Control23=IDC_new,button,1342177289
Control24=IDC_addelem,button,1342242816
Control25=IDC_STATIC,button,1342308359
Control26=IDC_copyport,button,1342308361
Control27=IDC_copyproc,button,1342177289
Control28=IDC_copynet,button,1342177289
Control29=IDC_copy_reset,button,1342242816
Control30=IDC_copy_up,button,1342242816
Control31=IDC_copy_down,button,1342242816
Control32=IDC_STATIC,static,1342308352
Control33=IDC_copy_level,edit,1350633600
Control34=IDC_copy_element,edit,1350631552
Control35=IDC_copy_from,edit,1350631552
Control36=IDC_copy_levels,RICHEDIT,1353779396
Control37=IDC_STATIC,button,1342177287
Control38=IDC_copy_standalone,button,1342177289
Control39=IDC_copy_fromproc,button,1342177289
Control40=IDC_copy_fromnet,button,1342177289
Control41=IDC_STATIC,static,1342308352
Control42=IDC_STATIC,static,1342308352
Control43=IDC_STATIC,button,1342308359
Control44=IDC_same,button,1342177289
Control45=IDC_newwire,button,1342177289
Control46=IDC_STATIC,button,1342308359
Control47=IDC_toproc,button,1342177289
Control48=IDC_tonet,button,1342177289
Control49=IDC_toparent,button,1342177289
Control50=IDC_STATIC,static,1342308352
Control51=IDC_fromtoport,edit,1350631552
Control52=IDC_STATIC,static,1342308352
Control53=IDC_toport,edit,1350631552
Control54=IDC_STATIC,button,1342308359
Control55=IDC_in,button,1342177289
Control56=IDC_out,button,1342177289
Control57=IDC_wireshist,RICHEDIT,1353779396
Control58=IDC_STATIC,static,1342308353
Control59=IDC_addwire,button,1342242816
Control60=IDC_errors_messages,RICHEDIT,1353779396
Control61=IDC_STATIC,static,1342308353
Control62=IDC_STATIC,static,1342308352
Control63=IDC_topart,edit,1350631552
Control64=IDC_from,combobox,1344339970
Control65=IDC_up_levels,combobox,1344340226
Control66=IDC_new_old,button,1342242819
Control67=IDC_oldelem,combobox,1344339970
Control68=IDC_pas_act,button,1342242819
Control69=IDC_all,button,1342242819
Control70=IDC_STATIC,button,1342177287
Control71=IDC_input,button,1342177289
Control72=IDC_output,button,1342177289

[CLS:CSInputPartModification]
Type=0
HeaderFile=SInputPartModification.h
ImplementationFile=SInputPartModification.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_addelem

