// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	ResHelper.h
// File mark:   
// File summary:����Res�����ļ�
// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2016-7-8
// ----------------------------------------------------------------
#pragma once
namespace DM
{

#define MAX_RES_TYPE        30						 //��Դ����Ԥ���壬��󳤶Ȳ�����30
#define MAX_RES_NAME        100						 //ע�⣺����Դ����ʱ����󳤶Ȳ�Ҫ����MAX_RES_NAME
#define DMRES_DMINDEX		   _T("dmindex.xml")    //�ļ�����Դ���ļ�ӳ����������ļ���
#define DMRES_THEMES_FOLDER    _T("\\themes\\")
#define DMRES_LAYOUT_FOLDER    _T("\\layout\\")

	/// <summary>
	///		����Res���������
	/// </summary>
	class ResItem
	{
	public:
		ResItem(LPCWSTR lpszType=L"", LPCWSTR lpszName=L"", LPCWSTR lpszPath = L"");

	public:
		wchar_t m_szType[MAX_RES_TYPE+1];			///< ��Դ����,��png,jpg,bmp,gif,flash
		wchar_t m_szName[MAX_RES_NAME+1];           ///< ��Դ��,ͬһ��Դ������Ψһ��ʶ����Դ��
		wchar_t m_szPath[MAX_PATH];                 ///< ��Դȫ·��
	};

	typedef ResItem* ResItemPtr;

	/// <summary>
	///		����ResFolderʹ�õ�Array
	/// </summary>
	class ResFolderItem:public DMRefNum
						 ,public DMArrayT<ResItemPtr>
	{
	public:
		ResFolderItem(){}
		virtual ~ResFolderItem();
	public:
		virtual void PreArrayObjRemove(const ResItemPtr &obj);
		virtual bool EqualArrayObj(const ResItemPtr &objsrc, const ResItemPtr &objdest);
	public:
		CStringW        m_strThemeName;			 ///< ���������
	};
	typedef ResFolderItem* ResFolderItemPtr;

}//namespace DM