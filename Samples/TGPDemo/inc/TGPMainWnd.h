// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved. 
// 
// File name:	TGPMainWnd.h
// File mark:   
// File summary: 

// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2016-4-21
// ----------------------------------------------------------------
#pragma once  
 
class CTGPMainWnd:public DMHWnd
{ 
public:
	DECLARE_MESSAGE_MAP()						// ��MFC��Ϣӳ��꣬Ҳ����ʹ��BEGIN_MSG_MAPT��ʹ��Ϣ������ͷ�ļ�
	DECLARE_EVENT_MAP()							// �¼��ַ�ӳ���,Ҳ����ʹ��BEGIN_EVENT_MAPT��ʹ�¼�������ͷ�ļ�

	//---------------------------------------------------
	// Function Des: ��Ϣ�ַ�ϵ�к���
	//---------------------------------------------------
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
	LRESULT OnHoldMenu(UINT uMsg, WPARAM wParam, LPARAM lParam);	

	//---------------------------------------------------
	// Function Des: �¼��ַ�ϵ�к���
	//---------------------------------------------------
	DMCode OnClose();
	DMCode OnMinimize();
	DMCode OnMenu();
	DMCode OnListBoxEx(DMEventArgs *pEvt);

public:
	 TGPMenu		m_CfMenu;
};