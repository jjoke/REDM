#include "DMDesignerAfx.h"
#include "LayoutDlg.h"

BEGIN_MSG_MAP(LayoutDlg)   
	MSG_WM_INITDIALOG(OnInitDialog) 
	MSG_WM_SIZE(OnSize) 
	MSG_WM_DROPFILES(OnDropFiles)
	CHAIN_MSG_MAP(DMHDialog)
END_MSG_MAP() 
BEGIN_EVENT_MAP(LayoutDlg)
	EVENT_NAME_HANDLER(L"ds_layout_name",DMEVT_RENOTIFY,OnEditChange)
	EVENT_NAME_HANDLER(L"ds_layout_dir",DMEVT_RENOTIFY,OnEditChange)
	EVENT_NAME_HANDLER(L"ds_layout_filename",DMEVT_RENOTIFY,OnEditChange)
	EVENT_NAME_HANDLER(L"ds_layout_fileafx",DMEVT_RENOTIFY,OnEditChange)
	EVENT_NAME_COMMAND(L"ds_layout_opendir",OnOpenDir)
END_EVENT_MAP()
LayoutDlg*  LayoutDlg::ms_pthis = NULL;
LayoutDlg::LayoutDlg(bool bEditMode)
{
	m_bEditMode = bEditMode;
	ms_pthis	= this;
	m_pTitle = m_pLayoutPath = NULL;
	m_pLayoutName = m_pLayoutDir = m_pLayoutFileName = m_pLayoutFileAfx = NULL;
	m_pXml = NULL;
}

BOOL LayoutDlg::OnInitDialog(HWND wndFocus, LPARAM lInitParam)
{
	DragAcceptFiles(TRUE);

	m_strDir = g_pMainWnd->m_pDesignerXml->m_strResDir; 
	m_strDir += L"Layout\\";

	m_pTitle         = FindChildByNameT<DUIStatic>(L"ds_title");DMASSERT(m_pTitle);
	m_pLayoutPath	 = FindChildByNameT<DUIStatic>(L"ds_layout_path");DMASSERT(m_pLayoutPath);
	m_pLayoutName	 = FindChildByNameT<DUIEdit>(L"ds_layout_name");DMASSERT(m_pLayoutName);
	m_pLayoutDir	 = FindChildByNameT<DUIEdit>(L"ds_layout_dir");DMASSERT(m_pLayoutDir);
	m_pLayoutFileName = FindChildByNameT<DUIEdit>(L"ds_layout_filename");DMASSERT(m_pLayoutFileName);
	m_pLayoutFileAfx  = FindChildByNameT<DUIEdit>(L"ds_layout_fileafx");DMASSERT(m_pLayoutFileAfx);
	m_pXml           = FindChildByNameT<DUIRichEdit>(L"ds_layout_xml");DMASSERT(m_pXml);

	m_pLayoutName->SetEventMask(ENM_CHANGE|m_pLayoutName->GetEventMask());
	m_pLayoutDir->SetEventMask(ENM_CHANGE|m_pLayoutDir->GetEventMask());
	m_pLayoutFileName->SetEventMask(ENM_CHANGE|m_pLayoutFileName->GetEventMask());
	m_pLayoutFileAfx->SetEventMask(ENM_CHANGE|m_pLayoutFileAfx->GetEventMask());

	if (m_bEditMode)// ��ʼ�����ֱ���
	{
		ObjXml* pXml = g_pMainWnd->m_pDesignerXml;
		ProjTree* pProjTree  = g_pMainWnd->FindChildByNameT<ProjTree>(L"ds_projtree");
		DMXmlNodePtr pFileNode = (DMXmlNodePtr)pProjTree->GetItemData(pXml->m_hProjSel);
		m_pLayoutName->SetWindowText(pFileNode->Attribute(XML_NAME));
		CStringW strPath = pXml->m_strResDir + pFileNode->Attribute(XML_PATH);
		CStringW strFileAfx = strPath.Right(strPath.GetLength()-strPath.ReverseFind(L'.'));
		CStringW strFileName =  strPath.Left(strPath.ReverseFind(L'.'));
		CStringW strDir = strPath.Right(strPath.GetLength()-m_strDir.GetLength());
		strDir =  strDir.Left(strDir.ReverseFind(L'\\'));
		strFileName = strFileName.Right(strFileName.GetLength()-1-strFileName.ReverseFind(L'\\'));
		m_pLayoutFileName->SetWindowText(strFileName);
		m_pLayoutFileAfx->SetWindowText(strFileAfx);
		m_pLayoutDir->SetWindowText(strDir);

		m_pLayoutFileName->SetAttribute(L"breadonly",L"1");// �༭ģʽ�²����������ļ���
	}

	DMXmlNode XmlBase = m_LayoutDoc.Base();
	m_LayoutNode = XmlBase.InsertChildNode(XML_FILE);
	UpdateXml();
	return TRUE;
}

void LayoutDlg::OnSize(UINT nType, CSize size)
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

void LayoutDlg::OnDropFiles(HDROP hDropInfo)
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

		// ���µ���ʾ��
		CStringW strPath = szPath;
		CStringW strFileAfx = strPath.Right(strPath.GetLength()-strPath.ReverseFind(L'.'));
		CStringW strFileName =  strPath.Left(strPath.ReverseFind(L'.'));
		strFileName = strFileName.Right(strFileName.GetLength()-1-strFileName.ReverseFind(L'\\'));
		m_pLayoutFileAfx->SetAttribute(L"text",strFileAfx);
		m_pLayoutFileName->SetAttribute(L"text",strFileName);
		m_pLayoutName->SetAttribute(L"text",strFileName);
		CStringW strTitle;
		strTitle += L"[LAYOUT]";
		strTitle += strPath;
		m_pTitle->SetAttribute(L"text",strTitle);

		// ����ļ�·�����ڱ�LAYOUT���ڣ��������ļ���·��Ϊ��ԭʼ·��
		bool bMatch = false;
		if (strPath.GetLength()>m_strDir.GetLength())
		{
			CStringW strLeft = strPath.Left(m_strDir.GetLength());
			if (0 == strLeft.CompareNoCase(m_strDir))
			{
				bMatch = true;
			}
		} 

		if (bMatch)// �ж�ԭʼ�ļ��Ƿ����LAYOUT�������ڣ������ñ���λ�ò��䣬��Ȼ��Ҳ�����Լ�ȥ�ı�
		{
			CStringW strDir = strPath.Right(strPath.GetLength()-m_strDir.GetLength());
			strDir = strDir.Left(strDir.ReverseFind(L'\\'));
			m_pLayoutDir->SetWindowText(strDir);
		}
	} while (false);
}

DMCode LayoutDlg::OnEditChange(DMEventArgs *pEvt)
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
		if (pEvent->m_pSender == m_pLayoutName
			||pEvent->m_pSender == m_pLayoutDir
			||pEvent->m_pSender == m_pLayoutFileName
			||pEvent->m_pSender == m_pLayoutFileAfx
			)
		{
			CStringW strPath = L"layout\\";
			strPath += m_pLayoutDir->GetWindowText();
			if (strPath.Right(1)!=L"\\")
			{
				strPath += L"\\";
			}
			strPath += m_pLayoutFileName->GetWindowText();
			strPath += m_pLayoutFileAfx->GetWindowText();
	
			m_pLayoutPath->SetAttribute(L"text",strPath);

			UpdateXml();
		}

		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}

DMCode LayoutDlg::UpdateXml()
{
	DMCode iErr = DM_ECODE_FAIL;
	do 
	{
		CStringW strLayoutName = m_pLayoutName->GetWindowText();
		m_LayoutNode.SetAttribute(XML_NAME,strLayoutName);

		CStringW strLayoutPath = m_pLayoutPath->m_pDUIXmlInfo->m_strText;
		m_LayoutNode.SetAttribute(XML_PATH, strLayoutPath);

		CStringW strXml;
		m_LayoutNode.GetXmlContent(strXml);
		m_pXml->SetWindowText(strXml);

		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}

DMCode LayoutDlg::OnOpenDir()
{
	DMCode iErr = DM_ECODE_FAIL;
	do 
	{
		if (m_bEditMode)
		{
			break;
		}
		wchar_t path[MAX_PATH] = {0};
		BROWSEINFOW bi = {0};
		//hgy note: BIF_NEWDIALOGSTYLE��Ӱ��BFFM_SETSTATUSTEXT�޷���ʾ
		bi.ulFlags	 = BIF_STATUSTEXT| BIF_RETURNONLYFSDIRS|BIF_VALIDATE/*|BIF_NEWDIALOGSTYLE*/;
		bi.lpszTitle = L"�����ڵ�ǰLayout��Ŀ¼��ѡ��";
		bi.hwndOwner = m_hWnd;//����ӵ�д���
		bi.lpfn = LayoutDlg::BrowseCallbackProc;//ָ���ص�������ַ
		ITEMIDLIST *pIDL = SHBrowseForFolderW(&bi);
		if (pIDL!=NULL)
		{
			if (SHGetPathFromIDListW(pIDL,path) == TRUE) //����path�д洢�˾����û�ѡ����Ŀ¼������·��.
			{
				CStringW strPath = path;
				strPath = strPath.Right(strPath.GetLength()-m_strDir.GetLength());
				m_pLayoutDir->SetWindowText(strPath);
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

int CALLBACK LayoutDlg::BrowseCallbackProc(HWND hwnd,UINT uMsg,LPARAM lParam,LPARAM lpData)
{
	CStringW strDir = ms_pthis->m_strDir;
	switch (uMsg)
	{
	case BFFM_INITIALIZED:    //��ʼ����Ϣ
		{
			strDir += ms_pthis->m_pLayoutDir->GetWindowText();
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

DMCode LayoutDlg::OnOK()
{
	DMCode iErr = DM_ECODE_FAIL;
	HDMTREEITEM hAdd = NULL;
	do 
	{
		ObjXml* pXml = g_pMainWnd->m_pDesignerXml;
		ProjTree* pProjTree  = g_pMainWnd->FindChildByNameT<ProjTree>(L"ds_projtree");

		//1.�ж�name�Ƿ�Ϊ�գ��жϱ�layout���Ƿ��Ѻ��д�name
		CStringW strLayoutName = m_pLayoutName->GetWindowText();
		if (strLayoutName.IsEmpty())
		{
			DM_MessageBox(L"δ����name!",MB_OK, L"MSG",m_hWnd);
			m_pLayoutName->DV_SetFocusWnd();
			break;
		}

		if (m_bEditMode)
		{
			//2. �ж�name�Ƿ�ռ��
			HDMTREEITEM hParent = pProjTree->GetParentItem(pXml->m_hProjSel);
			bool bFind = false;
			HDMTREEITEM hChild = pProjTree->GetChildItem(hParent);
			while (hChild)
			{
				DMXmlNodePtr pFileNode = (DMXmlNodePtr)pProjTree->GetItemData(hChild);
				CStringW strName = pFileNode->Attribute(XML_NAME);
				if (hChild != pXml->m_hProjSel&&0 == strName.CompareNoCase(strLayoutName))
				{
					bFind = true;
					break;
				}
				hChild = pProjTree->GetNextSiblingItem(hChild);
			}
			if (bFind)
			{
				DM_MessageBox(L"��LAYOUT���Ѵ��ڴ�name!",MB_OK, L"MSG",m_hWnd);
				m_pLayoutName->DV_SetFocusWnd();
				break;
			}

			//3. ����layout��name
			DMXmlNodePtr pNode = (DMXmlNodePtr)pProjTree->GetItemData(pXml->m_hProjSel);
			if (0 != strLayoutName.CompareNoCase(pNode->Attribute(XML_NAME)))
			{
				pNode->SetAttribute(XML_NAME,strLayoutName);
				pXml->SetDocUnSave(pNode);
			}
			
			iErr = DM_ECODE_OK;
			EndDialog(IDOK);
			break;
		}

		//2. �ж�name�Ƿ�ռ��
		bool bFind = false;
		HDMTREEITEM hChild = pProjTree->GetChildItem(pXml->m_hProjSel);
		while (hChild)
		{
			DMXmlNodePtr pFileNode = (DMXmlNodePtr)pProjTree->GetItemData(hChild);
			CStringW strName = pFileNode->Attribute(XML_NAME);
			if (0 == strName.CompareNoCase(strLayoutName))
			{
				bFind = true;
				break;
			}
			hChild = pProjTree->GetNextSiblingItem(hChild);
		}
		if (bFind)
		{
			DM_MessageBox(L"��LAYOUT���Ѵ��ڴ�name!",MB_OK, L"MSG",m_hWnd);
			m_pLayoutName->DV_SetFocusWnd();
			break;
		}

		//3.�ж�Ŀ¼�ļ����Ƿ�Ϊ�գ��ж��Ƿ�û�������ļ�
		CStringW strLayoutFileName = m_pLayoutFileName->GetWindowText();
		if (strLayoutFileName.IsEmpty())
		{
			DM_MessageBox(L"�ļ���Ϊ��!",MB_OK, L"MSG",m_hWnd);
			m_pLayoutFileName->DV_SetFocusWnd();
			break;
		} 

		//4.����xml�����������,��ʹ��outdata\\dui_addwnd.xmlΪģ�忽��
		CStringW strLayoutSrc = m_pTitle->m_pDUIXmlInfo->m_strText;
		strLayoutSrc = strLayoutSrc.Right(strLayoutSrc.GetLength()-8);//L"[LAYOUT]";
		CStringW strPath = pXml->m_strResDir + m_LayoutNode.Attribute(XML_PATH);
		if (!PathFileExistsW(strLayoutSrc))//˵��û�������ļ�
		{
			if (IDOK != DM_MessageBox(L"δ�����ļ�,�Ƿ��½�һ��DM�����ļ�?",MB_OKCANCEL,L"MSG",m_hWnd))
			{
				break;
			}
			// �½�һ��layout.xml
			wchar_t szPath[MAX_PATH] = {0};
			GetRootFullPath(L".\\DesignerRes\\outdata\\dui_addwnd.xml",szPath,MAX_PATH);
			if (PathFileExistsW(szPath))
			{	
				CopyFileW(szPath,strPath,FALSE);
			}
			else
			{
				DMXmlDocument doc;
				DMXmlNode XmlBase = doc.Base();
				DMXmlNode XmlDM = XmlBase.InsertChildNode(L"dm");
				XmlDM.SetAttribute(DMAttr::DMHWndAttr::SIZE_initsize,L"800,600");
				XmlDM.SetAttribute(DMAttr::DMHWndAttr::SIZE_minsize,L"800,600");
				XmlDM.SetAttribute(DMAttr::DMHWndAttr::bool_bresize,L"1");
				XmlDM.SetAttribute(DMAttr::DMHWndAttr::bool_btranslucent,L"1");
				XmlDM.SetAttribute(DMAttr::DMHWndAttr::BYTE_alpha,L"255");
				DMXmlNode XmlRoot = XmlDM.InsertChildNode(L"root");
				XmlRoot.SetAttribute(L"clrbg",L"pbgra(3d,3d,3d,ff)");
				DMXmlNode XmlDrag = XmlRoot.InsertChildNode(L"window");
				XmlDrag.SetAttribute(L"clrbg",L"pbgra(59,59,59,ff)");
				XmlDrag.SetAttribute(L"pos",L"0,0,-0,@36");
				doc.SaveXml(strPath);
			}
		}
		else
		{
			CopyFileW(strLayoutSrc,strPath,FALSE);
		}

		//5.д��Res��������
		if (!DMSUCCEEDED(pXml->m_pRes->AddResItem(RES_LAYOUT,strLayoutName,strPath,NULL)))
		{
			DM_MessageBox(L"����Resʧ��!",MB_OK, L"MSG",m_hWnd);
			break;
		}

		//6.д��xml��
		DMXmlNodePtr pLayoutNode = (DMXmlNodePtr)pProjTree->GetItemData(pXml->m_hProjSel);
		DMXmlNode XmlNode = pLayoutNode->InsertCopyChildNode(&m_LayoutNode);

		//7.�������ν��
		DMXmlDocument doc;
		DMXmlNode DataNode = doc.Base();
		pXml->InitProjTreeNode(DataNode,true);
		CStringW strName = strPath.Right(strPath.GetLength()-strPath.ReverseFind(L'\\')-1);
		hAdd = pXml->InsertProjTreeItem(DataNode,strName,pXml->m_hProjSel);
		pXml->BindProjTreeData(XmlNode,hAdd);

		//8.����xmlΪδ����״̬
		pXml->SetDocUnSave(pLayoutNode);

		EndDialog(IDOK);
		if (hAdd)
		{
			pProjTree->SelectItem(hAdd);
		}
		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}
