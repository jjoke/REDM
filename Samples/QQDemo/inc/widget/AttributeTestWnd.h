//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: AttributeTestWnd.h 
// File Des:  ��ָ������SetAttribute��������ֵ
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-3-16	1.0		
//-------------------------------------------------------
#pragma once

class CWidgetWnd;
class CAttributeTestWnd:public DMHWnd
{
public:
	CAttributeTestWnd(CWidgetWnd* pWidgetWnd);
	~CAttributeTestWnd();

	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
	//---------------------------------------------------
	// Function Des: �¼��ַ�ϵ�к���
	// Input Parameter:
	// Output Parameter:
	// return:
	//---------------------------------------------------
	DMCode OnClose();
	DMCode OnSetAttribute();

protected:
	DECLARE_MESSAGE_MAP()// ��MFC��Ϣӳ���
	BEGIN_EVENT_MAPT(CAttributeTestWnd)
		EVENT_NAME_COMMAND(L"btn_attrtestclose",OnClose)
		EVENT_NAME_COMMAND(L"btn_testattr",OnSetAttribute)
	END_EVENT_MAP()

public:
	CWidgetWnd*							  m_pWidgetWnd;
	DUIEdit*                              m_pNameEdit;
	DUIEdit*                              m_pAttrNameEdit;
	DUIEdit*                              m_pAttrValueEdit;
	DUIButton*                            m_pBtn;
	DUIRichEdit*                          m_pInfoEdit;
};

