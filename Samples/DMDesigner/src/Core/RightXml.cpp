#include "DMDesignerAfx.h"
#include "RightXml.h"
BEGIN_MSG_MAP(RightXml)
END_MSG_MAP()
BEGIN_EVENT_MAP(RightXml)
	CHAIN_EVENT_STATIC_MAP(NameAttr,s_DMHandleEvent)
	CHAIN_EVENT_STATIC_MAP(HostAttr,s_DMHandleEvent)
	CHAIN_EVENT_STATIC_MAP(WidgetAttr,s_DMHandleEvent)
	CHAIN_EVENT_STATIC_MAP(PosAttr,s_DMHandleEvent)
END_EVENT_INBASE()// ����
RightXml*  RightXml::ms_pthis = NULL;
RightXml::RightXml()
{
	m_pObjTree->m_EventMgr.SubscribeEvent(DUITreeExEyeChangedArgs::EventID, Subscriber(&RightXml::OnEyeChanged, this));// ����rightxml�б�ֻ֤ע��һ��
	m_pNameAttr  = NULL;
	m_pHostAttr  = NULL;
	m_pWidgetAttr= NULL;
	m_pPosAttr   = NULL;
	ms_pthis = this;
}

RightXml::~RightXml()
{
	m_pObjTree->m_EventMgr.UnSubscribeEvent(DUITreeExEyeChangedArgs::EventID, Subscriber(&RightXml::OnEyeChanged, this));
	ms_pthis   = NULL;
}

DMCode RightXml::UpdataInfo(HDMTREEITEM hSel,HDMTREEITEM hOldSel)
{
	DMCode iErr = DM_ECODE_FAIL;
	do 
	{
		if (NULL == hSel)
		{
			break;
		}
		m_pList->DM_SetVisible(true,true);
		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}

DMCode RightXml::InitRightXml()
{
	DMCode iErr = DM_ECODE_FAIL;
	do 
	{
		//1.��ʼ��name���Կ���
		m_pNameAttr = new NameAttr;
	
		//2.attr list��
		m_pList = g_pMainWnd->FindChildByNameT<DUIList>(L"ds_attr_list");DMASSERT(m_pList);
		m_pList->DM_SetVisible(false,true);
		m_pHostAttr = new HostAttr;
		m_pWidgetAttr = new WidgetAttr;

		//3.attr pos��
		m_pPosAttr = new PosAttr;

		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}

DMCode RightXml::UnInitRightXml()
{
	DMCode iErr = DM_ECODE_FAIL;
	do 
	{
		m_hObjSel  = NULL;

		//2.�ɵ�name�����Կ���
		if (m_pNameAttr)
		{
			DM_DELETE(m_pNameAttr);
		}

		//3.����attr list��
		m_pList->DM_SetVisible(false,true);
		if (m_pHostAttr)
		{
			DM_DELETE(m_pHostAttr);
		}
		if (m_pWidgetAttr)
		{
			DM_DELETE(m_pWidgetAttr);
		}
		if (m_pPosAttr)
		{
			DM_DELETE(m_pPosAttr);
		}
		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}

DMCode RightXml::OnEyeChanged(DMEventArgs* pEvt)
{
	DMAutoResetT<bool> AutoMuted(&m_bMuted,true);// �����л�ʱ����Ӱ����Ϣ
	DUITreeExEyeChangedArgs* pEvent =  (DUITreeExEyeChangedArgs*)pEvt;
	UpdateEye(pEvent->m_hItem);
	return DM_ECODE_OK;
}

DMCode RightXml::UpdateEye(HDMTREEITEM hItem)
{
	do 
	{
		if (NULL == hItem)
		{
			break;
		}
		ObjTreeDataPtr pData = (ObjTreeDataPtr)m_pObjTree->GetItemData(hItem);
		if (NULL == pData||NULL == pData->m_pDUIWnd||!pData->IsValid())
		{
			break;
		}
		
		/*
		1.m_iOrgVisible�ڳ�ʼʱΪDMVISIBLE_NULL,��״̬�²����κδ���
		2.�л���DMTVEXEye_UnEyeʱ,m_iOrgVisible��¼��ԭʼ��m_bvisible��ֵ,ͬʱ��m_bvisible��Ϊfalse
		3.�л���DMTVEXEye_Eyedʱ,�ж�m_iOrgVisible,�����ָ�����
		4.������DMTVEXEye_PartUnEyed,����������m_bvisible�ı�
		*/
		DM::LPTVITEMEX pTV = m_pObjTree->GetItem(hItem);
		if (DMTVEXEye_Eyed == pTV->iEyeValue)
		{
			if (DMVISIBLE_SHOW == pData->m_iOrgVisible)
			{
				pData->m_pDUIWnd->DM_SetVisible(true,true);
			}
			else if (DMVISIBLE_HIDE == pData->m_iOrgVisible)
			{
				pData->m_pDUIWnd->DM_SetVisible(false,true);
			}
		}
		else if (DMTVEXEye_UnEye == pTV->iEyeValue)
		{
			pData->m_iOrgVisible = pData->m_pDUIWnd->DM_IsVisible(false)?DMVISIBLE_SHOW:DMVISIBLE_HIDE;
			if (pData->m_pDUIWnd->DM_IsVisible(false))
			{
				pData->m_pDUIWnd->DM_SetVisible(false,true);
			}
		}
	} while (false);
	return DM_ECODE_OK;
}

DMCode RightXml::s_DMHandleEvent(DM::DMEventArgs *pEvt)
{
	if (ms_pthis&&!ms_pthis->m_bMuted)
	{
		if (DMEventOfPanelArgs::EventID == pEvt->GetEventID())
		{
			DMEventOfPanelArgs* pEvent = (DMEventOfPanelArgs*)pEvt;
			return ms_pthis->DMHandleEvent(pEvent->m_pOrgEvt);
		}
		else
		{
			return ms_pthis->DMHandleEvent(pEvt);// ת��
		}
	}

	return DM_ECODE_FAIL;
}

BOOL RightXml::s_ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID /*= 0*/)
{
	if (ms_pthis)
	{
		ms_pthis->ProcessWindowMessage(hWnd,uMsg,wParam,lParam,lResult,dwMsgMapID);
		if (ms_pthis->m_pHostAttr)
		{
			ms_pthis->m_pHostAttr->ProcessWindowMessage(hWnd,uMsg,wParam,lParam,lResult,dwMsgMapID);
		}
		if (ms_pthis->m_pWidgetAttr)
		{
			ms_pthis->m_pWidgetAttr->ProcessWindowMessage(hWnd,uMsg,wParam,lParam,lResult,dwMsgMapID);
		}
	}
	return FALSE;
}
