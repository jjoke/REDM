//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: IDMScript.h 
// File Des:
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-3-25	1.0			
//-------------------------------------------------------
#pragma once
namespace DM
{
	/// <summary>
	///		��չ�ӿڣ�lasstype=<see cref="DMREG_Script"/>
	/// </summary>
	class IDMScript : public DMBase
	{
		DMDECLARE_CLASS_NAME(IDMAnimate,L"IDMScript",DMREG_Script);
	public:
		virtual DMCode InitScript() = 0;                            ///< ���ڳ�ʼ��,(Ҳ���Է��������ʱ���ܰ󶨵�ȫ�ֱ�����
		virtual DMCode RunString(LPCSTR lpszString) = 0;			///< ͨ���ı����нű�
		virtual DMCode RunBuf(LPCSTR pBuf, size_t len) = 0;			///< ͨ��Buf���нű�
		virtual DMCode RunFile(LPCSTR lpszFilePath) = 0;			///< ͨ���ļ����нű�
		virtual DMCode RunEvent(DMEventArgs* pEvt) = 0;				///< ͨ���¼��������нű�
	};

}//namespace DM