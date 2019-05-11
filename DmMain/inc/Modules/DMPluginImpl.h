
//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMPluginImpl.h 
// File Des: ����ڲ�ʵ��,���ڼ��������ڲ�ʵ��ģ��
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-17	1.0			
//-------------------------------------------------------
#pragma once

namespace DM
{
	class DMPluginImpl:public IDMPlugin
	{
	public:
		const wchar_t* GetName() const;
		void Install();
		void Uninstall();

		void Initialise();
		void Shutdown();
	};


}//namespace DM