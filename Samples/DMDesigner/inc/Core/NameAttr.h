// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	NameAttr.h
// File mark:   
// File summary:Name������
// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2016-8-10
// ----------------------------------------------------------------
#pragma once

class NameAttr : public AttrBase
{
public:
	NameAttr();
	~NameAttr();
	DMCode UpdataInfo(HDMTREEITEM hSel,HDMTREEITEM hOldSel);
	DMCode OnEditChange(DMEventArgs *pEvt);

public:
	static DMCode s_DMHandleEvent(DM::DMEventArgs *pEvt);
	DECLARE_EVENT_MAP()

public:
	DUIEdit*											m_pNameEdit;
	DUIEdit*											m_pIdEdit;
	DUIStatic*											m_pClSta;

	// ����ת����Ϣ
	static NameAttr*                                    ms_pthis;
};