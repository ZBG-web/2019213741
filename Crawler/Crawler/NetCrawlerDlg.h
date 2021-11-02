////////////////////////////////////////////////////
//���������:LWZС�� ���˶� 00348231
//��Ŀ������ʵϰ-��������-���绯����
//�������ڣ�2004-12-10
//���һ���޸����ڣ�2004-12-26
//�����ƣ�CNetCrawlerDlg
//��������Ŀ�ģ�
//	������������ڣ������½����̣���ʾ���̽�չ��ǰ״̬
//�����ԣ�
//public:
//	CCriticalSection criSection;	������
//	UINT m_nTimer;	��ʱ��
//	MainThread * pMainThread;	���̵������߳�ָ��
//	bool m_active;	�����Ƿ��ڻ״̬
//	bool m_timer;	�Ƿ��������Զ�ˢ��

//���к��������ܣ�
//	CNetCrawlerDlg(CWnd* pParent = NULL); standard constructor 
//	void Add(CString &,bool);	�������״̬

//��������Ĺ�ϵ��
//	����MainThread�࣬����һ������

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
	CEdit	m_EditNum;					//�༭��ؼ�
	CEdit	m_EditBox;					//�༭��ؼ�
	CProgressCtrl	m_ProgressBar;		//������
	CString	m_Status;					//�༭���ַ���
	UINT	m_Num;						//������ҳ��Ŀ
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
