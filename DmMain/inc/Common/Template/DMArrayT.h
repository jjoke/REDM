//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMArray.h 
// File Des: ͳһ��Arrayģ��
// File Summary: ����������ʱ����RemoveAll!
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
	///		ͳһ��Arrayģ��
	/// </summary>
	/// <remarks>
	///		������������ʱ����RemoveAll!
	/// </remarks>
	template<class TObj>
	class DMArrayT
	{
	public:
		DMArrayT(){};
		~DMArrayT(){/*RemoveAll���������غ�����������ã���Ȼ���غ�����Ч*/}

		/// -------------------------------------------------
		/// @brief obj�Ƿ����
		/// @param[in]		 obj    ���ڲ��ҵ�obj
		/// @return DM_INVALID_VALUE(-1)��ʾ������
		int FindObj(const TObj &obj)
		{
			int count = (int)m_DMArray.GetCount();
			for (int i=0; i<count; i++)
			{
				if (EqualArrayObj(obj, m_DMArray[i]))
				{
					return i;
				}
			}

			return DM_INVALID_VALUE;
		}

		/// -------------------------------------------------
		/// @brief ȡ��obj,
		/// @param[in]  iElement		ָ�����index
		/// @param[out] obj			    ����ָ�����obj
		/// @remark ��ȫ��ȡ��ʽ���Ƽ�
		/// @return false:��ȡʧ��,true:��ȡ�ɹ�
		bool GetObj(size_t iElement, TObj &obj)
		{
			bool bRet = false;
			do 
			{
				if (iElement>=GetCount())
				{
					break;
				}

				obj = m_DMArray[iElement];
				bRet = true;
			} while (false);
			return true;
		}

		/// -------------------------------------------------
		/// @brief ȡ��obj
		/// @param[in] iElement		   ָ�����index
		/// @remark ����ȫ��ȡ��ʽ
		/// @return ��ȡ�Ķ���
		TObj &GetObj(size_t iElement)
		{
			return m_DMArray[iElement];
		}

		/// -------------------------------------------------
		/// @brief ����obj
		/// @param[in] obj			   ����ָ�����obj
		/// @return true:����ɹ�,false:obj�Ѵ���
		bool AddObj(const TObj &obj)
		{
			bool bRet = false;
			do 
			{
				if (DM_INVALID_VALUE != FindObj(obj))/// obj�Ѵ���
				{
					break;
				}
				m_DMArray.Add(obj);
				bRet = true;
			} while (false);
			return bRet;
		}

		/// -------------------------------------------------
		/// @brief �Ƴ�obj
		/// @param[in] iElement		ָ�����index
		/// @return true:�Ƴ��ɹ�,false:�Ƴ��ɹ�
		bool RemoveObj(size_t iElement)
		{
			bool bRet = false;
			do 
			{
				if (iElement>=GetCount())
				{
					break;
				}
				PreArrayObjRemove(m_DMArray[iElement]);
				m_DMArray[iElement] = NULL;//lzlong add
				m_DMArray.RemoveAt(iElement);
				bRet = true;
			} while (false);
			return bRet;
		}

		/// -------------------------------------------------
		/// @brief �Ƴ�obj
		/// @param[in] obj		ָ����obj
		/// @return true:�Ƴ��ɹ�,false:�Ƴ��ɹ�
		bool RemoveObj(TObj &obj)
		{
			bool bRet = false;
			do 
			{
				int iFind = FindObj(obj);
				if (-1 == iFind)//obj������
				{
					break;
				}
				PreArrayObjRemove(obj);
				obj = NULL;//lzlong add 
				m_DMArray.RemoveAt(iFind);
				bRet = true;
			} while (false);
			return bRet;
		}

		/// -------------------------------------------------
		/// @brief �Ƴ�����obj
		/// @return ��
		void RemoveAll()
		{
			int count = (int)m_DMArray.GetCount();
			for (int i=count-1; i>=0; i--)
			{
				PreArrayObjRemove(m_DMArray[i]);
				m_DMArray[i] = NULL; //lzlong add 
			}

			m_DMArray.RemoveAll();
		}

		/// -------------------------------------------------
		/// @brief ��ȡ��Ŀ
		/// @return ��Ŀ
		size_t GetCount()
		{
			return m_DMArray.GetCount();
		}
		
		/// -------------------------------------------------
		/// @brief ������
		/// @param[in] objsrc		��Ҫ�Ƚϵ���
		/// @param[in] objdest		Array�������Ƚϵ���
		/// @remark �ȽϺ��������������أ�Ĭ��ֱ��==
		/// @return true:���,false:�����
		virtual bool EqualArrayObj(const TObj &objsrc, const TObj &objdest)
		{
			/// �ⲿ��������
			if (objsrc == objdest)
			{
				return true;
			}
			return false;
		}

		/// -------------------------------------------------
		/// @brief ������
		/// @param[in] obj		ָ����
		/// @remark ���Ƴ�ǰ��Ԥ��������������������
		/// @return ��
		virtual void PreArrayObjRemove(const TObj &obj)
		{
			/// �ⲿ��������
		}

	public:
		DM::CArray<TObj>         m_DMArray;
	};

}//namespace DM