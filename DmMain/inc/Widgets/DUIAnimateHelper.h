//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DUIAnimateHelper.h 
// File Des: ���ö�������
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-3-3	1.0			
//--------------------------------------------------------
#pragma once
#include "DMGifParse.h"

namespace DM
{
	/// <summary>
	///		 Tabҳ�����ֶ�������
	/// </summary>
	enum  ///< ����Ч��
	{
		TABANI_NULL = 0,
		TABANI_SD_LEFTRIGHT,	///< ��չ��-��Ӧ�����SLIDEDIR
		TABANI_SD_RIGHTLEFT,
		TABANI_SD_TOPBOTTOM,
		TABANI_SD_BOTTOMTOP,
		TABANI_CINFLATE,		///< ��������
		TABANI_CDEFLATE,		///< ������С
	};


	/// <summary>
	///		 ֡����
	/// </summary>
	enum DISPOSAL_METHODS
	{
		DM_UNDEFINED  = 0,
		DM_NONE       = 1,
		DM_BACKGROUND = 2,
		DM_PREVIOUS   = 3 
	};
	typedef struct _stDMAnimateFrame
	{
		DMSmartPtrT<IDMBitmap>		  pBitmap;
		GIFFRAME                      gifFrame;

		~_stDMAnimateFrame()
		{
			pBitmap.Release();
			memset(&gifFrame,0,sizeof(GIFFRAME));
		}
	}DMAnimateFrame,*PDMAnimateFrame;

}//namespace DM
