////////////////////////////////////////////////////
//���������:LWZС�� ���˶� 00348231
//��Ŀ������ʵϰ-��������-���绯����
//�������ڣ�2004-12-10
//���һ���޸����ڣ�2004-12-26
//
//ȫ�ֱ�����
//		�õ�NetCrawler.cpp�ж���ȫ�ֱ���
//extern CNetCrawlerDlg *pDlg;	�����ڵ�ָ��
//extern bool ThreadPause;		�Ƿ���ͣ�߳�
//ע���������߳�(worker thread)�Ĵ��뺯������Ϊ���еĳ�Ա������
//�ʽ����뺯������Ϊȫ�ֺ���
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
//�û������̹߳��캯��
MainThread::MainThread()
{
	m_chinese=TRUE;
	m_bDone=FALSE;
}

MainThread::~MainThread()
{
}
//��ʼ������
BOOL MainThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	//����һ���½����̶Ի���
	CProjectDlg NewProjectDlg;
	if(NewProjectDlg.DoModal()==IDOK)
	{
		//һЩ���ڹ���������������
		m_DownData.SetPro(NewProjectDlg.m_FileId,NewProjectDlg.m_ThreadNum,NewProjectDlg.m_LocalDir);
		//���������̵߳�����
		//��ʼ��ַ������
		NewProjectDlg.m_BeginURL.MakeLower();
		if(NewProjectDlg.m_BeginURL.Find(_T("http://"))==-1)
		{
			str_BeginURL=_T("http://")+NewProjectDlg.m_BeginURL;
		}
		else
		{
			str_BeginURL=NewProjectDlg.m_BeginURL;
		}
		//������������
		str_ProjectName=NewProjectDlg.m_ProjectName;
		//URL�����ַ���������
		if(NewProjectDlg.m_Filter=="")
		{
			str_Confine=str_BeginURL.Mid(11,3);
		}
		else
		{
			str_Confine=NewProjectDlg.m_Filter;
		}
		//��������
		m_chinese=NewProjectDlg.m_CH;
		//��ʾ
		AfxMessageBox(_T("ѡ���URL��Ϊ���:")+str_BeginURL);
		CWnd *button;
		button=pDlg->GetDlgItem(IDC_BUTTON_NEW);
		button->EnableWindow(FALSE);
		//���й���
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
//�������ƣ�FindURL
//��������������ȫ�ֺ���
//	���������̵߳��ã�����ҳ����ȡURL
//��������֮ǰ��Ԥ��������
//	��ҳ�Ѿ������������ص����ش�Ϊ��ʱ�ļ�
//���غ�Ĵ���
//	ɾ����ʱ�ļ�
//���������������
//	CString s	��ʱ�ļ��ı��ص�ַ
//	MainThread *ptr	���ڻ�������̵߳Ĺ���������
//�����ĳ����㷨
//	1��ֻ����ʽ�򿪱����ļ�
//	2���������ӣ���δ�ڹ�����������URL��������г��֣���������
//	3���ر��ļ�
// ���������������к����ĵ��úͱ����ù�ϵ��
//	��ÿһ���������̵߳��ã�������ҳ�ж�ȡ����
//	�������߳�(worker thread)�Ĵ��뺯������Ϊ���еĳ�Ա������
//	�ʽ����뺯������Ϊȫ�ֺ���

void FindURL(CString s,	MainThread *ptr)
{
	CStdioFile fin;

	//ReadOnlyģʽ�򿪸��ļ�
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

	//�����ҳ�Ƿ񱻷��ʹ��ı�ǩ
	bool exist=false;

	while(fin.ReadString(str_Line))
	{
		//read a line from the given file
		//�ж�URL�����Ƿ�����
		if(ptr->m_DownData.IsFull())break;
		i=str_Line.Find(mark);
		//if this line doesn't contain a URL
		if(i==-1)continue;
//���¹���Ϊ��ȡһ������
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
//���¹���Ϊת�����·��
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
	//�ر�
	fin.Close();
}
//�������ƣ�UINT DownloadFile(LPVOID pParam)
//��������������ȫ�ֺ���
//	controlling function for the worker thread
//	��URL������еõ�һ����ַ������
//���������������
//	LPVOID pParam	�����̵߳�ָ�룬���ڻ�ȡ����������
//�����ĳ����㷨
//	1����ͼ��URL�����л�ȡһ��URL����ʧ���򷵻�(�����߳�)
//	2�����ݵ�ַ���������������������ʧ���򷵻�(�����߳�)
//	3��������ҳ����ȡ��Ҫ���ݣ�����һ����ʱ�ļ�����FindURL������������
//	4���ӹ���������ɾ���̱߳�ǩ
//	5�������߳�
//	�������߳�(worker thread)�Ĵ��뺯������Ϊ���еĳ�Ա������
//	�ʽ����뺯������Ϊȫ�ֺ���

UINT DownloadFile(LPVOID pParam)
{
	MainThread *ptr=(MainThread *)pParam;
	CString URL;
	//��ͼ��ȡһ��URL
	if(!(ptr->m_DownData.GetCurURL(URL)))
	{
		ptr->m_DownData.DeleThread();
		return 0;
	}
//����Ϊ�������緢������
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
	{//������
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
	//������ȡ�󱣴�Ϊ�����ļ�
	CStdioFile LocalFile;
	//������ʱ�ļ�
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
	//�ҳ���ҳ�ı���
	while(pHttpFile->ReadString(s))
	{//ÿ�ζ�ȡһ��
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
	//���������ݵĹ���
	while(pHttpFile->ReadString(s))
	{
		if(b)tempLocalFile.WriteString(s+_T("\n"));

		p=s.GetBuffer(1024);
		ptr->TrimString(p,w,k,ptr->m_chinese);
		s.ReleaseBuffer();
		if(s!="")
		{
			int f=0,g=0;
			//ȥ��&nbsp;����
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
//������ʱ�ļ��е�����
	if(b)
	{
		FindURL(str_FileName+_T(".tmp"),ptr);
//ɾ����ʱ�ļ�
		DeleteFile(str_FileName+_T(".tmp"));
	}


	pHttpFile->Close();
	delete pHttpFile;
	pServer->Close();
	delete pServer;
	MyConnect.Close();
//״̬��ʾ
	pDlg->Add(URL+"\r\nDownload successfully!\r\n",1);
	pDlg->m_ProgressBar.StepIt();
	ptr->m_DownData.DeleThread();
	return 1;

}
////////////////////////////////////////////////////////////////////////////
// MainThread message handlers
void MainThread::Run(CString &str_Begin)
{
	//����������URL���м����URL
	m_DownData.AddURL(str_Begin);
	//���ʸ�URL
	if(m_DownData.AddThread())
	{
		AfxBeginThread(DownloadFile,this);
	}
	//���������������̣߳����ݹ���������URL�������ε�ָ��URL����
	while(!m_bDone && !(m_DownData.IsEmpty() && m_DownData.GetCurThread()==0))
	{
		Sleep(100);
		//�ж�ȫ�ֱ���ThreadPause���Ƿ���ͣ�߳�
		if(ThreadPause)continue;
		if(m_DownData.AddThread())
		{
			AfxBeginThread(DownloadFile,this);
		}
	}
	Sleep(1000);

	AfxMessageBox(_T("������ɣ�"));
	ExitInstance();
}

//�������ƣ�TrimString
//�����������������˵��ַ����е�html���Ա�ǩ

//���������������
//	LPTSTR pszBuffer �ַ���ָ��ָ�򱻴�����ַ�������'\0'��β
//	UINT &w	�Ѿ����ֵ�"<"��Ŀ
//	UINT &K	�Ѿ����ֵ�"{"��Ŀ
//	bool chinese �Ƿ���Ҫ��������
//�����ĳ����㷨�� 
//	����html���룬������{}�м�ı���Ϊ������ᱻ��������ɾ��
//				������<>�м�Ĵ���ᵱ�����Ա�ǩ��ɾ��
//	�������Ҫ�������ģ�Ϊ�˸��õĹ��ˣ���һ����û��һ�������ַ�����ʡ�Ը���
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
		{//�����ַ����Ƿ��������ַ�
			ch=TRUE;	
		}
		if (*pszSource == '{')k++;

		if(k==0)
		{//���δ��������{}��
			if (w!=0)
			{//���������<>��

				if (*pszSource == '>')
					w--;
				else if(*pszSource == '<')
				{
					w++;
				}
			}
			else
			{//δ������<>��
				if (*pszSource == '<')
				{
					w++;
					mark=TRUE;
				}
				else
				{
					if(mark)
					{//ÿ�������Կո�ֿ�
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
	//��������
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

