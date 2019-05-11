// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	Events.h
// File mark:   
// File summary: �¼�ϵͳ����copy��CEGUI
// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2016-8-11
// ----------------------------------------------------------------
#pragma once

namespace DM
{
	/// <summary>
	///		�¼�ID
	/// </summary>
	enum EVT_ID
	{
		// DUIProp
		DMEVT_PROP_DELING = 24050,
		DMEVT_PROP_DEL,
		DMEVT_PROP_VALUECHANGED,

		// DUIRect
		DMEVT_DSRECT_CHANGED = 24100,

		// DUISize
		DMEVT_DSIZE_CHANGED  = 24200,

		// DUITreeEx
		DMEVT_DTREE_LOCKCHANGED = 24300,
		DMEVT_DTREE_EYECHANGED,

		// DUIRecentListBox
		DMEVT_DRLISTBOX_DBLCLICK = 24400,

		// XmlEditor
		DMEVT_XML_UPDATA = 24500,
	};

	/// <summary>
	///		DUIPropCtrlɾ�����¼�
	/// </summary>
	class IProp;
	class PropDelingArgs:public DMEventArgs
	{
	public:
		PropDelingArgs(DUIWindow *pWnd):DMEventArgs(pWnd),m_bCancel(false),m_pSel(NULL){}
		enum{EventID=DMEVT_PROP_DELING};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_PROP_DELING);}
		IProp*				m_pSel;				///<��ǰѡ����
		bool				m_bCancel;          ///<�Ƿ�ȡ����ǰ����
	};

	/// <summary>
	///		DUIPropCtrlɾ���¼�
	/// </summary>
	class PropDelArgs:public DMEventArgs
	{
	public:
		PropDelArgs(DUIWindow *pWnd):DMEventArgs(pWnd),m_pSel(NULL){}
		enum{EventID=DMEVT_PROP_DEL};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_PROP_DEL);}
		IProp*				m_pSel;				///<��ǰɾ��ѡ����
	};

	class PropValueChangedArgs:public DMEventArgs
	{
	public:
		PropValueChangedArgs(DUIWindow *pWnd):DMEventArgs(pWnd),m_pSel(NULL){}
		enum{EventID=DMEVT_PROP_VALUECHANGED};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_PROP_VALUECHANGED);}
		IProp*				m_pSel;				///<��ǰѡ����
		CStringW            m_strOldValue;
	};

	/// <summary>
	///		��ֵ�ı�ʱ,DUIRect���ʹ���Ϣ
	/// </summary>
	class DUIRectChangedArgs : public DMEventArgs
	{
	public:
		DUIRectChangedArgs(DUIWindow *pWnd) :DMEventArgs(pWnd){}
		enum{EventID=DMEVT_DSRECT_CHANGED};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_DSRECT_CHANGED);}
	};

	/// <summary>
	///		��ֵ�ı�ʱ,DUIList���ʹ���Ϣ
	/// </summary>
	class DUIListChangedArgs : public DMEventArgs
	{
	public:
		DUIListChangedArgs(DUIWindow *pWnd) :DMEventArgs(pWnd){}
		enum{EventID=DMEVT_DSIZE_CHANGED};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_DSIZE_CHANGED);}
	};

	/// <summary>
	///		��LOCK�ı��DUITreeEx���ʹ���Ϣ
	/// </summary>
	class DUITreeExLockChangedArgs :  public DMEventArgs
	{
	public:
		DUITreeExLockChangedArgs(DUIWindow *pWnd) :DMEventArgs(pWnd),m_hItem(NULL),m_iOldLockValue(0){}
		enum{EventID=DMEVT_DTREE_LOCKCHANGED};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_DTREE_LOCKCHANGED);}
		HDMTREEITEM                m_hItem; ///< �ı�lock����
		int                        m_iOldLockValue;
	};

	/// <summary>
	///		��EYE�ı��DUITreeEx���ʹ���Ϣ
	/// </summary>
	class DUITreeExEyeChangedArgs :  public DMEventArgs
	{
	public:
		DUITreeExEyeChangedArgs(DUIWindow *pWnd) :DMEventArgs(pWnd),m_hItem(NULL),m_iOldEyeValue(0){}
		enum{EventID=DMEVT_DTREE_EYECHANGED};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_DTREE_EYECHANGED);}
		HDMTREEITEM                m_hItem; ///< �ı�eye����
		int                        m_iOldEyeValue;
	};

	/// <summary>
	///		��˫��DUIRecentListBox����ʱ�����ʹ���Ϣ
	/// </summary>
	class DUIRecentListBoxDBLClickArgs :  public DMEventArgs
	{
	public:
		DUIRecentListBoxDBLClickArgs(DUIWindow *pWnd) :DMEventArgs(pWnd){}
		enum{EventID=DMEVT_DRLISTBOX_DBLCLICK};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_DRLISTBOX_DBLCLICK);}
		CStringW                  m_strDir;
	};

	/// <summary>
	///		Xml��Ҫ������ʾ
	/// </summary>
	class DUIXmlUpdateArgs : public DMEventArgs
	{
	public:
		DUIXmlUpdateArgs(DUIWindow *pWnd) :DMEventArgs(pWnd),m_UpdateType(XMLUPDATE_DELPROP){}
		enum{EventID=DMEVT_XML_UPDATA};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_XML_UPDATA);}
		enum{XMLUPDATE_DELPROP=0,XMLUPDATE_ADDPROP,XMLUPDATE_CHANGEPROP};
		int						 m_UpdateType;
	};
}//namespace DM