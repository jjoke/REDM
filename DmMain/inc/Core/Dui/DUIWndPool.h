//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DUIWndPool.h 
// File Des: ��ÿ��DUIģ�ⴰ��һ��Ψһ�Ĺ�����ʶ��
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-30	1.0			
//-------------------------------------------------------
#pragma once

namespace DM
{
	/// -------------------------------------------------
	class DUIWindow;
	/// <summary>
	///		����ģ��DUI���ھ���ĳ�
	/// </summary>
	class DM_EXPORT DUIWndPool:public DMMapT<DUIWND,DUIWindowPtr>
	{
	public:
		DUIWndPool();
		~DUIWndPool();

	public:
		/// -------------------------------------------------
		/// @brief ������DUI����
		/// @param[in]		 hDUIWnd		DUI���ڵ�Ψһ���
		/// @return DMCode 
		DMCode AddMainDUIWnd(DUIWND hDUIWnd);
		DMCode RemoveMainDUIWnd(DUIWND hDUIWnd);///< �Ƴ�

		DMCode AddRealDUIWnd(DUIWND hDUIWnd);	
		DMCode HideAllRealDUIWnd(DUIWND hMainDUIWnd);
		DMCode ShowAllRealDUIWnd(DUIWND hMainDUIWnd); //lzlong add
		DMCode RemoveRealDUIWnd(DUIWND hDUIWnd);///< �Ƴ�

		/// -------------------------------------------------
		/// @brief �ҵ�DUI����
		/// @param[in]		 hDUIWnd		DUI���ڵ�Ψһ���
		/// @return DUIWindowPtr��ʧ��ΪNULL
		DUIWindowPtr FindDUIWnd(DUIWND hDUIWnd);

		/// -------------------------------------------------
		/// @brief ���뵽DUIP���ھ����
		/// @param[in]		 pDUIWindow    Ҫ������DUI���ڵ�ָ��
		/// @return DUI���ڵ�Ψһ���
		DUIWND NewDUIWnd(DUIWindowPtr pDUIWindow);

		/// -------------------------------------------------
		/// @brief �Ƴ�DUIP���ھ��
		/// @param[in]		 hDUIWnd		Ҫ�Ƴ���DUI���ڵľ��
		/// @return true:�ɹ�,false:ʧ��
		bool DestoryDUIWnd(DUIWND hDUIWnd);

		/// -------------------------------------------------
		/// @brief ˢ��ʹ��skin�б��DUI���ڣ�
		/// @param[in]		 wp		����
		/// @param[in]		 lp		����
		/// @remark ���ڻ���
		/// @return DMCode
		DMCode UpdateSkin(WPARAM wp, LPARAM lp);

		DMCode RedrawAll();

		DMCode UpdateSkinLoop(DUIWindowPtr pWnd);

	public:
		DMLock                       m_Lock;
		DUIWND                       m_hNextWnd;		///< ��ǰʹ�õ����DUI���ھ��
		CArray<DUIWND>               m_MainDUIWndArray; ///< �����ڵ�DUI��
		CArray<DUIWND>               m_RealDUIWndArray; ///< ��ʵ���ڵ�DUI��
	};

	/// -------------------------------------------------


}//namespace DM