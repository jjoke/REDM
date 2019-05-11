// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	ActionSlotMgr.h
// File mark:   
// File summary:������ද����ǰ�����˶���ά��
//				����ڵ�ֲ� NullNode->ActionNode->NullNode->ActionNode->NullNode 
//				1.��ǰ�ڵ�һ����ָ��NullNode  Undo��ʱ��ǰ�ڵ����һ��  ָ��ActionNode Ȼ��ִ�ж�����ִ�����ٺ���һ��ָ��NullNode��Redo��ʱ�����෴
//				2.ÿ�������ڵ�����ϸ������һ��NullNode
//				3.��ǰ�������ִ��ʧ�ܣ��������������Ȼ����ǰ�������ƽ�ִ��
// Author:		lzlong
// Edition:     1.0
// Create date: 2019-3-20
// ----------------------------------------------------------------
#pragma once

template<class T>
class ActionSlotMgr
{
	///-----------------------------------------
	///  �ڵ�ṹ��
	typedef struct _ACTIONLINKNODE
	{
		struct _ACTIONLINKNODE *hPrevSibling; ///< �ֽڵ�
		struct _ACTIONLINKNODE *hNextSibling; ///< �ܽڵ�
		T* data;							  ///< ����
	}ACTIONLINKNODE, *HACTIONLINKNODE;

public:
	ActionSlotMgr()
	{
		m_bMuteAddSlot = false;
		m_hCurAction = NULL;
		m_hActionFirst = NULL;
	}

	virtual ~ActionSlotMgr()
	{
		FreeAllActionSlot();
	}

	void FreeAllActionSlot()
	{
		m_hCurAction = NULL;
		if (m_hActionFirst) FreeNode(m_hActionFirst);
		m_hActionFirst = NULL;
	}

	void InsertNewAction(T* action)
	{
		if (m_bMuteAddSlot) //���� ֱ��delete��
		{
			OnNodeFree(action);
			return;
		}
		HACTIONLINKNODE hInserted = new ACTIONLINKNODE;
		hInserted->data = action;
		hInserted->hPrevSibling = NULL;
		hInserted->hNextSibling = NULL;
		if (!m_hCurAction) //first item
		{
			m_hCurAction = hInserted;
			m_hCurAction->hPrevSibling = NULL;
			m_hCurAction->hNextSibling = NULL;
			m_hActionFirst = m_hCurAction;
		}
		else 
		{//��������
			if (m_hCurAction->hNextSibling) //����һ�� ������ͷŵ�  �¼���ľ������һ����
			{
				FreeNode(m_hCurAction->hNextSibling);
			}
			m_hCurAction->hNextSibling = hInserted;
			hInserted->hPrevSibling = m_hCurAction;
			m_hCurAction = hInserted;
		}
	}

	DMCode ExcutePrevSiblingAction()
	{
		DMCode iRet = DM_ECODE_FAIL;
		do 
		{
			if (!m_hCurAction)
				break;
			bool bActExcuteAble = m_hCurAction->data->IsActExCuteAble(); //��ǰһ����NullNode
			DMASSERT(!bActExcuteAble);
			if (!m_hCurAction->hPrevSibling)
				break;
			m_hCurAction = m_hCurAction->hPrevSibling;
			DMASSERT(m_hCurAction);
				
			iRet = m_hCurAction->data->PerformUndoActionSlot();
			m_hCurAction = m_hCurAction->hPrevSibling;
			DMASSERT(m_hCurAction && !m_hCurAction->data->IsActExCuteAble());//��ִ�ж���ǰ��һ����NullNode
		} while (DM_ECODE_OK != iRet); //ֱ���ɹ��Ķ���
		return iRet;
	}

	DMCode ExcuteNextSiblingAction()
	{
		DMCode iRet = DM_ECODE_FAIL;
		do
		{
			if (!m_hCurAction)
				break;
			bool bActExcuteAble = m_hCurAction->data->IsActExCuteAble(); //��ǰһ����NullNode
			DMASSERT(!bActExcuteAble);
			if (!m_hCurAction->hNextSibling)
				break;
			m_hCurAction = m_hCurAction->hNextSibling;
			DMASSERT(m_hCurAction);

			iRet = m_hCurAction->data->PerformRedoActionSlot();
			m_hCurAction = m_hCurAction->hNextSibling;
			DMASSERT(m_hCurAction && !m_hCurAction->data->IsActExCuteAble());//��ִ�ж�������һ����NullNode
		} while (DM_ECODE_OK != iRet); //ֱ���ɹ��Ķ���
		return iRet;
	}

	//�Ƿ����undo��
	bool IsExistPrevSiblingSteps()
	{
		if (!m_hCurAction)
			return false;
		return (NULL != m_hCurAction->hPrevSibling);
	}

	//�Ƿ����redo��
	bool IsExistNextSiblingSteps()
	{
		if (!m_hCurAction)
			return false;
		return (NULL != m_hCurAction->hNextSibling);
	}

	T* GetCurActData()
	{
		return m_hCurAction->data;
	}
	
	DMCode WalkPrevSiblingStep()
	{
		DMCode iRet = DM_ECODE_FAIL;
		do
		{
			if (!m_hCurAction)
				break;
			if (!m_hCurAction->hPrevSibling)
				break;

			m_hCurAction = m_hCurAction->hPrevSibling;
			iRet = DM_ECODE_OK;
		} while (DM_ECODE_OK != iRet); //ֱ���ɹ��Ķ���
		return iRet;
	}

	DMCode WalkNexSiblingStep()
	{
		DMCode iRet = DM_ECODE_FAIL;
		do
		{
			if (!m_hCurAction)
				break;
			if (!m_hCurAction->hNextSibling)
				break;

			m_hCurAction = m_hCurAction->hNextSibling;
			iRet = DM_ECODE_OK;
		} while (DM_ECODE_OK != iRet); //ֱ���ɹ��Ķ���
		return iRet;
	}

	void FreeNode(HACTIONLINKNODE& hsNode)
	{
		DMASSERT(hsNode);
		HACTIONLINKNODE hSibling = hsNode->hNextSibling;
		if (hSibling) FreeNode(hSibling);
		hsNode->hNextSibling = NULL;
		hsNode->hPrevSibling = NULL;
		OnNodeFree(hsNode->data);
		delete hsNode;
		hsNode = NULL;
	}

	virtual void OnNodeFree(T* & data)
	{
		delete data;
	}

	bool& GetMemberbMuteAddSlot()
	{
		return m_bMuteAddSlot;
	}

	bool IsActionArrayChainEmpty()
	{
		return NULL == m_hCurAction;
	}
private:
	HACTIONLINKNODE m_hCurAction;
	HACTIONLINKNODE	m_hActionFirst;
	bool			m_bMuteAddSlot;
};