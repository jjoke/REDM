//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMPluginsTool.h 
// File Des: ���ڼ��ء�������
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
	class DMDynLib;

	/// <summary>
	///		�������
	/// </summary>
	class DMPluginsTool
	{
		typedef void (*DLL_START_PLUGIN)(void);
		typedef void (*DLL_STOP_PLUGIN)(void);
	public:
		DMPluginsTool(void);
		virtual ~DMPluginsTool(void);

		//---------------------------------------------------
		// Function Des: ��������plugin-dll�����ļ���ע�������ĸ��������Ǽ��ض�̬dll
		//  dll�����ṩdllStartPlugin��dllStopPlugin��������
		//  һ����dllStartPlugin����InstallPlugin����dll�еĲ��
		//        dllStopPlugin����UninstallPlugin���dll�еĲ��
		// Input Parameter:
		// Output Parameter:
		// return:
		//---------------------------------------------------
		DMCode LoadPlugins(const wchar_t* pPluginsFile = L"dmplugins.cfg");
		void UnloadPlugins(void);

		DMCode LoadPlugin(const CStringW& strPluginName);
		void UnloadPlugin(const CStringW& strPluginName);

		//---------------------------------------------------
		// Function Des: ���ز���װplugin,���ڼ��ز��
		// ������dll�е��ô˺������ز����Ҳ������lib�е���
		// Input Parameter:
		// Output Parameter:
		// return:
		//---------------------------------------------------
		DMCode InstallPlugin(IDMPlugin* plugin);
		DMCode UninstallPlugin(IDMPlugin* plugin);

		void InitialisePlugins();
		void ShutdownPlugins();

		//---------------------------------------------------
		// Function Des: ����ϵͳ�������״̬
		// Input Parameter:
		// Output Parameter:
		// return:
		//---------------------------------------------------
		inline void SetInit(bool bInit=true){m_IsInitialised = bInit;}

	protected:
		void ParsePluginCfg(const wchar_t* pPluginsFile, wchar_t *szExeDir);

	protected:
		typedef DM::CArray<DMDynLib*>   PluginLibArray;
		typedef DM::CArray<IDMPlugin*>	PluginArray;

		PluginLibArray                  m_LibsArray;		///<���������dll��
		PluginArray                     m_PluginArray;		///<����У�dll�л�ע������,��̬libҲ����ע�����У�
		bool                            m_IsInitialised;    ///<�Ƿ�ϵͳ��ʼ�����
	};




}//namespace DM