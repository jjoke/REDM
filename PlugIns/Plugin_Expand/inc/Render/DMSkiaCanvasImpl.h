//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMSkiaRegionImpl.h 
// File Des: 
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-8-19	1.0			
//-------------------------------------------------------
#pragma once
#include "DMSkiaPenImpl.h"
#include "DMSkiaFontImpl.h"
#include "DMSkiaBrushImpl.h"
#include "DMSkiaBitmapImpl.h"
#include "DMSkiaRegionImpl.h"
#include "DMSkiaHelper.h"

namespace DM
{
	class DMSkiaCanvasImpl:public IDMCanvas
	{
	public:

		DMSkiaCanvasImpl(IDMRender* pRender, int nWid, int nHei);
		~DMSkiaCanvasImpl();
		void Canv_Init(IDMRender* pRender, int nWid, int nHei);
		void Canv_Release();

		//---------------------------------------------------
		// Function Des:����
		//---------------------------------------------------
		DMCode SelectObject(IDMMetaFile* pObj,IDMMetaFile** ppOldObj = NULL);
		DMCode GetObject(IDMMetaFile** ppObj, DMFTYPE DmfType);

		DMCode Resize(SIZE size);
		DMCode Resize(int nWid,int nHei);
		DMCode GetSize(SIZE &size);

		HDC GetDC();
		DMCode ReleaseDC(HDC hdc);
		DMCode SaveCanvas(int *pnState=NULL);
		DMCode RestoreCanvas(int nState=-1);

		//---------------------------------------------------
		// Function Des:HSL�任
		//---------------------------------------------------
		DMCode AdjustHSL32(int H, int S, int L,LPRECT lpRect=NULL);
		DMCode ResetHsl();
		PVOID GetPixelBits(int* pSize);

		//---------------------------------------------------
		// Function Des:����
		//---------------------------------------------------
		DMCode BitBlt(IDMCanvas*pCanvasSrc, int xSrc, int ySrc, LPCRECT lpRectDest, DWORD dwRop = SRCCOPY);
		DMCode AlphaBlend(IDMCanvas*pCanvasSrc, LPCRECT lpRectSrc, LPCRECT lpRectDest, BYTE alpha=0xFF);

		DMCode DrawBitamp(IDMBitmap *pBitamp, LPCRECT lpRectSrc, LPCRECT lpRectDest, BYTE alpha=0xFF, DMEXPEND_MODE ExpandMode=DEM_STRETCH);
		DMCode DrawBitmapNine(IDMBitmap *pBitamp, LPCRECT lpRectSrc, LPCRECT lpSrcMargin, LPCRECT lpRectDest, BYTE alpha=0xFF, DMEXPEND_MODE ExpandMode=DEM_STRETCH);
		
		DMCode DrawRectangle(LPCRECT lpRect);
		DMCode FillRectangle(LPCRECT lpRect);
		DMCode FillSolidRect(LPCRECT lpRect,DMColor clr);
		DMCode ClearRect(LPCRECT lpRect,DMColor clr);

		DMCode DrawRoundRect(LPCRECT lpRect,POINT &pt);
		DMCode FillRoundRect(LPCRECT lpRect,POINT &pt);

		DMCode DrawEllipse(LPCRECT lpRect);
		DMCode FillEllipse(LPCRECT lpRect);
	
		DMCode Polyline(LPPOINT lpPt,int cPoints);

		DMCode GradientFill(DMColor clrBegin,DMColor clrEnd,LPCRECT lpRect,BOOL bVert,BYTE alpha=0xFF);

		//---------------------------------------------------
		// Function Des:�ı�
		//---------------------------------------------------
		DMColor SetTextColor(DMColor clr);
		DMColor GetTextColor();

		DMCode MeasureText(LPCWSTR lpString, int nCount, OUT SIZE *pSize);
		DMCode DrawText(LPCWSTR lpString, int nCount, LPRECT lpRect, UINT uFormat,BYTE alpha=0xFF);
		DMCode TextOut(LPCWSTR lpString, int nCount, int x, int  y, BYTE alpha=0xFF);

		//---------------------------------------------------
		// Function Des:����任
		//---------------------------------------------------
		DMCode OffsetViewportOrg(int dx, int dy, OUT LPPOINT lpPoint = NULL);
		DMCode SetViewportOrgEx(int dx, int dy,  OUT LPPOINT lpPoint = NULL);
		DMCode GetViewportOrg(LPPOINT lpPoint);

		//---------------------------------------------------
		// Function Des:��������ü�
		//---------------------------------------------------
		DMCode PushClip(IDMRegion *pRegion,int fnCombineMode=RGN_AND);
		DMCode PushClip(LPCRECT lpRect,int fnCombineMode=RGN_AND);
		DMCode PopClip();
		DMCode GetClipBox(LPRECT lpRect);
		DMCode GetClipRegion(IDMRegion **ppRegion);

		DMCode ExcludeClipRect(LPCRECT lpRect);
		DMCode IntersectClipRect(LPCRECT lpRect);

		//---------------------------------------------------
		// Function Des:��������ʹ��
		//---------------------------------------------------
		DMCode SaveBmpToFile(LPCWSTR pszFileName);

		DMCode AdjustAlpha(byte byAlpha, LPRECT lpRect);
		DMCode AlphaBackup(LPRECT lpRect){return DM_ECODE_OK;};
		DMCode AlphaRestore(){return DM_ECODE_OK;};

	public:// ����
		bool Rect2SkRect(LPCRECT lpRect,SkRect &skiRc);
		void InflateSkRect(SkRect *lpRect,SkScalar dx,SkScalar dy);
		DMAutoMemDC AlphaBlendBackup(DMAutoMemDC& dcMem,LPCRECT lpRect,bool bInherit=false,bool bCopy=false);
		bool AlphaBlendRestore(DMAutoMemDC& dcMem,BYTE alpha=0xFF);

	public:
		//---------------------------------------------------
		// Function Des:���������������ӵ���չ����,�������,�Ա�֤���ϼ���
		//---------------------------------------------------
		DMCode DrawArc(LPCRECT lpRect,float startAngle, float sweepAngle);
		DMCode FillPie(LPCRECT lpRect,float startAngle, float sweepAngle);
	
	public:
		// 1
		SkCanvas									 *m_pSkCanvas;

		// 2��ѡ��Canvas�ĵ�ǰͼԪ
		DMColor									     m_CurTextColor;
		DMSmartPtrT<DMSkiaBitmapImpl>				 m_pCurBitmap;
		DMSmartPtrT<DMSkiaPenImpl>					 m_pCurPen;
		DMSmartPtrT<DMSkiaBrushImpl>				 m_pCurBrush;
		DMSmartPtrT<DMSkiaFontImpl>					 m_pCurFont;

		// 3
		SkPoint                                      m_ptOrg;
		HDC											 m_hGetDC;

		// �೧
		IDMRender									 *m_pRender;

		// �������ʹ��------------------
		int                                           m_iSaveState; //skia ��savestate��hdc��ͬ������-1������һ��~��

		// �������ʹ��------------------
		DMDIBHelper                                  m_DIBTemp;
		CRect                                        m_RcTemp;
		bool                                         m_bCopyTemp;
		HPEN										 m_hOldPen;
		HFONT										 m_hOldFont;
		HBRUSH										 m_hOldBrush;
		HBITMAP										 m_hOldBitmap;

		bool                                         m_bSupportLeetspeak; ///< �Ƿ�֧�ֻ�����
	};





}//namespace DM