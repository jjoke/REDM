//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMFontImpl.h 
// File Des: 
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-23	1.0			
//-------------------------------------------------------
#pragma once

namespace DM
{
	class DMFontImpl:public IDMFont
	{
	public:
		DMFontImpl(LPLOGFONTW plf);
		~DMFontImpl();
	public:
		virtual const LOGFONTW* GetLogFont() const;
		virtual LPCWSTR GetFaceName();				// ������
		virtual bool IsUnderline();				    // �Ƿ����»���
		virtual bool IsItalic();					// �Ƿ�Ϊб��
		virtual bool IsStrikeOut();				    // �Ƿ���ɾ����


	public:// ����
		HFONT  GetFont();

	protected:
		HFONT                                m_hFont;
		LOGFONTW                             m_lf;
	};



}//namespace DM