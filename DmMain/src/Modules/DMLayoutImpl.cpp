#include "DmMainAfx.h"
#include "DMLayoutImpl.h"

namespace DM
{
	DMLayoutImpl::DMLayoutImpl()
	{
		m_pOwner		= NULL;
		m_nCount		= 0;
		m_uPositionType = 0;
		m_nSepSpace     = 2;
		m_size.SetSize(POS_INIT,POS_INIT);
	}

	DMCode DMLayoutImpl::SetOwner(LPVOID lpWnd)
	{
		m_pOwner = (DUIWindow *)lpWnd;
		return DM_ECODE_OK;
	}

	DMCode DMLayoutImpl::UpdateLayout(LPRECT lpRcContainer,OUT CRect &rcWindow)
	{
		DMCode iErr = DM_ECODE_FAIL;
		int nRet = 0; // δ��ʼ���ɹ��Ĵ���
		do 
		{
			rcWindow.SetRect(POS_INIT,POS_INIT,POS_INIT,POS_INIT);// ��ʹԭ����������Ч
			CRect rcContainer;
			if (!lpRcContainer)
			{
				if (!m_pOwner->DM_GetWindow(GDW_PARENT))
				{
					break;
				}
				m_pOwner->DM_GetWindow(GDW_PARENT)->DV_GetChildMeasureLayout(rcContainer);
				lpRcContainer = &rcContainer;
			}
			rcContainer = lpRcContainer;

			if (4 == m_nCount)// ָ����4������
			{
				if (!Update4(lpRcContainer,rcWindow))
				{
					break;
				}
			}
			else
			{
				if (2 == m_nCount)// ָ����2������
				{
					if (!Update2(lpRcContainer,rcWindow))
					{
						break;
					}
				}
				else if (0 == m_nCount && // ʹ�����������ֿ��ÿռ䷽ʽ
					((m_uPositionType&SizeX_FitParent)&&(m_uPositionType &SizeY_FitParent)))
				{
					if (!UpdateFull(lpRcContainer,rcWindow))
					{
						break;
					}
				}
				else// �Զ��Ű�
				{
					if (!UpdateAuto(lpRcContainer,rcWindow))
					{
						break;
					}
				}
			}
			rcWindow.NormalizeRect();
			rcWindow = rcWindow&rcContainer;// �����������ܳ�����������
			iErr = DM_ECODE_OK;
		} while (false);
		return iErr;
	}

	DMCode DMLayoutImpl::UpdateChildLayout()
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			DM::CList<DUIWindow*> lstWnd;
			DUIWindow *pChild = m_pOwner->DM_GetWindow(GDW_FIRSTCHILD);
			while (pChild)
			{
				if (!pChild->m_bFloatLayout)
				{
					pChild->m_rcWindow.SetRect(POS_INIT,POS_INIT,POS_INIT,POS_INIT);
					lstWnd.AddTail(pChild);
				}
				else
				{
					// �������겻��Ҫ����
				}
				pChild = pChild->DM_GetWindow(GDW_NEXTSIBLING);
			}
			if (ParseChildPosition(&lstWnd))
			{
				iErr = DM_ECODE_OK;
			}
		} while (false);
		return iErr;
	}

	// ����--------------------------
	bool DMLayoutImpl::ParseChildPosition(DM::CList<DUIWindow*> *pList)
	{
		CRect rcContainer;
		m_pOwner->DV_GetChildMeasureLayout(rcContainer);
		POSITION pos	  = pList->GetHeadPosition();
		int iCount		  = (int)pList->GetCount();
		while (pos)
		{
			POSITION posOld	  = pos;
			DUIWindow *pChild = pList->GetNext(pos);
			//if (0 == pChild->DM_SendMessage(WM_WINDOWPOSCHANGED,0,(LPARAM)&rcContainer))
			if (0 == pChild->DM_UpdateLayout(&rcContainer))// ������Ϣ�ˣ�ֱ�ӵ���
			{
				pList->RemoveAt(posOld);
			}
		}
		if (0 == pList->GetCount())
		{
			return true;
		}

		if(iCount == pList->GetCount())
		{
			DMASSERT_EXPR(0,L"��,����������,������!");
			return false;
		}
		else
		{
			return ParseChildPosition(pList);// �ݹ�
		}
	}

	bool DMLayoutImpl::ParsePostion()
	{
		CStringW strPos = m_strPosValue;
		bool bRet = false;
		do 
		{
			CStringWList strPosList;
			SplitStringT(strPos,L',',strPosList);
			m_nCount = (int)strPosList.GetCount();
			if (2!=m_nCount&&4!=m_nCount)
			{
				break;
			}

			// ����item-----------------------------
			POS_ITEM item[4];
			memset(item,0, sizeof(POS_ITEM)*4);
			for (int i=0;i<m_nCount;i++)
			{
				ParseItem(strPosList[i],item[i]);
			}
			if (PIT_OFFSET==item[0].pit||PIT_OFFSET==item[1].pit)
			{
				DMASSERT_EXPR(0,L"����ǰ������������ʹ��@!");
				break;
			}
			m_Left = item[0];m_Top = item[1];m_Right = item[2]; m_Bottom = item[3];
			if(2 == m_nCount)
			{
				m_uPositionType = (m_uPositionType&~SizeX_Mask) | SizeX_FitContent;
				m_uPositionType = (m_uPositionType&~SizeY_Mask) | SizeY_FitContent;
			}
			bRet = true;
		} while (false);
		return bRet;
	}

	// ����ParsePostion������m_nCount<4ʱ����---------------------------- 
	bool DMLayoutImpl::ParsePostionType()
	{
		bool bRet = false;
		do 
		{
			if (4 == m_nCount)
			{
				bRet = true;
				break;
			}
			if (POS_INIT == m_size.cx||POS_INIT == m_size.cy)
			{
				break;
			}
			int nWidValue = m_size.cx;
			int nHeiValue = m_size.cy;
			// �ȴ���width ------------------------
			if (-1 == nWidValue && 0 == m_nCount)// ��������������
			{
				m_pOwner->m_rcWindow.right = 0;
				m_uPositionType			   = (m_uPositionType&~SizeX_Mask) | SizeX_FitParent;
			}
			else
			{
				if (nWidValue>=0)// ָ�����
				{
					m_pOwner->m_rcWindow.right = nWidValue;
					m_uPositionType            = (m_uPositionType&~SizeX_Mask) | SizeX_Specify;
				}
				else if(-1 == nWidValue)// ʹ�����ݿ��
				{
					m_pOwner->m_rcWindow.right = 0;
					m_uPositionType			   = (m_uPositionType&~SizeX_Mask) | SizeX_FitContent;
				}
			}

			// �ٴ���Height-----------------------
			if (-1 == nHeiValue&&0 == m_nCount)
			{
				m_pOwner->m_rcWindow.bottom = 0;
				m_uPositionType             = (m_uPositionType&~SizeY_Mask) | SizeY_FitParent;
			}
			else
			{
				if (nHeiValue >= 0)
				{
					m_pOwner->m_rcWindow.bottom = nHeiValue;
					m_uPositionType             = (m_uPositionType&~SizeY_Mask) | SizeY_Specify;
				}
				else if(-1 == nHeiValue)
				{
					m_pOwner->m_rcWindow.bottom = 0;
					m_uPositionType             = (m_uPositionType&~SizeY_Mask) | SizeY_FitContent;
				}
			}
			bRet = true;
		} while (false);
		return bRet;
	}

	bool DMLayoutImpl::ParseItem(CStringW &strPos, POS_ITEM &item)
	{
		bool bRet = false;
		do 
		{
			if (strPos.IsEmpty())
			{
				DMASSERT_EXPR(0,L"ParseItem���벻Ҫʹ�ÿ�ֵ");
				break;
			}

			LPCWSTR lpszPos = strPos;
			switch (lpszPos[0])
			{
			case POSFLAG_REFCENTER:		item.pit=PIT_CENTER,	lpszPos++;	break;		// 3.1.��|������ο������ڵ�����, PIT_CENTER:�ο����������ĵ�,��"|"��ʼ
			case POSFLAG_PERCENT:		item.pit=PIT_PERCENT,	lpszPos++;	break;		// 3.2. %�������ڸ����ڵİٷֱ�, PIT_PERCENT:ָ���ڸ�����������еİٷֱ�,��"%"��ͷ
			case POSFLAG_REFPREV_NEAR:  item.pit=PIT_PREV_NEAR, lpszPos++;  break;		// 3.3.��[�������ǰһ�ֵܴ��ڡ�����Xʱ���ο�ǰһ�ֵܴ��ڵ�right������Yʱ�ο�ǰһ�ֵܴ��ڵ�bottom,PIT_PREV_NEAR:�ο�ǰһ���ֵܴ������Լ����ı�
			case POSFLAG_REFNEXT_NEAR:  item.pit=PIT_NEXT_NEAR, lpszPos++;  break;		// 3.4.��]������ں�һ�ֵܴ��ڡ�����Xʱ���ο���һ�ֵܵ�left,����Yʱ�ο���һ�ֵܵ�top,PIT_NEXT_NEAR:�ο���һ���ֵܴ������Լ����ı�
			case POSFLAG_REFPREV_FAR:   item.pit=PIT_PREV_FAR,	lpszPos++;  break;		// 3.5.��{�������ǰһ�ֵܴ��ڡ�����Xʱ���ο�ǰһ�ֵܴ��ڵ�left������Yʱ�ο�ǰһ�ֵܴ��ڵ�top,PIT_PREV_FAR:�ο�ǰһ���ֵܴ������Լ�Զ�ı�
			case POSFLAG_REFNEXT_FAR:   item.pit=PIT_NEXT_FAR,	lpszPos++;	break;		// 3.6.��}������ں�һ�ֵܴ��ڡ�����Xʱ���ο���һ�ֵܵ�right,����Yʱ�ο���һ�ֵܵ�bottom,PIT_NEXT_FAR:�ο���һ���ֵܴ������Լ�Զ�ı�
			case POSFLAG_DEFSIZE:		item.pit=PIT_OFFSET,	lpszPos++;	break;		// 3.7.@:ָ�����ڵ�size��ֻ������x2,y2������x2ʱ��ָ�����ڵ�width������y2ʱָ�����ڵ�height,PIT_OFFSET:�����ǰ��x1,y1��ƫ��,ֻ����x2,y2��ʹ�ã���@��ͷ
			default: item.pit=PIT_NORMAL;break;
			}

			item.bMinus = false;
			if (L'-' == lpszPos[0])
			{
				lpszPos++;
				if (PIT_PERCENT != item.pit)// �ǰٷֱ�ֵ���ٷֱ�ֵ������ʹ�ø�ֵ
				{
					item.bMinus = true;
				}
			}
			item.nPos = (float)_wtof(lpszPos);
			if (item.nPos<0.0f && PIT_OFFSET == item.pit) 
			{
				DMASSERT_EXPR(0,L"��ʹ��@ʱ�벻Ҫʹ�ø�ֵ,�ڲ�ǿ��ת����ֵ��");
				item.nPos = DMABS(item.nPos);
			}
			bRet = true;
		} while (false);
		return bRet;
	}

	int DMLayoutImpl::ParseItemValue(const POS_ITEM &item,int nMin, int nMax,bool bX)
	{
		int nRet	=	0;
		int nWid	=	nMax-nMin;

		switch(item.pit)
		{
		case PIT_CENTER: 
			nRet = (int)item.nPos*(item.bMinus?-1:1) + nWid/2 + nMin;
			break;

		case PIT_NORMAL: 
			if (item.bMinus)
				nRet = nMax-(int)item.nPos;
			else			
				nRet = nMin+(int)item.nPos;
			break;

		case PIT_PERCENT: 
			nRet = nMin+(int)(item.nPos*nWid/100);
			if (nRet>nMax) 
				nRet=nMax;
			break;

		case PIT_PREV_NEAR:
		case PIT_PREV_FAR:
			{
				// ���ǰһ���ֵܴ��ڣ�û�У���ȡ�ø�����
				DUIWindow *pRefWnd = m_pOwner->DM_GetWindow(GDW_PREVSIBLING);
				CRect rcRef;
				if (pRefWnd)
				{
					pRefWnd->DV_GetWindowRect(&rcRef);
				}
				if (!pRefWnd) 
				{
					pRefWnd = m_pOwner->DM_GetWindow(GDW_PARENT);
					if (pRefWnd)
					{
						pRefWnd->DV_GetChildMeasureLayout(&rcRef);
						CRect rcTemp = rcRef;
						rcRef.right = rcTemp.left;// �����ڵ�Զ�����ֵܴ����෴��
						rcRef.left = rcTemp.right;
						rcRef.top = rcTemp.bottom;
						rcRef.bottom = rcTemp.top;
					}
				}

				if (pRefWnd) //��Ҫȷ���ο������Ƿ���ɲ���
				{
					if (bX)
					{
						LONG refPos = (item.pit == PIT_PREV_NEAR)?rcRef.right:rcRef.left;
						if (refPos == POS_INIT||refPos==POS_WAIT)
							nRet = POS_WAIT;
						else
							nRet = refPos+(int)item.nPos*(item.bMinus?-1:1);
					}
					else
					{
						LONG refPos = (item.pit == PIT_PREV_NEAR)?rcRef.bottom:rcRef.top;
						if(refPos == POS_INIT || refPos==POS_WAIT)
							nRet = POS_WAIT;
						else
							nRet = refPos+(int)item.nPos*(item.bMinus?-1:1);
					}
				}
			}
			break;
		case PIT_NEXT_NEAR:
		case PIT_NEXT_FAR:
			{
				DUIWindow *pRefWnd = m_pOwner->DM_GetWindow(GDW_NEXTSIBLING);
				CRect rcRef;
				if (pRefWnd)
				{
					pRefWnd->DV_GetWindowRect(&rcRef);
				}
				if (!pRefWnd) 
				{
					pRefWnd = m_pOwner->DM_GetWindow(GDW_PARENT);
					if (pRefWnd)
					{
						pRefWnd->DV_GetChildMeasureLayout(&rcRef);
						CRect rcTemp = rcRef;
						rcRef.right = rcTemp.left;// �����ڵ�Զ�����ֵܴ����෴��
						rcRef.left = rcTemp.right;
						rcRef.top = rcTemp.bottom;
						rcRef.bottom = rcTemp.top;
					}
				}
				if (pRefWnd)//��Ҫȷ���ο������Ƿ���ɲ���
				{
					if (bX)
					{
						LONG refPos = (item.pit == PIT_NEXT_NEAR)?rcRef.left:rcRef.right;
						if (refPos == POS_INIT || refPos==POS_WAIT)
							nRet = POS_WAIT;
						else
							nRet = refPos+(int)item.nPos*(item.bMinus?-1:1);
					}else
					{
						LONG refPos = (item.pit == PIT_NEXT_NEAR)?rcRef.top:rcRef.bottom;
						if(refPos == POS_INIT || refPos==POS_WAIT)
							nRet = POS_WAIT;
						else
							nRet = refPos+(int)item.nPos*(item.bMinus?-1:1);
					}
				}
			}
			break;
		}
		return nRet;
	}

	bool DMLayoutImpl::Update4(LPRECT lpRcContainer,OUT CRect &rcWindow)
	{
		int nRet = 0;
		if (IsUnInitPos(rcWindow.left))// left
		{
			rcWindow.left = ParseItemValue(m_Left,lpRcContainer->left,lpRcContainer->right,true);
		}
		if (IsUnInitPos(rcWindow.top))// top
		{
			rcWindow.top = ParseItemValue(m_Top,lpRcContainer->top,lpRcContainer->bottom,false);
		}
		if (IsUnInitPos(rcWindow.right))// right
		{
			if (PIT_OFFSET == m_Right.pit)
			{
				if (!IsUnInitPos(rcWindow.left))
				{
					rcWindow.right = rcWindow.left+(LONG)m_Right.nPos;// ���PIT_OFFSET���Ǿ��Ǽ��Ͽ��
				}
			}
			else
			{	
				rcWindow.right = ParseItemValue(m_Right,lpRcContainer->left,lpRcContainer->right,true);
			}
		}
		if (IsUnInitPos(rcWindow.bottom))// bottom
		{
			if (PIT_OFFSET == m_Bottom.pit)
			{
				if (!IsUnInitPos(rcWindow.top))
				{
					rcWindow.bottom = rcWindow.top+(LONG)m_Bottom.nPos;// ���PIT_OFFSET���Ǿ��Ǽ��ϸ߶�
				}
			}
			else
			{
				rcWindow.bottom = ParseItemValue(m_Bottom,lpRcContainer->top,lpRcContainer->bottom,false);
			}
		}
		if (POS_WAIT==rcWindow.left||POS_WAIT==rcWindow.top||POS_WAIT==rcWindow.right||POS_WAIT==rcWindow.bottom)
		{
			return false;
		}
		return true;
	}

	bool DMLayoutImpl::Update2(LPRECT lpRcContainer,OUT CRect &rcWindow)
	{
		bool bRet = false;
		do 
		{
			CPoint pt = rcWindow.TopLeft();
			CSize sz  = CalcSize(lpRcContainer);
			if (IsUnInitPos(pt.x)) 
			{
				pt.x = ParseItemValue(m_Left,lpRcContainer->left,lpRcContainer->right,true);
			}
			if (IsUnInitPos(pt.y))
			{
				pt.y = ParseItemValue(m_Top,lpRcContainer->top,lpRcContainer->bottom,false);
			}
			if (POS_WAIT == pt.x||POS_WAIT == pt.y)
			{
				break;
			}
			rcWindow = CRect(pt,sz);
			bRet = true;
		} while (false);
		return bRet;
	}

	bool DMLayoutImpl::UpdateFull(LPRECT lpRcContainer,OUT CRect &rcWindow)
	{
		bool bRet = false;
		do 
		{
			rcWindow = lpRcContainer;
			bRet = true;
		} while (false);
		return bRet;
	}

	bool DMLayoutImpl::UpdateAuto(LPRECT lpRcContainer,OUT CRect &rcWindow)
	{
		bool bRet = false;
		do 
		{
			CPoint pt(lpRcContainer->left,lpRcContainer->top);
			CSize sz  = CalcSize(lpRcContainer);
			DUIWindow *pSibling = m_pOwner->DM_GetWindow(GDW_PREVSIBLING);
			if (pSibling)
			{
				CRect rcSib;
				pSibling->DV_GetWindowRect(&rcSib);
				if (IsUnInitPos(rcSib.left)||IsUnInitPos(rcSib.top)||IsUnInitPos(rcSib.right)||IsUnInitPos(rcSib.bottom))
				{
					pt.x = lpRcContainer->left;
					pt.y = lpRcContainer->top;
				}
				else
				{
					pt.y = rcSib.bottom+m_nSepSpace;
				}
			}
			rcWindow = CRect(pt,sz);
			bRet = true;
		} while (false);
		return bRet;
	}

	bool DMLayoutImpl::IsUnInitPos(int iPos)
	{
		return POS_INIT == iPos || POS_WAIT == iPos;
	}

	CSize DMLayoutImpl::CalcSize(LPRECT pRcContainer)
	{
		CSize sz;
		if (m_uPositionType&SizeX_Specify)
		{
			sz.cx = m_size.cx;
		}
		else if(m_uPositionType&SizeX_FitParent)
		{
			sz.cx = pRcContainer->right-pRcContainer->left;
		}

		if (m_uPositionType&SizeY_Specify)
		{
			sz.cy = m_size.cy;
		}
		else if (m_uPositionType&SizeY_FitParent)
		{
			sz.cy = pRcContainer->bottom-pRcContainer->top;
		}

		if((m_uPositionType&SizeX_FitContent) || (m_uPositionType&SizeY_FitContent) && m_nCount!=4)
		{
			CSize szDesire;
			m_pOwner->DV_GetDesiredSize(pRcContainer,szDesire);    
			if (m_uPositionType&SizeX_FitContent)
			{
				sz.cx = szDesire.cx;
			}
			if (m_uPositionType&SizeY_FitContent)
			{
				sz.cy = szDesire.cy;
			}
		}
		return sz;
	}

	DMCode DMLayoutImpl::OnAttributePos(LPCWSTR pszValue, bool bLoadXml)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			CStringW strOldPosValue = m_strPosValue;
			m_strPosValue = pszValue;
			if (!ParsePostion())
			{
				break;
			}
			if (!ParsePostionType())
			{
				break;
			}
			
			iErr = DM_ECODE_OK;
		} while (false);
		return iErr;
	}

	DMCode DMLayoutImpl::OnAttributePosSize(LPCWSTR pszValue, bool bLoadXml)
	{
		dm_parsesize(pszValue,m_size);
	
		ParsePostion();
		ParsePostionType();

		return DM_ECODE_OK;
	}
}//namespace DM
