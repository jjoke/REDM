#include "QQDemoAfx.h"
#include "SpyWnd.h"

BEGIN_MSG_MAP(CSpyWnd)
	MSG_WM_INITDIALOG(OnInitDialog)
	CHAIN_MSG_MAP(DMHWnd)
END_MSG_MAP()
BEGIN_EVENT_MAP(CSpyWnd)
	EVENT_NAME_COMMAND(L"spy_minbutton", OnMinimize)
	EVENT_NAME_COMMAND(L"spy_closebutton",OnClose)
	EVENT_NAME_HANDLER(L"spyfindbtn",DMSpyInitArgs::EventID,OnSpyInitEvent)
	EVENT_NAME_HANDLER(L"spytree",DMEventTCSelChangedArgs::EventID,OnTreeSelChanged)
END_EVENT_MAP()
CSpyWnd::CSpyWnd()
{
	m_pTreeCtrl = NULL;
	m_pTreeEdit = NULL;
	m_pSearchSta= NULL;
	m_hRootWnd  = NULL;
	m_bDraw     = false;
	m_bHittest  = false;
	m_bInit     = false;
	m_pSpyEnum  = new DMSpyEnum;
	memset(m_pSpyEnum,0,sizeof(DMSpyEnum));
}

CSpyWnd::~CSpyWnd()
{
	DM_DELETE(m_pSpyEnum);
}

DMCode CSpyWnd::OnMinimize()
{
	SendMessage(WM_SYSCOMMAND,SC_MINIMIZE);
	return DM_ECODE_OK;
}

DMCode CSpyWnd::OnClose()
{
	DestroyWindow();
	return DM_ECODE_OK;
}	

BOOL CSpyWnd::OnInitDialog(HWND wndFocus, LPARAM lInitParam)
{
	m_pTreeCtrl  = FindChildByNameT<DUITreeCtrl>(L"spytree");
	m_pTreeEdit  = FindChildByNameT<DUIRichEdit>(L"spyedit");
	m_pSearchSta = FindChildByNameT<DUIStatic>(L"search_sta");
	m_pSearchSta->DV_SetWindowText(L"���϶�����ָ�뵽��Ҫ�鿴�Ĵ���/�ؼ����ͷ�");
	DMASSERT(m_pTreeCtrl);DMASSERT(m_pTreeEdit);DMASSERT(m_pSearchSta);

	return TRUE;
}

DMCode CSpyWnd::OnSpyInitEvent(DMEventArgs *pEvt)
{
	DMSpyInitArgs *pInitEvt = (DMSpyInitArgs*)pEvt;
	do 
	{

		if (!pInitEvt
			||!pInitEvt->m_hwnd)
			//||pInitEvt->m_hwnd == m_hWnd)
		{
			break;
		}
		if (pInitEvt->m_hwnd == m_hRootWnd&&m_bInit)
		{
			break;
		}
		m_pTreeCtrl->RemoveAllItems();
		DM_KillTimer(10);
		m_bDraw = false;
		m_bInit = false;
		m_pTreeEdit->SetWindowText(L"");
		m_pSearchSta->DV_SetWindowText(L"���϶�����ָ�뵽��Ҫ�鿴�Ĵ���/�ؼ����ͷ�");
		// Ĭ��wparam��ʲô����ʲô
		DWORD_PTR lresult = 0; 
		LRESULT lr  = ::SendMessageTimeout(pInitEvt->m_hwnd,WM_DMSPY,DMSPY_INIT,(LPARAM)m_hWnd,SMTO_NORMAL,2000,&lresult);
		if (lr&&DMSPY_INIT!=lresult)
		{
			break;
		}
		m_hRootWnd = pInitEvt->m_hwnd;
		DMSpyTool::ReleaseSharedMemory();
		DMSpyTool::CreateSharedMemory(sizeof(DMSpyEnum));

		// ��ʼ����pInitEvt->m_hwndΪroot��ö������DUI����
		InitTreeCtrl(pInitEvt->m_hwnd);

	} while (false);
	return DM_ECODE_OK;
}


DMCode CSpyWnd::OnTreeSelChanged(DMEventArgs *pEvt)
{
	if (m_bHittest)// ����pt���ң�pt���������Լ���
	{
		return DM_ECODE_OK;
	}
	DMEventTCSelChangedArgs *pSelEvt = (DMEventTCSelChangedArgs*)pEvt;
	HDMTREEITEM hSelItem = pSelEvt->m_hNewSel;
	if (hSelItem)
	{
		DUIWND hDUIWnd = (DUIWND)m_pTreeCtrl->GetItemData(hSelItem);
		if (hDUIWnd)
		{
			m_pSpyEnum->iCode   = GDW_FIRSTCHILD;
			m_pSpyEnum->hDUIWnd = hDUIWnd;
			DMSpyTool::WriteShareMemory(m_pSpyEnum,sizeof(DMSpyEnum));
			DWORD_PTR lresult = 0; 
			if (0!= ::SendMessageTimeout(m_hRootWnd, WM_DMSPY, DMSPY_INFO, 0,SMTO_NORMAL,2000,&lresult)&&DMSPY_INFO ==lresult)
			{
				ReflashEditInfo();
				m_bDraw = true;
				m_rcDraw = m_pSpyEnum->info.rcWindow;
				::BringWindowToTop(m_hRootWnd);
				DM_SetTimer(10,10);
			}
		}
		else
		{
			m_bDraw = false;
			DM_KillTimer(10);
		}
	}
	return DM_ECODE_OK;
}

void CSpyWnd::InitTreeCtrl(HWND hRootWnd)
{
	do 
	{
		CStringW strRoot;
		strRoot.Format(L"���� %08x-(root)",hRootWnd);
		HDMTREEITEM hRootTree = m_pTreeCtrl->InsertItem(strRoot,0,0,(LPARAM)-1);

		// ���xml�б�
		wchar_t szXmlPath[MAX_PATH] = {0};
		DM::GetRootFullPath(L".\\DMSpyTree.xml",szXmlPath,MAX_PATH);
		DMSpyTool::WriteShareMemory(szXmlPath,MAX_PATH);
		HRESULT hr = (HRESULT)::SendMessage(hRootWnd, WM_DMSPY, DMSPY_ENUM, 0);
		if (DMSPY_ENUM != hr)
		{
			break;
		}
		DMXmlDocument doc;
		if (!doc.LoadFromFile(szXmlPath))
		{
			break;
		}

		// �������οؼ�
		DMXmlNode XmlNode = doc.Root();
		if (!XmlNode.IsValid())
		{
			break;
		}
		InsertTreeItem(XmlNode,hRootTree);
		m_pTreeCtrl->Expand(hRootTree,TVE_COLLAPSE);
	} while (false);
	int nCount = m_pTreeCtrl->GetCount();
	if (nCount>1)
	{
		m_bInit = true;
		m_pSearchSta->DV_SetWindowText(L"DUI��ʼ�����,���϶�����ָ��鿴DUI����/�ؼ�");
	}
	else
	{
		m_bInit = false;
		m_pSearchSta->DV_SetWindowText(L"���϶�����ָ�뵽��Ҫ�鿴�Ĵ���/�ؼ����ͷ�");
	}
}

void CSpyWnd::InsertTreeItem(DMXmlNode &XmlNode,HDMTREEITEM hParentItem)
{
	int duiwnd = XmlNode.AttributeInt(L"duiwnd");
	int bsee = XmlNode.AttributeInt(L"bsee");
	int bPanel = XmlNode.AttributeInt(L"bpanel");
	CStringW classname = XmlNode.Attribute(L"classname");
	CStringW name = XmlNode.Attribute(L"name");
	CStringW id = XmlNode.Attribute(L"id");
	CStringW level = XmlNode.Attribute(L"level");

	CStringW strTree;
	if (1 == bPanel)
	{
		strTree.Format(L"(panel)����level(%s) ID:%d Name:%s ����:%s",level,duiwnd,name,classname);
	}
	else
	{
		strTree.Format(L"����level(%s) ID:%d Name:%s ����:%s",level,duiwnd,name,classname);
	}
	int iIcon = bsee?1:0;
	HDMTREEITEM hChildItem = m_pTreeCtrl->InsertItem(strTree,iIcon,iIcon,(LPARAM)duiwnd,hParentItem);
	for (DMXmlNode XmlChildNode = XmlNode.FirstChild(); XmlChildNode.IsValid(); XmlChildNode=XmlChildNode.NextSibling())
	{
		InsertTreeItem(XmlChildNode,hChildItem);
	}
}

void CSpyWnd::ReflashEditInfo()
{
	DMSpyTool::ReadShareMemory(m_pSpyEnum,sizeof(DMSpyEnum));
	CStringW strWnd;
	strWnd.Format(L"��������:left:%d,top:%d,wid:%d,hei:%d\r\n",m_pSpyEnum->info.rcWindow.left,m_pSpyEnum->info.rcWindow.top,m_pSpyEnum->info.rcWindow.Width(),m_pSpyEnum->info.rcWindow.Height());
	CStringW strClient;
	strClient.Format(L"�ͻ�����:left:%d,top:%d,wid:%d,hei:%d\r\n",m_pSpyEnum->info.rcClient.left,m_pSpyEnum->info.rcClient.top,m_pSpyEnum->info.rcClient.Width(),m_pSpyEnum->info.rcClient.Height());
	CStringW strInfo =strWnd + strClient;
	strInfo += L"XML:\r\n";
	strInfo += m_pSpyEnum->info.szXml;

	m_pTreeEdit->SetWindowText(strInfo);
}

bool CSpyWnd::HitTest(RECT &rc)
{
	bool bRet = false;
	do 
	{
		if (!m_bInit||0==m_pTreeCtrl->GetCount()||NULL==m_hRootWnd)
		{
			break;
		}
		POINT pnnt;
		::GetCursorPos(&pnnt);
		::ScreenToClient(m_hRootWnd,&pnnt);
		m_pSpyEnum->hDUIWnd = DMSPY_ENUM_BEGIN;
		m_pSpyEnum->pt = pnnt;
		DMSpyTool::WriteShareMemory(m_pSpyEnum,sizeof(DMSpyEnum));
		DWORD_PTR lresult = 0; 
		HRESULT hr = (HRESULT)::SendMessageTimeout(m_hRootWnd, WM_DMSPY, DMSPY_POINT, 0,SMTO_NORMAL,2000,&lresult);
		DMSpyTool::ReadShareMemory(m_pSpyEnum,sizeof(DMSpyEnum));
		if (hr&&DMSPY_POINT == lresult&&m_pSpyEnum->hNextDUIWnd)
		{
			// ����ѡ��tree
			HDMTREEITEM hItem = m_pTreeCtrl->GetRootItem();
			while (hItem)
			{
				DUIWND hDUIWnd = (DUIWND)m_pTreeCtrl->GetItemData(hItem);
				if (m_pSpyEnum->hNextDUIWnd == hDUIWnd)
				{
					m_bHittest = true;
					rc = m_pSpyEnum->info.rcWindow;
					m_pTreeCtrl->SelectItem(hItem, TRUE);
					ReflashEditInfo();
					m_bHittest = false;
					bRet = true;
					break;
				}
				hItem = m_pTreeCtrl->GetNextItem(hItem);
			}
		}

	} while (false);
	return bRet;
}

void CSpyWnd::OnDUITimer(char id)
{
	DMHWnd::OnDUITimer(id);
	if (10 == id&&m_bDraw)
	{
		static int ncount = 40;
		ncount--;
		if (ncount!=1)
		{
			return;
		}
		HWND DeskHwnd = ::GetDesktopWindow();//ȡ��������
		HDC DeskDC    = ::GetWindowDC(DeskHwnd);
		int oldRop2   = SetROP2(DeskDC, R2_NOTXORPEN);
		RECT rc = m_rcDraw;
		HPEN newPen = ::CreatePen(PS_DASHDOTDOT, 1, RGB(125, 0, 125));
		HGDIOBJ oldPen = ::SelectObject(DeskDC, newPen);
		::Rectangle(DeskDC, rc.left, rc.top,rc.right, rc.bottom);
		Sleep(200); //������˸ʱ����
		::Rectangle(DeskDC, rc.left, rc.top,rc.right, rc.bottom);

		::SetROP2(DeskDC, oldRop2);
		::SelectObject(DeskDC, oldPen);
		::DeleteObject(newPen);
		::ReleaseDC(DeskHwnd, DeskDC);
		DeskDC = NULL;
		ncount = 40;
	}
}
