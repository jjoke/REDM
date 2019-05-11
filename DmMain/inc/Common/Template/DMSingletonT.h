
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

namespace DM
{
	/// <summary>
	///		����ģʽģ����,�ر�ע��:��ģ�鴫��ʱ,T����Ҫ����ʵ��static T& getSingleton()��static T* getSingletonPtr()
	/// </summary>
	template <typename T> 
	class DMSingletonT
	{
	public:
		static T* ms_Singleton;

	public:
		DMSingletonT(void)
		{
			DMASSERT(!ms_Singleton);
			ms_Singleton = static_cast<T*>(this);
		}
		virtual ~DMSingletonT(void)
		{
			DMASSERT( ms_Singleton );
			ms_Singleton = 0;
		}

		/// <summary>
		///		��ȡ����ģʽ�Ķ���
		/// </summary>
		/// <returns>����ģʽ�Ķ���</returns>
		static T& getSingleton()
		{
			DMASSERT(ms_Singleton);
			return (*ms_Singleton);
		}

		/// <summary>
		///		��ȡ����ģʽ�Ķ���ָ��
		/// </summary>
		/// <returns>����ģʽ�Ķ���ָ��</returns>
		static T* getSingletonPtr()
		{
			return (ms_Singleton);
		}

	private:
		DMSingletonT& operator=(const DMSingletonT&)
		{
			return *this;
		}

		DMSingletonT(const DMSingletonT&) {}
	};

	template<class T>
	typename T* DMSingletonT<T>::ms_Singleton = 0;

}//namespace DM

