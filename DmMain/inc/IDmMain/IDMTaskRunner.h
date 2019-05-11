// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	IDMTaskRunner.h
// File mark:   
// File summary:ʵ��������QT�Ŀ��߳��¼���
// ����һ��ί�м�����ʽ,0. DMSolt������ԭ��Ϊbool fun(const DMEventSender& sender, const DMBundle& args), fun����Ϊȫ�ֻ����Ա����
//                      1. �û�ͨ��ConnectEvent,ConnectUiEvent,ConnectAsyncEventԤ�Ȱ�lpszEventName----DMSolt����
//						2. �û�ͨ��FireEvent����lpszEventName������DMSolt��������
//                      3. DMSolt�����ĵ��ó���������ͬ�����첽����UI�߳�,����1�İ󶨷�ʽ������

// ʾ��:��A,IDMTaskRunner�ı���g_taskrunner(ȫ��)
//			  class A{
//						A(){g_taskrunner.ConnectEvent(DMTT_ASYN_UI,"123",DMSolt(&A::fun, this));}
//						bool fun(const DMEventSender& sender, const DMBundle& args);}
//            ���������A�Ĺ��캯����Ԥ�Ȱ���DMSolt,֮��,��������봦����event.FireEvent("123")�����ᴥ����UI�߳����첽����fun����
//             
//      ��B���г�Ա����void UiFun(int a, CStringW b, double c);
//            g_taskrunner.PostTask(DMTT_ASYN_UI,DMNewRunnableMethod(&B::UiFun, this, 10, str , 5.67)),�ͻ���UI�߳��д����첽����UiFun
//            g_taskrunner.PostTask(DMTT_ASYN_WORK,DMNewRunnableMethod(&B::UiFun, this, 10, str , 5.67)),�ͻ���UI�߳��д����첽����UiFun
// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2019-03-02
// ----------------------------------------------------------------
#pragma once
#include "DMTaskT.h"

namespace DM
{
	enum DMTaskType
	{
		DMTT_SYNC,		///< ͬ������Task											
		DMTT_ASYN_UI,	///< ��UI�߳����첽����Task
		DMTT_ASYN_WORK,	///< �ڹ����߳����첽����Task
	};

	/// <summary>
	///		���߳��¼��󶨶�����չ�ӿ�,classtype=<see cref="DMREG_Event"/>
	/// </summary>
	class IDMTaskRunner : public DMBase
	{
		DMDECLARE_CLASS_NAME(IDMTaskRunner,L"IDMEvent",DMREG_TaskRunner);
	public:
		virtual DMCode InitEvent(DWORD dwUIThreadId) = 0;											     ///< ��ʼ����ָ��UI�߳�ID,���е�UI TASK����Post�����̴߳���,�˺���Ҫ����UI�߳��н��г�ʼ��
		virtual DMCode UninstallEvent() = 0;															 ///< ����ʼ��
		virtual bool   IsEventExists(LPCWSTR lpszEventName) = 0;										 ///< �¼��Ƿ��Ѵ���
		virtual DMCode RemoveEvent(LPCWSTR lpszEventName) = 0;											 ///< �Ƴ�ĳ���¼���Ӧ���¼���
		virtual DMCode RemoveEventIfThis(void* pThis) = 0;												 ///< �Ƴ�ĳ����������й����¼���(��������̬��Ա����)
		virtual DMCode RemoveAllEvents() = 0;															 ///< �Ƴ������¼���
		virtual DMCode ConnectEvent(DMTaskType tty, LPCWSTR lpszEventName, const DMSlot& slot, int group = 100) = 0;///< ��һ���¼���,���¼�����FireEventʱ(ͬ��,�첽UI�߳�,�첽�����߳�)����,ͬһ��lpszEventName,groupԽ��Խ�ٵ���(���ȼ�Խ��,group�ڲ���ת����ֵ)
		virtual DMCode FireEvent(LPCWSTR lpszEventName) = 0;											  ///< �����󶨵��¼���
		virtual DMCode FireEvent(LPCWSTR lpszEventName, DMBundle& args) = 0;							  ///< �������,�����󶨵��¼���

		virtual DMCode PostTask(DMTaskType tty, IDMTaskPtr pTask) = 0;                                    ///< ����󶨣�ֱ�Ӱ�һ������Post��(ͬ��,�첽UI�߳�,�첽�����߳�)����
	};

}//namespace DM