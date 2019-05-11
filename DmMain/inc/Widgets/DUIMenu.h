//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DUIMenu.h 
// File Des: 
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-3-10	1.0			
//--------------------------------------------------------
#pragma once
#include "DUIMenuHelper.h"

namespace DM
{
	/// <summary>
	///		 �˵����
	/// </summary>
	class DM_EXPORT DUIMenu:public DMCWnd
	{
	public:
		DUIMenu();
		~DUIMenu(void);

	public:// ������
		virtual DMMenuItemData* ParseItem(DMXmlNode& XmlItem);
		virtual DMMenuItemData* NewMenuItemData();
		virtual void DeleteMenuItemData(DMMenuItemData*pObj);
		virtual DUIMenuItem* NewMenuItem();

	public:
		bool LoadMenu(LPCWSTR lpszType,LPCWSTR lpszResName);								   ///< ͨ��ָ��xml��Դ����
		bool LoadMenu(DMXmlNode &XmlNode);													   ///< ͨ��xmlֱ�Ӽ���

	public:
		int TrackPopupMenu(UINT uFlags, int x, int y, HWND hWnd, LPCRECT lpRect=NULL);         ///< ���ص�ǰ�������һ��
		DUIMenu GetSubMenu(int nPos);
		bool InsertMenu(UINT nPosition, UINT nFlags, UINT_PTR nIDNewItem,LPCTSTR strText, int iIcon);
		void DestroyMenu();

	public:
		//---------------------------------------------------
		// Function Des: ��Ϣ�ַ�ϵ�к���
		//---------------------------------------------------
		void OnInitMenu(HMENU menu);															///< ��ʼ������TrackPopupMenu�д���
		void OnInitMenuPopup(HMENU menuPopup, UINT nIndex, BOOL bSysMenu);						///< ��ʼ������TrackPopupMenu�д���
		void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU menu);
		void OnMeasureItem(UINT /*wParam*/,LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	public:// ����
		void BuildMenu(HMENU menuPopup,DMXmlNode xmlNode);
		void InstallMenuHook();
		void UnInstallMenuHook();

	public:
		static LRESULT CALLBACK MenuHookProc(int iCode, WPARAM wParam, LPARAM lParam);

	public:// ����
		DECLARE_MSG_MAP()										// ��MFC��Ϣӳ���

	public:
		DMSmartPtrT<DUIMenu_XmlInfo>			m_pDUIMenuXmlInfo;
		DUIMenu*								m_pParent;
		HMENU									m_hMenu;
		DM::CArray<DMMenuItemData*>				m_DmmiArray;
	
		HWND									m_hMenuOwner;       ///< DUI����������
		HHOOK									m_hMenuHook;
		static DUIMenu*                         m_pThis;
	};
}//namespace DM