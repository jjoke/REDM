//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMDynLibMgr.h 
// File Des: ����plugin����б�<plugin handle--dll name>
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-16	1.0			
//-------------------------------------------------------
#pragma once
#include "DMDynLib.h"

namespace DM
{
	/// <summary>
	///		����<see cref="DMDynLib"/>,��ֲ��ogre���ϵͳ���ɲο�OgreDynLibManager.h/.cpp
	/// </summary>
	class DMDynLibMgr:public DMSingletonT<DMDynLibMgr>
	{
	public:
		DMDynLibMgr(void);
		virtual ~DMDynLibMgr(void);

		//---------------------------------------------------
		// Function Des: �����ʧ�ܣ�����null
		// Input Parameter:
		// Output Parameter:
		// return:
		//---------------------------------------------------
		DMDynLib* Load(const CStringW& strPluginPath);  ///<����DMDynLib����ؼ������
		void Unload(DMDynLib* plib);				    ///<�Ƴ�ָ����MDynLib��

	protected:
		DMDynLib* FindObj(const CStringW& strPluginPath);

	protected:
		typedef DM::CArray<DMDynLib*>       DMDynLibArray;
		DMDynLibArray						m_LibArray;
	};


}//namespace DM
