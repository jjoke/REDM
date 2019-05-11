// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	ResFolder.h
// File mark:   
// File summary:
// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2016-7-8
// ----------------------------------------------------------------
#pragma once
#include "ResHelper.h"

namespace DM
{
	/// <summary>
	///		����Res����ļ���Ϊ���½ṹ:�������ò����������󣬿����Լ��޸�һ�ݣ��Լ�ע���ȥ
	///     Res�ļ��а����������ļ��У�1.layout�ļ��� 2.themes�ļ���
	///		1.1.layout�ļ��ж��������в���xml��skin��style��ȫ��xml
	///     2.1.themes�ļ����¶����˶�������
	///     3.ÿ���ļ����¾���һ��dmindex.xml����ʶ��Դ����
	/// </summary>
	class  ResFolder:public IDMRes,public DMArrayT<ResFolderItemPtr>
						 //,public DMMapT<CStringW,ResFolderItemPtr>// themes���б�Map
	{
		DMDECLARE_CLASS_NAME(ResFolder,L"ResFolder",DMREG_Res);
	public:
		ResFolder();
		~ResFolder();
	public:
		virtual DMCode LoadResPack(WPARAM wp, LPARAM lp);
		virtual DMCode IsItemExists(LPCWSTR lpszType, LPCWSTR lpszName,LPCWSTR lpszThemeName=NULL);
		virtual DMCode GetItemSize(LPCWSTR lpszType, LPCWSTR lpszName, unsigned long& ulSize,LPCWSTR lpszThemeName=NULL);
		virtual DMCode GetItemBuf(LPCWSTR lpszType, LPCWSTR lpszName, LPVOID lpBuf, unsigned long ulSize,LPCWSTR lpszThemeName=NULL);
		virtual DMCode LoadTheme(WPARAM wp, LPARAM lp);
		virtual DMCode SetCurTheme(LPCWSTR lpszName, LPCWSTR lpszOldName=NULL);
		virtual DMCode SendExpandInfo(WPARAM wp, LPARAM lp);  ///< lpΪ0ʱ���ѳ��ȸ�ֵ��*wp

	public:// ����
		DMCode ParseThemes(LPCWSTR lpszIndexPath);
		DMCode ParseIndex(LPCWSTR lpszIndexPath,ResFolderItem** ppItem);
		LPCWSTR GetItemPath(LPCWSTR lpszType,LPCWSTR lpszName,LPCWSTR lpszThemeName);
		ResFolderItemPtr FindResItemObj(LPCWSTR lpszName);
		DMCode RemoveResItem(LPCWSTR lpszType,LPCWSTR lpszName,LPCWSTR lpszThemeName);
		DMCode AddResItem(LPCWSTR lpszType,LPCWSTR lpszName,LPCWSTR lpszPath,LPCWSTR lpszThemeName);

	protected:
		virtual void PreArrayObjRemove(const ResFolderItemPtr &obj);

	public:
		DM_BEGIN_ATTRIBUTES()
			DM_bool_ATTRIBUTE(L"bloop", m_bThemeLoop, DM_ECODE_OK)
			DM_STRING_ATTRIBUTE(L"name", m_strCurTheme, DM_ECODE_OK)
			DM_bool_ATTRIBUTE(L"boutstyle", m_bOutStyle, DM_ECODE_OK)
			DM_bool_ATTRIBUTE(L"bassert",m_bAssert, DM_ECODE_OK)
		DM_END_ATTRIBUTES()
	
	public:
		DM::CStringW                          m_strDir;
		DM::CStringW                          m_strCurTheme;       // ��ǰʹ�õ�theme Key
		ResFolderItemPtr			          m_pCurTheme;         // ��ǰʹ�õ�theme
		bool                                  m_bThemeLoop;        // �Ƿ�����ѭ������theme(��ǰtheme���Ҳ�����Դ,ֱ��ȥ����theme�в���)
		bool                                  m_bOutStyle;         // ��ǰ���ⲿģʽ���ⲿǿ�Ƹı���skin�ص����ݣ���ʱ���е�themeӦ�ö���Ҫˢ��)
		bool                                  m_bAssert;		   // �Ƿ���debug��������
		DMSmartPtrT<ResFolderItem>			  m_pLayout;		   // Layout���б�
		
	};

}//namespace DM