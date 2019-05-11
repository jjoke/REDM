//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: IDMStyle.h  
// File Des: IDMStyle�ṩStyle�ĸ��ֶ���ӿ�
// File Summary: �ο�Android Drawable
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-28	1.0			
//-------------------------------------------------------
#pragma once

namespace DM
{
	/// <summary>
	///		 ���Գ�����,classtype=<see cref="DMREG_Skin"/>
	/// </summary>
	/// <remarks>
	///		���ֽӿ�δʵ�ֵģ��᷵��DM_ECODE_NOTIMPL
	/// </remarks>
	class IDMStyle:public DMBase
	{
		DMDECLARE_CLASS_NAME(IDMStyle,L"IDMStyle",DMREG_Style);
	public:
		/// -------------------------------------------------
		/// @brief			ȡ��ÿ��ʵ����Style�����ΨһID    
		/// @return			DMCode
		virtual DMCode GetID(wchar_t* lpszId, int iSize) = 0;
		virtual DMCode CopyData(IDMStyle* pStyle) = 0;

		//---------------------------------------------------
		// Function Des: �ı����
		//---------------------------------------------------
		virtual DMCode GetTextAlign(UINT &ulAlign) = 0;                                          ///<��ȡ�ı�Format
		virtual DMCode GetTextColor(int iState,DMColor &Clr) = 0;                                ///<ȡ��״̬�ı���ɫ
		virtual DMCode GetTextFont(int iState, IDMFont** ppFont) = 0;                            ///<ȡ��״̬����,�ڲ��������ü������ⲿ�ͷ� 
		virtual DMCode GetTextStates(int &iState) = 0;											 ///<ȡ���ı�״̬��
	
		//---------------------------------------------------
		// Function Des: ������
		//---------------------------------------------------
		virtual DMCode GetCursor(HCURSOR &hCursor) = 0;											 ///<ȡ�ù����

		//---------------------------------------------------
		// Function Des: �������
		//---------------------------------------------------
		virtual DMCode GetBgSkin(IDMSkin** ppSkin) = 0;											 ///<ȡ�ñ���skin
		virtual DMCode GetBgColor(int iState,DMColor &Clr) = 0;                                  ///<ȡ�ñ�����ɫ	
		virtual DMCode GetBgClrStates(int  &iState) = 0;                                         ///<ȡ�ñ���(�ͻ�-�ǿͻ�)��ɫ״̬��

		virtual DMCode GetNcMargin(LPRECT lpRect) = 0;				                             ///<ȡ�÷ǿͻ����ı߿�
		virtual DMCode GetNcColor(int iState, DMColor &Clr) = 0;                                 ///<ȡ�÷ǿͻ�����ɫ
		virtual DMCode GetNcSkin(IDMSkin** ppSkin) = 0;											 ///<ȡ�÷ǿͻ���skin

		virtual DMCode GetAlpha(byte &alpha) = 0;												 ///<ȡ�ô���͸����
	};
	typedef IDMStyle* IDMStylePtr;

}//namespace DM