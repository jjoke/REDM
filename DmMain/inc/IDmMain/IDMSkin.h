//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: IDMSkin.h  
// File Des: IDMSkin��һ��ͨ�õĳ����࣬����Ŀ���Ǹ�������ô��һ��������Canvas��
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
	///		Ƥ��������,��״̬ͼ��9���񡢶�����,classtype=<see cref="DMREG_Skin"/>
	/// </summary>
	/// <remarks>
	///		���ֽӿ�δʵ�ֵģ��᷵��DM_ECODE_NOTIMPL
	/// </remarks>
	class IDMSkin:public DMBase
	{
		DMDECLARE_CLASS_NAME(IDMSkin,L"IDMSkin",DMREG_Skin);
	public:
		/// -------------------------------------------------
		/// @brief			ȡ��ÿ��ʵ����Skin�����ΨһID    
		/// @return			DMCode
		virtual DMCode GetID(wchar_t* lpszId, int iSize) = 0;											              
		virtual	DMCode Draw(IDMCanvas *pCanvas, LPCRECT lpRectDraw, int iState,BYTE alpha=0xFF) = 0;	///<��״̬����
		virtual DMCode GetStateSize(SIZE &sz, int iState=0) = 0;                                        ///<ȡ��ָ��״̬�Ĵ�С
		virtual DMCode GetStates(int &iStates) = 0;													    ///<ȡ��״̬��
		virtual DMCode GetBitmap(IDMBitmap** ppBitmap) = 0;                                             ///<ȡ��bitmap
		virtual DMCode SetBitmap(LPBYTE pBuf,size_t szLen,LPCWSTR pszType) = 0;							///<ͨ���ڴ�����bitmap
		virtual DMCode UpdateSkin(WPARAM wp, LPARAM lp) = 0;										    ///<����
		virtual DMCode IsValid() = 0;                                                                   ///<�ж�skin�Ƿ���Ч�������Ч,�ڲ�skin�ؽ��Զ��Ƴ���skin
	};
	typedef IDMSkin* IDMSkinPtr;

}//namespace DM