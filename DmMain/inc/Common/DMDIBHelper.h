//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMDIBHelper111.h��DibBase_Hgy.h ��
// File Des: DIB���������ӿ��࣬�˴������DibBase_Hgy.h 2011��汾��д
// File Summary: ѧϰʹ�÷�ʽ���Բο�gtest-DMDIBHelper_Test.cpp
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2011-12-31	1.0			
//      guoyou      2014-10-14  1.1           ��ȡ���ֹ���֧�ֻ���DIB����
//-------------------------------------------------------
#pragma once
#include "DMColor.h"

namespace DM
{
	/// <summary>
	///		���汾�����ȥ���˶�8��16��24λ��֧��,
	///     ֻ֧��32λBI_RGB���������϶���ɨ���DIBSection��ע�������϶��£�����CreateDIBSection��nHei���ڲ�ʹ�����为ֵ��
	/// </summary>
	class DM_EXPORT DMDIBHelper
	{
		enum{Red,Green,Blue};
		struct  AlphaCheck
		{
			bool bActive;            // ���ṹ�е����������Ƿ����
			bool bSameAlpha;         // DIB����ͬ��Alpha
			byte Alpha;              // alphaֵ
		};

	public:
		DMDIBHelper();
		virtual~DMDIBHelper();
		void DIBRelease();

	public:
		static HBITMAP CreateDIBSection(HDC hdc,int nWid,int nHei,void** ppBits);
		static bool AlphaBlend32(DMDIBHelper* pDest, int nX, int nY, int nWd, int nHd, DMDIBHelper*pSrc,int nX2,int nY2,int nWs, int nHs,int nAlpha);

	public:

		/// <summary>
		///     ����DIBSection
		/// </summary>
		/// <returns>�������HBITMAP</returns>
		HBITMAP CreateDIBSection(HDC hdc, int nWid,int nHei);

		//---------------------------------------------------
		// Function Des:alpha����,�˲��ֹ��ܺ���ʹ��MMX�Ż�
		//---------------------------------------------------
		void  AdjustAlpha(byte byAlpha);  ///< ��������alpha
		void  AdjustAlphaRect(byte byAlpha, LPRECT lpRect);
		void  AlphaCheckInit();			  ///< check���������Ƿ�����ͬ��alpha
		void  AlphaCheckUninit();		  ///< ��check
		void  AlphaBackup(LPRECT lpRect); ///< <see cref="AlphaRestore"/> ����ɶԳ��֣�
		void  AlphaRestore();			  ///< <see cref="AlphaBackup"/>  ����ɶԳ��֣�
	   
		/// <summary>
		///     H:-180~180���ȣ�,=0��������, S/L:0~200(���飬���ֵ��>200),=100��������
		/// </summary>
		/// <remarks>
		///     HSL�任,HSL�����������ڷ�Ԥ�����������½��У���Ϊ�˸����Ч�ʣ�Ŀǰ����Ԥ����������
		///     HSL�任Ӧ���������������в��ٱ仯ʱ��ʼ������.��Ȼԭʼ�������оͲ���׼ȷ
		/// </remarks>
		/// <returns>�������HBITMAP</returns>
		bool AdjustHSL32(int H, int S, int L);
		bool AdjustHSL32Rect(int H, int S, int L,LPRECT lpRect);
		bool ResetHSL32(void);
		
		DMColor GetPixel(int x, int y);
		bool SetPixel(int x, int y, DMColor clr);
		BYTE GetAlpha(int x, int y);
		bool SetAlpha(int x, int y, BYTE alpha);

		
		bool GreyImage(void); 

		/// <summary>
		///    ���԰����ǿ��ٵĹ۲�����д�����е�ÿ֡�仯,���Ƶ������Ƿ���ȷ
		///    ��򵥵�ʹ�÷�ʽ��ֱ�Ӵ�windowͼ�β鿴���鿴�����ͼƬ(����Ҳ���Զ��仯)
		/// </summary>
		bool SaveFile(LPCWSTR pszFileName);			

		inline PVOID GetPixelBits(void)       const	{ return m_pPixelBits;}
		inline PVOID GetPixelCopyBits(void)   const	{ return NULL!=m_pPixelCopyBits?m_pPixelCopyBits:m_pPixelBits;}
		inline int  GetWidth(void)			  const	{ return m_nWidth;}
		inline int  GetHeight(void)			  const	{ return m_nHeight;}
		inline int  GetSize(void)			  const { return m_nImageSize;}
		inline int  GetBPS(void)			  const { return m_nBPS;}
	
	public:// ����
		void DM_RGBtoHSL(BYTE &R, BYTE &G, BYTE &B, float &H, float &S, float &L);
		void DM_HSLtoRGB(float &H, float &S, float &L, BYTE &R, BYTE &G, BYTE &B);
		void RGBtoHSL(BYTE R,BYTE G,BYTE B,float* H,float* S,float* L);
		COLORREF HSLtoRGB(float H,float S,float L);

	public:
		HBITMAP                                             m_hBitmap;				///< DIBSection������HBitmap
		BYTE*												m_pPixelBits;	        ///< pixel array
		BYTE*												m_pPixelCopyBits;		///< copy origin pixel array
		int													m_nImageSize;			///< pixel array size
		int												    m_nWidth;				///< image pixel width
		int													m_nHeight;				///< image pixel height, positive
		int													m_nBPS;					///< byte per scan line, per plane

		LPBITMAPINFO									    m_pBMI;					///< λͼͷ
		
		// ---------------------------------------------------------------------------
		AlphaCheck                                          m_AlphaCheck;
#define  MAX_ALPHABUF   60000
		static BYTE											ms_AlphaBk[MAX_ALPHABUF];///< static ���ݲ���ռ��sizeof��DMDIBHelper)
		static BYTE*                                        ms_pBk;
		static DM::CRect                                    ms_ApRect;
	};

}//namespace DM