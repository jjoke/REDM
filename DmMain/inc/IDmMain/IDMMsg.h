//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: IDMMsg.h 
// File Des:
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-3-3	1.0			
//-------------------------------------------------------
#pragma once

namespace DM
{
	/// <summary>
	///		������ʵ������Ϣ�ַ��Ļ���
	/// </summary>
	class DM_EXPORT IDMMsgMap
	{
		// Ϊֱ����atl����Ϣ�꣬��������ֵ�ı�
		virtual BOOL ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
			LRESULT& lResult, DWORD dwMsgMapID) = 0;
	};

	/// <summary>
	///		��Ϣ���˻���
	/// </summary>
	/// <remarks>
	///		GetMessage֮���ȵ���PreTranslateMessage�������������TRUE����Ϣ���ݽ���!
	/// </remarks>
	class  DM_EXPORT IDMMessageFilter
	{
	public://
		IDMMessageFilter(){m_dwThreadId = ::GetCurrentThreadId();}
		virtual BOOL PreTranslateMessage(MSG* pMsg) = 0;
	public:
		DWORD              m_dwThreadId;
	};
	typedef IDMMessageFilter* IDMMessageFilterPtr;

	/// <summary>
	///		���д������
	/// </summary>
	class IDMIdleHandler
	{
	public:
		IDMIdleHandler(){m_dwThreadId = ::GetCurrentThreadId();}
		virtual BOOL OnIdle() = 0;
	public:
		DWORD              m_dwThreadId;
	};
	typedef IDMIdleHandler* IDMIdleHandlerPtr;
}