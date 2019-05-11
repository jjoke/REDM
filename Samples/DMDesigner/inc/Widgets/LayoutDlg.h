// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	LayoutDlg.h
// File mark:   
// File summary:�½���༭layout
// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2016-8-5
// ----------------------------------------------------------------
#pragma once

class LayoutDlg : public DMHDialog
{
public:
	LayoutDlg(bool bEditMode = false);
	DECLARE_MESSAGE_MAP()
	DECLARE_EVENT_MAP()

	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
	void OnSize(UINT nType, CSize size);
	void OnDropFiles(HDROP hDropInfo);

	DMCode OnEditChange(DMEventArgs *pEvt);
	DMCode OnOpenDir(); 

	DMCode UpdateXml();

	static int CALLBACK  BrowseCallbackProc(HWND hwnd,UINT uMsg,LPARAM lParam,LPARAM lpData);
protected:
	DMCode OnOK();

private:  
	bool							m_bEditMode;
	DUIStatic*                      m_pTitle;
	DUIStatic*                      m_pLayoutPath;

	DUIEdit*                        m_pLayoutName;
	DUIEdit*                        m_pLayoutDir;
	DUIEdit*                        m_pLayoutFileName;
	DUIEdit*                        m_pLayoutFileAfx;

	DUIRichEdit*                    m_pXml;

	// xml
	DMXmlDocument                   m_LayoutDoc;
	DMXmlNode                       m_LayoutNode;

	CStringW                        m_strDir;    ///< Layout���ڵ�·����"e:\\layout"
	static  LayoutDlg*              ms_pthis; 	
};