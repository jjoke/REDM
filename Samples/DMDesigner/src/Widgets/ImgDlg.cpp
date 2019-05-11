#include "DMDesignerAfx.h"
#include "ImgDlg.h"

BEGIN_MSG_MAP(ImgDlg)   
	MSG_WM_INITDIALOG(OnInitDialog) 
	MSG_WM_SIZE(OnSize) 
	MSG_WM_DROPFILES(OnDropFiles)
	CHAIN_MSG_MAP(DMHDialog)
END_MSG_MAP() 
BEGIN_EVENT_MAP(ImgDlg)
	EVENT_NAME_HANDLER(L"ds_img_bmult",DMEVT_CHECKCHANGING,OnCheckChange)
	EVENT_NAME_HANDLER(L"ds_img_bvert",DMEVT_CHECKCHANGING,OnCheckChange)
	EVENT_NAME_HANDLER(L"ds_img_name",DMEVT_RENOTIFY,OnEditChange)
	EVENT_NAME_HANDLER(L"ds_img_dir",DMEVT_RENOTIFY,OnEditChange)
	EVENT_NAME_HANDLER(L"ds_img_filename",DMEVT_RENOTIFY,OnEditChange)
	EVENT_NAME_HANDLER(L"ds_img_fileafx",DMEVT_RENOTIFY,OnEditChange)
	EVENT_NAME_COMMAND(L"ds_img_save",OnSaveBtn)
	EVENT_NAME_COMMAND(L"ds_img_clean",OnClearBtn)
	EVENT_NAME_COMMAND(L"ds_img_opendir",OnOpenDir)
END_EVENT_MAP()
ImgDlg*  ImgDlg::ms_pthis = NULL;
ImgDlg::ImgDlg(bool bEditMode)
{
	m_bEditMode = bEditMode;
	ms_pthis	= this;
	m_pTitle = m_pImgPath = NULL;
	m_pSave = m_pClean = NULL;
	m_pImgEditor = NULL;
	m_pImgName = m_pImgDir = m_pImgFileName = m_pImgFileAfx = NULL;
	m_pXml = NULL;
}
 
BOOL ImgDlg::OnInitDialog(HWND wndFocus, LPARAM lInitParam)
{
	DragAcceptFiles(TRUE);

	//1.���±���
	m_pTitle = FindChildByNameT<DUIStatic>(L"ds_title");
	m_strTitle = m_bEditMode?L"[�༭IMG]":L"[�¼�IMG]";
	m_pTitle->DV_SetWindowText(m_strTitle);

	// 2.��ʼ���ؼ�����
	m_pImgPath = FindChildByNameT<DUIStatic>(L"ds_img_path");
	ObjXml* pXml = g_pMainWnd->m_pDesignerXml;
	ProjTree* pProjTree  = g_pMainWnd->FindChildByNameT<ProjTree>(L"ds_projtree");
	m_pImgEditor = FindChildByNameT<DUImgEditor>(L"ds_img_editor");DMASSERT(m_pImgEditor);
	m_pbMultImg  = FindChildByNameT<DUICheckBox>(L"ds_img_bmult");DMASSERT(m_pbMultImg);
	m_pbVert     = FindChildByNameT<DUICheckBox>(L"ds_img_bvert");DMASSERT(m_pbVert);
	m_pSave      = FindChildByNameT<DUIButton>(L"ds_img_save");DMASSERT(m_pSave);
	m_pClean     = FindChildByNameT<DUIButton>(L"ds_img_clean");DMASSERT(m_pClean);
	m_pImgName	 = FindChildByNameT<DUIEdit>(L"ds_img_name");DMASSERT(m_pImgName);
	m_pImgDir	 = FindChildByNameT<DUIEdit>(L"ds_img_dir");DMASSERT(m_pImgDir);
	m_pImgFileName = FindChildByNameT<DUIEdit>(L"ds_img_filename");DMASSERT(m_pImgFileName);
	m_pImgFileAfx  = FindChildByNameT<DUIEdit>(L"ds_img_fileafx");DMASSERT(m_pImgFileAfx);
	m_pXml = FindChildByNameT<DUIRichEdit>(L"ds_img_xml");DMASSERT(m_pXml);
	m_pImgName->SetEventMask(ENM_CHANGE|m_pImgName->GetEventMask());
	m_pImgDir->SetEventMask(ENM_CHANGE|m_pImgDir->GetEventMask());
	m_pImgFileName->SetEventMask(ENM_CHANGE|m_pImgFileName->GetEventMask());
	m_pImgFileAfx->SetEventMask(ENM_CHANGE|m_pImgFileAfx->GetEventMask());

	// 3.�õ��������node
	HDMTREEITEM hTheme = NULL;
	if (m_bEditMode)
	{
		HDMTREEITEM h_p = pProjTree->GetParentItem(pXml->m_hProjSel);
		hTheme = pProjTree->GetParentItem(h_p);
	}
	else
	{
		hTheme = pProjTree->GetParentItem(pXml->m_hProjSel);
	}

	DMXmlNodePtr pThemeNode = (DMXmlNodePtr)pProjTree->GetItemData(hTheme);
	m_strDirName = pThemeNode->Attribute(XML_PATH);
	m_strDirName = m_strDirName.Left(m_strDirName.ReverseFind(L'\\')+1);
	m_strDir = pXml->m_strResDir + m_strDirName;
	m_pImgPath->DV_SetWindowText(m_strDirName);

	//3.����img���
	DMXmlNode XmlBase = m_ImgDoc.Base();
	m_ImgNode = XmlBase.InsertChildNode(XML_FILE);

	if (m_bEditMode)
	{
		DMXmlNodePtr pNode = (DMXmlNodePtr)pProjTree->GetItemData(pXml->m_hProjSel);
		if (pNode)
		{
			// title
			m_pImgName->SetWindowText(pNode->Attribute(XML_NAME));
			CStringW strPath = pXml->m_strResDir + pNode->Attribute(XML_PATH);
			m_pTitle->DV_SetWindowText(m_strTitle+strPath);

			// ����ͼƬ
			m_pImgEditor->AddImg(strPath);

			// ͼƬ��+��׺
			CStringW strFileAfx = strPath.Right(strPath.GetLength()-strPath.ReverseFind(L'.'));
			CStringW strFileName =  strPath.Left(strPath.ReverseFind(L'.'));
			strFileName = strFileName.Right(strFileName.GetLength()-1-strFileName.ReverseFind(L'\\'));
			m_pImgFileAfx->SetAttribute(L"text",strFileAfx);m_pImgFileAfx->DM_EnableWindow(false);
			m_pImgFileName->SetAttribute(L"text",strFileName);m_pImgFileName->DM_EnableWindow(false);
			m_pbMultImg->DM_SetVisible(false,true);

			// ����Ŀ¼
			strPath = strPath.Right(strPath.GetLength()-m_strDir.GetLength());
			strPath = strPath.Left(strPath.ReverseFind(L'\\')+1);
			m_pImgDir->SetWindowText(strPath);
			DUIButton* pOpenDir = FindChildByNameT<DUIButton>(L"ds_img_opendir");
			if (pOpenDir)
			{
				pOpenDir->DM_SetVisible(false,true);
			}

			// img·��
			m_pImgPath->SetAttribute(L"text",pNode->Attribute(XML_PATH));
		}
	}
	UpdateXml();
	return TRUE;
}   

void ImgDlg::OnSize(UINT nType, CSize size)
{
	if (!IsIconic()) 
	{ 
		CRect rcWnd;
		::GetWindowRect(m_hWnd, &rcWnd);
		::OffsetRect(&rcWnd, -rcWnd.left, -rcWnd.top);  
		HRGN hWndRgn = ::CreateRoundRectRgn(0, 0, rcWnd.right, rcWnd.bottom,4,4);
		SetWindowRgn(hWndRgn, TRUE);
		::DeleteObject(hWndRgn); 
		if (m_pImgEditor)
		{
			m_pImgEditor->UpdateScrollRangeSize();
		}
	}             
	SetMsgHandled(FALSE);
} 

void ImgDlg::OnDropFiles(HDROP hDropInfo)
{
	do 
	{
		if (m_bEditMode)
		{
			break;
		}
		
		int nDropCount = DragQueryFile(hDropInfo, -1, NULL, 0);
		if (1!=nDropCount)
		{
			break;
		} 

		wchar_t szPath[MAX_PATH] = {0};
		DragQueryFile(hDropInfo, 0, szPath,MAX_PATH);
		if (IsDirectoryExist(szPath))
		{
			DM_MessageBox(L"��֧���ļ���",MB_OK,L"MSG",m_hWnd);
			break;
		}
   
		// ���µ��ұߵ���ʾ��
		if (!m_pbMultImg->DM_IsChecked())// ��ͼģʽ
		{
			m_pImgEditor->Clear();
			m_pImgEditor->AddImg(szPath);
		}
		else
		{
			m_pImgEditor->AddImg(szPath);
		}

		// ���µ���ʾ��
		CStringW strPath = szPath;
		CStringW strFileAfx = strPath.Right(strPath.GetLength()-strPath.ReverseFind(L'.'));
		CStringW strFileName =  strPath.Left(strPath.ReverseFind(L'.'));
		strFileName = strFileName.Right(strFileName.GetLength()-1-strFileName.ReverseFind(L'\\'));
		m_pImgFileAfx->SetAttribute(L"text",strFileAfx);
		m_pImgFileName->SetAttribute(L"text",strFileName);
		m_pImgName->SetAttribute(L"text",strFileName);
		CStringW strTitle;
		strTitle += L"[�¼�IMG]";
		strTitle += strPath;
		m_pTitle->SetAttribute(L"text",strTitle);

		// ����ļ�·�����ڱ�������ڣ��������ļ���·��Ϊ��ԭʼ·��
		bool bMatch = false;
		if (strPath.GetLength()>m_strDir.GetLength())
		{
			CStringW strLeft = strPath.Left(m_strDir.GetLength());
			if (0 == strLeft.CompareNoCase(m_strDir))
			{
				bMatch = true;
			}
		}

		if (bMatch)// �ж�ԭʼ�ļ��Ƿ��������������ڣ������ñ���λ�ò��䣬��Ȼ��Ҳ�����Լ�ȥ�ı�
		{
			CStringW strDir = strPath.Right(strPath.GetLength()-m_strDir.GetLength());
			strDir = strDir.Left(strDir.ReverseFind(L'\\'));
			m_pImgDir->SetWindowText(strDir);
		}
	} while (false);
}

DMCode ImgDlg::OnCheckChange(DMEventArgs *pEvt)
{
	DMCode iErr = DM_ECODE_FAIL;
	do 
	{
		DMEventCheckChangingCmdArgs* pEvent = (DMEventCheckChangingCmdArgs*)pEvt;
		if (pEvent->m_pSender == m_pbMultImg)
		{
			if (pEvent->m_bChecking)
			{
				m_pbVert->DM_SetVisible(true,true);
				m_pSave->DM_SetVisible(true,true);
				m_pClean->DM_SetVisible(true,true);
			}
			else
			{
				m_pbVert->DM_SetVisible(false,true);
				m_pSave->DM_SetVisible(false,true);
				m_pClean->DM_SetVisible(false,true);
				m_pImgEditor->Clear();
			}
		}
		if (pEvent->m_pSender == m_pbVert)
		{
			m_pImgEditor->SetVert(pEvent->m_bChecking);
		}
		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}

DMCode ImgDlg::OnEditChange(DMEventArgs *pEvt)
{
	DMCode iErr = DM_ECODE_FAIL;
	do 
	{
		DMEventRENotifyArgs *pEvent = (DMEventRENotifyArgs*)(pEvt);
		if (EN_CHANGE != pEvent->m_iNotify)
		{
			break;
		}

		// �����������ʾpath
		if (pEvent->m_pSender == m_pImgName
			||pEvent->m_pSender == m_pImgDir
			||pEvent->m_pSender == m_pImgFileName
			||pEvent->m_pSender == m_pImgFileAfx
			)
		{
			CStringW strPath = m_strDirName;
			strPath += m_pImgDir->GetWindowText();
			if (strPath.Right(1)!=L"\\")
			{
				strPath += L"\\";
			}
	
			strPath += m_pImgFileName->GetWindowText();
			strPath += m_pImgFileAfx->GetWindowText();
			m_pImgPath->SetAttribute(L"text",strPath);

			UpdateXml();
		}

		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}

DMCode ImgDlg::OnSaveBtn()
{
	wchar_t szFileTitle[_MAX_FNAME] = {0};  
	wchar_t szFileName[_MAX_PATH]   = {0};
	OPENFILENAMEW ofn;
	memset(&ofn, 0, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile	= szFileName;
	ofn.nMaxFile	= _MAX_PATH;
	ofn.lpstrDefExt = L"png";
	ofn.lpstrFileTitle = (LPTSTR)szFileTitle;
	ofn.nMaxFileTitle  = _MAX_FNAME;
	ofn.Flags		   = OFN_FILEMUSTEXIST|OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT;
	ofn.lpstrFilter = L"img files(*.png)\0*.png\0img files(*.jpeg)\0*.jpeg\0img files(*.jpg)\0*.jpg\0img files(*.bmp)\0*.bmp\0\0";
	ofn.hwndOwner = m_hWnd;
	if (0 != ::GetSaveFileNameW(&ofn))
	{
		m_pImgEditor->Save(szFileName);
	}
	
	return DM_ECODE_OK;
}

DMCode ImgDlg::OnClearBtn()
{
	m_pImgEditor->Clear();
	m_pImgName->SetAttribute(L"text",L"");
	m_pImgFileName->SetAttribute(L"text",L"");
	m_pImgFileAfx->SetAttribute(L"text",L"");
	return DM_ECODE_OK;
}

DMCode ImgDlg::OnOpenDir()
{
	DMCode iErr = DM_ECODE_FAIL;
	do 
	{
		wchar_t path[MAX_PATH] = {0};
		BROWSEINFOW bi = {0};
		//hgy note: BIF_NEWDIALOGSTYLE��Ӱ��BFFM_SETSTATUSTEXT�޷���ʾ
		bi.ulFlags	 = BIF_STATUSTEXT| BIF_RETURNONLYFSDIRS|BIF_VALIDATE/*|BIF_NEWDIALOGSTYLE*/;
		bi.lpszTitle = L"�����ڵ�ǰ�������Ŀ¼��ѡ��";
		bi.hwndOwner = m_hWnd;//����ӵ�д���
		bi.lpfn = ImgDlg::BrowseCallbackProc;//ָ���ص�������ַ
		ITEMIDLIST *pIDL = SHBrowseForFolderW(&bi);
		if (pIDL!=NULL)
		{
			if (SHGetPathFromIDListW(pIDL,path) == TRUE) //����path�д洢�˾����û�ѡ����Ŀ¼������·��.
			{
				CStringW strPath = path;
				strPath = strPath.Right(strPath.GetLength()-m_strDir.GetLength());
				m_pImgDir->SetWindowText(strPath);
			}
			// free memory used   
			IMalloc * imalloc = 0;   
			if (SUCCEEDED(SHGetMalloc( &imalloc)))   
			{   
				imalloc->Free (pIDL);   
				imalloc->Release();   
			}   
		} 

		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}

DMCode ImgDlg::UpdateXml()
{
	DMCode iErr = DM_ECODE_FAIL;
	do 
	{
		CStringW strImgName = m_pImgName->GetWindowText();
		m_ImgNode.SetAttribute(XML_NAME,strImgName);

		CStringW strImgPath = m_pImgPath->m_pDUIXmlInfo->m_strText;
		m_ImgNode.SetAttribute(XML_PATH, strImgPath);

		CStringW strXml;
		m_ImgNode.GetXmlContent(strXml);
		m_pXml->SetWindowText(strXml);

		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}

int CALLBACK ImgDlg::BrowseCallbackProc(HWND hwnd,UINT uMsg,LPARAM lParam,LPARAM lpData)
{
	CStringW strDir = ms_pthis->m_strDir;
	switch (uMsg)
	{
	case BFFM_INITIALIZED:    //��ʼ����Ϣ
		{
			strDir += ms_pthis->m_pImgDir->GetWindowText();
			::SendMessageW(hwnd,BFFM_SETSELECTION,TRUE,(LPARAM)(LPWSTR)(LPCWSTR)strDir);  
		}
		break;

	case BFFM_SELCHANGED: //ѡ��·���仯
		{
			wchar_t szPath[MAX_PATH];   
			SHGetPathFromIDListW((LPCITEMIDLIST)lParam,szPath);   
			CStringW strPath = szPath;
			if (strPath.GetLength()<strDir.GetLength())
			{
				strPath = strDir;
			}
			else 
			{
				CStringW strLeft = strPath.Left(strDir.GetLength());
				if (0 != strLeft.CompareNoCase(strDir))
				{
					strPath = strDir;
				}
			}
			::SendMessageW(hwnd,BFFM_SETSTATUSTEXT,0,(LPARAM)(LPWSTR)(LPCWSTR)strPath); 
			::SendMessageW(hwnd,BFFM_SETSELECTION,TRUE,(LPARAM)(LPWSTR)(LPCWSTR)strPath);  
		}
		break;
	default:
		break;
	}

	return 0;
}

DMCode ImgDlg::OnOK()
{
	DMCode iErr = DM_ECODE_FAIL;
	HDMTREEITEM hAdd = NULL;
	ObjXml* pXml = g_pMainWnd->m_pDesignerXml;
	ProjTree* pProjTree  = g_pMainWnd->FindChildByNameT<ProjTree>(L"ds_projtree");
	do 
	{
		// 1.�ж�name�Ƿ�Ϊ�գ��жϱ�������Ƿ��Ѻ��д�name,ע�⣬��û���жϴ��ļ���û�б�����nameռ��
		CStringW strImgName = m_pImgName->GetWindowText();
		if (strImgName.IsEmpty())
		{
			DM_MessageBox(L"δ����name!",MB_OK, L"MSG",m_hWnd);
			m_pImgName->DV_SetFocusWnd();
			break;
		}

		if (m_bEditMode)// �༭ģʽ
		{
			DMXmlNodePtr pNode = (DMXmlNodePtr)pProjTree->GetItemData(pXml->m_hProjSel);
			bool bFind = false;
			HDMTREEITEM hParentItem = pProjTree->GetParentItem(pXml->m_hProjSel);
			//2. �ж�name�Ƿ��Ѵ���
			if (hParentItem)
			{
				HDMTREEITEM hChildItem = pProjTree->GetChildItem(hParentItem);
				while (hChildItem)
				{
					if (hChildItem != pXml->m_hProjSel)
					{// �����༭����
						DMXmlNodePtr pChildNode = (DMXmlNodePtr)pProjTree->GetItemData(hChildItem);
						if (0 == strImgName.CompareNoCase(pChildNode->Attribute(XML_NAME)))
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
				DM_MessageBox(L"name�Ѵ���,����������!",MB_OK,L"MSG",m_hWnd);
				m_pImgName->DV_SetFocusWnd();
				break;
			}
			
			//3.�ж������Ƿ����ǰ��ͬ���粻ͬ�������������ֵ�pNode�У�������Ϊδ����״̬
			CStringW strOldName = pNode->Attribute(XML_NAME);
			if (0 != strOldName.CompareNoCase(strImgName))
			{
				pNode->SetAttribute(XML_NAME,strImgName);
				pXml->SetDocUnSave(pNode);
			}
			
			iErr = DM_ECODE_OK;
			EndDialog(IDOK);
			break;// �м�����������Ϊ�½�ģʽ
		}
		
		DMXmlNodePtr pTypeNode = (DMXmlNodePtr)pProjTree->GetItemData(pXml->m_hProjSel);
		CStringW strType = pTypeNode->GetName();
		HDMTREEITEM hTheme = pProjTree->GetParentItem(pXml->m_hProjSel);
		DMXmlNodePtr pThemeNode = (DMXmlNodePtr)pProjTree->GetItemData(hTheme);
		CStringW strThemeName = pThemeNode->Attribute(XML_NAME);
		DMAutoResetT<bool> AutoNoLoop(&pXml->m_pRes->m_bThemeLoop,false);// �������������������
		if (DMSUCCEEDED(pXml->m_pRes->IsItemExists(strType,strImgName,strThemeName)))
		{
			DM_MessageBox(L"��������Ѵ��ڴ�name!",MB_OK, L"MSG",m_hWnd);
			m_pImgName->DV_SetFocusWnd();
			break;
		}
		//2.�ж�Ŀ¼�ļ����Ƿ�Ϊ�գ��ж��Ƿ�û�������ļ�
		CStringW strImgFileName = m_pImgFileName->GetWindowText();
		if (strImgFileName.IsEmpty())
		{
			DM_MessageBox(L"�ļ���Ϊ��!",MB_OK, L"MSG",m_hWnd);
			m_pImgFileName->DV_SetFocusWnd();
			break;
		}

		CStringW strImgSrc = m_pTitle->m_pDUIXmlInfo->m_strText;
		strImgSrc = strImgSrc.Right(strImgSrc.GetLength()-7);//L"[�¼�IMG]";
		if (!PathFileExistsW(strImgSrc))//˵��û�������ļ�
		{
			DM_MessageBox(L"δ�����ļ�!",MB_OK, L"MSG",m_hWnd);
			break;
		}
		
		// 3.����ͼƬ,����Ƕ��ͼƬ��ע���Ƕ�ͼƬ������������һ��png��һ��xml����Ҳֻ��һ��ͼƬ�������Զ�ͼƬֱ�ӱ����(��ʽ�����һ��ͼƬ�ĺ�׺)������ǵ�ͼƬ����ô�Ͳ��õ��ļ�ͬ���ķ�ʽ��ֱ�ӿ���
		CStringW strPath = pXml->m_strResDir + m_ImgNode.Attribute(XML_PATH);
		if (m_pbMultImg->DM_IsChecked() && m_pImgEditor->GetImgCount()>1)// ��ͼƬ���
		{
			m_pImgEditor->Save(strPath);
		}
		else
		{
			CStringW strImgSrc = m_pTitle->m_pDUIXmlInfo->m_strText;
			strImgSrc = strImgSrc.Right(strImgSrc.GetLength()-7);//L"[�¼�IMG]";
			if (!PathFileExistsW(strImgSrc))
			{
				DM_MessageBox(L"�ļ�������!",MB_OK, L"MSG",m_hWnd);
			}
			CopyFileW(strImgSrc,strPath,FALSE);
		}

		//4.����Res��������
		if (!DMSUCCEEDED(pXml->m_pRes->AddResItem(strType,strImgName,strPath,strThemeName)))
		{
			DM_MessageBox(L"����Resʧ��!",MB_OK, L"MSG",m_hWnd);
			break;
		}

		//5.д��xml��
		DMXmlNode XmlNode = pTypeNode->InsertCopyChildNode(&m_ImgNode);

		//6.�������ν��
		DMXmlDocument doc;
		DMXmlNode DataNode = doc.Base();
		pXml->InitProjTreeNode(DataNode,true);
		CStringW strName = strPath.Right(strPath.GetLength()-strPath.ReverseFind(L'\\')-1);
		hAdd = pXml->InsertProjTreeItem(DataNode,strName,pXml->m_hProjSel);
		pXml->BindProjTreeData(XmlNode,hAdd);

		//7.����xmlΪδ����״̬
		pXml->SetDocUnSave(pTypeNode);

		EndDialog(IDOK);
		if (hAdd)
		{
			pProjTree->SelectItem(hAdd);
		}
		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}

