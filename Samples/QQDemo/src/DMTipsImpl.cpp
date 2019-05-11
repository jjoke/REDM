#include "QQDemoAfx.h"
#include "DMTipsImpl.h"

namespace DM
{
//----------------------------------------------------------------------------------
#define TIMERID_DELAY    1
#define TIMERID_SPAN     2
#define MARGIN_TIP       5
	BEGIN_MSG_MAP(DMTipsImpl)
		MSG_WM_TIMER(OnTimer)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()
	DMTipsImpl::DMTipsImpl(void)
	:m_iDelayTime(500),
	m_iSpanTime(5000),
	m_bShowing(false)
	{
		m_rcPosFlags.SetRect(-1,0,0,0);
	}

	DMTipsImpl::~DMTipsImpl(void)
	{
	}

	bool DMTipsImpl::Create()
	{
		bool bRet = false;
		do 
		{
			if (IsWindow())
			{
				bRet = true;
				break;
			}
			ATOM Atom = g_pDMApp->GetClassAtom(true);  // �Ƿ�ʹ����Ӱ�����ഴ��
			HWND hWnd = DMCWnd::CreateWindowEx((LPCWSTR)Atom,L"tips",WS_POPUP,WS_EX_TOOLWINDOW|WS_EX_TOPMOST|WS_EX_NOACTIVATE,0,0,0,0,NULL,NULL);// �������صĶ�ʱ������
			if (NULL == hWnd)
			{
				break;
			}
			ShowWindow(SW_HIDE);// Ĭ�����أ���ʹ���䶨ʱ������
			bRet = true;
		} while (false);
		return bRet;
	}

	bool DMTipsImpl::CreateTipsWnd()
	{
		bool bRet = false;
		do 
		{
			if (IsTipWindows())// �Ѵ���
			{
				bRet = true;
				break;
			}
			m_pWnd.Attach(new DMTipHWnd);
			if (!m_strXmlId.IsEmpty())
			{
				if (NULL == m_pWnd->DM_CreateWindowEx(m_strXmlId,L"tipsWnd",WS_POPUP,WS_EX_TOOLWINDOW|WS_EX_TOPMOST|WS_EX_NOACTIVATE,0,0,0,0,NULL,NULL,true))// ����������
				{
					break;
				}
			}
			else if (!m_strTip.IsEmpty())// �����򵥵�str����
			{
				DMAutoDC hdc;
				CRect rcText(0,0,500,1000);
				DrawText(hdc,m_strTip,-1,&rcText,DT_CALCRECT|DT_LEFT|DT_WORDBREAK);// �����ı���С

				CRect rcWnd = rcText;
				rcWnd.InflateRect(MARGIN_TIP,MARGIN_TIP);
				rcWnd.OffsetRect(-rcWnd.TopLeft());

				CStringW strXml;
				strXml.Format(L"<dm  initsize=\"%d,%d\"><root pos=\"0,0,-0,-0\" skin=\"tip_frame\" text=\"%s\"/></dm>",rcWnd.Width(),rcWnd.Height(),m_strTip);
				int ulSize = 200;
				DMBufT<BYTE>pBuf;pBuf.Allocate(ulSize);
				UnicodeToUtf8(strXml.GetBuffer(),(PCHAR)pBuf.get(),ulSize);
				strXml.ReleaseBuffer();
				if (NULL == m_pWnd->DM_CreateWindowEx(pBuf,ulSize,L"tipsWnd",WS_POPUP,WS_EX_TOOLWINDOW|WS_EX_TOPMOST|WS_EX_NOACTIVATE,0,0,0,0,NULL,NULL,true))// ����������
				{
					break;
				}
			}
			CPoint pt;
			GetCursorPos(&pt);
			m_pWnd->SetWindowPos(0,pt.x,pt.y,0,0,SWP_NOSIZE|SWP_NOZORDER|SWP_NOSENDCHANGING|SWP_NOACTIVATE);
			m_pWnd->ShowWindow(SW_HIDE);
			bRet = true;
		} while (false);
		return bRet;
	}

	void DMTipsImpl::OnTimer(UINT_PTR idEvent)
	{
		switch (idEvent)
		{
		case TIMERID_DELAY:// ��ʾ,�ӳ���ʧ
			{
				m_bShowing = false;
				KillTimer(TIMERID_DELAY);      
				ShowTips(true);
				SetTimer(TIMERID_SPAN,m_iSpanTime);
			}
			break;

		case TIMERID_SPAN:
			{
				if (!IsCursorPtInRect())// ��ǰû��ͣ����tip������
				{
					m_bShowing = false;
					ShowTips(false);
					KillTimer(TIMERID_SPAN);
				}
			}
			break;
		}
	}

	//
	DMCode DMTipsImpl::Update(PDMToolTipInfo pInfo)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			if (NULL == pInfo)
			{
				break;
			}
			CStringW strXmlId = pInfo->strXmlId;
			CStringW strTip   = pInfo->strTip;

			if (IsTipWindows())
			{
				if ((!m_strXmlId.IsEmpty()&&strXmlId == m_strXmlId)// ԭ��ͨ��xmlid�����������´����xmlid����һ��
					||m_strXmlId.IsEmpty()&&!m_strTip.IsEmpty()&&strTip == m_strTip// ԭ��ͨ��text�����������´����text����һ��
					)
				{
				}
				else
				{
					DestroyTipsWnd();
				}
			}
			m_strXmlId	 = strXmlId;
			m_strTip	 = pInfo->strTip;
			m_rcPosFlags = pInfo->rcPosFlags;
			m_rcScreenTarget = pInfo->rcScreenTarget;
			Create();
			CreateTipsWnd();
	
			/// ��������
			m_rcTarget = pInfo->rcTarget;
			m_iDelayTime = pInfo->iDelayTime;
			m_iSpanTime  = pInfo->iSpanTime;

			if (m_pWnd->IsWindowVisible())
			{
				ShowTips(true);
			} 

			iErr = DM_ECODE_OK;
		} while (false);
		return iErr;
	}

	DMCode DMTipsImpl::Hide()
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			if (!IsTipWindows())
			{
				break;// ��ʱ��Ҫ�����ˣ���Ϊ����Ҳ���ܷ����������������ٺ���ʱ��Ϣѭ������û������
			}
			ShowTips(false);
			iErr = DM_ECODE_OK;
		} while (false);
		return iErr;
	}

	DMCode DMTipsImpl::Clear()
	{
		if (IsWindow())
		{
			DestroyWindow();
		}
		if (m_pWnd)
		{
			if (m_pWnd->IsWindow())
			{
				m_pWnd->DestroyWindow();
			}
			m_pWnd.Release();
		}
		return DM_ECODE_OK;
	}

	DMCode DMTipsImpl::RelayEvent(const MSG *pMsg)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			if (!IsTipWindows())
			{
				break;
			}

			switch (pMsg->message)
			{
			case WM_MOUSEMOVE:
				{
					CPoint pt(GET_X_LPARAM(pMsg->lParam),GET_Y_LPARAM(pMsg->lParam));

					if (!m_rcTarget.PtInRect(pt))
					{
						if (!IsCursorPtInRect())
						{
							OnTimer(TIMERID_SPAN);// ֱ������
						}
					}
					else if (IsTipWindows() && !m_pWnd->IsWindowVisible() && !m_bShowing)
					{
						KillTimer(TIMERID_DELAY);
						SetTimer(TIMERID_DELAY,m_iDelayTime);    
						m_bShowing = true;
						::ClientToScreen(pMsg->hwnd,&pt);
						m_pWnd->SetWindowPos(0,pt.x,pt.y,0,0,SWP_NOSIZE|SWP_NOZORDER|SWP_NOSENDCHANGING|SWP_NOACTIVATE);
					}
				}
				break;

			case WM_MOUSELEAVE:
				{
					CPoint pt(GET_X_LPARAM(pMsg->lParam),GET_Y_LPARAM(pMsg->lParam));

					if (!m_rcTarget.PtInRect(pt))
					{
						if (!IsCursorPtInRect())
						{
							OnTimer(TIMERID_SPAN);// ֱ������
						}
					}
				}
				break;
			}

			if (!m_pWnd->IsWindowVisible())
			{
				break;
			}
			iErr = DM_ECODE_OK;

		} while (false);
		return iErr;
	}

	BOOL DMTipsImpl::PreTranslateMessage(MSG* pMsg)
	{
		if (IsTipWindows()) 
		{
			RelayEvent(pMsg);
		}
		return FALSE;
	}

	// ����---------------------------------
	void DMTipsImpl::ShowTips(bool bShow)
	{
		do 
		{
			if (!IsTipWindows())
			{
				break;
			}

			if (!bShow)
			{
				m_bShowing = false;// ����ʱҪ����Ϊ������ʾ������
				m_rcTarget.SetRect(0,0,0,0);
				if (!m_pWnd->IsWindowVisible())
				{
					break;
				}
				m_pWnd->ShowWindow(SW_HIDE);
				KillTimer(TIMERID_DELAY);
				KillTimer(TIMERID_SPAN);
				break;// ����
			}

			CRect rcWnd;
			m_pWnd->GetWindowRect(&rcWnd);
			// ����̶�λ��
			int iFlags = m_rcPosFlags.left;
			bool bFixPos = (m_rcPosFlags.bottom!=0);
			if (-1 != iFlags)
			{
				int x = m_rcPosFlags.top;
				int y = m_rcPosFlags.right;
			
				int iWid = rcWnd.Width();
				int iHei = rcWnd.Height();
			
				if (TPM_LEFTALIGN == (iFlags&TPM_LEFTALIGN))//�����ô˱�־������ʹ��ݲ˵�����߽���m_rcScreenTarget.left+xָ�����������,ͬʱ��ݲ˵����ϱ߽��m_rcScreenTarget.bottom����
				{
					rcWnd.left = m_rcScreenTarget.left + x;
					rcWnd.right = rcWnd.left + iWid;
					rcWnd.top = m_rcScreenTarget.bottom;
					rcWnd.bottom = rcWnd.top + iHei;
				}
				if (TPM_RIGHTALIGN == (iFlags&TPM_RIGHTALIGN))//�����ô˱�־������ʹ��ݲ˵����ұ߽���m_rcScreenTarget.right+xָ�����������,ͬʱ��ݲ˵����ϱ߽��m_rcScreenTarget.bottom����
				{
					rcWnd.right = m_rcScreenTarget.right + x;
					rcWnd.left = rcWnd.right - iWid;
				}

				if (TPM_BOTTOMALIGN == (iFlags&TPM_BOTTOMALIGN))//�����ô˱�־������ʹ��ݲ˵����±߽�����m_rcScreenTarget.top+yָ�����������,
				{
					rcWnd.bottom = m_rcScreenTarget.top + y;
					rcWnd.top = rcWnd.bottom - iHei;
				}
			}

			if (-1 == m_rcPosFlags.left|| // δָ����ʾ����
				false == bFixPos)// ��ǿ�ƹ̶�
			{
			}
			HMONITOR hMonitor = ::MonitorFromRect(&rcWnd, MONITOR_DEFAULTTONEAREST);
			if (NULL != hMonitor)
			{
				MONITORINFO mi = {sizeof(MONITORINFO)};
				::GetMonitorInfo(hMonitor, &mi);
				CRect rcWork = mi.rcWork;
				if (rcWork.left < rcWork.right)
				{// �򵥵�֧��λ������Ļ��
					if (rcWnd.right > rcWork.right) 
						rcWnd.OffsetRect(rcWork.right - rcWnd.right, 0);
					if (rcWnd.bottom > rcWork.bottom)
						rcWnd.OffsetRect(0, rcWork.bottom - rcWnd.bottom);
					if (rcWnd.left < rcWork.left)
						rcWnd.OffsetRect(rcWork.left - rcWnd.left, 0);
					if (rcWnd.top < rcWork.top)
						rcWnd.OffsetRect(0, rcWork.top - rcWnd.top);
				}
			}
			m_pWnd->SetWindowPos(HWND_TOPMOST,rcWnd.left,rcWnd.top,rcWnd.Width(),rcWnd.Height(),SWP_NOSENDCHANGING|SWP_SHOWWINDOW|SWP_NOACTIVATE);
		} while (false);
	}

	bool DMTipsImpl::IsCursorPtInRect()
	{
		CPoint ptScreen;
		GetCursorPos(&ptScreen);
		CRect rcWnd;
		m_pWnd->GetWindowRect(rcWnd);
		if (!rcWnd.PtInRect(ptScreen))
		{
			return false;
		}
		return true;
	}

	void DMTipsImpl::DestroyTipsWnd()
	{
		if (m_pWnd)
		{
			if (m_pWnd->IsWindow())
			{
				m_pWnd->DestroyWindow();
			}
			m_pWnd.Release();
		}
	}
}//namespace DM