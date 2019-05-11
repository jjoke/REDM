// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	Draw.h 
// File mark:   
// File summary:������DMDrawImpl.h,������DMDesignerWnd�Ļ���
// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2016-8-23
// ----------------------------------------------------------------
#pragma once

namespace DM
{
	typedef enum _DRAWSTATE
	{
		DRAW_START=0,    //��ʼ
		DRAW_DRAWING,    //������
		DRAW_END         //�Ἢ
	}DMDRAW_STATE;

	/// <summary>
	///		�����߼�����ʵ��
	/// </summary>
	class DMDraw:public IDMDraw
	{
		DMDECLARE_CLASS_NAME(DMDraw,L"draw",DMREG_Draw);
	public:
		DMDraw();

	public:

		DMCode DrawBackground(IDMCanvas* pCanvas,IDMRegion* lpRgn,DUIWindow* pWnd);
		DMCode DrawForeground(IDMCanvas* pCanvas,IDMRegion* lpRgn,DUIWindow* pWnd);
		DMCode Draw(IDMCanvas* pCanvas, IDMRegion* lpRgn,DUIWindow* pWnd);

		DMCode InvalidateRect(DUIWND hDUIWnd,LPCRECT lpRect,int fnCombineMode=RGN_AND);
		int    GetInvalidateRect(DM::CArray<CRect>& Array);
		bool   IsInvalidate(){return m_bNeedRepaint;};
		DMCode Render(DUIWindow* pWnd);

		DMCode GetCanvas(IDMCanvas** ppCanvas);
		DMCode ResizeCanvas(SIZE size);

	private:// ����
		DMCode _OnRender(IDMCanvas* pCanvas, IDMRegion* pRgn,DUIWindow* pWndCur,DUIWindow* pStart,DUIWindow *pEnd, DMDRAW_STATE& Draw_State);

	public:

		DMSmartPtrT<IDMRender>                  m_pRender;
		DMSmartPtrT<IDMRegion>					m_pInvalidRegion; 
		DMSmartPtrT<IDMCanvas>					m_pMemCanvas;

		bool								    m_bNeedRepaint;
		bool                                    m_bOnlyOneRectRepaint;			///< ��ֻ��һ����Ч������
		CRect                                   m_rcOnlyOne;                   
		CRect                                   m_rcCanvas;
	};

}//namespace DM