#include "DMDemoAfx.h"
#include "MainWnd.h"
#include "IEWnd.h"   ///< realwnd���ⲿ�Լ�ʵ�ֽӿڴ���
#include "DUIRealWnd.h"
#include "DUIWebkit.h"

CMainWnd* g_pMainWnd = NULL;
int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
	DMCode iErr = DM_ECODE_OK;
	DMApp theApp(hInstance);

	// ��װplugin���������Ҫ!
#ifdef DLL_DMMAIN// lib���²�֧�ֲ��
#ifdef _DEBUG
	theApp.LoadPlugins(L"dmpluginsd.cfg");
#else
	theApp.LoadPlugins(L"dmplugins.cfg");
#endif
#endif//DLL_DMMAIN

	iErr = theApp.SetDefRegObj(L"DMResFolderImpl",DMREG_Res);// ����ʹ�����õ��ļ��н���Res��ʽ
	iErr = theApp.LoadResPack((WPARAM)(L"DMRes"),NULL,NULL); // ·���������������Ŀ¼
	iErr = theApp.InitGlobal();								 // ��ʼ��ָ����ȫ��skin��style��Ĭ������
	iErr = theApp.Register(DMRegHelperT<IERealWnd>(),true);  // ��ʼ���ⲿ���Ƶ�Pop RealWnd
	//iErr = theApp.Register(DMRegHelperT<DUIRealWnd>(),true); // ��ʼ���ⲿ���Ƶ�Child RealWnd
	iErr = theApp.Register(DMRegHelperT<DUIWebKit>(),true);  // ��ʼ���ⲿ���Ƶ�Webkit

	DMSmartPtrT<CMainWnd> pMainWnd;
	if (DMSUCCEEDED(iErr))
	{
		pMainWnd.Attach(new CMainWnd());
		g_pMainWnd = pMainWnd;
		pMainWnd->DM_CreateWindow(L"dui_main",0,0,0,0,NULL,false);				// ����������
		pMainWnd->SendMessage(WM_INITDIALOG);
		pMainWnd->CenterWindow();
		pMainWnd->ShowWindow(SW_SHOW);

		theApp.Run(pMainWnd->GetSafeHwnd());				// ���е�ǰ�̵߳���Ϣѭ������������Ϣ���й�����
	}
	return (int) 0;
}