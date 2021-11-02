////////////////////////////////////////////////////
//设计者姓名:LWZ小组 刘克东 00348231
//项目名：大实习-搜索引擎-网络化爬虫
//创建日期：2004-12-10
//最近一次修改日期：2004-12-26
//
// DownloadData.cpp: implementation of the DownloadData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NetCrawler.h"

#include "afxmt.h"
#include "DownloadData.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DownloadData::DownloadData()
{
	uCur_URLnum=0;				//初始化当前队列中URL数量为0
	uMaxSizeOfContainer=4000;	//URL队列最大容量
	uCur_URLptr=0;				//当前队列头部指针
	uCur_ActiveThread=0;		//当前活动线程数量为0
	uMaxThreadNum=10;			//初始化线程数目10
	uCur_Fileid=1;				//初始化本地文件名称为1
	str_LocalDir="C:\\";		//初始化本地文件目录为C:
}


DownloadData::~DownloadData()
{
}
//是否URL队列已经满了
bool DownloadData::IsEmpty()
{
	criSection.Lock();
	bool r=(uCur_URLnum<=uCur_URLptr);
	criSection.Unlock();
	return r;
}
//是否URL已经存在于队列中
bool DownloadData::IsExisted(CString &str)
{
	criSection.Lock();
	for(UINT i=0;i<uCur_URLnum;i++)
	{
		if(URLcontainer[i]==str)
		{
			criSection.Unlock();
			return TRUE;
		}
	}
	criSection.Unlock();
	return FALSE;
}
//是否URL队列空了（无未处理的URL）
bool DownloadData::IsFull()
{		
	criSection.Lock();
	bool r=(uCur_URLnum==uMaxSizeOfContainer);
	criSection.Unlock();
	return r;
}
//获得当前活动线程数目
UINT DownloadData::GetCurThread()
{
	criSection.Lock();
	UINT n=uCur_ActiveThread;
	criSection.Unlock();
	return n;
}
//获得最大线程数目
UINT DownloadData::GetMaxThreadnum()
{
	return uMaxThreadNum;
}
//线程开始，向数据区添加一个线程记录,成功返回true
bool DownloadData::AddThread()
{
	criSection.Lock();
	if(uCur_ActiveThread==uMaxThreadNum)
	{
		criSection.Unlock();
		return FALSE;
	}
	uCur_ActiveThread++;
	criSection.Unlock();
	return TRUE;
}
//线程结束后，从数据区删除一个线程记录，成功返回true
bool DownloadData::DeleThread()
{
	criSection.Lock();
	if(uCur_ActiveThread==0)
	{
		criSection.Unlock();
		return FALSE;
	}
	uCur_ActiveThread--;
	criSection.Unlock();
	return TRUE;
}
//从共享数据区URL队列头取出一个URL
bool DownloadData::GetCurURL(CString &str)
{
	criSection.Lock();
	if(uCur_URLptr>=uCur_URLnum)
	{
		criSection.Unlock();
		return FALSE;
	}
	str=URLcontainer[uCur_URLptr];
	uCur_URLptr++;
	criSection.Unlock();
	return TRUE;

}
//向共享数据区URL队列尾添加一个URL
bool DownloadData::AddURL(CString &str)
{
	criSection.Lock();
	if(uCur_URLnum==uMaxSizeOfContainer)
	{
		criSection.Unlock();
		return FALSE;
	}
	URLcontainer[uCur_URLnum]=str;
	uCur_URLnum++;
	criSection.Unlock();
	return FALSE;

}
//获得当前本地存储文件的地址
void DownloadData::GetFileName(CString &str)
{
	criSection.Lock();
	CString str_temp;
	str_temp.Format("%d",uCur_Fileid);
	str=str_LocalDir+str_temp+".txt";
	uCur_Fileid++;
	criSection.Unlock();
}

//根据用户设定起始文件名称，最大线程数量，保存路径
bool DownloadData::SetPro(UINT Fileid, UINT ThreadNum, CString &str)
{
	if(str[str.GetLength()-1]!='\\')
		str+="\\";
	str_LocalDir=str;
	uCur_Fileid=Fileid;
	uMaxThreadNum=ThreadNum;
	return TRUE;
}

//显示URL队列内容(调试用)
void DownloadData::showURL()
{
	for(UINT i=0;i<uCur_URLnum;i++)
	{
		AfxMessageBox(URLcontainer[i]);
	}

}
