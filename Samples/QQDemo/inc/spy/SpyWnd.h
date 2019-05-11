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
//      guoyou		2015-2-2	1.0		
//-------------------------------------------------------
#pragma once
#include "SpyFindBtn.h"

class CSpyWnd:public DMHWnd
{
public:
	CSpyWnd();	
	~CSpyWnd();
	DECLARE_MESSAGE_MAP()// ��MFC��Ϣӳ���
	DECLARE_EVENT_MAP()

	//---------------------------------------------------
	// Function Des: ��Ϣ�ַ�ϵ�к���
	//---------------------------------------------------
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
	void OnDUITimer(char id);

	//---------------------------------------------------
	// Function Des: �¼��ַ�ϵ�к���
	//---------------------------------------------------
	DMCode OnClose();
	DMCode OnMinimize();
	DMCode OnSpyInitEvent(DMEventArgs *pEvt);
	DMCode OnTreeSelChanged(DMEventArgs *pEvt);


public:// ����
	void InitTreeCtrl(HWND hRootWnd);
	void InsertTreeItem(DMXmlNode &XmlNode,HDMTREEITEM hParentItem);
	void ReflashEditInfo();
	bool HitTest(RECT &rc);

public:
	DUITreeCtrl*            m_pTreeCtrl;
	DUIRichEdit*            m_pTreeEdit;
	DUIStatic*              m_pSearchSta;
	PDMSpyEnum              m_pSpyEnum;
	HWND                    m_hRootWnd;
	bool                    m_bInit;

	// ����
	bool                    m_bHittest;
	bool                    m_bDraw;
	CRect                   m_rcDraw;

};