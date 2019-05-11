#include "DmMainAfx.h"
#include "DMDrawImpl.h"

namespace DM
{
	DMDrawImpl::DMDrawImpl()
	{
		g_pDMApp->GetDefRegObj((void**)&m_pRender, DMREG_Render);
		m_pRender->CreateCanvas(0,0,&m_pMemCanvas);
		m_bNeedRepaint = m_bOnlyOneRectRepaint = false;
	}

	DMCode DM::DMDrawImpl::DrawBackground(IDMCanvas* pCanvas,IDMRegion* lpRgn,DUIWindow* pWnd)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			DUIWindow *pTopWnd = pWnd->DM_GetTopParentWnd();
			if (NULL == pTopWnd)
			{
				break;
			}
			pCanvas->PushClip(lpRgn);
			DMDRAW_STATE Render_State = DRAW_START;
			_OnRender(pCanvas,lpRgn,pTopWnd,pTopWnd,pWnd,Render_State);// �Ӷ��㸸���ڻ��Ƶ�������
			pCanvas->PopClip();
			iErr = DM_ECODE_OK;
		} while (false);
		return iErr;
	}

	DMCode DMDrawImpl::DrawForeground(IDMCanvas* pCanvas,IDMRegion* lpRgn,DUIWindow* pWnd)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			CRect rcDraw = pWnd->m_rcWindow;
			if (lpRgn)
			{
				lpRgn->CombineRect(rcDraw,RGN_AND);
			}
			CRect rcInvalid;
			lpRgn->GetRgnBox(&rcInvalid);
			rcDraw.IntersectRect(rcDraw,rcInvalid);
			DUIWindow* pStart = pWnd->DM_GetNextVisibleWnd(pWnd,rcInvalid);
			if (NULL == pStart)
			{
				break;
			}

			pCanvas->PushClip(lpRgn);
			DMDRAW_STATE Render_State = DRAW_START;
			_OnRender(pCanvas,lpRgn,pWnd,pStart,NULL,Render_State);
			pCanvas->PopClip();

			iErr = DM_ECODE_OK;
		} while (false);
		return iErr;
	}

	DMCode DMDrawImpl::Draw(IDMCanvas* pCanvas, IDMRegion* lpRgn,DUIWindow* pWnd)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			DMDRAW_STATE Render_State = DRAW_START;
			if (NULL == lpRgn)
			{	
				DMSmartPtrT<IDMRegion> pAllRgn;
				m_pRender->CreateRegion(&pAllRgn);
				CRect rcWnd;
				pWnd->DV_GetWindowRect(rcWnd);
				pAllRgn->CombineRect(rcWnd, RGN_OR);
				iErr = _OnRender(pCanvas,pAllRgn,pWnd,pWnd,NULL,Render_State);
			}	
			else
			{
				iErr = _OnRender(pCanvas,lpRgn,pWnd,pWnd,NULL,Render_State);
			}
		}while(false);
		return iErr;
	}

	DMCode DMDrawImpl::InvalidateRect(DUIWND hDUIWnd,LPCRECT lpRect,int fnCombineMode)
	{// Ŀ��:m_pInvalidRegion����������Ч��,m_bOnlyOneRectRepaint��¼�Ƿ�Ϊ��Ч������

		CRect rcInvalid = m_rcCanvas;
		do 
		{
			//1.�ж��Ƿ���Ч����
			if (NULL == lpRect)
			{// ΪNULLʱʹ�û�����С,��ʱֻ����Ч����m_rcCanvas
				m_bOnlyOneRectRepaint = true;
				m_rcOnlyOne = m_rcCanvas;
				break;
			}

			//2.�ж��Ƿ�Ϊ��
			rcInvalid = lpRect;
			rcInvalid.left = rcInvalid.left>0?rcInvalid.left:0;
			rcInvalid.top = rcInvalid.top>0?rcInvalid.top:0;
			if (rcInvalid.IsRectEmpty())
			{
				rcInvalid.SetRectEmpty();
				break;
			}
			//4.����һ��Rectʱ,ǰ���ų�lpRectΪNULL��״̬,��ʱֻ����Ч����
			if (RGN_COPY == fnCombineMode
				||RGN_AND == fnCombineMode
				)
			{
				m_bOnlyOneRectRepaint = true;
				m_rcOnlyOne = rcInvalid;
				break;
			}

			//5. ǰ������������lpRect��ΪNULL,�Ҳ���ȫˢ��,�Ҳ���RGN_COPY||RGN_AND
			if (m_bOnlyOneRectRepaint)
			{
				CRect rcNew = m_rcOnlyOne;
				rcNew.UnionRect(rcInvalid,m_rcOnlyOne);
				if (rcNew.EqualRect(m_rcOnlyOne)// �µ���Ч������ԭ��Ч��������
					||rcNew.EqualRect(rcInvalid))// �ɵ���Ч����������Ч��������
				{
					m_rcOnlyOne = rcNew;
					break;
				}
			}
			m_bOnlyOneRectRepaint = false;// ����һ����Ч����
		} while (false);

		// ��������ЧRgn����
		if (NULL == m_pInvalidRegion)
		{
			m_pRender->CreateRegion(&m_pInvalidRegion);
		}
		if (!rcInvalid.IsRectEmpty())
		{
			m_pInvalidRegion->CombineRect(&rcInvalid,fnCombineMode);// �����Ч��
			m_bNeedRepaint = true;
		}
		return DM_ECODE_OK;
	}

	int DMDrawImpl::GetInvalidateRect(DM::CArray<CRect>& Array)
	{
		do 
		{// ��Render�����߼�����һ��
			if (!m_bNeedRepaint)
			{
				break;
			}

			if (m_bOnlyOneRectRepaint)
			{
				if (!m_rcOnlyOne.IsRectEmpty())
				{
					Array.Add(m_rcOnlyOne);
				}
				break;
			}

			CRect rcInvalid;
			m_pInvalidRegion->GetRgnBox(&rcInvalid);
			if (rcInvalid.IsRectEmpty())
			{
				break;
			}
			if (rcInvalid.Width()+100<m_rcCanvas.Width()
				||rcInvalid.Height()+100<m_rcCanvas.Height())						// �󻭲�,��Ч����С��gdi�ڲ����Ż���,���Ƶ�Ч�ʻ���Ҫ������Ч����С�Ļ�����ֱ�ӻ���
			{
				int iNum = 0;
				DMBufT<RECT> pRect;
				if (DMSUCCEEDED(m_pInvalidRegion->GetRectNum(iNum)) // �ɹ���ȡ
					&&iNum<10&&iNum>1                               // ��Ч�����б���[2,10)֮��,1��ʾm_pInvalidRegion����һ������
					&&NULL!=pRect.Allocate(iNum)                    // �ڴ����ɹ�
					&&DMSUCCEEDED(m_pInvalidRegion->GetRectArray(pRect,iNum))
					)
				{
					for (int i=0;i<iNum;i++)
					{
						CRect rcRect = pRect+i;
						Array.Add(rcRect);
					}
				}
				else
				{
					Array.Add(rcInvalid);
				}
			}
			else
			{
				Array.Add(rcInvalid);
			}

		} while (false);
		return (int)Array.GetCount();
	}

	DMCode DMDrawImpl::Render(DUIWindow* pWnd)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			if (!m_bNeedRepaint)
			{
				break;
			}
			m_bNeedRepaint = false;
			if (m_bOnlyOneRectRepaint)// ֻ��һ����Ч����
			{
				if (m_rcOnlyOne.IsRectEmpty())
				{
					break;
				}
				if (m_rcOnlyOne != m_rcCanvas)
				{
					m_pMemCanvas->PushClip(m_rcOnlyOne,RGN_COPY);	
				}

				m_pMemCanvas->ClearRect(m_rcOnlyOne,0);		
				DMSmartPtrT<IDMFont> pOldFont;
				m_pMemCanvas->SelectObject(g_pDMApp->GetFont(L""),(IDMMetaFile**)&pOldFont);
				m_pMemCanvas->SelectObject(pOldFont);

				Draw(m_pMemCanvas,m_pInvalidRegion,pWnd);

				if (m_rcOnlyOne != m_rcCanvas)
				{
					m_pMemCanvas->PopClip();	
				}
				m_pMemCanvas->SelectObject(pOldFont);
				m_rcOnlyOne.SetRectEmpty();
			}
			else// �����ж����Ч���ε�������Ч��
			{
				CRect rcInvalid;
				m_pInvalidRegion->GetRgnBox(&rcInvalid);
				m_pMemCanvas->PushClip(m_pInvalidRegion,RGN_COPY);						// ǿ������Ϊ��������С,ע�ⲻҪ��rcInvalid����ΪrcInvalid���ܰ�������������Ҫˢ�µ��ӿؼ�����
				m_pMemCanvas->ClearRect(rcInvalid,0);									// ���������alphaֵ
				DMSmartPtrT<IDMFont> pOldFont;
				m_pMemCanvas->SelectObject(g_pDMApp->GetFont(L""),(IDMMetaFile**)&pOldFont);
				if (rcInvalid.Width()+100<m_rcCanvas.Width()
					||rcInvalid.Height()+100<m_rcCanvas.Height())						// �󻭲�,��Ч����С��gdi�ڲ����Ż���,���Ƶ�Ч�ʻ���Ҫ������Ч����С�Ļ�����ֱ�ӻ���
				{
					int iNum = 0;
					DMBufT<RECT> pRect;
					if (DMSUCCEEDED(m_pInvalidRegion->GetRectNum(iNum)) // �ɹ���ȡ
						&&iNum<10&&iNum>1                               // ��Ч�����б���[2,10)֮��,1��ʾm_pInvalidRegion����һ������
						&&NULL!=pRect.Allocate(iNum)                    // �ڴ����ɹ�
						&&DMSUCCEEDED(m_pInvalidRegion->GetRectArray(pRect,iNum))
						)
					{
						for (int i=0;i<iNum;i++)
						{
							CRect rcRect = pRect+i;
							DMSmartPtrT<IDMCanvas>   pTempCanvas;
							m_pRender->CreateCanvas(rcRect.Width(),rcRect.Height(),&pTempCanvas);
							DMSmartPtrT<IDMFont> pOldTempFont;
							pTempCanvas->SelectObject(g_pDMApp->GetFont(L""),(IDMMetaFile**)&pOldTempFont);
							pTempCanvas->OffsetViewportOrg(-rcRect.left,-rcRect.top);// ��������rcInvalid.left������rcInvalid.top
							DMSmartPtrT<IDMRegion> pRgn;
							m_pRender->CreateRegion(&pRgn);
							pRgn->CombineRect(rcRect);
							Draw(pTempCanvas,pRgn,pWnd);
							pTempCanvas->SelectObject(pOldTempFont);
							m_pMemCanvas->BitBlt(pTempCanvas,rcRect.left,rcRect.top,rcRect);
						}
					}
					else
					{
						Draw(m_pMemCanvas,m_pInvalidRegion,pWnd);
					}
				}
				else
				{
					Draw(m_pMemCanvas,m_pInvalidRegion,pWnd);
				}
				m_pMemCanvas->SelectObject(pOldFont);
				m_pMemCanvas->PopClip();		
			}
			m_pInvalidRegion->Clear();												// ���ˢ����
			iErr = DM_ECODE_OK;
		} while (false);
		return iErr;
	}

	DMCode DMDrawImpl::GetCanvas(IDMCanvas** ppCanvas)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			if (NULL == ppCanvas
				||NULL == m_pMemCanvas)
			{
				break;
			}
			*ppCanvas = m_pMemCanvas;
			m_pMemCanvas->AddRef();
			iErr = DM_ECODE_OK;
		} while (false);
		return iErr;
	}

	DMCode DMDrawImpl::ResizeCanvas(SIZE size)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			if (NULL == m_pMemCanvas)
			{
				iErr = m_pRender->CreateCanvas(size.cx,size.cy,&m_pMemCanvas);
			}
			else
			{
				iErr = m_pMemCanvas->Resize(size);
			}
			m_rcCanvas.SetRect(0,0,size.cx,size.cy);
		} while (false);
		return iErr;
	}

	// ����
	DMCode DMDrawImpl::_OnRender(IDMCanvas* pCanvas, IDMRegion* pRgn,DUIWindow* pWndCur,DUIWindow* pStart,DUIWindow *pEnd, DMDRAW_STATE& Draw_State)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			if (NULL == pRgn										// ��Ч��ΪNULL
				||pRgn->IsEmpty()									// ��Ч��Ϊ��
				||DRAW_END == Draw_State							// �����������
				||(DRAW_DRAWING == Draw_State && pWndCur == pEnd))  // ����������־�����ˣ�����־����һ��ΪNULL����㴰��
			{
				Draw_State = DRAW_END;
				break;
			}

			CRect rcPlaceHolder;
			pWndCur->DV_GetWindowRect(&rcPlaceHolder);				// ���ռλ��С���粻��ʾ
			if (!pWndCur->DM_IsVisible(true)						// ���ڲ��ɼ�
				||!pRgn->RectInRegion(&rcPlaceHolder)				// ռλ�ͻ������޽���
				||rcPlaceHolder.IsRectEmpty())                      // ռλΪ��
			{
				break;
			}

			if (DRAW_START == Draw_State&&pWndCur == pStart)
			{//0. ��ʼ���л���,���Ǹ���ѯ��pWndCur������pStart�ĸ����ڣ��ϲ㴰�ڣ�������������ҵ���ʼ���Ƶ�
				Draw_State = DRAW_DRAWING;
			}

			DMDRAW_STATE DrawBack = Draw_State;    // ���浱ǰ�Ļ���״̬,�ڵݹ������������״̬���ж��Ƿ���Ҫ���Ʒǿͻ���
			CRect rcClient;
			pWndCur->DV_GetClientRect(&rcClient);
			if (DRAW_DRAWING == DrawBack            // ����״̬
				&&pRgn->RectInRegion(rcClient)		  // �ӿؼ�����ͻ������н���
				)
			{// 1.��������ͻ���
				if (pWndCur->DV_IsOnlyDrawClient())
				{
					pCanvas->PushClip(&rcClient);
				}
				if (pWndCur->DM_IsDrawToCache())
				{
					CRect rcWnd = pWndCur->m_rcWindow;
					IDMCanvas* pCacheCanvas =  pWndCur->DM_GetCacheCanvas();
					if (pCacheCanvas&&pWndCur->DM_IsCacheDirty()) 
					{//1.1 ���滭�����࣬��Ҫ����
						CPoint pt = -rcWnd.TopLeft();
						pCacheCanvas->SetViewportOrgEx(pt.x,pt.y);

						pCacheCanvas->BitBlt(pCanvas,rcWnd.left,rcWnd.top,&rcWnd,SRCCOPY);//�Ѹ����ڵ����ݸ��ƹ�����

						DMSmartPtrT<IDMFont> oldFont;
						DMSmartPtrT<IDMFont> pFont;
						DMColor crOld = pCanvas->GetTextColor();
						if (pWndCur->DV_IsNeedDrawEnviron())//�Ƿ���Ҫ׼�����ƻ���
						{
							pCanvas->GetObject((IDMMetaFile**)&pFont,DMF_FONT);// ȡ�ô��������
							pCacheCanvas->SelectObject(pFont,(IDMMetaFile**)&oldFont);
							pCacheCanvas->SetTextColor(crOld);
						}

						pWndCur->DM_SendMessage(WM_ERASEBKGND, (WPARAM)pCacheCanvas);
						pWndCur->DM_SendMessage(WM_PAINT, (WPARAM)pCacheCanvas);

						if (pWndCur->DV_IsNeedDrawEnviron())
						{
							pCacheCanvas->SelectObject(oldFont);
							pCacheCanvas->SetTextColor(crOld);
						}

						pWndCur->DM_MarkCacheDirty(false);
					}
					pCanvas->BitBlt(pCacheCanvas,rcWnd.left,rcWnd.top,&rcWnd,SRCCOPY);
				}
				else
				{
					pWndCur->DM_SendMessage(WM_ERASEBKGND, (WPARAM)pCanvas);
					pWndCur->DM_SendMessage(WM_PAINT, (WPARAM)pCanvas);
				}
			}

			DUIDrawEnviron DrawEnviron;
			if (pWndCur->DV_IsNeedDrawEnviron())
			{			
				pWndCur->DV_PushDrawEnviron(pCanvas, DrawEnviron);    // ׼�����ƻ���
			}

			DUIWindow *pChild=pWndCur->DM_GetWindow(GDW_FIRSTCHILD);
			while (pChild) 	           // �ݹ����0
			{// 2. �ݹ���������Ӵ���
				if (pChild==pEnd)
				{
					break;             // �ݹ����1
				}
				_OnRender(pCanvas,pRgn,pChild,pStart,pEnd,Draw_State);
				if (Draw_State == DRAW_END)
				{
					break;             // �ݹ����2
				}
				pChild=pChild->DM_GetWindow(GDW_NEXTSIBLING);
			}

			if (pWndCur->DV_IsNeedDrawEnviron())
			{	
				pWndCur->DV_PopDrawEnviron(pCanvas, DrawEnviron);   // �������ƻ���
			}
			if(Draw_State == DRAW_DRAWING&&pWndCur->DV_IsOnlyDrawClient())
			{
				pCanvas->PopClip();
			}

			if (DRAW_DRAWING == Draw_State)
			{// 3. ����ݹ���Ʒǿͻ����������Ӵ������Ȼ�ǿͻ���
				pWndCur->DM_SendMessage(WM_NCPAINT, (WPARAM)pCanvas);
			}

			if (DRAW_DRAWING == Draw_State||Draw_State == DRAW_END)
			{
				iErr = DM_ECODE_OK;
			}
		} while (false);
		return iErr;
	}

}//namespace DM