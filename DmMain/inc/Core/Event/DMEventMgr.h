//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMEventManager.h 
// File Des:  cegui�Ĺ۲����¼�ע��ģʽ���ɲο�doc
// File Summary:
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2014-11-12	1.0			
//--------------------------------------------------------
#pragma once
#include "DMEventSubscriber.h"

namespace DM
{
	/// <summary>
	///		�¼��ÿ���¼���������������ע�ắ��
	/// </summary>
	class DM_EXPORT DMEventItem
	{
	public:
		DMEventItem(DWORD dwEventID);
		virtual~DMEventItem();

		DWORD GetEventID(){return m_dwEventID;};		   ///< ��ȡ�¼�ID
		bool Subscribe(const DMSlotFunctorBase&slot);	   ///< ע���¼�
		bool UnSubscribe(const DMSlotFunctorBase&slot);	   ///< ��ע���¼�
		int FindSlotFunctor(const DMSlotFunctorBase&slot);  

		void operator()(DMEventArgs& Args)
		{
			for (UINT i=0; i<m_EvtSlots.GetCount(); i++)
			{
				if ((*m_EvtSlots[i])(&Args))//ѭ��ִ��ע�ắ��
				{
					++Args.m_iHandleCount;
				}
			}
		}

	protected:
		DWORD							    m_dwEventID;
		DM::CArray<DMSlotFunctorBase*>		m_EvtSlots;
	};

	/// <summary>
	///		�����¼��ÿ���¼���������������ע�ắ��
	/// </summary>
	class DM_EXPORT DMEventMgr
	{
	public:
		DMEventMgr(void);
		virtual ~DMEventMgr(void);

		void AddEvent(const DWORD dwEventID);		///< ����ע��ID
		void RemoveEvent(const DWORD dwEventID);	///< �Ƴ�ע��ID
		bool IsEventPresent(const DWORD dwEventID); ///< ע��ID�Ƿ����
		void RemoveAllEvent(void);					///< �Ƴ����е�ע��ID

		bool SubscribeEvent(const DWORD dwEventID, const DMSlotFunctorBase & subscriber);	///< ��ID����ע���¼�
		bool UnSubscribeEvent(const DWORD dwEventID, const DMSlotFunctorBase & subscriber); ///< ��ID��ע���¼�

		void FireEvent(DMEventArgs& Args);			///< �¼�����ʱ֪ͨ����ע��Ĺ۲���

		bool IsMuted();								///< �Ƿ������¼�����
		void SetMuted(bool bMuted);					///< ���á��ر��¼����ˣ��¼����˿����󣬲���ִ��ע�ắ��
	protected:
		DMEventItem *GetEventObject(const DWORD dwEventID);

	protected:
		DM::CArray<DMEventItem *>					m_EvtArr;
		bool										m_bMuted;
	};
	typedef DMEventMgr* DMEventMgrPtr;
}//namespace DM