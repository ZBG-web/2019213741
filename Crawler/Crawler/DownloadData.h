////////////////////////////////////////////////////
//设计者姓名:LWZ小组 刘克东 00348231
//项目名：大实习-搜索引擎-网络化爬虫
//创建日期：2004-12-10
//最近一次修改日期：2004-12-26
//类名称：DownloadData
//定义该类的目的：
//	储存工程下载信息，每个下载线程共享数据区，包括URL队列，当前线程数量等等
//类属性：
//private
//	CCriticalSection criSection;	临界区对象

//	UINT uMaxSizeOfContainer;		URL队列最大容量
//	UINT uMaxThreadNum;				最大线程数目
//	CString URLcontainer[4000];		URL队列（数组实现）

//	UINT uCur_URLnum;				当前URL数量
//	UINT uCur_URLptr;				URL队列头部指针
//	UINT uCur_Fileid;				当前本地文件编号
//	UINT uCur_ActiveThread;			当前活动线程数量

//	CString str_LocalDir;			本地储存目录
//类中函数及功能：
//	DownloadData();
//	virtual ~DownloadData();

//	bool IsFull();					是否URL队列已经满了
//	bool IsExisted(CString &);		是否URL已经存在于队列中
//	bool IsEmpty();					是否URL队列空了（无未处理的URL）

//	UINT GetMaxThreadnum();			获得最大线程数目
//	UINT GetCurThread();			获得当前活动的线程数目
//	bool DeleThread();				线程结束后，从数据区删除一个线程记录，成功返回true
//	bool AddThread();				线程开始，向数据区添加一个线程记录,成功返回true

//	bool AddURL(CString &);			向共享数据区URL队列尾添加一个URL
//	bool GetCurURL(CString &);		从共享数据区URL队列头取出一个URL

//	void GetFileName(CString &);	获得当前本地存储文件的地址
//	bool SetPro(UINT,UINT,CString &);	根据用户设定起始文件名称，最大线程数量，保存路径
//	void showURL();					显示URL队列内容(调试用)
//与其他类的关系：
//	被用户界面线MainThread程调用，生成一个工程的共享数据区，从而实现多线程下载任务
////////////////////////////////////////////////////
// DownloadData.h: interface for the DownloadData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOWNLOADDATA_H__0D70A93F_DC0C_41FD_B4B7_CC3756B176D0__INCLUDED_)
#define AFX_DOWNLOADDATA_H__0D70A93F_DC0C_41FD_B4B7_CC3756B176D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class DownloadData  
{
private:
	CCriticalSection criSection;

	UINT uMaxSizeOfContainer;
	UINT uMaxThreadNum;
	CString URLcontainer[4000];

	UINT uCur_URLnum;
	UINT uCur_URLptr;
	UINT uCur_Fileid;
	UINT uCur_ActiveThread;

	CString str_LocalDir;

public:
	DownloadData();
	virtual ~DownloadData();

	bool IsFull();
	bool IsExisted(CString &);
	bool IsEmpty();
	

	UINT GetCurThread();
	bool DeleThread();
	bool AddThread();
	UINT GetMaxThreadnum();
	
	bool AddURL(CString &);
	bool GetCurURL(CString &);
	
	void GetFileName(CString &);
	bool SetPro(UINT,UINT,CString &);

	void showURL();
};

#endif // !defined(AFX_DOWNLOADDATA_H__0D70A93F_DC0C_41FD_B4B7_CC3756B176D0__INCLUDED_)
