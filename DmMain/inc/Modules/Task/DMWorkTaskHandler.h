// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	DMWorkTaskHandler.h
// File mark:   
// File summary:����һ���߳�,��������Task
// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2019-3-1
// ----------------------------------------------------------------
#pragma once

namespace DM
{
	/// <summary>
	///		�����̴߳���Task������ʵ��
	/// </summary>
	class DMWorkTaskHandler : public DMRefNum
	{
	public:
		DMWorkTaskHandler();
		~DMWorkTaskHandler();
	public:
		DMCode InitTasks(DWORD dwTimeOut = INFINITE);		
		DMCode RunTasks();		                                
		DMCode StopTasks();		                                   
		DMCode AddTask(IDMTaskPtr pTask, bool bExec=true);			
		DMCode ExecTask(bool bSync=false, DWORD dwTimeOut=INFINITE);   
		bool BelongsToThread(DWORD dwThreadId);

	public:// ����
		bool InitTasksThread();
		DWORD RunTasksThread();
		bool UnInitTasksThread();
		bool IsTaskRunning();

		bool DealWithMessage();
		void GetNewTaskList();
		void DealWithTaskList();
		bool DestroyTasks();

	public:
		virtual void OnStart();
		static unsigned int WINAPI s_ThreadProc(LPVOID lp);

	public:
		HANDLE										m_hThread;				///< �߳̾��
		typedef DM::CList<IDMTaskPtr>				t_lstTaskQueue;
		t_lstTaskQueue								m_TaskWaitList;			///< ��������������
		t_lstTaskQueue								m_TaskRunList;			///< ���ڴ�����������
		DMLock										m_TaskLocker;			///< ������
		DMLock*										m_pThreadLocker;        ///< �߳���
		HANDLE										m_hTaskWaitEvent;		///< �ȴ����������¼�
		HANDLE										m_hTaskFinishEvent;		///< �ȴ�����������¼�
		DWORD										m_dwThreadId;			///< ���̵߳�ID
		bool										m_bRunning;				///< �Ƿ���������
		volatile bool								m_bExitTaskThread;	    ///< �Ƿ��˳�
		DWORD										m_dwTimeOut;			///< �����̳߳�ʱʱ��
	};
}//namespace DM