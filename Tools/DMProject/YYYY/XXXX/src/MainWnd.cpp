#include "StdAfx.h"
#include "MainWnd.h"

BEGIN_MSG_MAP(CMainWnd)
	MSG_WM_INITDIALOG(OnInitDialog)
	MSG_WM_SIZE(OnSize)
	CHAIN_MSG_MAP(DMHWnd)// ��δ�������Ϣ����DMHWnd����
END_MSG_MAP()
BEGIN_EVENT_MAP(CMainWnd)
	EVENT_NAME_COMMAND(L"closebutton",OnClose)
	EVENT_NAME_COMMAND(L"maxbutton",OnMaximize)
	EVENT_NAME_COMMAND(L"restorebutton",OnRestore)
	EVENT_NAME_COMMAND(L"minbutton", OnMinimize)
END_EVENT_MAP()

BOOL CMainWnd::OnInitDialog(HWND wndFocus, LPARAM lInitParam)
{
	return TRUE;
}

void CMainWnd::OnSize(UINT nType, CSize size)
{
	DUIWindow* pMaxBtn = FindChildByName(L"maxbutton");
	DUIWindow* pRestoreBtn = FindChildByName(L"restorebutton");
	if (0 != size.cx&&0 != size.cy&&pMaxBtn&&pRestoreBtn)
	{
		if (SIZE_MAXIMIZED == nType)
		{
			pMaxBtn->DM_SetVisible(false);
			pRestoreBtn->DM_SetVisible(true);
		}
		else if (SIZE_RESTORED == nType)
		{
			pMaxBtn->DM_SetVisible(true);
			pRestoreBtn->DM_SetVisible(false);
		}
	}
	SetMsgHandled(FALSE);  // ��DMHWnd��������OnSize��Ϣ
}

DMCode CMainWnd::OnClose()
{
	DestroyWindow(); 
	return DM_ECODE_OK;
}

DMCode CMainWnd::OnMaximize()
{
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
	return DM_ECODE_OK;
}

DMCode CMainWnd::OnRestore()
{
	SendMessage(WM_SYSCOMMAND,SC_RESTORE);
	return DM_ECODE_OK;
}


DMCode CMainWnd::OnMinimize()
{
	SendMessage(WM_SYSCOMMAND,SC_MINIMIZE);
	return DM_ECODE_OK;
}