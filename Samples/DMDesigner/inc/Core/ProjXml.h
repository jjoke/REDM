// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	ProjXml.h
// File mark:   
// File summary:��������ͼ
// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2016-7-8
// ----------------------------------------------------------------
#pragma once

class ProjXml:public DMArrayT<DocDataPtr>,public DMMapT<HDMTREEITEM,DMXmlNodePtr>
{
public:
	ProjXml();
	virtual~ProjXml();

public:
	DMCode ParseRes(CStringW strResDir);
	bool   IsNeedSave();
	DMCode SaveRes(bool bCheck = true);
	DMCode InitProjTree();							
	DMCode ReleaseProjTree();
	DMCode PopProjTreeMenu(HDMTREEITEM hSel);
	DMCode HandleProjTreeMenu(int nID);

	// ����
	DMCode InitSubXmlList();
	DMCode SetDocUnSave(CStringW strPath);
	DMCode SetDocUnSave(DMXmlNodePtr pNode);
	DMCode InitProjTreeNode(DMXmlNode& TreeNode,bool IsData = false);
	DMCode BindProjTreeData(DMXmlNode& DataNode,HDMTREEITEM hTreeItem);
	HDMTREEITEM InsertProjTreeItem(DMXmlNode& TreeNode,CStringW strText,HDMTREEITEM hParent =DMTVI_ROOT);
	DocDataPtr FindDocData(CStringW strPath);
	DocDataPtr FindDocData(DMXmlNodePtr pNode);
	CStringW GetProjTreeItemText(HDMTREEITEM hSel);
	

protected:
	// Menu���ʼ��
	DMCode InitCustomProjMenu(DMXmlNode& XmlNode);
	DMCode InitSkinPoolsProjMenu(DMXmlNode& XmlNode);
	DMCode InitStylePoolsProjMenu(DMXmlNode& XmlNode);
	DMCode InitSkinProjMenu(DMXmlNode& XmlNode);
	DMCode InitStyleProjMenu(DMXmlNode& XmlNode);
	DMCode InitImgTypeMenu(DMXmlNode& XmlNode);
	DMCode InitThemeMenu(DMXmlNode& XmlNode);
	DMCode InitImgMenu(DMXmlNode& XmlNode);
	DMCode InitLayoutMenu(DMXmlNode& XmlNode);

	// Menu�¼�����
	DMCode ProjMenu_OpenDir();
	DMCode ProjMenu_Scan();
	DMCode ProjMenu_AddSkinPool();
	DMCode ProjMenu_DelSkinPool();
	DMCode ProjMenu_EditSkinPool();
	DMCode ProjMenu_AddStylePool();
	DMCode ProjMenu_DelStylePool();
	DMCode ProjMenu_EditStylePool();
	DMCode ProjMenu_AddSkin();
	DMCode ProjMenu_DelSkin();
	DMCode ProjMenu_EditSkin();
	DMCode ProjMenu_AddStyle();
	DMCode ProjMenu_DelStyle();
	DMCode ProjMenu_EditStyle();
	DMCode ProjMenu_AddImgType();
	DMCode ProjMenu_DelImgType();
	 DMCode ProjMenu_EditImgType();
	DMCode ProjMenu_AddTheme();
	DMCode ProjMenu_DelTheme();
	DMCode ProjMenu_EditTheme();
	DMCode ProjMenu_SetDefTheme();
	DMCode ProjMenu_AddImg();
	DMCode ProjMenu_DelImg();
	DMCode ProjMenu_EditImg();
	DMCode ProjMenu_AddLayout();
	DMCode ProjMenu_DelLayout();
	DMCode ProjMenu_EditLayout();

private:
	virtual void PreArrayObjRemove(const DocDataPtr &obj);
	virtual void PreMapKeyRemove(const DMXmlNodePtr &obj);
	virtual bool EqualArrayObj(const DocDataPtr &objsrc, const DocDataPtr &objdest);

public:
	DMSmartPtrT<ResFolder>								m_pRes;				///< ��Դ��,Ԥ�������ɴ���Դ���ṩ��Դ
	CStringW											m_strResDir;		///< ��Դ��·��,����"\"
	CStringW											m_strGlobalName;	///< ȫ����Դ������

	// ���οؼ�
	ProjTree*											m_pProjTree;	
	HDMTREEITEM                                         m_hProjLayouts;		///< ��ʽ-Ƥ��-�����ļ������
	HDMTREEITEM                                         m_hProjThemes;		///< ������б�����
	HDMTREEITEM                                         m_hProjLayoutFiles; ///< �����ļ��б�����
	HDMTREEITEM                                         m_hProjGlobal;      ///< Global���ڵĽ��
	HDMTREEITEM                                         m_hProjGlobalStyleSkins;
	HDMTREEITEM                                         m_hProjPrivStyleSkins;
	HDMTREEITEM                                         m_hProjGlobalStyles;///< ȫ����ʽ�б�
	HDMTREEITEM                                         m_hProjGlobalSkins; ///< ȫ��Ƥ���б�

	HDMTREEITEM											m_hProjSel;			
	HDMTREEITEM                                         m_hProjDefTheme;

	bool                                                m_bSubInit;			///< sub���Ƿ��ѳ�ʼ�����
	
};