// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	DMEventSlot.h
// File mark:   
// File summary:
// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2019-3-2
// ----------------------------------------------------------------
#pragma once

namespace DM
{
	/// <summary>
	///		����չ�ӿ�
	/// </summary>
	interface IDMSlot : public DMRefNum
	{
		virtual bool Connected() const = 0;
	};

	/// <summary>
	///		ͬ����,ͬ�����òۺ���
	/// </summary>
	class DMSyncSlot : public IDMSlot
	{
	public:
		DMSyncSlot(const DMSlot& slot);
		bool operator==(const DMSyncSlot& src) const;
		virtual ~DMSyncSlot();

	public:
		bool Connected() const;
		void Disconnect();
		bool IsMuted() const;
		void SetMuted(bool bMuted);
		bool CompareIfThis(void* pThis) const;	
		const DMSlot GetSlot() const;

	public:
		virtual bool Invoke(DMEventSender& sender, DMBundle& args);
		virtual DMSyncSlot* Clone() const;

	public:
		bool									m_bMuted;		///< Ϊtrueʱ�������¼�
		int										m_SlotId;		///< ��Id��
		DMSlot									m_Slot;		    ///< ��ʵ����
	};


	/// <summary>
	///		�¼���,�¼�����---ͬ��/�첽/UI��
	/// </summary>
	class DMEventSlot : public DMRefNum
	{
	public:
		typedef DMSmartPtrT<DMSyncSlot>		   Connection;
		typedef	int							   Group;
	public:
		DMEventSlot(LPCWSTR lpszEventName);
		void operator()(DMEventSender& sender, DMBundle& args);
		~DMEventSlot();

	public:
		const CStringW& GetName(void) const;
		bool EmptySlot(void) const;
		Connection ConnectSlot(const DMSyncSlot& slot, Group group = -1);
		bool DisconnectIfThis(void* pThis);

	public:
		CStringW								m_strEventName;					   ///< �¼���
		DM::CMap<int, DM::CArray<Connection>>   m_slotContainer;                   ///< �¼������������Խ��Խ���ȵ���,MAP���Զ������ְ���С��������
	};
	typedef DMSmartPtrT<DMEventSlot>			RefEventSlot;

}//namespace DM
