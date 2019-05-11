//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMDragWnd.h 
// File Des: ��ģ���϶�
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-3-13	1.0			
//-------------------------------------------------------
#pragma once

namespace DM
{
	/// <summary>
	///		�϶���ʵ����
	/// </summary>
	class DM_EXPORT DMDragWnd : public DMCWnd
	{
	public:
		DMDragWnd(void);
		virtual~DMDragWnd(void);

		//---------------------------------------------------
		// Function Des: �ӿ�
		//---------------------------------------------------
		static bool DragBegin(IDMCanvas* pCanvas,POINT ptHot,COLORREF crKey, BYTE byAlpha,DWORD dwFlags);
		static void DragMove(POINT pt);
		static void DragEnd();
	
	public:
		CPoint								m_ptHot;					///< ������϶��������Ͻǵ�ƫ��
		static DMDragWnd*					ms_pCurDragWnd;
	};
}//namespace DM