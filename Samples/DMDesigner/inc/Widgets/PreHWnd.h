// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	PreHWnd.h
// File mark:   
// File summary:���ڽ���DM Xml,�����ɶ�ӦԤ������
// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2016-8-8
// ----------------------------------------------------------------
#pragma once

class PreHWnd : public DMHWnd
{
public:
	DECLARE_MESSAGE_MAP()						

	HWND ObjCreateWindow(DMXmlDocument &XmlDoc);
	DMCode LoadDMData(DMXmlDocument &XmlDoc);	
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);		///< ����ECS��Ϣ��������
};