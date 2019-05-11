#include "DmMainAfx.h"
#include "DMContainerImpl.h"

namespace DM
{
	DMContainerImpl::DMContainerImpl(DUIWindow *pHWnd)
		:m_pContainWnd(pHWnd)
		,m_FocusMgr(pHWnd)
		,m_DropTarget(pHWnd)
	{
		m_hDUICaptureWnd = 0;
		m_hDUIHoverWnd	 = 0;
		m_bNcHover		 = false;
	}

	LRESULT DMContainerImpl::OnFrameEvent(UINT uMsg,WPARAM wParam,LPARAM lParam)
	{
		LRESULT lRet = 0;
		m_pContainWnd->AddRef();
		m_pContainWnd->SetMsgHandled(TRUE);
		switch (uMsg)
		{// �˲�����Ϣ��ֱ�Ӳο�DMMsgCrack.h��
		case WM_MOUSEMOVE:
			{
				OnFrameMouseMove((UINT)wParam,CPoint(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)));
			}
			break;

		case WM_MOUSEHOVER:
			{
				OnFrameMouseEvent(uMsg,wParam,lParam);
			}
			break;

		case WM_MOUSELEAVE:
			{
				OnFrameMouseLeave();
			}
			break;

		case WM_SETCURSOR:
			{
				lRet = DMSUCCEEDED(OnFrameSetCursor(CPoint(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam))));
			}
			break;

		case WM_KEYDOWN:
			{
				OnFrameKeyDown((UINT)wParam,(UINT)lParam&0xFFFF, (UINT)((lParam&0xFFFF0000)>>16));
			}
			break;

		case WM_SETFOCUS:
			{
				OnActivate(WA_ACTIVE);
			}
			break;

		case WM_KILLFOCUS:
			{
				OnActivate(WA_INACTIVE);
			}
			break;

		case WM_ACTIVATE:// WM_ACTIVATEֻ�����������ʧȥ�����ָ������
			{
				OnActivate(LOWORD(wParam));
			}
			break;

		case WM_ACTIVATEAPP:// WM_ACTIVATEAPP�����������ʧȥ�����Ӧ�ó�����ӵ�е����д���
			{
				OnActivateApp((BOOL)wParam,(DWORD)lParam);
			}
			break;

		case WM_IME_STARTCOMPOSITION:
		case WM_IME_ENDCOMPOSITION:
		case WM_IME_COMPOSITION:
		case WM_IME_CHAR:
			{
				OnFrameKeyEvent(uMsg,wParam,lParam);
			}
			break;

		default:
			{
				if (uMsg>=WM_KEYFIRST&&uMsg<=WM_KEYLAST)// KeyDown���
				{
					OnFrameKeyEvent(uMsg,wParam,lParam);
				}
				else if(uMsg>=WM_MOUSEFIRST&&uMsg<= WM_MOUSELAST)// ��������
				{
					OnFrameMouseEvent(uMsg,wParam,lParam);
				}
				else
				{
					m_pContainWnd->SetMsgHandled(FALSE);
				}
			}
			break;
		}
		m_pContainWnd->Release();
		return lRet;
	}

	DMCode DMContainerImpl::OnSetFocusWnd(DUIWND DUIWnd)
	{
		HWND hWnd = OnGetHWnd();
		if (DUIWnd && ::GetFocus()!=hWnd&& !(::GetWindowLongPtr(hWnd,GWL_EXSTYLE)&WS_EX_TOOLWINDOW))
		{
			::SetFocus(hWnd);
		}

		m_FocusMgr.SetFocusedWnd(DUIWnd);
		return DM_ECODE_OK;
	}

	DMCode DMContainerImpl::OnGetFocusWnd(DUIWND &DUIWnd)
	{
		DUIWnd = m_FocusMgr.GetFocusedWnd();
		return DM_ECODE_OK;
	}

	DMCode DMContainerImpl::OnSetCaptureWnd(DUIWND DUIWnd,DUIWNDPtr pOldDUIWnd/*=NULL*/)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			DUIWindow *pWnd = g_pDMDWndPool->FindDUIWnd(DUIWnd);
			if (NULL == pWnd
				||pWnd->DM_IsDisable(true)
				)
			{
				break;
			}

			if (pOldDUIWnd)
			{
				*pOldDUIWnd = m_hDUICaptureWnd;
			}
			m_hDUICaptureWnd = DUIWnd;
			iErr = DM_ECODE_OK;
		} while (false);
		return iErr;
	}

	DMCode DMContainerImpl::OnGetCaptureWnd(DUIWND &DUIWnd)
	{
		DUIWnd = m_hDUICaptureWnd;
		return DM_ECODE_OK;
	}

	DMCode DMContainerImpl::OnReleaseCaptureWnd()
	{
		m_hDUICaptureWnd = 0;
		return DM_ECODE_OK;
	}

	DMCode DMContainerImpl::OnRegisterDragDrop(DUIWND hDUIWnd, IDropTarget *pDropTarget)
	{
		if (m_DropTarget.RegisterDragDrop(hDUIWnd,pDropTarget))
		{
			return DM_ECODE_OK;
		}
		return DM_ECODE_FAIL;
	}

	DMCode DMContainerImpl::OnUnRegisterDragDrap(DUIWND hDUIWnd)
	{
		if (m_DropTarget.UnRegisterDragDrap(hDUIWnd))
		{
			return DM_ECODE_OK;
		}
		return DM_ECODE_FAIL;
	}

	DMCode DMContainerImpl::OnRegisterTimeline(IDMTimeline *pHandler)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			if (NULL == pHandler)
			{
				break;
			}
			POSITION pos = m_TimelineList.Find(pHandler);
			if (pos)
			{
				break;
			}

			m_TimelineList.AddTail(pHandler);
			iErr = DM_ECODE_OK;
		} while (false);
		return iErr;
	}

	DMCode DMContainerImpl::OnUnregisterTimeline(IDMTimeline *pHandler)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			if (NULL == pHandler)
			{
				break;
			}
			POSITION pos = m_TimelineList.Find(pHandler);
			if (!pos)
			{
				break;
			}
			m_TimelineList.RemoveAt(pos);
			iErr = DM_ECODE_OK;
		} while (false);
		return iErr;
	}

	DMCode DMContainerImpl::OnTimeline()
	{
		DMTimelineHanderList TimelineList; 
		POSITION Pos = m_TimelineList.GetHeadPosition();
		while (Pos)// ����һ�ݣ���ֹԭ���ݱ���Ⱦ
		{
			IDMTimelinePtr &t = m_TimelineList.GetNext(Pos);
			TimelineList.AddTail(t);
		}

		Pos = TimelineList.GetHeadPosition();
		while (Pos)// ѭ������
		{
			IDMTimelinePtr pHandler = TimelineList.GetNext(Pos);
			pHandler->OnTimeline();
		}
		return DM_ECODE_OK;
	}

	// ���� -------------------------------------------
	// ����host window WM_MOUSEMOVE��Ϣ
	/*
	�߼���
	1.������Capture���ڣ�������괰�ڣ��������������Ϣ�����۹�꽹���Ƿ���DUI�����ڣ�
		1.1.���ͣ���ڴ��������ڣ���ʱCapture���ڼ�Ϊ�µ�MouseHover����(pHoverWnd==pCaptureWnd)
			1.1.1.ȡ�þɵ�MouseHover����(pOldHoverWnd)
			1.1.2.��(pOldHoverWnd!=NULL&&pOldHoverWnd!=pHoverWnd)����ԭΪ�ǿͻ���Hover״̬(true==m_bNcHover)����WM_NCMOUSELEAVE��������WM_MOUSELEAVE
			1.1.3.���÷ǿͻ���Hover״̬(m_bNcHover),�����µ�MouseHover���ھ����m_hDUIHoverWnd = hDUIHoverWnd��
			1.1.4.��(pHoverWnd!=pOldHoverWnd),��(true==m_bNcHover)����WM_NCMOUSEHOVER��������WM_MOUSEHOVER
		1.2.���δͣ���ڴ���������,��ʱ�µ�MouseHover����ΪNULL
			1.2.1.ȡ�þɵ�MouseHover����(pOldHoverWnd)
			1.2.2.��(pOldHoverWnd!=NULL)����ԭΪ�ǿͻ���Hover״̬(true==m_bNcHover)����WM_NCMOUSELEAVE��������WM_MOUSELEAVE
			1.2.3.�����µ�MouseHover���ھ��Ϊ0���������δͣ���ڷǿͻ���
	1.3.Capture������ԭΪ�ǿͻ���Hover״̬(true==m_bNcHover)����WM_NCMOUSEMOVE��������WM_MOUSEMOVE
	2.δ����Capture���ڣ��߼���1����
	*/
	void DMContainerImpl::OnFrameMouseMove(UINT uFlag,CPoint pt)
	{
		do 
		{
			DUIWindow *pCaptureWnd = g_pDMDWndPool->FindDUIWnd(m_hDUICaptureWnd);
			if (pCaptureWnd)
			{//1 Capture�£������Capture�����ڣ��Ͷ�Capture���ڷ�hover��Ϣ����ԭʼhover���ڷ�leave��Ϣ��ͬʱ����hover���ھ��
				CRect rcWindow;
				pCaptureWnd->DV_GetWindowRect(rcWindow);
				DUIWindow* pHoverWnd = rcWindow.PtInRect(pt)?pCaptureWnd:NULL;
				DUIWND hDUIHoverWnd = pHoverWnd?pHoverWnd->GetDUIWnd():0;
				if (hDUIHoverWnd != m_hDUIHoverWnd)
				{
					DUIWindow* pOldHoverWnd = g_pDMDWndPool->FindDUIWnd(m_hDUIHoverWnd);//1.1.1
					m_hDUIHoverWnd = hDUIHoverWnd;
					if (pOldHoverWnd)
					{
						 pOldHoverWnd->DM_SendMessage(m_bNcHover?WM_NCMOUSELEAVE:WM_MOUSELEAVE);
					}
					if (pHoverWnd)
					{
						pHoverWnd->DM_SendMessage(m_bNcHover?WM_NCMOUSEHOVER:WM_MOUSEHOVER,uFlag,MAKELPARAM(pt.x,pt.y));
					}
				}
				pCaptureWnd->DM_SendMessage(m_bNcHover?WM_NCMOUSEMOVE:WM_MOUSEMOVE,uFlag,MAKELPARAM(pt.x,pt.y));
				break;// Capture������
			}

			// 2.��Capture
			DUIWND hDUIHoverWnd = m_pContainWnd->HitTestPoint(pt);
			DUIWindow* pHoverWnd = g_pDMDWndPool->FindDUIWnd(hDUIHoverWnd);
			if (hDUIHoverWnd!=m_hDUIHoverWnd)
			{// 2.1��Hover���ڲ�ͬ��ԭʼhover���ڣ�����ڣ�ԭʼ��lever(nc+client),�µķ�(hover+nchover)��Ϣ
				DUIWindow* pOldHoverWnd = g_pDMDWndPool->FindDUIWnd(m_hDUIHoverWnd);
				m_hDUIHoverWnd = hDUIHoverWnd;
				if (pOldHoverWnd)
				{
					if (m_bNcHover) 
					{
						pOldHoverWnd->DM_SendMessage(WM_NCMOUSELEAVE);
					}
					pOldHoverWnd->DM_SendMessage(WM_MOUSELEAVE);
				}

				if (pHoverWnd&&!pHoverWnd->DM_IsDisable(true))
				{
					m_bNcHover = DMSUCCEEDED(pHoverWnd->DV_OnNcHitTest(pt));
					if (m_bNcHover) 
					{
						pHoverWnd->DM_SendMessage(WM_NCMOUSEHOVER,uFlag,MAKELPARAM(pt.x,pt.y));
					}
					pHoverWnd->DM_SendMessage(WM_MOUSEHOVER,uFlag,MAKELPARAM(pt.x,pt.y));
				}
			}
			else if (pHoverWnd&&!pHoverWnd->DM_IsDisable(true))
			{// 2.2ǰ�ᣬ��hover����==ԭʼhover���ڣ���ʱ����nchover״̬����mouse��Ϣ
				bool bNcHover = DMSUCCEEDED(pHoverWnd->DV_OnNcHitTest(pt));
				if (bNcHover != m_bNcHover)
				{
					m_bNcHover = bNcHover;
					if (m_bNcHover)
					{
						pHoverWnd->DM_SendMessage(WM_MOUSELEAVE);
						pHoverWnd->DM_SendMessage(WM_NCMOUSEHOVER,uFlag,MAKELPARAM(pt.x,pt.y));
					}
					else
					{
						pHoverWnd->DM_SendMessage(WM_NCMOUSELEAVE);
						pHoverWnd->DM_SendMessage(WM_MOUSEHOVER,uFlag,MAKELPARAM(pt.x,pt.y));
					}
				}
			}
			if (pHoverWnd&&!pHoverWnd->DM_IsDisable(TRUE))
			{
				pHoverWnd->DM_SendMessage(m_bNcHover?WM_NCMOUSEMOVE:WM_MOUSEMOVE,uFlag,MAKELPARAM(pt.x,pt.y));
			}

		} while (FALSE);

#if 0
		do 
		{
			DUIWindow *pCaptureWnd = g_pDMDWndPool->FindDUIWnd(m_hDUICaptureWnd);
			if (pCaptureWnd)
			{//1
				CRect rcWindow;
				pCaptureWnd->DV_GetWindowRect(rcWindow);
				bool bInRect = false;
				if (rcWindow.PtInRect(pt))
				{//1.1
					bInRect = true;
				}

				if (bInRect)
				{
					DUIWindow* pOldHoverWnd = g_pDMDWndPool->FindDUIWnd(m_hDUIHoverWnd);//1.1.1
					if (pOldHoverWnd&&pOldHoverWnd!=pCaptureWnd)//pOldHoverWnd==pCaptureWnd ��ʾ��Ϊԭ��Hover����
					{//1.1.2
						pOldHoverWnd->DM_SendMessage(m_bNcHover?WM_NCMOUSELEAVE:WM_MOUSELEAVE);
					}	
					m_bNcHover		= pCaptureWnd->DMSUCCEEDED(DV_OnNcHitTest(pt));//1.1.3
					m_hDUIHoverWnd  = pCaptureWnd->GetDUIWnd();	   //1.1.3
					if (pOldHoverWnd != pCaptureWnd)
					{
						pCaptureWnd->DM_SendMessage(m_bNcHover?WM_NCMOUSEHOVER:WM_MOUSEHOVER,uFlag,MAKELPARAM(pt.x,pt.y));//1.1.4
					}
				}
				else
				{//1.2
					DUIWindow* pOldHoverWnd = g_pDMDWndPool->FindDUIWnd(m_hDUIHoverWnd);//1.2.1
					if (pOldHoverWnd)
					{//1.2.2
						pOldHoverWnd->DM_SendMessage(m_bNcHover?WM_NCMOUSELEAVE:WM_MOUSELEAVE);
					}	
					m_hDUIHoverWnd = 0;			//1.2.3
					m_bNcHover     = false;		//1.2.3
				}
				pCaptureWnd->DM_SendMessage(m_bNcHover?WM_NCMOUSEMOVE:WM_MOUSEMOVE,uFlag,MAKELPARAM(pt.x,pt.y));
			}
			else
			{
				DUIWND hDUIHoverWnd = m_pContainWnd->HitTestPoint(pt);
				DUIWindow* pHoverWnd = g_pDMDWndPool->FindDUIWnd(hDUIHoverWnd);
				if (hDUIHoverWnd!=m_hDUIHoverWnd)
				{
					DUIWindow* pOldHoverWnd = g_pDMDWndPool->FindDUIWnd(m_hDUIHoverWnd);
					m_hDUIHoverWnd = hDUIHoverWnd;
					if (pOldHoverWnd)
					{
						pOldHoverWnd->DM_SendMessage(m_bNcHover?WM_NCMOUSELEAVE:WM_MOUSELEAVE);
					}

					if (pHoverWnd&&!pHoverWnd->DM_IsDisable(true))
					{
						m_bNcHover = pHoverWnd->DMSUCCEEDED(DV_OnNcHitTest(pt));
						pHoverWnd->DM_SendMessage(m_bNcHover?WM_NCMOUSEHOVER:WM_MOUSEHOVER,uFlag,MAKELPARAM(pt.x,pt.y));
					}
				}
				else if (pHoverWnd&&!pHoverWnd->DM_IsDisable(true))
				{
					bool bNcHover = pHoverWnd->DMSUCCEEDED(DV_OnNcHitTest(pt));
					if (bNcHover != m_bNcHover)
					{
						m_bNcHover = bNcHover;
						if (m_bNcHover)
						{
							pHoverWnd->DM_SendMessage(WM_MOUSELEAVE);
							pHoverWnd->DM_SendMessage(WM_NCMOUSEHOVER,uFlag,MAKELPARAM(pt.x,pt.y));
						}
						else
						{
							pHoverWnd->DM_SendMessage(WM_NCMOUSELEAVE);
							pHoverWnd->DM_SendMessage(WM_MOUSEHOVER,uFlag,MAKELPARAM(pt.x,pt.y));
						}
					}
				}
				if (pHoverWnd&&!pHoverWnd->DM_IsDisable(TRUE))
				{
					pHoverWnd->DM_SendMessage(m_bNcHover?WM_NCMOUSEMOVE:WM_MOUSEMOVE,uFlag,MAKELPARAM(pt.x,pt.y));
				}
			}	

		} while (false);
#endif //0
	}

	//-----------------------------------------------
	// ��������������Ϣ��MOUSEHOVER��Ϣ
	void DMContainerImpl::OnFrameMouseEvent(UINT uMsg,WPARAM wParam,LPARAM lParam)
	{
		DUIWindow* pCaptureWnd = g_pDMDWndPool->FindDUIWnd(m_hDUICaptureWnd);
		if (pCaptureWnd)
		{// Capture���ڲ��������������Ϣ�����������
			if (m_bNcHover&&WM_MOUSEWHEEL!=uMsg)
			{
				uMsg += WM_NCMOUSEFIRST-WM_MOUSEFIRST;// ת����NC��Ӧ����Ϣ
			}
			BOOL bMsgHandled = FALSE;
			pCaptureWnd->DM_SendMessage(uMsg,wParam,lParam,&bMsgHandled);// ת����Ϣ
			m_pContainWnd->SetMsgHandled(bMsgHandled);
		}
		else
		{
			m_hDUIHoverWnd = m_pContainWnd->HitTestPoint(CPoint(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)));
			DUIWindow* pHoverWnd = g_pDMDWndPool->FindDUIWnd(m_hDUIHoverWnd);
			if (pHoverWnd&&!pHoverWnd->DM_IsDisable(true))
			{
				if (m_bNcHover&&WM_MOUSEWHEEL!=uMsg)
				{
					uMsg += WM_NCMOUSEFIRST-WM_MOUSEFIRST;// ת����NC��Ӧ����Ϣ
				}
				BOOL bMsgHandled = FALSE;
				pHoverWnd->DM_SendMessage(uMsg,wParam,lParam,&bMsgHandled);// ת����Ϣ
				m_pContainWnd->SetMsgHandled(bMsgHandled);
			}
			else
			{
				m_pContainWnd->SetMsgHandled(FALSE);
			}
		}
	}

	// ����WM_MOUSELEAVE
	void DMContainerImpl::OnFrameMouseLeave()
	{
		DUIWindow* pCaptureWnd = g_pDMDWndPool->FindDUIWnd(m_hDUICaptureWnd);
		if (pCaptureWnd)
		{
			pCaptureWnd->DM_SendMessage(WM_MOUSELEAVE);
		}
		else if (m_hDUIHoverWnd)
		{
			DUIWindow* pHoverWnd = g_pDMDWndPool->FindDUIWnd(m_hDUIHoverWnd);
			if (pHoverWnd&&!pHoverWnd->DM_IsDisable(true))
			{
				pHoverWnd->DM_SendMessage(m_bNcHover?WM_NCMOUSELEAVE:WM_MOUSELEAVE);
			}
		}

		m_hDUIHoverWnd = 0;
	}

	// 
	DMCode DMContainerImpl::OnFrameSetCursor(const CPoint &pt)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			DUIWindow* pCaptureWnd = g_pDMDWndPool->FindDUIWnd(m_hDUICaptureWnd);
			if (pCaptureWnd)
			{
				iErr = pCaptureWnd->DV_OnSetCursor(pt);
			}
			else
			{	
				DUIWindow* pHoverWnd = g_pDMDWndPool->FindDUIWnd(m_hDUIHoverWnd);
				if (pHoverWnd&&!pHoverWnd->DM_IsDisable(true))
				{
					iErr = pHoverWnd->DV_OnSetCursor(pt);
				}
			}

			if (!DMSUCCEEDED(iErr))
			{// ����Ϊ��׼�ļ�ͷ
				HCURSOR hCursor = ::LoadCursorW(NULL, IDC_ARROW);
				::SetCursor(hCursor);
			}
		} while (false);
		return iErr;
	}

	void DMContainerImpl::OnFrameKeyEvent(UINT uMsg,WPARAM wParam,LPARAM lParam)
	{
		DUIWindow* pFocusWnd = g_pDMDWndPool->FindDUIWnd(m_FocusMgr.GetFocusedWnd());
		if (pFocusWnd)
		{
			BOOL bMsgHandled = FALSE;
			pFocusWnd->DM_SendMessage(uMsg,wParam,lParam,&bMsgHandled);
			m_pContainWnd->SetMsgHandled(bMsgHandled);
		}
		else
		{
			m_pContainWnd->SetMsgHandled(FALSE);
		}
	}

	// ����WM_KEYDOWN��Ϣ
	void DMContainerImpl::OnFrameKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		do 
		{
			if (m_FocusMgr.OnKeyDown(nChar))
			{// ���ȴ������л�
				break;
			}
			OnFrameKeyEvent(WM_KEYDOWN,(WPARAM)nChar,MAKELPARAM(nRepCnt,nFlags));
		} while (FALSE);
	}

	void DMContainerImpl::OnActivate(UINT nState)
	{
		if (WA_INACTIVE == nState)
		{
			m_FocusMgr.StoreFocuseWnd();  // �洢��ǰ���㴰��
		}
		else if (WA_ACTIVE == nState)
		{
			m_FocusMgr.RestoreFocuseWnd();// �ָ���ǰ���㴰��
		}
	}

	void DMContainerImpl::OnActivateApp( BOOL bActive, DWORD dwThreadID )
	{
		MSG Msg = {0,WM_ACTIVATEAPP,MAKEWPARAM(bActive,0),MAKELPARAM(dwThreadID,0),0};
		m_pContainWnd->DM_DispatchMessage(&Msg);
	}



}//namespace DM