//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMLock.h 
// File Des: �Զ���
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-01-11	1.0			
//-------------------------------------------------------
#pragma once

namespace DM
{
	/// <summary>
	///		����ģ���࣬ʹ��<see cref="DMAutoLock"/>ʵ���Զ��������ͷ�
	/// </summary>
	class DM_EXPORT DMLock
	{
	public:
		DMLock()
		{
			::InitializeCriticalSection(&m_sesion);
		}
		~DMLock()
		{
			::DeleteCriticalSection(&m_sesion);
		}
	public:
		/// -------------------------------------------------
		/// @brief ����
		/// @return ����
		void lock(void)
		{
			::EnterCriticalSection(&m_sesion);
		}

		/// -------------------------------------------------
		/// @brief ����
		/// @return ����
		void unlock(void)
		{
			::LeaveCriticalSection(&m_sesion);
		}

		/// -------------------------------------------------
		/// @brief ��������
		/// @return ��������
		bool tryLock()
		{
			return (TRUE==::TryEnterCriticalSection(&m_sesion));
		}

	public:
		CRITICAL_SECTION			m_sesion;
	};

	/// <summary>
	///		�Զ�����ģ���࣬����<see cref="DMLock"/>ʵ���Զ��������ͷ�
	/// </summary>
	/// <remarks>
	///		DMLock m_pLock,��ʱ��������DMAutoLock autolock(m_pLock);��������������Զ���
	/// </remarks>
	class DM_EXPORT DMAutoLock
	{
	public:
		DMAutoLock(IN DMLock* pLock)
			:m_pLock(pLock)
		{
			if (m_pLock)	
			{
				m_pLock->lock();
			}
		}
		~DMAutoLock()
		{
			if (m_pLock) 
			{
				m_pLock->unlock();
			}
		}

	public:
		DMLock*						m_pLock;
	};

}//namespace DM