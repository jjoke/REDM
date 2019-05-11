#pragma once

namespace DM
{
#define TIMER_FADE                     1111
	class DMAnimateWndBase : public DMCWnd
	{
	public:
		DMAnimateWndBase();

	public:
		DMCode BeginFade(bool bEnd,int iSpeed,int iTimerDelta);
		virtual DMCode StartFadeFinish(){return DM_ECODE_NOTIMPL;};
		virtual DMCode EndFadeFinish(){return DM_ECODE_NOTIMPL;};
	public: 
		virtual DMCode Create(LPCRECT lpRect,DWORD dwStyle=WS_POPUP,DWORD dwExStyle=WS_EX_TRANSPARENT|WS_EX_TOOLWINDOW|WS_EX_TOPMOST); 

	public:
		void OnTimer(UINT_PTR idEvent);
	public:// ����
		BOOL DMANI_ClientToScreen(HWND hWnd,CRect &rc);
		BOOL UpdateLayerWnd(IDMCanvas*pCanvas,byte alpha,CPoint pt=CPoint(0,0));

	public:
		DECLARE_MESSAGE_MAP()										// ��MFC��Ϣӳ���

	public:

		// ���Ƶ��뵭��--------------------------------------------
		int                                 m_byFadeAlpha;				///< ���Խ���ʱ��alpha
		int                                 m_iFadeSpeed;				///< ���Խ������ٶ�
		bool                                m_bFadeEnd;					///< Ϊfalse��ʾ���ԣ�Ϊtrue��ʾ����
		bool                                m_bFadeing;					///< ���ڽ��Խ���������

	};
}//namespace DM