#include "DmMainAfx.h"
#include "DUISkinPool.h"

namespace DM
{
	DMSkinPoolItem::~DMSkinPoolItem()
	{
		RemoveAll();
	}

	void DMSkinPoolItem::PreMapKeyRemove(const IDMSkinPtr &obj)
	{
		obj->Release();
	}

	// ------------------------------DUISkinPool
	DUISkinPool::~DUISkinPool()
	{
		RemoveAll();
	}

	DMCode DUISkinPool::AddSkinPoolItem(DMXmlNode &XmlNode)
	{
		DMCode iErr = DM_ECODE_FAIL;
		DMSkinPoolItemPtr pItem = NULL;
		do 
		{
			if (!XmlNode.IsValid())
			{
				break;
			}

			CStringW strName = XmlNode.Attribute(L"name");strName.MakeLower();
			bool bExist = true;
			if (false == GetObjByKey(strName, pItem))
			{
				bExist  = false;
				pItem   = new DMSkinPoolItem;
			}

			DMXmlNode XmlSkin = XmlNode.FirstChild();
			while (XmlSkin.IsValid())
			{
				CStringW strId = XmlSkin.Attribute(L"id");strId.MakeLower();
				if (strId.IsEmpty())
				{
					CStringW szInfo; 
					XmlSkin.GetXmlContent(szInfo);
					szInfo += L"(skin)δ����id,���Զ�����";
					DMASSERT_EXPR(0, szInfo);
				}
				else
				{
					if (!pItem->IsKeyExist(strId))
					{// key������ʱ�ż���
						LPCWSTR lpszClassName = XmlSkin.GetName();  
						IDMSkinPtr pSkinPtr = NULL;
						if (DMSUCCEEDED(g_pDMApp->CreateRegObj((void**)&pSkinPtr,lpszClassName,DMREG_Skin)))
						{
							pSkinPtr->InitDMData(XmlSkin);
							if (!DMSUCCEEDED(pSkinPtr->IsValid()))
							{
								CStringW szInfo = lpszClassName;
								szInfo += L"(skin)��Ч��,���Զ��Ƴ�";
								DMASSERT_EXPR(0, szInfo);
								pSkinPtr->Release();
							}
							else
							{
								pItem->AddKey(strId,pSkinPtr);
							}
						}
						else
						{
							CStringW szInfo = lpszClassName;
							szInfo += L"(skinpool)�����޷�������,��鿴�Ƿ�д��";
							DMASSERT_EXPR(0, szInfo);
						}
					}
				}
				XmlSkin = XmlSkin.NextSibling();
			}

			if (false == bExist)
			{
				AddKey(strName,pItem);
			}
			iErr = DM_ECODE_OK;
		} while (false);
		return iErr;
	}

	DMCode DUISkinPool::RemoveSkinPoolItem(LPCWSTR lpszName)
	{
		CStringW szKey = lpszName;szKey.MakeLower();
		RemoveKey(szKey);
		return DM_ECODE_OK;
	}

	DMCode DUISkinPool::RemoveAllSkinPoolItemExcept(LPCWSTR lpszName)
	{
		DMSkinPoolItemPtr pItem = NULL;
		CStringW strKey = lpszName;strKey.MakeLower();
		if (GetObjByKey(strKey, pItem))
		{
			pItem->AddRef();// ��ֹ��ɾ��
		}
		RemoveAll();// �˴�pItem��1,�������ͷ� 
		if (pItem)
		{
			AddKey(strKey,pItem);
		}
		return DM_ECODE_OK;
	}

	DMCode DUISkinPool::UpdateSkin(WPARAM wp, LPARAM lp)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			LPCWSTR lpSrc = (LPCWSTR)wp;
			int nLen = (int)lp;
			if (NULL == lpSrc||0>=nLen)
			{
				break;
			}

			wchar_t *pBuf = new wchar_t[nLen];
			memcpy(pBuf,lpSrc,nLen*2);
			CStringW strValue = pBuf;
			CStringWList strUpdateList;
			int nCount = (int)SplitStringT(strValue,L';',strUpdateList);
			// 1. ������������µ�skin
			m_UpdateSkinArray.RemoveAll();
			for (int i=0;i<nCount;i++)
			{
				LPCWSTR lpszUpdate = strUpdateList[i];
				POSITION pos = m_Map.GetStartPosition();
				while (pos)
				{
					DM::CMap<CStringW,DMSkinPoolItemPtr>::CPair *p = m_Map.GetNext(pos);
					DMSkinPoolItemPtr &pCur = p->m_value;
					POSITION poscur = pCur->m_Map.GetStartPosition();
					while(poscur)
					{
						DM::CMap<CStringW,IDMSkinPtr>::CPair *pcur = pCur->m_Map.GetNext(poscur);
						IDMSkinPtr &pTemp = pcur->m_value;
						if (DMSUCCEEDED(pTemp->UpdateSkin((WPARAM)lpszUpdate,0)))
						{
							m_UpdateSkinArray.Add(pTemp);
						}
					}
				}
			}
			// 2.֪ͨ����ʹ����Щskin��DUI����ˢ���Լ�����
			iErr = g_pDMDWndPool->UpdateSkin(0,DMREG_Skin);
			DM_DELETE_ARRAY(pBuf);
		} while (false);
		return iErr;
	}

	bool DUISkinPool::IsNeedUpdateSkin(IDMSkinPtr pSkin)
	{
		bool bRet = false;
		do 
		{
			int nCount = (int)m_UpdateSkinArray.GetCount();
			for (int i=0;i<nCount;i++)
			{
				if (pSkin == m_UpdateSkinArray[i])
				{
					bRet = true;
					break;// ����
				}
			}
		} while (false);
		return bRet;
	}

	DMCode DUISkinPool::ClearUpdateSkinArray()
	{
		m_UpdateSkinArray.RemoveAll();
		return DM_ECODE_OK;
	}

	DMCode DUISkinPool::AddSkin(void *pBuf,size_t bufLen,LPCWSTR pszType,
		LPCWSTR lpszXml,LPCWSTR lpszPoolName/*=NULL*/)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			if (NULL == pBuf
				||0>=bufLen
				||NULL == lpszXml)
			{
				break;
			}

			//1. ����xml����L"<imglist id=\"1\" states=\"1\" />";
			CStringW strWXml(lpszXml);
			CStringA strXml = DMW2A(strWXml,CP_UTF8);
			DMXmlDocument doc;
			if (false == doc.LoadFromBuffer((const PVOID)(LPCSTR)strXml, strXml.GetLength()))
			{
				break;
			}
			DMXmlNode XmlNode = doc.Root();
			if (!XmlNode.IsValid())
			{
				break;
			}

			//2.�ж�skin��id�Ƿ�Ϊ��
			CStringW strId = XmlNode.Attribute(L"id");strId.MakeLower();
			if (strId.IsEmpty())
			{
				CStringW szInfo; 
				XmlNode.GetXmlContent(szInfo);
				szInfo += L"(skin)δ����id,���Զ�����";
				DMASSERT_EXPR(0, szInfo);
				break;
			}

			//3.�ж�skin��id�Ƿ����
			if (FindSkinFromAll(strId))				// Ĭ�ϴ�����skin���в���
			{
				CStringW szInfo = strId;
				szInfo += L"(skinpool)��skin���Ѵ���";
				DMASSERT_EXPR(0, szInfo);
				break;// �����Ѵ���
			}

			//4.����skin����
			LPCWSTR lpszClassName = XmlNode.GetName();
			IDMSkinPtr pSkinPtr = NULL;
			if (!DMSUCCEEDED(g_pDMApp->CreateRegObj((void**)&pSkinPtr,lpszClassName,DMREG_Skin)))
			{
				CStringW szInfo = lpszClassName;
				szInfo += L"(skinpool)�����޷�������,��鿴�Ƿ�д��";
				DMASSERT_EXPR(0, szInfo);
				break;
			}
			pSkinPtr->InitDMData(XmlNode);

			//5.��ʼ��skin��ͼԪ
			CStringW strType = (NULL==pszType)?L"png":pszType;
			if (!DMSUCCEEDED(pSkinPtr->SetBitmap((LPBYTE)pBuf,bufLen,strType)))
			{
				pSkinPtr->Release();
				break;
			}

			//6.�ж�skinpool�Ƿ���ڣ��������򴴽�����
			bool bExist = true;
			CStringW strName = lpszPoolName;strName.MakeLower();
			DMSkinPoolItemPtr pItem = NULL;
			if (false == GetObjByKey(strName, pItem))
			{
				bExist  = false;
				pItem   = new DMSkinPoolItem;
			}
			
			pItem->AddKey(strId,pSkinPtr);
			if (false == bExist)
			{
				AddKey(strName,pItem);
			}
			iErr = DM_ECODE_OK;
		} while (false);
		return iErr;
	}

	DMCode DUISkinPool::RemoveSkin(LPCWSTR lpszKey,LPCWSTR lpszName,bool bLoopFind /*= true*/)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			if (NULL == lpszKey||wcslen(lpszKey)<=0)
			{
				break;
			}

			DMSkinPoolItemPtr pCur = NULL;
			CStringW strName = lpszName;strName.MakeLower();
			CStringW strKey = lpszKey;  strKey.MakeLower();
			if (false == GetObjByKey(strName, pCur))
			{
				if (bLoopFind)
				{
					iErr = RemoveSkinFromAll(strKey);
				}
				break;
			}
			else
			{
				if (!pCur->RemoveKey(strKey))
				{
					if (bLoopFind)
					{
						iErr = RemoveSkinFromAll(strKey);
					}
					break;
				}
			}
			iErr = DM_ECODE_OK;
		} while (false);
		return iErr;
	}

	DMCode DUISkinPool::RemoveSkinFromAll(LPCWSTR lpszKey)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			if (NULL == lpszKey||wcslen(lpszKey)<=0)
			{
				break;
			}
			CStringW strKey = lpszKey;strKey.MakeLower();
			POSITION pos = m_Map.GetStartPosition();
			while (pos)
			{
				DM::CMap<CStringW,DMSkinPoolItemPtr>::CPair *p = m_Map.GetNext(pos);
				DMSkinPoolItemPtr &pCur = p->m_value;
				if (pCur->RemoveKey(strKey))
				{
					iErr = DM_ECODE_OK;
				}
			}
		} while (false);
		return iErr;
	}

	IDMSkinPtr DUISkinPool::FindSkin(LPCWSTR lpszKey,LPCWSTR lpszName,bool bLoopFind)
	{
		IDMSkinPtr  pSkin = NULL;
		do 
		{
			if (NULL == lpszKey||wcslen(lpszKey)<=0)
			{
				break;
			}

			DMSkinPoolItemPtr pCur = NULL;
			CStringW strName = lpszName;strName.MakeLower();
			CStringW strKey = lpszKey;  strKey.MakeLower();
			if (false == GetObjByKey(strName, pCur))
			{
				if (bLoopFind)
				{
					pSkin = FindSkinFromAll(strKey);
				}
				break;
			}
			else
			{
				if (pCur->GetObjByKey(strKey,pSkin))
				{
					break;// ���ҵ�
				}

				if (bLoopFind)
				{
					pSkin = FindSkinFromAll(strKey);
				}
			}
		} while (false);
		return pSkin;
	}

	IDMSkinPtr DUISkinPool::FindSkin(LPCWSTR lpszBuf,bool bLoopFind/* = true*/)
	{
		IDMSkinPtr  pSkin = NULL;
		do 
		{
			if (NULL == lpszBuf||wcslen(lpszBuf)<=0)
			{
				break;
			}

			CStringW strValue = lpszBuf;
			CStringWList strList;
			CStringW strName;
			CStringW strKey;
			int nCount = (int)SplitStringT(strValue,L':',strList);
			if (1==nCount)
			{
				strKey = strValue;
			}
			else if (2 == nCount)
			{
				strName = strList[0];
				strKey  = strList[1];
			}
			else
			{
				CStringW strInfo;
				strInfo.Format(L"skin-%s���ô���",strValue);
				DMASSERT_EXPR(0,strInfo);
				break;
			}

			pSkin = FindSkin(strKey,strName,bLoopFind);
		} while (false);
		return pSkin;
	}

	IDMSkinPtr DUISkinPool::FindSkinFromAll(LPCWSTR lpszKey)
	{
		IDMSkinPtr  pSkin = NULL;
		do 
		{
			if (NULL == lpszKey||wcslen(lpszKey)<=0)
			{
				break;
			}

			CStringW strKey = lpszKey;strKey.MakeLower();
			POSITION pos = m_Map.GetStartPosition();
			while (pos)
			{
				DM::CMap<CStringW,DMSkinPoolItemPtr>::CPair *p = m_Map.GetNext(pos);
				DMSkinPoolItemPtr &pCur = p->m_value;
				if (pCur->GetObjByKey(strKey,pSkin))
				{
					break;
				}
			}
		} while (false);
		return pSkin;
	}

	void DUISkinPool::PreMapKeyRemove(const DMSkinPoolItemPtr &obj)
	{
		obj->Release();
	}

}//namespace DM