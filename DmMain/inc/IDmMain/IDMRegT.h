//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: IDMRegT.h 
// File Des: �����ⲿע�Ḩ���ӿڣ�ÿ���ⲿע�����������DMObj
// File Summary: ʹ�÷�ʽ����class DMRegister:public DMBase
// ��DMRegT(DMRegister)�;��д���DMRegister����������ˣ�������Ϊע���ഫ��
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-29	1.0			
//-------------------------------------------------------
#pragma once

namespace DM
{
	class IDMReg;
	typedef IDMReg* IDMRegPtr; 
	/// <summary>
	///		ÿ��ע����ͨ��Helper���������д����������(NewObj)���������������(Clone)
	/// </summary>
	class DM_EXPORT IDMReg
	{
	public:
		virtual ~IDMReg(){}
		virtual PVOID NewObj() = 0;				 ///< �����������(NewObj)
		virtual IDMRegPtr Clone() = 0;           ///< ��������

		// ȡ�û���DMBaseע����ı�ʶ������ı�ʶ��ע�����ͣ�����ʹ��DMDECLARE_CLASS_NAME��
		virtual LPCWSTR GetClassName() = 0;		///< ȡ��ע������
		virtual LPCWSTR GetBaseClassName() = 0; ///< ȡ��ע���ุ����
		virtual int     GetClassType() = 0;     ///< ȡ��ע������
	};

	/// <summary>
	///		����ע���࣬T�����ǻ���DMBase���࣬����ʵ����(static)GetClassName��GetBaseClassName����
	/// </summary>
	template<class T>
	class  DMRegHelperT:public IDMReg
	{
	public:// Ĭ�Ϲ��캯���Ǳ���ģ���Ȼ�޷���ʼ������
		DMRegHelperT(){}
		~DMRegHelperT(){}
	public:
		virtual PVOID NewObj()
		{
			return new T;
		}

		virtual IDMRegPtr Clone()
		{
			return new DMRegHelperT<T>;
		}

		virtual LPCWSTR GetClassName()
		{
			return T::GetClassName();
		}

		virtual LPCWSTR GetBaseClassName()
		{
			return T::GetBaseClassName();
		}

		virtual int GetClassType()
		{
			return T::GetClassType();	///ע�⣬�˴�ʹ�õ��Ǿ�̬GetClassType�����⻹�и���GetClassType
		}
	};

}