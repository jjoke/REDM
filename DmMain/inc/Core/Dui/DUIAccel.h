//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMAccel.h 
// File Des: Accel�ӿ�
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-2-4	1.0			
//-------------------------------------------------------
#pragma once

#ifndef NOHOTKEY
#define HOTKEYF_SHIFT           0x01
#define HOTKEYF_CONTROL         0x02
#define HOTKEYF_ALT             0x04
#endif 

namespace DM
{
	/// <summary>
	///		���ټ�ת��
	/// </summary>
    class DM_EXPORT DUIAccel
    {
    public:
        DUIAccel(DWORD dwAccel);							///< dwAccel���ټ�ֵ
        DUIAccel(UINT vKey=0,bool bCtrl=false,bool bAlt=false,bool bShift=false);///< UINT vKey��Ctrl��ϡ���Alt��ϡ���Shilft���
        ~DUIAccel(void);

        CStringW GetKeyName(WORD vk);					    ///< ������ֵת��Ϊ��Ӧ���ַ���
        CStringW FormatHotkey();						    ///< ��õ�ǰ���ټ����ַ�����ʽ

        WORD GetModifier() const {return m_wModifier;}	    ///< ��ü��ټ�������λ
        WORD GetKey() const {return m_wVK;}				    ///< ��ü��ټ�������
	
        static DWORD TranslateAccelKey(LPCWSTR lpszAccelKey);	///< �������ַ�����Ӧ�ļ��ټ�ֵ

    protected:
        WORD					 m_wModifier;
        WORD					 m_wVK;
    };


	/// <summary>
	///		���̼��ټ����¼��������ӿ�
	/// </summary>
    class DM_EXPORT IDMAccelHandler
    {
	public:
		/// -------------------------------------------------
		/// @brief obj�Ƿ����
		/// @param[in]		 Accel    ���µļ��ټ�
		/// @return ���ټ���������true
        virtual bool OnAccelPressed(const DUIAccel& Accel) = 0;
    };

	/// <summary>
	///		���ټ��������ӿ�
	/// </summary>
    class DM_EXPORT IDMAccelMgr
    {
	public:
        virtual void RegisterAccel(const DUIAccel& Accel, IDMAccelHandler* pHandler) = 0;	///< ע����ټ��Լ��¼�����ӿڶ���
        virtual void UnregisterAccel(const DUIAccel& Accel,IDMAccelHandler* pHandler) = 0;	///< ��ע����ټ��Լ��¼�����ӿڶ���
        virtual void UnregisterAccels(IDMAccelHandler* pHandler) = 0;						///< ��ע���¼�����ӿڶ�������м��ټ�
    };

}//namespace DM