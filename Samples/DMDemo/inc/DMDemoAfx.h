#pragma once
#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
#include <windows.h>
#include <tchar.h>

// 2  DM
#include "DmMainOutput.h"

// 3 �Զ���
#include "DUIScrollBase.h"
#include "DUIGif.h"
#include "DUIEdit.h"
#include "DUIMenu.h"
#include "DUIButton.h"
#include "DUISliderCtrl.h"
#include "DUIProcessCtrl.h"
#include "DUIRadioButton.h"
#include "IDUIWeb.h"

// lib
#ifdef _DEBUG
#pragma comment(lib,"DmMain_d.lib")
#else
#pragma comment(lib,"DmMain.lib")
#endif

using namespace DM;
