//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DUIAnimate.h 
// File Des: ���ö���ʵ��
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-2-9	1.0			
//--------------------------------------------------------
#pragma once
#include "DUIAnimateHelper.h"

namespace DM
{
	/// <summary>
	///		 Tabҳ�����ֶ�����ӵ����
	/// </summary>
	class DM_EXPORT IDMTabAnimateOwner
	{
	public:
		 virtual DUIWindow* GetOwnerWindow() = 0;        
		virtual DMCode OnTabAnimateFinish() = 0;                         ///< ��������
	};

	/// <summary>
	///		 Tabҳ�����ֶ���
	/// </summary>
	class DM_EXPORT DUITabAnimate:public DUIWindow,public IDMTimeline
	{
		DMDECLARE_CLASS_NAME(DUIWindow,DUINAME_TabAnimate,DMREG_Window);
	public:
		DUITabAnimate(IDMTabAnimateOwner *pOwner, DUIWindowPtr pFrom, DUIWindowPtr pTo,int iSteps,int iType);

	public:
		DM_BEGIN_MSG_MAP()
			DM_MSG_WM_ERASEBKGND(DM_OnEraseBkgnd)
			DM_MSG_WM_PAINT(DM_OnPaint)
			MSG_WM_DESTROY(OnDestroy)
			MSG_WM_SIZE(OnSize)
		DM_END_MSG_MAP()
	public:
		BOOL DM_OnEraseBkgnd(IDMCanvas* pCanvas);
		void DM_OnPaint(IDMCanvas* pCanvas);
		void OnDestroy();
		void OnSize(UINT nType, CSize size);

	public:
		DMCode OnTimeline();
		void StopFrame();

	public: // ����
		void BitBlt(IDMCanvas* pCanvasDest,int xDest,int yDest,int nWid,int nHei,IDMCanvas *pCanvasSrc,int xSrc,int ySrc,DWORD rop);
		void MyCenterDeflateDraw(IDMCanvas *pCanvas);
		void MyCenterInflateDraw(IDMCanvas *pCanvas);
		void MySlideDraw(int iType,IDMCanvas *pCanvas);

	public:
		DMSmartPtrT<IDMCanvas>							m_pMemCanvas;
		int                                             m_iCurSteps;
		int                                             m_nStepCount;
		int                                             m_TabAniType;         ///< ��������
		IDMTabAnimateOwner*                             m_pOwner;
	};

}//namespace DM