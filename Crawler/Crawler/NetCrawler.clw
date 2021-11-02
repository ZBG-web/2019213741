; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CNetCrawlerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "NetCrawler.h"

ClassCount=5
Class1=CNetCrawlerApp
Class2=CNetCrawlerDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_NETCRAWLER_DIALOG
Resource2=IDR_MAINFRAME
Class4=MainThread
Resource3=IDD_ABOUTBOX
Class5=CProjectDlg
Resource4=IDD_DIALOG_PROJECT

[CLS:CNetCrawlerApp]
Type=0
HeaderFile=NetCrawler.h
ImplementationFile=NetCrawler.cpp
Filter=N

[CLS:CNetCrawlerDlg]
Type=0
HeaderFile=NetCrawlerDlg.h
ImplementationFile=NetCrawlerDlg.cpp
Filter=D
LastObject=IDC_EDIT_NUM
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=NetCrawlerDlg.h
ImplementationFile=NetCrawlerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_NETCRAWLER_DIALOG]
Type=1
Class=CNetCrawlerDlg
ControlCount=12
Control1=ID_BUTTON_UPDATE,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_STATUS,edit,1352663172
Control4=IDC_BUTTON_NEW,button,1342242817
Control5=IDC_BUTTON_STOP,button,1342242816
Control6=IDC_BUTTON_PAUSE,button,1342242816
Control7=IDC_STATIC,static,1342308865
Control8=IDC_PROGRESS_D,msctls_progress32,1350565889
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT_NUM,edit,1484857472

[CLS:MainThread]
Type=0
HeaderFile=MainThread.h
ImplementationFile=MainThread.cpp
BaseClass=CWinThread
Filter=N
LastObject=MainThread

[DLG:IDD_DIALOG_PROJECT]
Type=1
Class=CProjectDlg
ControlCount=18
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_BEGINURL,edit,1350631552
Control4=IDC_EDIT_LOCALDIR,edit,1350631552
Control5=IDC_EDIT_FILEBEGIN,edit,1350639616
Control6=IDC_EDIT_THREADMAX,edit,1350639616
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT_PROJECTNAME,edit,1350631424
Control13=IDC_STATIC,button,1342177287
Control14=IDC_STATIC,static,1342308352
Control15=IDC_EDIT_URLFITER,edit,1350631552
Control16=IDC_STATIC,static,1342308352
Control17=IDC_CHECK_CH,button,1342242819
Control18=IDC_BUTTON_DIR,button,1342242816

[CLS:CProjectDlg]
Type=0
HeaderFile=ProjectDlg.h
ImplementationFile=ProjectDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_RADIO_CH

