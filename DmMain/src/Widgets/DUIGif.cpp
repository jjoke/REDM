#include "DmMainAfx.h"
#include "DUIGif.h"

namespace DM
{
	DUIGif::DUIGif()
	{
		Clear();
		m_bAdjustPic  = true;    // Ĭ������gif����Ӧ����
		m_bCalcClip   = false;
	}

	DUIGif::~DUIGif()
	{
		Clear();
	}

	DMCode DUIGif::LoadFromFile(LPCWSTR pszFileName)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			wchar_t szPath[MAX_PATH] = {0};
			if (false == GetRootFullPath((wchar_t*)pszFileName, szPath,MAX_PATH))
			{
				break;
			}
			DWORD dwSize = GetFileSizeW(szPath);
			if (0 == dwSize)
			{
				break;
			}
			DMBufT<byte>pBuf;pBuf.Allocate(dwSize);
			DWORD dwRead;
			if (false == GetFileBufW(szPath, (void**)&pBuf,dwSize,dwRead))
			{
				break;
			}

			iErr = LoadFromMemory(pBuf,dwSize); 
		} while (false);
		return iErr;
	}

	DMCode DUIGif::LoadFromMemory(LPVOID lpBuf, UINT ulSize)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{
			Clear();
			DMSmartPtrT<IDMImgDecoder> pImgDecoder;DMSmartPtrT<IDMRes> pRes;DMSmartPtrT<IDMRender> pRender;
			g_pDMApp->CreateRegObj((void**)&pImgDecoder,NULL, DMREG_ImgDecoder);
			g_pDMApp->GetDefRegObj((void**)&pRes, DMREG_Res);
			g_pDMApp->GetDefRegObj((void**)&pRender,DMREG_Render);
			if (NULL== pImgDecoder||NULL == pRes||NULL == pRender)
			{
				break;
			}

			if (!DMSUCCEEDED(pImgDecoder->LoadFromMemory(lpBuf, ulSize)))
			{
				break;
			}
			pImgDecoder->GetTotalLoopCount(m_ulTotalLoopCount);
			pImgDecoder->GetFrameCount(m_ulFrameCount);
			if (1 == m_ulFrameCount)
			{// ��֡�¿�����GIF��Ҳ�����������ɱ�WIC�����ͼƬ
				DMAnimateFrame* pAnimateFrame = new DMAnimateFrame;
				memset(pAnimateFrame,0,sizeof(DMAnimateFrame));
				pRender->CreateBitmap(&pAnimateFrame->pBitmap);
				DMSmartPtrT<IDMImgFrame> pImgFrame;
				if (!DMSUCCEEDED(pImgDecoder->GetFrame(0,&pImgFrame)))
				{
					DM_DELETE(pAnimateFrame);
					break;
				}
				if (!DMSUCCEEDED(pAnimateFrame->pBitmap->InitFromFrame(pImgFrame)))
				{
					DM_DELETE(pAnimateFrame);
					break;
				}
				AddObj(pAnimateFrame);
				iErr = DM_ECODE_OK; 
				break;
			}

			if (1 >= m_ulFrameCount||0 == m_ulTotalLoopCount)
			{
				break;
			}
			// gif�����ʽ,wic���Խ���֡�����԰�ͼ�����ݲ���ȥ����
			bool bGif = false;
			DMSmartPtrT<DMGifParse> pObj;
			pObj.Attach(new DMGifParse);
			UINT ulMaxWid=0,ulMaxHei=0;
			if (pObj->LoadFromMemory((BYTE*)lpBuf,ulSize))
			{
				bGif = true;
				LPGLOBAL_INFO pGlobalInfo = pObj->GetGlobalInfo();
				DMASSERT_EXPR(pGlobalInfo->frames==m_ulFrameCount,L"�����֡��ͬ!");
				ulMaxWid = pGlobalInfo->scrWidth;
				ulMaxHei = pGlobalInfo->scrHeight;
			}
			for (int i=0;i<(int)m_ulFrameCount;i++)
			{
				DMAnimateFrame* pAnimateFrame = new DMAnimateFrame;
				memset(pAnimateFrame,0,sizeof(DMAnimateFrame));
				pRender->CreateBitmap(&pAnimateFrame->pBitmap);
				DMSmartPtrT<IDMImgFrame> pImgFrame;
				if (!DMSUCCEEDED(pImgDecoder->GetFrame(i,&pImgFrame)))
				{
					DM_DELETE(pAnimateFrame);
					break;
				}
				if (!DMSUCCEEDED(pAnimateFrame->pBitmap->InitFromFrame(pImgFrame)))
				{
					DM_DELETE(pAnimateFrame);
					break;
				}
				UINT ulDelay = 0;
				pImgFrame->GetDelay(ulDelay);
				if (bGif)
				{
					memcpy(&pAnimateFrame->gifFrame,pObj->GetFrame(i),sizeof(GIFFRAME));
					DMASSERT_EXPR(ulDelay==pAnimateFrame->gifFrame.ctrlExt.delayTime*10,L"������ӳٲ�ͬ!");
				}
				else
				{
					UINT ulWid=0,ulHei=0;
					pImgFrame->GetSize(ulWid,ulHei);
					ulMaxWid = DMMAX(ulMaxWid,ulWid);
					ulMaxHei = DMMAX(ulMaxHei,ulHei);
					pAnimateFrame->gifFrame.ctrlExt.delayTime = (WORD)ulDelay;
					pAnimateFrame->gifFrame.imageWidth  = (WORD)ulWid;
					pAnimateFrame->gifFrame.imageHeight = (WORD)ulHei;
					pAnimateFrame->gifFrame.ctrlExt.disposalMethod = DM_BACKGROUND;
				}
				AddObj(pAnimateFrame);
			}

			m_ulFrameCount = (UINT)GetCount();// �²�������֡���ܽ����ɹ�
			pRender->CreateCanvas(ulMaxWid,ulMaxHei,&m_pMemCanvas);
			pRender->CreateCanvas(ulMaxWid, ulMaxHei, &m_pPreviousCanvas);
			m_rcGif.SetRect(0,0,ulMaxWid,ulMaxHei);
			iErr = DM_ECODE_OK; 
		} while (false);
		if (!DMSUCCEEDED(iErr))
		{
			Clear();
		}
		return iErr;
	}

	DMCode DUIGif::Start()
	{
		Reset();
		if (IsReady())
		{
			GetContainer()->OnRegisterTimeline(this);// ע��
		}
		return DM_ECODE_OK;
	}

	DMCode DUIGif::Pause()
	{
		m_bPause = true;
		return DM_ECODE_OK;
	}

	DMCode DUIGif::Restart()
	{	
		m_bPause = false;
		if (IsReady())
		{
			GetContainer()->OnRegisterTimeline(this);// ע��
		}
		return DM_ECODE_OK;
	}

	DMCode DUIGif::Clear()
	{
		m_ulCurFrame	     = 0;
		m_ulFrameCount		 = 0;
		m_ulCurLoop          = 0;
		m_ulTotalLoopCount   = INFINITE;// Ĭ��������ѭ��
		m_dwPreFrameTime     = 0;       // ʱ��ˢ��ʱ��ʼ��
		m_bPause             = false;
		m_pMemCanvas.Release();
		m_pPreviousCanvas.Release();
		RemoveAll();
		return DM_ECODE_OK;
	}

	void DUIGif::DM_OnPaint(IDMCanvas* pCanvas)
	{
		do 
		{
			__super::DM_OnPaint(pCanvas);
			if (1 == m_ulFrameCount)
			{// ��֡�¿�����GIF��Ҳ�����������ɱ�WIC�����ͼƬ
				CRect rcClient;
				DV_GetClientRect(rcClient);
				PDMAnimateFrame pFrame = NULL;
				if (!GetObj(0,pFrame)||NULL == pFrame)
				{
					break;
				}
				if (pFrame->pBitmap.isValid())
				{
					CRect rcSrc(0,0,pFrame->pBitmap->GetWidth(),pFrame->pBitmap->GetHeight());
					if (m_bAdjustPic)
					{
						CSize szPic(rcSrc.Width(),rcSrc.Height());
						MeetRect(rcClient, szPic);
					}
					pCanvas->DrawBitamp(pFrame->pBitmap,&rcSrc,rcClient);
				}
				break;
			}

			int iState = ReadyCurFrame(m_ulCurFrame);
			if (DMGIF_NOREADY==iState)
			{
				break;
			}
			if (DMGIF_LOOPEND == iState)
			{
				m_ulCurFrame = 0;// ���ûس�ʼ֡
				m_ulCurLoop  = 0;// ���ûس�ʼloop
				m_bPause = true; // Endʱ����Ϊ��ʼ֡��ͣ״̬,�´ξ������²�����
			}
			CRect rcClient;
			DV_GetClientRect(rcClient);
			if (m_bAdjustPic)
			{
				CSize szPic(m_rcGif.Width(), m_rcGif.Height());
				MeetRect(rcClient, szPic);
			}
			bool bClip = false;
			if (DMGIF_READY == iState)
			{
				if (m_bCalcClip)
				{
					CRect rcInvalid;
					pCanvas->GetClipBox(rcInvalid);
					CRect rcDest = rcInvalid&rcClient;
					if (!rcDest.IsRectEmpty()&&rcClient!=rcDest)// ��Ч���ͻ������н���
					{
						bClip = true;
						pCanvas->PushClip(rcClient,RGN_OR);
					}
				}

				// ����
				PDMAnimateFrame &pFrame = m_DMArray[m_ulCurFrame];
				CRect rcFrame(pFrame->gifFrame.imageLPos, pFrame->gifFrame.imageTPos, 
					pFrame->gifFrame.imageLPos+pFrame->gifFrame.imageWidth,pFrame->gifFrame.imageTPos+pFrame->gifFrame.imageHeight);

				CRect rcSor = rcFrame;
				rcSor.OffsetRect(-rcSor.TopLeft());
				// If starting a new animation loop
				if (0 == m_ulCurFrame)
				{
					m_pMemCanvas->ClearRect(m_rcGif,0);
					m_pPreviousCanvas->ClearRect(m_rcGif, 0);
				}
				else
				{
					PDMAnimateFrame &pPreFrame = m_DMArray[m_ulCurFrame - 1];
					CRect rcPreFrame(pPreFrame->gifFrame.imageLPos, pPreFrame->gifFrame.imageTPos, 
						pPreFrame->gifFrame.imageLPos+pPreFrame->gifFrame.imageWidth,pPreFrame->gifFrame.imageTPos+pPreFrame->gifFrame.imageHeight);

					// dispoalMethod��ʾ�����굱ǰ֡�󣬻�����һ֡ͼƬǰ�Ĵ���ʽ
					// http://giflib.sourceforge.net/whatsinagif/animation_and_transparency.html
					switch (pPreFrame->gifFrame.ctrlExt.disposalMethod)
					{
					case DM_UNDEFINED:
						break;
					case DM_NONE:
						break;
					case DM_BACKGROUND:
						m_pMemCanvas->ClearRect(rcPreFrame,PBGRA(0,0,0,0));// ���frame��������
						break;
					case DM_PREVIOUS:
						// �ָ�����֡
						m_pMemCanvas->BitBlt(m_pPreviousCanvas, m_rcGif.left, m_rcGif.top, m_rcGif);
						break;
					default:
						break;
					}
				}
				
				m_pMemCanvas->DrawBitamp(pFrame->pBitmap,rcSor,rcFrame);

				switch(pFrame->gifFrame.ctrlExt.disposalMethod)
				{
				case DM_UNDEFINED:
				case DM_NONE:
					// ���ݸ�֡
					m_pPreviousCanvas->BitBlt(m_pMemCanvas, m_rcGif.left, m_rcGif.top, m_rcGif);
					break;
				case DM_BACKGROUND:
					// ����һ֡����֮ǰ��������DMGIF_NOREADYʱ����Ƴ��м����֡�������˸
					break;
				case DM_PREVIOUS:
					// ����һ֡����֮ǰ��������DMGIF_NOREADYʱ����Ƴ��м����֡�������˸
					break;
				default:
					break; 
				}

				m_dwPreFrameTime = GetTickCount();// ������ʱ��
				m_ulCurFrame++;					  // �������ü���
			}
			pCanvas->AlphaBlend(m_pMemCanvas,m_rcGif, rcClient);
			if (bClip)
			{
				pCanvas->PopClip();
			}
		} while (false);
	}


	void DUIGif::OnShowWindow(BOOL bShow, UINT nStatus)
	{
		__super::OnShowWindow(bShow, nStatus);
		if (!bShow)
		{
			Pause();
		}
		else
		{
			Restart();
		}
	}

	void DUIGif::OnDestroy()
	{
		GetContainer()->OnUnregisterTimeline(this);
		__super::OnDestroy();
	}

	DMCode DUIGif::OnTimeline()
	{
		do 
		{
			if (!DM_IsVisible(true))
			{
				break;
			}
			int iState = ReadyCurFrame(m_ulCurFrame);
			if (DMGIF_READY == iState)
			{
				DM_Invalidate();
			}
		} while (false);
		return DM_ECODE_OK;
	}

	bool  DUIGif::IsReady()
	{
		bool bRet = false;
		do 
		{
			if (0 == m_ulTotalLoopCount)
			{
				break;
			}
			if (m_ulFrameCount<2)		// ����2֡
			{
				break;
			}
			if (m_pMemCanvas.isNull())	// gif�������,����֡���������ʼ��
			{
				break;
			}
			if (m_pPreviousCanvas.isNull())
			{
				break;
			}
			bRet = true;
		} while (false);
		return bRet;
	}

	bool  DUIGif::Reset()
	{
		bool bRet = false;
		do 
		{
			if (!IsReady())
			{
				break;
			}
			m_ulCurFrame	     = 0;
			m_ulCurLoop          = 0;
			m_dwPreFrameTime     = 0;       // ʱ��ˢ��ʱ��ʼ��
			m_pMemCanvas->ClearRect(m_rcGif,0);
			m_pPreviousCanvas->ClearRect(m_rcGif, 0);
			m_bPause             = false;

			bRet = true;
		} while (false);
		return bRet;
	}

	int DUIGif::ReadyCurFrame(UINT ulFrame)
	{
		DMGifState iState = DMGIF_NOREADY;
		do 
		{
			if (!IsReady())
			{
				break;
			}

			//1. �Ƿ���ͣ
			if (m_bPause)
			{
				iState = DMGIF_PAUSE;
				break;
			}

			//1. ����ѭ��
			if (m_ulCurFrame>=m_ulFrameCount)
			{
				m_ulCurFrame = 0; // ѭ��һ��
				if (INFINITE!=m_ulTotalLoopCount)
				{
					m_ulCurLoop++;
				}
			}

			//2. ѭ�������ѵ�����ͣ
			if (INFINITE!=m_ulTotalLoopCount&&m_ulCurLoop>=m_ulTotalLoopCount)
			{
				iState = DMGIF_LOOPEND;
				break;
			}

			PDMAnimateFrame &pFrameObj = m_DMArray[m_ulCurFrame];
			if (0 == pFrameObj->gifFrame.ctrlExt.delayTime)
			{
				pFrameObj->gifFrame.ctrlExt.delayTime = 10;// Ĭ��0.1s��
			}

			//3. ʱ��δ��
			if (GetTickCount()-m_dwPreFrameTime<(DWORD)m_DMArray[m_ulCurFrame]->gifFrame.ctrlExt.delayTime*10)
			{
				iState = DMGIF_NODELAY;
				break;
			}

			iState = DMGIF_READY;
		} while (false);
		return iState;
	}

	DMCode DUIGif::OnAttrGif(LPCWSTR lpszValue, bool bLoadXml)
	{
		DMCode iErr = DM_ECODE_FAIL;
		do 
		{	
			CStringW  strValue = lpszValue;
			if (PathFileExistsW(strValue))// ����һ���ļ�����·��
			{
				iErr = LoadFromFile(strValue);
				break;
			}

			CStringW strType;
			CStringW strResName;
			CStringWList strList;
			int nCount = (int)SplitStringT(strValue,L':',strList);
			if (1== nCount)// ������GIF:IDR_GIF
			{
				strType    = L"GIF";
				strResName = strList[0];
			}
			else if(2 == nCount)
			{
				strType    = strList[0];
				strResName = strList[1];
			}
			else
			{
				CStringW strInfo;
				strInfo.Format(L"gifskin����%s���ô���",lpszValue);
				DMASSERT_EXPR(0,L"gifskin���ô���!");
				break;
			}
			DMSmartPtrT<IDMRes> pRes;
			g_pDMApp->GetDefRegObj((void**)&pRes, DMREG_Res);
			if (!pRes)
			{
				break;
			}
			ULONG ulSize = 0;
			pRes->GetItemSize(strType,strResName,ulSize);
			if (0>=ulSize)
			{
				break;
			}
			DMBufT<byte>pBuf;pBuf.Allocate(ulSize);
			if (!DMSUCCEEDED(pRes->GetItemBuf(strType,strResName, pBuf, ulSize)))
			{
				break;
			}
			iErr = LoadFromMemory(pBuf,ulSize); 
		} while (false);
		if (DMSUCCEEDED(iErr))
		{
			Start(); // ����
		}
		return iErr;
	}

	void DUIGif::PreArrayObjRemove(const PDMAnimateFrame &obj)
	{
		delete obj;
	}
}//namespace DM