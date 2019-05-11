//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMPlugin_Test.cpp 
// File Des: ���Կ��߳��¼��󶨵Ĳ�������
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-16	1.0			
//-------------------------------------------------------
#pragma once
#include "DMUintTestAfx.h"

enum DMEventNameId
{
	EVENTID_SYNC1,
	EVENTID_SYNC2,

	EVENTID_UI1,
	EVENTID_UI2,

	EVENTID_AYNC1,
	EVENTID_AYNC2,
};

class TaskRunnerTest:public::testing::Test,public DMRefNum
{
public:
	DMSmartPtrT<IDMTaskRunner> m_pTaskRunner;
	//DMDISABLE_RUNNABLE_METHOD_REFCOUNT(TaskRunnerTest);//ǿ�ƽ������ü���������������,����Ҫ,Ӧ�÷�����.h�ļ��У�����DMRefNum����,����Ҫ�˾䣬Ĭ��DM�ⶼ����DMRefNum

public:
	virtual void SetUp()
	{
		//1. ��ȡ����,���ַ�ʽ------------------------------------------------
		EXPECT_EQ(DMSUCCEEDED(g_pDMApp->GetDefRegObj((void**)&m_pTaskRunner,DMREG_TaskRunner)),true);// ʹ���ڲ��ѳ�ʼ����ɵ�TaskRunner����
		//EXPECT_EQ(DMSUCCEEDED(g_pDMApp->CreateRegObj((void**)&m_pTaskRunner,NULL, DMREG_TaskRunner)),true);// �Լ�����һ��TaskRunner���󣬵�Ҫ��UI�߳��е���InitEvent��ʼ��UI������
		//m_pTaskRunner->InitEvent(::GetCurrentThreadId());

		//2. ��ǰ�󶨣�ֻҪ��FireEvent֮ǰ�󶨼���---------------------------
		InitBind();
	}

	virtual void TearDown(){}
	virtual void OnFinalRelease(){}	
	~TaskRunnerTest(){m_RefCount = 0;}

public:// ����
	void InitBind()
	{
		if (m_pTaskRunner)
		{
			// ͬ���󶨣���FireEventʱͬ������
			m_pTaskRunner->ConnectEvent(DMTT_SYNC, ID2NAME(EVENTID_SYNC1),DMSlot(&TaskRunnerTest::s_slotSyncEvent1));			// ��ȫ�ֺ���
			m_pTaskRunner->ConnectEvent(DMTT_SYNC, ID2NAME(EVENTID_SYNC1),DMSlot(&TaskRunnerTest::slotSyncEvent1, this));
			m_pTaskRunner->ConnectEvent(DMTT_SYNC, ID2NAME(EVENTID_SYNC1),DMSlot(&TaskRunnerTest::slotSyncEvent1, this));		// ��ΰ󶨣���һ�α�����
			m_pTaskRunner->ConnectEvent(DMTT_SYNC, ID2NAME(EVENTID_SYNC1),DMSlot(&TaskRunnerTest::slotSyncEvent2, this),99);	// ��󶨣����ȵ��ã���Ϊ99��Ĭ��100С
			m_pTaskRunner->ConnectEvent(DMTT_SYNC, ID2NAME(EVENTID_SYNC2),DMSlot(&TaskRunnerTest::slotSyncEvent2, this),99);	// ��󶨣����ȵ��ã���Ϊ99��Ĭ��100С
			//m_pTaskRunner->RemoveEvent(ID2NAME(EVENTID_SYNC1));	// �Ƴ�����	
			//m_pTaskRunner->RemoveEventIfThis(this);				// �Ƴ����������а�
			//m_pTaskRunner->RemoveAllEvents();						// �Ƴ����а�

			// UI�󶨣���FireEventʱ�첽��UI�̴߳���
			m_pTaskRunner->ConnectEvent(DMTT_ASYN_UI,ID2NAME(EVENTID_UI1),DMSlot(&TaskRunnerTest::s_slotUIEvent1));				// ��ȫ�ֺ���
			m_pTaskRunner->ConnectEvent(DMTT_ASYN_UI,ID2NAME(EVENTID_UI1),DMSlot(&TaskRunnerTest::slotUIEvent1, this));
			m_pTaskRunner->ConnectEvent(DMTT_ASYN_UI,ID2NAME(EVENTID_UI1),DMSlot(&TaskRunnerTest::slotUIEvent1, this));			// ��ΰ󶨣���һ�α�����
			m_pTaskRunner->ConnectEvent(DMTT_ASYN_UI,ID2NAME(EVENTID_UI1),DMSlot(&TaskRunnerTest::slotUIEvent2, this),99);		// ��󶨣����ȵ��ã���Ϊ99��Ĭ��100С
			m_pTaskRunner->ConnectEvent(DMTT_ASYN_UI,ID2NAME(EVENTID_UI2),DMSlot(&TaskRunnerTest::slotUIEvent2, this),99);		// ��󶨣����ȵ��ã���Ϊ99��Ĭ��100С

			// �����̰߳�,��FireEventʱ�첽���ڲ��Ĺ����̴߳���
			m_pTaskRunner->ConnectEvent(DMTT_ASYN_WORK,ID2NAME(EVENTID_AYNC1),DMSlot(&TaskRunnerTest::s_slotAyncEvent1));				// ��ȫ�ֺ���
			m_pTaskRunner->ConnectEvent(DMTT_ASYN_WORK,ID2NAME(EVENTID_AYNC1),DMSlot(&TaskRunnerTest::slotAyncEvent1, this));
			m_pTaskRunner->ConnectEvent(DMTT_ASYN_WORK,ID2NAME(EVENTID_AYNC1),DMSlot(&TaskRunnerTest::slotAyncEvent1, this));		// ��ΰ󶨣���һ�α�����
			m_pTaskRunner->ConnectEvent(DMTT_ASYN_WORK,ID2NAME(EVENTID_AYNC1),DMSlot(&TaskRunnerTest::slotAyncEvent2, this),99);	// ��󶨣����ȵ��ã���Ϊ99��Ĭ��100С
			m_pTaskRunner->ConnectEvent(DMTT_ASYN_WORK,ID2NAME(EVENTID_AYNC2),DMSlot(&TaskRunnerTest::slotAyncEvent2, this),99);	// ��󶨣����ȵ��ã���Ϊ99��Ĭ��100С
			m_pTaskRunner->ConnectEvent(DMTT_ASYN_WORK,ID2NAME(EVENTID_AYNC2),DMSlot(&TaskRunnerTest::s_slotAyncEvent1));			// ��ȫ�ֺ���
		}
	}

	void FireBind()
	{
		if (m_pTaskRunner)
		{
			// ����FireEvent��ֱ�Ӱ�һ������Post��(ͬ��,�첽UI�߳�,�첽�����߳�)����
			CStringW str = L"abc";
			m_pTaskRunner->PostTask(DMTT_SYNC,DMNewRunnableMethod(&TaskRunnerTest::UiFun, this, 10, str , 5.67));
			m_pTaskRunner->PostTask(DMTT_ASYN_UI,DMNewRunnableMethod(&TaskRunnerTest::UiFun, this, 10, str , 5.67));
			m_pTaskRunner->PostTask(DMTT_ASYN_WORK,DMNewRunnableMethod(&TaskRunnerTest::UiFun, this, 10, str , 5.67));


			// ʹ�ò������������ð󶨵ĺ���
			DMBundle bundle = InitBundle();
			m_pTaskRunner->FireEvent(ID2NAME(EVENTID_SYNC1),bundle);
			m_pTaskRunner->FireEvent(ID2NAME(EVENTID_SYNC2),bundle);

			m_pTaskRunner->FireEvent(ID2NAME(EVENTID_UI1),bundle);
			m_pTaskRunner->FireEvent(ID2NAME(EVENTID_UI2),bundle);

			m_pTaskRunner->FireEvent(ID2NAME(EVENTID_AYNC1),bundle);
			m_pTaskRunner->FireEvent(ID2NAME(EVENTID_AYNC2),bundle);
		}
	}

	// ʹ��DMBundle���ð�����
	DMBundle InitBundle()
	{
		DMBundle bundle;
		bundle.PutBool(L"1", true);
		bundle.PutByte(L"2", 'a');
		bundle.PutChar(L"3", 'b');
		bundle.PutDword(L"4", 450);
		bundle.PutDouble(L"5", 500.122);
		bundle.PutFloat(L"6", 510.2f);
		bundle.PutInt(L"7", 54546);
		bundle.PutInt64(L"8", 0xffffffffffff);
		bundle.PutShort(L"9", 0xfffff);
		bundle.PutString(L"10", "127758857");
		bundle.PutStringW(L"11", L"234565");
		bundle.PutSize(L"12", CSize(10,9));
		bundle.PutRect(L"13", CRect(1,2,3,4));
		bundle.PutVoidPtr(L"14", (void*)0x12233);
		CStringW strWXml = L"<imglist id=\"1\" src=\"png:1\" states=\"1\" />";
		CStringA strXml = DMW2A(strWXml,CP_UTF8);
		DMXmlDocument doc;
		doc.LoadFromBuffer((const PVOID)(LPCSTR)strXml, strXml.GetLength());
		DMXmlNode XmlNode = doc.Root();
		XmlNode.SetAttribute(L"name1",L"value");
		XmlNode.SetAttributeInt(L"name2",222);
		bundle.PutXmlNode(L"15", XmlNode);

		return bundle;
	}

public:// ����
	static bool TaskRunnerTest::s_slotSyncEvent1(const DMEventSender& sender, const DMBundle& args)
	{
		DMXmlNode ret15 = args.GetXmlNode(L"15");
		return true;
	}

	bool TaskRunnerTest::slotSyncEvent1(const DMEventSender& sender, const DMBundle& args)
	{
		DMXmlNode ret15 = args.GetXmlNode(L"15");
		return true;
	}


	bool TaskRunnerTest::slotSyncEvent2(const DMEventSender& sender, const DMBundle& args)
	{
		DMXmlNode ret15 = args.GetXmlNode(L"15");
		return true;
	}

	static bool TaskRunnerTest::s_slotUIEvent1(const DMEventSender& sender, const DMBundle& args)
	{
		DMXmlNode ret15 = args.GetXmlNode(L"15");
		return true;
	}

	bool TaskRunnerTest::slotUIEvent1(const DMEventSender& sender, const DMBundle& args)
	{
		DMXmlNode ret15 = args.GetXmlNode(L"15");
		return true;
	}

	bool TaskRunnerTest::slotUIEvent2(const DMEventSender& sender, const DMBundle& args)
	{
		DMXmlNode ret15 = args.GetXmlNode(L"15");
		return true;
	}

	static bool TaskRunnerTest::s_slotAyncEvent1(const DMEventSender& sender, const DMBundle& args)
	{
		DMXmlNode ret15 = args.GetXmlNode(L"15");
		return true;
	}

	bool TaskRunnerTest::slotAyncEvent1(const DMEventSender& sender, const DMBundle& args)
	{
		DMXmlNode ret15 = args.GetXmlNode(L"15");
		return true;
	}

	bool TaskRunnerTest::slotAyncEvent2(const DMEventSender& sender, const DMBundle& args)
	{
		DMXmlNode ret15 = args.GetXmlNode(L"15");
		return true;
	}

	void TaskRunnerTest::UiFun(int a, CStringW b, double c)
	{
		int cd; 
	}
};


TEST_F(TaskRunnerTest,����)
{
	//3. ��������,���������⺯��������------------------------------------------------------------------------------------ 
	FireBind();
}
