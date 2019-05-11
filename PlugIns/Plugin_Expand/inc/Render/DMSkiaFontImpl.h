//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMSkiaFontImpl.h 
// File Des: 
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-8-19	1.0			
//-------------------------------------------------------
#pragma once

namespace DM
{
	class DMSkiaFontImpl:public IDMFont
	{
	public:
		DMSkiaFontImpl(LPLOGFONTW plf);
		~DMSkiaFontImpl();
	public:
		virtual const LOGFONTW* GetLogFont() const;
		virtual LPCWSTR GetFaceName();				// ������
		virtual bool IsUnderline();				    // �Ƿ����»���
		virtual bool IsItalic();					// �Ƿ�Ϊб��
		virtual bool IsStrikeOut();				    // �Ƿ���ɾ����

	public:// ����
		SkPaint GetSkPaint();
		SkTypeface* GetSkTypeFace();
		HFONT  GetFont();

	protected:
		// SkTypeface����ָ���������񣬿������������ͻ������֣�Ҳ����˵�����������ڻ����ı������������������ı�
		SkTypeface                          *m_SkFont;	 // ��������
		SkPaint                              m_SkPaint;  // �������ֻ�������
		LOGFONTW                             m_lf;
		HFONT                                m_hFont;
	};

}//namespace DM