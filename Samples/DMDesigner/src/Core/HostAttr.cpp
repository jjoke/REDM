#include "DMDesignerAfx.h"
#include "HostAttr.h"

BEGIN_MSG_MAP(HostAttr)
	MSG_WM_LBUTTONDOWN(OnLButtonDown)
END_MSG_MAP()
BEGIN_EVENT_MAP(HostAttr)
	EVENT_NAME_COMMAND(L"ds_host_expand", OnExpand)
END_EVENT_INBASE()

HostAttr*  HostAttr::ms_pthis = NULL;
HostAttr::HostAttr()
{  
	m_pPanel     = m_pObjXml->m_pRighXml->m_pList->FindChildByName(L"ds_attr_host_panel",true);DMASSERT(m_pPanel);
	m_pExpandBtn = m_pObjXml->m_pRighXml->m_pList->FindChildByNameT<DUIButton>(L"ds_host_expand",true);DMASSERT(m_pExpandBtn);
	m_pPropFrame = m_pObjXml->m_pRighXml->m_pList->FindChildByNameT<DUIPropFrame>(L"ds_host_prop",true);DMASSERT(m_pPropFrame);
	m_pPropFrame->m_pPropList->m_EventMgr.SubscribeEvent(DM::PropValueChangedArgs::EventID, Subscriber(&HostAttr::OnPropValueChanged, this));
	m_pPropFrame->m_pPropList->m_EventMgr.SubscribeEvent(DM::PropDelingArgs::EventID, Subscriber(&HostAttr::OnPropDeling, this));
	m_pPropFrame->m_pPropList->m_EventMgr.SubscribeEvent(DM::PropDelArgs::EventID, Subscriber(&HostAttr::OnPropDel, this));
	ms_pthis     = this;
	m_pHost      = NULL;
	m_pInitSize  = NULL;
}   

HostAttr::~HostAttr()
{ 
	ms_pthis     = NULL; 
	m_pHost      = NULL;
	m_pInitSize  = NULL;
	if (m_pExpandWnd.isValid()&&m_pExpandWnd->IsWindow())
	{
		m_pExpandWnd->DestroyWindow();
		m_pExpandWnd.Release();
	}
	if (m_pPropFrame)
	{
		m_pPropFrame->m_pPropList->m_EventMgr.UnSubscribeEvent(DM::PropValueChangedArgs::EventID, Subscriber(&HostAttr::OnPropValueChanged, this));
		m_pPropFrame->m_pPropList->m_EventMgr.UnSubscribeEvent(DM::PropDelingArgs::EventID, Subscriber(&HostAttr::OnPropDeling, this));
		m_pPropFrame->m_pPropList->m_EventMgr.UnSubscribeEvent(DM::PropDelArgs::EventID, Subscriber(&HostAttr::OnPropDel, this));
	}

	ReleaseProp();
}

DMCode HostAttr::UpdataInfo(HDMTREEITEM hSel,HDMTREEITEM hOldSel)
{
	DMCode iErr = DM_ECODE_FAIL;
	do 
	{
		ObjTreeDataPtr pData = (ObjTreeDataPtr)m_pObjTree->GetItemData(hSel);
		if (NULL == pData||NULL == pData->m_pDUIWnd)
		{
			DM_MessageBox(L"���������ϲ�Ӧ�ó��ֵĵ���!");
			break;
		}

		if (hOldSel && 0 == m_pObjTree->GetParentItem(hOldSel))// �л�ǰ��DMHWnd����
		{
			m_pObjXml->m_pRighXml->m_pList->ExpandItem(HOST_ATTR,false);
		}
		if (hSel && 0 == m_pObjTree->GetParentItem(hSel))// �л������ϲ��ˣ�Ĭ��ΪDMHWnd����
		{
			m_pObjXml->m_pRighXml->m_pList->ExpandItem(HOST_ATTR,true);
		}
	
		if (m_pHost != pData->m_pRootWnd)// ����Ⱦ��л�
		{
			InitAttrArray(pData);
			m_pHost = pData->m_pRootWnd;
		}
	
		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}

DMCode HostAttr::OnExpand()
{
	DMCode iErr = DM_ECODE_FAIL;
	do 
	{
		if (m_pExpandWnd.isNull())
		{
			m_pExpandWnd.Attach(new AttrExpandWnd(this));
			m_pExpandWnd->DM_CreateWindowEx(L"ds_expandwnd",DM_DEF_WINDOW_NAME,WS_POPUP,WS_EX_TOOLWINDOW|WS_EX_TOPMOST|WS_EX_NOACTIVATE,0,0,0,0,g_pMainWnd->m_hWnd,NULL,false);
			m_pExpandWnd->SendMessage(WM_INITDIALOG);
		} 

		if (m_pExpandWnd->IsWindowVisible())
		{
			m_pExpandWnd->Hide();
		}
		else
		{
			CRect rcExpand = m_pExpandBtn->m_rcWindow;
			m_pExpandBtn->GetContainer()->OnClientToScreen(rcExpand);
			m_pExpandWnd->SetWindowPos(g_pMainWnd->m_hWnd, rcExpand.right,rcExpand.bottom-34,0, 0, SWP_NOSIZE);
			m_pExpandWnd->Show();
		}

		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}

DMCode HostAttr::OnPropValueChanged(DMEventArgs *pEvt)
{
	DMCode iErr = DM_ECODE_FAIL;
	do 
	{
		if (NULL == pEvt || NULL == m_hObjSel)
		{
			break;
		}
		ObjTreeDataPtr pData = (ObjTreeDataPtr)m_pObjTree->GetItemData(m_hObjSel);
		if (pData->m_pRootWnd != m_pHost)
		{// ������һ��������δ����ʱ,ͻȻ�л�����һ��������,��ʱ������
			break;
		}

		PropValueChangedArgs* pEvent = (PropValueChangedArgs*)pEvt;
		CStringW strName  = pEvent->m_pSel->GetName();
		CStringW strValue = pEvent->m_pSel->GetValue();

		iErr = m_pHost->SetAttribute(strName,strValue);
		if (!DMSUCCEEDED(iErr))
		{
			DM_MessageBox(L"��������ʧ��");
		}
		else
		{
			DMXmlNode XmlNode = pData->m_pDoc->m_pXmlDoc->Root(MAINWND_NODE);
			XmlNode.SetAttribute(strName,strValue);
			pData->m_pDoc->m_bChange = true;
		}
		// ֪ͨXmlEditor����
		if (g_pMainWnd)
		{
			DUIXmlUpdateArgs Evt(g_pMainWnd);
			Evt.m_UpdateType = DUIXmlUpdateArgs::XMLUPDATE_CHANGEPROP;
			g_pMainWnd->DV_FireEvent(Evt);
		}
	} while (false);
	return iErr;
}

DMCode HostAttr::OnPropDeling(DMEventArgs *pEvt)
{
	PropDelingArgs* pEvent = (PropDelingArgs*)pEvt;
	if (0 == pEvent->m_pSel->GetData())
	{
		pEvent->m_bCancel = true;// ��ɾ����һ��Ŀ¼
	}

	return DM_ECODE_OK;
}

DMCode HostAttr::OnPropDel(DMEventArgs *pEvt)
{
	DMCode iErr = DM_ECODE_FAIL;
	do 
	{
		if (NULL == pEvt || NULL == m_hObjSel)
		{
			break;
		}
		PropDelArgs* pEvent = (PropDelArgs*)pEvt;
		DMXmlInitAttrPtr pInitAttr = (DMXmlInitAttrPtr)pEvent->m_pSel->GetData();
		if (NULL == pInitAttr)
		{
			break;
		}
		if (pEvent->m_pSel == m_pInitSize)
		{
			m_pInitSize = NULL;
		}
		pInitAttr->m_bUse = false;///< �Ƴ�������Ϊδʹ��״̬
	
		//1.����ȡ��Ĭ�ϵ�value�������ý�ȥ
		CStringW strType,strName,strValue,strDesc;
		g_pAttr->Parse(pInitAttr->m_pAttr,strType,strName,strValue,strDesc);
		ObjTreeDataPtr pData = (ObjTreeDataPtr)m_pObjTree->GetItemData(m_hObjSel);
		iErr = pData->m_pRootWnd->SetAttribute(strName,strValue);
		if (!DMSUCCEEDED(iErr))
		{
			DM_MessageBox(L"��������ʧ��");
		}
		else
		{
			//2.��xml���Ƴ��˽��,����δ����״̬
			DMXmlNode XmlNode = pData->m_pDoc->m_pXmlDoc->Root(MAINWND_NODE);
			XmlNode.RemoveAttribute(strName);
			pData->m_pDoc->m_bChange = true;
		}
		// ֪ͨXmlEditor����
		if (g_pMainWnd)
		{
			DUIXmlUpdateArgs Evt(g_pMainWnd);
			Evt.m_UpdateType = DUIXmlUpdateArgs::XMLUPDATE_DELPROP;
			g_pMainWnd->DV_FireEvent(Evt);
		}
		iErr = DM_ECODE_OK;
	} while (false);

	return iErr;
}

DMCode HostAttr::OnSetWidth(int wid)
{
	if (m_pInitSize)
	{
		m_pInitSize->m_pSize->m_pEdit[0]->SetField(wid);
		m_pInitSize->OnInPlaceCtrlShow(false);//�����ı���Ϣ
		return DM_ECODE_OK;
	}
	else
	{
		SetLogInfo(L"�������initsize����");
		return DM_ECODE_FAIL;
	}
}

DMCode HostAttr::OnSetHei(int hei)
{
	if (m_pInitSize)
	{
		m_pInitSize->m_pSize->m_pEdit[1]->SetField(hei);
		m_pInitSize->OnInPlaceCtrlShow(false);//�����ı���Ϣ
		return DM_ECODE_OK;
	}
	else
	{
		SetLogInfo(L"�������initsize����");
		return DM_ECODE_FAIL;
	}
}

void HostAttr::OnLButtonDown(UINT nFlags, CPoint point)
{
	CPoint ptScreen = point;
	::ClientToScreen(g_pMainWnd->m_hWnd,&ptScreen);
	CRect rcExpand = m_pExpandBtn->m_rcWindow;
	m_pExpandBtn->GetContainer()->OnClientToScreen(rcExpand);
	if (!rcExpand.PtInRect(ptScreen))
	{
		if (m_pExpandWnd.isValid()&&m_pExpandWnd->IsWindowVisible())
		{
			m_pExpandWnd->Hide();
		}
	}

	SetMsgHandled(FALSE);
}

DUIWindow* HostAttr::GetOwnerWindow()
{
	if (m_pPanel&&m_pPanel->DM_IsVisible())
	{
		return m_pPanel;
	}
	return NULL;
}

DMCode HostAttr::OnTreeInit(AttrTree* pTree)
{
	DMCode iErr = DM_ECODE_FAIL;
	do 
	{
		pTree->RemoveAllItems();
		DMXmlDocument doc;
		DMXmlNode NoDataNode = doc.Base();
		DMXmlNode DataNode = doc.Base();
		AttrExpandWnd::InitTreeNode(NoDataNode,false);
		AttrExpandWnd::InitTreeNode(DataNode,true);

		//1. �����
		NoDataNode.SetAttribute(XML_TEXT,L"DMHWndAttr");
		HDMTREEITEM hTreeRoot = pTree->InsertItem(NoDataNode);

		//2. �����ӽ��
		int iCount = (int)GetCount();
		for (int i=0;i<iCount;i++)
		{
			DMXmlInitAttrPtr pInitAttr = GetObj(i);
			if (false == pInitAttr->m_bUse)
			{
				DataNode.SetAttribute(XML_TEXT,pInitAttr->m_pAttr->GetName());
				HDMTREEITEM hRet = pTree->InsertItem(DataNode,hTreeRoot);
				pTree->SetItemData(hRet,(LPARAM)pInitAttr);	
			}
		}
		pTree->Expand(hTreeRoot);
		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}

DMCode HostAttr::OnTreeSel(AttrTree* pTree)
{
	DMCode iErr = DM_ECODE_FAIL;
	do 
	{
		HDMTREEITEM hSel = pTree->GetSelectedItem();
		if (NULL == hSel)
		{
			break;
		}
		DMXmlInitAttrPtr pInitAttr = (DMXmlInitAttrPtr)pTree->GetItemData(hSel);
		if (NULL == pInitAttr)// ���۵�ʱ��ѡ�е��ǵ�һ�У��������ݵ�
		{
			break;
		}
		pInitAttr->m_bUse = true;
		IPropPtr pProp = m_pPropFrame->m_pPropList->m_lstProps.GetHead();
		IPropPtr pPropTemp = m_pPropFrame->AddInitAttrProperty(pInitAttr,pProp);
		
		//���µ�XML��,��Ϊ�¼ӵ�ΪĬ��ֵ�����Բ�����SetAttribute
		if (m_hObjSel)
		{
			CStringW strType,strName,strValue,strDesc;
			g_pAttr->Parse(pInitAttr->m_pAttr,strType,strName,strValue,strDesc);
			ObjTreeDataPtr pData = (ObjTreeDataPtr)m_pObjTree->GetItemData(m_hObjSel);
			pData->m_pDoc->m_pXmlDoc->Root().SetAttribute(strName,strValue);
			pData->m_pDoc->m_bChange = true;

			if (0 == strName.CompareNoCase(DMAttr::DMHWndAttr::SIZE_initsize))
			{
				m_pInitSize = dynamic_cast<PropSize*>(pPropTemp);
			}
		}

		// ֪ͨXmlEditor����
		if (g_pMainWnd)
		{
			DUIXmlUpdateArgs Evt(g_pMainWnd);
			Evt.m_UpdateType = DUIXmlUpdateArgs::XMLUPDATE_ADDPROP;
			g_pMainWnd->DV_FireEvent(Evt);
		}

		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}

DMCode HostAttr::OnTreeEnd(AttrTree* pTree)
{
	pTree->RemoveAllItems();
	return DM_ECODE_OK;
}

DMCode HostAttr::InitAttrArray(ObjTreeDataPtr pData)
{
	ReleaseProp();
	m_pInitSize = NULL;
	DMXmlNode XmlRoot = g_pAttr->GetAttrNode(L"DMHWndAttr");
	DMXmlAttribute XmlAttribute = XmlRoot.FirstAttribute();
	while (XmlAttribute.IsValid())
	{
		DMXmlInitAttrPtr pInitAttr = new DMXmlInitAttr(XmlAttribute);
		AddObj(pInitAttr);
		XmlAttribute = XmlAttribute.NextAttribute();
	}

	// ��ʼ���б� 
	DMXmlNode XmlNode = pData->m_pDoc->m_pXmlDoc->Root(MAINWND_NODE);
	XmlAttribute = XmlNode.FirstAttribute();
	while (XmlAttribute.IsValid())
	{
		CStringW strName = XmlAttribute.GetName();
		CStringW strValue = XmlAttribute.GetValue();
		DMXmlInitAttrPtr pInitAttr = FindAttrByName(strName);
		IPropPtr pProp = m_pPropFrame->m_pPropList->m_lstProps.GetHead();
		if (pInitAttr)
		{
			IPropPtr pPropTemp = m_pPropFrame->AddInitAttrProperty(pInitAttr,pProp,strValue);
			pInitAttr->m_bUse = true;// ��ʼ�����ģ�������expand�����г���
			if (0 == strName.CompareNoCase(DMAttr::DMHWndAttr::SIZE_initsize))
			{
				m_pInitSize = dynamic_cast<PropSize*>(pPropTemp);
			}
		} 

		XmlAttribute = XmlAttribute.NextAttribute();
	}

	return DM_ECODE_OK;
}

DMXmlInitAttrPtr HostAttr::FindAttrByName(CStringW strName)
{
	DMXmlInitAttrPtr pInitAttr = NULL;
	do 
	{
		if (strName.IsEmpty())
		{
			break;
		}

		int iCount = (int)GetCount();
		for (int i=0;i<iCount;i++)
		{
			DMXmlInitAttrPtr ptr = GetObj(i);
			CStringW strTempType,strTempName;
			g_pAttr->ParseName(ptr->m_pAttr,strTempType,strTempName);
			if (0 == strName.CompareNoCase(strTempName))
			{
				pInitAttr = ptr;
				break;
			}
		}
	} while (false);
	return pInitAttr;
}

void HostAttr::PreArrayObjRemove(const DMXmlInitAttrPtr &obj)
{
	delete obj;
}

void HostAttr::ReleaseProp()
{
	if (m_pPropFrame)
	{
		m_pPropFrame->m_pPropList->SetCurSel(NULL);// ������ΪNULL,���Ƴ�prop list ��Ȼ���prop descˢ��,����ʱprop list ��������,���ܻ���������
		IPropPtr pProp = m_pPropFrame->m_pPropList->m_lstProps.GetHead();// ��һ��attr����
		pProp->RemoveAllSubItem();
		RemoveAll();
	}
}

DMCode HostAttr::s_DMHandleEvent(DM::DMEventArgs *pEvt)
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



