
//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: IDMPlugin.h 
// File Des: ����ӿ�
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-16	1.0			
//-------------------------------------------------------
#pragma once

namespace DM
{
	/// <summary>
	///		����ӿڽ����OGRE.ÿ�����Ӧ����4����:��װ����ʼ���� �رա�ж��
	/// </summary>
	/// <remarks>
	///     �˲���ӿڼ�����Ϊdll���ã�Ҳ����Ϊ��̬lib����
	/// </remarks>
	class IDMPlugin
	{
	public:
		IDMPlugin(){}
		virtual~IDMPlugin(){}

		virtual const wchar_t* GetName() const = 0;

		//---------------------------------------------------
		// Function Des: ��������ϵͳ��ʼ��
		// Input Parameter:
		// Output Parameter:
		// return:
		//---------------------------------------------------
		virtual void Install() = 0;			///< ��������ϵͳ��ʼ��

		//---------------------------------------------------
		// Function Des: ����������
		// Input Parameter:
		// Output Parameter:
		// return:
		//---------------------------------------------------
		virtual void Uninstall() = 0;		///< ����������

		//---------------------------------------------------
		// Function Des: ������ϵͳ��ʼ��
		// Input Parameter:
		// Output Parameter:
		// return:
		//---------------------------------------------------
		virtual void Initialise() = 0;		///< ������ϵͳ��ʼ��

		//---------------------------------------------------
		// Function Des: ��ϵͳ�ؼ�����û��ж��ʱ����������
		// Input Parameter:
		// Output Parameter:
		// return:
		//---------------------------------------------------
		virtual void Shutdown() = 0;		///< ��ϵͳ�ؼ�����û��ж��ʱ����������
	};
}//namespace DM
