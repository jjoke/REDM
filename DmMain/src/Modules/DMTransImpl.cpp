#include "DmMainAfx.h"
#include "DMTransImpl.h"

namespace DM
{
	DMTransImpl::DMTransImpl()
	{
		m_pCurLanguage = NULL;
	}

	DMTransImpl::~DMTransImpl()
	{
		RemoveAll();
	}

	DMCode DMTransImpl::LoadTrans(WPARAM wp, LPARAM lp)
	{
		DMCode iErr = DM_ECODE_OK;
		do 
		{
			if (0 == wp||IsBadReadPtr((void*)wp,4))
			{
				break;
			}

			//1. ����XML
			DMXmlDocument XmlDoc;
			if (0 == lp)
			{
				LPWSTR lpszXmlId = (LPWSTR)wp;
				if (!DMSUCCEEDED(g_pDMApp->InitDMXmlDocument(XmlDoc,RES_LAYOUT,lpszXmlId)))
				{
					break;
				}	
			}
			else if (1 == lp)
			{
				LPWSTR lpszPath = (LPWSTR)wp;
				wchar_t szPath[MAX_PATH] = {0};
				if (!GetRootFullPath(lpszPath,szPath,MAX_PATH))
				{
					break;
				}
				if (!XmlDoc.LoadFromFile(szPath))
				{
					break;
				}
			}

			//2.����XML
			DMXmlNode XmlLanguage = XmlDoc.Root(DMLAG_ROOT);
			if (!XmlLanguage.IsValid())
			{
				break;
			}

			//3.������԰�����
			DMLanguageItemPtr pLanguageItem = FindLanguageItemPtr(XmlLanguage.Attribute(DMLAG_NAME));
			if (NULL == pLanguageItem)// ���ԭ��������������԰����󣬾��½�һ����������
			{
				pLanguageItem = new DMLanguageItem(XmlLanguage.Attribute(DMLAG_NAME));
				AddObj(pLanguageItem);
			}

			//4.������԰���node
			DMXmlNode XmlNode = XmlLanguage.FirstChild(DMLAG_NODE);// loop 1
			while (XmlNode.IsValid())
			{
				DMTransNodePtr pNode = pLanguageItem->FindTransNodePtr(XmlNode.Attribute(DMLAG_NAME));
				if (NULL == pNode)// �����Node�����ڣ��ʹ���������
				{
					pNode = new DMTransNode(XmlNode.Attribute(DMLAG_NAME));
					pLanguageItem->AddObj(pNode);
				}

				//5. ���node��item
				DMXmlNode XmlItem = XmlNode.FirstChild(DMLAG_ITEM);// loop 2
				while (XmlItem.IsValid())
				{
					CStringW strSrc = XmlItem.Attribute(DMLAG_SRC);
					CStringW strTrans = XmlItem.Attribute(DMLAG_TRANS);
					if (pNode->IsKeyExist(strSrc))
					{// �����һ��Ϊ׼
						pNode->RemoveKey(strSrc);
					}
					pNode->AddKey(strSrc,strTrans);
					XmlItem = XmlItem.NextSibling(DMLAG_ITEM);// loop 2
				}

				XmlNode = XmlNode.NextSibling(DMLAG_NODE);// loop 1
			}
		} while (false);
		return iErr;
	}

	DMCode DMTransImpl::SetTrans(CStringW strLanguageName)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			//1. Ϊ�ձ�ʾʹ���ڲ�ԭʼ��,��������ַ���
			if (strLanguageName.IsEmpty())
			{
				m_pCurLanguage = NULL;
				m_strCurLanguageName = L"";
				iErr = DM_ECODE_OK;
				break;
			}

			//2. ������ͬ,������
			if (0 == strLanguageName.CompareNoCase(m_strCurLanguageName))
			{
				break;
			}

			//3. ������԰�,�����ȡ�ɹ�,�����m_strCurLanguageName,�����ȡʧ��,������m_strCurLanguageNameΪ��
			m_pCurLanguage = FindLanguageItemPtr(strLanguageName);
			if (m_pCurLanguage)
			{
				m_strCurLanguageName = strLanguageName;
			}
			else
			{
				m_strCurLanguageName = L"";
			}
			iErr = DM_ECODE_OK;
		} while (false);
		return iErr;
	}

	DMCode DMTransImpl::AddTransItem(CStringW strSrc, CStringW strTrans,CStringW strNodeName,CStringW strLanguageName)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			//1.�������԰�����,���������,�򴴽���
			DMLanguageItemPtr pLanguageItem = NULL;
			if (strLanguageName.IsEmpty())
			{
				pLanguageItem = m_pCurLanguage;
			}
			else
			{
				pLanguageItem = FindLanguageItemPtr(strLanguageName);
			}
			if (NULL == pLanguageItem&&!strLanguageName.IsEmpty())// �����µ����԰�
			{
				pLanguageItem = new DMLanguageItem(strLanguageName);
				AddObj(pLanguageItem);
			}
			if (NULL == pLanguageItem)
			{
				break;
			}

			//2.�������԰�������Node�Ӷ���,���������,�򴴽�
			DMTransNodePtr pNode = pLanguageItem->FindTransNodePtr(strNodeName);
			if (NULL == pNode)
			{
				pNode = new DMTransNode(strNodeName);
				pLanguageItem->AddObj(pNode);
			}

			//3.��������Ѵ���,���Ƴ�ԭ����,�����·���
			if (pNode->IsKeyExist(strSrc))
			{
				pNode->RemoveKey(strSrc);
			}
			pNode->AddKey(strSrc,strTrans);
			iErr = DM_ECODE_OK;
		} while (false);
		return iErr;
	}

	CStringW DMTransImpl::GetTrans(CStringW strSrc,CStringW strNodeName,CStringW strLanguageName)
	{
		CStringW strTrans = strSrc;// Ĭ�Ϸ���ԭʼ��
		do 
		{
			if (strSrc.IsEmpty()||0==(int)GetCount())
			{
				break;
			}
			//1.�������԰�����
			DMLanguageItemPtr pLanguageItem = NULL;
			if (strLanguageName.IsEmpty())// �ӵ�ǰ���õ����԰��в���
			{
				pLanguageItem = m_pCurLanguage;
			}
			else
			{
				pLanguageItem = FindLanguageItemPtr(strLanguageName);
			}
			if (NULL == pLanguageItem)
			{
				break;
			}


			if (strNodeName.IsEmpty())
			{
				strNodeName = L"custom";
			}
			//2.���ȴ��ض�strNodeName���ò���,������Ҳ���,���custom�в���
			if (0!=strNodeName.CompareNoCase(L"custom"))// �������custom
			{
				DMTransNodePtr pNode = pLanguageItem->FindTransNodePtr(strNodeName);
				if (NULL == pNode || !pNode->IsKeyExist(strSrc))// �ڵ㲻����,��ڵ���ڵ�key������,�����Ŵ�custom����
				{
					pNode = pLanguageItem->FindTransNodePtr(L"custom");
					if (NULL != pNode)
					{
						pNode->GetObjByKey(strSrc,strTrans);
					}
				}
				else
				{
					pNode->GetObjByKey(strSrc,strTrans);
				}
			}
			else//3.ֱ�Ӵ�custom�в���
			{
				DMTransNodePtr pNode = pLanguageItem->FindTransNodePtr(strNodeName);
				if (NULL != pNode)
				{
					pNode->GetObjByKey(strSrc,strTrans);
				}
			}

			//4.���ת��Ϊ��,�򷵻�ԭʼ
			if (strTrans.IsEmpty())
			{
				strTrans = strSrc;
			}
		} while (false);
		return strTrans;
	}

	DMLanguageItemPtr DMTransImpl::FindLanguageItemPtr(CStringW strLanguageName)
	{
		DMLanguageItemPtr pFindItem = NULL;
		do 
		{
			if (strLanguageName.IsEmpty())
			{
				break;
			}

			DMLanguageItem Item(strLanguageName);
			int iElement = FindObj(&Item);
			if (DM_INVALID_VALUE == iElement)
			{
				break;
			}
			pFindItem = GetObj(iElement);
		} while (false);
		return pFindItem;
	}

	void DMTransImpl::PreArrayObjRemove(const DMLanguageItemPtr &obj)
	{
		delete obj;
	}

	bool DMTransImpl::EqualArrayObj(const DMLanguageItemPtr &objsrc, const DMLanguageItemPtr &objdest)
	{
		if (0 == objsrc->m_strLanguageName.CompareNoCase(objdest->m_strLanguageName))
		{
			return true;
		}
		return false;
	}

}//namespace DM