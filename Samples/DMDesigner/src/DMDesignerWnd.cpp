#include "DMDesignerAfx.h"
#include "DMDesignerWnd.h"
#include "NewResDlg.h"

DesignMenu g_GlbMenuItem[] = \
{
	{GLBMENU_NEW,			  L" �½� ctrl+n"},//0 
	{GLBMENU_SAVE,			  L" ���� ctrl+s"},//1 
	{GLBMENU_CLOSE,			  L" �ر�"},//2 
	{GLBMENU_EXIT,		      L" �˳�"},//3 

	{GLBMENU_UNDO,			  L" ���� ctrl+z" }, //4
	{GLBMENU_REDO,			  L" ���� ctrl+r" }, //5

	{GLBMENU_OPTOBJPROJ,	  L" �л�������ͼ ctrl+q"},//6 
	{GLBMENU_RELOAD,		  L" ���¼���     f5"},//7

	{GLBMENU_MOVEMODE,		  L" Moveģʽ ctrl+1"},//8
	{GLBMENU_SELMODE,		  L" Selģʽ  ctrl+2"},//9
	{GLBMENU_ADDMODE,		  L" Addģʽ  ctrl+3"},//10

	{GLBMENU_HELPDOC,		  L" �����ĵ�"},//11
	{GLBMENU_ONLINEHELP,	  L" ���߽̳�"},//12
};
enum
{
	GLBMENUBTN_ID_MIN          = 100,
	GLBMENUBTN_ID_FILE,							///< �ļ�
	GLBMENUBTN_ID_EDIT,							///< �༭
	GLBMENUBTN_ID_VIEW,							///< ��ͼ
	GLBMENUBTN_ID_MODE,							///< ģʽ
	GLBMENUBTN_ID_HELP,							///< ����
	//
	GLBMENUBTN_ID_MAX		   = 110
};

DMDesignerWnd* g_pMainWnd = NULL;
DMSmartPtrT<ResMultFolder> g_pRes;
BEGIN_MSG_MAP(DMDesignerWnd)    
	CHAIN_MSG_STATIC_MAP(AddXml,s_ProcessWindowMessage)
	CHAIN_MSG_STATIC_MAP(RightXml,s_ProcessWindowMessage)
	MSG_WM_INITDIALOG(OnInitDialog) 
	MSG_WM_SIZE(OnSize)
	MSG_WM_DESTROY(OnDestroy)
	MSG_WM_LBUTTONDOWN(OnLButtonDown)
	MSG_WM_LBUTTONDBLCLK(OnLButtonDbClick)
	MSG_WM_DROPFILES(OnDropFiles)
	MSG_WM_COMMAND(OnCommand)
	MSG_WM_TIMER(OnTimer) 
	CHAIN_MSG_MAP(DMHWnd)// ��δ�������Ϣ����DMHWnd����
	REFLECT_NOTIFICATIONS_EX()
END_MSG_MAP() 
BEGIN_EVENT_MAP(DMDesignerWnd)
	EVENT_NAME_COMMAND(L"ds_closebutton",	OnClose)
	EVENT_NAME_COMMAND(L"ds_maxbutton",		OnMaximize)
	EVENT_NAME_COMMAND(L"ds_restorebutton", OnRestore)
	EVENT_NAME_COMMAND(L"ds_minbutton",		OnMinimize)
	EVENT_NAME_HANDLER(L"ds_preview",DMEVT_CMD,OnPreview)
	EVENT_ID_COMMAND_RANGE(GLBMENUBTN_ID_MIN,GLBMENUBTN_ID_MAX,OnGlobalMenuBtn)	
	CHAIN_EVENT_STATIC_MAP(RightXml,s_DMHandleEvent)
	CHAIN_EVENT_STATIC_MAP(AddXml,s_DMHandleEvent)
END_EVENT_MAP()

CStringW g_Tips[] = \
{
	L"���F5���´Ӵ����м�����Դ�ļ�",
	L"�������ϸ�������˵�->����->�����ĵ�",
	L"ʹ��Ctrl+N���½���Դ�����Լ���ʷ��¼",
	L"ʹ��Ctrl+S��ʱ������Դ�ļ���������",
	L"�������ϸ�������˵�->����->�����ĵ�",
	L"ʹ��Ctrl+Q�ڽ���������ͼ�����ٶ�����ͼ���л�",
	L"�ڹ���/������ͼ�е���Ҽ����Կ�����ת������ļ�",
	L"�������ϸ�������˵�->����->�����ĵ�",
	L"�ڶ�����ͼ�е��С��ͼ���������ؼ������ı�",
	L"�ڶ�����ͼ�е��С�۾�ͼ������ʱ���ؿؼ�",
	L"�������ϸ�������˵�->����->�����ĵ�",
	L"�ڶ�����ͼ�еĿؼ����Ҽ�����/ճ�����Կ��ٸ���/ճ���ؼ�",
	L"�ڶ�����ͼ�й�ѡ֧��Panel���Կ���Panel֧��",
	L"�������ϸ�������˵�->����->�����ĵ�",
	L"��SELģʽ�£���ʾ�ɻ�ɫ��DOT�����϶�",
	L"��SELģʽ�£���/�һ����ɿ���ѡ�пؼ�",
	L"�������ϸ�������˵�->����->�����ĵ�",
	L"ʹ��DELETE��ݼ�����ɾ���Ҳ��PROP��",
	L"���е���ʾ����֧���϶����ı��С",
	L"�������ϸ�������˵�->����->�����ĵ�",
	L"�ұ������б���м�Ҳ֧���϶����ı����Ҵ�С",
	L"�ڹ�����ͼ�У�δ��XML�Ľ��Ϊ��ɫ",
	L"�������ϸ�������˵�->����->�����ĵ�",
	L"�ڶ�����ͼ�У�ItemPanel����ʾ�ɺ�ɫ",
	L"CTRL+1���Կ����л���MOVEģʽ",
	L"�������ϸ�������˵�->����->�����ĵ�",
	L"CTRL+2���Կ����л���SELģʽ",
	L"CTRL+3���Կ����л���Addģʽ",
	L"�������ϸ�������˵�->����->�����ĵ�",
};
#define  TIMER_TIPS                                  110
DMDesignerWnd::DMDesignerWnd()
{
	g_pMainWnd = this;
	g_pDMApp->GetDefRegObj((void**)&g_pRes, DMREG_Res);
	m_pDesignerXml = NULL;
	SetData(L"1C3A5807-CEE1-438C-BC46-624F74BDC8D1",L"440A2781-8BC2-4AC4-8225-9AC451FE42B4");
}

DMDesignerWnd::~DMDesignerWnd()
{
	m_pDesignerXml = NULL;
}

// ��Ϣ�ַ�
BOOL DMDesignerWnd::OnInitDialog(HWND wndFocus, LPARAM lInitParam)
{
	DragAcceptFiles(TRUE);

	DWORD accel = DUIAccel::TranslateAccelKey(L"ctrl+n");
	DUIAccel acc(accel);
	GetAccelMgr()->RegisterAccel(acc,this);
	accel = DUIAccel::TranslateAccelKey(L"ctrl+s");
	
	DUIAccel accsave(accel);
	GetAccelMgr()->RegisterAccel(accsave,this);

	accel = DUIAccel::TranslateAccelKey(L"ctrl+q");
	DUIAccel accobjtree(accel);
	GetAccelMgr()->RegisterAccel(accobjtree,this);

	CStringW strAcc;
	for (int i=1;i<=4;i++)
	{
		strAcc.Format(L"ctrl+%d",i);
		accel = DUIAccel::TranslateAccelKey(strAcc);
		DUIAccel acctemp(accel);
		GetAccelMgr()->RegisterAccel(acctemp,this);		
	}

	accel = DUIAccel::TranslateAccelKey(L"f5");
	DUIAccel accf5(accel);
	GetAccelMgr()->RegisterAccel(accf5,this);

	accel = DUIAccel::TranslateAccelKey(L"ctrl+z");
	DUIAccel accCtrlZ(accel);
	GetAccelMgr()->RegisterAccel(accCtrlZ, this);

	accel = DUIAccel::TranslateAccelKey(L"ctrl+r");
	DUIAccel accCtrlR(accel);
	GetAccelMgr()->RegisterAccel(accCtrlR, this);

	SetTimer(TIMER_TIPS,4000);
	return TRUE;  
}

void DMDesignerWnd::OnLButtonDown(UINT nFlags,CPoint pt)
{
	SetFocus();
	SetMsgHandled(FALSE);
}

void DMDesignerWnd::OnLButtonDbClick(UINT nFlags,CPoint pt)
{
	do 
	{	
		SetMsgHandled(FALSE);
		DUIWND hDUIWnd = 0;
		if (pt.y>=40)
		{
			break;
		}

		DUIWindow*pMaxWnd     = FindChildByName(L"ds_maxbutton");
		DUIWindow*pRestoreWnd = FindChildByName(L"ds_restorebutton");
		if (pMaxWnd->DM_IsVisible())
		{
			OnMaximize();
		}
		else
		{
			OnRestore();
		}	

	} while (false);
}

void DMDesignerWnd::OnSize(UINT nType, CSize size)
{
	DUIWindow*pMaxWnd     = FindChildByName(L"ds_maxbutton");
	DUIWindow*pRestoreWnd = FindChildByName(L"ds_restorebutton");
	if (!IsIconic())  
	{
		CRect rcWnd;
		::GetWindowRect(m_hWnd, &rcWnd);
		::OffsetRect(&rcWnd, -rcWnd.left, -rcWnd.top);  
		HRGN hWndRgn = ::CreateRoundRectRgn(0, 0, rcWnd.right, rcWnd.bottom,4,4);
		SetWindowRgn(hWndRgn, TRUE);
		::DeleteObject(hWndRgn);  
	}                        
	if (SIZE_MAXIMIZED == nType&&pMaxWnd&&pRestoreWnd) 
	{  
		pMaxWnd->DM_SetVisible(false);
		pRestoreWnd->DM_SetVisible(true);
	}                 
	else if (SIZE_RESTORED == nType&&pMaxWnd&&pRestoreWnd)
	{
		pMaxWnd->DM_SetVisible(true);
		pRestoreWnd->DM_SetVisible(false);
	} 
	SetMsgHandled(FALSE);
}

void DMDesignerWnd::OnDestroy()
{
	DM_DELETE(m_pDesignerXml);
	SetMsgHandled(FALSE);
}

void DMDesignerWnd::OnDropFiles(HDROP hDropInfo)
{    
	do 
	{
		int nDropCount = DragQueryFile(hDropInfo, -1, NULL, 0);
		if (1!=nDropCount)
		{
			break;
		} 

		wchar_t szPath[MAX_PATH] = {0};
		DragQueryFile(hDropInfo, 0,(LPWSTR)szPath,MAX_PATH);

		// �ж��Ƿ�ΪĿ¼
		if (IsDirectoryExist(szPath))
		{
			OnParseRes(szPath);
		}
	} while (false);
}

void DMDesignerWnd::OnCommand(UINT uNotifyCode, int nID, HWND wndCtl)
{
	if (nID>=GLBMENU_BASE)
	{
		HandleGlobalMenu(nID);
	}
	else if (nID>=OBJMENU_OPENDIR)
	{
		m_pDesignerXml->HandleObjTreeMenu(nID);
	}
	else if (nID>=PROJMENU_OPENDIR)
	{
		m_pDesignerXml->HandleProjTreeMenu(nID);
	}
}

void DMDesignerWnd::OnTimer(UINT_PTR idEvent)
{
	SetMsgHandled(FALSE);
	do 
	{
		if (TIMER_TIPS != idEvent)
		{
			break;
		}
		static int i = 0;
		int iTipsNum = sizeof(g_Tips)/sizeof(g_Tips[0]);
		if (i>=iTipsNum)
		{
			i = 0;
		}
		FindChildByNameT<DUIStatic>(L"ds_tips")->SetAttribute(XML_CLRTEXT,L"pbgra(00,ff,ff,ff)");
		FindChildByNameT<DUIStatic>(L"ds_tips")->DV_SetWindowText(g_Tips[i++]);
	} while (false);
}

// �¼��ַ�
DMCode DMDesignerWnd::OnClose()
{
	if (m_pDesignerXml)
	{
		if (m_pDesignerXml->IsNeedSave())
		{
			m_pDesignerXml->SaveRes(false);
		}
	}
	KillTimer(TIMER_TIPS);
	DestroyWindow();
	return DM_ECODE_OK;
}		

DMCode DMDesignerWnd::OnMaximize()
{
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
	SetActiveWindow();
	return DM_ECODE_OK;
}

DMCode DMDesignerWnd::OnRestore()
{
	SendMessage(WM_SYSCOMMAND,SC_RESTORE);
	SetActiveWindow();
	return DM_ECODE_OK;
} 

DMCode DMDesignerWnd::OnMinimize()
{
	SendMessage(WM_SYSCOMMAND,SC_MINIMIZE);
	return DM_ECODE_OK;
}

DMCode DMDesignerWnd::OnPreview(DMEventArgs *pEvt)
{
	if (m_pDesignerXml)
	{
		m_pDesignerXml->ShowPreview();
	}
	return DM_ECODE_OK;
}

bool DMDesignerWnd::OnAccelPressed(const DUIAccel& Accel)
{
	DUIAccel acc = Accel;
	CStringW str = acc.FormatHotkey();
	if (0 == str.CompareNoCase(L"CTRL+N"))
	{
		OpenNewProj();
	}
	else if (0 == str.CompareNoCase(L"CTRL+S"))
	{
		if (m_pDesignerXml)
		{
			m_pDesignerXml->SaveRes();
		}
	}
	else if (0 == str.CompareNoCase(L"CTRL+Q"))
	{
		OptionObjProj();
	}
	else if (0 == str.CompareNoCase(L"CTRL+1")
			||0 == str.CompareNoCase(L"CTRL+2")
			||0 == str.CompareNoCase(L"CTRL+3")
			)
	{
		int iSel = 0;
		swscanf_s((LPCWSTR)str,L"Ctrl+%d",&iSel);
		FindChildByNameT<DUITabCtrl>(L"ds_tool")->SetCurSel(iSel-1);
	}
	else if (0 == str.CompareNoCase(L"f5"))
	{
		ReloadProj();
	}
	else if (0 == str.CompareNoCase(L"Ctrl+Z"))
	{
		HandleGlobalMenu(GLBMENU_UNDO);
	}
	else if (0 == str.CompareNoCase(L"Ctrl+R"))
	{
		HandleGlobalMenu(GLBMENU_REDO);
	}

	return true;
}

DMCode DMDesignerWnd::OnParseRes(CStringW strResDir)
{
	DMCode iErr = DM_ECODE_FAIL;
	do 
	{
		CloseProj();
		m_pDesignerXml = new ObjXml;
		m_pDesignerXml->ParseRes(strResDir);
		iErr = m_pDesignerXml->InitProjTree();
		if (!DMSUCCEEDED(iErr))
		{
			DM_Invalidate();
			break;
		}
		FindChildByNameT<DUIStatic>(L"ds_resdirsta")->DV_SetWindowText(strResDir);
		g_pAttr->AddRecentResDir(strResDir);
	} while (false);
	if (!DMSUCCEEDED(iErr))
	{
		DM_DELETE(m_pDesignerXml);
	}
	return iErr;
}

DMCode DMDesignerWnd::OnGlobalMenuBtn(int idFrom)
{
	DMCode iErr = DM_ECODE_FAIL;
	do 
	{
		DUIWindow* pCur = FindChildById(idFrom);
		if (NULL == pCur)
		{
			break;
		}
		
		DMXmlDocument Doc;
		g_pDMApp->InitDMXmlDocument(Doc, XML_LAYOUT,L"ds_menu_proj");
		DMXmlNode XmlNode = Doc.Root();
		XmlNode.SetAttributeInt(XML_BSHADOW,1);
		XmlNode.SetAttribute(L"clrtext",L"pbgra(ff,ff,00,ff)");
		InitFileMenu(XmlNode,idFrom);
		InitEditMenu(XmlNode,idFrom);
		InitViewMenu(XmlNode,idFrom);
		InitModeMenu(XmlNode,idFrom);
		InitHelpMenu(XmlNode,idFrom);

		DUIMenu Menu;
		Menu.LoadMenu(XmlNode); 
		CRect rcButton = pCur->m_rcWindow;
		ClientToScreen(rcButton);
		CPoint pt(rcButton.left,rcButton.bottom);
		Menu.TrackPopupMenu(0,pt.x,pt.y,m_hWnd);
		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}

DMCode DMDesignerWnd::HandleGlobalMenu(int nID)
{
	switch (nID)
	{
	case GLBMENU_NEW:
		{
			OpenNewProj();
		}
		break;

	case GLBMENU_SAVE:
		{
			if (m_pDesignerXml)
			{
				m_pDesignerXml->SaveRes();
			}
		}
		break;

	case GLBMENU_CLOSE:
		{
			CloseProj();
		}
		break;

	case GLBMENU_EXIT:
		{
			OnClose();
		}
		break;

	case GLBMENU_UNDO:
		{
			m_ActionSlotMgr.ExcutePrevSiblingAction();
		}
		break;

	case GLBMENU_REDO:
		{
			m_ActionSlotMgr.ExcuteNextSiblingAction();
		}
		break;

	case GLBMENU_OPTOBJPROJ:
		{
			OptionObjProj();
		}
		break;

	case GLBMENU_RELOAD:
		{
			ReloadProj();
		}
		break;

	case GLBMENU_MOVEMODE:
	case GLBMENU_SELMODE:
	case GLBMENU_ADDMODE:
		{
			int iSel = nID-GLBMENU_MOVEMODE;
			FindChildByNameT<DUITabCtrl>(L"ds_tool")->SetCurSel(iSel);
		}
		break;

	case GLBMENU_HELPDOC:
		{
			wchar_t szDocPath[MAX_PATH]={0};
			DM::GetRootFullPath(L".\\DesignerRes\\DMDesign-Help.docx",szDocPath,MAX_PATH);
			if (::PathFileExists(szDocPath))
			{
				::ShellExecuteW(NULL,L"open",szDocPath,NULL,NULL,SW_SHOWNORMAL);
			}
		}
		break;

	case GLBMENU_ONLINEHELP:
		{
			SHELLEXECUTEINFOW shelli = { 0 };
			shelli.cbSize = sizeof(SHELLEXECUTEINFOW);
			shelli.fMask = SEE_MASK_FLAG_NO_UI | SEE_MASK_NOCLOSEPROCESS;
			shelli.lpVerb = L"open";
			shelli.lpFile = L"http://hgy413.com/3382.html";
			shelli.nShow = SW_SHOW;
			::ShellExecuteExW(&shelli);
		}
		break;

	default:
		break;
	}
	return DM_ECODE_OK;
}

DMCode DMDesignerWnd::InitFileMenu(DMXmlNode& XmlNode,int idFrom)
{
	DMCode iErr = DM_ECODE_FAIL;
	do 
	{
		if (GLBMENUBTN_ID_FILE != idFrom)
		{
			break;
		}
		
		DMXmlNode XmlItem = XmlNode.InsertChildNode(XML_ITEM);
		XmlItem.SetAttribute(XML_ID,IntToString(g_GlbMenuItem[GLBMENU_NEW-GLBMENU_BASE].id));XmlItem.SetAttribute(XML_TEXT,g_GlbMenuItem[GLBMENU_NEW-GLBMENU_BASE].text);
		XmlItem = XmlNode.InsertChildNode(XML_ITEM);
		XmlItem.SetAttribute(XML_ID,IntToString(g_GlbMenuItem[GLBMENU_SAVE-GLBMENU_BASE].id));XmlItem.SetAttribute(XML_TEXT,g_GlbMenuItem[GLBMENU_SAVE-GLBMENU_BASE].text);XmlItem.SetAttributeInt(XML_BDISABLE,m_pDesignerXml?0:1);
		XmlItem = XmlNode.InsertChildNode(XML_ITEM);
		XmlItem.SetAttribute(XML_ID,IntToString(g_GlbMenuItem[GLBMENU_CLOSE-GLBMENU_BASE].id));XmlItem.SetAttribute(XML_TEXT,g_GlbMenuItem[GLBMENU_CLOSE-GLBMENU_BASE].text);XmlItem.SetAttributeInt(XML_BDISABLE,m_pDesignerXml?0:1);
		XmlItem = XmlNode.InsertChildNode(XML_ITEM);
		XmlItem.SetAttribute(XML_ID,IntToString(g_GlbMenuItem[GLBMENU_EXIT-GLBMENU_BASE].id));XmlItem.SetAttribute(XML_TEXT,g_GlbMenuItem[GLBMENU_EXIT-GLBMENU_BASE].text);
		Init_Debug_XmlBuf(XmlNode);

		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;

}

DMCode DMDesignerWnd::InitEditMenu(DMXmlNode& XmlNode, int idFrom)
{
	DMCode iErr = DM_ECODE_FAIL;
	do
	{
		if (GLBMENUBTN_ID_EDIT != idFrom)
		{
			break;
		}

		DMXmlNode XmlItem = XmlNode.InsertChildNode(XML_ITEM);
		XmlItem.SetAttribute(XML_ID, IntToString(g_GlbMenuItem[GLBMENU_UNDO - GLBMENU_BASE].id)); XmlItem.SetAttribute(XML_TEXT, g_GlbMenuItem[GLBMENU_UNDO - GLBMENU_BASE].text);
		XmlItem.SetAttributeInt(XML_BDISABLE, m_ActionSlotMgr.IsExistPrevSiblingSteps() ? 0 : 1);
		XmlItem = XmlNode.InsertChildNode(XML_ITEM);
		XmlItem.SetAttribute(XML_ID, IntToString(g_GlbMenuItem[GLBMENU_REDO - GLBMENU_BASE].id)); XmlItem.SetAttribute(XML_TEXT, g_GlbMenuItem[GLBMENU_REDO - GLBMENU_BASE].text);
		XmlItem.SetAttributeInt(XML_BDISABLE, m_ActionSlotMgr.IsExistNextSiblingSteps() ? 0 : 1);
		Init_Debug_XmlBuf(XmlNode);

		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}

DMCode DMDesignerWnd::InitViewMenu(DMXmlNode& XmlNode,int idFrom)
{
	DMCode iErr = DM_ECODE_FAIL;
	do 
	{
		if (GLBMENUBTN_ID_VIEW != idFrom)
		{
			break;
		}

		DMXmlNode XmlItem = XmlNode.InsertChildNode(XML_ITEM);
		XmlItem.SetAttribute(XML_ID,IntToString(g_GlbMenuItem[GLBMENU_OPTOBJPROJ-GLBMENU_BASE].id));XmlItem.SetAttribute(XML_TEXT,g_GlbMenuItem[GLBMENU_OPTOBJPROJ-GLBMENU_BASE].text);XmlItem.SetAttributeInt(XML_BDISABLE,m_pDesignerXml?0:1);
		XmlItem = XmlNode.InsertChildNode(XML_ITEM);
		XmlItem.SetAttribute(XML_ID,IntToString(g_GlbMenuItem[GLBMENU_RELOAD-GLBMENU_BASE].id));XmlItem.SetAttribute(XML_TEXT,g_GlbMenuItem[GLBMENU_RELOAD-GLBMENU_BASE].text);XmlItem.SetAttributeInt(XML_BDISABLE,m_pDesignerXml?0:1);
		Init_Debug_XmlBuf(XmlNode);

		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}

DMCode DMDesignerWnd::InitModeMenu(DMXmlNode& XmlNode,int idFrom)
{
	DMCode iErr = DM_ECODE_FAIL;
	do 
	{
		if (GLBMENUBTN_ID_MODE != idFrom)
		{
			break;
		}

		DMXmlNode XmlItem = XmlNode.InsertChildNode(XML_ITEM);
		XmlItem.SetAttribute(XML_ID,IntToString(g_GlbMenuItem[GLBMENU_MOVEMODE-GLBMENU_BASE].id));XmlItem.SetAttribute(XML_TEXT,g_GlbMenuItem[GLBMENU_MOVEMODE-GLBMENU_BASE].text);
		XmlItem = XmlNode.InsertChildNode(XML_ITEM);
		XmlItem.SetAttribute(XML_ID,IntToString(g_GlbMenuItem[GLBMENU_SELMODE-GLBMENU_BASE].id));XmlItem.SetAttribute(XML_TEXT,g_GlbMenuItem[GLBMENU_SELMODE-GLBMENU_BASE].text);
		XmlItem = XmlNode.InsertChildNode(XML_ITEM);
		XmlItem.SetAttribute(XML_ID,IntToString(g_GlbMenuItem[GLBMENU_ADDMODE-GLBMENU_BASE].id));XmlItem.SetAttribute(XML_TEXT,g_GlbMenuItem[GLBMENU_ADDMODE-GLBMENU_BASE].text);
		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}

DMCode DMDesignerWnd::InitHelpMenu(DMXmlNode& XmlNode,int idFrom)
{
	DMCode iErr = DM_ECODE_FAIL;
	do 
	{
		if (GLBMENUBTN_ID_HELP != idFrom)
		{
			break;
		}

		DMXmlNode XmlItem = XmlNode.InsertChildNode(XML_ITEM);
		XmlItem.SetAttribute(XML_ID,IntToString(g_GlbMenuItem[GLBMENU_HELPDOC-GLBMENU_BASE].id));XmlItem.SetAttribute(XML_TEXT,g_GlbMenuItem[GLBMENU_HELPDOC-GLBMENU_BASE].text);
		XmlItem = XmlNode.InsertChildNode(XML_ITEM);
		XmlItem.SetAttribute(XML_ID,IntToString(g_GlbMenuItem[GLBMENU_ONLINEHELP-GLBMENU_BASE].id));XmlItem.SetAttribute(XML_TEXT,g_GlbMenuItem[GLBMENU_ONLINEHELP-GLBMENU_BASE].text);
		Init_Debug_XmlBuf(XmlNode);

		iErr = DM_ECODE_OK;
	} while (false);
	return iErr;
}

DMCode DMDesignerWnd::OpenNewProj()
{
	DMSmartPtrT<NewResDlg> pDlg;
	pDlg.Attach(new NewResDlg());
	if (IDOK == pDlg->DoModal(L"ds_newdlg",m_hWnd,true))
	{
		OnParseRes(pDlg->m_strResDir);
	}
	return DM_ECODE_OK;
}

DMCode DMDesignerWnd::CloseProj()
{
	if (m_pDesignerXml&&m_pDesignerXml->IsNeedSave())
	{
		m_pDesignerXml->SaveRes(false);
	}
	DM_DELETE(m_pDesignerXml);
	FindChildByNameT<DUIStatic>(L"ds_resdirsta")->DV_SetWindowText(L"ctrl+n������б����קRes�ļ�����");
	return DM_ECODE_OK;
}

DMCode DMDesignerWnd::OptionObjProj()
{
	if (m_pDesignerXml)
	{
		if (m_pDesignerXml->m_bInitObjTree)
		{
			if (IDOK == DM_MessageBox(L"ȷ�Ϲرն�����ͼ?\r\n",MB_OKCANCEL))
			{
				m_ActionSlotMgr.FreeAllActionSlot();//ȥ�����ж������
				m_pDesignerXml->ReleaseObjTree();
			}
		}
		else
		{
			if (IDOK == DM_MessageBox(L"ȷ�ϼ��ض�����ͼ?\r\n",MB_OKCANCEL))
			{
				m_pDesignerXml->InitObjTree();
			}
		}
	}
	return DM_ECODE_OK;
}

DMCode DMDesignerWnd::ReloadProj()
{
	if (m_pDesignerXml)
	{
		bool bInitObj = m_pDesignerXml->m_bInitObjTree;
		OnParseRes(m_pDesignerXml->m_strResDir);

		if (bInitObj)
		{
			m_pDesignerXml->InitObjTree();
		}
	}
   return DM_ECODE_OK;
}










