////////////////////////////////////////////////////
//���������:LWZС�� ���˶� 00348231
//��Ŀ������ʵϰ-��������-���绯����
//�������ڣ�2004-12-10
//���һ���޸����ڣ�2004-12-26
//ȫ�ֱ�����
//		�õ�NetCrawler.cpp�ж���ȫ�ֱ���
//	extern CNetCrawlerDlg *pDlg;	�����ڵ�ָ��
//	extern bool ThreadPause;		�Ƿ���ͣ�߳�
// NetCrawlerDlg.cpp : implementation file

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

extern 	CNetCrawlerDlg *pDlg;
extern  bool ThreadPause;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetCrawlerDlg dialog
//���캯��
CNetCrawlerDlg::CNetCrawlerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNetCrawlerDlg::IDD, pParent)
{
	pMainThread=NULL;	//��ʼ��Ϊ��
	m_active = true ;	//��ʼ��Ϊ�
	m_timer = false ;	//��ʼ��Ϊ���Զ�ˢ��
	//{{AFX_DATA_INIT(CNetCrawlerDlg)
	m_Status = _T("Weclome to NetCrawler!\r\n");
	m_Num = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNetCrawlerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNetCrawlerDlg)
	DDX_Control(pDX, IDC_EDIT_NUM, m_EditNum);
	DDX_Control(pDX, IDC_EDIT_STATUS, m_EditBox);
	DDX_Control(pDX, IDC_PROGRESS_D, m_ProgressBar);
	DDX_Text(pDX, IDC_EDIT_STATUS, m_Status);
	DDX_Text(pDX, IDC_EDIT_NUM, m_Num);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNetCrawlerDlg, CDialog)
	//{{AFX_MSG_MAP(CNetCrawlerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_NEW, OnButtonNew)
	ON_BN_CLICKED(ID_BUTTON_UPDATE, OnButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, OnButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_WM_TIMER()
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_PROGRESS_D, OnOutofmemoryProgressD)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetCrawlerDlg message handlers

BOOL CNetCrawlerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//�������ĳ�ʼ��
	m_ProgressBar.SetRange(0,4000);
	m_ProgressBar.SetStep(1);
	m_ProgressBar.SetPos(0);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNetCrawlerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNetCrawlerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNetCrawlerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CNetCrawlerDlg::OnOK() 
{
	// TODO: Add extra validation here
}
//��ť"�½�����"����Ӧ����
//����һ�������߳�
void CNetCrawlerDlg::OnButtonNew() 
{
	// TODO: Add your control notification handler code here
	::pDlg=this;
	m_Status = _T("Weclome to NetCrawler!\r\n");
	m_Num = 0;
	UpdateData(FALSE);
	pMainThread=(MainThread*)AfxBeginThread(RUNTIME_CLASS(MainThread));
	OnButtonUpdate();
}
//��ť"����/ֹͣ�Զ�ˢ��"��Ӧ����
void CNetCrawlerDlg::OnButtonUpdate() 
{
	// TODO: Add your control notification handler code here
	if(m_timer)
	{//�����ʱ�����ڣ�˵���Ѿ������Զ�ˢ��
		KillTimer(m_nTimer);
		m_timer=false;
	}
	else
	{//��������ڣ�˵��δ�����Զ�ˢ��
		m_nTimer=SetTimer(1,2000,NULL);
		m_timer=true;
	}
	
}
//��ť"��ͣ/����"��Ӧ����
void CNetCrawlerDlg::OnButtonPause() 
{
	// TODO: Add your control notification handler code here
	//�ı�ȫ�ֱ���ThreaPause��ʵ����ͣ�߳�
	if(m_active)
	{
		ThreadPause=true;
		m_active=false;
	}
	else
	{
		ThreadPause=false;
		m_active=true;
	}
}
//��ť"ֹͣ"��Ӧ����
void CNetCrawlerDlg::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	if(pMainThread!=NULL)
	{
		pMainThread->m_bDone=true;
	}
	
}
//��ʱ������Ӧ����
void CNetCrawlerDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	criSection.Lock();
	UpdateData(FALSE);
	m_EditBox.Invalidate();
	m_EditNum.Invalidate();
	criSection.Unlock();
	CDialog::OnTimer(nIDEvent);
}
//�˳�����
void CNetCrawlerDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	if(m_timer)
		KillTimer(m_nTimer);
	
	CDialog::OnCancel();
}
//�޸�״̬
void CNetCrawlerDlg::Add(CString &str,bool b)
{
	criSection.Lock();
	m_Status+=str;
	if(b)
		m_Num++;
	criSection.Unlock();
}

void CNetCrawlerDlg::OnOutofmemoryProgressD(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
