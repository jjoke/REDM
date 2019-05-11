//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMMsgLoop.h 
// File Des:
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-12	1.0			
//-------------------------------------------------------
#pragma once

namespace DM
{
	/// <summary>
	///		������Ϣ�ַ�������atlapp.CMessageLoop
	/// </summary>
	/// <remarks>
	///		����smartָ����ƣ���Ϊһ���߳̿��ܶ�������ڵ���Run
	/// </remarks>
	class DM_EXPORT DMMsgLoop:public DMRefNum
	{
	public:
		DMMsgLoop();
		~DMMsgLoop();
	public:
		/// -------------------------------------------------
		/// @brief			��ʼ��Ϣѭ��
		/// @return			Msg.Wparam
		virtual int Run();

		/// -------------------------------------------------
		/// @brief			����Ԥ������Ϣ
		/// @param[in]		pMessageFilter		����<see cref="IDMMessageFilter"/>
		/// @return			TRUE:�ɹ�,False:ʧ��
		BOOL AddMessageFilter(IDMMessageFilter* pMessageFilter);

		/// -------------------------------------------------
		/// @brief			�Ƴ�Ԥ������Ϣ
		/// @param[in]		pMessageFilter		����<see cref="IDMMessageFilter"/>
		/// @return			TRUE:�ɹ�,False:ʧ��
		BOOL RemoveMessageFilter(IDMMessageFilter* pMessageFilter);

		/// -------------------------------------------------
		/// @brief			���ӿ��д�����Ϣ
		/// @param[in]		pIdleHandler		����<see cref="IDMIdleHandler"/>
		/// @return			TRUE:�ɹ�,False:ʧ��
		BOOL AddIdleHandler(IDMIdleHandler* pIdleHandler);

		/// -------------------------------------------------
		/// @brief			�Ƴ����д�����Ϣ
		/// @param[in]		pIdleHandler		����<see cref="IDMIdleHandler"/>
		/// @return			TRUE:�ɹ�,False:ʧ��
		BOOL RemoveIdleHandler(IDMIdleHandler* pIdleHandler);

	public:
		/// -------------------------------------------------
		/// @brief			��ϢԤ���˺���
		/// @remark         �����أ��Ӷ��ı���Ϣ����
		/// @param[in]		pMsg		����<see cref="MSG"/>
		/// @return			TRUE:�ɹ�,False:ʧ��
		virtual BOOL PreTranslateMessage(MSG* pMsg);

		/// -------------------------------------------------
		/// @brief			����Ԥ������
		/// @remark         �����أ��Ӷ��ı���Ϣ����
		/// @return			TRUE:�ɹ�,False:ʧ��
		virtual BOOL OnIdle(int /*nIdleCount*/);

	public:
		static BOOL IsIdleMessage(MSG* pMsg);

	public:
		typedef CList<IDMMessageFilterPtr>	    IDMMessageFilterList;
		typedef CList<IDMIdleHandlerPtr>        IDMIdleHandlerList;
		IDMMessageFilterList					m_MsgFilterList;				
		IDMIdleHandlerList						m_IdleHandlerList;
		
		MSG										m_msg;
		DMLock*								    m_pMsgLock;
		DMLock*                                 m_pIdleLock;

	};

	/// <summary>
	///		����<see cref="DMMsgLoop"/>����,����atlapp.CAppModule
	/// </summary>
	/// <remarks>
	///		�����<see cref="DMMsgLoop"/>������ʹ��new ���䣬smartָ��������ü���Ϊ0ʱ�Զ��ͷ�
	/// </remarks>
	class DM_EXPORT DMMsgLoopTool
		:public DMMapT<DWORD, DMMsgLoop*>
	{
	public:
		DMMsgLoopTool();
		virtual~DMMsgLoopTool();

		/// -------------------------------------------------
		/// @brief			����Loop����
		/// @remark         ����ʹ��new���䣬��ΪDMMsgLoop�ǻ�������ָ�����
		/// @return			true:�ɹ�,false:ʧ��
		bool AddMessageLoop(DMMsgLoop* pMsgLoop);		
		bool RemoveMessageLoop();											 ///< �Ƴ���ǰ�߳�loop����
		DMMsgLoop* GetMessageLoop(DWORD dwThreadID = ::GetCurrentThreadId());///< ��ȡ��ǰ�߳�loop����
		void Term();

	protected:
		DWORD							m_dwMainThreadID;					///< ���߳�ID
		DMLock							m_Lock;

	};

}//namespace DM