//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.      
//        
// File Name: TGP����ר��demo
// File Des:      
// File Summary:           
// Cur Version: 1.0 
// Author:
// Create Data: 
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2016-4-21	1.0			
//--------------------------------------------------------
#include "TGPDemoAfx.h" 
#include "TGPMainWnd.h"  
#include "TGPListBoxEx.h"
#include "TGPTipsImpl.h"
#include "TGPComboboxEx.h" 
#include "TGPLoginWnd.h"
#include "DMResZipParam.h"

CTGPMainWnd* g_pMainWnd = NULL;
int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{                       
	DMApp theApp(hInstance);   
	// ��װplugin���������Ҫ! 
#ifdef DLL_DMMAIN// lib���²�֧�ֲ��
#ifdef _DEBUG
	theApp.LoadPlugins(L"dmpluginsd.cfg");
#else
	theApp.LoadPlugins(L"dmplugins.cfg");
#endif
#endif//DLL_DMMAIN
 
	do  
	{  
#ifdef DLL_DMMAIN// DLL����ʾ���֧�ֶ�zip��ǰ���أ���ǰ�ͷ�----------------------------------------------------------
		//1. login���ڵ�½ 
		DMResZipParam ziploginres(L"TGPRes\\zips\\zip_login.zip"); 
		theApp.LoadResPack((WPARAM)(&ziploginres),(LPARAM)L"loginzip",L"DMResMultZipImpl");		///< ע��loginzipΪkey��zip��

		// main������Դ������ǰ���룬��ȻΪ�˽�ʡ���ڴ���Ҳ������ʹ��ʱ�ټ���
		DMResZipParam zipres(L"TGPRes\\zips\\zip_main.zip");
		theApp.LoadResPack((WPARAM)(&zipres),(LPARAM)L"mainzip",L"DMResMultZipImpl");			///< ע��mainzipΪkey��zip��

		theApp.InitGlobal(L"global_login");	
		DMSmartPtrT<CTGPLoginWnd> pLoginWnd; 
		pLoginWnd.Attach(new CTGPLoginWnd());
		pLoginWnd->DM_CreateWindow(L"dui_loginwnd",0,0,0,0,NULL,false);							///< ������½����
		pLoginWnd->SendMessage(WM_INITDIALOG);
		pLoginWnd->CenterWindow();
		pLoginWnd->ShowWindow(SW_SHOW);
		theApp.Run(pLoginWnd->GetSafeHwnd());													///< �˺���ִ�к��˳���½����

		DMSmartPtrT<IDMRes> pRes;
		theApp.GetDefRegObj((void**)&pRes, DMREG_Res);											///< �õ�TGPResMultZipImpl����
		pRes->SendExpandInfo(NULL,(LPARAM)L"loginzip");											///< ����չ���ͷ�loginzip��
#else
		theApp.LoadResPack((WPARAM)(L"TGPRes"),NULL,NULL);										///< ·���������������Ŀ¼
#endif//DLL_DMMAIN


		//2.������
		theApp.InitGlobal();																	///< ��ʼ��ָ����ȫ��skin��style��Ĭ������
		theApp.Register(DMRegHelperT<TGPListBoxEx>(),true);
		theApp.Register(DMRegHelperT<TGPTipsImpl>(),true);										///< ��ʼ���ⲿ��tip����
		theApp.Register(DMRegHelperT<TGPComboboxEx>(),true);

		DMSmartPtrT<CTGPMainWnd> pMainWnd;
		pMainWnd.Attach(new CTGPMainWnd());
		pMainWnd->DM_CreateWindow(L"dui_mainwnd",0,0,0,0,NULL,false);							///< ����������
		g_pMainWnd =  pMainWnd;
		pMainWnd->SendMessage(WM_INITDIALOG);
		pMainWnd->CenterWindow();
		pMainWnd->ShowWindow(SW_SHOW);
		theApp.Run(pMainWnd->GetSafeHwnd());													///< ���е�ǰ�̵߳���Ϣѭ������������Ϣ���й�����
	} while (false);
	return (int) 0;
}