//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMDynLib.h 
// File Des: ����dll��ʽ��plugin
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
	///		ÿ��dll�����Ӧһ���˶���,��ֲ��ogre���ϵͳ���ɲο�OgreDynLib.h/.cpp
	/// </summary>
	class DMDynLib
	{
	public:
		DMDynLib(const CStringW &strPluginPath);
		virtual ~DMDynLib(void);

		bool Load();									///<����
		void Unload();									///<ж��

		const CStringW& GetName()const;					///<��ȡ�����
		void* GetSymbol(const char* pProcName)const;	///<��ȡ����������ַ

	protected:
		CStringW DynlibError(void);						///<��ȡ����ʧ��ԭ��

	protected:
		CStringW			m_strPluginPath;			///<�����·��
		HMODULE             m_hModule;					///<������ص�handle
	};

}//namespace DM
