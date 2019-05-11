#include "DmMainAfx.h"
#include "DMResFolderImpl.h"

namespace DM
{
	///
	DMResFolderImpl::DMResFolderImpl()
	{
		m_bThemeLoop = true;
		m_pCurTheme  = NULL;
		m_bOutStyle  = false;
	}

	DMResFolderImpl::~DMResFolderImpl()
	{
		RemoveAll();
	}

	DMCode DMResFolderImpl::LoadResPack(WPARAM wp, LPARAM lp)
	{
		DMCode iErr = DM_ECODE_OK;
		do 
		{
			if (0 == wp||IsBadReadPtr((void*)wp,4))
			{
				break;
			}

			LPWSTR lpszPath = (LPWSTR)wp;
			wchar_t szPath[MAX_PATH] = {0};
			if (!GetRootFullPath(lpszPath,szPath,MAX_PATH))
			{
				break;
			}
			m_strDir = szPath;// ��ʼ����Դ��λ��
		
			DM::CStringW strLayoutPathIndex = szPath;DM::CStringW strThemesPathIndex = szPath;
			strLayoutPathIndex += DMRES_LAYOUT_FOLDER;strLayoutPathIndex += DMRES_DMINDEX;
			strThemesPathIndex += DMRES_THEMES_FOLDER;strThemesPathIndex += DMRES_DMINDEX;
			LPCWSTR lpszLayoutPathIndex = strLayoutPathIndex;
			if (!CheckFileExistW((wchar_t*)lpszLayoutPathIndex))
			{
				CStringW szErrInfo = strLayoutPathIndex;szErrInfo+=L"�ļ�������";
				DMASSERT_EXPR(0, szErrInfo);
				iErr = DM_ECODE_FAIL;
				break;
			}

			m_pLayout.Release();// ���ͷ�ԭʼ�������-----------��
			m_pCurTheme = NULL; // ��ǰʹ�õ�������ÿ�---------��
			RemoveAll();		// ���ͷ�ԭʼthemes-------------��
			
			// ����Layout
			m_pLayout.Attach(new DMResFolderItem);
			iErr = ParseIndex(lpszLayoutPathIndex, &m_pLayout);

			// ����themes
			LPCWSTR lpszThemesPathIndex = strThemesPathIndex;
			iErr = ParseThemes(lpszThemesPathIndex);
		} while (false);
		return iErr;
	}

	DMCode DMResFolderImpl::IsItemExists(LPCWSTR lpszType, LPCWSTR lpszName,LPCWSTR lpszThemeName)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			if (NULL == lpszType||NULL == lpszName)
			{
				break;
			}
			DMResItem Item(lpszType, lpszName);// ����������EqualArrayObj��ֻҪǰ����������ȣ�����Ϊ�Ѵ���
			if (0 == _wcsicmp(lpszType, RES_LAYOUT)||0 == _wcsicmp(lpszType, RES_GLOBAL))
			{
				if (NULL == m_pLayout || DM_INVALID_VALUE == m_pLayout->FindObj(&Item))
				{
					break;
				}
			}
			else
			{
				DMResFolderItemPtr pTheme = FindResItemObj(lpszThemeName);
				if (pTheme && DM_INVALID_VALUE == pTheme->FindObj(&Item))
				{
					if (false == m_bThemeLoop)
					{
						break;
					}
					bool bFind = false;// ������themes�в���
					int nCount = (int)GetCount();
					for (int i=0;i<nCount;i++)
					{
						DMResFolderItemPtr &pCur = GetObj(i);
						if (pCur && DM_INVALID_VALUE !=pCur->FindObj(&Item))
						{
							bFind = true;
							break;
						}
					}
					if (false == bFind)
					{
						break;
					}
				}
				else if(NULL == pTheme)
				{
					break;
				}
			}
			iErr = DM_ECODE_OK;
		} while (false);
		return iErr;
	}

	DMCode DMResFolderImpl::GetItemSize(LPCWSTR lpszType, LPCWSTR lpszName, unsigned long& ulSize,LPCWSTR lpszThemeName)
	{
		DMCode iErr = DM_ECODE_OK;
		size_t size = 0;
		do 
		{
			LPCWSTR lpszFilePath = GetItemPath(lpszType, lpszName,lpszThemeName);
			if (NULL == lpszFilePath) 
			{
				iErr = DM_ECODE_FAIL;
				break;
			}

			size = DM::GetFileSizeW((wchar_t*)lpszFilePath);
			if (0 == size)
			{
				iErr = DM_ECODE_FAIL;
				break;
			}
			ulSize = (unsigned long)size;
		} while (false);
		if (!DMSUCCEEDED(iErr)&&m_bAssert)
		{
			CStringW strInfo;
			strInfo.Format(L"Res��Դ��%s:%s��ȡsizeʧ��",lpszType,lpszName);
			DMASSERT_EXPR(0,strInfo);
		}
		return iErr;
	}

	DMCode DMResFolderImpl::GetItemBuf(LPCWSTR lpszType, LPCWSTR lpszName, LPVOID lpBuf, unsigned long ulSize,LPCWSTR lpszThemeName)
	{
		DMCode iErr = DM_ECODE_OK;
		do 
		{
			LPCWSTR lpszFilePath = GetItemPath(lpszType, lpszName,lpszThemeName);
			if (NULL == lpszFilePath) 
			{
				iErr = DM_ECODE_FAIL;
				break;
			}

			DWORD dwReadSize = 0;
			if (false == DM::GetFileBufW((wchar_t*)lpszFilePath, &lpBuf, ulSize, dwReadSize))
			{
				iErr = DM_ECODE_FAIL;
				break;
			}
		} while (false);
		if (!DMSUCCEEDED(iErr)&&m_bAssert)
		{
			CStringW strInfo;
			strInfo.Format(L"Res��Դ��%s:%s��ȡbufʧ��",lpszType,lpszName);
			DMASSERT_EXPR(0,strInfo);
		}
		return iErr;
	}

	DMCode DMResFolderImpl::LoadTheme(WPARAM wp, LPARAM lp)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			if (0 == wp||IsBadReadPtr((void*)wp,4)||0 == lp||IsBadReadPtr((void*)lp,4))
			{
				break;
			}
			LPCWSTR lpszName = (LPCWSTR)wp;
			LPWSTR lpszFilePath = (LPWSTR)lp;
			wchar_t szPath[MAX_PATH] = {0};
			if (!GetRootFullPath(lpszFilePath,szPath,MAX_PATH))
			{
				break;
			}
		
			DMResFolderItemPtr pItem = new DMResFolderItem;
			if (!DMSUCCEEDED(ParseIndex(szPath,&pItem)))
			{
				pItem->Release();
				break;
			}
			pItem->m_strThemeName = lpszName;
			if (AddObj(pItem))
			{
				iErr = DM_ECODE_OK;
			}
			else
			{
				CStringW szInfo = lpszName;
				szInfo += L"������Ѵ���,�������ԣ�";
				DMASSERT_EXPR(0,szInfo);
				pItem->Release();
			}
		} while (false);
		return iErr;
	}

	DMCode DMResFolderImpl::SetCurTheme(LPCWSTR lpszName, LPCWSTR lpszOldName)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{	
			if (lpszOldName)
			{// �����ɵ�theme����,���۳ɹ���񣬶���ȡ��
				memcpy((void*)lpszOldName,m_strCurTheme,m_strCurTheme.GetLength()*2);
			}

			DMResFolderItemPtr pCurTheme=NULL;
			CStringW strName = lpszName;
			if (strName == m_strCurTheme// Ҫ���õĺ͵�ǰ����ͬ
				&&NULL != m_pCurTheme&&!m_bOutStyle)
			{
				iErr = DM_ECODE_OK;
				break;
			}

			pCurTheme = FindResItemObj(lpszName);
			if (NULL == pCurTheme)
			{
				break;
			}
			DMResFolderItemPtr	pOldTheme = m_pCurTheme;  
			m_pCurTheme = pCurTheme;
			m_strCurTheme = strName;
			// 1.�Ƚ�����themes֮ǰ��index�Ĳ����ȫ��ͬ����Ϊ��Ҫ���£�����Ҫ���µ�type+name
			int nCount    = (int)m_pCurTheme->GetCount();
			int nCmpCount = (int)pOldTheme->GetCount();
			if (m_bOutStyle||NULL == pOldTheme)
			{
				nCmpCount = 0;// �ⲿģʽ��Ӧ��Ҫ�������е�theme,����ֱ�ӰѱȽ�������Ϊ0
			}
			bool bFind = false;// �Ƿ����ǰthemesһ��
			CStringW strUpdateInfo;
			for (int i=0;i<nCount;i++)
			{
				DMResItemPtr &pItem = m_pCurTheme->m_DMArray[i];
				for (int j=0;j<nCmpCount;j++)
				{
					bFind = false;// ��Ԥ��Ϊfalse
					DMResItemPtr &pCmpItem = pOldTheme->m_DMArray[j];
					if (0 == _wcsicmp(pItem->m_szName,pCmpItem->m_szName)
						&&0 == _wcsicmp(pItem->m_szType,pCmpItem->m_szType))
					{
						if (0 == _wcsicmp(pItem->m_szPath,pCmpItem->m_szPath))
						{
							bFind = true;
						}
						break;// ������ѭ��
					}
				}
				if (false == bFind)
				{
					strUpdateInfo += pItem->m_szType;
					strUpdateInfo += L':';
					strUpdateInfo += pItem->m_szName;
					strUpdateInfo += L';';
				}
			}
			// TODO.��ʼ�㲥��Ϣ������Skin--
			int nLen = strUpdateInfo.GetLength()+1;
			DMBufT<wchar_t>pBuf;pBuf.Allocate(nLen);
			memcpy(pBuf,strUpdateInfo.GetBuffer(),(nLen-1)*2);
			strUpdateInfo.ReleaseBuffer();
			g_pDMApp->UpdateSkin((WPARAM)pBuf.get(),(LPARAM)nLen);
			m_bOutStyle = false;// �������ⲿģʽ��
			iErr = DM_ECODE_OK;
		} while (false);
		return iErr;
	}

	DMCode DMResFolderImpl::SendExpandInfo(WPARAM wp, LPARAM lp)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			CStringW strAllTheme;
			int nCount = (int)GetCount();
			for (int i=0; i<nCount; i++)
			{
				DMResFolderItemPtr &pCur = GetObj(i);
				CStringW strTheme = pCur->m_strThemeName;
				strTheme += L";";
				strAllTheme += strTheme;
			}
			int nSize = 2*(strAllTheme.GetLength()+1);
			if (wp&&NULL==lp)
			{
				if (!IsBadReadPtr((void*)wp,4))
				{
					*(DWORD*)wp  = nSize;
				}
			}
			else if(wp&&lp>=nSize)
			{
				if (!IsBadReadPtr((void*)wp,4))
				{
					memcpy((void*)wp,strAllTheme.GetBuffer(),nSize);
				}
			}
			iErr = DM_ECODE_OK;
		} while (false);
		return iErr;
	}

	// ����
	DMCode DMResFolderImpl::ParseThemes(LPCWSTR lpszIndexPath)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			DMXmlDocument XmlDoc;
			if (false == XmlDoc.LoadFromFile(lpszIndexPath))
			{
				break;
			}

			DMXmlNode XmlNode = XmlDoc.Root();
			if (false == XmlNode.IsValid())
			{
				break;
			}

			XmlNode = XmlNode.FirstChild();
			while (XmlNode.IsValid())
			{
				InitDMData(XmlNode);// ʹ��xml�����滻
				DMXmlNode XmlFileNode = XmlNode.FirstChild(L"file");
				while (XmlFileNode.IsValid())
				{
					LPCWSTR lpszName = XmlFileNode.Attribute(L"name");
					LPCWSTR lpszFilePath = XmlFileNode.Attribute(L"path");
					wchar_t szPath[MAX_PATH] = {0};
					if (0 != PathCombineW(szPath, m_strDir, lpszFilePath))
					{
						DMResFolderItemPtr pItem = new DMResFolderItem;
						if (DMSUCCEEDED(ParseIndex(szPath,&pItem)))
						{
							pItem->m_strThemeName = lpszName;
							if (false == AddObj(pItem))
							{
								CStringW szInfo = lpszName;
								szInfo += L"������Ѵ���,�������ԣ�";
								DMASSERT_EXPR(0,szInfo);
								pItem->Release();
							}
						}
						else
						{
							pItem->Release();
						}
					}
					XmlFileNode = XmlFileNode.NextSibling(L"file");
				}
				XmlNode = XmlNode.NextSibling();
			}

			// ��ʼ����ǰʹ�õ�theme
			if ((int)GetCount()>=1)
			{
				m_pCurTheme = FindResItemObj(m_strCurTheme);
				if (NULL == m_pCurTheme)
				{
					m_pCurTheme = GetObj(0);
					m_strCurTheme = m_pCurTheme->m_strThemeName;
				}	
			}
			DMASSERT_EXPR(NULL!=m_pCurTheme,L"m_pCurTheme��ȻΪ�գ�������");
			iErr = DM_ECODE_OK;
		} while (false);
		return iErr;
	}

	DMCode DMResFolderImpl::ParseIndex(LPCWSTR lpszIndexPath,DMResFolderItem** ppItem)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			if (NULL == lpszIndexPath||NULL == ppItem)
			{
				break;
			}
	
			DMXmlDocument XmlDoc;
			if (false == XmlDoc.LoadFromFile(lpszIndexPath))
			{
				CStringW strInfo;
				strInfo.Format(L"xml LoadFromFile:%s fail",lpszIndexPath);
				DMASSERT_EXPR(0,strInfo);
				LOG_ERR("[mid]-xml LoadFromFile:%s fail\n",lpszIndexPath);
				break;
			}

			DMXmlNode XmlNode = XmlDoc.Root();
			if (false == XmlNode.IsValid())
			{
				LOG_ERR("[mid]-xmlnode inValid\n");
				break;
			}

			XmlNode = XmlNode.FirstChild();
			while (XmlNode.IsValid())
			{
				LPCWSTR lpszType = XmlNode.GetName();
				DMXmlNode XmlFileNode = XmlNode.FirstChild(L"file");
				while (XmlFileNode.IsValid())
				{
					LPCWSTR lpszName = XmlFileNode.Attribute(L"name");
					LPCWSTR lpszFilePath = XmlFileNode.Attribute(L"path");
					if (NULL!=lpszFilePath&&0!=wcslen(lpszFilePath))
					{
						wchar_t szPath[MAX_PATH] = {0};
						if (0 != PathCombineW(szPath, m_strDir, lpszFilePath))
						{
#if defined(_DEBUG)
							if (!CheckFileExistW(szPath))
							{
								CStringW szInfo = szPath;szInfo+=L"�ļ������ڣ�";
								DMASSERT_EXPR(0,szInfo);
							}
#endif 
							DMResItem *pResItem = new DMResItem(lpszType,lpszName,szPath);
							(*ppItem)->AddObj(pResItem);// ����DMArrayT
						}
					}
					XmlFileNode = XmlFileNode.NextSibling(L"file");
				}

				XmlNode = XmlNode.NextSibling();
			}

			(*ppItem)->m_DMArray;//������DEBUG�鿴m_Array�ĵط�,watchһ�¾ͺ���
			iErr = DM_ECODE_OK;
		} while (false);
		return iErr;
	}

	LPCWSTR DMResFolderImpl::GetItemPath(LPCWSTR lpszType,LPCWSTR lpszName,LPCWSTR lpszThemeName)
	{
		LPCWSTR lpszPath = NULL;
		do 
		{
			if (NULL == lpszType||NULL == lpszName)
			{
				break;
			}
			DMResItem Item(lpszType, lpszName);// ����������EqualArrayObj��ֻҪǰ����������ȣ�����Ϊ�Ѵ���
			if (0 == _wcsicmp(lpszType, RES_LAYOUT)||0 == _wcsicmp(lpszType, RES_GLOBAL))
			{
				if (NULL == m_pLayout)
				{
					break;
				}
				int iElement = m_pLayout->FindObj(&Item);
				if (DM_INVALID_VALUE == iElement)
				{
					break;
				}
				lpszPath = m_pLayout->GetObj(iElement)->m_szPath;
			}
			else
			{
				DMResFolderItemPtr pTheme = FindResItemObj(lpszThemeName);
				if (NULL==pTheme)
				{
					break;
				}
				int iElement = pTheme->FindObj(&Item);
				if (DM_INVALID_VALUE == iElement)
				{
					if (false == m_bThemeLoop)
					{
						break;
					}
					bool bFind = false;// ������themes�в���
					int nCount = (int)GetCount();
					for (int i=0;i<nCount;i++)
					{
						DMResFolderItemPtr &pCur = GetObj(i);
						if (pCur)
						{
							iElement = pCur->FindObj(&Item);
							if (DM_INVALID_VALUE != iElement)
							{
								bFind = true;
								lpszPath = pCur->GetObj(iElement)->m_szPath;
								break;
							}
						}
					}
					if (false == bFind)
					{
						break;
					}
				}
				else
				{
					lpszPath = pTheme->GetObj(iElement)->m_szPath;
				}
			}

		} while (false);
		return lpszPath;
	}

	DMResFolderItemPtr DMResFolderImpl::FindResItemObj(LPCWSTR lpszName)
	{
		DMResFolderItemPtr pFindItem = NULL;
		do 
		{
			if (NULL == lpszName)
			{
				pFindItem = m_pCurTheme;
				break;
			}

			int nCount = (int)GetCount();
			for (int i=0; i<nCount; i++)
			{
				DMResFolderItemPtr &pItem = GetObj(i);
				if (pItem&&0==pItem->m_strThemeName.CompareNoCase(lpszName))
				{
					pFindItem = pItem;
					break;
				}
			}
		} while (false);
		return pFindItem;
	}

	void DMResFolderImpl::PreArrayObjRemove(const DMResFolderItemPtr &obj)
	{
		obj->Release(); // �����ü���Ϊ0�����Զ�delete this
	}

}//namespace DM