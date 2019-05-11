//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMSpyTool.h 
// File Des: Spy����ط�װ
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-2-2	1.0		
//-------------------------------------------------------
#pragma once

namespace DM
{
	enum DMSPYCMD
	{
		DMSPY_INIT = 1314,  													    ///< У���ʼ����Ϣ
		DMSPY_ROOT,																    ///< ͨ��hWndȡ����ʼDUI
		DMSPY_ENUM,		                                                            ///< ȡ�ô���	
		DMSPY_INFO,                                                                 ///< ȡ������
		DMSPY_POINT,                                                                ///< ͨ��ptȡ�ô���
	};

#define  DMSPY_NAME_LEN					260
#define  DMSPY_CLASSNAME_LEN            260
#define  DMSPY_XML_LEN                  10000
#define  DMSPY_ENUM_BEGIN               -1
#define  DMSPY_ENUM_END                 -2
#define  DMSPY_SHAREMEMORY             L"DMSPY_SHAREMEMORY" 
#define  DMSPY_SHAREMEMORYSIZE         L"DMSPY_SHAREMEMORYSIZE" 
	struct DMSpyInfo
	{
		bool               bVisible;
		DUIWND             hDUIWnd;
		int                iId;
		CRect              rcWindow;
		CRect              rcClient;
		wchar_t            szName[DMSPY_NAME_LEN];
		wchar_t			   szClassName[DMSPY_CLASSNAME_LEN];
		wchar_t            szXml[DMSPY_XML_LEN];
	};
	typedef struct stDMSpyEnum
	{
		DUIWND              hDUIWnd;
		DUIWND              hNextDUIWnd;
		int                 iCode;
		int                 iPanelIndex;// ��¼panel��ǰ��������1��ʼ,����panel,��Ϊ0��
		bool                bPanel;
		CPoint              pt;    // ʹ�����궨λ
		DMSpyInfo           info;

	}DMSpyEnum,*PDMSpyEnum;

	/// <summary>
	///		��װSpy�����
	/// </summary>
	class DM_EXPORT DMSpyTool
	{
	public:
		DMSpyTool();
		~DMSpyTool();
	public:
		LRESULT OnSpy(UINT uMsg, WPARAM wParam, LPARAM lParam);
		void EnumDUITree(LPCWSTR lpszPath);
		void EnumTreeItem(DUIWindow* pWnd,DMXmlNode XmlNode,int iLevel,bool bPanel); //iLevelָ��XmlNode����һ�㣬Ҳ��pWnd���ڵĲ�
		void EnumPanelTreeItem(DUIWindow* pWnd,DMXmlNode XmlNode,int iLevel);// ����pwnd����panel�У�XmlNodeΪpwnd���ڵ�Node,ÿ��ֻ��һ��
		void EnumInfo(DUIWindow*pWnd,PDMSpyEnum pSpyEnum);

	public:// �����ڴ������װ
		static bool CreateSharedMemory(UINT nSize);
		static bool GetShareMemorySize(UINT& nSize);
		static bool WriteShareMemory(void *pDate, UINT nSize);
		static bool ReadShareMemory(void *pDate, UINT nSize);
		static bool ReleaseSharedMemory();

	public:
		DUIWND                    m_hMainDUIWnd;  // ��ʼ��DUI����
		HWND                      m_hSpyWnd;
		PDMSpyEnum                m_pSpyEnum;
		DMXmlNode				  m_XmlBase;
		CMap<int,bool>			  m_PanelParseMap; // ����֤�㷨ʹ��
	};

}//namespace DM