////////////////////////Honor Code////////////////
// ����ϵر�֤��
    
// ���Լ��������������������ӷ�������Ƶ���������й�����
// ��������������У���������ʲô���Ѷ�������ˣ���ô���ҽ��ڳ���ʵϰ������
// ��ϸ���о��������������⣬�Լ����˸��ҵ���ʾ��

// �ڴˣ��Ҹ�л �����ҵ������Ͱ�������ʵϰ�����У��һ��������ᵽ
// ���ڸ����������ҵİ�����
 
// �ҵĳ������з������õ�����������ĵ�֮����
// ����̲ġ����ñʼǡ����ϵ�Դ�����Լ������ο����ϵĴ����,
// �Ҷ��Ѿ��ڳ����ע����������ע�������õĳ�����

// �Ҵ�δû��Ϯ�����˵ĳ���Ҳû�е��ñ��˵ĳ���
// �������޸�ʽ�ĳ�Ϯ����ԭ�ⲻ���ĳ�Ϯ��

// �ұ�д������򣬴���û�����Ҫȥ�ƻ���������������ϵͳ��������ת��
    
// <���˶� 00348231>

////////////////////////////////////////////////////
//�ļ����ƣ�NetCrawler
//��Ŀ������ʵϰ-��������-���绯����
//���������:LWZС�� ���˶� 00348231
//�������ڣ�2004-12-10
//���һ���޸����ڣ�2004-12-26

//���ܣ�
//	����ָ������ַ��������ҳ�����������е�URL�������أ�������ҳ��Ҫ���ݴ�Ϊ�����ļ�
//	Ϊ��������������Ľ����ṩԭ���� 
//�ļ��ж����ȫ�ֱ����ͼ򵥹���������
//	CNetCrawlerDlg *pDlg=NULL;	�����ڵ�ָ��
//	bool ThreadPause=false;		�����߳��Ƿ���ͣ

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
