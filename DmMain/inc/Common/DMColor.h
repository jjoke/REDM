//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMColor.h 
// File Des:
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-7	1.0			
//-------------------------------------------------------
#pragma once

namespace DM
{
#define GetAValue(rgb)		 (LOBYTE((rgb)>>24))
#define RGBA(r,g,b,a)		 (RGB(r,g,b)|(a<<24))
#define	DMCLR_INVALID		  0x00FFFFFF				  ///< ��������Alpha����ȻGDI�޷���ʾ
#define BGR(b,g,r)           ((DWORD)(((BYTE)(b)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(r))<<16)))
#define PBGRA(b,g,r,a)       ((DWORD)(BGR(b,g,r)|(a<<24)))///<��ע����PBGRA,����Ԥ��alpha���ף�
	/// <summary>
	///		ͼ�ν�����������DIBĬ�ϴӵ͵���λ��BGRA
	///     ��RGBA(COLORREF)Ĭ�ϴӵ͵���λ��RGBA
	///     DM�ڲ�Ĭ��ʹ��BGRA
	///     ͳһʹ��PBGRA
	/// </summary>
	class DM_EXPORT DMColor
	{
	public:
		DMColor();
		DMColor(BYTE r,BYTE g,BYTE b,BYTE a=0xFF);
		DMColor(DWORD clr);///<ʹ��DWORD���캯��������ֱ��ʹ��PBGRA��ֵ

		const COLORREF ToCOLORREF() const;							 ///< ת����COLORREF,����alpha��Ϊ0
		const DWORD	   ToBGRA() const;		

		void SetRGBA(BYTE R,BYTE G,BYTE B,BYTE A);
		void SetbyBGRA(DWORD Clr);									 ///< clrΪBGRA��ʽ

		static DMColor PreMultiPly(DMColor clr,BYTE alpha);          ///< ȫ��Ԥ��
		void PreMultiply(BYTE alpha);								 ///< Ԥ��
		bool IsDefault(){return 0==b&&0==g&&0==r&&0xff==a;}          ///< �Ƿ�Ĭ��ɫ     
		bool IsTranslucent(){return 0==a;}                           ///< �Ƿ�͸��
		bool IsTextInvalid(){return 0==a&&0xff==b&&0xff==g&&0xff==r;}///< ����͸����Ϊ0����Ϊ����Ч����ɫ
		void SetTextInvalid(){a=0;g=b=r=0xff;}						 ///< ������Ч����ɫ

		bool operator==(DMColor& obj) const throw()
		{
			return b == obj.b&&g == obj.g&&r == obj.r&&a == obj.a;
		}

		bool operator!=(DMColor& obj) const throw()
		{
			return b != obj.b|| g != obj.g||r != obj.r||a != obj.a;
		}

	public:
		DWORD						b:8;
		DWORD						g:8;
		DWORD						r:8;
		DWORD						a:8;
	};

}//namespace DM