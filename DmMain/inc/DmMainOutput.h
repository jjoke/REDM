//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DmMainOutput.h 
// File Des: ����Ԥ�����а������Լ���չ����а���
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-7	1.0			
//-------------------------------------------------------
#pragma once

/// �����괦��
#ifdef DLL_DMMAIN

#ifdef	 DmMain_EXPORTS
	#define  DM_EXPORT		 __declspec( dllexport )
#else
	#define	 DM_EXPORT		 __declspec( dllimport )
	#pragma message("DmMainʹ��dll�汾")
#endif// DmMain_EXPORTS

#else

	#pragma message("DmMainʹ��lib�汾")
	#define DM_EXPORT

#endif// DLL_DMMAIN

// ���ڱ�������templateҪ��������ʵ��һ���ṩ�����Բ����˸澯
// Ҳ�ɵ���ģ��,��:template class DM_EXPORT CStringT<wchar_t>
__pragma(warning(disable: 4251))
__pragma(warning(disable: 4275))
/// ͷ�ļ�����

// 0 ϵͳ��
#include <Windows.h>
#include <stdio.h>
#include <assert.h>
#include <crtdbg.h>
#include <tchar.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")// ���ļ��Ƚ�С��������Ӱ������С
#pragma comment(lib,"msimg32.lib")

// 1 �궨��
#include "DMDef.h"
#include "DMError.h"

// 2 û���κ������ĸ�����
#include "DMMemDispatch.h"
#include "DMHelper.h"
#include "DMRefNum.h"
#include "DMDC.h"
#include "DMMisc.h"
#include "DMLock.h"
#include "DMSingletonT.h"
#include "DMSmartPtrT.h"
#include "DMArrayT.h"
#include "DMMapT.h"
#include "DMAutoResetT.h"
#include "DMAllocT.h"
#include "IDMRegT.h"
#include "DMXmlParse.h"
#include "DMBase.h"
#include "DUIAccel.h"
#include "DMColor.h"
#include "DMBundle.h"

// 3 �¼�
#include "DMEventMgr.h"
#include "DMEvents.h"
#include "DMEventCrack.h"

// 4 ģ����չ�ӿ�
#include "IDMPlugin.h"
#include "IDMMsg.h"
#include "IDMRes.h"
#include "IDMLog.h"
#include "IDMAttribute.h"
#include "IDMImgDecoder.h"
#include "IDMRender.h"
#include "IDMDraw.h"
#include "IDMSkin.h"
#include "IDMStyle.h"
#include "IDMLayout.h"
#include "IDMContainer.h"
#include "IDMToolTip.h"
#include "IDMAnimate.h"
#include "IDMScript.h"
#include "IDMTrans.h"
#include "IDMTaskRunner.h"

// 5 ��Ϣ
#include "DMMsgCrack.h"
#include "DUIMsgCrack.h"
#include "DMDispatch.h"				
#include "DMXmlCrack.h"

// 6 ����������
#include "DMMsgThunk.h"
#include "DMCWndBase.h"
#include "DMCWnd.h"
#include "DUIWindow.h"
#include "IDUIRealWnd.h"
#include "DMHWndHelper.h"
#include "DMHWnd.h"
#include "DMHDialog.h"
#include "DMApp.h"








