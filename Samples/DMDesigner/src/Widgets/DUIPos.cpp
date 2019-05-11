#include "DMDesignerAfx.h"
#include "DUIPos.h"

namespace DM
{
	#define  POSITEM_DELTA           4
	CStringW g_Tips[] = \
	{// ��PIT����һ��
		L"��������(��)Ϊ�ο���,����������Ϊ�ο���\n������(��)��,������(��)��\n����:-10��ʾ����(��)����(��)��10������", //0 
		L"�ο�����������\n������(��)��,������(��)��\n����:|-10��ʾ�Ը�����������(��)��10������",						   //1 
		L"���ø����ڵİٷֱ�\n���ű�����\n������(��)��,������(��)��\n����:%10��ʾ�����ڵ���(��)������(�£�ƫ��10%��λ��",//2
		L"�ο�ǰһ���ֵܴ������Լ����ı�\n������(��)��,������(��)��\n����:[10��ʾǰһ���ֵܴ������Լ����ı���(��)��10������",//3 
		L"�ο���һ���ֵܴ������Լ����ı�\n������(��)��,������(��)��\n����:]-10��ʾ��һ���ֵܴ������Լ����ı���(��)��10������",//4
		L"�ο�ǰһ���ֵܴ������Լ�Զ�ı�\n������(��)��,������(��)��\n����:[10��ʾǰһ���ֵܴ������Լ�Զ�ı���(��)��10������",//5
		L"�ο���һ���ֵܴ������Լ�Զ�ı�\n������(��)��,������(��)��\n����:]-10��ʾ��һ���ֵܴ������Լ�Զ�ı���(��)��10������",//6 
		L"��pos�����ж��崰�ڵ�size\n������(��)��,������(��)��\n����:@100��ʾ��(��)100����",//7 
	};

	CRect PosList::GetItemRect(int iItem)
	{
		CRect rcDest;
		do 
		{
			if (iItem<0
				||iItem>=(int)GetCount())
			{
				break;
			}

			CRect rcClient;
			DV_GetClientRect(&rcClient);
			int nPos = 0;
			for (int i = 0; i < iItem; i++)
			{
				nPos += m_DMArray[i]->nHeight;
			}
			rcDest.SetRect(0,nPos,rcClient.Width(), m_DMArray[iItem]->nHeight+nPos);
			rcDest.OffsetRect(rcClient.TopLeft()-m_ptCurPos);
		} while (false);
		return rcDest;
	}

	DMCode PosList::DV_OnUpdateToolTip(CPoint pt, DMToolTipInfo &tipInfo)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			if (-1!=m_iHoverItem && m_pContainer)
			{
				tipInfo.hDUIWnd    = m_hDUIWnd;
				tipInfo.rcTarget   = GetItemRect(m_iHoverItem);
				tipInfo.strTip    = g_Tips[m_iHoverItem];
				tipInfo.strXmlId  = m_pDUIXmlInfo->m_strTipsXmlId;
				tipInfo.iDelayTime = m_pDUIXmlInfo->m_iTooltipDelayTime;
				tipInfo.iSpanTime  = m_pDUIXmlInfo->m_iTooltipSpanTime;
				tipInfo.rcPosFlags = m_pDUIXmlInfo->m_rcTooltipPosFlags;
				tipInfo.rcScreenTarget = tipInfo.rcTarget;
				m_pContainer->OnClientToScreen(tipInfo.rcScreenTarget);
				iErr = DM_ECODE_OK;
			}
		} while (false);
		return iErr;
	}

	// PosEdit-----------------------------------------------------
	void PosEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		if (0 == isdigit(nChar)&&nChar!='-')
		{
			if (0 == GetWindowTextLength())
			{// ������һλ�ַ�
				SetWindowText(L"0");
				SetSel(MAKELONG(-1,-1));
			}
			return;
		}
		__super::OnChar(nChar,nRepCnt,nFlags);
	}

	LRESULT PosEdit::OnImeChar(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		DM_MessageBox(L"��Ҫʹ�����뷨����!,���л���Ӣ��ģʽ");
		return 0;
	}

	BOOL PosEdit::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
	{
		CStringW strValue = GetWindowText();
		int iValue = StringToInt(strValue);
		bool bInit = false;
		if (0 == iValue)
		{
			if (strValue.Left(1) == L"-" && zDelta>0)// ԭ����-0
			{
				strValue = L"0";
				bInit = true;
			}
			else if(strValue.Left(1) != L"-" && zDelta<0)// ԭ����0
			{
				strValue = L"-0";
				bInit = true;
			}
		}
		if (false == bInit)
		{
			iValue += (zDelta>0?1:-1);
			strValue.Format(L"%d",iValue);
		}
		SetWindowText(strValue);
		SetSel(MAKELONG(-1,-1));
		return TRUE;
	} 

	//PosItem---------------------------------------------------------------
	PosItem::PosItem()
	{
		m_pItem = NULL;
	}

	DMCode PosItem::InitPosItem(POS_ITEM* pItem,Layout* pLayout)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			if (NULL == pItem||NULL == pLayout)
			{
				break;
			}
		
			m_pItem   = pItem;
			m_pLayout = pLayout;
			m_pCbx->GetListBox()->m_EventMgr.SetMuted(true);// �����л�ʱ����Ӱ����Ϣ
			m_pEdit->m_EventMgr.SetMuted(true);
			
			m_pCbx->SetCurSel(m_pItem->pit);
			CStringW strValue = IntToString(DMABS((int)m_pItem->nPos));
			if (m_pItem->bMinus)// ֧��-0
			{
				strValue = strValue.Format(L"-%s",strValue);
			}
			m_pEdit->SetWindowText(strValue);
			m_pCbx->GetListBox()->m_EventMgr.SetMuted(false);
			m_pEdit->m_EventMgr.SetMuted(false);// �����л�ʱ����Ӱ����Ϣ

			iErr = DM_ECODE_OK;
		} while (false);
		return iErr;
	}

	DMCode PosItem::UnInitPosItem()
	{
		m_pItem = NULL;
		m_pLayout = NULL;
		m_pCbx->GetListBox()->m_EventMgr.SetMuted(true);// �����л�ʱ����Ӱ����Ϣ
		m_pEdit->m_EventMgr.SetMuted(true);
		m_pCbx->SetCurSel(0);
		m_pEdit->SetWindowText(L"0");
		m_pCbx->GetListBox()->m_EventMgr.SetMuted(false);
		m_pEdit->m_EventMgr.SetMuted(false);// �����л�ʱ����Ӱ����Ϣ
		return DM_ECODE_OK;
	}

	DMCode PosItem::OnSelChange(DMEventArgs *pEvt)
	{
		DMEventLBSelChangedArgs* pEvent = (DMEventLBSelChangedArgs*)pEvt;
		if (-1!=pEvent->m_nNewSel)
		{
			m_pCbx->SetAttribute(DMAttr::DUIWindowAttr::STRING_tiptext,g_Tips[pEvent->m_nNewSel]);// ����tips
			OnItemChange();
		}
		return DM_ECODE_OK;
	}

	DMCode PosItem::OnEditChange(DMEventArgs *pEvt)
	{
		DMEventRENotifyArgs *pEvent = (DMEventRENotifyArgs*)(pEvt);
		if (EN_CHANGE == pEvent->m_iNotify)
		{
			OnItemChange();
		}
		return DM_ECODE_OK;
	}

	DMCode PosItem::OnItemChange(POS_ITEM* pItem)
	{
		if (NULL == m_pLayout||NULL == m_pItem)
		{
			return DM_ECODE_FAIL;
		}

		// 1.��ʱ����
		POS_ITEM Pos_Copy;
		memcpy(&Pos_Copy,m_pItem,sizeof(POS_ITEM));
		if (!pItem)// ��NULL��ʾʹ��UI��ʼ��,pItemָ��m_pItem����,��ΪNULL��ʾΪdragframe����
		{
			m_pItem->pit		= (PIT)m_pCbx->GetCurSel();
			CStringW strValue   = m_pEdit->GetWindowText();
			int iValue			= StringToInt(strValue);
			m_pItem->bMinus		= (strValue.Left(1) == L"-");// ֧��-0
			m_pItem->nPos		= (float)DMABS(iValue);
			pItem               = m_pItem;
		}

		if (pItem->pit != Pos_Copy.pit// �����
			||pItem->nPos != Pos_Copy.nPos
			||(PIT_PERCENT!=pItem->pit&&PIT_OFFSET!=pItem->pit&&pItem->bMinus != Pos_Copy.bMinus))//%��@ʱ����-��
		{
			if (pItem != m_pItem)//��ΪNULL��ʾΪdragframe����
			{
				memcpy(m_pItem,pItem,sizeof(POS_ITEM));
			}
			
			if (m_pLayout->m_pOwner && m_pLayout->m_pOwner->m_Node.m_pParent)
			{
				//2.����Pos
				if (DMSUCCEEDED(m_pLayout->m_pOwner->m_Node.m_pParent->DV_UpdateChildLayout()))
				{
					g_pMainWnd->m_pDesignerXml->m_pObjEditor->DragFrameInSelMode();
					//3.����xml
					CStringW strPos = m_pLayout->GetPosString();
					ObjTreeDataPtr pData = (ObjTreeDataPtr)g_pMainWnd->m_pDesignerXml->m_pObjTree->GetItemData(g_pMainWnd->m_pDesignerXml->m_hObjSel);
					if (pData)
					{
						pData->m_pXmlNode->SetAttribute(XML_POS,strPos);
						pData->m_pDoc->m_bChange = (0 != strPos.CompareNoCase(m_pLayout->m_strPosValue));// �仯���ֺ�ԭʼ������ͬ��������Ϊδ�仯״̬
					}
					if (pItem != m_pItem)
					{
						InitPosItem(m_pItem,m_pLayout);// ����ֱ�Ӵ�pItem��m_pItem����Ҫ��Layout����
					}	
				}
				else
				{
					DM_MessageBox(L"��������ʧ��,���ع�����");
					memcpy(m_pItem,&Pos_Copy,sizeof(POS_ITEM));
					if (pItem == m_pItem)// ��NULL��ʾʹ��UI��ʼ��
					{
						InitPosItem(m_pItem,m_pLayout);
					}
				}
			}
		}
		return DM_ECODE_OK;
	}

	void PosItem::OnSize(UINT nType, CSize size)
	{
		__super::OnSize(nType,size);
		if (m_pEdit&&m_pCbx)
		{
			m_pCbx->SetAttribute(XML_POS,L"0,0,@15,-0",false);
			m_pEdit->SetAttribute(XML_POS,L"[2,0,-0,-0");
		}
	} 

	DMCode PosItem::DV_CreateChildWnds(DMXmlNode &XmlNode)
	{
		DMCode iErr = __super::DV_CreateChildWnds(XmlNode);

		// ����һ��combox+edit
		CStringW strWXml = L"<combobox clslistbox=\"poslist\" clrtextdisable=\"pbgra(c0,c0,c0,ff)\" clrtext=\"pbgra(F0,F0,F0,FF)\"  clrbg=\"pbgra(00,00,00,ff)\" textoffset=\"5\" bhideedit=\"1\" bfocusable=\"0\" dropheight=\"200\">"\
			L"<subedit clrtext=\"pbgra(F0,F0,F0,FF)\" font=\"face:������,size:14,weight:100\" />"\
			L"<sublistbox textpoint=\"5,-1\" clrbg=\"pbgra(00,00,00,ff)\" clritemtext=\"pbgra(F0,F0,F0,FF)\" bhottrack=\"1\" clritemselbg=\"pbgra(bd,bd,bd,ff)\" clritemseltext=\"pbgra(33,33,33,ff)\"/>"\
			L"</combobox>";

		CStringA strXml = DMW2A(strWXml,CP_UTF8);
		DMXmlDocument *pDoc = new DMXmlDocument;;
		pDoc->LoadFromBuffer((const PVOID)(LPCSTR)strXml, strXml.GetLength());
		DMXmlNode EditNode = pDoc->Root();

		g_pDMApp->CreateRegObj((void**)&m_pCbx, DUINAME_ComboxBox,DMREG_Window);
		DM_InsertChild(m_pCbx);
		m_pCbx->InitDMData(EditNode);
		m_pCbx->GetListBox()->m_EventMgr.SubscribeEvent(DMEventLBSelChangedArgs::EventID,Subscriber(&PosItem::OnSelChange, this));

		strWXml = L"<posedit clrtext=\"pbgra(ff,ff,ff,ff)\" bnumber=\"1\" clrtextdisable=\"pbgra(c0,c0,c0,ff)\" clrcaret=\"pbgra(ff,ff,ff,ff)\" bautosel=\"1\"/>";
		strXml = DMW2A(strWXml,CP_UTF8);
		DM_DELETE(pDoc);
		pDoc = new DMXmlDocument;
		pDoc->LoadFromBuffer((const PVOID)(LPCSTR)strXml, strXml.GetLength());
		EditNode = pDoc->Root();

		g_pDMApp->CreateRegObj((void**)&m_pEdit, L"posedit",DMREG_Window);
		DM_InsertChild(m_pEdit);
		m_pEdit->InitDMData(EditNode);
		m_pEdit->SetEventMask(ENM_CHANGE|m_pEdit->GetEventMask());
		m_pEdit->m_EventMgr.SubscribeEvent(DMEventRENotifyArgs::EventID,Subscriber(&PosItem::OnEditChange, this));

		DM_DELETE(pDoc);

		return iErr;
	}

	//DUIPos---------------------------------------------------------------
	DMCode DUIPos::InitLayout(IDMLayout* pLayout)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			if (NULL == pLayout)
			{
				break;
			}
			InitItem();
	
			m_pLayout = dynamic_cast<Layout*>(pLayout);
			//1.�������ĸ��߿���
			m_pItem[0]->InitPosItem(&m_pLayout->m_Left,m_pLayout);
			m_pItem[1]->InitPosItem(&m_pLayout->m_Top,m_pLayout);
			m_pItem[2]->InitPosItem(&m_pLayout->m_Right,m_pLayout);
			m_pItem[3]->InitPosItem(&m_pLayout->m_Bottom,m_pLayout);
			
			iErr = DM_ECODE_OK;
		} while (false);
		return iErr;
	}

	DMCode DUIPos::UnInitLayout()
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			if (m_pItem[0].isNull())
			{
				break;
			}
			for (int i=0; i<4; i++)
			{
				m_pItem[i]->UnInitPosItem();
			}
			iErr = DM_ECODE_OK;
		} while (false);
		return iErr;
	}

	void DUIPos::DM_OnPaint(IDMCanvas* pCanvas)
	{
		do 
		{
			if (m_pItem[0].isNull())
			{
				break;
			}

			CRect rcClient;
			DV_GetClientRect(rcClient);
			int iEditWid = (rcClient.Width()-POSITEM_DELTA*3)/4;
			if (iEditWid<=0)
			{
				break;
			}
			CRect rcStep = rcClient;
			rcStep.left += iEditWid+1;
			rcStep.right = rcStep.left + 1;
			for (int i=0;i<3;i++)
			{
				CRect rcDot = rcStep;
				rcDot.top += (rcStep.Height()-2)/2;
				rcDot.bottom = rcDot.top+1;
				pCanvas->FillSolidRect(rcDot,PBGRA(0xff,0xff,0xff,0xff));
				rcStep.OffsetRect(iEditWid+POSITEM_DELTA,0);
			}
		} while (false);
	} 

	void DUIPos::OnSize(UINT nType, CSize size)
	{
		do 
		{ 
			__super::OnSize(nType,size);
			if (m_pItem[0].isNull())
			{
				break;
			}
			CRect rcClient;
			DV_GetClientRect(rcClient);
			int iItemWid = (rcClient.Width()-POSITEM_DELTA*3)/4;
			if (iItemWid<=0)
			{
				break;
			}   
			CStringW strAttr;
			int iLeft = 0;
			for (int i=0;i<4;i++)
			{
				strAttr.Format(L"%d,0,@%d,-0",iLeft,iItemWid);
				m_pItem[i]->SetAttribute(XML_POS,strAttr,false);
				iLeft += iItemWid;
				iLeft += POSITEM_DELTA;
			}
		} while (false);
	}
	
	void DUIPos::InitItem()
	{
		do 
		{
			if (m_pItem[0].isNull())
			{
				break;
			}
			for (int i=0;i<4;i++)
			{
				if (m_pItem[i]->m_pCbx&&0 == m_pItem[i]->m_pCbx->m_pListBox->GetCount())
				{// ��һ�γ�ʼ��POSFLAG,��PIT����һ��
					CStringW 
						strAdd = POSFLAG_NULL;			m_pItem[i]->m_pCbx->m_pListBox->AddString(strAdd);
					strAdd = POSFLAG_REFCENTER;		m_pItem[i]->m_pCbx->m_pListBox->AddString(strAdd);
					strAdd = POSFLAG_PERCENT;		m_pItem[i]->m_pCbx->m_pListBox->AddString(strAdd);
					strAdd = POSFLAG_REFPREV_NEAR;	m_pItem[i]->m_pCbx->m_pListBox->AddString(strAdd);
					strAdd = POSFLAG_REFNEXT_NEAR;	m_pItem[i]->m_pCbx->m_pListBox->AddString(strAdd);
					strAdd = POSFLAG_REFPREV_FAR;	m_pItem[i]->m_pCbx->m_pListBox->AddString(strAdd);
					strAdd = POSFLAG_REFNEXT_FAR;	m_pItem[i]->m_pCbx->m_pListBox->AddString(strAdd);
					if (i>1)
					{
						strAdd = POSFLAG_DEFSIZE;m_pItem[i]->m_pCbx->m_pListBox->AddString(strAdd);
					}
					m_pItem[i]->m_pCbx->GetListBox()->m_EventMgr.SetMuted(true);
					m_pItem[i]->m_pCbx->SetCurSel(0);
					m_pItem[i]->m_pCbx->GetListBox()->m_EventMgr.SetMuted(false);
				}
			}
		} while (false);
	}

	DMCode DUIPos::DV_CreateChildWnds(DMXmlNode &XmlNode)
	{
		DMCode iErr = __super::DV_CreateChildWnds(XmlNode);
		CStringW strWXml = L"<positem skin=\"ds_attreditframe\" />";
		CStringA strXml = DMW2A(strWXml,CP_UTF8);
		DMXmlDocument doc;
		doc.LoadFromBuffer((const PVOID)(LPCSTR)strXml, strXml.GetLength());
		DMXmlNode ItemNode = doc.Root();
		for (int i=0;i<4;i++)
		{
			g_pDMApp->CreateRegObj((void**)&m_pItem[i], L"positem",DMREG_Window);
			if (m_pItem[i])
			{
				DM_InsertChild(m_pItem[i]);
				m_pItem[i]->AddRef();
				m_pItem[i]->InitDMData(ItemNode);
			}
		}
		return iErr;
	}
}