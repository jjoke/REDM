//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMPlugin_Test.cpp 
// File Des: ���Բ����ʽ�Ĳ�������
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-16	1.0			
//-------------------------------------------------------
#pragma once

#include "DMUintTestAfx.h"

class DMPluginTest:public::testing::Test
{
public:
	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{
	}

};

class Plugin_Test:public IDMPlugin
{
public:
	Plugin_Test(){}
	~Plugin_Test(){}
	const wchar_t* GetName() const{return L"Plugin_Test";};
	void Install()
	{
		printf("Plugin_Test::Install\n");
	}

	void Uninstall()
	{
		printf("Plugin_Test::Uninstall\n");
	}

	void Initialise()
	{
	}

	void Shutdown()
	{
	}
};

TEST_F(DMPluginTest,����)
{
#ifdef DLL_DMMAIN
	IDMPlugin* plugin = new Plugin_Test;// �������delete�������ȷ���װ
	g_pDMApp->InstallPlugin(plugin);
	g_pDMApp->UninstallPlugin(plugin);
	DM_DELETE(plugin);


// ����·������
#if 0
#ifdef _DEBUG
	g_pDMApp->LoadPlugins(L"I:\\REDM\\Docs\\TestData\\dmpluginsd.cfg");
#else
	g_pDMApp->LoadPlugins(L"I:\\REDM\\Docs\\TestData\\dmplugins.cfg");
#endif if
#endif
#endif
}
