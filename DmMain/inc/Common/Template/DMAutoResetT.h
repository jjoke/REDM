//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name:
// File Des: �Զ��ָ���ǰֵ
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2014-11-10	1.0		
//      guoyou		2015-01-09	1.1	           ���Ӱ���chmע��
//-------------------------------------------------------
#pragma once

namespace DM
{
	/// <summary>
	///		��������ʱ������ֵ�������������ʱ�ָ�ԭʼֵ
	/// </summary>
	template<class T>
	class DMAutoResetT
	{
	public:

		/// <summary>
		///     ��������ʱ������ֵ
		/// </summary>
		/// <remarks>
		///		����ԭʼֵ���ڲ�
		/// </remarks>
		/// <param name="pCopy">Ҫ���õĶ���</param>
		/// <param name="NewValue">�������õ���ֵ</param>
		/// <returns>��</returns>
		DMAutoResetT(T*  pCopy, T NewValue)
		{
			m_pCopy		= pCopy;     // ָ��
			m_OrgValue  = *pCopy;	 // ����ԭʼֵ
			*m_pCopy    = NewValue;  // ����ֵ
		}

		~DMAutoResetT()
		{
			*m_pCopy    = m_OrgValue; // ����ֵ
		}

	public:
		T*         m_pCopy;
		T          m_OrgValue;
	};


}//namespace DM