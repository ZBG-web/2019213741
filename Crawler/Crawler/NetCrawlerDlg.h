////////////////////////////////////////////////////
//设计者姓名:LWZ小组 刘克东 00348231
//项目名：大实习-搜索引擎-网络化爬虫
//创建日期：2004-12-10
//最近一次修改日期：2004-12-26
//类名称：CNetCrawlerDlg
//定义该类的目的：
//	本程序的主窗口，用于新建工程，显示工程进展当前状态
//类属性：
//public:
//	CCriticalSection criSection;	保护区
//	UINT m_nTimer;	计时器
//	MainThread * pMainThread;	工程的主控线程指针
//	bool m_active;	工程是否处于活动状态
//	bool m_timer;	是否启动了自动刷新

//类中函数及功能：
//	CNetCrawlerDlg(CWnd* pParent = NULL); standard constructor 
//	void Add(CString &,bool);	添加下载状态

//与其他类的关系：
//	调用MainThread类，生成一个工程

// NetCrawlerDlg.h : header file
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETCRAWLERDLG_H__0F4EBF35_9A63_46AB_A4E3_E791278E2FD9__INCLUDED_)
#define AFX_NETCRAWLERDLG_H__0F4EBF35_9A63_46AB_A4E3_E791278E2FD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CNetCrawlerDlg dialog

class CNetCrawlerDlg : public CDialog
{
// Construction
public:

	CCriticalSection criSection;
	UINT m_nTimer;
	MainThread * pMainThread;
	bool m_active;
	bool m_timer;
	CNetCrawlerDlg(CWnd* pParent = NULL);	// standard constructor
	void Add(CString &,bool);
	// Dialog Data
	//{{AFX_DATA(CNetCrawlerDlg)
	enum { IDD = IDD_NETCRAWLER_DIALOG };
	CEdit	m_EditNum;					//编辑框控件
	CEdit	m_EditBox;					//编辑框控件
	CProgressCtrl	m_ProgressBar;		//进度条
	CString	m_Status;					//编辑框字符串
	UINT	m_Num;						//下载网页数目
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetCrawlerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CNetCrawlerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnButtonNew();
	afx_msg void OnButtonUpdate();
	afx_msg void OnButtonPause();
	afx_msg void OnButtonStop();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnCancel();
	afx_msg void OnOutofmemoryProgressD(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETCRAWLERDLG_H__0F4EBF35_9A63_46AB_A4E3_E791278E2FD9__INCLUDED_)
