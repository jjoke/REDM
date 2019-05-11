//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMRefNum.h 
// File Des: SMartָ��Ļ���
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-7	1.0			
//-------------------------------------------------------
#pragma once

namespace DM
{
	/// <summary>
	///		DMRefNum:SMartָ��Ļ���,��<see cref="DMSmartPtrT"/>ʹ��
	/// </summary>
	/// <remarks>
	///		���ü�����Ϊ�˱�֤���ͷ�ʱ�����Ѳ���ʹ�� 
	/// <remarks>
	class DM_EXPORT DMRefNum
	{
	public:

		/// <summary>
		///     �������ü���
		/// </summary>
		/// <returns>���Ӻ�����ü���Num</returns>
		int AddRef(void){return ::InterlockedIncrement(&m_RefCount);}

		/// <summary>
		///     �������ü���
		/// </summary>
		/// <remarks>
		///		Ϊ0ʱ�Զ�����<see cref="OnFinalRelease"/>
		/// </remarks>
		/// <returns>���ٺ�����ü���Num</returns>
		int Release(void)
		{
			int r = ::InterlockedDecrement(&m_RefCount);
			if (0 == r)
			{
				OnFinalRelease();
			}

			return r;
		}

		/// <summary>
		///     ��ȡ��ǰ�����ü���
		/// </summary>
		/// <returns>��ǰ�����ü���Num</returns>
		int GetRefCount(void) const {return m_RefCount;}

		/// <summary>
		///     �������ü���
		/// </summary>
		/// <remarks>
		///		����ǿ�Ƶ������ü���
		/// </remarks>
		/// <param name="RefCount">���ü���Num</param>
		/// <returns>���ٺ�����ü���Num</returns>
		void SetRefCount(long RefCount) {m_RefCount = RefCount;}

		/// <summary>
		///     �����ü���Ϊ0ʱ������
		/// </summary>
		/// <remarks>
		///		Ĭ��Ϊɾ���������������
		/// </remarks>
		/// <returns>��</returns>
		virtual void OnFinalRelease()	
		{
			delete this;
		}

	protected:
		DMRefNum(void):m_RefCount(1){}
		virtual ~DMRefNum(void)
		{
			DMASSERT(0== m_RefCount);						// �˱�־���ڸ����������ǵ���Դ���������ͷ� 
		}

	public:
		volatile long              m_RefCount;
	};
}// namespace DM 