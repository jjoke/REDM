#include "DmMainAfx.h"
#include "DMEvents.h"
#include "DUIWindow.h"

namespace DM
{
	DMEventArgs::DMEventArgs(DUIWindow* pSender)
		:m_iHandleCount(0)
		,m_IdFrom(0)
		,m_pSender(pSender)
	{
		if (m_pSender)
		{
			m_IdFrom      = m_pSender->GetID();
			m_szNameFrom = m_pSender->GetName();
		}
	}

	DMEventArgs::~DMEventArgs()
	{

	}

	bool DMEventArgs::IsValid()
	{
		return (NULL!=m_pSender);//(NULL!=m_pSender&&(false==m_szNameFrom.IsEmpty()||0!=m_IdFrom));// ��headerctrl���ܲ���Ҫname��id����Ϊ��ֻ�Ǹ�����ʾlistctrl
	}

}//namespace DM