////////////////////////////////////////////////////
//���������:LWZС�� ���˶� 00348231
//��Ŀ������ʵϰ-��������-���绯����
//�������ڣ�2004-12-10
//���һ���޸����ڣ�2004-12-26
//�����ƣ�DownloadData
//��������Ŀ�ģ�
//	���湤��������Ϣ��ÿ�������̹߳���������������URL���У���ǰ�߳������ȵ�
//�����ԣ�
//private
//	CCriticalSection criSection;	�ٽ�������

//	UINT uMaxSizeOfContainer;		URL�����������
//	UINT uMaxThreadNum;				����߳���Ŀ
//	CString URLcontainer[4000];		URL���У�����ʵ�֣�

//	UINT uCur_URLnum;				��ǰURL����
//	UINT uCur_URLptr;				URL����ͷ��ָ��
//	UINT uCur_Fileid;				��ǰ�����ļ����
//	UINT uCur_ActiveThread;			��ǰ��߳�����

//	CString str_LocalDir;			���ش���Ŀ¼
//���к��������ܣ�
//	DownloadData();
//	virtual ~DownloadData();

//	bool IsFull();					�Ƿ�URL�����Ѿ�����
//	bool IsExisted(CString &);		�Ƿ�URL�Ѿ������ڶ�����
//	bool IsEmpty();					�Ƿ�URL���п��ˣ���δ�����URL��

//	UINT GetMaxThreadnum();			�������߳���Ŀ
//	UINT GetCurThread();			��õ�ǰ����߳���Ŀ
//	bool DeleThread();				�߳̽����󣬴�������ɾ��һ���̼߳�¼���ɹ�����true
//	bool AddThread();				�߳̿�ʼ�������������һ���̼߳�¼,�ɹ�����true

//	bool AddURL(CString &);			����������URL����β���һ��URL
//	bool GetCurURL(CString &);		�ӹ���������URL����ͷȡ��һ��URL

//	void GetFileName(CString &);	��õ�ǰ���ش洢�ļ��ĵ�ַ
//	bool SetPro(UINT,UINT,CString &);	�����û��趨��ʼ�ļ����ƣ�����߳�����������·��
//	void showURL();					��ʾURL��������(������)
//��������Ĺ�ϵ��
//	���û�������MainThread�̵��ã�����һ�����̵Ĺ������������Ӷ�ʵ�ֶ��߳���������
////////////////////////////////////////////////////
// DownloadData.h: interface for the DownloadData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOWNLOADDATA_H__0D70A93F_DC0C_41FD_B4B7_CC3756B176D0__INCLUDED_)
#define AFX_DOWNLOADDATA_H__0D70A93F_DC0C_41FD_B4B7_CC3756B176D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class DownloadData  
{
private:
	CCriticalSection criSection;

	UINT uMaxSizeOfContainer;
	UINT uMaxThreadNum;
	CString URLcontainer[4000];

	UINT uCur_URLnum;
	UINT uCur_URLptr;
	UINT uCur_Fileid;
	UINT uCur_ActiveThread;

	CString str_LocalDir;

public:
	DownloadData();
	virtual ~DownloadData();

	bool IsFull();
	bool IsExisted(CString &);
	bool IsEmpty();
	

	UINT GetCurThread();
	bool DeleThread();
	bool AddThread();
	UINT GetMaxThreadnum();
	
	bool AddURL(CString &);
	bool GetCurURL(CString &);
	
	void GetFileName(CString &);
	bool SetPro(UINT,UINT,CString &);

	void showURL();
};

#endif // !defined(AFX_DOWNLOADDATA_H__0D70A93F_DC0C_41FD_B4B7_CC3756B176D0__INCLUDED_)
