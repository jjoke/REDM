// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	XmlEditor.h
// File mark:   
// File summary:��ʾ���༭XML
// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2017-5-5
// ----------------------------------------------------------------
#pragma once

/// <summary>
///		subclass Scintilla wnd
/// </summary>
class XmlEditor : public DMHWnd
{
	DECLARE_MESSAGE_MAP()	
public:
	XmlEditor();

public:// ��Ϣ����
	void Destroy();
	LRESULT OnImeChar(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT DefWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);


public:// ����ӿ�
	HWND Create(HWND hWndParent);

public:// http://www.naughter.com/scintilla.html,��װScintilla�ĵ���
	void InitXml();
	LRESULT Call(UINT message,WPARAM wParam=0,LPARAM lParam=0,bool bDirect=true);
	LRESULT AddText(int iLen, LPCSTR lpszText, bool bDirect = true);									///< ��posλ�ú������ı�
	LRESULT Cancel(bool bDirect = true);
	LRESULT ClearAll(bool bDirect = true);																///< ��������ı�
	LRESULT EmptyUndoBuffer(bool bDirect = true);
	LRESULT GotoPos(int iPos, bool bDirect = true);														///< ��ת��ָ��pos
	int GetCurrentPos(bool bDirect = true);																///< ��õ�ǰ���ڵ�pos(0��ʼ)
	int GetCurLine(int iLen, LPCSTR lpszText, bool bDirect = true);
	LRESULT SetUndoCollection(bool bCollectUndo, bool bDirect = true);
	LRESULT SetSavePoint(bool bDirect = true);
	bool GetReadOnly(bool bDirect = true);																///< �Ƿ�ΪReadOnly״̬
	LRESULT SetReadOnly(bool bReadOnly, bool bDirect = true);											///< ReadOnly״̬ʱ�����۵�������ʾ��꣬�����ܱ༭

public:
	LRESULT				m_DirectFunction;
	LRESULT				m_DirectPointer;
};


/// <summary>
///		DUI��RealWnd�ӿ�
/// </summary>
class DUIRealXml : public IDUIRealWnd, public AttrBase
{
	DMDECLARE_CLASS_NAME(DUIWindow,L"xmleditor",DMREG_Window);
public:
	DUIRealXml();

public:
	HWND OnCreateRealWnd(LPCWSTR atom,HWND hWndParent);
	DMCode OnDestoryRealWnd();
	DMCode OnShowRealWnd(BOOL bShow, UINT nStatus){return DM_ECODE_NOTIMPL;};
	DMCode OnMoveRealWnd(LPRECT lpRect);
	DMCode OnIsPopupWnd(){return DM_ECODE_FAIL;}

public:
	DMCode UpdataInfo(HDMTREEITEM hSel,HDMTREEITEM hOldSel);
	DMCode UpdateLock(HDMTREEITEM hItem);
	DMCode OnUpdateXml(DMEventArgs* pEvt);			
	
public:
	DMSmartPtrT<XmlEditor>         m_pXmlEditor;   
	HWND                           m_hParent;
};
