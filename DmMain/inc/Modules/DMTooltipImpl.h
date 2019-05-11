//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMTooltipImpl.h 
// File Des: Tooltip���߼�Ϊ:
//              1.DMHWnd����괦��������ToolTip��Ϣ����,����ȡ��ǰDUI����Ҫ��ʾ��tip��Ϣ���µ�DMTooltipImpl
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
//      guoyou		2015-1-29	1.0			
//-------------------------------------------------------
#pragma once

namespace DM
{
	class DM_EXPORT DMTooltipImpl:public IDMToolTip,public DMCWnd
	{
		DMDECLARE_CLASS_NAME(DMTooltipImpl,L"DMTooltipImpl",DMREG_ToolTip);
	public:
		DMTooltipImpl(void);
		virtual ~DMTooltipImpl(void);

		bool Create();
	public:
		//---------------------------------------------------
		// Function Des: ��Ϣ�ַ�ϵ�к���
		//---------------------------------------------------
		void OnPaint(HDC hdc);
		void OnTimer(UINT_PTR idEvent);

	public:
		DMCode Update(PDMToolTipInfo pInfo);
		DMCode Hide();
		DMCode Clear();
		DMCode RelayEvent(const MSG *pMsg);
		BOOL PreTranslateMessage(MSG* pMsg);

	public:// ����
		void ShowTooltip(bool bShow);
	
	public:
		DECLARE_MSG_MAP()										// ��MFC��Ϣӳ���

	protected:
		int						  m_iDelayTime;
		int						  m_iSpanTime;
		CStringW				  m_strTip;
		CRect					  m_rcTarget;
		HFONT					  m_font;
		bool                      m_bShowing;                       // ��ʾ��ʱ�������ã������ڻ�δ��ʾ
	};
}//namespace DM