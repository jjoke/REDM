//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: IDUIRealWnd.h 
// File Des: ��ʵ���ڻ���
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-4	1.0			
//-------------------------------------------------------
#pragma once

namespace DM
{	
	/// <summary>
	///		��ΪRealWnd�Ľӿ��࣬�ⲿ��ʵ�ֽӿڣ���ע�����
	/// </summary>
	class DM_EXPORT IDUIRealWnd:public DUIWindow	
	{
	public:
		//---------------------------------------------------
		// Function Des: ���ⲿʵ�ֵ���չ�ӿ�
		//---------------------------------------------------
		virtual HWND OnCreateRealWnd(LPCWSTR atom,HWND hWndParent) = 0;			///< �ⲿ�������ڣ���ΪchildҲ��Ϊpupop		
		virtual DMCode OnDestoryRealWnd() = 0;									///< �ⲿ���ٴ��ڣ�
		virtual DMCode OnShowRealWnd(BOOL bShow, UINT nStatus) = 0;		        
		virtual DMCode OnIsPopupWnd() = 0;                                      ///< �Ƿ�Ϊchild����
		virtual DMCode OnMoveRealWnd(LPRECT lpRect) = 0;						///< ͬ���ƶ����ڣ�lpRect��pupopʱ��Ϊ����ڸ��������꣬���Ӵ����Լ�ת��
	
	public:
		IDUIRealWnd();

	public:
		DM_BEGIN_MSG_MAP()
			MSG_WM_CREATE(OnCreate)
			DM_MSG_WM_PAINT(DM_OnPaint)
			MSG_WM_DESTROY(OnDestroy)
			MSG_WM_SIZE(OnSize)
			MSG_WM_SHOWWINDOW(OnShowWindow)
		DM_END_MSG_MAP()

	public:
		//---------------------------------------------------
		// Function Des: DUI����Ϣ�ַ�ϵ�к���
		//---------------------------------------------------
		int OnCreate(LPVOID);									// MSDN: ��Ϊ0����Destory��Ϣ
		void DM_OnPaint(IDMCanvas* pCanvas);
		void OnDestroy();
		void OnSize(UINT nType, CSize size);
		void OnShowWindow(BOOL bShow, UINT nStatus);
		void OnMove(CPoint pt);

	public:
		bool DV_IsStateChangeRedraw(){return false;}

	public:// ����
		void MoveRealWnd();
		void CatchRealWndScreen(IDMCanvas* pCanvas);

	public:
		HWND                              m_hRealWnd;
	};

}// namespace DM