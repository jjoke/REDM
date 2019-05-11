//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DUIFocusMgr.h 
// File Des: ���㴦����
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2014-11-10	1.0			
//-------------------------------------------------------
#pragma once
#include "DUIAccel.h"

namespace DM
{
#define  PUSH_CTRL         (GetKeyState(VK_CONTROL)&0x8000)
#define  PUSH_SHIFT        (GetKeyState(VK_SHIFT)&0x8000)
#define  PUSH_ALT          (GetKeyState(VK_MENU)&0x8000)
#define  PUSH_LBUTTONDOWN  (GetAsyncKeyState(VK_LBUTTON)&0x8000)
	class FocusSearch
	{
	public:
		FocusSearch(DUIWindow* pHWnd, bool bCycle);
		virtual ~FocusSearch();

		/// -------------------------------------------------
		/// @brief			 ������һ���н���Ĵ��ڣ�����һ��,����Ϊcheck״̬�Ĵ���Ϊ�����
		/// @param[in]		 pStartWnd		��ʼ���ҵĴ���,��ΪNULL,��ȡm_pHWnd��ײ����һ���Ӵ��ڿ�ʼ��bReverse=true�����m_pHWnd�ĵ�һ���Ӵ��ڿ�ʼ(bReverse=false)
		/// @param[in]		 bReverse		Ϊtrue��ʾ�Ӻ���ǰ��
		/// @remark			 ��û���ҵ�״̬�£����m_bCycleΪtrue,���ͷ����һ��(ѭ��һ�Σ�m_bCycle��Ϊfalse)
		/// @return  t:NULL��ʾû���ҵ�
		DUIWindow* FindNextFocusableWnd(DUIWindow* pStartWnd,bool bReverse);

	public:
		bool IsFocusable(DUIWindow* pWnd);   
		bool IsWndFocusableCandidate(DUIWindow* pWnd, DUIWindow* pGroupOwner);

		// ������һ���н���Ĵ���,bResetStartWndΪtrue��ʾ��ʼ�������ڲ��Զ��趨��
		DUIWindow* FindNextFocusableWndImpl(DUIWindow* pStartWnd,bool bResetStartWnd,bool bFindUp,bool bFindDown, DUIWindow* pSkipGroupOwner);
		DUIWindow* FindPreviousFocusableWndImpl(DUIWindow* pStartWnd,bool bResetStartWnd,bool bFindUp,bool bFindDown,DUIWindow* pSkipGroupOwner);

	protected:
		DUIWindow*			m_pHWnd;
		bool				m_bCycle;    ///< �Ƿ�������ٴ�ͷѭ������
	};

	template<>// �˴�������DUIFocusMgr�е�CMap��ʼ�����Ƚ�
	class DM::CElementTraits<DM::DUIAccel>:public DM::CElementTraitsBase<DM::DUIAccel>
	{
	public:
		static ULONG Hash(INARGTYPE element) throw()
		{
			return MAKELONG(element.GetModifier(),element.GetKey());
		}

		static bool CompareElements(INARGTYPE element1, INARGTYPE element2)
		{
			return Hash(element1)==Hash(element2);
		}

		static int CompareElementsOrdered(INARGTYPE element1, INARGTYPE element2)
		{
			return Hash(element1)-Hash(element2);
		}
	};

	typedef IDMAccelHandler* IDMAccelHandlerPtr;
	/// <summary>
	///		��������DUI�����еķַ����Լ����ټ���ע��
	/// </summary>
	class DM_EXPORT DUIFocusMgr : public IDMAccelMgr
	{
	public:
		enum FocusChangeReason
		{
			FocusReasonByTab,			 // Tab or Shift+Tab                
			FocusReasonByDirect,		 // �����ֱ����ת
			FocusReasonByRestore,		 // ������ʧȥ�ٳ��Իָ�����
		};

		DUIFocusMgr(DUIWindow *pHWnd);
		~DUIFocusMgr(void);

		/// -------------------------------------------------
		/// @brief ���ý���
		/// @param[in]  DUIWnd		�����ý����DUI���
		/// @return ��
		void SetFocusedWnd(DUIWND DUIWnd);

		/// -------------------------------------------------
		/// @brief ��ý���
		/// @return ��ǰ���ý����DUI���
		DUIWND GetFocusedWnd();

		//---------------------------------------------------
		// Function Des: ע���ȼ�
		//---------------------------------------------------
		void RegisterAccel(const DUIAccel& Accel,IDMAccelHandler* pHandler);	///< ע����ټ��Լ��¼�����ӿڶ���
		void UnregisterAccel(const DUIAccel& Accel,IDMAccelHandler* pHandler);	///< ��ע����ټ��Լ��¼�����ӿڶ���
		void UnregisterAccels(IDMAccelHandler* pHandler);						///< ��ע���¼�����ӿڶ�������м��ټ�
		bool ProcessAccel(const DUIAccel& Accel);								///< ѭ������ע��ļ��ټ��¼�

	public:// ����
		bool IsTabChanged(UINT vKey);  
		bool OnKeyDown(UINT vKey);        // 1. tab 2.����RedioButton 3.���ټ�������

		//---------------------------------------------------
		// Function Des: ���´���״̬
		//---------------------------------------------------
		void AdvanceFocus(bool bReverse);
		void SetFocuseWndWithReason(DUIWND DUIWnd, FocusChangeReason reason);

		//---------------------------------------------------
		// Function Des: �洢�ͻָ�focuse���ڣ����ڴ�����active/inactive���л�
		//---------------------------------------------------
		void StoreFocuseWnd();
		void RestoreFocuseWnd();

		DUIWindow* GetNextFocusableWnd(DUIWindow* pStartWnd, bool bReverse, bool bLoop);
		void ClearFocus();
		void CheckFocusedWnd();
		
	private:
		DUIWND								m_hDUIFocusWnd;
		DUIWND								m_hDUIFocusBackupWnd;   
		FocusChangeReason					m_FocusChangeReason;

		DUIWindow*							m_pHWnd;

		typedef CList<IDMAccelHandler*> AccelHandlerList;
		typedef CMap<DUIAccel, AccelHandlerList> AccelMap;
		AccelMap						    m_AccelMap;
	};

}//namespace DM
