#include "DMDesignerAfx.h"
#include "ThemeDlg.h"

BEGIN_MSG_MAP(ThemeDlg)
	MSG_WM_INITDIALOG(OnInitDialog) 
	MSG_WM_SIZE(OnSize)
	CHAIN_MSG_MAP(DMHDialog)
END_MSG_MAP()
BEGIN_EVENT_MAP(ThemeDlg)
END_EVENT_MAP()
ThemeDlg::ThemeDlg(bool bEditMode,CStringW strThemeName,CStringW strDir)
{
	m_bEditMode = bEditMode;
	m_strThemeName = strThemeName;
	m_strDir = strDir;
}

BOOL ThemeDlg::OnInitDialog(HWND wndFocus, LPARAM lInitParam)
{
	DUIStatic* pTitle = FindChildByNameT<DUIStatic>(L"ds_title");
	CStringW strTitle;
	if (false == m_bEditMode)
	{
		strTitle = L"����";
	}
	else
	{
		strTitle = L"�༭";
	}

	strTitle += L"�����";
	pTitle->DV_SetWindowText(strTitle);

	DUIEdit* pThemeNameEdit = FindChildByNameT<DUIEdit>(L"ds_themename");
	if (m_bEditMode)
	{
		pThemeNameEdit->SetWindowText(m_strThemeName);

		DUIEdit* pDirNameEdit = FindChildByNameT<DUIEdit>(L"ds_dirname");
		pDirNameEdit->SetWindowText(m_strDir);
		pDirNameEdit->SetReadOnly(true);
	}
	pThemeNameEdit->DV_SetFocusWnd();

	return TRUE;
}

void ThemeDlg::OnSize(UINT nType, CSize size)
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

DMCode ThemeDlg::OnOK()
{
	DMCode iErr = DM_ECODE_FAIL;
	HDMTREEITEM hAdd = NULL;
	do 
	{
		//1.���������������ļ������Ƿ�Ϊ��
		ObjXml* pXml = g_pMainWnd->m_pDesignerXml;
		ProjTree* pProjTree  = g_pMainWnd->FindChildByNameT<ProjTree>(L"ds_projtree");
		if (NULL == pXml||NULL == pProjTree)
		{
			break;
		}
		DUIEdit* pThemeNameEdit = FindChildByNameT<DUIEdit>(L"ds_themename");
		DUIEdit* pDirNameEdit = FindChildByNameT<DUIEdit>(L"ds_dirname");
		CStringW strThemeName = pThemeNameEdit->GetWindowText();
		CStringW strDir		  = pDirNameEdit->GetWindowText();

		if (strThemeName.IsEmpty())
		{
			DM_MessageBox(L"��������ֲ���Ϊ��",MB_OK,L"Error",m_hWnd);
			pThemeNameEdit->DV_SetFocusWnd();
			break;
		}

		if (strDir.IsEmpty())
		{
			DM_MessageBox(L"������ļ���������Ϊ��",MB_OK,L"Error",m_hWnd);
			pDirNameEdit->DV_SetFocusWnd();
			break;
		}
		// �༭ģʽ ------------------------------
		if (m_bEditMode)
		{
			DMXmlNodePtr pNode = (DMXmlNodePtr)pProjTree->GetItemData(pXml->m_hProjSel);
			if (m_strThemeName != strThemeName)
			{
				//2.�ж�������������Ƿ��ѱ����������ʹ��
				bool bFind = false;
				HDMTREEITEM hParentItem = pProjTree->GetParentItem(pXml->m_hProjSel);
				if (hParentItem)
				{
					HDMTREEITEM hChildItem = pProjTree->GetChildItem(hParentItem);
					while (hChildItem)
					{
						if (hChildItem != pXml->m_hProjSel)
						{// �����༭����
							DMXmlNodePtr pChildNode = (DMXmlNodePtr)pProjTree->GetItemData(hChildItem);
							if (0 == strThemeName.CompareNoCase(pChildNode->Attribute(XML_NAME)))
							{
								bFind = true;
								break;
							}
						}
						hChildItem = pProjTree->GetNextSiblingItem(hChildItem);
					}
				}
				if (bFind)
				{
					DM_MessageBox(L"����������ѱ�ռ��",MB_OK,L"MSG",m_hWnd);
					pThemeNameEdit->DV_SetFocusWnd();
					break;
				}


				//3. ����xml���
				pNode->SetAttribute(XML_NAME,strThemeName);
				//4. �ж��Ƿ�ΪĬ�������,�����,�͸��¸��ڵ��name����
				DMXmlNodePtr pParentNode = (DMXmlNodePtr)pProjTree->GetItemData(pXml->m_hProjThemes);
				CStringW strDefThemeName = pParentNode->Attribute(XML_NAME);
				if (0 == strDefThemeName.CompareNoCase(m_strThemeName))
				{
					pParentNode->SetAttribute(XML_NAME,strThemeName);
				} 

				//5. ����tree�����ʾ
				DM::LPTVITEMEX pData = pProjTree->GetItem(pXml->m_hProjSel);
				pData->pPanel->m_pDUIXmlInfo->m_strText = strThemeName;
				pProjTree->UpdateItemRect(pXml->m_hProjSel);

				CStringW strPath = pXml->m_strResDir;
				strPath += XML_THEMES_DMINDEX;
				//6. ��themes xml����Ϊδ����״̬
				pXml->SetDocUnSave(strPath);
			}
			
			EndDialog(IDOK);
			break;
		}

		// �½�ģʽ ------------------------------
		//2.�ж�������ļ��л��������Ƿ��ѱ����������ʹ��
		bool bFind = false;
		HDMTREEITEM hThemes = pXml->m_hProjThemes;
		HDMTREEITEM hChild = pProjTree->GetChildItem(hThemes);
		while (hChild)
		{
			DMXmlNodePtr pChildNode = (DMXmlNodePtr)pProjTree->GetItemData(hChild);
			CStringW strOtherThemeName = pChildNode->Attribute(XML_NAME);
			if (0 == strOtherThemeName.CompareNoCase(strThemeName))
			{
				DM_MessageBox(L"����������ѱ�ռ��",MB_OK,L"MSG",m_hWnd);
				pThemeNameEdit->DV_SetFocusWnd();
				bFind = true;
				break;
			}

			CStringW strOtherDir = pChildNode->Attribute(XML_PATH);
			strOtherDir = strOtherDir.Left(strOtherDir.ReverseFind(L'\\'));
			strOtherDir = strOtherDir.Right(strOtherDir.GetLength()-strOtherDir.ReverseFind(L'\\')-1);
			if (0 == strOtherDir.CompareNoCase(strDir))
			{
				CStringW strInfo;
				strInfo.Format(L"�ļ����ѱ�[%s]-�����ʹ��",strOtherThemeName);
				DM_MessageBox(strInfo,MB_OK,L"MSG",m_hWnd);
				pDirNameEdit->DV_SetFocusWnd();
				bFind = true;
				break;
			}

			hChild = pProjTree->GetNextSiblingItem(hChild);
		}
		if (true == bFind)
		{
			break;
		}

		//3. ����������ļ���
		CStringW strPath = pXml->m_strResDir + XML_THEMES;
		strPath += L"\\";
		strPath += strDir;
		if (0 == CreateDirectoryW(strPath,NULL)&&ERROR_ALREADY_EXISTS != GetLastError())
		{
			DM_MessageBox(L"�����ļ���ʧ��",MB_OK,L"MSG",m_hWnd);
			break;
		}

		//4. ���������dmindex.xml�ļ�
		DMXmlDocument Doc;
		DMXmlNode XmlNode = Doc.Base();
		XmlNode = XmlNode.InsertChildNode(L"resource");
		strPath += L"\\dmindex.xml";
		if (!Doc.SaveXml(strPath))
		{
			DM_MessageBox(L"����dmindex.xmlʧ��",MB_OK,L"MSG",m_hWnd);
			break;
		}
		DocDataPtr pDoc = new DocData(strPath);
		if (!pDoc->IsValid())
		{
			DM_MessageBox(L"����dmindex.xmlʧ��",MB_OK,L"MSG",m_hWnd);
			DM_DELETE(pDoc);
			break;
		}
		pXml->AddObj(pDoc);

		//5. themes��Ӧxml����theme node
		DMXmlNodePtr pNode = (DMXmlNodePtr)pProjTree->GetItemData(hThemes); 
		DMXmlNode XmlFile  = pNode->InsertChildNode(XML_FILE);
		XmlFile.SetAttribute(XML_NAME,strThemeName);
		CStringW strRelative = XML_THEMES;
		strRelative += L"\\";
		strRelative += strDir;
		strRelative += L"\\dmindex.xml";
		XmlFile.SetAttribute(XML_PATH,strRelative);
		Init_Debug_XmlBuf(*pNode);

		//6. ����tree,�����԰�
		DMXmlDocument doc;
		DMXmlNode DataNode = doc.Base();
		pXml->InitProjTreeNode(DataNode,true);
		hAdd = pXml->InsertProjTreeItem(DataNode,strThemeName,hThemes);
		pXml->BindProjTreeData(XmlFile,hAdd);

		strPath = pXml->m_strResDir;
		strPath += XML_THEMES_DMINDEX;
		//7. ��themes��dmindex.xml����Ϊδ����
		pXml->SetDocUnSave(strPath);

		//8.Res����������һ���������
		ResFolderItemPtr pItem = new ResFolderItem;
		pItem->m_strThemeName = strThemeName;
		pXml->m_pRes->AddObj(pItem);
		
		EndDialog(IDOK);
		if (hAdd)
		{
			pProjTree->SelectItem(hAdd);
		}
		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}

