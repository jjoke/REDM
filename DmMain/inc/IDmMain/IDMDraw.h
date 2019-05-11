// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	IDMDraw.h
// File mark:   
// File summary:ָ�������߼���ÿ��DMHWnd���Զ���һ������Ļ����߼�
// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2015-3-10
// ----------------------------------------------------------------
#pragma once

namespace DM
{
	/// <summary>
	///		���ƶ�����չ�ӿ�,classtype=<see cref="DMREG_Draw"/>
	/// </summary>
	class IDMDraw:public DMBase
	{
		DMDECLARE_CLASS_NAME(IDMDraw,L"IDMDraw",DMREG_Draw);
	public:
		// DUIͨ�û���
		virtual  DMCode DrawBackground(IDMCanvas* pCanvas,IDMRegion* lpRgn,DUIWindow* pWnd) = 0; 			///< ���Ʊ���
		virtual  DMCode DrawForeground(IDMCanvas* pCanvas,IDMRegion* lpRgn,DUIWindow* pWnd) = 0; 			///< ����ǰ��
		virtual  DMCode Draw(IDMCanvas* pCanvas, IDMRegion* lpRgn,DUIWindow* pWnd) = 0; 					///< ����,���ƺ�һ����Ч���ᱻ���
		
		// DMHWnd��Ч��+�������
		virtual  DMCode InvalidateRect(DUIWND hDUIWnd,LPCRECT lpRect,int fnCombineMode=RGN_AND) = 0;					    ///< ������Ч��
		virtual  int    GetInvalidateRect(DM::CArray<CRect>& Array) = 0;									///< �õ���Ч�����б�,���ظ���
		virtual  bool   IsInvalidate() = 0;																	///< �Ƿ������Ч��
		virtual  DMCode Render(DUIWindow* pWnd) = 0;														///< ������Ч���б���л���,pWndһ��ΪDMHWnd����DUIWindow
		
		virtual  DMCode GetCanvas(IDMCanvas** ppCanvas) = 0;                                                ///< ȡ�û��ƻ���,�ڲ����Զ��������ü���,��ʹ������ָ��
		virtual  DMCode ResizeCanvas(SIZE size) = 0;														///< ������ƻ�����С

	};

}//namespace DM