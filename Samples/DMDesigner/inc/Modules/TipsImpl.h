// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	TipsImpl.h
// File mark:   
// File summary:
// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2016-8-3
// ----------------------------------------------------------------
#pragma once

namespace DM
{
	class TipHWnd: public DMHWnd
	{  
	public:

	};

	/// <summary>
	///		DUI������ʽ��ʾtips
	/// </summary>
	class TipsImpl:public IDMToolTip,public DMCWnd
	{
		DMDECLARE_CLASS_NAME(TipsImpl,L"TipsImpl",DMREG_ToolTip);

	public:
		TipsImpl(void);
		virtual ~TipsImpl(void);

		bool Create();													///< ������ʱ�������ش���
		bool CreateTipsWnd();											///< ������ʵ����ʾ����

	public:
		//---------------------------------------------------
		// Function Des: ��Ϣ�ַ�ϵ�к���
		//---------------------------------------------------
		void OnTimer(UINT_PTR idEvent);	

	public:
		DMCode Update(PDMToolTipInfo pInfo);
		DMCode Hide();
		DMCode Clear();
		DMCode RelayEvent(const MSG *pMsg);
		BOOL PreTranslateMessage(MSG* pMsg);


	public:// ����
		void ShowTips(bool bShow);
		bool IsTipWindows(){return IsWindow()&&m_pWnd&&m_pWnd->IsWindow();}///< ���ش��ں���ʾ���ڶ�OK
		bool IsCursorPtInRect();
		void DestroyTipsWnd();

	public:
		DECLARE_MESSAGE_MAP()										// ��MFC��Ϣӳ���

	public:
		DMSmartPtrT<DMHWnd>			 m_pWnd;

	protected:
		int							 m_iDelayTime;
		int							 m_iSpanTime;
		CStringW					 m_strXmlId;
		CStringW					 m_strTip; 
		LPARAM                       m_dwReserve;
		CRect						 m_rcTarget;
		bool						 m_bShowing;                         ///< ��ʾ��ʱ�������ã������ڻ�δ��ʾ
		CRect                        m_rcPosFlags;
		CRect                        m_rcScreenTarget;
	};

}//namespace DM