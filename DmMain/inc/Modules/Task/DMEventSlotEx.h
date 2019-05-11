// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	DMEventSlotEx.h
// File mark:   
// File summary:DMEventSlot����չ
// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2019-2-27
// ----------------------------------------------------------------
#pragma once
#include "IDMTaskRunner.h"
#include "DMEventSlot.h"
#include "DMTaskT.h"

namespace DM
{
	/// <summary>
	///		����ת����Task
	/// </summary>
	class DMSlotTask : public IDMTask
	{
	public:
		DMSlotTask(const DMSlot& Slot,const DMEventSender& Sender,const DMBundle& Bundle,IDMSlot* pSlot);
		~DMSlotTask();

		void Run();
	private:
		DMSmartPtrT<IDMSlot>					m_spSlot;
		DMSlot									m_Slot;
		DMEventSender							m_Sender;
		DMBundle								m_Bundle;
	};


	/// <summary>
	///		UI��
	/// </summary>
	class DMUISlot : public DMSyncSlot
	{
	public:
		DMUISlot(const DMSlot& slot,IDMTaskRunner* pOwner);

	public:
		virtual bool Invoke(DMEventSender& sender, DMBundle& args);
		virtual DMSyncSlot* Clone() const;

	public:
		IDMTaskRunner*                     m_pOwner;
	};

	/// <summary>
	///		�첽��
	/// </summary>
	class DMWorkSlot : public DMSyncSlot
	{
	public:
		DMWorkSlot(const DMSlot& slot, IDMTaskRunner* pOwner);

	public:
		virtual bool Invoke(DMEventSender& sender, DMBundle& args);
		virtual DMSyncSlot* Clone() const;

	public:
		IDMTaskRunner*                     m_pOwner;
	};

}//namespace DM