// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	DMVersion.h
// File mark:   
// File summary:����汾��
// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2017-3-16
// ----------------------------------------------------------------
#pragma once
#define VER_MAJOR		1
#define VER_MINOR		0
#define VER_SLAVE		0
#define VER_BUILD		238

#define PRODUCTNAME     "DMMain"

// ���¶���ͬʱ��RC��CPP�ļ�ʹ�ã��벻Ҫ�޸�
#define VER			    VER_MAJOR.VER_MINOR.VER_SLAVE.VER_BUILD
#define VER_KEY		    VER_MAJOR,VER_MINOR,VER_SLAVE,VER_BUILD

#define __STR(x)		 #x
#define _STR(x) 		__STR(x)
#define __WSTR(x)		L##x
#define _WSTR(x) 		__WSTR(x)

#define VER_STR			_STR(VER)
#define VER_WSTR		_WSTR(VER_STR)
