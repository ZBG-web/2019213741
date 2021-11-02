////////////////////////////////////////////////////
//设计者姓名:LWZ小组 刘克东 00348231
//项目名：大实习-搜索引擎-网络化爬虫
//创建日期：2004-12-10
//最近一次修改日期：2004-12-26
//类名称：CProjectDlg
//定义该类的目的：
//	新建工程时显示对话框，方便用户对工程属性进行设定
//类属性：
//public:
//	CString	m_BeginURL;		设定爬虫起始网页
//	UINT	m_FileId;		设定保存文件起始文件名
//	CString	m_LocalDir;		设定保存文件的路径
//	CString	m_ProjectName;	设定工程名
//	UINT	m_ThreadNum;	设定线程数量上限
//	CString	m_Filter;		设定过滤URL的字符串
//	bool	m_CH;			中英文设置
//与其他类的关系：
//	被用户界面线MainThread程调用，进行新建的工程一些设置
#if !defined(AFX_PROJECTDLG_H__551CEB98_6B4D_45BE_8DB1_C888959DFAD8__INCLUDED_)
#define AFX_PROJECTDLG_H__551CEB98_6B4D_45BE_8DB1_C888959DFAD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProjectDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProjectDlg dialog

class CProjectDlg : public CDialog
{
// Construction
public:
	CProjectDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProjectDlg)
	enum { IDD = IDD_DIALOG_PROJECT };
	CString	m_BeginURL;
	UINT	m_FileId;
	CString	m_LocalDir;
	CString	m_ProjectName;
	UINT	m_ThreadNum;
	CString	m_Filter;
	BOOL	m_CH;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProjectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProjectDlg)
	virtual void OnOK();
	afx_msg void OnButtonDir();
	afx_msg void OnChangeEditBeginurl();
	afx_msg void OnChangeEditLocaldir();
	afx_msg void OnChangeEditUrlfiter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROJECTDLG_H__551CEB98_6B4D_45BE_8DB1_C888959DFAD8__INCLUDED_)
