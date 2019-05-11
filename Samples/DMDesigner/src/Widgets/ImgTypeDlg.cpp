#include "DMDesignerAfx.h"
#include "ImgTypeDlg.h"

BEGIN_MSG_MAP(ImgTypeDlg)   
	MSG_WM_INITDIALOG(OnInitDialog) 
	MSG_WM_SIZE(OnSize) 
	CHAIN_MSG_MAP(DMHDialog)
END_MSG_MAP() 
ImgTypeDlg::ImgTypeDlg(bool bEditMode,CStringW strName)
{ 
	m_bEditMode = bEditMode;
	m_strName   = strName;
}  
 
BOOL ImgTypeDlg::OnInitDialog( HWND wndFocus, LPARAM lInitParam )
{
	DUIStatic* pTitle = FindChildByNameT<DUIStatic>(L"ds_title");
	CStringW strTitle;
	if (false == m_bEditMode)
	{
		strTitle = L"[";
		ObjXml* pXml = g_pMainWnd->m_pDesignerXml;
		ProjTree* pProjTree = g_pMainWnd->FindChildByNameT<ProjTree>(L"ds_projtree");
		DMXmlNodePtr pThemeData = (DMXmlNodePtr)pProjTree->GetItemData(pXml->m_hProjSel);
		strTitle += pThemeData->Attribute(XML_NAME);
		strTitle += L"]";
	}
	
	if (false == m_bEditMode)
	{
		strTitle += L"����Img����";
	}
	else
	{
		strTitle += L"�༭Img����";
	}
	pTitle->DV_SetWindowText(strTitle);
	DUIEdit* pEdit = FindChildByNameT<DUIEdit>(L"ds_name");
	if (m_bEditMode)
	{
		pEdit->SetWindowText(m_strName);
	}
	pEdit->DV_SetFocusWnd();
	return TRUE;
}

void ImgTypeDlg::OnSize( UINT nType, CSize size )
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

DMCode ImgTypeDlg::OnOK()
{
	DMCode iErr = DM_ECODE_FAIL;
	HDMTREEITEM hAdd = NULL;
	do 
	{
		ObjXml* pXml = g_pMainWnd->m_pDesignerXml;
		ProjTree* pProjTree  = g_pMainWnd->FindChildByNameT<ProjTree>(L"ds_projtree");
		if (NULL == pXml||NULL == pProjTree)
		{
			break;
		}
		DUIEdit* pEdit = FindChildByNameT<DUIEdit>(L"ds_name");
		CStringW strName = pEdit->GetWindowText();
		strName.Trim();
		HDMTREEITEM hSel = pXml->m_hProjSel;
		DMXmlNodePtr pNode = (DMXmlNodePtr)pProjTree->GetItemData(hSel);
		if (NULL == pNode)
		{
			break;
		}
		if (strName.IsEmpty())
		{
			DM_MessageBox(L"���ֲ���Ϊ��",MB_OK,L"Error",m_hWnd);
			pEdit->DV_SetFocusWnd();
			break;
		}

		// �༭ģʽ ------------------------------
		if (m_bEditMode)
		{
			CStringW strOldName = pNode->GetName();
			if (strOldName != strName)
			{
				// �޸�Node��Name
				pNode->SetName(strName);
				DM::LPTVITEMEX pData = pProjTree->GetItem(hSel);
				pData->pPanel->m_pDUIXmlInfo->m_strText = strName;
				pProjTree->UpdateItemRect(hSel);

				// ����Ӧxml����Ϊδ����
				pXml->SetDocUnSave(pNode);
			}

			iErr = DM_ECODE_OK;
			EndDialog(IDOK);
			break;
		}

		// �½�ģʽ ------------------------------
		CStringW strPath = pXml->m_strResDir + pNode->Attribute(XML_PATH);
		DocDataPtr pDoc = pXml->FindDocData(strPath);
		if (NULL == pDoc)
		{
			DM_MessageBox(L"�������Ϊ��,����ɨ�����",MB_OK,L"Error",m_hWnd);
			EndDialog(IDCANCEL);
			break;
		}

		//1.����xml���
		DMXmlNode XmlNode = pDoc->m_XmlRoot.InsertChildNode(strName);

		//2.����tree���,��������
		DMXmlDocument doc;
		DMXmlNode DataNode = doc.Base();
		pXml->InitProjTreeNode(DataNode,true);
		hAdd = pXml->InsertProjTreeItem(DataNode,strName,hSel);
		pXml->BindProjTreeData(XmlNode,hAdd);

		//3.����Ӧxml����Ϊδ����״̬
		pXml->SetDocUnSave(strPath);

		iErr = DM_ECODE_OK;
		EndDialog(IDOK);
		if (hAdd)
		{
			pProjTree->SelectItem(hAdd);
		}
	} while (false);
	return iErr;
}

