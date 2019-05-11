//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: IDMLayout.h 
// File Des:
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-10	1.0			
//-------------------------------------------------------
#pragma once
namespace DM
{
	/// <summary>
	///		ê�㲼�ֶ�����չ�ӿ�,classtype=<see cref="DMREG_Layout"/>
	/// </summary>
	class IDMLayout:public DMBase
	{
		DMDECLARE_CLASS_NAME(IDMLayout,L"IDMLayout",DMREG_Layout);
	public:
		virtual  DMCode SetOwner(LPVOID lpWnd) = 0;									///< ����ӵ�д�layout��DUI����
		virtual  DMCode UpdateLayout(LPRECT prcContainer, CRect &rcWindow) = 0;		///< ���������С
		virtual  DMCode UpdateChildLayout() = 0;									///< ����ӵ�д�layout��DUI���ڵ������Ӵ��ڴ�С
	};
}//namespace DM