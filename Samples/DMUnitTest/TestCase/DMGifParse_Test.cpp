//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMGifParse_Test.cpp 
// File Des: ����gif�����Ĳ�������
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-8	1.0			
//-------------------------------------------------------
#pragma once
#include "DMUintTestAfx.h"
#include "DMGifParse.h"

class DMGifParseTest:public::testing::Test
{
public:
	virtual void SetUp()
	{

	}

	virtual void TearDown()
	{

	}

protected:
};

TEST_F(DMGifParseTest, ����GifParse�ļ����ع���)
{
	wchar_t szExeDir[MAX_PATH] = {0};
	GetRootDirW(szExeDir, MAX_PATH);
	wchar_t szPath[MAX_PATH] = {0};
	PathCombineW(szPath, szExeDir, L".\\UTRes\\UTTest\\1.gif");
	DMSmartPtrT<DMGifParse> pObj;
	pObj.Attach(new DMGifParse);
	EXPECT_EQ(pObj->LoadFromFile(szPath),true);
	LPGLOBAL_INFO gi = pObj->GetGlobalInfo();
	printf("����GifParse�ļ����ع���----------------------------------\n");
	printf("�߼���Ļ���=%d,�߶�=%d\n",gi->scrWidth,gi->scrHeight);
	if (gi->bLoop)
	{
		printf("ѭ������=%d\n",gi->totalLoopCount);
	}
	else
	{
		printf("ѭ������1��\n");
	}
	for (int i=0;i<(int)gi->frames;i++)
	{
		GIFFRAMEPTR fm = pObj->GetFrame(i);
		EXPECT_EQ(NULL!=fm, true);

		printf("��%d֡,���:%d,�߶�:%d,left:%d,top:%d\n",i+1,fm->imageWidth,fm->imageHeight,fm->imageLPos,fm->imageTPos);
		if (fm->ctrlExt.active)
			printf("��%d֡��ʱ�����룩=%d,͸��ɫ:%d,�ȴ��û�����:%d\n",i+1,fm->ctrlExt.delayTime*10,fm->ctrlExt.trsFlag,fm->ctrlExt.userInputFlag);
	}

	printf("����GifParse�ļ����ع���----------------------------------\n");
}

TEST_F(DMGifParseTest, ����GifParse�ڴ���ع���)
{
	wchar_t szExeDir[MAX_PATH] = {0};
	GetRootDirW(szExeDir, MAX_PATH);
	wchar_t szPath[MAX_PATH] = {0};
	PathCombineW(szPath, szExeDir, L".\\UTRes\\UTTest\\1.gif");

	DWORD dwSize = DM::GetFileSizeW(szPath);
	EXPECT_EQ(dwSize!=0, true);
	PBYTE pBuf = new BYTE[dwSize];
	DWORD dwRead;
	GetFileBufW(szPath, (void**)&pBuf, dwSize,dwRead);
	EXPECT_EQ(dwRead == dwSize, true);


	DMSmartPtrT<DMGifParse> pObj;
	pObj.Attach(new DMGifParse);
	EXPECT_EQ(pObj->LoadFromMemory(pBuf,dwSize),true);
	LPGLOBAL_INFO gi = pObj->GetGlobalInfo();
	printf("����GifParse�ڴ���ع���----------------------------------\n");
	printf("�߼���Ļ���=%d,�߶�=%d\n",gi->scrWidth,gi->scrHeight);
	if (gi->bLoop)
	{
		printf("ѭ������=%d\n",gi->totalLoopCount);
	}
	else
	{
		printf("ѭ������1��\n");
	}
	for (int i=0;i<(int)gi->frames;i++)
	{
		GIFFRAMEPTR fm = pObj->GetFrame(i);
		EXPECT_EQ(NULL!=fm, true);

		printf("��%d֡,���:%d,�߶�:%d,left:%d,top:%d\n",i+1,fm->imageWidth,fm->imageHeight,fm->imageLPos,fm->imageTPos);
		if (fm->ctrlExt.active)
			printf("��%d֡��ʱ�����룩=%d,͸��ɫ:%d,�ȴ��û�����:%d\n",i+1,fm->ctrlExt.delayTime*10,fm->ctrlExt.trsFlag,fm->ctrlExt.userInputFlag);
	}

	printf("����GifParse�ڴ���ع���----------------------------------\n");

	DM_DELETE_ARRAY(pBuf);
}