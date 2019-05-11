//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: ����ר��demo
// File Des:  
// File Summary: 
// Cur Version: 1.0
// Author:   
// Create Data: 
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-4-7	1.0			
//--------------------------------------------------------
#include "QQDemoAfx.h"
#include "QQMainWnd.h" 
#include "WndShadow.h"
#include "SkinPreview.h"
#include "SpyFindBtn.h"
#include "IEWnd.h"
#include "DUIWebkit.h"
#include "DMResZipParam.h"
#include "DMTipsImpl.h"
#include "DMScriptImpl.h"
#include <time.h>
#include <Dbghelp.h>
#pragma comment(lib,"Dbghelp.lib")

LONG __stdcall _UnhandledExceptionFilter(_EXCEPTION_POINTERS* ExceptionInfo)
{
	wchar_t szDir[MAX_PATH] = {0};
	GetRootDirW(szDir,MAX_PATH);
	CStringW  strDumpDir = szDir; 
	time_t  tt = time(NULL);
	tm* ptime = localtime(&tt);
	CStringW strDumpPath;
	strDumpPath.Format(L"%s-%04d-%02d-%02d-%02d-%02d-%02d.dmp",
		strDumpDir,
		1900 + ptime->tm_year,
		(ptime->tm_mon + 1) ,
		ptime->tm_mday,
		ptime->tm_hour,
		ptime->tm_min,
		ptime->tm_sec);
	HANDLE  hFile = CreateFile(strDumpPath, GENERIC_WRITE, FILE_SHARE_WRITE|FILE_SHARE_READ, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if (INVALID_HANDLE_VALUE != hFile)
	{ 
		MINIDUMP_EXCEPTION_INFORMATION   ExInfo; 
		ExInfo.ThreadId = ::GetCurrentThreadId();
		ExInfo.ExceptionPointers = ExceptionInfo;
		ExInfo.ClientPointers = NULL;

		BOOL bOK = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpWithFullMemory,&ExInfo, NULL, NULL);
		CloseHandle(hFile); 
	} 
	return EXCEPTION_EXECUTE_HANDLER;
}

CQQMainWnd* g_pMainWnd = NULL;
int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{                      
	SetUnhandledExceptionFilter(&_UnhandledExceptionFilter);
	DMApp theApp(hInstance);
	// ��װplugin���������Ҫ!
#ifdef DLL_DMMAIN// lib���²�֧�ֲ��
#ifdef _DEBUG
	theApp.LoadPlugins(L"dmpluginsd.cfg");
#else
	theApp.LoadPlugins(L"dmplugins.cfg");
#endif
#endif//DLL_DMMAIN

	CWndShadow::Initialize(hInstance);
	do 
	{ 
		//DMResZipParam zipres(L"QQRes.zip");
		//theApp.LoadResPack((WPARAM)(&zipres),NULL,L"DMResZipImpl");			// ·���������������Ŀ¼-zip��ʽ
		theApp.LoadResPack((WPARAM)(L"QQRes"),NULL,NULL);						// ·���������������Ŀ¼
		theApp.InitGlobal();													// ��ʼ��ָ����ȫ��skin��style��Ĭ������
		theApp.Register(DMRegHelperT<SkinPreview>(),true);
		theApp.Register(DMRegHelperT<SpyFindBtn>(),true);
		theApp.Register(DMRegHelperT<IERealWnd>(),true);						// ��ʼ���ⲿ���Ƶ�Pop RealWnd
		theApp.Register(DMRegHelperT<DUIWebKit>(),true);						// ��ʼ���ⲿ���Ƶ�Webkit
		theApp.Register(DMRegHelperT<DMTipsImpl>(),true);                       // ��ʼ���ⲿ��tip����
		theApp.Register(DMRegHelperT<DMScriptImpl>(),true);						// ��ʼ���ⲿ�Ľű�ʵ��

		// �������԰����֣���widget�п�ʹ�ò˵��л�
		theApp.LoadTrans((WPARAM)L"dmlg_fh");
		theApp.LoadTrans((WPARAM)L"dmlg_en");
		//theApp.SetTrans(L"dmlg_en");                                            // Ĭ��ʹ��dmlg_en���԰�

		DMSmartPtrT<CQQMainWnd> pMainWnd;
		pMainWnd.Attach(new CQQMainWnd());
		pMainWnd->DM_CreateWindow(L"dui_mainwnd",0,0,0,0,NULL,false);			// ����������
		g_pMainWnd =  pMainWnd;
		pMainWnd->SendMessage(WM_INITDIALOG);
		pMainWnd->CenterWindow();
		pMainWnd->ShowWindow(SW_SHOW);
		theApp.Run(pMainWnd->GetSafeHwnd());								    // ���е�ǰ�̵߳���Ϣѭ������������Ϣ���й�����
	} while (false);
	
	return (int) 0;
}