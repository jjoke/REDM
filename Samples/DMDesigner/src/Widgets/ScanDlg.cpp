#include "DMDesignerAfx.h"
#include "ScanDlg.h"

BEGIN_MSG_MAP(ScanDlg)    
	MSG_WM_SIZE(OnSize) 
	CHAIN_MSG_MAP(DMHDialog)
END_MSG_MAP() 
void ScanDlg::OnSize(UINT nType, CSize size)
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

DMCode ScanDlg::OnOK()
{
	DUITabCtrl *pTab = FindChildByNameT<DUITabCtrl>(L"ds_scantabctrl");
	int iCurSel = pTab->GetCurSel();
	if (0 == iCurSel)//0.��� ��ʼ��찴ť
	{
		pTab->SetCurSel(2);
		SetWindowPos(NULL,0,0,500,200,SWP_NOMOVE|SWP_NOACTIVATE|SWP_NOZORDER);  
		
		Scan();
		if (false == m_bExistErr)//1.��ʾ�޴���
		{
			pTab->SetCurSel(1);
			SetWindowPos(NULL,0,0,400,100,SWP_NOMOVE|SWP_NOACTIVATE|SWP_NOZORDER);  
		}
	}
	else if (2 == iCurSel)//2.��� �����޸���ť
	{
		Scan(true);
		pTab->SetCurSel(3);
	}
	else if (3 == iCurSel||1==iCurSel)// �˳�
	{
		EndDialog(IDOK); 
	}
	return DM_ECODE_OK;
}

DMCode ScanDlg::Scan(bool bRepair)
{
	m_bExistErr = false;
	DMCode iErr = DM_ECODE_FAIL;
	do 
	{
		ObjXml* pXml		 = g_pMainWnd->m_pDesignerXml;
		CStringW strResDir	 = pXml->m_strResDir;
		DMSmartPtrT<ResFolder>pRes = pXml->m_pRes;
		ProjTree* pProjTree  = g_pMainWnd->FindChildByNameT<ProjTree>(L"ds_projtree");
		DUIListBox* pListBox = FindChildByNameT<DUIListBox>(bRepair?L"ds_repairlist":L"ds_scanlist");
		pListBox->DeleteAll();

		DMXmlNodePtr pData = NULL;
		CStringW strPath,strErrText;
		//1.ɨ�貼���ļ��б��ж����ǵ�ID�Ƿ���Ч
		HDMTREEITEM hLayoutFiles = pXml->m_hProjLayoutFiles;
		HDMTREEITEM hGlobal		 = pXml->m_hProjGlobal;

		if (hGlobal)
		{
			pData		  = (DMXmlNodePtr) pProjTree->GetItemData(hGlobal);
			strPath		  = strResDir + pData->Attribute(XML_PATH);
			
			//1.1.0.�ж�global�ļ��Ƿ����
			if (!CheckFileExistW((wchar_t*)(const wchar_t*)strPath))
			{
				strErrText.Format(L"[global]�ļ�δ�ҵ�:%s",strPath);
				m_bExistErr = true;
				if (bRepair)
				{
					//1.1.1.�Ӹ�xml�ڵ��Ƴ�global�ڵ�
					HDMTREEITEM hParent = pProjTree->GetParentItem(hGlobal);
					DMXmlNodePtr pParentData = (DMXmlNodePtr) pProjTree->GetItemData(hParent);
					pParentData->RemoveChildNode(pData);

					//1.1.2.����xmlΪδ����״̬
					strPath = strResDir + XML_LAYOUT_DMINDEX;
					pXml->SetDocUnSave(strPath);

					//1.1.3.��Res�������а�global�Ƴ�
					pRes->RemoveResItem(XML_GLOBAL,pData->Attribute(XML_NAME),L"");
	
					strErrText += L"[���Ƴ�]";

					//1.1.4.��map���Ƴ�
					pXml->DMMapT<HDMTREEITEM,DMXmlNodePtr>::RemoveKey(hGlobal);

					//1.1.5.��tree���Ƴ���global��㣬����global��Ա������0
					pProjTree->RemoveItem(hGlobal);
					pXml->m_hProjGlobal = NULL;		
				}
				pListBox->AddString(strErrText);
			}
		}

		//1.2.0.�ж�layout�ļ��Ƿ����
		HDMTREEITEM hLayout = pProjTree->GetChildItem(hLayoutFiles,false);
		if (hLayout)
		{
			HDMTREEITEM hChild = pProjTree->GetChildItem(hLayout);
			while (hChild)
			{
				pData = (DMXmlNodePtr) pProjTree->GetItemData(hChild);
				HDMTREEITEM hTemp = pProjTree->GetNextSiblingItem(hChild);

				strPath = strResDir + pData->Attribute(XML_PATH);

				//1.2.0.�ж�layout�ļ��Ƿ����
				if (!CheckFileExistW((wchar_t*)(const wchar_t*)strPath))
				{
					strErrText.Format(L"[layout]�ļ�δ�ҵ�:%s",strPath);
					m_bExistErr = true;
					if (bRepair)
					{
						//1.2.1.�Ӹ�xml�ڵ��Ƴ�layout�ڵ�
						DMXmlNodePtr pParentData = (DMXmlNodePtr) pProjTree->GetItemData(hLayout);
						pParentData->RemoveChildNode(pData);

						//1.2.2.����xmlΪδ����״̬
						strPath = strResDir + XML_LAYOUT_DMINDEX;
						pXml->SetDocUnSave(strPath);

						//1.2.3.��Res�������а�layout�Ƴ�
						pRes->RemoveResItem(XML_LAYOUT,pData->Attribute(XML_NAME),L"");

						strErrText += L"[���Ƴ�]";

						//1.2.4.��map���Ƴ�
						pXml->DMMapT<HDMTREEITEM,DMXmlNodePtr>::RemoveKey(hChild);

						//1.2.5.��tree���Ƴ���layout���
						pProjTree->RemoveItem(hChild);
					}
					pListBox->AddString(strErrText);
				}

				hChild = hTemp;
			}
		}
		
		//2.ɨ��������б��е������б��ж����ǵ�dmindex.xml�Ƿ����
		HDMTREEITEM hThemes = pXml->m_hProjThemes;
		HDMTREEITEM hTheme = pProjTree->GetChildItem(hThemes);
		while (hTheme)
		{
			HDMTREEITEM hTemp = pProjTree->GetNextSiblingItem(hTheme);
			pData = (DMXmlNodePtr) pProjTree->GetItemData(hTheme);
			strPath = strResDir + pData->Attribute(XML_PATH);
			//2.1.ĳ�������dmindex.xml�����ڣ������ʧ��
			if (!pXml->FindDocData(strPath))
			{
				strErrText.Format(L"[theme]dmindex.xml����ʧ��:%s",strPath);
				m_bExistErr = true;
				if (bRepair)
				{
					//2.2.�Ӹ�xml�ڵ��Ƴ�theme�ڵ�
					DMXmlNodePtr pParentData = (DMXmlNodePtr) pProjTree->GetItemData(hThemes);
					pParentData->RemoveChildNode(pData);
					
					//2.3.����xmlΪδ����״̬
					strPath = strResDir + XML_THEMES_DMINDEX;
					pXml->SetDocUnSave(strPath);
					
					strErrText += L"[���Ƴ�]";

					//2.4.��map���Ƴ�
					pXml->DMMapT<HDMTREEITEM,DMXmlNodePtr>::RemoveKey(hTheme);

					// 2.5.��tree���Ƴ���theme���
					pProjTree->RemoveItem(hTheme);
				}
				pListBox->AddString(strErrText);
			}
			hTheme = hTemp;
		}

		//3.ɨ���������е��ļ��б��ж����ǵ�ID�Ƿ���Ч
		hTheme = pProjTree->GetChildItem(hThemes);
		while (hTheme)
		{
			HDMTREEITEM hType = pProjTree->GetChildItem(hTheme);
			while (hType)
			{
				HDMTREEITEM hFile = pProjTree->GetChildItem(hType);
				while (hFile)
				{
					HDMTREEITEM hTemp = pProjTree->GetNextSiblingItem(hFile);
					pData = (DMXmlNodePtr) pProjTree->GetItemData(hFile);
					strPath = strResDir + pData->Attribute(XML_PATH);
					//3.0.�ж�file�ļ��Ƿ����
					if (!CheckFileExistW((wchar_t*)(const wchar_t*)strPath))
					{
						strErrText.Format(L"[file]δ�ҵ�:%s",strPath);
						m_bExistErr = true;
						if (bRepair)
						{
							//3.1.�Ӹ�xml�ڵ��Ƴ�file�ڵ�
							DMXmlNodePtr pParentData = (DMXmlNodePtr) pProjTree->GetItemData(hType);
							pParentData->RemoveChildNode(pData);
							
							DMXmlNodePtr pThemeData = (DMXmlNodePtr) pProjTree->GetItemData(hTheme);
							//3.2.����xmlΪδ����״̬
							strPath = strResDir + pThemeData->Attribute(XML_PATH);
							pXml->SetDocUnSave(strPath);

							//3.3.��Res�������а�file�Ƴ�
							pRes->RemoveResItem(pParentData->GetName(),pData->Attribute(XML_NAME),pThemeData->Attribute(XML_NAME));

							strErrText += L"[���Ƴ�]";

							//3.4.��map���Ƴ�
							pXml->DMMapT<HDMTREEITEM,DMXmlNodePtr>::RemoveKey(hFile);

							//3.5.��tree���Ƴ���file���
							pProjTree->RemoveItem(hFile);
						}

						pListBox->AddString(strErrText);
					}

					hFile = hTemp;
				}
				hType = pProjTree->GetNextSiblingItem(hType);
			}

			hTheme = pProjTree->GetNextSiblingItem(hTheme);
		}

		//4.ɨ��ȫ��Ƥ���б��ж����ǵ�ID�Ƿ���Ч
		HDMTREEITEM hGlobalSkins = pXml->m_hProjGlobalSkins;
		if (hGlobalSkins)
		{
			HDMTREEITEM hGlobalSkin = pProjTree->GetChildItem(hGlobalSkins);
			while (hGlobalSkin)
			{
				HDMTREEITEM hGlobalSkinId = pProjTree->GetChildItem(hGlobalSkin);
				while (hGlobalSkinId)
				{
					HDMTREEITEM hTemp = pProjTree->GetNextSiblingItem(hGlobalSkinId);

					//4.1.ȡ��Ƥ��id
					pData = (DMXmlNodePtr) pProjTree->GetItemData(hGlobalSkinId);
					CStringW strSrc = pData->Attribute(XML_SRC);
					CStringWList strList;
					CStringW strName;
					CStringW strKey;
					int nCount = (int)SplitStringT(strSrc,L':',strList);
					if (1==nCount)
					{
						strKey  = L"PNG";
						strName = strSrc;
					}
					else if (2 == nCount)
					{
						strKey  = strList[0];
						strName = strList[1];
					}
					//4.2.��Res��������ѭ�����Ҵ�id�Ƿ����
					if (!DMSUCCEEDED(pXml->m_pRes->IsItemExists(strKey,strName)))//ѭ������
					{
						strErrText.Format(L"[global-skins]id:%s-src:%sδ�ҵ���ӦƤ��",pData->Attribute(XML_ID),strSrc);
						m_bExistErr = true;
						if (bRepair)
						{
							//4.3.�Ӹ�xml�ڵ��Ƴ�Ƥ�����
							DMXmlNodePtr pParentData = (DMXmlNodePtr) pProjTree->GetItemData(hGlobalSkin);
							pParentData->RemoveChildNode(pData);

							//4.4.����xmlΪδ����״̬
							DMXmlNodePtr pGlobal = (DMXmlNodePtr) pProjTree->GetItemData(pXml->m_hProjGlobal);
							strPath = strResDir + pGlobal->Attribute(XML_PATH);
							pXml->SetDocUnSave(strPath);
							// ��ΪRes�����ڣ����Բ���Ҫ�Ƴ�Res
							
							strErrText += L"[���Ƴ�]";
							//4.5.��map���Ƴ�
							pXml->DMMapT<HDMTREEITEM,DMXmlNodePtr>::RemoveKey(hGlobalSkinId);

							//4.6.��tree���Ƴ���skin���
							pProjTree->RemoveItem(hGlobalSkinId);
						}

						pListBox->AddString(strErrText);
					}

					hGlobalSkinId = hTemp;
				}
				hGlobalSkin = pProjTree->GetNextSiblingItem(hGlobalSkin);
			}
		}

		//5.ɨ��˽��Ƥ���б��ж����ǵ�ID�Ƿ���Ч
		HDMTREEITEM hPrivStyleSkins = pXml->m_hProjPrivStyleSkins;
		if (hPrivStyleSkins)
		{
			HDMTREEITEM hDM = pProjTree->GetChildItem(hPrivStyleSkins);
			while (hDM)
			{
				HDMTREEITEM hPrivSkins = pProjTree->GetChildItem(hDM,false);// ���һ����skin
				if (hPrivSkins)
				{
					HDMTREEITEM hPrivSkin = pProjTree->GetChildItem(hPrivSkins);
					while (hPrivSkin)
					{
						HDMTREEITEM hPrivSkinId = pProjTree->GetChildItem(hPrivSkin);
						while (hPrivSkinId)
						{
							HDMTREEITEM hTemp = pProjTree->GetNextSiblingItem(hPrivSkinId);
							pData = (DMXmlNodePtr) pProjTree->GetItemData(hPrivSkinId);
							CStringW strSrc = pData->Attribute(XML_SRC);
							CStringWList strList;
							CStringW strName;
							CStringW strKey;
							int nCount = (int)SplitStringT(strSrc,L':',strList);
							if (1==nCount)
							{
								strKey = L"PNG";
								strName = strSrc;
							}
							else if (2 == nCount)
							{
								strKey = strList[0];
								strName  = strList[1];
							}
							if (!DMSUCCEEDED(pXml->m_pRes->IsItemExists(strKey,strName)))//ѭ������
							{
								strErrText.Format(L"[private-skins]id:%s-src:%sδ�ҵ���ӦƤ��",pData->Attribute(XML_ID),strSrc);
								m_bExistErr = true;
								if (bRepair)
								{
									DMXmlNodePtr pParentData = (DMXmlNodePtr) pProjTree->GetItemData(hPrivSkin);
									pParentData->RemoveChildNode(pData);

									DMXmlNodePtr pDM = (DMXmlNodePtr) pProjTree->GetItemData(hDM);
									strPath = strResDir + pDM->Attribute(XML_PATH);
									pXml->SetDocUnSave(strPath);
									// ��ΪRes�����ڣ����Բ���Ҫ�Ƴ�Res

									strErrText += L"[���Ƴ�]";
									pXml->DMMapT<HDMTREEITEM,DMXmlNodePtr>::RemoveKey(hPrivSkinId);
									pProjTree->RemoveItem(hPrivSkinId);

								}
								pListBox->AddString(strErrText);
							}

							hPrivSkinId = hTemp;
						}

						hPrivSkin = pProjTree->GetNextSiblingItem(hPrivSkin);
					}
				}

				hDM = pProjTree->GetNextSiblingItem(hDM);
			}
		}
		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}
