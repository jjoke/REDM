// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	Data.h
// File mark:   
// File summary:�����ݶ���
// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2016-7-8
// ----------------------------------------------------------------
#pragma once
/// <summary>
///		ÿ��XML Docά��һ���ṹ��
/// </summary>
class DocData;
typedef DocData* DocDataPtr;
class DocData : public DMArrayT<DocDataPtr>///< ����XML�ҵ���sub��,������dm xml
{
public:
	DocData();
	DocData(CStringW strXmlPath);
	~DocData();
	bool IsValid() const;

public:
	DMXmlDocument*                        m_pXmlDoc;			///< �����XML DOC
	CStringW                              m_strXmlPath;			///< ����XML���ڵ�Doc��ȫ·��
	DMXmlNode                             m_XmlRoot;			///< �����
	bool                                  m_bChange;			///< �Ƿ񱻸ı�(���ı����ܱ�����)
};

/// <summary>
///		objtreeÿһ��󶨵�����
/// </summary>
 enum {DMVISIBLE_NULL,DMVISIBLE_HIDE,DMVISIBLE_SHOW};
 class ObjTreeData
 {
 public:
	 ObjTreeData(DocDataPtr pDoc,DUIRoot* pRootWnd,DUIWindowPtr pDUI,DMXmlNode& Node,bool bPanel=false);
	 ~ObjTreeData();
	 void SetData(DocDataPtr pDoc,DUIRoot* pRootWnd,DUIWindowPtr pDUI,DMXmlNode& Node,bool bPanel=false);
	 bool IsValid() const;

 public:
	 DocDataPtr                           m_pDoc;				///< ����XML
	 DUIRoot*							  m_pRootWnd;			///< �������ڱ༭������
	 DUIWindowPtr                         m_pDUIWnd;			///< �������ڴ���
	 DMXmlNodePtr						  m_pXmlNode;			///< ����XML���
	 int                                  m_iOrgVisible;        ///< ������eye�ر�ʱ��¼ԭʼ��visible״̬    
	 bool                                 m_bPanel;				///< �Ƿ�ΪPanelItem;
 };
 typedef ObjTreeData* ObjTreeDataPtr;