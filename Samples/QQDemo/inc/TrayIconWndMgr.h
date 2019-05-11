// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	TrayIconWndMgr.h
// File mark:   ������̲˵���һ����װ
// File summary:
// Author:		lzlong
// Edition:     1.0
// Create date: 2016-11-11
// ----------------------------------------------------------------
#pragma once
#include <shellapi.h>

#define  WM_SHOWTRAYMENU     WM_USER + 1244
/// <summary>
///		�򵥵�����ʵ�ִ���
/// </summary>
class CTrayIconWndMgr : public DMCWnd, public DMSingletonT<CTrayIconWndMgr>
{
public:
	CTrayIconWndMgr();
	~CTrayIconWndMgr();

	/// -------------------------------------------------
	/// @brief			��װ����ͼ��
	/// @param[in]		lpszToolTip       ���̵���ʾ
	/// @param[in]		hParentWnd		  ���̵ĸ�����
	/// @param[in]		hIcon	          ��Ҫ���/�޸�/ɾ����ͼ����
	/// @param[in]		nID				  Ӧ�ó������������ͼ���ID			
	/// @return			true or false
	bool InstallTrayIcon(LPCWSTR lpszToolTip, HWND hParentWnd, HICON hIcon, UINT nID);

	/// -------------------------------------------------
	/// @brief			�Ƴ�����ͼ��
	bool UnInstallTrayIcon();

	/// -------------------------------------------------
	/// @brief			�����ı���ʾ,���á�����������ʾ
	bool SetTipText(LPCWSTR lpszTipText);
	bool SetBalloonDetails(LPCWSTR lpszBalloonText, LPCWSTR lpszBalloonCaption = NULL,UINT nTimeout = 1000, 
							DWORD style = NIIF_INFO, HICON hUserIcon = NULL, bool bNoSound = false);
	bool HideBalloon();

protected:
	LRESULT OnTrayIcon(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnTaskbarRestart(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/);

public:
	DECLARE_MESSAGE_MAP()	
	static DWORD StartTimeCheck(LPVOID lp);

public:
	NOTIFYICONDATA					  m_Nid;
	UINT							  m_CbMsg;
	UINT                              m_RestartMsg;

	HWND                              m_hParentWnd;
	bool                              m_bInstall;
	bool                              m_bExitBalloon;

	DWORD                             m_dwOldTime;

};