////////////////////////////////////////////////////
//���������:LWZС�� ���˶� 00348231
//��Ŀ������ʵϰ-��������-���绯����
//�������ڣ�2004-12-10
//���һ���޸����ڣ�2004-12-26
//�����ƣ�MainThread
//��������Ŀ�ģ�
//	���湤��������Ϣ��ÿ�������̹߳���������������URL���У���ǰ�߳������ȵ�
//�����ԣ�
//public:
//	DownloadData m_DownData;	���̹���������
//	CString str_ProjectName;	��������
//	CString str_BeginURL;		������ʼ�����ַ
//	bool m_bDone;				����ֹͣ
//	bool m_chinese;				��������
//	CString str_Confine;		URL�����ַ���
//���к��������ܣ�
//	MainThread(); 
//	virtual ~MainThread();
//	virtual BOOL InitInstance();	��д��ʼ������
//	bool TrimString(LPTSTR,UINT &,UINT &,bool);		���˵���ҳ��html���Ա�ǩ
//	void Run(CString &);		�����ػ��̣߳������������̣߳�������ҳ
//��������Ĺ�ϵ��
//	��NetCrawlerDlg����ã�����һ�����̣�������ҳ
//	����DownloadData�࣬����һ�����ݹ�����
//	����ProjectDlg�࣬����һЩ������������
// MainThread.h : header file
/////////////////////////////////////////////////////////////////////////////
#if !defined(AFX_MAINTHREAD_H__4C21F270_F37B_4A1B_9B99_69C8175E9054__INCLUDED_)
#define AFX_MAINTHREAD_H__4C21F270_F37B_4A1B_9B99_69C8175E9054__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// MainThread thread

class MainThread : public CWinThread
{
	DECLARE_DYNCREATE(MainThread)
protected:
	MainThread();           // protected constructor used by dynamic creation

// Attributes
public:
	DownloadData m_DownData;
	CString str_ProjectName;
	CString str_BeginURL;
	bool m_bDone;
	bool m_chinese;
	CString str_Confine;
// Operations
public:

	bool TrimString(LPTSTR,UINT &,UINT &,bool);
	void Run(CString &);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MainThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~MainThread();

	// Generated message map functions
	//{{AFX_MSG(MainThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINTHREAD_H__4C21F270_F37B_4A1B_9B99_69C8175E9054__INCLUDED_)
