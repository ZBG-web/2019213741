////////////////////////////////////////////////////
//设计者姓名:LWZ小组 刘克东 00348231
//项目名：大实习-搜索引擎-网络化爬虫
//创建日期：2004-12-10
//最近一次修改日期：2004-12-26
//
//全局变量：
//		用到NetCrawler.cpp中定义全局变量
//extern CNetCrawlerDlg *pDlg;	主窗口的指针
//extern bool ThreadPause;		是否暂停线程
//注：工作者线程(worker thread)的传入函数不能为类中的成员函数，
//故将传入函数声明为全局函数
// MainThread.cpp : implementation file
////////////////////////////////////////////////////

#include "stdafx.h"
#include "NetCrawler.h"
#include <afxmt.h>
#include "DownloadData.h"
#include "ProjectDlg.h"
#include "MainThread.h"
#include "NetCrawlerDlg.h"
#include <afxinet.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern 	CNetCrawlerDlg *pDlg;
extern  bool ThreadPause;
/////////////////////////////////////////////////////////////////////////////
// MainThread

IMPLEMENT_DYNCREATE(MainThread, CWinThread)
//用户界面线程构造函数
MainThread::MainThread()
{
	m_chinese=TRUE;
	m_bDone=FALSE;
}

MainThread::~MainThread()
{
}
//初始化函数
BOOL MainThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	//生成一个新建工程对话框
	CProjectDlg NewProjectDlg;
	if(NewProjectDlg.DoModal()==IDOK)
	{
		//一些关于共享数据区的设置
		m_DownData.SetPro(NewProjectDlg.m_FileId,NewProjectDlg.m_ThreadNum,NewProjectDlg.m_LocalDir);
		//关于主控线程的设置
		//起始地址的设置
		NewProjectDlg.m_BeginURL.MakeLower();
		if(NewProjectDlg.m_BeginURL.Find(_T("http://"))==-1)
		{
			str_BeginURL=_T("http://")+NewProjectDlg.m_BeginURL;
		}
		else
		{
			str_BeginURL=NewProjectDlg.m_BeginURL;
		}
		//工程名的设置
		str_ProjectName=NewProjectDlg.m_ProjectName;
		//URL过滤字符串的设置
		if(NewProjectDlg.m_Filter=="")
		{
			str_Confine=str_BeginURL.Mid(11,3);
		}
		else
		{
			str_Confine=NewProjectDlg.m_Filter;
		}
		//语言设置
		m_chinese=NewProjectDlg.m_CH;
		//提示
		AfxMessageBox(_T("选择该URL作为起点:")+str_BeginURL);
		CWnd *button;
		button=pDlg->GetDlgItem(IDC_BUTTON_NEW);
		button->EnableWindow(FALSE);
		//运行工程
		Run(str_BeginURL);
	}
	return TRUE;
}

int MainThread::ExitInstance()
{
	CWnd *button;
	button=pDlg->GetDlgItem(IDC_BUTTON_NEW);
	button->EnableWindow(TRUE);
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(MainThread, CWinThread)
	//{{AFX_MSG_MAP(MainThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
//Global function
//函数名称：FindURL
//函数功能描述：全局函数
//	被工作者线程调用，从网页中提取URL
//函数调用之前的预备条件：
//	网页已经从网络上下载到本地存为临时文件
//返回后的处理：
//	删除临时文件
//函数的输入参数：
//	CString s	临时文件的本地地址
//	MainThread *ptr	用于获得主控线程的共享数据区
//函数的抽象算法
//	1、只读方式打开本地文件
//	2、查找连接，若未在共享数据区的URL任务队列中出现，则加入队列
//	3、关闭文件
// 函数与其他对象中函数的调用和被调用关系：
//	被每一个工作者线程调用，来从网页中读取链接
//	工作者线程(worker thread)的传入函数不能为类中的成员函数，
//	故将传入函数声明为全局函数

void FindURL(CString s,	MainThread *ptr)
{
	CStdioFile fin;

	//ReadOnly模式打开该文件
	//if file doesn't exist
	if(!fin.Open(s,CFile::modeRead))
	{
		return;
	}
	CString str_BaseURL;
	if(!fin.ReadString(str_BaseURL))
	{
		return;
	}

	//the link must begins with "href="
	CString mark="href";

	int i=-1,j=-1,URL_end=-1;
	CString str_Line,str_URL;

	//标记网页是否被访问过的标签
	bool exist=false;

	while(fin.ReadString(str_Line))
	{
		//read a line from the given file
		//判断URL队列是否满了
		if(ptr->m_DownData.IsFull())break;
		i=str_Line.Find(mark);
		//if this line doesn't contain a URL
		if(i==-1)continue;
//以下工作为提取一个链接
		//filter the URL contained in this line
		str_Line=str_Line.Mid(i+4);
		//do with URL like "href =                "http://..."   "
		str_Line.TrimLeft();
		if(str_Line[0]=='=')
		str_Line=str_Line.Mid(1);
		str_Line.TrimLeft();
		
		//do with URL in " "
		if(str_Line[0]=='\"')
		{
			URL_end=str_Line.Find("\"",1);
			if(URL_end==-1 || URL_end==1)continue;
			str_URL=str_Line.Mid(1,URL_end-1);
		}
		else if(str_Line[0]=='\'')
		{
		//do with URL in ' '
			URL_end=str_Line.Find("\'",1);
			if(URL_end==-1 || URL_end==1)continue;
			str_URL=str_Line.Mid(1,URL_end-1);
		}
		else
		{
			i=str_Line.Find(">");
			j=str_Line.Find(" ");
			if(i==-1)URL_end=j;
			else if(j==-1)URL_end=i;
			else if(i>j)URL_end=j;
			else URL_end=i;
			if(URL_end==-1)continue;
			str_URL=str_Line.Left(URL_end);
		}
		
		//if the URL is a mail link,it should be beglected
		if(str_URL.Find("mailto:")!=-1 ) continue;
		//if the URL is #
		if(str_URL.Find("#")!=-1 ) continue;
		//if the URL is an internet one,it should be neglected
		if(str_URL.Find(".htm")==-1 &&str_URL.Find(".html")==-1 && str_URL.Find(".shtml")==-1 
				&&str_URL.Find(".shtml")==-1 && str_URL[str_URL.GetLength()-1]!='/')continue;		
//以下工作为转换相对路径
		if(str_URL.Find("http:")==-1)
		{
			LPTSTR p=new TCHAR[200];
			unsigned long m=200;
			if(!InternetCombineUrl(str_BaseURL,str_URL,p,&m,ICU_BROWSER_MODE))
			{
				continue;
			}
			str_URL=p;
			delete []p;
		}
		if(str_URL.Find(ptr->str_Confine)==-1)continue;
//Judge whether file has already been visited
		if(!(ptr->m_DownData.IsExisted(str_URL)))
		{
			ptr->m_DownData.AddURL(str_URL);
		}
	}
	//关闭
	fin.Close();
}
//函数名称：UINT DownloadFile(LPVOID pParam)
//函数功能描述：全局函数
//	controlling function for the worker thread
//	从URL任务队列得到一个网址并尝试
//函数的输入参数：
//	LPVOID pParam	主控线程的指针，用于获取共享数据区
//函数的抽象算法
//	1、试图从URL队列中获取一个URL，若失败则返回(结束线程)
//	2、根据地址向服务器发送请求，若请求失败则返回(结束线程)
//	3、根据网页，提取主要内容，并存一个临时文件，用FindURL函数查找链接
//	4、从共享数据区删除线程标签
//	5、结束线程
//	工作者线程(worker thread)的传入函数不能为类中的成员函数，
//	故将传入函数声明为全局函数

UINT DownloadFile(LPVOID pParam)
{
	MainThread *ptr=(MainThread *)pParam;
	CString URL;
	//试图获取一个URL
	if(!(ptr->m_DownData.GetCurURL(URL)))
	{
		ptr->m_DownData.DeleThread();
		return 0;
	}
//以下为建立网络发出请求
	CInternetSession MyConnect("Microsoft MFC APP",1,INTERNET_OPEN_TYPE_DIRECT);
	CHttpConnection* pServer = NULL;
	CHttpFile* pHttpFile=NULL;

	// check to see if this is a reasonable URL
	CString strServerName;
	CString strObject;
	INTERNET_PORT nPort;
	DWORD dwServiceType;

	try
	{
		if (!AfxParseURL(URL, dwServiceType, strServerName, strObject, nPort) ||
			dwServiceType != INTERNET_SERVICE_HTTP)
		{
			THROW(new CInternetException(dwServiceType));
		}
		pServer=MyConnect.GetHttpConnection(strServerName, nPort);
		pHttpFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET,
			strObject, NULL, 1, NULL, NULL);
		pHttpFile->AddRequestHeaders(_T("Accept: text/*\r\nUser-Agent: MFC\r\n"));
		pHttpFile->SendRequest();
	
		DWORD StatusCode;
		pHttpFile->QueryInfoStatusCode(StatusCode);

		//file isn't there or is redirected
		if (StatusCode == HTTP_STATUS_MOVED ||StatusCode == HTTP_STATUS_REDIRECT ||
			StatusCode == HTTP_STATUS_REDIRECT_METHOD)
		{
			CString strNewLocation;
			pHttpFile->QueryInfo(HTTP_QUERY_RAW_HEADERS_CRLF, strNewLocation);

			int nPlace = strNewLocation.Find(_T("Location: "));
			if (nPlace == -1)
			{
				THROW(new CInternetException(StatusCode));
			}
			strNewLocation = strNewLocation.Mid(nPlace + 10);
			nPlace = strNewLocation.Find('\n');
			if (nPlace > 0)
				strNewLocation = strNewLocation.Left(nPlace);

			// close up the redirected site
			pHttpFile->Close();
			delete pHttpFile;
			pServer->Close();
			delete pServer;

			// figure out what the old place was
			if (!AfxParseURL(strNewLocation, dwServiceType, strServerName, strObject, nPort))
			{
				THROW(new CInternetException(StatusCode));
			}

			if (dwServiceType != INTERNET_SERVICE_HTTP)
			{
				THROW(new CInternetException(StatusCode));
			}

			// try again at the new location
			pServer = MyConnect.GetHttpConnection(strServerName, nPort);
			pHttpFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET,
				strObject, NULL, 1, NULL, NULL);
			pHttpFile->AddRequestHeaders(_T("Accept: text/*\r\nUser-Agent: MFC\r\n"));
			pHttpFile->SendRequest();

			pHttpFile->QueryInfoStatusCode(StatusCode);
		}

		if (StatusCode != HTTP_STATUS_OK)
		{
			THROW(new CInternetException(StatusCode));
		}

	}catch(CInternetException *pEx)
	{//出错处理
		if(pServer!=NULL)
		{
			pServer->Close();
			delete pServer;
		}
		if(pHttpFile!=NULL)
		{
			pHttpFile->Close();
			delete pHttpFile;
		}
		pEx->Delete();
		MyConnect.Close();
		ptr->m_DownData.DeleThread();
		pDlg->Add(URL+"\r\nDownload failed!\r\n",0);
		return 0;
	}
	//message for "Connected"
	//if m_DownData is not full save the file
	bool b=!(ptr->m_DownData.IsFull());
	CString str_FileName;
	ptr->m_DownData.GetFileName(str_FileName);
	//内容提取后保存为本地文件
	CStdioFile LocalFile;
	//本地临时文件
	CStdioFile tempLocalFile;
	LocalFile.Open(str_FileName,
	CFile::modeCreate|CFile::modeWrite|CFile::typeText);
	if(b)tempLocalFile.Open(str_FileName+".tmp",
	CFile::modeCreate|CFile::modeWrite|CFile::typeText);
	if(b)tempLocalFile.WriteString(URL+_T("\n"));
	LocalFile.WriteString(URL+_T("\n"));

	CString s;
	UINT w=0,k=0;
	int i=0,j=0;
	LPTSTR p;
	//找出本页的标题
	while(pHttpFile->ReadString(s))
	{//每次读取一行
		if(b)tempLocalFile.WriteString(s+_T("\n"));
		i=s.Find(_T("<TITLE>"));
		if(i==-1) i=s.Find(_T("<Title>"));
		if(i==-1) i=s.Find(_T("<title>"));
		if(i!=-1)
		{
			i+=7;
			j=s.Find(_T("</"),i);
			if(j!=-1)LocalFile.WriteString(s.Mid(i,j-i)+_T("\n"));
				else
			{
				LocalFile.WriteString(s.Mid(i));
				while(pHttpFile->ReadString(s))
				{
					if(b)tempLocalFile.WriteString(s+_T("\n"));
					j=s.Find(_T("</"));
					if(j==-1)
					{
						LocalFile.WriteString(s);
						continue;
					}
					LocalFile.WriteString(s.Left(j)+"\n");
					break;
				}
			}
			break;
		}
		if(s.Find(_T("</HAED>"))!=-1 || s.Find(_T("</Head>"))!=-1 || s.Find(_T("</head>"))!=-1)
		{
			LocalFile.WriteString(_T("Untitled Page\n"));
			break;
		}
	};
	bool body=false;
	while(pHttpFile->ReadString(s))
	{
		if(b)tempLocalFile.WriteString(s+_T("\n"));
		if(s.Find(_T("<BODY"))!=-1 || s.Find(_T("<body"))!=-1 || s.Find(_T("<Body"))!=-1)
			body=true;
		if(body && s.Find('>')!=-1)break;
	}
	//对主体内容的过滤
	while(pHttpFile->ReadString(s))
	{
		if(b)tempLocalFile.WriteString(s+_T("\n"));

		p=s.GetBuffer(1024);
		ptr->TrimString(p,w,k,ptr->m_chinese);
		s.ReleaseBuffer();
		if(s!="")
		{
			int f=0,g=0;
			//去除&nbsp;符号
			while((g=s.Find(_T("&nbsp;"),f))!=-1)
			{
				s.Delete(g,6);
				s.Insert(g," ");
				f=g;
			}
			s.TrimLeft();
			s.TrimRight();
			if(s!="")
			{
				LocalFile.WriteString(s+_T(" "));
			}
		}
	}

	LocalFile.Close();
	if(b)tempLocalFile.Close();
//查找临时文件中的链接
	if(b)
	{
		FindURL(str_FileName+_T(".tmp"),ptr);
//删除临时文件
		DeleteFile(str_FileName+_T(".tmp"));
	}


	pHttpFile->Close();
	delete pHttpFile;
	pServer->Close();
	delete pServer;
	MyConnect.Close();
//状态显示
	pDlg->Add(URL+"\r\nDownload successfully!\r\n",1);
	pDlg->m_ProgressBar.StepIt();
	ptr->m_DownData.DeleThread();
	return 1;

}
////////////////////////////////////////////////////////////////////////////
// MainThread message handlers
void MainThread::Run(CString &str_Begin)
{
	//向共享数据区URL队列加入根URL
	m_DownData.AddURL(str_Begin);
	//访问根URL
	if(m_DownData.AddThread())
	{
		AfxBeginThread(DownloadFile,this);
	}
	//依次启动工作者线程，根据共享数据区URL队列依次到指定URL下载
	while(!m_bDone && !(m_DownData.IsEmpty() && m_DownData.GetCurThread()==0))
	{
		Sleep(100);
		//判断全局变量ThreadPause，是否暂停线程
		if(ThreadPause)continue;
		if(m_DownData.AddThread())
		{
			AfxBeginThread(DownloadFile,this);
		}
	}
	Sleep(1000);

	AfxMessageBox(_T("任务完成！"));
	ExitInstance();
}

//函数名称：TrimString
//函数功能描述：过滤掉字符串中的html语言标签

//函数的输入参数：
//	LPTSTR pszBuffer 字符串指针指向被处理的字符串，以'\0'结尾
//	UINT &w	已经出现的"<"数目
//	UINT &K	已经出现的"{"数目
//	bool chinese 是否主要保留中文
//函数的抽象算法： 
//	对于html代码，出现在{}中间的被视为函数体会被无条件的删除
//				出现在<>中间的代码会当作语言标签被删除
//	如果是主要保留中文，为了更好的过滤，若一行中没有一个中文字符，则省略该行
bool MainThread::TrimString(LPTSTR pszBuffer,UINT &w,UINT &k,bool chinese)
{
	LPTSTR pszSource = pszBuffer;
	LPTSTR pszDest = pszBuffer;
	LPTSTR pszTemp = pszBuffer;
	bool ch=FALSE;
	bool mark=FALSE;

	while (*pszSource != '\0')
	{
		if (!ch && (*pszSource)<0)
		{//本段字符中是否含有中文字符
			ch=TRUE;	
		}
		if (*pszSource == '{')k++;

		if(k==0)
		{//如果未被包含在{}中
			if (w!=0)
			{//如果包含在<>中

				if (*pszSource == '>')
					w--;
				else if(*pszSource == '<')
				{
					w++;
				}
			}
			else
			{//未包含在<>中
				if (*pszSource == '<')
				{
					w++;
					mark=TRUE;
				}
				else
				{
					if(mark)
					{//每段文字以空格分开
						*pszDest=' ';
						pszDest++;
						mark=FALSE;
					}
					*pszDest = *pszSource;
					pszDest++;
				}
			}
		}
		if (*pszSource == '}')k--;
		pszSource++;
	}
	//结束处理
	if(chinese)
	{
		if(ch)
		{
			*pszDest = '\0';
		}
		else
		{
			*pszTemp= '\0';
		}
	}
	else
	{
		*pszDest = '\0';
	}
	return TRUE;
}

