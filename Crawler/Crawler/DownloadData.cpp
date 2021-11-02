////////////////////////////////////////////////////
//���������:LWZС�� ���˶� 00348231
//��Ŀ������ʵϰ-��������-���绯����
//�������ڣ�2004-12-10
//���һ���޸����ڣ�2004-12-26
//
// DownloadData.cpp: implementation of the DownloadData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NetCrawler.h"

#include "afxmt.h"
#include "DownloadData.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DownloadData::DownloadData()
{
	uCur_URLnum=0;				//��ʼ����ǰ������URL����Ϊ0
	uMaxSizeOfContainer=4000;	//URL�����������
	uCur_URLptr=0;				//��ǰ����ͷ��ָ��
	uCur_ActiveThread=0;		//��ǰ��߳�����Ϊ0
	uMaxThreadNum=10;			//��ʼ���߳���Ŀ10
	uCur_Fileid=1;				//��ʼ�������ļ�����Ϊ1
	str_LocalDir="C:\\";		//��ʼ�������ļ�Ŀ¼ΪC:
}


DownloadData::~DownloadData()
{
}
//�Ƿ�URL�����Ѿ�����
bool DownloadData::IsEmpty()
{
	criSection.Lock();
	bool r=(uCur_URLnum<=uCur_URLptr);
	criSection.Unlock();
	return r;
}
//�Ƿ�URL�Ѿ������ڶ�����
bool DownloadData::IsExisted(CString &str)
{
	criSection.Lock();
	for(UINT i=0;i<uCur_URLnum;i++)
	{
		if(URLcontainer[i]==str)
		{
			criSection.Unlock();
			return TRUE;
		}
	}
	criSection.Unlock();
	return FALSE;
}
//�Ƿ�URL���п��ˣ���δ�����URL��
bool DownloadData::IsFull()
{		
	criSection.Lock();
	bool r=(uCur_URLnum==uMaxSizeOfContainer);
	criSection.Unlock();
	return r;
}
//��õ�ǰ��߳���Ŀ
UINT DownloadData::GetCurThread()
{
	criSection.Lock();
	UINT n=uCur_ActiveThread;
	criSection.Unlock();
	return n;
}
//�������߳���Ŀ
UINT DownloadData::GetMaxThreadnum()
{
	return uMaxThreadNum;
}
//�߳̿�ʼ�������������һ���̼߳�¼,�ɹ�����true
bool DownloadData::AddThread()
{
	criSection.Lock();
	if(uCur_ActiveThread==uMaxThreadNum)
	{
		criSection.Unlock();
		return FALSE;
	}
	uCur_ActiveThread++;
	criSection.Unlock();
	return TRUE;
}
//�߳̽����󣬴�������ɾ��һ���̼߳�¼���ɹ�����true
bool DownloadData::DeleThread()
{
	criSection.Lock();
	if(uCur_ActiveThread==0)
	{
		criSection.Unlock();
		return FALSE;
	}
	uCur_ActiveThread--;
	criSection.Unlock();
	return TRUE;
}
//�ӹ���������URL����ͷȡ��һ��URL
bool DownloadData::GetCurURL(CString &str)
{
	criSection.Lock();
	if(uCur_URLptr>=uCur_URLnum)
	{
		criSection.Unlock();
		return FALSE;
	}
	str=URLcontainer[uCur_URLptr];
	uCur_URLptr++;
	criSection.Unlock();
	return TRUE;

}
//����������URL����β���һ��URL
bool DownloadData::AddURL(CString &str)
{
	criSection.Lock();
	if(uCur_URLnum==uMaxSizeOfContainer)
	{
		criSection.Unlock();
		return FALSE;
	}
	URLcontainer[uCur_URLnum]=str;
	uCur_URLnum++;
	criSection.Unlock();
	return FALSE;

}
//��õ�ǰ���ش洢�ļ��ĵ�ַ
void DownloadData::GetFileName(CString &str)
{
	criSection.Lock();
	CString str_temp;
	str_temp.Format("%d",uCur_Fileid);
	str=str_LocalDir+str_temp+".txt";
	uCur_Fileid++;
	criSection.Unlock();
}

//�����û��趨��ʼ�ļ����ƣ�����߳�����������·��
bool DownloadData::SetPro(UINT Fileid, UINT ThreadNum, CString &str)
{
	if(str[str.GetLength()-1]!='\\')
		str+="\\";
	str_LocalDir=str;
	uCur_Fileid=Fileid;
	uMaxThreadNum=ThreadNum;
	return TRUE;
}

//��ʾURL��������(������)
void DownloadData::showURL()
{
	for(UINT i=0;i<uCur_URLnum;i++)
	{
		AfxMessageBox(URLcontainer[i]);
	}

}
