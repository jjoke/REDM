 #include "DMDesignerAfx.h"
#include "DUIRoot.h"
       
DocDataPtr g_pCurDoc = NULL;
DMXmlDocument* GetSubXmlDoc(LPCWSTR lpszType,LPCWSTR lpszResName)
{
	DMXmlDocument* pXmlDoc = NULL;
	do 
	{
		if (NULL==lpszType||NULL==lpszResName||NULL==g_pCurDoc)
		{
			break;
		}

		DMSmartPtrT<ResFolder>pRes = g_pMainWnd->m_pDesignerXml->m_pRes;
		CStringW strPath = pRes->GetItemPath(lpszType,lpszResName,L"");
		if (!PathFileExists(strPath))
		{
			break;
		}
		DocDataPtr pSubData = g_pMainWnd->m_pDesignerXml->FindDocData(strPath);
		if (pSubData&&pSubData->IsValid())// ԭ���ѽ�������
		{
			g_pCurDoc->AddObj(pSubData);// ������xml���γ���xml-���sub  xml
			pXmlDoc = pSubData->m_pXmlDoc;
			break;
		}
		pSubData = new DocData(strPath);
		if (!pSubData->IsValid())
		{
			DM_DELETE(pSubData);
			break;
		}
		g_pMainWnd->m_pDesignerXml->AddObj(pSubData);
		g_pCurDoc->AddObj(pSubData);// ������xml���γ���xml-���sub  xml
		pXmlDoc = pSubData->m_pXmlDoc;
	} while (false);
	return pXmlDoc;
}
CPoint DUIRoot::m_pAddParentPt;
DUIRoot::DUIRoot()
{
	m_pParent  = NULL;
	m_hRoot    = NULL;
	m_pObjTree = g_pMainWnd->FindChildByNameT<ObjTree>(L"ds_objtree");DMASSERT(m_pObjTree); 
	m_pObjXml  = g_pMainWnd->m_pDesignerXml;
	m_bDown = false;	
	m_pAddWnd  = NULL;
}

DMCode DUIRoot::InitDesignEditor(HDMTREEITEM hRootTree)
{
	DMCode iErr = DM_ECODE_FAIL;
	do 
	{
		ObjTreeDataPtr pData = (ObjTreeDataPtr)m_pObjTree->GetItemData(hRootTree);
		if (NULL == pData||NULL == pData->m_pDoc||!pData->m_pDoc->IsValid())// ��Ҫʹ��pData->IsValid()���ж�,��Ϊ��ʱDUI���ڻ�û�д���
		{
			break; 
		} 
		m_XmlNode = pData->m_pDoc->m_pXmlDoc->Root(MAINWND_NODE);
		if (!m_XmlNode.IsValid())
		{
			break;
		}
		// ����˽��Skin�ڵ�,�ⲿ�����ͷ���---------------
		DMXmlNode XmlSkin = m_XmlNode.FirstChild(L"skin");
		while (XmlSkin.IsValid())
		{
			g_pDMApp->AddSkinPoolItem(XmlSkin);
			XmlSkin = XmlSkin.NextSibling(L"skin");
		}

		// ����˽��Style�ڵ�,�ⲿ�����ͷ���--------------
		DMXmlNode XmlStyle = m_XmlNode.FirstChild(L"style");
		while (XmlStyle.IsValid())
		{
			g_pDMApp->AddStylePoolItem(XmlStyle);
			XmlStyle = XmlStyle.NextSibling(L"style");
		}

		//1. ��OnAttributeFinished�������˴�С
		DMBase::InitDMData(m_XmlNode);

		//2.�����ӿؼ�
		g_pCurDoc = pData->m_pDoc;
		g_pDMApp->SetSubXmlDocCallBack(GetSubXmlDoc);
		InitDMData(m_XmlNode.FirstChild(DUIROOT_NODE));
		g_pDMApp->SetSubXmlDocCallBack(NULL);
		g_pCurDoc = NULL;

		m_hRoot = hRootTree;
		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}

DMCode DUIRoot::SetDesignMode(DesignMode ds_mode)
{
	m_DesignMod = ds_mode;
	return DM_ECODE_OK;
}

void DUIRoot::OnLButtonDown(UINT nFlags,CPoint pt)
{
	DM_SetCapture();
	if (MoveMode == m_DesignMod||AddMode == m_DesignMod)
	{
		m_bDown = true;
		m_StartDragPt = pt;
		m_TrackDragPt = m_StartDragPt;
		m_StartDragRc = m_rcWindow;
	}
	else if (SelectMode == m_DesignMod)
	{
		DUIWND hDUIHoverWnd = __super::HitTestPoint(pt,true);
		if (m_pObjXml->m_hObjSel)
		{
			ObjTreeDataPtr pData = (ObjTreeDataPtr)m_pObjTree->GetItemData(m_pObjXml->m_hObjSel);
			if (pData->m_pDUIWnd->GetDUIWnd() != hDUIHoverWnd)
			{
				DUIWindow* pHoverWnd = g_pDMApp->FindDUIWnd(hDUIHoverWnd);
				SelOrHoverTreeItemByDUIWnd(m_hRoot,pHoverWnd,true);
			}
		}
	}
}

void DUIRoot::OnLButtonUp(UINT nFlags,CPoint pt)
{
	m_bDown = false;
	if (AddMode == m_DesignMod)
	{
		if (m_pAddWnd && 0 == _wcsicmp(m_pAddWnd->V_GetClassName(),DUISplitLayout::GetClassName()))
		{// ���splite���⴦��,spliteӦ����������ɺ���ִ�г�ʼ��
			DUISplitLayout* pSplit = (DUISplitLayout*)m_pAddWnd;
			pSplit->m_iFixWid = -1;
			pSplit->DV_UpdateChildLayout();
		}  
	}
	m_pAddWnd  = NULL;
	m_pAddParentPt.SetPoint(0,0);
	DM_ReleaseCapture();
} 

void DUIRoot::OnRButtonDown(UINT nFlags, CPoint pt)
{
	bool bRet = false;
	do 
	{
		if (NULL == m_pObjXml||NULL == m_pObjTree||NULL == m_pObjTree->m_hHoverItem)
		{
			break;
		}
		m_pObjTree->SelectItem(m_pObjTree->m_hHoverItem);
		m_pObjXml->PopObjTreeMenu(m_pObjTree->m_hHoverItem);
		bRet = true;
	} while (false);
	SetMsgHandled(true == bRet);
}

void DUIRoot::OnMouseMove(UINT nFlags,CPoint pt)
{
	if (MoveMode == m_DesignMod)
	{
		if (m_bDown)
		{
			m_TrackDragPt = pt;
			CPoint ptOffset = m_TrackDragPt - m_StartDragPt;
			CRect rcWnd = m_StartDragRc;
			rcWnd.OffsetRect(ptOffset);
			DM_FloatLayout(rcWnd);
			if (m_pParent)
			{	
				m_pParent->UpdateScrollRangeSize();
				m_pParent->SelFrameInAllMode();
				m_pParent->DM_Invalidate();
			}
		}
		SetAttribute(L"cursor",L"ds_tool_move");
	}
	else if (SelectMode == m_DesignMod)
	{
		SetAttribute(L"cursor",L"arrow");
	}
	else if (AddMode == m_DesignMod)
	{
		SetAttribute(L"cursor",L"ds_add");
		if (m_bDown)
		{
			m_TrackDragPt = pt;
			MLDownInAddMode(pt);
		}
	}
}

DUIWND DUIRoot::HitTestPoint(CPoint pt,bool bFindNoMsg)
{
	if (MoveMode != m_DesignMod)
	{
		DUIWND hDUIHoverWnd = __super::HitTestPoint(pt,true);
		DUIWindow* pHoverWnd = g_pDMApp->FindDUIWnd(hDUIHoverWnd);
		if (pHoverWnd&&m_pParent)
		{
			m_pParent->HoverInSelOrAddMode(pHoverWnd);
			SelOrHoverTreeItemByDUIWnd(m_hRoot,pHoverWnd,false);
		}
	}

	return m_hDUIWnd;
}

HDMTREEITEM DUIRoot::SelOrHoverTreeItemByDUIWnd(HDMTREEITEM hRoot,DUIWindow* pDUIWnd,bool bSel)
{
	HDMTREEITEM hTreeItem = NULL;
	do 
	{
		ObjTreeDataPtr pData = (ObjTreeDataPtr)m_pObjTree->GetItemData(hRoot);
		if (pData&&pData->m_pDUIWnd == pDUIWnd)
		{
			hTreeItem = hRoot;
			break;
		}

		HDMTREEITEM hChild = m_pObjTree->GetChildItem(hRoot);
		while (hChild)
		{
			HDMTREEITEM hTemp = SelOrHoverTreeItemByDUIWnd(hChild,pDUIWnd,bSel);
			if (hTemp)
			{
				hTreeItem = hTemp;
				break;
			}
			hChild = m_pObjTree->GetNextSiblingItem(hChild);
		}

	} while (false);
	if (hTreeItem)
	{
		if (bSel)
		{
			m_pObjTree->SelectItem(hTreeItem);
		}
		else
		{
			if (hTreeItem == m_hRoot)
			{
				hTreeItem = m_pObjTree->GetChildItem(m_hRoot);//hoverֻ����ͣ����Root��,��ͣ�������ڲ�
			}
			m_pObjTree->HoverItem(hTreeItem,false);
		}
	}
	
	return hTreeItem;
}

bool DUIRoot::MLDownInSelMode(CPoint pt,DUIWindow* pCurSelWnd)
{
	bool bRet = false;
	do 
	{
		DUIWND hDUIHoverWnd = __super::HitTestPoint(pt,true);
		DUIWindow* pHoverWnd = g_pDMApp->FindDUIWnd(hDUIHoverWnd);
		if (pCurSelWnd == pHoverWnd||NULL == pHoverWnd)// ��Ȼ�δ�ҵ�����false,dragframe���������ڱ߿�
		{
			break;
		}

		if (pHoverWnd&&m_pParent)
		{
			HDMTREEITEM hSel = SelOrHoverTreeItemByDUIWnd(m_hRoot,pHoverWnd,true);
		}
		bRet = true;
	} while (false);
	return bRet;
}

bool DUIRoot::MLDownInAddMode(CPoint pt)
{
	bool bRet = false;
	do 
	{
		m_pAddWnd = GetAddChild();
		if (NULL == m_pAddWnd)
		{
			break;
		}
		DUIPos* m_pPos = m_pObjXml->m_pRighXml->m_pPosAttr->m_pPos;
		CRect rcDrag(m_StartDragPt,m_TrackDragPt);
		rcDrag.NormalizeRect();
		CPoint ptFirst = rcDrag.TopLeft() - m_pAddParentPt;
		m_pPos->m_pItem[0]->m_pEdit->SetWindowText(IntToString(DMABS(ptFirst.x)));
		m_pPos->m_pItem[1]->m_pEdit->SetWindowText(IntToString(DMABS(ptFirst.y)));
		m_pPos->m_pItem[2]->m_pEdit->SetWindowText(IntToString(rcDrag.Width()));
		m_pPos->m_pItem[3]->m_pEdit->SetWindowText(IntToString(rcDrag.Height()));
		
		bRet = true;
	} while (false);
	return bRet;
} 

bool DUIRoot::IsSupportAddChild(DUIWindow* pParentWnd,CStringW strReg)
{
	bool bRet = true;
	CStringW strParent = pParentWnd->V_GetClassName();
	do 
	{
		if (0 == strParent.CompareNoCase(L"TabCtrl")&&0 != strReg.CompareNoCase(L"TabPage")
			||0 == strReg.CompareNoCase(L"TabPage")&&0 != strParent.CompareNoCase(L"TabCtrl"))
		{
			bRet = false;
			break;
		}

		if (0 == strParent.CompareNoCase(L"ListBox")
			||0 == strParent.CompareNoCase(L"ListBoxEx")
			||0 == strParent.CompareNoCase(L"TreeCtrl")
			||0 == strParent.CompareNoCase(L"TreeCtrlEx")
			||0 == strParent.CompareNoCase(L"ListCtrlEx")
			||0 == strParent.CompareNoCase(L"item")
			||0 == strParent.CompareNoCase(L"treeitem")
			||0 == strParent.CompareNoCase(L"splitlayout")
			)
		{
			bRet = false;
			break;
		} 
	} while (false);
	if (false == bRet)
	{
		CStringW strInfo;
		strInfo.Format(L"[%s]��������Ϊ�ӿؼ���ӵ�[%s]��",strReg,strParent);
		SetLogInfo(strInfo);
	}
	return bRet;
}

DUIWindow* DUIRoot::CreateAddChild(DUIWindow* pParentWnd,CStringW strReg)
{
	DUIWindow *pChild = NULL;
	do 
	{
		if (!DMSUCCEEDED(g_pDMApp->CreateRegObj((void**)&pChild, strReg,DMREG_FlowLayout)))
		{// ��ʽ����Ҳ��duiwindow,�������ж��Ƿ�Ϊ��ʽ���ֶ���
			g_pDMApp->CreateRegObj((void**)&pChild,strReg,DMREG_Window);
		}      

		if (NULL == pChild)
		{ 
			break;
		}

		pParentWnd->DM_InsertChild(pChild);
	} while (false);
	return pChild;
}

bool DUIRoot::InitAddChild(ObjTreeData* pParentData,DUIWindow* pWnd,CRect rcDrag,bool bRight)
{
	bool bRet = false;
	do 
	{
		if (NULL == pParentData ||NULL == pParentData->m_pDUIWnd || NULL == pWnd)
		{
			break;
		}
		
		DMXmlNode XmlNode = bRight? g_pAttr->m_CopyNode:g_pAttr->Parse(pWnd->V_GetClassName());
		if (!XmlNode.IsValid())
		{
			break;
		}

		CRect rcMeasure;
		pParentData->m_pDUIWnd->DV_GetChildMeasureLayout(rcMeasure);
		m_pAddParentPt = rcMeasure.TopLeft();
		bool bTabPage = 0 == _wcsicmp(pWnd->V_GetClassName(),L"TabPage");
		CStringW strPos = L"0,0,-0,-0"; 
		if (false == bTabPage)
		{
			CPoint ptFirst = rcDrag.TopLeft() - m_pAddParentPt;
			strPos.Format(L"%d,%d,@%d,@%d",ptFirst.x,ptFirst.y,rcDrag.Width(),rcDrag.Height());
		}
		XmlNode.SetAttribute(L"pos",strPos,false);
		DMXmlNode ChildNode = pParentData->m_pXmlNode->InsertCopyChildNode(&XmlNode);
		pParentData->m_pDoc->m_bChange = true;

		// ��ֹ���Ƶ���node����sub����
		g_pCurDoc = pParentData->m_pDoc;
		g_pDMApp->SetSubXmlDocCallBack(GetSubXmlDoc);
		pWnd->InitDMData(ChildNode);// ʹ��ChildNode����ʹ����ʱXmlNode,��Ϊ���뱣֤xmlnodeΪpdoc��ӵ��
		g_pDMApp->SetSubXmlDocCallBack(NULL);

		if (bTabPage)
		{
			((DUITabCtrl*)(pParentData->m_pDUIWnd))->m_PageArray.Add((DUITabPage*)pWnd);
		}

		bRet = true;
	} while (false);
	return bRet;
}

DUIWindow* DUIRoot::GetAddChild()
{
	DUIWindow* pAdd = NULL;
	do 
	{
		if (m_pAddWnd)
		{
			pAdd = m_pAddWnd;
			break; 
		} 

		CRect rcDrag(m_StartDragPt,m_TrackDragPt);
		rcDrag.NormalizeRect();
		HDMTREEITEM hHoverItem = m_pObjTree->m_hHoverItem;
		if (NULL == m_pParent ||NULL == hHoverItem ||rcDrag.IsRectEmpty())
		{
			break;
		}

		//1.�ж��Ƿ�����
		DM::LPTVITEMEX pTviData = m_pObjTree->GetItem(hHoverItem);
		if (DMTVEXLock_UnLocked != pTviData->iLockValue)
		{
			SetLogInfo(L"�ؼ����ڱ�����״̬���޷������ӿؼ�!");
			break;
		}

		ObjTreeDataPtr pData = (ObjTreeDataPtr)m_pObjTree->GetItemData(hHoverItem);
		DUIWindow* pHoverWnd = pData->m_pDUIWnd;
		//2. �жϴ����Ƿ�֧�ֲ����Ӵ���
		CStringW strReg = m_pParent->m_pCheckBtn->m_pDUIXmlInfo->m_strText;
		if (!IsSupportAddChild(pHoverWnd,strReg))
		{ 
			break;
		}

		//3. �����´���
		DUIWindow *pChild = CreateAddChild(pHoverWnd,strReg);
		if (NULL == pChild)
		{ 
			break;
		}

		//4. ��ʼ��ͨ������
		InitAddChild(pData,pChild,rcDrag);

		//5.ö�ټ���
		m_pObjXml->EnumChildTreeItem(this,pChild,hHoverItem);
	
		//6.ѡ�����һ������,���¼��������
		m_pObjTree->SelectItem(m_pObjTree->GetChildItem(hHoverItem,false));

		if (0 == strReg.CompareNoCase(L"ie"))
		{
			pChild->DM_SetVisible(true,true);// ����һ�Σ����ӳټ��ص�ieǿ�Ƴ�ʼ��
		}
		
		pAdd = pChild;
	} while (false);
	return pAdd;
}

DMCode DUIRoot::OnAttributeFinished(LPCWSTR pszAttribute,LPCWSTR pszValue,bool bLoadXml,DMCode iErr)
{
	// DMHWnd�����ԣ�����ģ��֧��HostAttr��SetAttribute
	if (0 == dm_wcsicmp(pszAttribute, DMAttr::DMHWndAttr::SIZE_minsize)
		||0 == dm_wcsicmp(pszAttribute, DMAttr::DMHWndAttr::SIZE_maxsize)
		||0 == dm_wcsicmp(pszAttribute, DMAttr::DMHWndAttr::bool_bresize)
		||0 == dm_wcsicmp(pszAttribute, DMAttr::DMHWndAttr::bool_btranslucent)
		||0 == dm_wcsicmp(pszAttribute, DMAttr::DMHWndAttr::BYTE_alpha)
		||0 == dm_wcsicmp(pszAttribute, DMAttr::DMHWndAttr::INT_h)
		||0 == dm_wcsicmp(pszAttribute, DMAttr::DMHWndAttr::INT_s)
		||0 == dm_wcsicmp(pszAttribute, DMAttr::DMHWndAttr::INT_l)
		||0 == dm_wcsicmp(pszAttribute, DMAttr::DMHWndAttr::RECT_maxinset)
		||0 == dm_wcsicmp(pszAttribute, DMAttr::DMHWndAttr::STRING_title)
		||0 == dm_wcsicmp(pszAttribute, DMAttr::DMHWndAttr::STRING_regtip)
		||0 == dm_wcsicmp(pszAttribute, DMAttr::DMHWndAttr::STRING_regdraw)
		||0 == dm_wcsicmp(pszAttribute, DMAttr::DMHWndAttr::STRING_transid)
		||0 == dm_wcsicmp(pszAttribute, DMAttr::DMHWndAttr::SIZE_initsize)
		)
	{
		if (0 == dm_wcsicmp(pszAttribute, DMAttr::DMHWndAttr::SIZE_initsize))
		{
			CSize szInit;
			dm_parsesize(pszValue,szInit);
			CRect rcWnd(0,0,szInit.cx,szInit.cy);
			if (bLoadXml)
			{
				rcWnd.OffsetRect(m_pParent->m_rcWindow.TopLeft());
				rcWnd.OffsetRect(100,100);//�������Ͻ���ʾ��
			}
			else
			{
				rcWnd.OffsetRect(m_rcWindow.TopLeft());
			}

			DM_FloatLayout(rcWnd);
			m_pParent->HoverInSelOrAddMode(this);
			m_pParent->SelFrameInAllMode();
			m_pParent->DragFrameInSelMode();
			m_pParent->DM_Invalidate();
		}

		if (0 == dm_wcsicmp(pszAttribute, DMAttr::DMHWndAttr::BYTE_alpha))
		{// ����DUI��alpha��ģ��Res�������ڵ�alpha
			m_pDUIXmlInfo->m_pStyle->SetAttribute(DMAttr::DMHWndAttr::BYTE_alpha,pszValue,bLoadXml);
			if (!bLoadXml)
			{
				DM_Invalidate();
			}
		}

		iErr = DM_ECODE_OK;
	}
	return __super::OnAttributeFinished(pszAttribute,pszValue,bLoadXml,iErr);
}



