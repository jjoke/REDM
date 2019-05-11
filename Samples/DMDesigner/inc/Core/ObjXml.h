//----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	ObjXml.h
// File mark:   
// File summary:���������ͼ
// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2016-7-8
// ----------------------------------------------------------------
#pragma once

class ObjTreeData;
class ObjXml : public ProjXml,public DMMapT<HDMTREEITEM,ObjTreeDataPtr>
{
public:
	ObjXml();
	~ObjXml();

public:
	DMCode InitObjTree();							
	DMCode ReleaseObjTree();
	DMCode ShowPreview();
	DMCode PopObjTreeMenu(HDMTREEITEM hSel);
	DMCode HandleObjTreeMenu(int nID);

	// ����
	DMCode OnObjTreeChanged(DMEventArgs* pEvt);
	DMCode InitObjTreeNode(DMXmlNode& TreeNode,bool IsDMXml = false);
	DMCode BindObjTreeData(DocDataPtr pDoc,DUIRoot* pEditor,DUIWindowPtr pDUI, DMXmlNode& Node, HDMTREEITEM hTreeItem,bool bPanel = false);
	HDMTREEITEM InsertObjTreeItem(DMXmlNode& TreeNode,CStringW strText,HDMTREEITEM hParent =DMTVI_ROOT);
	HDMTREEITEM FindStyle(CStringW strStyle);// ע��,�����ҵ���HDMTREEITEMΪProjTree�е���
protected:
	// Menu���ʼ��
	DMCode InitCopyObjMenu(DMXmlNode& XmlNode);
	DMCode InitCustomObjMenu(DMXmlNode& XmlNode);
	
	// Menu�¼�����
	DMCode ObjMenu_OpenDir();
	DMCode ObjMenu_Paste();
	DMCode ObjMenu_Copy();
	DMCode ObjMenu_LockAllChild(bool bLock);
	DMCode ObjMenu_Del();

public:
	DMCode InitObjRootTree();
	DMCode InitObjChildTree(HDMTREEITEM hRootItem);
	DMCode EnumChildTreeItem(DUIRoot*pMainWnd, DUIWindow* pWnd, HDMTREEITEM hTreeItem,bool bPanel = false);
	DMCode EnumPanelTreeItem(DUIRoot*pMainWnd, DUIWindow* pWnd, HDMTREEITEM hTreeItem);
	DMCode RemoveObjTreeItemMap(HDMTREEITEM hTreeItem);///< �Ƴ�hTreeItem�����Ӧ�����ӽڵ��map

private:
	HDMTREEITEM _FindStyle(HDMTREEITEM hStylePoolParent,CStringW strName,CStringW strKey);
	virtual void PreMapKeyRemove(const ObjTreeDataPtr &obj);

public:
	DUIObjEditor*										m_pObjEditor;
	bool												m_bInitObjTree;
	DMSmartPtrT<PreHWnd>								m_pPreWnd;				///<  Ԥ������

	// ���οؼ�
	ObjTree*										    m_pObjTree;
	HDMTREEITEM											m_hObjSel;	

	// �Ҳ�����
	RightXml*                                           m_pRighXml;

	// Add����
	AddXml*                                             m_pAddXml;

	// ֧�����
	DUICheckBox*                                        m_pbPanelCheck;
};
