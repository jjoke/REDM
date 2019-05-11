#include "DMDesignerAfx.h"
#include "PreHWnd.h"

DMXmlDocument* GetPreSubXmlDoc(LPCWSTR lpszType,LPCWSTR lpszResName)
{
	DMXmlDocument* pXmlDoc = NULL;
	do 
	{
		if (!g_pMainWnd->m_pDesignerXml)
		{
			break; 
		}
		if (NULL==lpszType||NULL==lpszResName)
		{
			break;
		}
		DMSmartPtrT<ResFolder>pRes = g_pMainWnd->m_pDesignerXml->m_pRes;
		CStringW strPath = pRes->GetItemPath(lpszType,lpszResName,L"");
		DocDataPtr pData = g_pMainWnd->m_pDesignerXml->FindDocData(strPath);
		if (pData&&pData->IsValid())
		{
			pXmlDoc = pData->m_pXmlDoc;
		}
	} while (false);
	return pXmlDoc;
}

BEGIN_MSG_MAP(PreHWnd)  
	MSG_WM_KEYDOWN(OnKeyDown)
	CHAIN_MSG_MAP(DMHWnd)// ��δ�������Ϣ����DMHWnd����
END_MSG_MAP() 
HWND PreHWnd::ObjCreateWindow(DMXmlDocument &XmlDoc)
{
	do 
	{
		// �����Ѵ���
		if (m_hWnd)
		{
			break;
		}

		ATOM Atom = g_pDMApp->GetClassAtom();  // �Ƿ�ʹ����Ӱ�����ഴ��
		// ����ʱ���ȵ��õ�OnNcCreate������XML��Դ����OnNcCreate����ʧ��,�򴴽�ʧ�ܣ�m_hWndΪNULL
		DMCWnd::CreateWindowEx((LPCWSTR)Atom,DM_DEF_WINDOW_NAME, DM_DEF_STYLE, 0, 0, 0, 0, 0, g_pMainWnd->m_hWnd, NULL);
		if (NULL == m_hWnd)
		{
			break;
		}

		// ����xml
		g_pDMApp->SetSubXmlDocCallBack(GetPreSubXmlDoc);
		LoadDMData(XmlDoc);
		g_pDMApp->SetSubXmlDocCallBack(NULL);
	} while (false);
	if (m_hWnd)
	{
		// ��ʼ����
		InitFromDMData();			

		// ע����϶�
		::RegisterDragDrop(m_hWnd, &m_DropTarget);
	}

	return m_hWnd;
}

DMCode PreHWnd::LoadDMData(DMXmlDocument &XmlDoc)
{
	DMCode iErr = DM_ECODE_OK;
	do 
	{
		DMXmlNode XmlNode = XmlDoc.Root(MAINWND_NODE);
		if (!XmlNode.IsValid())
		{
			break;
		}

		m_pHWndXmlInfo->ResetXmlInfo();                // ������XML����

		// ����˽��Skin�ڵ�,�ⲿ�����ͷ���---------------
		DMXmlNode XmlSkin = XmlNode.FirstChild(L"skin");
		while (XmlSkin.IsValid())
		{
			g_pDMApp->AddSkinPoolItem(XmlSkin);
			XmlSkin = XmlSkin.NextSibling(L"skin");
		}

		// ����˽��Style�ڵ�,�ⲿ�����ͷ���--------------
		DMXmlNode XmlStyle = XmlNode.FirstChild(L"style");
		while (XmlStyle.IsValid())
		{
			g_pDMApp->AddStylePoolItem(XmlStyle);
			XmlStyle = XmlStyle.NextSibling(L"style");
		}

		// ���������XML-Attribute-----------------------
		DMBase::InitDMData(XmlNode);

		// ѭ������DUI��XML -----------------------------
		// root�ڵ㱾��Ҳ��һ��DUIWindow���ڶ��󣬵��������������"root"����ʶ��������ڵ��п�����DUIWindow�ĸ������ԣ����ǺͲ���λ����ص������Զ���Ч����Ϊ�ô������ǳ��������������ڡ�
		DUIWindow::InitDMData(XmlNode.FirstChild(DUIROOT_NODE));
	} while (false);
	return iErr;
}

void PreHWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	do 
	{
		DMHWnd::OnKeyEvent(WM_KEYDOWN,(WPARAM)nChar,MAKELPARAM(nRepCnt,nFlags));
		if (VK_ESCAPE!=nChar)
		{
			break;
		}
		ShowWindow(SW_HIDE);
	} while (false);
}
