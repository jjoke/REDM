// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	DMTransImpl.h
// File mark:   
// File summary:�����������ʵ��
// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2016-11-21
// ----------------------------------------------------------------
#pragma once
#include "DMTransHelper.h"

namespace DM
{
	/// <summary>
	///		�������԰��Ĵ���ʾ��
	/// </summary>
	class DMTransImpl : public IDMTrans,public DMArrayT<DMLanguageItemPtr>
	{
		DMDECLARE_CLASS_NAME(DMTransImpl,L"DMTransImpl",DMREG_Trans);
	public:
		DMTransImpl();
		~DMTransImpl();

		DMCode LoadTrans(WPARAM wp, LPARAM lp);
		DMCode SetTrans(CStringW strLanguageName);
		DMCode AddTransItem(CStringW strSrc, CStringW strTrans,CStringW strNodeName = L"",CStringW strLanguageName = L"");
		CStringW GetTrans(CStringW strSrc,CStringW strNodeName = L"",CStringW strLanguageName = L"");

	public:// ����
		DMLanguageItemPtr FindLanguageItemPtr(CStringW strLanguageName);

	protected:
		virtual void PreArrayObjRemove(const DMLanguageItemPtr &obj);
		virtual bool EqualArrayObj(const DMLanguageItemPtr &objsrc, const DMLanguageItemPtr &objdest);

	public:
		DMLanguageItemPtr			      m_pCurLanguage;			  ///< ��ǰʹ�õ����԰�
		CStringW                          m_strCurLanguageName;       ///< ��ǰʹ�õ�theme Key
	};
}//namespace DM