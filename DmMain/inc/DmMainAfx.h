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

/// �˴�����ҪΪVS2013ʹ�����ã�vs2008����ֱ��ȥ��-------
#ifndef WINVER                 
#define WINVER 0x0501         
#endif

#ifndef _WIN32_WINNT            
#define _WIN32_WINNT 0x0501     
#endif

#ifndef _WIN32_WINDOWS         
#define _WIN32_WINDOWS 0x0501 
#endif

#ifndef _WIN32_IE                  
#define _WIN32_IE 0x0501    
#endif
///------------------------------------------------------
// ���ڱ�������templateҪ��������ʵ��һ���ṩ�����Բ����˸澯
// Ҳ�ɵ���ģ��,��:template class DM_EXPORT CStringT<wchar_t>
__pragma(warning(disable: 4251 4355))
#include "DmMainOutput.h"

// �ڲ�ʹ��
#include "DMAppData.h"
#include "DMDIBHelper.h"

