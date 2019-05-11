//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMEventCrack.h 
// File Des:  
// File Summary:
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-2-3	1.0			
//--------------------------------------------------------
#pragma once

namespace DM
{
//-------------------------------------------------------
// ��ͷ�ļ�������,��Դ�ļ��ж���,ͨ�õ�����������ʱ��ʹ��MacroToolת���ɻ��е�Դ�������
#define DECLARE_EVENT_MAP()\
public:\
	virtual DMCode DMHandleEvent(DM::DMEventArgs *pEvt);

#define BEGIN_EVENT_MAP(classname)\
	DMCode classname::DMHandleEvent(DM::DMEventArgs *pEvt)\
	{ \
		DMCode iErr = DM_ECODE_FAIL;\
		do\
		{\
			UINT  uCode = pEvt->GetEventID();

//-------------------------------------------------------
// ��ͷ�ļ�������������,����ģ����
#define BEGIN_EVENT_MAPT(classname)\
	DMCode DMHandleEvent(DM::DMEventArgs *pEvt)\
	{ \
		DMCode iErr = DM_ECODE_FAIL;\
		do\
		{\
		UINT  uCode = pEvt->GetEventID();


//-------------------------------------------------------
// ����
#define END_EVENT_MAP()\
		} while (false);\
		if (DM_ECODE_FAIL==iErr)\
		{\
			return __super::DMHandleEvent(pEvt);\
		}\
		return iErr;\
	}

#define END_EVENT_INBASE()\
		} while (false);\
		return iErr;\
	}

//-------------------------------------------------------
// �л������ദ��,�л��������ྲ̬��������
#define CHAIN_EVENT_MAP(ChainClass)\
	if (DM_ECODE_FAIL!=(iErr=ChainClass::DMHandleEvent(pEvt)))\
	{\
		break;\
	}

#define CHAIN_EVENT_STATIC_MAP(ChainClass,OtherFun)\
	if (DM_ECODE_FAIL!=(iErr=ChainClass::OtherFun(pEvt)))\
	{\
		break;\
	}

//-------------------------------------------------------
// DMCode OnEvent(DMEventArgs *pEvt)
#define EVENT_HANDLER(cd, func)\
	if (cd == uCode)\
	{\
		iErr = func(pEvt);\
		break;\
	}

#define EVENT_ID_HANDLER(id, cd, func)\
	if (cd == uCode && id == pEvt->m_IdFrom)\
	{\
		iErr = func(pEvt);\
		break;\
	}

#define EVENT_NAME_HANDLER(name, cd, func)\
	if (cd == uCode && IsValidString(pEvt->m_szNameFrom) && 0==_wcsicmp(pEvt->m_szNameFrom,name))\
	{\
		iErr = func(pEvt);\
		break;\
	}

#define EVENT_COMMAND(func)\
	if (DM::DMEVT_CMD == uCode)\
	{\
		iErr = func(pEvt);\
		break;\
	}

//-------------------------------------------------------
// DMCode OnCommand()
#define EVENT_ID_COMMAND(id, func)\
	if (DM::DMEVT_CMD == uCode && id == pEvt->m_IdFrom)\
	{\
		iErr = func();\
		break;\
	}

#define EVENT_NAME_COMMAND(name, func)\
	if (DM::DMEVT_CMD == uCode && IsValidString(pEvt->m_szNameFrom) && 0==_wcsicmp(pEvt->m_szNameFrom,name))\
	{\
		iErr = func();\
		break;\
	}

//-------------------------------------------------------
// DMCode OnCommand(int idFrom)
#define EVENT_ID_COMMAND_RANGE(idMin, idMax, func)\
	if (DM::DMEVT_CMD == uCode && idMin <= pEvt->m_IdFrom && idMax >= pEvt->m_IdFrom )\
	{\
		iErr = func(pEvt->m_IdFrom);\
		break;\
	}
}
