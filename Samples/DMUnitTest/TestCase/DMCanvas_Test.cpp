//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMCanvas_Test.cpp 
// File Des: ����Canvas���ƵĲ�������
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

class CanvasTest:public::testing::Test
{
public:
	virtual void SetUp()
	{
		EXPECT_EQ(DMSUCCEEDED(g_pDMApp->CreateRegObj((void**)&m_pRender,NULL, DMREG_Render)),true);
		EXPECT_EQ(DMSUCCEEDED(g_pDMApp->GetDefRegObj((void**)&m_pDefRender,DMREG_Render)),true);
		m_pDefName = g_pDMApp->GetDefRegObj(DMREG_Render);
	}

	virtual void TearDown()
	{

	}

protected:
	DMSmartPtrT<IDMRender> m_pRender;
	DMSmartPtrT<IDMRender> m_pDefRender; // �ڲ���Ĭ��ʹ�ö���
	LPCWSTR                m_pDefName;   // �ڲ�ʹ�õĶ�����
	
};

TEST_F(CanvasTest, ���Ի�������)
{
	/// ����------------------------
	DMSmartPtrT<IDMCanvas>  pCanvas;
	EXPECT_EQ(DMSUCCEEDED(m_pDefRender->CreateCanvas(100,200,&pCanvas)),true);

	/// ��ȡ------------------------
	DMSmartPtrT<IDMBitmap>     pBitmap;
	EXPECT_EQ(DMSUCCEEDED(pCanvas->GetObject((IDMMetaFile**)&pBitmap,DMF_BITMAP)),true);

	/// �����ô�С-------------------
	EXPECT_EQ(DMSUCCEEDED(pCanvas->Resize(400,500)),true);

	/// ����ƽ�̻��ƺ��������------
	pBitmap.Release();

	// ȡ�ý�����
	DMSmartPtrT<IDMImgDecoder> pImgDecoder;
	EXPECT_EQ(DMSUCCEEDED(g_pDMApp->CreateRegObj((void**)&pImgDecoder,NULL,DMREG_ImgDecoder)),true);
	EXPECT_EQ(DMSUCCEEDED(pImgDecoder->LoadFromFile(L"UTRes\\UTTest\\canvas-1.png")), true);

	// ȡ��֡
	DMSmartPtrT<IDMImgFrame> pFrame;
	pImgDecoder->GetFrame(0, &pFrame);//png�϶�ֻ��һ֡�����Դ�0

	EXPECT_EQ(DMSUCCEEDED(m_pDefRender->CreateBitmap(&pBitmap)),true);
	EXPECT_EQ(DMSUCCEEDED(pBitmap->InitFromFrame(pFrame)), true);

	RECT rcSor  = {0, 0, pBitmap->GetWidth()+0, pBitmap->GetHeight()+0};
	RECT rcDest = {0, 0, pBitmap->GetWidth()+0, pBitmap->GetHeight()+0};
	EXPECT_EQ(DMSUCCEEDED(pCanvas->DrawBitamp(pBitmap, NULL, NULL,0xcc)),true);//ԭͼ����,ֱ�Ӵ�NULL

	rcDest.top = rcDest.bottom+1;//���ƣ�ģ������һ��
	rcDest.bottom = rcDest.top + pBitmap->GetHeight();
	rcDest.right  = rcDest.left + pBitmap->GetWidth()*2;
	EXPECT_EQ(DMSUCCEEDED(pCanvas->DrawBitamp(pBitmap, &rcSor, &rcDest,255)),true);

	rcDest.top = rcDest.bottom+1;//����,ƽ��
	rcDest.bottom = 150;//���ռ�������9�������
	rcDest.right  = 150;
	EXPECT_EQ(DMSUCCEEDED(pCanvas->DrawBitamp(pBitmap, &rcSor, &rcDest,255,DEM_TILE)),true);

	// ����DrawBitmapNine9����----------------------------------
	pImgDecoder.Release();
	EXPECT_EQ(DMSUCCEEDED(g_pDMApp->CreateRegObj((void**)&pImgDecoder,NULL,DMREG_ImgDecoder)),true);
	EXPECT_EQ(DMSUCCEEDED(pImgDecoder->LoadFromFile(L"UTRes\\UTTest\\canvas-9.png")), true);
	pFrame.Release();
	pImgDecoder->GetFrame(0, &pFrame);//png�϶�ֻ��һ֡�����Դ�0
	pBitmap.Release();
	EXPECT_EQ(DMSUCCEEDED(m_pDefRender->CreateBitmap(&pBitmap)),true);
	EXPECT_EQ(DMSUCCEEDED(pBitmap->InitFromFrame(pFrame)), true);
	RECT rcNineSor = {0, 0, pBitmap->GetWidth()+0, pBitmap->GetHeight()+0};
	RECT rcNineDest = {0, 151, 150, 250};
	RECT rcNineMargin = {48, 42, 48, 2};
	EXPECT_EQ(DMSUCCEEDED(pCanvas->DrawBitmapNine(pBitmap, &rcNineSor,&rcNineMargin, &rcNineDest,255, DEM_STRETCH)),true);

	// ��������任--------------------------------------------
	EXPECT_EQ(DMSUCCEEDED(pCanvas->OffsetViewportOrg(100, 0)), true);// ��������100
	//EXPECT_EQ(DMSUCCEEDED(pCanvas->SetViewportOrgEx(-100, 0)), true);
	POINT OrgPt;
	EXPECT_EQ(DMSUCCEEDED(pCanvas->GetViewportOrg(&OrgPt)), true);

	// ��������-----------------------------------------------
	DMColor TextClr = PBGRA(0,0,0xff,0xff);
	pCanvas->SetTextColor(TextClr);

	CRect rcGetString;
	EXPECT_EQ(DMSUCCEEDED(pCanvas->DrawText(L"DuiMagic DrawText",-1, &rcGetString, DT_SINGLELINE|DT_NOPREFIX|DT_CALCRECT)),true);
	rcGetString.bottom+=rcGetString.Height();
	rcGetString.left = -100;rcGetString.right = 0;
	EXPECT_EQ(DMSUCCEEDED(pCanvas->DrawText(L"DuiMagic\nDrawText",-1, &rcGetString, DT_LEFT)),true);

	SIZE MesureSize;
	EXPECT_EQ(DMSUCCEEDED(pCanvas->MeasureText(L"MeasureText",-1,&MesureSize)),true);
	EXPECT_EQ(DMSUCCEEDED(pCanvas->TextOut(L"TextOut", -1, 100, 0)), true);

	// ����FillRectangle-------------------------------------
	RECT rcFillRectangle = {270, 0, 310, 40};// ע�⻭�������ˣ�����300-310�ǻ治������
	DMSmartPtrT<IDMBrush>pBrush;
	EXPECT_EQ(DMSUCCEEDED(m_pRender->CreateSolidColorBrush(PBGRA(0,0x70, 0, 0x70), &pBrush)), true);
	pCanvas->SelectObject(pBrush);
	pCanvas->FillRectangle(&rcFillRectangle);

	// ����DrawRectangle-------------------------------------
	//RECT rcDrawRectangle = {270, 41, 310, 81};// ע�⻭�������ˣ�����300-310�ǻ治������
	RECT rcDrawRectangle = {-100, 0, 300, 300};
	DMSmartPtrT<IDMPen> pPen;
	EXPECT_EQ(DMSUCCEEDED(m_pRender->CreatePen(PBGRA(0xa0,0xa0, 0, 0xa0),PS_DASH,1, &pPen)), true);
	pCanvas->SelectObject(pPen);
	pCanvas->DrawRectangle(&rcDrawRectangle);

	// ����FillSolidRect-------------------------------------
	RECT rcSolidRectangle = {-19, 40,60, 80};
	pCanvas->FillSolidRect(&rcSolidRectangle, PBGRA(0x70,0x70,0x70,0x70));// ע����PBGRA������Ϊ0x70͸���ȵİ�ɫ

	// ����DrawRoundRect-------------------------------------
	RECT rcDrawRoundRect = {270, 40, 310, 80};
	POINT ptDrawRoundRec = {10,10};
	pCanvas->DrawRoundRect(&rcDrawRoundRect, ptDrawRoundRec);

	// ����FillRoundRect-------------------------------------
	RECT rcFillRoundRect = {270, 80, 310, 120};
	POINT ptFillRoundRect = {10,10};
	pCanvas->FillRoundRect(&rcFillRoundRect, ptFillRoundRect);

	// ����DrawEllipse-------------------------------------
	RECT rcDrawEllipse = {240, 121, 310, 161};
	pCanvas->DrawEllipse(&rcDrawEllipse);

	// ����FillEllipse-------------------------------------
	RECT rcFillEllipse = {240, 162, 310, 201};
	pCanvas->FillEllipse(&rcFillEllipse);

	// ����Polyline----------------------------------------
	pPen.Release();
	EXPECT_EQ(DMSUCCEEDED(m_pRender->CreatePen(PBGRA(0x0,0x0, 0xcc, 0xcc),PS_DASHDOTDOT,1, &pPen)), true);
	pCanvas->SelectObject(pPen);
	POINT pt[5] = {0};
	pt[0].x = 100; pt[0].y = 200;
	pt[1].x = 100; pt[1].y = 100;
	pt[2].x = 120; pt[2].y = 80;
	pt[3].x = 140; pt[3].y = 100;
	pt[4].x = 100; pt[4].y = 200;
	//pt[3] = pt[0];
	pCanvas->Polyline(pt, 5);

	// �ü���------------------------------------------------
	CRect rcClip(100, 0, 200,100);//ϸ�ڿ��Կ�http://hgy413.com/1847.html
	pCanvas->PushClip(rcClip);
	CRect rcClipDest;
	pCanvas->GetClipBox(rcClipDest);
	EXPECT_EQ(100 == rcClipDest.left,true);
	EXPECT_EQ(200 == rcClipDest.right,true);
	pCanvas->PopClip();
	pCanvas->GetClipBox(rcClipDest);
	EXPECT_EQ(-100 == rcClipDest.left,true);

	DMSmartPtrT<IDMCanvas> pCanvasTemp;
	EXPECT_EQ(DMSUCCEEDED(m_pDefRender->CreateCanvas(400,500,&pCanvasTemp)),true);
	CRect rcCanvas(0,0,400,500);
	CRect rcCanvasSrc(-100,0,300,500);
	//pCanvasTemp->FillSolidRect(rcCanvas, PBGRA(0x00,0xff,0x00,0xff));
	pCanvasTemp->BitBlt(pCanvas, -100,0,rcCanvas,SRCCOPY);
	pCanvasTemp->AlphaBlend(pCanvas,rcCanvasSrc,rcCanvas);

	// ����GradientFill----------------------------------------
	RECT rcGradientFill = {150, 40, 250, 60};
	pCanvasTemp->GradientFill(PBGRA(0,0xff,0xff,0xcc),PBGRA(0,0xff, 0,0x80),&rcGradientFill, FALSE,0xff);

	// ����DrawArc----------------------------------------------
	//https://blog.csdn.net/clever101/article/details/6195026
	RECT rcArc = {260, 0, 320, 60};
	float startAngle = 60.0f;// �������Ƕ�Ϊ60��  
	float sweepAngle = 150.0f;// ������ת�Ƕ�Ϊ150��  
	pPen.Release();
	EXPECT_EQ(DMSUCCEEDED(m_pRender->CreatePen(PBGRA(0x0,0xff,0xff,0xff),PS_SOLID,1, &pPen)), true);
	pCanvasTemp->SelectObject(pPen);
	pCanvasTemp->DrawArc(&rcArc,startAngle,sweepAngle);

	RECT rcPie = {320, 0, 380, 60};
	pBrush.Release();
	EXPECT_EQ(DMSUCCEEDED(m_pRender->CreateSolidColorBrush(PBGRA(0,0,0xff,0xff), &pBrush)), true);
	pCanvasTemp->SelectObject(pBrush);
	pCanvasTemp->FillPie(&rcPie,startAngle,sweepAngle);

	// end ���Ƶ���Ļ
#if SHOW_TOSCREEN
	DMAutoDC hdc;
	HDC dcMem = pCanvasTemp->GetDC();
	BLENDFUNCTION bf = {AC_SRC_OVER,0,0xff,AC_SRC_ALPHA};
	bool bRet = ::AlphaBlend(hdc, 400, 0,400,400,dcMem, 0, 0,400,400,bf);// ֻ��Alpha�ܻ��͸��Ч��,�ɻ�������100������Դx=-100
	//::BitBlt(hdc, 0, 0,400,500,dcMem, -100,0, SRCCOPY);
	pCanvasTemp->ReleaseDC(dcMem);
#endif

}