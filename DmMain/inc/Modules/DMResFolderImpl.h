//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMResFolderImpl.h 
// File Des: 
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-7	1.0			
//-------------------------------------------------------
#pragma once
#include "DMResHelper.h"

namespace DM
{
	/// <summary>
	///		����Res����ļ���Ϊ���½ṹ:�������ò����������󣬿����Լ��޸�һ�ݣ��Լ�ע���ȥ
	///     Res�ļ��а����������ļ��У�1.layout�ļ��� 2.themes�ļ���
	///		1.1.layout�ļ��ж��������в���xml��skin��style��ȫ��xml
	///     2.1.themes�ļ����¶����˶�������
	///     3.ÿ���ļ����¾���һ��dmindex.xml����ʶ��Դ����
	/// </summary>
	class DM_EXPORT DMResFolderImpl:public IDMRes,public DMArrayT<DMResFolderItemPtr>
						 //,public DMMapT<CStringW,DMResFolderItemPtr>// themes���б�Map
	{
		DMDECLARE_CLASS_NAME(DMResFolderImpl,L"DMResFolderImpl",DMREG_Res);
	public:
		DMResFolderImpl();
		~DMResFolderImpl();
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
		DMCode ParseIndex(LPCWSTR lpszIndexPath,DMResFolderItem** ppItem);
		LPCWSTR GetItemPath(LPCWSTR lpszType,LPCWSTR lpszName,LPCWSTR lpszThemeName);
		DMResFolderItemPtr FindResItemObj(LPCWSTR lpszName);

	protected:
		virtual void PreArrayObjRemove(const DMResFolderItemPtr &obj);

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
		DMResFolderItemPtr			          m_pCurTheme;         // ��ǰʹ�õ�theme
		bool                                  m_bThemeLoop;        // �Ƿ�����ѭ������theme(��ǰtheme���Ҳ�����Դ,ֱ��ȥ����theme�в���)
		bool                                  m_bOutStyle;         // ��ǰ���ⲿģʽ���ⲿǿ�Ƹı���skin�ص����ݣ���ʱ���е�themeӦ�ö���Ҫˢ��)
		bool                                  m_bAssert;		   // �Ƿ���debug��������
		DMSmartPtrT<DMResFolderItem>		  m_pLayout;		   // Layout���б�
		
	};

}//namespace DM