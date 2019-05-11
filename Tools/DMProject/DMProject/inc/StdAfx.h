#pragma once
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
#include <windows.h>
#include <tchar.h> 
#include <shlobj.h>
#include <shellapi.h>
#include <commdlg.h>
#include <time.h>
#pragma comment(lib,"shell32.lib")

// DM
#include "DmMainOutput.h"

// lib
#ifdef _DEBUG
#pragma comment(lib,"DmMain_d.lib")
#else
#pragma comment(lib,"DmMain.lib")
#endif

using namespace DM;

#include "DUIEdit.h"