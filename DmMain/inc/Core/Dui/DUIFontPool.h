//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DUIFontPool.h 
// File Des:// font="face:����,size:0,weight:400,charset:0,underline:1,italic:1,strike:1",face:��weight:���λ������:������1λ,����ո�!�ڲ����˿ո�ȥ������
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-30	1.0			
//-------------------------------------------------------
#pragma once

namespace DM
{
	typedef IDMFont*  IDMFontPtr;
	/// <summary>
	///		��������ĳ�
	/// </summary>
	/// <remarks>
	///		������Ϊ�˷���gtest����
	/// </remarks>
	class DM_EXPORT DUIFontPool:public DMMapT<CStringW,IDMFontPtr>
	{
	public:
		DUIFontPool();
		~DUIFontPool();

	public:
		bool SetDefaultFont(const CStringW& strFont);				///< ����Ĭ������
		IDMFontPtr GetFont(const CStringW& strFont);				///< ��ȡ����,��strFontΪNULL��ʾ��ȡĬ������
		
	public:// ����
		virtual void PreMapKeyRemove(const IDMFontPtr &obj);

	protected:
		CStringW GetFontKey(const LPLOGFONTW lpLogFont);
		bool GetLogFont(const CStringW& strFont,LPLOGFONTW lpLogFont);

	protected:
		LOGFONTW				m_lfDefault;					   ///< Ĭ������
		wchar_t					m_szDefFontFace[LF_FACESIZE];      ///< Ĭ����������
	};

}//namespace DM