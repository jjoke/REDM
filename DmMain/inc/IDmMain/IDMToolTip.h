//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: IDMToolTip.h 
// File Des: IDMToolTip�Ƕ�tooltip�ĳ�����
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-3-3	1.0			
//-------------------------------------------------------
#pragma once

namespace DM
{
	typedef struct stDMToolTipInfo
	{
		stDMToolTipInfo()
		{
			hDUIWnd = 0;iDelayTime = 500;iSpanTime = 5000;dwReserve = 0;rcPosFlags.SetRect(-1,0,0,0);
		}
		DUIWND		hDUIWnd;		 ///< ӵ��tooltip��DUI���ھ��
		int         iDelayTime;      ///< ��ʱ��ʾ
		int         iSpanTime;       ///< ��ʱ��ʧ
		CRect		rcTarget;		 ///< tooltip��Ӧ��
		CStringW	strTip;			 ///< tooltip�ַ���
		CStringW	strXmlId;        ///< tooltip��xml
		CRect       rcPosFlags;		 ///< ����TrackPopupMenu�Ĳ�����ǰ����ֱ����UINT uFlags, int x, int y,��������ڱ�ʾǿ�ƹ̶���Ϊ0��ʾ��ǿ�ƹ̶�������Ļ����ʱ���Զ�����
		CRect       rcScreenTarget;  ///< rcTargetΪ������䴰�ڵĿͻ�����rcScreenTargetΪ��Ļ����
		
		LPARAM      dwReserve;       ///< ����
	}DMToolTipInfo,*PDMToolTipInfo;

	/// <summary>
	///		ToolTip������չ�ӿ�,classtype=<see cref="DMREG_ToolTip"/>
	/// </summary>
	class DM_EXPORT IDMToolTip:public DMBase,public IDMMessageFilter
	{
		DMDECLARE_CLASS_NAME(IDMToolTip,L"IDMToolTip",DMREG_ToolTip);
	public:
		virtual DMCode Update(PDMToolTipInfo pInfo) = 0;					///< ���²�������ʾ��ʱ��
		virtual DMCode Hide() = 0;											///< ֱ������
		virtual DMCode Clear() = 0;											///< ������
		virtual DMCode RelayEvent(const MSG *pMsg) = 0;                     ///< ת����Ϣ
	};
}
