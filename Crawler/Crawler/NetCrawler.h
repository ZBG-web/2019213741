////////////////////////////////////////////////////
//设计者姓名:LWZ小组 刘克东 00348231
//项目名：大实习-搜索引擎-网络化爬虫
//创建日期：2004-12-10
//最近一次修改日期：2004-12-26
// NetCrawler.h : main header file for the NETCRAWLER application
//

#if !defined(AFX_NETCRAWLER_H__4ED50645_4D94_4932_B698_E6D97F60B1E0__INCLUDED_)
#define AFX_NETCRAWLER_H__4ED50645_4D94_4932_B698_E6D97F60B1E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNetCrawlerApp:
// See NetCrawler.cpp for the implementation of this class
//

class CNetCrawlerApp : public CWinApp
{
public:
	CNetCrawlerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetCrawlerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNetCrawlerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETCRAWLER_H__4ED50645_4D94_4932_B698_E6D97F60B1E0__INCLUDED_)
