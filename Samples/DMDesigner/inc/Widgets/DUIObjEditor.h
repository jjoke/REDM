//----------------------------------------------------------------
// Copyright (c)     
// All rights reserved.  
//          
// File name:	DUIObjEditor.h 
// File mark:   
// File summary:������ͼ�༭������
// Author:		guoyouhuang
// Edition:     1.0 
// Create date: 2016-8-6
// ----------------------------------------------------------------
#pragma once
#include "DUIRoot.h" 

class ObjXml;
class DUIObjEditor : public DUIScrollBase
{
	DMDECLARE_CLASS_NAME(DUIObjEditor, L"dsobjeditor",DMREG_Window)
public:
	DUIObjEditor();

public:
	DMCode InitObjEditor();
	DMCode UnInitObjEditor();
	DMCode SetDesignMode(DesignMode ds_mode);

	DUIRoot* InitDesignChild(HDMTREEITEM hRootTree);			///< ��ʼ��Design�Ӵ���
	DUIRoot* GetShowDesignChild();
	DMCode ShowDesignChild(DUIRoot* pShow);
	DMCode RemoveAllDesignChild();

	// ���ƹ�����Χ
	void UpdateScrollRangeSize();												
	void OnRangeCurPosChanged(CPoint ptOld,CPoint ptNew);		
	
	DMCode DV_GetChildMeasureLayout(LPRECT lpRect);	
	DMCode OnDesignModeChanged(DMEventArgs* pEvt);
	DMCode OnCheckChanging(DMEventArgs* pEvt);
	DMCode OnCheckChanged(DMEventArgs* pEvt);

	// ���Ƹ�frame
	DMCode HoverInSelOrAddMode(DUIWindow* pDUIHover);
	DMCode SelFrameInAllMode();
	DMCode DragFrameInSelMode();

public:
	DUIRoot*											m_pShow;
	DUIStatic*											m_pHoverlFrame;					///< ��SelectMode��AddModeʱ��ѡͣ��DUI
	DUIStatic*                                          m_pSelFrame;                    ///< ������ģʽ�¿�ѡ ѡ�е����οؼ� ��Ӧ��DUI
	DUIDragFrame*                                       m_pDragFrame;                   ///< ��SelectMode�¿�ѡ ѡ�е����οؼ�  ��Ӧ��DUI

	//
	ObjXml*												m_pObjXml;
	DUITabCtrl*											m_pTools;
	DUICheckBox*									    m_pCheckBtn;					///< m_pChcekBtn��m_pTools������ƣ�ֻ����AddMode�²���ѡ��m_pChcekBtn
	DesignMode											m_DesignMod;
	CRect												m_rcMeasure;
	bool                                                m_bInit;
};