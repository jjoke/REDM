
//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMSingletonT.h 
// File Des: ����ģʽ
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2014-9-12	1.0			
//      guoyou		2015-01-09	1.1	           ���Ӱ���chmע��
//-------------------------------------------------------
#pragma once
#include <assert.h>
#include "DMMapT.h"
__pragma(warning(disable: 4661))
namespace DM
{
	/// <summary>
	///		���̵߳���ģʽģ����
	/// </summary>
	template <typename T> 
	class DMSingletonT
	{
	public:
		static T* ms_Singleton;

	public:
		DMSingletonT(void)
		{
			if (m_Map.IsKeyExist(::GetCurrentThreadId()))
			{
				DMASSERT_EXPR(false,L"��Ҫ��ʼ�����DMApp����");
			}
			T* pObj = static_cast<T*>(this);
			m_Map.AddKey(::GetCurrentThreadId(),pObj);
		}
		virtual ~DMSingletonT(void)
		{
			m_Map.RemoveKey(::GetCurrentThreadId());
		}

		/// <summary>
		///		��ȡ����ģʽ�Ķ���
		/// </summary>
		/// <returns>����ģʽ�Ķ���</returns>
		static T& getSingleton()
		{
			T* pObj = NULL;
			if (!m_Map.GetObjByKey(::GetCurrentThreadId(),pObj))
			{
				DMASSERT_EXPR(false,L"��ǰ�߳�δ����DMApp����");
			}
			return *pObj;
		}

		/// <summary>
		///		��ȡ����ģʽ�Ķ���ָ��
		/// </summary>
		/// <returns>����ģʽ�Ķ���ָ��</returns>
		static T* getSingletonPtr()
		{
			T* pObj = NULL;
			if (!m_Map.GetObjByKey(::GetCurrentThreadId(),pObj))
			{
				DMASSERT_EXPR(false,L"��ǰ�߳�δ����DMApp����");
			}
			return pObj;
		}

	private:
		DMSingletonT& operator=(const DMSingletonT&)
		{
			return *this;
		}

		DMSingletonT(const DMSingletonT&) {}
	public:
		static DMMapT<DWORD, T*>   m_Map;
	};

	template<class T> typename DMMapT<DWORD, T*> DMSingletonT<T>::m_Map;

}//namespace DM

