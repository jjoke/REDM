// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	DUIDragFrame.h
// File mark:   
// File summary:ѡ��ʱ�϶����ı߿�
// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2016-8-10
// ----------------------------------------------------------------
#pragma once
#include "DMDelegate.h"// д����ô�ã��ܵ���һ�ΰɣ�

/// <summary>
///		����������
/// </summary>
enum DSDOT
{
	DSDOT_MOVE,
	DSDOT_LEFT,
	DSDOT_LEFTOP,
	DSDOT_TOP,
	DSDOT_RIGHTOP,
	DSDOT_RIGHT,
	DSDOT_RIGHTBTM,
	DSDOT_BTM,
	DSDOT_LEFTBTM,
	DSDOT_BOX,
};

class DragMeta;
typedef DMDelegate<void(DragMeta&, int)> DragMetaEventHandler;
class DragMeta
{
public:
	DragMeta(int idx=-1,HCURSOR hCursor = ::LoadCursor(NULL,IDC_ARROW));
	DMCode OnRender(IDMCanvas* pCanvas);
	DMCode SetCurSor();

public:
	int					 m_Index;			///< 0Ϊ��������dot�ľ����������ؼ�����,1Ϊ����dot��˳ʱ��8���㣬9Ϊ���Ͻǵ�movСͼ��,��ӦDSDOT
	CRect				 m_Rect;			///< �˵�ľ�������Ĭ��1-9�㶼�ڿؼ�����Χ����ռ�ÿؼ���
	HCURSOR				 m_hCursor;			///< ͣ���ڴ˾�����ʱ��ʾ������
	DMColor				 m_Clr;				///< ����������ʱ�����ɫ
	DMColor              m_GrayClr;			///< ����������ʱ�����ɫ
	bool				 m_bDragDot;		///< ����0�⣬���������϶���(true)
	bool				 m_bEnable;			///< �˵��Ƿ����
	DragMetaEventHandler m_DragMetaAction;

	DMSmartPtrT<IDMSkin>	m_pSkin;		///< ����movСͼ��
};

class ObjTreeData;
class RightXml;
class DUIDragFrame : public DUIWindow
{
	DMDECLARE_CLASS_NAME(DUIDragFrame,L"duidragframe",DMREG_Window);
public:
	DUIDragFrame();

	DMCode InitDragFrame(ObjTreeData* pData,CRect& rcLayout);
	static bool IsSupportPos(ObjTreeData* pData);

private:
	void LinkDragMetaEvent();
	void InitDragMeta(CRect Rect,bool bMain,bool bAllGray=false);
	DragMeta* HittestDragMeta(CPoint pt,bool bMain);

	void OnDragLeft(DragMeta& meta, int iAction);		 // �϶����
	void OnDragLeftTop(DragMeta& meta, int iAction);	 // �϶����Ͻ�
	void OnDragTop(DragMeta& meta, int iAction);		 // �϶��ϱ�
	void OnDragRightTop(DragMeta& meta, int iAction);	 // �϶����Ͻ�
	void OnDragRight(DragMeta& meta, int iAction);		 // �϶��ұ�
	void OnDragRightBottom(DragMeta& meta, int iAction); // �϶����½�
	void OnDragBottom(DragMeta& meta, int iAction);		 // �϶��±�
	void OnDragLeftBottom(DragMeta& meta, int iAction);  // �϶����½�
	void OnDragBox(DragMeta& meta, int iAction);
	void OnDragMove(DragMeta& meta, int iAction);		 // �ƶ�

	CRect CalcDragFrameRect(CRect rcDrag);
	void InternalHandleDrag(CRect& rect, int* pHori, int* pVert);
	
public:
	void SetElementWidth(int wid);
	void SetElementHeight(int hei);
	bool SetElementRect(CRect rect);

public:
	DM_BEGIN_MSG_MAP()
		DM_MSG_WM_PAINT(DM_OnPaint)
		MSG_WM_LBUTTONDOWN(OnLButtonDown)
		MSG_WM_LBUTTONUP(OnLButtonUp)
		MSG_WM_RBUTTONDOWN(OnRButtonDown)
		MSG_WM_MOUSEMOVE(OnMouseMove)
	DM_END_MSG_MAP()
	void DM_OnPaint(IDMCanvas* pCanvas);
	void OnLButtonDown(UINT nFlags,CPoint pt);
	void OnLButtonUp(UINT nFlags,CPoint pt);
	void OnRButtonDown(UINT nFlags, CPoint pt);
	void OnMouseMove(UINT nFlags,CPoint pt);
	DUIWND HitTestPoint(CPoint pt,bool bFindNoMsg);///< ������Ϣ�ַ�

public:
	RightXml*                                m_pRightXml;		///< �ұ�����,���е����궼ͨ���ұ�����������
	DMSmartPtrT<Layout>						 m_pLayout;			///< ָ��Ҫ�༭��layout			
	DragMeta*								 m_pCurdragMeta;
	DragMeta								 m_dragMetas[10];
	int										 m_dragMetaCount;
	bool								     m_bMain;			///< ��Root��Ҳ��Ϊ���ϲ�
	bool                                     m_bDown;			///< ֻ���ڰ���ʱͣ����dot�ϻ�box�ϲ�����m_bDown
	
	CPoint									 m_StartDragPt;
	CPoint									 m_TrackDragPt;
	CRect									 m_StartDragRc;		///< ��ʼ�϶�ʱԪ�������С

	// ����
	ObjTreeData*							 m_pData;
};