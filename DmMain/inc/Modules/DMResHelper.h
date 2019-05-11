//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMResHelper.h 
// File Des:  ����Res�����ļ�
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-19	1.0			
//-------------------------------------------------------
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
	class DM_EXPORT DMResItem
	{
	public:
		DMResItem(LPCWSTR lpszType=L"", LPCWSTR lpszName=L"", LPCWSTR lpszPath = L"");

	public:
		wchar_t m_szType[MAX_RES_TYPE+1];			///< ��Դ����,��png,jpg,bmp,gif,flash
		wchar_t m_szName[MAX_RES_NAME+1];           ///< ��Դ��,ͬһ��Դ������Ψһ��ʶ����Դ��
		wchar_t m_szPath[MAX_PATH];                 ///< ��Դȫ·��
	};

	typedef DMResItem* DMResItemPtr;

	/// <summary>
	///		����ResFolderʹ�õ�Array
	/// </summary>
	class DMResFolderItem:public DMRefNum
						 ,public DMArrayT<DMResItemPtr>
	{
	public:
		DMResFolderItem(){}
		virtual ~DMResFolderItem();
	public:
		virtual void PreArrayObjRemove(const DMResItemPtr &obj);
		virtual bool EqualArrayObj(const DMResItemPtr &objsrc, const DMResItemPtr &objdest);
	public:
		CStringW        m_strThemeName;			 ///< ���������
	};
	typedef DMResFolderItem* DMResFolderItemPtr;

}//namespace DM