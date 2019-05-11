//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMMemPool.h 
// File Des: ��֤cstring�ȶѷ��䶼����dll�н���
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-3-31	1.0		
//-------------------------------------------------------
#pragma once

namespace DM
{
	/// <summary>
	///		��֤��dll�Ķ��Ϸ����ڴ�
	/// </summary>
	class DM_EXPORT DMMemDispatch
	{
	public:
		static void *DM_malloc(size_t size);
		static void *DM_realloc(void* memblock, size_t size);
		static void *DM_calloc(size_t num,size_t size);
		static void DM_free(void* memblock);
		static void* Get_CString_InitData();

	};

	/// <summary>
	///	ģ��New[],iNumָ��T���͵ĸ���
	/// </summary>
	template <class T>
	T* DMNewT(int iNum)
	{	
		T* ptr = NULL;
		do 
		{
			if (0>=iNum
				||NULL == (ptr = (T*)DMMemDispatch::DM_malloc(iNum*sizeof(T)+12)))
			{
				break;
			}
			memcpy(ptr,"RedM",4);// ǰ4�ֽڸ�Ϊmagic��
			*((int*)ptr+1) = iNum;// ǰ8�ֽڸ�ֵΪ��������ĸ���
			*((int*)ptr+2) = sizeof(T);// ǰ12�ֽڸ�ֵΪT����Ĵ�С
			ptr = (T*)((int*)ptr+3);// new���������صĵ�ַ�ǿ��ٵ������ռ�������12���ֽ�֮��ĵ�ַ
			for (int i=0; i<iNum; i++)
			{
				//placement new���û�ָ�����ڴ�λ���Ϲ����µĶ�������������̲���Ҫ��������ڴ棬ֻ��Ҫ���ö���Ĺ��캯������
				new (ptr+i)T(); //new���ʽ��placeement new�� ��ʽ(place_address)type(initializer-list)
			}
		} while (false);
		return ptr;
	}

	/// <summary>
	///	ģ��Delete[],����״̬,1.���������,��ʱDMNewTת���Ļ���ָ�������һ��,2.���������,����ָ��=����ָ��-���(4�ֽ�)
	/// T:��Ϊ����
	/// </summary>
	template <class T>
	void DMDelT(T* ptr)
	{
		do 
		{
			if (NULL == ptr)
			{
				break;
			}
			if (0 != memcmp((byte*)ptr-12,"RedM",4))
			{
				if (0 == memcmp((byte*)ptr-16,"RedM",4))// ����û�����������
				{
					ptr = (T*)((byte*)ptr - 4);
				}
				else
				{
					break;// �����������!
				}
			}

			int iNum = *((int*)ptr-2);
			int iSize = *((int*)ptr-1);
			for (int i=0; i<iNum; i++)
			{
				((T*)((byte*)ptr+i*iSize))->~T();//���ͷ�ǰ�Զ�������������
			}
			DMMemDispatch::DM_free((int*)ptr - 3);
		} while (false);
	}

}//namespace DM