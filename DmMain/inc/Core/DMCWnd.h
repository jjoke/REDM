//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMCWndBase.h 
// File Des: ��ʵ��CWnd��ͬʱ֧��trunk���ڹ���
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-13	1.0			
//-------------------------------------------------------
#pragma once
namespace DM
{
	/// <summary>
	///		����thunk����Ϣ�ַ������ں�����װ��
	/// </summary>
	class DM_EXPORT DMCWnd:public DMCWndBase		// ��װCWnd
						  ,public DMMsgThunkTool	// trunk����
						  ,public IDMMsgMap			// ��Ϣ�ַ�
	{
	public:
		enum{DMSTATE_DESTROYED = 0x00000001};  
	public:
		DMCWnd();
		virtual ~DMCWnd();

	public:
		/// -------------------------------------------------
		/// @brief			��������
		/// @param[in]		lpClassName		����
		/// @param[in]		lpWindowName	������
		/// @param[in]		dwStyle			��ʽ
		/// @param[in]		dwExStyle		��չ��ʽ
		/// @param[in]		x				x����
		/// @param[in]		y				y����
		/// @param[in]		nWidth			���
		/// @param[in]		nHeight			�߶�
		/// @param[in]		hWndParent		������
		/// @param[in]		lpParam			Long pointer to a value to be passed to the window through the CREATESTRUCT structure passed in the lParam parameter the WM_CREATE message	
		/// @return			HWND
		HWND CreateWindowEx(LPCWSTR lpClassName, LPCWSTR lpWindowName,DWORD dwStyle, DWORD dwExStyle, 
			int x, int y, int nWidth, int nHeight, HWND hWndParent, PVOID lpParam); 

		/// -------------------------------------------------
		/// @brief			��������ǰ����
		/// @param[in]		hWnd			���ھ��
		/// @remark         �����أ��������ش���
		/// @return			��
		virtual void OnFinalMessage(HWND hWnd);		

		BOOL SubclassWindow(HWND hWnd);
		HWND UnsubclassWindow(BOOL bForce = FALSE);

	public:
		DECLARE_MSG_MAP();// ����ProcessWindowMessage
		static LRESULT CALLBACK FirstWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT DefWindowProc();
		virtual LRESULT DefWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

		// copy from atlwin
		LRESULT ForwardNotifications(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT ReflectNotifications(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		static BOOL DefaultReflectionHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult);

	public:
		const MSG*					 m_pCurrentMsg;                            // ��ATL
		WNDPROC						 m_pfnSuperWindowProc;		
		DWORD						 m_dwState;                                // �Ƿ�destory
		BOOL						 m_bMsgHandled;

		static DMCWnd*				 ms_pThis;
	};

}//namespace DM