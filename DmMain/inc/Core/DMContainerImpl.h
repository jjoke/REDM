//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DUIContainer.h 
// File Des: �������ڸ����ַ�������Ϣ��DUI����.����DUI����״̬
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2014-11-6	1.0			
//-------------------------------------------------------
#pragma once
#include "DUIFocusMgr.h"
#include "DUIDropTargetDispatch.h"

namespace DM
{
	class DM_EXPORT DMContainerImpl:public IDMContainer
	{
	public:
		DMContainerImpl(DUIWindow *pHWnd);

	public:
		LRESULT OnFrameEvent(UINT uMsg,WPARAM wp,LPARAM lp);

		DMCode OnSetFocusWnd(DUIWND DUIWnd);
		DMCode OnGetFocusWnd(DUIWND &DUIWnd);

		DMCode OnSetCaptureWnd(DUIWND DUIWnd,DUIWNDPtr pOldDUIWnd=NULL);
		DMCode OnGetCaptureWnd(DUIWND &DUIWnd);
		DMCode OnReleaseCaptureWnd();

		DMCode OnRegisterDragDrop(DUIWND hDUIWnd, IDropTarget *pDropTarget);
		DMCode OnUnRegisterDragDrap(DUIWND hDUIWnd);

		//---------------------------
		// δʵ��
		DMCode OnFireEvent(DMEventArgs &Evt){return DM_ECODE_NOTIMPL;}
		DMCode OnGetDraw(IDMDraw** ppObj){return DM_ECODE_NOTIMPL;}
		DMCode OnGetCanvas(LPCRECT lpRect,DWORD dcFlags,IDMCanvas**ppCanvas){return DM_ECODE_NOTIMPL;}
		DMCode OnReleaseCanvas(LPCRECT lpRect,DWORD dcFlags,IDMCanvas*pCanvas){return DM_ECODE_NOTIMPL;}
		HWND   OnGetHWnd(){return NULL;}
		DMCode OnGetContainerRect(LPRECT lpRect){return DM_ECODE_NOTIMPL;}
		DMCode OnIsTranslucent(){return DM_ECODE_NOTIMPL;}
		DMCode OnUpdateWindow(){return DM_ECODE_NOTIMPL;}
		DMCode OnForceUpdateWindow(){return DM_ECODE_NOTIMPL;}
		DMCode OnUpdateRect(LPCRECT lpRect,DUIWND hDUIWnd){return DM_ECODE_NOTIMPL;}
		DMCode OnClientToScreen(LPRECT lpRect){return DM_ECODE_NOTIMPL;}
		DMCode OnIsSizChanging(){return DM_ECODE_NOTIMPL;}

		//---------------------------
		IDMAccelMgr* GetAccelMgr(){return &m_FocusMgr;}

		//---------------------------
		DMCode OnRegisterTimeline(IDMTimeline *pHandler);
		DMCode OnUnregisterTimeline(IDMTimeline *pHandler);
		DMCode OnTimeline();

	public:// ����
		void OnFrameMouseMove(UINT uFlag,CPoint pt);
		void OnFrameMouseEvent(UINT uMsg,WPARAM wParam,LPARAM lParam);
		void OnFrameMouseLeave();

		DMCode OnFrameSetCursor(const CPoint &pt);
		void OnFrameKeyEvent(UINT uMsg,WPARAM wParam,LPARAM lParam);
		void OnFrameKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

		void OnActivate(UINT nState);
		void OnActivateApp(BOOL bActive, DWORD dwThreadID);

	public:

		DUIWindow*					     m_pContainWnd;              ///<�˴���������һ��Ϊ��������(DMHWnd��DMHDialog),�������ָ��崰��
		DUIWND                           m_hDUICaptureWnd;			 ///<��ǰ������Ϣ��DUI����
		DUIWND                           m_hDUIHoverWnd;			 ///<��ǰͣ����DUI����
		bool                             m_bNcHover;			     ///<��ǰ�Ƿ�ͣ���ڷǿͻ���

		DUIFocusMgr						 m_FocusMgr;
		DUIDropTargetDispatch			 m_DropTarget;
		typedef CList<IDMTimelinePtr> DMTimelineHanderList;
		DMTimelineHanderList		     m_TimelineList;
	};
}//namespace DM