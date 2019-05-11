//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: IDMAnimate.h 
// File Des:
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-3-10	1.0			
//-------------------------------------------------------
#pragma once
namespace DM
{
	class IDMAnimate;
	/// <summary>
	///		����ӵ����,classtype=<see cref="DMREG_Attribute"/>
	/// </summary>
	class IDMAnimateOwner
	{
	public:
		virtual DUIWindow* GetAnimateOwnerWnd() = 0;											///< ����ӵ����
		virtual DMCode AnimateBegin_Callback(IDMAnimate*pAni,WPARAM wp=0, LPARAM lp=0) = 0;		///< ������ʼʱ�ص�
		virtual DMCode AnimateMid_Callback(IDMAnimate*pAni, WPARAM wp=0, LPARAM lp=0) = 0;      ///< �����м�ص�		
		virtual DMCode AnimateEnd_Callback(IDMAnimate*pAni,WPARAM wp=0, LPARAM lp=0) = 0;		///< ���������ص�
	};

	/// <summary>
	///		����������չ�ӿ�,classtype=<see cref="DMREG_Animate"/>
	/// </summary>
	class IDMAnimate:public DMBase
	{
		DMDECLARE_CLASS_NAME(IDMAnimate,L"IDMAnimate",DMREG_Animate);
	public:
		virtual DMCode AnimateInit(IDMAnimateOwner*pOwner,IDMCanvas* pStartCanvas,IDMCanvas* pEndCanvas,WPARAM wp=0, LPARAM lp=0) = 0;   ///< ��ʼ������
		virtual DMCode AnimateBegin(WPARAM wp=0, LPARAM lp=0) = 0;																		 ///< ��ʼ����
		virtual DMCode AnitmateGet(WPARAM wp=0, LPARAM lp=0) = 0;                                                                        ///< �Ӷ����ӿڻ�ȡĳЩ��Ϣ
		virtual DMCode AnimateEnd(WPARAM wp=0, LPARAM lp=0) = 0;																		 ///< ��������
	};
}//namespace DM