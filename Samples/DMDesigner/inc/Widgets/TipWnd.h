// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	TipWnd.h
// File mark:   
// File summary:ר���������tips��ʾ
// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2016-8-3
// ----------------------------------------------------------------
#pragma once

class AttrTipWnd : public DMHWnd
{					
public:
	bool InitAttr(DMXmlInitAttrPtr ptr);
};

class AddTipWnd : public DMHWnd
{
public:
	bool InitAdd(CStringW strInfo);
};