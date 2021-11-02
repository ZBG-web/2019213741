////////////////////////////////////////////////////
//设计者姓名:LWZ小组 刘克东 00348231
//项目名：大实习-搜索引擎-网络化爬虫
//创建日期：2004-12-10
//最近一次修改日期：2004-12-26
//类名称：MainThread
//定义该类的目的：
//	储存工程下载信息，每个下载线程共享数据区，包括URL队列，当前线程数量等等
//类属性：
//public:
//	DownloadData m_DownData;	工程共享数据区
//	CString str_ProjectName;	工程名称
//	CString str_BeginURL;		工程起始网络地址
//	bool m_bDone;				工程停止
//	bool m_chinese;				语言类型
//	CString str_Confine;		URL过滤字符串
//类中函数及功能：
//	MainThread(); 
//	virtual ~MainThread();
//	virtual BOOL InitInstance();	重写初始化函数
//	bool TrimString(LPTSTR,UINT &,UINT &,bool);		过滤掉网页的html语言标签
//	void Run(CString &);		运行守护线程，启动工作者线程，下载网页
//与其他类的关系：
//	被NetCrawlerDlg类调用，生成一个工程，下载网页
//	调用DownloadData类，生成一个数据共享区
//	调用ProjectDlg类，进行一些工程属性设置
// MainThread.h : header file
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_MAINTHREAD_H__4C21F270_F37B_4A1B_9B99_69C8175E9054__INCLUDED_)
#define AFX_MAINTHREAD_H__4C21F270_F37B_4A1B_9B99_69C8175E9054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// MainThread thread

class MainThread : public CWinThread
{
	DECLARE_DYNCREATE(MainThread)
protected:
	MainThread();           // protected constructor used by dynamic creation

// Attributes
public:
	DownloadData m_DownData;
	CString str_ProjectName;
	CString str_BeginURL;
	bool m_bDone;
	bool m_chinese;
	CString str_Confine;
// Operations
public:

	bool TrimString(LPTSTR,UINT &,UINT &,bool);
	void Run(CString &);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MainThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~MainThread();

	// Generated message map functions
	//{{AFX_MSG(MainThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINTHREAD_H__4C21F270_F37B_4A1B_9B99_69C8175E9054__INCLUDED_)
