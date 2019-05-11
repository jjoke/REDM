//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: IDMContainer.h 
// File Des: �������ⲿֻ�ܼ̳У��޷�ֱ��ע�ᵽ�ڲ�ʹ��
// File Summary: ���ڸ����ַ�������Ϣ��DUI����.����DUI����״̬
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-2-4	1.0			
//-------------------------------------------------------
#pragma once

namespace DM
{
	/// <summary>
	///		ȫ�ֶ�ʱ����չ����
	/// </summary>
	class IDMTimeline
	{
	public:
		virtual DMCode OnTimeline()=0;
	};
	typedef IDMTimeline* IDMTimelinePtr;

	/// <summary>
	///		������չ����
	/// </summary>
	class DM_EXPORT IDMContainer
	{
	public:
		virtual ~IDMContainer(){}

		virtual LRESULT OnFrameEvent(UINT uMsg,WPARAM wp,LPARAM lp) = 0;					///<�ַ���Ϣ�������ڵĸ�DUI���ڣ��ǳ���Ҫ��

		virtual DMCode OnSetFocusWnd(DUIWND DUIWnd) = 0;									///<���õ�ǰ�н����DUI����
		virtual DMCode OnGetFocusWnd(DUIWND &DUIWnd) = 0;									///<��ȡ��ǰ�н����DUI����

		virtual DMCode OnSetCaptureWnd(DUIWND DUIWnd,DUIWNDPtr pOldDUIWnd=NULL) = 0;	    ///<����������ָ��DUI���ڽ���
		virtual DMCode OnGetCaptureWnd(DUIWND &DUIWnd) = 0;									///<��ȡ������ӵ�н����DUI����
		virtual DMCode OnReleaseCaptureWnd() = 0;											///<�ͷŽ���

		virtual DMCode OnRegisterDragDrop(DUIWND hDUIWnd, IDropTarget *pDropTarget) = 0;    ///<��ָ��DUI����ע���ϷŶ���
		virtual DMCode OnUnRegisterDragDrap(DUIWND hDUIWnd) = 0;						    ///<��ע���Ϸ�

		virtual DMCode OnFireEvent(DMEventArgs &Evt) = 0;									///<��Ϣ�ַ�

		//----------------------------------------------
		// ��������ץȡ�����ڵ����򲿷ֱ���,�ٺ�ָ����ǰ��������
		virtual DMCode OnGetDraw(IDMDraw** ppObj) = 0;
		virtual DMCode OnGetCanvas(LPCRECT lpRect,DWORD dcFlags,IDMCanvas**ppCanvas) = 0;	///<��ȡ����,�����ɰ�����ǰ�����ĵ�ǰ����״̬
		virtual DMCode OnReleaseCanvas(LPCRECT lpRect,DWORD dcFlags,IDMCanvas*pCanvas) = 0;///<�ͷŻ���

		//----------------------------------------------
		// ��ǰ���������������
		virtual HWND   OnGetHWnd() = 0;													    ///<��ȡ��ǰ������������				
		virtual DMCode OnGetContainerRect(LPRECT lpRect) = 0;								///<��ȡ����������ʹ��*lpRect��ֵ��
		virtual DMCode OnIsTranslucent() = 0;												///<�Ƿ�ֲ㴰��
		virtual DMCode OnUpdateWindow() = 0;												///<����ϵͳUpdateWindow				
		virtual DMCode OnForceUpdateWindow() = 0;											///<ǿ����������ˢ��									
		virtual DMCode OnUpdateRect(LPCRECT lpRect,DUIWND hDUIWnd) = 0;						///<������Ч��
		virtual DMCode OnClientToScreen(LPRECT lpRect) = 0;                                 ///<��������ӿؼ�ת������Ļ����
		virtual DMCode OnIsSizChanging() = 0;                                               ///<�����ж������Ƿ����ڲ���

		//----------------------------------------------
		// �������
		virtual IDMAccelMgr* GetAccelMgr() = 0;

		//----------------------------------------------
		// ����֡���
		virtual DMCode OnRegisterTimeline(IDMTimeline *pHandler) = 0;						///< ע��ʹ��ȫ�ֶ�ʱ��
		virtual DMCode OnUnregisterTimeline(IDMTimeline *pHandler) = 0;						///< ��ע�᲻ʹ��ȫ�ֶ�ʱ��
		virtual DMCode OnTimeline() = 0;													///< ��Ҫ�ڶ���֡�е���OnRegisterTimeline��OnUnregisterTimeline
	
		//----------------------------------------------
		// ���԰����
		virtual CStringW OnGetTransId() = 0;												///< �������԰��ض�id,������ΪNULL,��Ĭ�ϴ�custom�в���,����,���ȴӴ��ض�id����,�鲻��,��ȥcustom
	};
	typedef IDMContainer* IDMContainerPtr;

}//namespace DM