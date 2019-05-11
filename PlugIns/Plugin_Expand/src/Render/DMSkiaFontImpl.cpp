#include "Plugin_ExpandAfx.h"
#include "DMSkiaFontImpl.h"

namespace DM
{

	DMSkiaFontImpl::DMSkiaFontImpl(LPLOGFONTW plf)
		:m_SkFont(NULL)
	{
		if (plf)
		{
			// SkTypeface���ĵ��ɲο�https://sites.google.com/site/skiadocs/developer-documentation/testing/using-gm-golden-master-baseline-tools-to-validate-results/gm-and-fonts
			memcpy(&m_lf, plf, sizeof(LOGFONTW));
#if 0
			char szFaceName[LF_FACESIZE*2] = {0};
			DM::UnicodeToUtf8(plf->lfFaceName,szFaceName, LF_FACESIZE*2);


			byte style = SkTypeface::kNormal;
			if (plf->lfItalic) 
			{
				style |= SkTypeface::kItalic;
			}

			if (FW_BOLD == plf->lfWeight)
			{
				style |= SkTypeface::kBold;
			}

			m_SkFont = SkTypeface::CreateFromName(szFaceName,(SkTypeface::Style)style);
#endif 
			m_SkFont = SkCreateTypefaceFromLOGFONT((const LOGFONTW)m_lf);
			//
			m_SkPaint.setTextSize(SkIntToScalar(abs(plf->lfHeight)));// ��������ߴ硣 
			m_SkPaint.setUnderlineText(!!plf->lfUnderline);
			m_SkPaint.setStrikeThruText(!!plf->lfStrikeOut);

			m_SkPaint.setTextEncoding(SkPaint::kUTF16_TextEncoding);
			m_SkPaint.setAntiAlias(true);// ȥ���
			m_SkPaint.setLCDRenderText(true);

			m_lf.lfQuality = CLEARTYPE_QUALITY;
			m_hFont = ::CreateFontIndirectW(&m_lf);
		}
	}

	DMSkiaFontImpl::~DMSkiaFontImpl()
	{
		if (m_SkFont)// �ͷţ���Ȼ���ڴ�й¶
		{
			m_SkFont->unref();
			m_SkFont = NULL;
		}
		DM_DELETE_OBJECT(m_hFont);
	}

	const LOGFONTW* DMSkiaFontImpl::GetLogFont() const
	{
		return &m_lf;
	}

	LPCWSTR DMSkiaFontImpl::GetFaceName()
	{
		return m_lf.lfFaceName;
	}

	bool DMSkiaFontImpl::IsUnderline()		
	{
		return !!m_lf.lfUnderline;
	}

	bool DMSkiaFontImpl::IsItalic()			
	{
		return !!m_lf.lfItalic;
	}

	bool DMSkiaFontImpl::IsStrikeOut()		
	{
		return !!m_lf.lfStrikeOut;
	}

	SkPaint DMSkiaFontImpl::GetSkPaint()
	{
		return m_SkPaint;
	}

	SkTypeface* DMSkiaFontImpl::GetSkTypeFace()
	{
		return m_SkFont;
	}

	HFONT DMSkiaFontImpl::GetFont()
	{
		return m_hFont;
	}

}//namespace DM