////////////////////////////////////////////////////
//设计者姓名:LWZ小组 刘克东 00348231
//项目名：大实习-搜索引擎-网络化爬虫
//创建日期：2004-12-10
//最近一次修改日期：2004-12-26
//
// ProjectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NetCrawler.h"
#include "ProjectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProjectDlg dialog


CProjectDlg::CProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProjectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProjectDlg)
	//初始化变量
	m_BeginURL = _T("");
	m_FileId = 1;
	m_LocalDir = _T("c:\\");
	m_ProjectName = _T("");
	m_ThreadNum = 10;
	m_Filter = _T("");
	m_CH = TRUE;
	//}}AFX_DATA_INIT
}


void CProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProjectDlg)
	DDX_Text(pDX, IDC_EDIT_BEGINURL, m_BeginURL);
	DDX_Text(pDX, IDC_EDIT_FILEBEGIN, m_FileId);
	DDX_Text(pDX, IDC_EDIT_LOCALDIR, m_LocalDir);
	DDX_Text(pDX, IDC_EDIT_PROJECTNAME, m_ProjectName);
	DDV_MaxChars(pDX, m_ProjectName, 50);
	DDX_Text(pDX, IDC_EDIT_THREADMAX, m_ThreadNum);
	DDV_MinMaxUInt(pDX, m_ThreadNum, 1, 200);
	DDX_Text(pDX, IDC_EDIT_URLFITER, m_Filter);
	DDV_MaxChars(pDX, m_Filter, 20);
	DDX_Check(pDX, IDC_CHECK_CH, m_CH);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProjectDlg, CDialog)
	//{{AFX_MSG_MAP(CProjectDlg)
	ON_BN_CLICKED(IDC_BUTTON_DIR, OnButtonDir)
	ON_EN_CHANGE(IDC_EDIT_BEGINURL, OnChangeEditBeginurl)
	ON_EN_CHANGE(IDC_EDIT_LOCALDIR, OnChangeEditLocaldir)
	ON_EN_CHANGE(IDC_EDIT_URLFITER, OnChangeEditUrlfiter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProjectDlg message handlers

void CProjectDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
//当用户点击按钮"目录"时的响应函数
void CProjectDlg::OnButtonDir() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	TCHAR dispname[256];
	TCHAR path[256];
	BROWSEINFO bi;
	ITEMIDLIST *pidl;
	bi.hwndOwner=m_hWnd;
	bi.pidlRoot=0;
	bi.pszDisplayName=dispname;
	bi.lpszTitle="下载至目录";
	bi.ulFlags=BIF_RETURNONLYFSDIRS;
	bi.lpfn=0;
	bi.lParam=0;
	bi.iImage=0;
	if(pidl=SHBrowseForFolder(&bi))
		SHGetPathFromIDList(pidl,path);
	else
	{
		return;
	}
	//将结果传回新建工程对话框
	m_LocalDir.Format("%s",path);
	UpdateData(FALSE);
}

void CProjectDlg::OnChangeEditBeginurl() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CProjectDlg::OnChangeEditLocaldir() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}

void CProjectDlg::OnChangeEditUrlfiter() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}
