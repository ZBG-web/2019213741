////////////////////////////////////////////////////
//���������:LWZС�� ���˶� 00348231
//��Ŀ������ʵϰ-��������-���绯����
//�������ڣ�2004-12-10
//���һ���޸����ڣ�2004-12-26
//�����ƣ�CProjectDlg
//��������Ŀ�ģ�
//	�½�����ʱ��ʾ�Ի��򣬷����û��Թ������Խ����趨
//�����ԣ�
//public:
//	CString	m_BeginURL;		�趨������ʼ��ҳ
//	UINT	m_FileId;		�趨�����ļ���ʼ�ļ���
//	CString	m_LocalDir;		�趨�����ļ���·��
//	CString	m_ProjectName;	�趨������
//	UINT	m_ThreadNum;	�趨�߳���������
//	CString	m_Filter;		�趨����URL���ַ���
//	bool	m_CH;			��Ӣ������
//��������Ĺ�ϵ��
//	���û�������MainThread�̵��ã������½��Ĺ���һЩ����
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
