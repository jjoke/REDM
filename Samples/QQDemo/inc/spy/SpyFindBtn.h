//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: SpyFindBtn.h 
// File Des: ��������
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-4-17	1.0			
//--------------------------------------------------------
#pragma once
class CQQMainWnd;
class CSpyWnd;
extern CQQMainWnd* g_pMainWnd;
/// <summary>
///		�ڴ��ڲ��ҽ���ʱ�����Լ���������
/// </summary>
class DMSpyInitArgs:public DMEventArgs
{
public:
	DMSpyInitArgs(DUIWindow *pWnd):DMEventArgs(pWnd){}
	enum{EventID = DMEVT_END+1};
	UINT GetEventID(){return EventID;}
public:
	HWND               m_hwnd;
};


class SpyFindBtn:public DUIWindow,public IDMTimeline
{
	DMDECLARE_CLASS_NAME(DUIWindow,L"spyfindbtn",DMREG_Window);
public:
	SpyFindBtn();

public:
	DM_BEGIN_MSG_MAP()
		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_LBUTTONUP(OnLButtonUp)
		MSG_WM_MOUSELEAVE(OnMouseLeave)
		MSG_WM_DESTROY(OnDestroy)
	DM_END_MSG_MAP()

public:
	void OnLButtonDown(UINT nFlags,CPoint pt);
	void OnLButtonUp(UINT nFlags,CPoint pt);
	void OnMouseLeave();
	void OnDestroy();

public:
	DMCode DV_OnSetCursor(const CPoint &pt);					    ///< ���õ�ǰ�Ĺ��
	DMCode OnTimeline();


public:// ����
	void RefreshFindInfo(HWND hWnd);
	CStringT Display(int nVal);
	CStringT GetProcPath(int PID);
	HWND InitCurHWnd();

protected:
	bool                       bLButtonDown;
	CSpyWnd*                   m_pSpyWnd;
};