// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	TGPLoginWnd.h
// File mark:   
// File summary:

// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2016-5-20
// ----------------------------------------------------------------
#pragma once  

class CTGPLoginWnd:public DMHWnd
{ 
public:
	DECLARE_MESSAGE_MAP()						// ��MFC��Ϣӳ��꣬Ҳ����ʹ��BEGIN_MSG_MAPT��ʹ��Ϣ������ͷ�ļ�
	DECLARE_EVENT_MAP()							// �¼��ַ�ӳ���,Ҳ����ʹ��BEGIN_EVENT_MAPT��ʹ�¼�������ͷ�ļ�


	//---------------------------------------------------
	// Function Des: ��Ϣ�ַ�ϵ�к���
	//---------------------------------------------------
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);

	//---------------------------------------------------
	// Function Des: �¼��ַ�ϵ�к���
	//---------------------------------------------------
	DMCode OnClose();
	DMCode OnMinimize();
};