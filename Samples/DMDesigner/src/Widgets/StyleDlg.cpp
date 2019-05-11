#include "DMDesignerAfx.h"
#include "StyleDlg.h"

BEGIN_MSG_MAP(StyleDlg)
	MSG_WM_INITDIALOG(OnInitDialog) 
	MSG_WM_SIZE(OnSize)
	MSG_WM_DESTROY(OnDestroy)
	MSG_WM_LBUTTONDOWN(OnLButtonDown)
	CHAIN_MSG_MAP(DMHDialog)
END_MSG_MAP()
BEGIN_EVENT_MAP(StyleDlg)
	EVENT_NAME_COMMAND(L"ds_style_expand",	OnExpand)
END_EVENT_MAP()
StyleDlg::StyleDlg(bool bEditMode /*= false*/)
{
	m_bEditMode = bEditMode;
	m_pExpandBtn = NULL;
	m_pPropFrame = NULL;
}

StyleDlg::~StyleDlg()
{
	RemoveAll();
}

BOOL StyleDlg::OnInitDialog(HWND wndFocus, LPARAM lInitParam)
{
	m_pExpandBtn = FindChildByNameT<DUIButton>(L"ds_style_expand");
	m_pPropFrame = FindChildByNameT<DUIPropFrame>(L"ds_style_prop");
	m_pPropFrame->m_pPropList->m_EventMgr.SubscribeEvent(DM::PropDelingArgs::EventID, Subscriber(&StyleDlg::OnPropDeling, this));
	m_pPropFrame->m_pPropList->m_EventMgr.SubscribeEvent(DM::PropDelArgs::EventID, Subscriber(&StyleDlg::OnPropDel, this));
	// ��ʼ����array
	InitAttrArray();

	m_pObjXml    = g_pMainWnd->m_pDesignerXml;
	m_pProjTree  = g_pMainWnd->FindChildByNameT<ProjTree>(L"ds_projtree");
	DMXmlNode XmlBase = m_StyleDoc.Base();
	m_StyleNode = XmlBase.InsertChildNode(XML_STYLE);
	if (m_bEditMode)// �༭ģʽ����ʼ�����ֱ���
	{
		DMXmlNodePtr pNode = (DMXmlNodePtr)m_pProjTree->GetItemData(m_pObjXml->m_hProjSel);
		CStringW strId = pNode->Attribute(XML_ID);
		if (strId.IsEmpty())
		{
			pNode->SetAttribute(XML_ID,L"",false);///���idԭ���ʹ���(ֻ��Ϊ��),�򲻻����
			m_pObjXml->SetDocUnSave(pNode);
		}
		DMXmlAttribute XmlAttribute = pNode->FirstAttribute();
		while (XmlAttribute.IsValid())
		{
			CStringW strName = XmlAttribute.GetName();
			CStringW strValue = XmlAttribute.GetValue();
			DMXmlInitAttrPtr pInitAttr = FindByName(strName);
			IPropPtr pProp = m_pPropFrame->m_pPropList->m_lstProps.GetHead();
			if (pInitAttr)
			{
				m_pPropFrame->AddInitAttrProperty(pInitAttr,pProp,strValue);
				pInitAttr->m_bUse = true;
			}
			
			XmlAttribute = XmlAttribute.NextAttribute();
		}
	}
	else
	{
		DMXmlInitAttrPtr pInitAttr = FindByName(XML_ID);
		IPropPtr pProp = m_pPropFrame->m_pPropList->m_lstProps.GetHead();
		if (pInitAttr)
		{// ��֤ID�Ǳ�����ڵ�
			m_pPropFrame->AddInitAttrProperty(pInitAttr,pProp);
			pInitAttr->m_bUse = true;
		}
	}

	return TRUE;
}

void StyleDlg::OnSize(UINT nType, CSize size)
{  
	if (!IsIconic()) 
	{
		CRect rcWnd;
		::GetWindowRect(m_hWnd, &rcWnd);
		::OffsetRect(&rcWnd, -rcWnd.left, -rcWnd.top);  
		HRGN hWndRgn = ::CreateRoundRectRgn(0, 0, rcWnd.right, rcWnd.bottom,4,4);
		SetWindowRgn(hWndRgn, TRUE);
		::DeleteObject(hWndRgn); 
	}                 
	SetMsgHandled(FALSE);
}

void StyleDlg::OnDestroy()
{
	if (m_pPropFrame)
	{
		m_pPropFrame->m_pPropList->m_EventMgr.UnSubscribeEvent(DM::PropDelingArgs::EventID, Subscriber(&StyleDlg::OnPropDeling, this));
		m_pPropFrame->m_pPropList->m_EventMgr.UnSubscribeEvent(DM::PropDelArgs::EventID, Subscriber(&StyleDlg::OnPropDel, this));
	}

	SetMsgHandled(FALSE);
}

void StyleDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rcExpand = m_pExpandBtn->m_rcWindow;
	if (!rcExpand.PtInRect(point))
	{
		if (m_pExpandWnd.isValid()&&m_pExpandWnd->IsWindowVisible())
		{
			m_pExpandWnd->Hide();
		}
	}
	
	SetMsgHandled(FALSE);
}

DUIWindow* StyleDlg::GetOwnerWindow()
{
	return this;
}

DMCode StyleDlg::OnTreeInit(AttrTree* pTree)
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
		NoDataNode.SetAttribute(XML_TEXT,L"DUIStyleAttr");
		HDMTREEITEM hTreeRoot =  pTree->InsertItem(NoDataNode);

		int iCount = (int)GetCount();
		if (0 == iCount)
		{
			break;
		}
		
		//2. �����ӽ��
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

DMCode StyleDlg::OnTreeSel(AttrTree* pTree)
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
		m_pPropFrame->AddInitAttrProperty(pInitAttr,pProp);

		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}

DMCode StyleDlg::OnTreeEnd(AttrTree* pTree)
{
	pTree->RemoveAllItems();
	return DM_ECODE_OK;
}

DMCode StyleDlg::OnPropDeling(DMEventArgs *pEvt)
{
	PropDelingArgs* pEvent = (PropDelingArgs*)pEvt;
	DMXmlInitAttrPtr pInitAttr = (DMXmlInitAttrPtr)pEvent->m_pSel->GetData();
	if (NULL == pInitAttr
		||0 == _wcsicmp(pInitAttr->m_pAttr->GetName(),L"STRING_ID"))
	{
		DM_MessageBox(L"����ɱ�ɾ��");
		pEvent->m_bCancel = true;// ��ɾ��id������
	}
	return DM_ECODE_OK;
}

DMCode StyleDlg::OnPropDel(DMEventArgs *pEvt)
{
	PropDelArgs* pEvent = (PropDelArgs*)pEvt;
	DMXmlInitAttrPtr pInitAttr = (DMXmlInitAttrPtr)pEvent->m_pSel->GetData();
	if (pInitAttr)
	{
		pInitAttr->m_bUse = false;
	}
	return DM_ECODE_OK;
}

DMCode StyleDlg::OnExpand()
{
	DMCode iErr = DM_ECODE_FAIL;
	do 
	{
		if (m_pExpandWnd.isNull())
		{
			m_pExpandWnd.Attach(new AttrExpandWnd(this));
			m_pExpandWnd->DM_CreateWindowEx(L"ds_expandwnd",DM_DEF_WINDOW_NAME,WS_POPUP,WS_EX_TOOLWINDOW|WS_EX_TOPMOST|WS_EX_NOACTIVATE,0,0,0,0,m_hWnd,NULL,false);
			m_pExpandWnd->SendMessage(WM_INITDIALOG);
		} 

		if (m_pExpandWnd->IsWindowVisible())
		{
			m_pExpandWnd->Hide();
		}
		else
		{
			CRect rcExpand = m_pExpandBtn->m_rcWindow;
			ClientToScreen(rcExpand);
			m_pExpandWnd->SetWindowPos(m_hWnd, rcExpand.right,rcExpand.bottom-34,0, 0, SWP_NOSIZE);
			m_pExpandWnd->Show();
		}

		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}

DMCode StyleDlg::InitAttrArray()
{
	DMXmlNode XmlRoot = g_pAttr->GetAttrNode(L"DUIStyleAttr");
	DMXmlAttribute XmlAttribute = XmlRoot.FirstAttribute();
	while (XmlAttribute.IsValid())
	{
		DMXmlInitAttrPtr pInitAttr = new DMXmlInitAttr(XmlAttribute);
		AddObj(pInitAttr);
		XmlAttribute = XmlAttribute.NextAttribute();
	}
	return DM_ECODE_OK;
}

void StyleDlg::PreArrayObjRemove(const DMXmlInitAttrPtr &obj)
{
	delete obj;
}

DMCode StyleDlg::OnOK()
{
	DMCode iErr = DM_ECODE_FAIL;
	HDMTREEITEM hAdd = NULL;
	do 
	{
		//1. ����style xml�ڵ�
		if (m_pPropFrame->m_pPropList->m_pSel)
		{
			m_pPropFrame->m_pPropList->m_pSel->OnInPlaceCtrlShow(false);
		}
		IPropPtr pProp = m_pPropFrame->m_pPropList->m_lstProps.GetHead();
		pProp->UpdateSubXml(m_StyleNode);
		CStringW strId = m_StyleNode.Attribute(XML_ID);strId.Trim();
		if (strId.IsEmpty())
		{
			DM_MessageBox(L"δ����id!",MB_OK,L"MSG",m_hWnd);
			break;
		}

		if (m_bEditMode)// editģʽ
		{
			//2.�ж�id�Ƿ��Ѵ���
			bool bFind = false;
			HDMTREEITEM hParentItem = m_pProjTree->GetParentItem(m_pObjXml->m_hProjSel);
			if (hParentItem)
			{
				HDMTREEITEM hChildItem = m_pProjTree->GetChildItem(hParentItem);
				while (hChildItem)
				{
					if (hChildItem != m_pObjXml->m_hProjSel)
					{// �����༭����
						DMXmlNodePtr pChildNode = (DMXmlNodePtr)m_pProjTree->GetItemData(hChildItem);
						if (0 == strId.CompareNoCase(pChildNode->Attribute(XML_ID)))
						{
							bFind = true;
							break;
						}
					}
					hChildItem = m_pProjTree->GetNextSiblingItem(hChildItem);
				}
			}
			if (bFind)
			{
				DM_MessageBox(L"id�Ѵ���,����������!",MB_OK,L"MSG",m_hWnd);
				break;
			}

			bool bChanged = false;
			DMXmlNodePtr pNode = (DMXmlNodePtr)m_pProjTree->GetItemData(m_pObjXml->m_hProjSel);
			DMXmlAttribute XmlAttribute = m_StyleNode.FirstAttribute();
			while (XmlAttribute.IsValid())
			{
				CStringW strName = XmlAttribute.GetName();
				CStringW strValue = XmlAttribute.GetValue();
				CStringW strOldValue = pNode->Attribute(strName);
				if (0 != strValue.CompareNoCase(strOldValue))
				{
					bChanged = true;
					//3. ����style xml�ڵ��б��ı������
					pNode->SetAttribute(strName,strValue);
				}
				XmlAttribute = XmlAttribute.NextAttribute();
			}
			if (bChanged)
			{
				m_pObjXml->SetDocUnSave(pNode);
			}

			//4. ����tree�����ʾ
			DM::LPTVITEMEX pData = m_pProjTree->GetItem(m_pObjXml->m_hProjSel);
			pData->pPanel->m_pDUIXmlInfo->m_strText = pNode->Attribute(XML_ID);
			m_pProjTree->UpdateItemRect(m_pObjXml->m_hProjSel);

			iErr = DM_ECODE_OK;
			EndDialog(IDOK);
			break;
		}

		//2.�ж�id�Ƿ��Ѵ���
		DMXmlNodePtr pNode = (DMXmlNodePtr)m_pProjTree->GetItemData(m_pObjXml->m_hProjSel);
		DMXmlNode XmlNode = pNode->FirstChild();
		bool bFind = false;
		while (XmlNode.IsValid())
		{
			if (0 == strId.CompareNoCase(XmlNode.Attribute(XML_ID)))
			{
				bFind = true;
				break;
			}
			XmlNode = XmlNode.NextSibling();
		}
		if (bFind)
		{
			DM_MessageBox(L"id�Ѵ���,����������!",MB_OK,L"MSG",m_hWnd);
			break;
		}

		//3. ���뵽xml��
		DMXmlNodePtr pStyleTypeNode = (DMXmlNodePtr)m_pProjTree->GetItemData(m_pObjXml->m_hProjSel);
		DMXmlNode XmlStyleNode = pStyleTypeNode->InsertCopyChildNode(&m_StyleNode);
		
		//4. ���뵽tree��
		DMXmlDocument doc;
		DMXmlNode DataNode = doc.Base();
		m_pObjXml->InitProjTreeNode(DataNode,true);
		hAdd = m_pObjXml->InsertProjTreeItem(DataNode,strId,m_pObjXml->m_hProjSel);
		m_pObjXml->BindProjTreeData(XmlStyleNode,hAdd);

		//5. ����xmlΪδ����״̬
		m_pObjXml->SetDocUnSave(pStyleTypeNode);

		//���������ͼ
		if (hAdd&&m_pObjXml->m_bInitObjTree)// 
		{
			//1. ���ӵ�style��
			DMXmlDocument Doc;
			DMXmlNode XmlBase = Doc.Base();
			DMXmlNode XmlStyle = XmlBase.InsertChildNode(XML_STYLE);
			XmlStyle.SetAttribute(XML_NAME,pStyleTypeNode->Attribute(XML_NAME));// �����name��Ϊ����style��name
			XmlStyle.InsertCopyChildNode(&XmlStyleNode);
			g_pDMApp->AddStylePoolItem(XmlStyle);
		}

		if (hAdd)
		{
			m_pProjTree->SelectItem(hAdd);
		}

		EndDialog(IDOK);
		
		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}

DMXmlInitAttrPtr StyleDlg::FindByName(CStringW strName)
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





