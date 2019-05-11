//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMRes_Test.cpp 
// File Des: ������Դ�����ʽ�Ĳ�������
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-11	1.0			
//-------------------------------------------------------
#pragma once

#include "DMUintTestAfx.h"

class DMResTest:public::testing::Test
{
public:
	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{
	}
};

TEST_F(DMResTest,����Res�ļ��д��)
{
	EXPECT_EQ(DMSUCCEEDED(g_pDMApp->LoadResPack((WPARAM)L"UTRes",NULL,L"DMResFolderImpl")),true);
	
	// �������õ�DMResFolderImpl���Ƿ�����
	DMSmartPtrT<IDMRes> m_pRes;
	EXPECT_EQ(DMSUCCEEDED(g_pDMApp->GetDefRegObj((void**)&m_pRes, DMREG_Res)),true);

	//EXPECT_EQ(DMSUCCEEDED(g_pDMApp->CreateRegObj((void**)&m_pRes,L"DMResFolderImpl",DMREG_Res)),true);

	// �������
	EXPECT_EQ(DMSUCCEEDED(m_pRes->LoadResPack((WPARAM)(L"UTRes"),NULL)),true);

	// �ж�layout�е�XML_MAINWND�Ƿ����
	EXPECT_EQ(DMSUCCEEDED(m_pRes->IsItemExists(RES_LAYOUT,L"dui_main")),true);
	EXPECT_EQ(DMSUCCEEDED(m_pRes->IsItemExists(RES_LAYOUT,L"dui_main1")),false);

	// �ж�theme�е�Btn_Restore�Ƿ����
	EXPECT_EQ(DMSUCCEEDED(m_pRes->IsItemExists(L"png",L"Btn_Restore")),true);

	// ȡ��default�����µ�btn_menu
	unsigned long size1 = 0;
	EXPECT_EQ(DMSUCCEEDED(m_pRes->GetItemSize(L"png",L"Btn_Menu",size1)),true);

	DMBufT<byte>pBuf;pBuf.Allocate(size1);
	EXPECT_EQ(DMSUCCEEDED(m_pRes->GetItemBuf(L"png",L"Btn_Menu",pBuf,size1)),true);


	EXPECT_EQ(DMSUCCEEDED(m_pRes->SetCurTheme(L"theme1")),true);

	EXPECT_EQ(DMSUCCEEDED(m_pRes->IsItemExists(L"png",L"Btn_Restore")),true);
	EXPECT_EQ(DMSUCCEEDED(m_pRes->GetItemSize(L"png",L"Btn_Menu",size1)),true);
	EXPECT_EQ(DMSUCCEEDED(m_pRes->GetItemSize(L"png",L"Btn_Restore",size1)),true);


	// �ⲿ����Ƥ������
	EXPECT_EQ(DMSUCCEEDED(m_pRes->LoadTheme((WPARAM)L"theme2",(LPARAM)L"UTRes\\themes\\theme2\\dmindex.xml")),true);
	EXPECT_EQ(DMSUCCEEDED(m_pRes->SetCurTheme(L"theme2")),true);
	EXPECT_EQ(DMSUCCEEDED(m_pRes->GetItemSize(L"png",L"Btn_Menu",size1)),true);
	

}