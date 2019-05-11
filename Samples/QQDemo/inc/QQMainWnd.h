//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: MainWnd.h 
// File Des: ������
// File Summary: 
// Cur Version: 1.0
// Author: 
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-4-7	1.0		
//-------------------------------------------------------
#pragma once
#include "WndShadow.h"
#include "SkinWnd.h"
#include "SpyWnd.h" 
#include "WidgetWnd.h"

class CQQMainWnd:public DMHWnd
{
public:
	CQQMainWnd();
	~CQQMainWnd();
	DECLARE_MESSAGE_MAP()						// ��MFC��Ϣӳ��꣬Ҳ����ʹ��BEGIN_MSG_MAPT��ʹ��Ϣ������ͷ�ļ�
	DECLARE_EVENT_MAP()							// �¼��ַ�ӳ���,Ҳ����ʹ��BEGIN_EVENT_MAPT��ʹ�¼�������ͷ�ļ�

	//---------------------------------------------------
	// Function Des: ��Ϣ�ַ�ϵ�к���
	//---------------------------------------------------
	int OnCreate(LPVOID);
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
	void OnSize(UINT nType, CSize size);	
	void OnShowWindow(BOOL bShow, UINT nStatus);
	LRESULT OnShowTrayMenu(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void OnCommand(UINT uNotifyCode, int nID, HWND wndCtl);// �˵�����

	//---------------------------------------------------
	// Function Des: �¼��ַ�ϵ�к���
	//---------------------------------------------------
	DMCode OnClose();
	DMCode OnMinimize();
	DMCode OnNameEditBtn();
	DMCode OnSkin();
	DMCode OnSpy();
	DMCode OnWidget();

	//
	DMCode OnNameEditKillFocus(DMEventArgs* pEvent);
	DMCode OnSubListTree(DMEventArgs* pEvent);
	DMCode OnSubListEx(DMEventArgs* pEvent);

public:
	CWndShadow								m_WndShadow;
	DUIListBoxEx*                           m_pListEx;
	DUITreeCtrl*                            m_pSubListTree[3];
	DUIListBoxEx*                           m_pSubListEx[3];

public:
	DMSmartPtrT<CSkinWnd>					m_pSkinWnd;
	DMSmartPtrT<CSpyWnd>                    m_pSpyWnd;
	DMSmartPtrT<CWidgetWnd>                 m_pWidgetWnd;
};