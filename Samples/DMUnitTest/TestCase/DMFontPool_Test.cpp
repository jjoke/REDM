//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMUintTestAfx.h 
// File Des: ����������ַ����Ĺ���
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-31	1.0			
//-------------------------------------------------------
#pragma once 
#include "DMUintTestAfx.h"
#include "DUIFontPool.h"

class DMFontPoolTest:public::testing::Test
{
public:
	virtual void SetUp()
	{	
	}

	virtual void TearDown()
	{

	}

public:

};

TEST_F(DMFontPoolTest, ����FontPool)
{
	CStringW str = L"face:΢���ź�,size:0,weight:400,charset:134,underline:1,italic:1,strike:1,adding:0";
	DUIFontPool fontpool;
	fontpool.SetDefaultFont(str);
	IDMFontPtr pDefFont = fontpool.GetFont(L"");// ȡ��Ĭ������
	IDMFontPtr pDFont = fontpool.GetFont(L"size:0,weight:400"); //��һ�δ���
	IDMFontPtr pFont1 = fontpool.GetFont(L"size:0,weight:400"); //�ڶ���ȡ��
	EXPECT_EQ(pDFont == pFont1,true);

	EXPECT_EQ(0==_wcsicmp(pDFont->GetFaceName(),L"΢���ź�"),true);//û�����õľͲ���Ĭ�ϵ�


}