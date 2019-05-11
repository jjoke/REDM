//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: WidgetWnd.h 
// File Des: ����Widget��������
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-4-20	1.0		
//-------------------------------------------------------
#pragma once
#include "DUIWebkit.h"
#include "AttributeTestWnd.h"
#include "DMScriptHelper.h" 
class CWidgetWnd:public DMHWnd, public IDMWebEvent
{
public: 
	CWidgetWnd();
	DECLARE_MESSAGE_MAP()// ��MFC��Ϣӳ���
	DECLARE_EVENT_MAP()

	//---------------------------------------------------
	// Function Des: ��Ϣ�ַ�ϵ�к���
	//---------------------------------------------------
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
	void OnSize(UINT nType, CSize size);
	void OnCommand(UINT uNotifyCode, int nID, HWND wndCtl);// �˵�����

	//---------------------------------------------------
	// Function Des: �¼��ַ�ϵ�к���
	//---------------------------------------------------
	DMCode OnClose();
	DMCode OnMaximize();
	DMCode OnRestore();
	DMCode OnMinimize();
	DMCode OnBtnMenu();
	DMCode OnAttrTest();
	DMCode OnEditChange(DMEventArgs *pEvt);
	DMCode OnEditRButtonMenu(DMEventArgs *pEvt);
	DMCode ListCtrlExHeaderClick(DMEventArgs* pEvt);

	
	// Webkit����
	DMCode OnBtnWebBack();
	DMCode OnBtnWebRefresh(); 
	DMCode OnBtnWebfront();
	DMCode RefreshWeb(DMEventArgs* pEvent);
	static void OnTitleChanged(const DMClientHandler*, DMString title);
	static void OnURLChanged(const DMClientHandler*, DMString url);

	// IE����
	HRESULT NavigateComplete2(DUIWND hWnd,DMIN IDispatch *pDisp,DMIN wchar_t *pUrl);

	DMCode OnFireEvent(DMEventArgs &Evt);
	void OnDUITimer(char id);

public:
	DUIWebKit*					    m_pWebkit;
	DMClientHandler					m_handler;// ������ȫ�ֵģ���Ȼ���
	IDUIWeb*						m_pIE;
	DMSmartPtrT<CAttributeTestWnd>	m_pAttrTestWnd;
	DMScriptHelper                  m_ScriptHelper; 
};