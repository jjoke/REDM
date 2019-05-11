//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: IDMLog.h 
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
	enum DMLOGLEVEL///LOG����
	{
		DMLOG_TRACE = 0,		///<��������
		DMLOG_DEBUG = 1,		///<Debug����
		DMLOG_INFO  = 2,		///<��������
		DMLOG_WARN  = 3,		///<��������
		DMLOG_ERR   = 4,		///<��������
		DMLOG_FATAL = 5,		///<�������ش���
	};

	/// <summary>
	///		LOG��ӡ������չ�ӿ�,classtype=<see cref="DMREG_Log"/>
	/// </summary>
	/// <remarks>
	///     ����������򱣴��log�ļ�
	/// </remarks>
	class IDMLog:public DMBase
	{
		DMDECLARE_CLASS_NAME(IDMLog,L"IDMLog",DMREG_Log);
	public:
		/// @brief ��ӡLOG�ӿ�
		/// @param[in]		 iLevel			LOG����<see cref="DMLOGLEVEL"/>
		/// @param[in]		 lpszFuncName	������
		/// @param[in]		 lpszFileName	�ļ���
		/// @param[in]		 iLine			�к�
		/// @param[in]		 szLogBuf		�����LOG
		/// @remark			
		/// @return DM_ECODE_OKΪ�ɹ�
		virtual DMCode LogW(DMLOGLEVEL iLevel,LPCWSTR lpszFuncName, LPCWSTR lpszFileName, int iLine,LPCWSTR szLogBuf) = 0;
	};
}
