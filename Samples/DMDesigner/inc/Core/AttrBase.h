// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	AttrBase.h
// File mark:   
// File summary:���ڼ�¼ObjXml��صĹ�������
// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2016-8-10
// ----------------------------------------------------------------
#pragma once

class ObjTree;
class ObjXml;
class AttrBase
{
public:
	AttrBase();
	~AttrBase();
	DMCode OnObjTreeChanged(DMEventArgs* pEvt);
	DMCode OnLockChanged(DMEventArgs* pEvt);
	virtual DMCode UpdataInfo(HDMTREEITEM hSel,HDMTREEITEM hOldSel) = 0;
	virtual DMCode UpdateLock(HDMTREEITEM hItem);

public:
	ObjTree*											m_pObjTree;
	ObjXml*												m_pObjXml;
	HDMTREEITEM											m_hObjSel;	
	bool												m_bMuted;		///< �Ƿ������Ϣ

	// lock���
	DUIWindow*										    m_pPanel;       ///< ��Ҫ�����������

	// ģ��DMCWnd
	BOOL												m_bMsgHandled;
};