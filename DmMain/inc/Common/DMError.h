//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMError.h 
// File Des: ������
// File Summary: ��������:
// ������ΪANAME�������enum ANAME_ERROR_CODEö����
// �纯����ΪfunNAME,�����ANAME_FUNNAME_XX_ERR,XX��ʾ����ԭ��
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-7	1.0			
//-------------------------------------------------------
#pragma once

/// <summary>
///		�������б�
/// </summary>
namespace DM
{
	#define DMSUCCEEDED(dmcode)   (0 == (int)(dmcode))
	enum DM_ERROR_CODE///ͨ�ô�����ENUM
	{
		DM_ECODE_OK = 0,											///< ͨ�õĳɹ�	
		DM_ECODE_FAIL = 1,											///< ͨ�õ�ʧ��,��xml�����б�ʾδ����xml	
		DM_ECODE_NOXMLLOADREFRESH = 2,                              ///< ��xml��ʽ����ʱ��Ҫˢ������
		DM_ECODE_NOXMLLOADPARENTREFRESH,							///< ��xml��ʽ����ʱ��Ҫˢ�¸����ڣ���tabpage��
		DM_ECODE_NOXMLRELAYOUT,										///< ��xml��ʽ����ʱ���²���
		DM_ECODE_NOTIMPL,                                           ///< δʵ�ֽӿ�
		DM_ECODE_SMALLBUF,                                          ///< BUF̫С
		DM_ECODE_GETROOTDIR_FAIL,									///< ��ȡexe��Ŀ¼ʧ��
		DM_ECODE_PATHCOMBINE_FAIL,                                  ///< PathCombineWʧ��
		DM_ECODE_NOLOOP,                                            ///< ����ѭ��
		DM_ECODE_END  = 100,                                        ///< ͨ�õĴ�ʶ�����
	};

	enum DMDATABASE_ERROR_CODE///XML������ENUM
	{
		// LoadDMData
		DMDATABASE_LOADDMDATA_PARAM_INVALID = 200,					///< �����Ƿ�

	};

	enum DMAPPDATA_ERROR_CODE
	{
		DMAPPDATA_BASE  = 300,
		// Run
		DMAPP_RUN_ADDMESSAGELOOP_FAIL,							    ///< ������Ϣѭ���б�ʧ��
	};

	enum DMREGMGR_ERROR_CODE///REG������ENUM
	{
		// RegisterByType
		DMREGMGR_REGISTERBYTYPE_REG_EXIST = 400,					///< ע���Ѵ���

		// CreateRegObjByType
		DMREGMGR_CREATEREGOBJBYTYPE_PARAM_INVALID,                  ///< ��������Ƿ�
		DMREGMGR_CREATEREGOBJBYTYPE_COUNT_ISZERO,                   ///< ע����Ϊ0

		// SetDefRegObjByType
		DMREGMGR_SETDEFREGOBJBYTYPE_DEFREGNAME_SAME,                ///< SetDefRegObj��ԭ����һ��
	};

	enum DMPLUGINSTOOL_ERROR_CODE///���������
	{
		// LoadPlugins
		DMPLUGINSTOOL_LOADPLUGINS_CFGFILE_NOTEXIST,                 ///< CFG�ļ������� 

		// LoadPlugin
		DMPLUGINSTOOL_LOADPLUGIN_LOAD_FAIL,                         ///< dll����ʧ��
		DMPLUGINSTOOL_LOADPLUGIN_ALREADY_EXIST,                     ///< dll�ѱ����ع�
		DMPLUGINSTOOL_LOADPLUGIN_NOFIND_START_EXPORT,               ///< dllû�е���dllStartPlugin
	};
}
