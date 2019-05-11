#pragma once
#include "3d/3dTransform.h"
#include "DMAnimateWndBase.h"

namespace DM
{
#define  TIMER_3D      1
	struct PARAM3DOFF{int  x;int y; int   z;int  f;};///3Dÿ��ƫ����
	class DM3DAnimate:public IDMAnimate,public DMAnimateWndBase
	{
		DMDECLARE_CLASS_NAME(DM3DAnimate,L"DM3DAnimate",DMREG_Animate);
	public:
		DM3DAnimate();

	public:
		DMCode AnimateInit(IDMAnimateOwner*pOwner,IDMCanvas* pStartCanvas,IDMCanvas* pEndCanvas,WPARAM wp, LPARAM lp);// wp����3dÿ��ƫ��,lp������ת����������Ҳ�����Զ�
		DMCode AnimateBegin(WPARAM wp, LPARAM lp);		/// wp��λΪ�����ٶȣ���λΪ����ʱ���,lp��ÿ����ת��ʱ���
		DMCode AnitmateGet(WPARAM wp=0, LPARAM lp=0);  
		DMCode AnimateEnd(WPARAM wp, LPARAM lp);		/// wp��λΪ�����ٶȣ���λΪ����ʱ���

	public:
		virtual DMCode EndFadeFinish();

	public:
		void OnPaint(HDC hdc);
		void OnTimer(UINT_PTR idEvent);

	public:
		DECLARE_MESSAGE_MAP()										// ��MFC��Ϣӳ���

	public:
		IDMAnimateOwner*				    m_pOwner; 

		PARAM3DOFF                          m_3doffset;
		int                                 m_count;
		int                                 m_curFrame;
		IMAGE3D::PARAM3DTRANSFORM			m_3dparam;
		         
		DMSmartPtrT<IDMCanvas>              m_pStartCanvas;
		DMSmartPtrT<IDMCanvas>              m_pEndCanvas;
		DMSmartPtrT<IDMCanvas>              m_pTransCanvas;

		byte                                m_byAlpha;
	};
}//namespace DM
