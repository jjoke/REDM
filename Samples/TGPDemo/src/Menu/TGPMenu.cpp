#include "TGPDemoAfx.h"
#include "TGPMenu.h"

namespace DM
{
	void TGPMenuItem::OnRelease()
	{
		delete this;// �ⲿnew�Ķ���TGPMenu::NewMenuItem()��,�����ⲿ�ͷ�
	}

	void TGPMenuItem::DrawOwnerItem(IDMCanvas* pCanvas, CRect& rcItem, MENUITEMINFO &mii)
	{
		do 
		{
			__super::DrawOwnerItem(pCanvas,rcItem,mii);
			// TGP�¼ӻ���,���������������ƣ�����ֱ�Ӱ�__super::DrawOwnerItem copy���������м����
			TGPMenuItemData *pdmmi = (TGPMenuItemData*)mii.dwItemData;
			if (pdmmi
				&&pdmmi->bHold
				&&pdmmi->pHoldSkin)
			{
				pdmmi->pHoldSkin->Draw(pCanvas,rcItem, pdmmi->bSel);
			}
		} while (false);
	}

	LRESULT TGPMenuItem::MenuProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (NULL != m_hMenu && 
			(MN_BUTTONUP == uMsg || MN_DBLCLK == uMsg))
		{
			return On_MN_BUTTON(hWnd,uMsg,wParam,lParam);
		}
		return __super::MenuProc(hWnd,uMsg,wParam,lParam);
	}

	LRESULT TGPMenuItem::On_MN_BUTTON(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		MENUITEMINFO mii;
		::ZeroMemory(&mii,sizeof(MENUITEMINFO));
		mii.cbSize = sizeof(MENUITEMINFO);
		mii.fMask  = MIIM_FTYPE | MIIM_DATA | MIIM_STATE | MIIM_STRING | MIIM_ID | MIIM_BITMAP | MIIM_SUBMENU | MIIM_BITMAP | MIIM_CHECKMARKS;
		if (0 == ::GetMenuItemInfo(m_hMenu, (UINT)wParam, MF_BYPOSITION, &mii))
		{
			return ::CallWindowProc(m_pOldProc, hWnd, MN_BUTTONUP, wParam, lParam);
		}

		TGPMenuItemData *pdmmi = (TGPMenuItemData*)mii.dwItemData;
		if (pdmmi->bHold&&pdmmi->pHoldSkin)
		{
			pdmmi->bSel = !pdmmi->bSel;
			// �����﷢�Զ�����Ϣ��TGPMainWnd��
			if (m_hMenuOwner&&::IsWindow(m_hMenuOwner))
			{
				::PostMessage(m_hMenuOwner,WM_USER+1010,pdmmi->nID,NULL);
			}
			Render();//����͵���ˣ�ǿ��ˢ�������˵�,����԰Ѳ˵���ָ�����ˢ��
			return 0;//0��ʾ���˳��˵�
		}

		return ::CallWindowProc(m_pOldProc, hWnd, uMsg, wParam, lParam);;
	}

	// ------------------------TGPMenu----------------------------
	TGPMenu::~TGPMenu()
	{
		UnInstallMenuHook();
		DestroyMenu();/// �˴�������ã������ߵ�TGPMenu::DeleteMenuItemData
	} 

	DMMenuItemData* TGPMenu::ParseItem(DMXmlNode& XmlItem)
	{
		TGPMenuItemData* pdmmi = (TGPMenuItemData*)__super::ParseItem(XmlItem);
		if (pdmmi)
		{
			// ������չ��MENU
			pdmmi->pHoldSkin = g_pDMApp->GetSkin(XmlItem.Attribute(DMAttr::TGPMenuAttr::ITEM_holdskin));
			pdmmi->bHold = pdmmi->bSel = false;
			DMAttributeDispatch::ParseBool(XmlItem.Attribute(DMAttr::TGPMenuAttr::ITEM_bhold),pdmmi->bHold);
			DMAttributeDispatch::ParseBool(XmlItem.Attribute(DMAttr::TGPMenuAttr::ITEM_bsel),pdmmi->bSel);
			return (DMMenuItemData*)pdmmi;
		}
		return NULL;
	}

	DMMenuItemData* TGPMenu::NewMenuItemData()
	{
		return new TGPMenuItemData();
	}

	void TGPMenu::DeleteMenuItemData(DMMenuItemData*pObj)
	{
		delete (TGPMenuItemData*)pObj;
	}

	DUIMenuItem* TGPMenu::NewMenuItem()
	{
		return new TGPMenuItem();
	}




}//namespace DM