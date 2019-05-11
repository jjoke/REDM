#include "StdAfx.h"
#include "MainWnd.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{   
	OleInitialize(NULL);
	DMApp theApp(hInstance);   

	theApp.LoadResPack((WPARAM)(L"MyRes"),NULL,NULL);						// ·���������������Ŀ¼
	theApp.InitGlobal();													// ��ʼ��ָ����ȫ��skin��style��Ĭ������

	DMSmartPtrT<CMainWnd> pMainWnd;
	pMainWnd.Attach(new CMainWnd());
	pMainWnd->DM_CreateWindow(L"main",0,0,0,0,NULL,false);					// ����������

	pMainWnd->SendMessage(WM_INITDIALOG);
	pMainWnd->CenterWindow();
	pMainWnd->ShowWindow(SW_SHOW);
	theApp.Run(pMainWnd->GetSafeHwnd());								    // ���е�ǰ�̵߳���Ϣѭ������������Ϣ���й�����

	return (int) 0;
}