//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMSmartPtrT.h 
// File Des: ����ָ��ģ����,�������л���DMRefNum��ָ��
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2014-9-19	1.0			
//      guoyou      2014-10-11  1.1           ����CComPtr���ܣ�֧��COMָ��
//      guoyou		2015-01-09	1.2	           ���Ӱ���chmע��
//-------------------------------------------------------
#pragma once

namespace DM
{
	/// <summary>
	///		����ָ��ģ���࣬����DMʹ�����������ڴ��Զ��ͷţ����<see cref="DMRefNum"/>������ʹ��
	/// </summary>
	template<class T>
	class DMSmartPtrT
	{
	public:
		DMSmartPtrT(void) throw()
			:m_ptr(0)
		{
		}

		DMSmartPtrT(int nNull) throw()
		{
			(void)nNull;
			m_ptr = NULL;
		}

		DMSmartPtrT(T *ptr) throw()
			:m_ptr(ptr)
		{
			if (m_ptr)
			{
				m_ptr->AddRef();
			}
		}

		DMSmartPtrT(const DMSmartPtrT & sour) throw()
			:m_ptr(sour.m_ptr)
		{
			if (m_ptr)
			{
				m_ptr->AddRef();
			}
		}

		~DMSmartPtrT(void) throw()
		{
			if (0 != m_ptr)
			{
				m_ptr->Release();
			}
		}

		T * operator->() const throw()
		{
			DMASSERT_EXPR(NULL != m_ptr,L"m_ptrΪ��,��ȷ���Ƿ��ʼ��!");
			return m_ptr;
		};

		operator T*() const throw()
		{
			return m_ptr;
		}

		T& operator*() const throw()
		{
			return *m_ptr;
		}

		/// �˴�������CComPtr
		T** operator&() throw()
		{
			//DMASSERT(m_ptr==NULL);
			return &m_ptr;
		}

		bool operator!() const throw()
		{
			return (NULL == m_ptr);
		}

		bool operator<(T* ptr) const throw()
		{
			return m_ptr < ptr;
		}
		bool operator!=(T* ptr) const
		{
			return !operator==(ptr);
		}
		bool operator==(T* ptr) const throw()
		{
			return m_ptr == ptr;
		}

		T* operator=(T* lp) throw()
		{
			if(*this != lp)
			{
				if (m_ptr)
				{
					m_ptr->Release();
				}
				m_ptr = lp;
				if(m_ptr)
				{
					m_ptr->AddRef();
				}
			}
			return *this;
		}

		T* operator=(const DMSmartPtrT<T>& lp) throw()
		{
			if (*this != lp)
			{
				if(m_ptr)
				{
					m_ptr->Release();
				}
				m_ptr = lp;
				if (m_ptr)
				{
					m_ptr->AddRef();
				}
			}
			return *this;	
		}

		bool isNull()const {return 0 == m_ptr;}
		bool isValid()const {return 0 != m_ptr;}

		T * get(void) const {return m_ptr;}

		/// <summary>
		///		���¸���һ������ָ�룬ԭ���ü�����1���¶���ָ�����ü���+1
		/// </summary>
		/// <param name="ptr">����ָ��</param>
		/// <returns>��</returns>
		void reset(T* ptr=0)
		{
			if (0 != ptr)
			{
				ptr->AddRef();
			}

			if (0 != m_ptr)
			{
				m_ptr->Release();
			}

			m_ptr = ptr;
		}

		/// <summary>
		///		�ͷŸ��Ӷ���ָ�룬������������ΪNULL,
		/// </summary>
		/// <remarks>
		///     ע��ʹ�õ���.������->,��A.Release()
		///  </remarks>
		/// <returns>��</returns>
		void Release() throw()
		{
			T* pTemp = m_ptr;
			if (pTemp)
			{
				m_ptr = NULL;
				pTemp->Release();
			}
		}

		/// <summary>
		///		����һ������ָ�룬�����������ü���
		/// </summary>
		/// <param name="p2">����ָ��</param>
		/// <returns>��</returns>
		void Attach(T* p2) throw()
		{
			if (m_ptr)
				m_ptr->Release();
			m_ptr = p2;
		}

		/// <summary>
		///		���븽�ӵĶ���ָ�룬���ӵĶ������ü������䣬��ʱҪע���ⲿ�ͷ�
		/// </summary>
		/// <returns>���ӵĶ���ָ��</returns>
		T* Detach() throw()
		{
			T* pt = m_ptr;
			m_ptr = NULL;
			return pt;
		}

		/// <summary>
		///		��������ָ��
		/// </summary>
		/// <param name="ppT">����ָ��</param>
		/// <returns>S_OK��ʾ�ɹ�</returns>
		HRESULT CopyTo(OUT T** ppT) throw()
		{
			if (ppT == NULL)
				return E_POINTER;
			*ppT = m_ptr;
			if (m_ptr)
			{
				m_ptr->AddRef();
			}

			return S_OK;
		}

	private:
		T                 *m_ptr;
	};
}// namespace DM


