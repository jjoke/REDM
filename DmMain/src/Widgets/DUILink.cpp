#include "DmMainAfx.h"
#include "DUILink.h"

namespace DM
{
	DMCode DUILink::DV_OnSetCursor(const CPoint &pt)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			if (!m_rcText.IsRectEmpty()// ����Ϊ��ʱ����ֱ�����ðɣ�ֻ��ͼ����
				&&!m_rcText.PtInRect(pt))
			{
				break;
			}

			iErr = __super::DV_OnSetCursor(pt);
		} while (false);
		return iErr;
	}

	DMCode DUILink::DV_DrawText(IDMCanvas* pCanvas, LPCWSTR pszBuf,int cchText,LPRECT lpRect,UINT uFormat)
	{
		CalcTextRect(pCanvas,pszBuf, cchText, lpRect, uFormat);
		return __super::DV_DrawText(pCanvas,pszBuf, cchText,lpRect,uFormat);
	}

	void DUILink::OnLButtonDown(UINT nFlags,CPoint pt)
	{
		if (!m_rcText.IsRectEmpty()// ����Ϊ��ʱ����ֱ�����ðɣ�ֻ��ͼ����
			&&!m_rcText.PtInRect(pt)) 
		{
			return;
		}
		__super::OnLButtonDown(nFlags,pt);
	}

	void DUILink::OnLButtonUp(UINT nFlags,CPoint pt)
	{
		if(!m_rcText.IsRectEmpty()// ����Ϊ��ʱ����ֱ�����ðɣ�ֻ��ͼ����
			&&!m_rcText.PtInRect(pt))
		{
			DM_ReleaseCapture();
			return;
		}
		__super::OnLButtonUp(nFlags,pt);
		if (!m_strLinkUrl.IsEmpty())
		{
			//��ʹ��Ĭ��������򿪣�����ʧ�ܣ�������Ĭ�������������ǿ��ʹ��IE��
			HINSTANCE hIns = ::ShellExecute(NULL, _T("open"), m_strLinkUrl, NULL, NULL, SW_SHOWNORMAL);
			if ((LPARAM)(hIns) <= 32 )	//If the function succeeds, it returns a value greater than 32.
			{
				ShellExecute(NULL, _T("open"), _T("iexplore.exe"), m_strLinkUrl, NULL, SW_SHOW);
			}

		}
	}

	void DUILink::OnMouseMove(UINT nFlags,CPoint pt)
	{
		if (!m_rcText.IsRectEmpty()// ����Ϊ��ʱ����ֱ�����ðɣ�ֻ��ͼ����
			&&!m_rcText.PtInRect(pt))
		{
			if (m_dwDUIState&DUIWNDSTATE_Hover)
			{
				OnMouseLeave();
			}

		}
		else
		{
			if (!(m_dwDUIState&DUIWNDSTATE_Hover))
			{
				OnMouseHover(nFlags, pt);
			}
		}
	}

	void DUILink::OnMouseHover(WPARAM wParam, CPoint pt)
	{
		if (!m_rcText.IsRectEmpty()// ����Ϊ��ʱ���Ͳ����˰ɣ�ֻ��ͼ����
			&&!m_rcText.PtInRect(pt))
		{
			return;
		}
		__super::OnMouseHover(wParam, pt);
	}


	// ����
	void DUILink::CalcTextRect(IDMCanvas* pCanvas, LPCWSTR pszBuf,int cchText,LPRECT pRect,UINT uFormat)
	{
		if(!(uFormat&DT_CALCRECT))
		{
			CRect rcText; //1. �������������ռ��С
			pCanvas->DrawText(pszBuf,cchText,&rcText,DT_LEFT|DT_CALCRECT);

			UINT uAlign = 0;
			m_pDUIXmlInfo->m_pStyle->GetTextAlign(uAlign);
			if (uAlign&DT_CENTER)
			{// 2.1���ˮƽ���У����������rc������
				m_rcText.left  = pRect->left + (pRect->right-pRect->left - rcText.Width())/2;
				m_rcText.right = m_rcText.left + rcText.Width();
			}
			else if (uAlign&DT_RIGHT)
			{// 2.2 ������ң������Ϊ�Ҷ���
				m_rcText.left  = pRect->right - rcText.Width();
				m_rcText.right = pRect->right;
			}
			else
			{// 2.3����Ϊ�����
				m_rcText.left  = pRect->left;
				m_rcText.right = pRect->left + rcText.Width();
			}

			if(uAlign&DT_VCENTER)
			{// 3.1��������
				m_rcText.top    = pRect->top+ (pRect->bottom-pRect->top-rcText.Height())/2;
				m_rcText.bottom = m_rcText.top+rcText.Height();
			}
			else if(uAlign&DT_BOTTOM)
			{// 3.2����Ϊ�¶���
				m_rcText.bottom = m_rcText.bottom;
				m_rcText.top    = m_rcText.bottom-rcText.Height();
			}
			else
			{// 3.3����Ϊ�϶���
				m_rcText.top    = m_rcText.top;
				m_rcText.bottom = m_rcText.top+rcText.Height();
			}
		}
	}

}//namespace DM