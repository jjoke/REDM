//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: SkinWnd.h 
// File Des:  �����Ӵ��ڲ���
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-4-16	1.0		
//-------------------------------------------------------
#pragma once
#include "WndShadow.h"
class CQQMainWnd;
class CSkinWnd:public DMHWnd
{
public:
	CSkinWnd(CQQMainWnd*pOwner);

	//---------------------------------------------------
	// Function Des: ��Ϣ�ַ�ϵ�к���
	//---------------------------------------------------
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
	int OnCreate(LPVOID);
	void OnSize(UINT nType, CSize size);
	void OnShowWindow(BOOL bShow, UINT nStatus);
	//---------------------------------------------------
	// Function Des: �¼��ַ�ϵ�к���
	//---------------------------------------------------
	DMCode OnClose();
	DMCode OnOutSkin();
protected:
	DECLARE_MESSAGE_MAP()// ��MFC��Ϣӳ���
	DECLARE_EVENT_MAP()

public:
	CWndShadow								m_WndShadow;
	CQQMainWnd*								m_pMainWnd;
	wchar_t									m_szCurThemes[100];
};
