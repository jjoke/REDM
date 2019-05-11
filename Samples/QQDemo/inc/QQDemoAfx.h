#pragma once
#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
#include <windows.h>
#include <tchar.h>

// DM
#include "DmMainOutput.h"

// lib
#ifdef _DEBUG
#pragma comment(lib,"DmMain_d.lib")
#else
#pragma comment(lib,"DmMain.lib")
#endif

using namespace DM;

// ������dui
#include "IDUIWeb.h"
#include "DUIButton.h"
#include "DUIEdit.h"
#include "DUITabCtrl.h"
#include "DUIListBox.h"
#include "DUIListBoxEx.h"
#include "DUIComboBox.h"
#include "DUITreeCtrl.h"
#include "DUIGif.h"
#include "DMResFolderImpl.h"
#include "DUIStatic.h"
#include "DMSpyTool.h"