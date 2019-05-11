//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMTreeT.h 
// File Des: Tree���������ģ��
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-2-22	1.0			
//-------------------------------------------------------
#pragma once

namespace DM
{
#pragma warning(push)
#pragma warning(disable: 4312) 
#define DMTVI_ROOT     ((HDMTREEITEM)0xFFFF0000)///<=TVI_ROOT
#define DMTVI_FIRST    ((HDMTREEITEM)0xFFFF0001)///<=TVI_FIRST
#define DMTVI_LAST     ((HDMTREEITEM)0xFFFF0002)///<=TVI_LAST
#define DMTVN_ROOT     ((HDMTREENODE)(ULONG_PTR)0xFFFF0000)///<=DMTVN_ROOT
#define DMTVN_FIRST    ((HDMTREENODE)(ULONG_PTR)0xFFFF0001)///<=DMTVN_FIRST
#define DMTVN_LAST     ((HDMTREENODE)(ULONG_PTR)0xFFFF0002)///<=DMTVN_LAST
#define STVL_ROOT      ((PDMTREELINK)0xFFFF0000)

	template<class T>
	class DMTreeT  
	{
		///-----------------------------------------
		///  �ڵ�ṹ��
		typedef struct _DMTREENODE
		{
			struct _DMTREENODE *hParent;      ///< ���ڵ�
			struct _DMTREENODE *hChildFirst;  ///< ��һ���ӽڵ�
			struct _DMTREENODE *hChildLast;   ///< ���һ���ӽڵ�
			struct _DMTREENODE *hPrevSibling; ///< �ֽڵ�
			struct _DMTREENODE *hNextSibling; ///< �ܽڵ�
			T data;                           ///< ����
		}DMTREENODE,*HDMTREENODE;

		///-----------------------------------------
		/// �˽ṹ�������������ڵ�
		typedef struct _DMTREELINK
		{
			HDMTREENODE  hParent;			 ///< ���ڵ�
			HDMTREENODE  hChildFirst;		 ///< ��һ���ӽڵ�
			HDMTREENODE  hChildLast;		 ///< ���һ���ӽڵ�
			HDMTREENODE  hPrevSibling;		 ///< �ֽڵ�
			HDMTREENODE  hNextSibling;		 ///< �ܽڵ�
		}DMTREELINK,*PDMTREELINK;

		///-----------------------------------------
		/// ����һ�������Ļص�����ԭ��
		typedef bool (*CBTRAVERSING)(T*,LPARAM);

	public:
		DMTreeT()
		{
			m_hRootFirst = NULL;
			m_hRootLast  = NULL;
		}

		virtual ~DMTreeT()
		{
			DeleteAllItems();
		}

		void DeleteAllItems()
		{
			if (m_hRootFirst)
			{
				FreeNode(DMTVN_ROOT);
				m_hRootFirst = NULL;
				m_hRootLast  = NULL;
			}
		}

		///-----------------------------------------
		/// ��ȡ��һ���ֵ�
		static HDMTREEITEM GetNextSiblingItem(HDMTREEITEM hItem)
		{
			PDMTREELINK pLink= (PDMTREELINK)hItem;
			DMASSERT(pLink&&pLink!=STVL_ROOT);
			return (HDMTREEITEM)pLink->hNextSibling;
		}

		///-----------------------------------------
		/// ��ȡ��һ���ֵ�
		static HDMTREEITEM GetPrevSiblingItem(HDMTREEITEM hItem)
		{
			PDMTREELINK pLink  = (PDMTREELINK)hItem;
			DMASSERT(pLink&&pLink!=STVL_ROOT);
			return (HDMTREEITEM)pLink->hPrevSibling;
		}

		///-----------------------------------------
		/// ��ȡ�����
		static HDMTREEITEM GetParentItem(HDMTREEITEM hItem)
		{
			PDMTREELINK pLink= (PDMTREELINK)hItem;
			DMASSERT(pLink&&pLink!=STVL_ROOT);
			return (HDMTREEITEM)pLink->hParent;
		}

		///< ��ȡ������
		static int GetItemLevel(HDMTREEITEM hItem)
		{
			int nRet = -1;
			if (hItem==DMTVI_ROOT) 
			{
				hItem = NULL;
			}
			while (hItem)
			{
				nRet++;
				hItem = GetParentItem(hItem);
			}
			return nRet;
		}

		///< HDMTREEITEM ���ڵ�
		static HDMTREEITEM GetRootItem(HDMTREEITEM hItem)
		{
			HDMTREEITEM hParent=hItem;
			while(GetParentItem(hParent))
			{
				hParent = GetParentItem(hParent);
			}
			return hParent;
		}

		///< ��ȡ��һ���ӽ��,
		HDMTREEITEM GetChildItem(HDMTREEITEM hItem,bool bFirst=true)
		{
			HDMTREENODE hsNode = (HDMTREENODE)hItem;
			DMASSERT(hsNode);
			if (hsNode==DMTVN_ROOT)
			{
				if (bFirst)
				{
					return (HDMTREEITEM)m_hRootFirst;
				}
				else
				{
					return (HDMTREEITEM)m_hRootLast;
				}
			}
			else
			{
				if (bFirst)
				{
					return (HDMTREEITEM)hsNode->hChildFirst;
				}
				else
				{
					return (HDMTREEITEM)hsNode->hChildLast;
				}
			}
		}

		///< ��ȡ�ӽ������
		int GetChildrenCount(HDMTREEITEM hItem)
		{
			int nRet = 0;
			HDMTREEITEM hChild = GetChildItem(hItem);
			while (hChild)
			{
				nRet++;
				hChild = GetNextSiblingItem(hChild);
			}
			return nRet;
		}

		///< ɾ��һ���ڵ㣬���Ա�����������
		virtual void DeleteItem(HDMTREEITEM hItem)
		{
			HDMTREENODE hsNode = (HDMTREENODE)hItem;
			DMASSERT(hsNode);
			if (hsNode==DMTVN_ROOT)
			{
				FreeNode(DMTVN_ROOT);
				m_hRootFirst = NULL;
				m_hRootLast = NULL;
				return;
			}
			DMTREENODE nodeCopy = *hsNode;
			bool bRootFirst=hsNode==m_hRootFirst;
			bool bRootLast=hsNode==m_hRootLast;
			FreeNode(hsNode);

			if (nodeCopy.hPrevSibling)///<has prevsibling
			{
				nodeCopy.hPrevSibling->hNextSibling=nodeCopy.hNextSibling;
			}
			else if (nodeCopy.hParent)///<parent's first child
			{
				nodeCopy.hParent->hChildFirst=nodeCopy.hNextSibling;
			}
			if (nodeCopy.hNextSibling)///< update next sibling's previous sibling
			{
				nodeCopy.hNextSibling->hPrevSibling=nodeCopy.hPrevSibling;
			}
			else if (nodeCopy.hParent)///<parent's last child
			{
				nodeCopy.hParent->hChildLast=nodeCopy.hPrevSibling;
			}
			///<update root item
			if (bRootFirst)   
			{
				m_hRootFirst=nodeCopy.hNextSibling;
			}
			if (bRootLast) 
			{
				m_hRootLast=nodeCopy.hPrevSibling;
			}
		}

		///< ɾ��һ������֦������ý��ĸ����û�������ӽڵ���һ��ɾ��
		bool DeleteItemEx(HDMTREEITEM hItem)
		{
			if(GetChildItem(hItem)) return false;
			while(hItem && !GetChildItem(hItem))
			{
				HDMTREEITEM hParent=GetParentItem(hItem);
				DeleteItem(hItem);
				hItem=hParent;
			}
			return true;
		}

		///< ��ȡ����б��������
		static T GetItem(HDMTREEITEM hItem)
		{
			DMASSERT(hItem!=DMTVI_ROOT);
			HDMTREENODE hsNode = (HDMTREENODE)hItem;
			DMASSERT(hsNode);
			return hsNode->data;
		}

		///< ��ȡ����б��������
		static T *GetItemPt(HDMTREEITEM hItem)
		{
			DMASSERT(hItem!=DMTVI_ROOT);
			HDMTREENODE hsNode = (HDMTREENODE)hItem;
			DMASSERT(hsNode);
			return &hsNode->data;
		}

		///< ����һ���½��,data:�������hParent:�½��ĸ����,hInsertAfter:�½���ǰһ���ֵܽ��,����HDMTREEITEM �½���ָ��
		HDMTREEITEM InsertItem(const T &data,HDMTREEITEM hParent=DMTVI_ROOT,HDMTREEITEM hInsertAfter=DMTVI_LAST)
		{
			HDMTREENODE hParentNode      = (HDMTREENODE) hParent;
			HDMTREENODE hInsertAfterNode = (HDMTREENODE) hInsertAfter;
			if (hParentNode==DMTVN_ROOT)
			{
				hParentNode = NULL;
			}
			DMASSERT(hInsertAfter);
			if (hInsertAfterNode!=DMTVN_FIRST && hInsertAfterNode!=DMTVN_LAST)
			{
				if (hInsertAfterNode->hParent!=hParentNode) 
				{
					return NULL;
				}
				if (hInsertAfterNode->hNextSibling==NULL)
				{
					hInsertAfterNode=DMTVN_LAST;
				}
			}

			HDMTREENODE hInserted=new DMTREENODE;
			hInserted->data=data;
			hInserted->hParent=hParentNode;
			hInserted->hChildFirst=NULL;
			hInserted->hChildLast=NULL;

			if (hInsertAfterNode==DMTVN_FIRST)
			{
				hInserted->hPrevSibling=NULL;
				if(hParentNode==NULL)///<root
				{
					hInserted->hNextSibling=m_hRootFirst;
					if (m_hRootFirst)
					{
						m_hRootFirst->hPrevSibling=hInserted;
					}
					m_hRootFirst=hInserted;
					if (m_hRootLast==NULL) 
					{
						m_hRootLast=hInserted;
					}
				}
				else ///<has parent
				{
					hInserted->hNextSibling=hParentNode->hChildFirst;
					if (hInserted->hNextSibling)
					{
						hInserted->hNextSibling->hPrevSibling=hInserted;
						hParentNode->hChildFirst=hInserted;
					}
					else
					{
						hParentNode->hChildLast=hParentNode->hChildFirst=hInserted;
					}
				}
			}
			else if(hInsertAfterNode==DMTVN_LAST)
			{
				hInserted->hNextSibling=NULL;
				if (hParentNode==NULL)///<root
				{
					hInserted->hPrevSibling=m_hRootLast;
					if (m_hRootLast) 
					{
						m_hRootLast->hNextSibling=hInserted;
					}
					m_hRootLast=hInserted;
					if (!m_hRootFirst) 
					{
						m_hRootFirst=hInserted;
					}
				}else
				{
					hInserted->hPrevSibling=hParentNode->hChildLast;
					if (hParentNode->hChildLast) 
					{
						hInserted->hPrevSibling->hNextSibling=hInserted;
						hParentNode->hChildLast=hInserted;
					}
					else
					{
						hParentNode->hChildLast=hParentNode->hChildFirst=hInserted;
					}                
				}
			}
			else
			{
				HDMTREENODE hNextSibling=hInsertAfterNode->hNextSibling;
				hInserted->hPrevSibling=hInsertAfterNode;
				hInserted->hNextSibling=hNextSibling;
				hNextSibling->hPrevSibling = hInsertAfterNode->hNextSibling = hInserted;
			}
			return (HDMTREEITEM)hInserted;
		}

		///< ���õݹ鷽ʽ����һ�������,CBTRAVERSINGΪ�ص�����,���ر���ֹ�������
		HDMTREEITEM TraversingRecursion(HDMTREEITEM hItem,CBTRAVERSING funTraversing,LPARAM lParam)
		{
			DMASSERT(hItem);
			if (hItem!=DMTVI_ROOT)
			{
				if (funTraversing(GetItemPt(hItem),lParam))
				{
					return hItem;
				}
			}

			HDMTREEITEM hChild = GetChildItem(hItem);
			while (hChild)
			{
				HDMTREEITEM hTmp = GetChildItem(hChild);
				if (hTmp)
				{
					HDMTREEITEM hRet=TraversingRecursion(hTmp,funTraversing,lParam);
					if (hRet) 
					{
						return hRet;
					}
				}
				else
				{
					if (funTraversing(GetItemPt(hChild),lParam)) 
					{
						return hChild;
					}
				}
				hChild = GetNextSiblingItem(hChild);
			}
			return NULL;
		}

		///< ��˳��ʽ��ָ����㿪ʼ���Һ���Ľ�㣬�����Լ����ӽڵ㼰�Լ����µ��ֵܽ��
		HDMTREEITEM TraversingSequence(HDMTREEITEM hItem,CBTRAVERSING funTraversing,LPARAM lParam)
		{
			if (!m_hRootFirst) 
			{
				return NULL;
			}
			if (hItem!=DMTVI_ROOT)
			{
				if (funTraversing(GetItemPt(hItem),lParam)) 
				{
					return hItem;
				}
			}
			HDMTREEITEM hNext = GetNextItem(hItem);
			while (hNext)
			{
				if (funTraversing(GetItemPt(hNext),lParam))
				{
					return hNext;
				}
				hNext = GetNextItem(hNext);
			}
			return NULL;
		}

		///< ��ȡ���ڵ�
		HDMTREEITEM GetRootItem(bool bFirst=true)
		{
			return (HDMTREEITEM)(bFirst?m_hRootFirst:m_hRootLast);
		}

		///< ��ȡ���οؼ�������Ŀ
		int GetCount()
		{
			HDMTREEITEM hRoot = (HDMTREEITEM)m_hRootFirst;
			if (NULL == hRoot)
			{
				return 0;
			}
			return GetDesendants(hRoot)+1;
		}

		///< ��ȡ������������
		int GetDesendants(HDMTREEITEM hItem)
		{
			int nRet = 0;
			HDMTREEITEM hChild = GetChildItem(hItem);
			while (hChild)
			{
				nRet += 1+GetDesendants(hChild);
				hChild = GetNextSiblingItem(hChild);
			}
			return nRet;
		}

		///< ��ȡ��ǰ������һ�����
		/*Describe  ��ȡ��ǰ������һ�����
		* �����ǰ������ӽ�㣬�򷵻��Լ��ĵ�һ���ӽ�㣬
		* ������������µ��ֵܽ�㣬�򷵻��Լ������ֵܽ�㡢
		* ���������Լ��ĸ����������ֵܽ��
		*/
		HDMTREEITEM GetNextItem(HDMTREEITEM hItem)
		{
			if (hItem==DMTVI_ROOT)
			{
				return (HDMTREEITEM)m_hRootFirst;
			}

			HDMTREEITEM hRet = GetChildItem(hItem);
			if (hRet)
			{
				return hRet;
			}
			HDMTREEITEM hParent = hItem;
			while (hParent)
			{
				hRet = GetNextSiblingItem(hParent);
				if (hRet) 
				{
					return hRet;
				}
				hParent = GetParentItem(hParent);
			}
			return NULL;
		}

		///< ��ȡ��ǰ������һ�����
		/* int &nLevel -- ��ǰ���(hItem)��Ŀ����(return)�Ĳ�ι�ϵ:1-���ӹ�ϵ��0���ֵܹ�ϵ��-n����->�����ֵ�
		* Describe  ��ȡ��ǰ������һ�����
		*           �����ǰ������ӽ�㣬�򷵻��Լ��ĵ�һ���ӽ�㣬
		*           ������������µ��ֵܽ�㣬�򷵻��Լ������ֵܽ�㡢
		*           ���������Լ��ĸ����������ֵܽ��
		*/
		HDMTREEITEM GetNextItem(HDMTREEITEM hItem,int &nLevel)
		{
			if (hItem==DMTVI_ROOT)
			{
				nLevel = 1;
				return (HDMTREEITEM)m_hRootFirst;
			}

			HDMTREEITEM hRet = GetChildItem(hItem);
			if (hRet)
			{
				nLevel = 1;
				return hRet;
			}
			HDMTREEITEM hParent = hItem;
			nLevel = 0;
			while (hParent)
			{
				hRet = GetNextSiblingItem(hParent);
				if (hRet) 
				{
					return hRet;
				}
				nLevel--;
				hParent = GetParentItem(hParent);
			}
			return NULL;
		}
	public:///< ����
		///< ���ú�������ķ�ʽ�ͷŽ��ռ�õĿռ�
		void FreeNode(HDMTREENODE hsNode)
		{
			DMASSERT(hsNode);		
			HDMTREENODE hSibling=(HDMTREENODE)GetChildItem((HDMTREEITEM)hsNode);
			while (hSibling)
			{
				HDMTREENODE hNextSibling=hSibling->hNextSibling;
				FreeNode(hSibling);
				hSibling=hNextSibling;
			}
			if (hsNode!=DMTVN_ROOT)
			{
				OnNodeFree(hsNode->data);// �����νṹ�ƻ�ǰ�ͷ�
				delete hsNode;
			}
		}

	public:///< ������
		///< ����������ʵ�����ݵ��ͷŲ���
		virtual void OnNodeFree(T & data){}

	public:
		HDMTREENODE  m_hRootFirst;  ///< ��һ�����ڵ�
		HDMTREENODE  m_hRootLast;   ///< ���һ�����ڵ�
	};

#pragma warning(pop)
}//namespace DM