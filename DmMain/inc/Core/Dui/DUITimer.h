//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DUISetTimer.h 
// File Des: DUI��ʱ��
// File Summary: ʹ��ԭ��ɲο�window��������嶨ʱ�������ַ�ʽ
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
	struct TIMERINFO
	{
		DUIWND			hDUIWnd;
		UINT_PTR		uTimerID;
	};

	/// <summary>
	///		 ȫ�ֵĶ�ʱ����ʹ��callback��ʽʵ��
	/// </summary>
	class DM_EXPORT DUITimer:public DMMapT<UINT_PTR, TIMERINFO>
	{
	public:
		DMCode SetTimer(DUIWND hDUIWnd,UINT_PTR uTimerID,UINT nElapse);	///< ���ö�ʱ��

		DMCode KillTimer(DUIWND hDUIWnd,UINT_PTR uTimerID);				///< ɾ����ʱ��(hDUIWnd+uTimerID����ͬ)
		DMCode KillTimer(DUIWND hDUIWnd);								///< ɾ����ʱ��(hDUIWnd��ͬ)

	public:
		static void CALLBACK TimerProc(HWND hwnd,UINT uMsg,UINT_PTR uRealTimeID,DWORD dwTime);
	};

	/// <summary>
	///		 ���ڵĶ�ʱ��,ͨ���ⲿSetTimer������
	/// </summary>
	class DM_EXPORT FastTimerID
	{
	public:
		FastTimerID(DUIWND hDUIWnd, char TimerId)
		{
			m_Flag		 = 1;
			m_hDUIWnd	 = hDUIWnd;
			m_dwTimerID  = TimerId;
		}

		FastTimerID(DWORD dwID)
		{
			memcpy(this,&dwID,sizeof(DWORD));
		}
		operator DWORD &() const// ����ǿ��ת����DWORD
		{
			return *(DWORD*)this;
		}

	public:
		DWORD    m_hDUIWnd:24;     
		DWORD    m_dwTimerID:7;     
		DWORD    m_Flag:1;          ///< ��־Ϊ1ʱ����ʾ�ö�ʱ��ΪDUI��ʱ��������Ϊ���λ��0x80000000
	};


}//namespace DM