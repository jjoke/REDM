//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DUIStatic.h 
// File Des: ����staticʵ��
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-2-28	1.0			
//--------------------------------------------------------
#pragma once

namespace DMAttr
{
	/// <summary>
	///		<see cref="DM::DUIStatic"/>��xml���Զ���
	/// </summary>
	class DUIStaticAttr:public DUIWindowAttr
	{
	public:
		static wchar_t* bool_bmultiLines;                                     ///< �Ƿ�֧�ֶ���,ʾ��:bmultiLines="1"
		static wchar_t* INT_lineinter;                                        ///< �м��,Ĭ��Ϊ5��ʾ��:lineinter="5"
	};
	DMAttrValueInit(DUIStaticAttr,bool_bmultiLines)DMAttrValueInit(DUIStaticAttr,INT_lineinter)
}

namespace DM
{
	/// <summary>
	///		 DUIStatic������ʵ��
	/// </summary>
	class DM_EXPORT DUIStatic:public DUIWindow
	{
		DMDECLARE_CLASS_NAME(DUIStatic,DUINAME_Static,DMREG_Window);
	public:
		DUIStatic();

		//---------------------------------------------------
		// Function Des: ����DUIWindow
		//---------------------------------------------------
		DMCode DV_DrawText(IDMCanvas* pCanvas, LPCWSTR pszBuf,int cchText,LPRECT lpRect,UINT uFormat);

	public:
		DM_BEGIN_ATTRIBUTES()
			DM_bool_ATTRIBUTE(DMAttr::DUIStaticAttr::bool_bmultiLines, m_bMultiLines, DM_ECODE_OK)
			DM_INT_ATTRIBUTE(DMAttr::DUIStaticAttr::INT_lineinter, m_nLineInter, DM_ECODE_OK)
		DM_END_ATTRIBUTES()
	public:
		bool                                m_bMultiLines;
		int                                 m_nLineInter;
	};

}//namespace DM