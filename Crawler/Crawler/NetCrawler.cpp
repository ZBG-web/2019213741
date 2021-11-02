////////////////////////Honor Code////////////////
// 我真诚地保证：
    
// 我自己独立地完成了整个程序从分析、设计到编码的所有工作。
// 如果在上述过程中，我遇到了什么困难而求教于人，那么，我将在程序实习报告中
// 详细地列举我所遇到的问题，以及别人给我的提示。

// 在此，我感谢 陈昊罡对我的启发和帮助。在实习报告中，我还会具体地提到
// 他在各个方法对我的帮助。
 
// 我的程序里中凡是引用到其他程序或文档之处，
// 例如教材、课堂笔记、网上的源代码以及其他参考书上的代码段,
// 我都已经在程序的注释里很清楚地注明了引用的出处。

// 我从未没抄袭过别人的程序，也没有盗用别人的程序，
// 不管是修改式的抄袭还是原封不动的抄袭。

// 我编写这个程序，从来没有想过要去破坏或妨碍其他计算机系统的正常运转。
    
// <刘克东 00348231>

////////////////////////////////////////////////////
//文件名称：NetCrawler
//项目名：大实习-搜索引擎-网络化爬虫
//设计者姓名:LWZ小组 刘克东 00348231
//创建日期：2004-12-10
//最近一次修改日期：2004-12-26

//功能：
//	根据指定的网址，下载网页，并分析其中的URL继续下载，并将网页主要内容存为本地文件
//	为搜索引擎的索引的建立提供原材料 
//文件中定义的全局变量和简单功能描述：
//	CNetCrawlerDlg *pDlg=NULL;	主窗口的指针
//	bool ThreadPause=false;		主控线程是否暂停

// NetCrawler.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxmt.h"
#include "NetCrawler.h"
#include "DownloadData.h"
#include "ProjectDlg.h"
#include "MainThread.h"

#include "NetCrawlerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
///////////////////////////////////
//Global Variable
CNetCrawlerDlg *pDlg=NULL;
bool ThreadPause=false;
/////////////////////////////////////////////////////////////////////////////
// CNetCrawlerApp

BEGIN_MESSAGE_MAP(CNetCrawlerApp, CWinApp)
	//{{AFX_MSG_MAP(CNetCrawlerApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetCrawlerApp construction

CNetCrawlerApp::CNetCrawlerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CNetCrawlerApp object

CNetCrawlerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CNetCrawlerApp initialization

BOOL CNetCrawlerApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CNetCrawlerDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
