//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DUIItemPanel.h 
// File Des: DUI�������
// File Summary:  
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-3-11	1.0			
//-------------------------------------------------------
#pragma once

namespace DM
{
	class DUIItemPanel;
	/// <summary>
	///		����ӵ����
	/// </summary>
	class DM_EXPORT IDMItemPanelOwner
	{
	public:
		virtual DUIWindow* GetOwnerWindow() = 0;   
		virtual DMCode OnSetCapture(DUIItemPanel* pPanel) = 0;
		virtual DMCode OnReleaseCapture(DUIItemPanel* pPanel) = 0;
		virtual DMCode OnGetPanelRect(DUIItemPanel* pPanel,LPRECT lpRect) = 0; ///< ��ʹ��*lpRect��ֵ��
	};

	/// <summary>
	///		��������ʵ��
	/// </summary>
	class DM_EXPORT DUIItemPanel:public DUIWindow,public DMContainerImpl
	{
	public:
		DUIItemPanel(DMXmlNode XmlNode, IDMItemPanelOwner *pItemOwner = NULL);
		~DUIItemPanel();

	public://����
		void DrawItem(IDMCanvas* pCanvas, CRect& rc);
		void ModifyState(DWORD dwStateAdd, DWORD dwStateRemove);
		void SetItemId(LPARAM id);										///< ���ñ�ʶ,��֤��һ����������Ψһ��
		LPARAM GetItemId();
		
	public:
		virtual void OnFinalRelease();

	public:// ����
		DMCode OnSetCaptureWnd(DUIWND DUIWnd,DUIWNDPtr pOldDUIWnd=NULL);
		DMCode OnReleaseCaptureWnd();
		DMCode OnGetContainerRect(LPRECT lpRect);                       ///< ��ȡ����������

	public:// ����IDMContainer
		LRESULT OnFrameEvent(UINT uMsg,WPARAM wp,LPARAM lp);
		DMCode OnFireEvent(DMEventArgs &Evt);							///< ��ԭʼ��Ϣ��װ�������Ϣ,�����Ϣ�д���ԭʼ��Ϣ
		DMCode OnGetDraw(IDMDraw** ppObj);
		DMCode OnGetCanvas(LPCRECT lpRect,DWORD dcFlags,IDMCanvas**ppCanvas);
		DMCode OnReleaseCanvas(LPCRECT lpRect,DWORD dcFlags,IDMCanvas*pCanvas);
		HWND OnGetHWnd();											    ///< ת��
		DMCode OnIsTranslucent();                                       ///< ת��
		DMCode OnUpdateWindow();										///< ת��
		DMCode OnForceUpdateWindow();									///< ת��
		DMCode OnUpdateRect(LPCRECT lpRect,DUIWND hDUIWnd);             ///< ����ڿؼ�����ˢ��
		DMCode OnClientToScreen(LPRECT lpRect);                         ///< ת��  
		DMCode OnRegisterTimeline(IDMTimeline *pHandler);				///< ת��
		DMCode OnUnregisterTimeline(IDMTimeline *pHandler);				///< ת��
		CStringW OnGetTransId();										///< ת��

	public:// ����DUIWindow
		bool DV_IsStateChangeRedraw(){return true;}
		DMCode DV_OnUpdateToolTip(CPoint pt, DMToolTipInfo &tipInfo);	///< ת��

	public:// ����
		bool PreHandleFrameEvent(UINT uMsg,WPARAM wp,LPARAM lp);        ///< Ԥ������Ϣ,������������屳����״̬

	public:
		DUIWindow*                                  m_pDUIWnd;			///< ��������ڵ�DUI����
		IDMItemPanelOwner*                          m_pItemOwner;		///< ӵ�����������������ں��ⲿ������
		LPARAM										m_dwData;			///< ��������
		LPARAM										m_dwItemId;         ///< ����Ψһ�ⲿ��ʶ
	};

}//namespace DM
