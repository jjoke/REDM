//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMTooltipImpl2.h 
// File Des: tips���߼�Ϊ:
//              1.DMHWnd����괦��������Tips��Ϣ����,����ȡ��ǰDUI����Ҫ��ʾ��tip��Ϣ���µ�DMtipImpl
//              2.PreTranslateMessage��Ϣ������ת����Ϣ��RelayEvent�ж���ʾ״̬
//                2.1.����Ŀ������,����δ����ʾ��ʱ��,����ʾ��ʱ��,�ӳ���ʾ
//                2.2.�粻��Ŀ��������,��ֱ��kill��ʾ��ʱ��,��ʧ
//              3.��ʾ��ʱ��������,����������ʧ��ʱ��.
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-7-13	1.0			
//-------------------------------------------------------
#pragma once

namespace DM
{
	class TGPTipHWnd: public DMHWnd
	{  
	public:

	};

	/// <summary>
	///		DUI������ʽ��ʾtips
	/// </summary>
	class TGPTipsImpl:public IDMToolTip,public DMCWnd
	{
		DMDECLARE_CLASS_NAME(TGPTipsImpl,L"TGPTipsImpl",DMREG_ToolTip);

	public:
		TGPTipsImpl(void);
		virtual ~TGPTipsImpl(void);

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
		DMSmartPtrT<TGPTipHWnd>		  m_pWnd;

	protected:
		int							 m_iDelayTime;
		int							 m_iSpanTime;
		CStringW					 m_strXmlId;
		CStringW					 m_strTip;        
		CRect						 m_rcTarget;
		bool						 m_bShowing;                         ///< ��ʾ��ʱ�������ã������ڻ�δ��ʾ
		CRect                        m_rcPosFlags;
		CRect                        m_rcScreenTarget;
	};

}//namespace DM