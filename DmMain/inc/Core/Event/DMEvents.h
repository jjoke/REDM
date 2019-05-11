//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMEvents.h 
// File Des: �¼�ϵͳ����copy��CEGUI
// File Summary:
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-2-3	1.0			
//--------------------------------------------------------
#pragma once

namespace DM
{
	class DUIWindow;
	/// <summary>
	///		�¼�����,������ע������¼������ȴ���һ������̳�������������һ���µ��¼�ID
	/// </summary>
	class DM_EXPORT DMEventArgs
	{
	public:
		DMEventArgs(DUIWindow *pSender);
		virtual ~DMEventArgs();
		virtual bool IsValid();								  // �ж��Ƿ�Ϸ����ɷ���ȥ
		virtual UINT GetEventID() = 0;
		virtual LPCSTR GetEventName(){return NULL;};

	public:
		int								     m_iHandleCount;  ///< ���¼�������ʱ��m_iHandleCount����
		int									 m_IdFrom;        ///< �¼�������ID
		LPCWSTR								 m_szNameFrom;    ///< �¼�������name
		DUIWindow*							 m_pSender;       ///< �����¼���ԭʼ���ڶ���
	};

	/// <summary>
	///		�¼�ID
	/// </summary>
	enum DMEVT_ID
	{
		DMEVT_CMD			   = 10000,	
		DMEVT_HOVERCMD,
		DMEVT_LEAVECMD,
		DMEVT_SIZECHANGED,
		DMEVT_CHECKCHANGING,
		DMEVT_CHECKCHANGED,
		DMEVT_RBUTTONMENU,

		DMEVT_TAB_SELCHANGING  = 11000,			
		DMEVT_TAB_SELCHANGED,
		
		DMEVT_TAB_3DVIEW       = 12000,

		DMEVT_SCROLLBAR        = 13000,

		DMEVT_RENOTIFY         = 14000,
		DMEVT_REWANTRETURN,

		DMEVT_SETFOCUS         = 15000,
		DMEVT_KILLFOCUS,

		DMEVT_LB_SELCHANGING   = 16000,
		DMEVT_LB_SELCHANGED,
		DMEVT_LB_GETDISPINFO,

		DMEVT_OFPANEL          = 17000,
		DMEVT_OFPANELCLICK     = 17001,
		DMEVT_OFPANELRCLICK    = 17002,

		DMEVT_CB_SELCHANGE     = 18000,

		DMEVT_TC_SELCHANGING   = 19000,
		DMEVT_TC_SELCHANGED,
		DMEVT_TC_CHECKSTATE,
		DMEVT_TC_EXPAND,
		DMEVT_TC_DBCLICK,

		DMEVT_HEADER_CLICK	   = 20000,
		DMEVT_HEADER_ITEMCHANGING,
		DMEVT_HEADER_ITEMCHANGED,
		DMEVT_HEADER_ITEMSWAP,
		
		DMEVT_LC_GETDISPINFO   = 21000,
		DMEVT_LC_SELCHANGING,
		DMEVT_LC_SELCHANGED,
		DMEVT_LC_ITEMDELETED,

		DMEVT_SD_POSCHANG      = 22000,
		DMEVT_SD_POSCHANGED,

		DMEVT_SC_ONSCROLL      = 22100,

		DMEVT_CL_SETDATE       = 22150,
		DMEVT_CL_CLICKDATECHANGED,


		// Ԥ��1000�ռ��script�����¼�
		DMEVT_SCRIPT_START     = 23000,
		DMEVT_SCRIPT_END       = 24000,

		DMEVT_END				= 10000000,
	};

	/// <summary>
	///		ͨ���¼�
	/// </summary>
	class DM_EXPORT DMEventCmdArgs:public DMEventArgs
	{
	public:
		DMEventCmdArgs(DUIWindow *pWnd):DMEventArgs(pWnd){}
		enum{EventID = DMEVT_CMD};
		UINT GetEventID(){return EventID;};
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_CMD);}
	};

	/// <summary>
	///		ͨ�����ͣ���¼�
	/// </summary>
	class DM_EXPORT DMEventHoverCmdArgs:public DMEventArgs
	{
	public:
		DMEventHoverCmdArgs(DUIWindow *pWnd):DMEventArgs(pWnd){}
		enum{EventID = DMEVT_HOVERCMD};
		UINT GetEventID(){return EventID;};
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_HOVERCMD);}
	};

	/// <summary>
	///		ͨ������뿪�¼�
	/// </summary>
	class DM_EXPORT DMEventLeaveCmdArgs:public DMEventArgs
	{
	public:
		DMEventLeaveCmdArgs(DUIWindow *pWnd):DMEventArgs(pWnd){}
		enum{EventID = DMEVT_LEAVECMD};
		UINT GetEventID(){return EventID;};
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_LEAVECMD);}
	};


	/// <summary>
	///		ͨ�ò��������Ϣ
	/// </summary>
	class DM_EXPORT DMEventSizeChangedCmdArgs:public DMEventArgs
	{
	public:
		DMEventSizeChangedCmdArgs(DUIWindow *pWnd):DMEventArgs(pWnd){}
		enum{EventID = DMEVT_SIZECHANGED};
		UINT GetEventID(){return EventID;};
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_SIZECHANGED);}
	};

	/// <summary>
	///		ͨ��Check�ı���Ϣ
	/// </summary>
	class DM_EXPORT DMEventCheckChangingCmdArgs:public DMEventArgs
	{
	public:
		DMEventCheckChangingCmdArgs(DUIWindow *pWnd):DMEventArgs(pWnd),m_bChecking(false),m_bCancel(false){}
		enum{EventID = DMEVT_CHECKCHANGING};
		UINT GetEventID(){return EventID;};
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_CHECKCHANGING);}
		bool                m_bChecking;        ///< ��uncheck��Ϊcheck����ֵΪ�棬����Ϊ��
		bool				m_bCancel;			///< �Ƿ�ȡ����ǰ����
	};

	class DM_EXPORT DMEventCheckChangedCmdArgs:public DMEventArgs
	{
	public:
		DMEventCheckChangedCmdArgs(DUIWindow *pWnd):DMEventArgs(pWnd){}
		enum{EventID = DMEVT_CHECKCHANGED};
		UINT GetEventID(){return EventID;};
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_CHECKCHANGED);}
	};

	/// <summary>
	///		ͨ���Ҽ��˵���Ϣ
	/// </summary>
	class DM_EXPORT DMEventRButtonMenuCmdArgs:public DMEventArgs
	{
	public:
		DMEventRButtonMenuCmdArgs(DUIWindow *pWnd):DMEventArgs(pWnd){m_pt.x=m_pt.y=0;}
		enum{EventID = DMEVT_RBUTTONMENU};
		UINT GetEventID(){return EventID;};
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_RBUTTONMENU);}
		POINT				m_pt;
	};

	/// <summary>
	///		Tabҳ�л����¼�
	/// </summary>
	class DM_EXPORT DMEventTabSelChangingArgs:public DMEventArgs
	{
	public:
		DMEventTabSelChangingArgs(DUIWindow *pWnd):DMEventArgs(pWnd),m_bCancel(false){}
		enum{EventID=DMEVT_TAB_SELCHANGING};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_TAB_SELCHANGING);}
		UINT				m_uOldSel;			///<��ǰѡ��ҳ
		UINT				m_uNewSel;			///<��ǰѡ��ҳ
		bool				m_bCancel;          ///<�Ƿ�ȡ����ǰ�л�ҳ�Ĳ���
	};

	/// <summary>
	///		Tabҳ�л����¼�
	/// </summary>
	class DM_EXPORT DMEventTabSelChangedArgs:public DMEventArgs
	{
	public:
		DMEventTabSelChangedArgs(DUIWindow *pWnd):DMEventArgs(pWnd){}
		enum{EventID=DMEVT_TAB_SELCHANGED};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_TAB_SELCHANGED);}
		UINT				m_uOldSel;			///<��ǰѡ��ҳ
		UINT				m_uNewSel;			///<��ǰѡ��ҳ
	};

	/// <summary>
	///		3Dת���¼�
	/// </summary>
	class DM_EXPORT DMEvent3dViewArgs:public DMEventArgs
	{
	public:
		DMEvent3dViewArgs(DUIWindow *pWnd,bool bTurn2Front):DMEventArgs(pWnd),m_bTurn2Front(bTurn2Front){}
		enum{EventID=DMEVT_TAB_3DVIEW};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_TAB_3DVIEW);}
		bool				m_bTurn2Front;     
	};

	/// <summary>
	///		�������¼�
	/// </summary>
	class DM_EXPORT DMEventScrollArgs:public DMEventArgs
	{
	public:
		DMEventScrollArgs(DUIWindow *pWnd):DMEventArgs(pWnd){}
		enum{EventID=DMEVT_SCROLLBAR};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_SCROLLBAR);}
		UINT				 m_uSbCode;		  ///<��ǰ������λ��
		int					 m_nPos;		  ///<������pos
		bool				 m_bVert;         ///<ˮƽ����ֱ������
	};


	/// <summary>
	///		RichEdit�¼�
	/// </summary>
	class DM_EXPORT DMEventRENotifyArgs:public DMEventArgs
	{
	public:
		DMEventRENotifyArgs(DUIWindow *pWnd):DMEventArgs(pWnd){}
		enum{EventID=DMEVT_RENOTIFY};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_RENOTIFY);}
		DWORD				 m_iNotify;
		LPVOID				 m_pv;
		HRESULT              m_hr;
	};

	/// <summary>
	///		RichEdit�¼�,��������wantReturn״̬ʱ������Ϊ����ʱ��������Ϣ�����������ҳ��ʾ�ؼ�
	/// </summary>
	class DM_EXPORT DMEventREWantReturnArgs:public DMEventArgs
	{
	public:
		DMEventREWantReturnArgs(DUIWindow *pWnd):DMEventArgs(pWnd){}
		enum{EventID=DMEVT_REWANTRETURN};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_REWANTRETURN);}
	};

	/// <summary>
	///		���ý����¼�
	/// </summary>
	class DM_EXPORT DMEventSetFocusArgs : public DMEventArgs
	{
	public:
		DMEventSetFocusArgs(DUIWindow *pWnd):DMEventArgs(pWnd){}
		enum{EventID=DMEVT_SETFOCUS};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_SETFOCUS);}
	};

	/// <summary>
	///		ʧȥ�����¼�
	/// </summary>
	class DM_EXPORT DMEventKillFocusArgs : public DMEventArgs
	{
	public:
		DMEventKillFocusArgs(DUIWindow *pWnd):DMEventArgs(pWnd){}
		enum{EventID=DMEVT_KILLFOCUS};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_KILLFOCUS);}
	};

	/// <summary>
	///		LISTBOX�¼�
	/// </summary>
	class DM_EXPORT DMEventLBGetDispInfoArgs : public DMEventArgs
	{
	public:
		DMEventLBGetDispInfoArgs(DUIWindow *pWnd):DMEventArgs(pWnd){}
		enum{EventID=DMEVT_LB_GETDISPINFO};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_LB_GETDISPINFO);}
		int						m_iItem;
		DUIWindow*				m_pItem;
		bool					m_bSel;
		bool					m_bHover;
	};

	/// <summary>
	///		LISTBOXѡ�����¼�
	/// </summary>
	class DM_EXPORT DMEventLBSelChangingArgs : public DMEventArgs
	{
	public:
		DMEventLBSelChangingArgs(DUIWindow *pWnd):DMEventArgs(pWnd),m_bCancel(false){}
		enum{EventID=DMEVT_LB_SELCHANGING};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_LB_SELCHANGING);}
		int						m_nNewSel;           ///<��ǰѡ����
		int						m_nOldSel;			 ///<��ǰѡ����
		bool					m_bCancel;			  ///<�Ƿ�ȡ��ѡ����
	};

	/// <summary>
	///		LISTBOXѡ����¼�
	/// </summary>
	class DM_EXPORT DMEventLBSelChangedArgs : public DMEventArgs
	{
	public:
		DMEventLBSelChangedArgs(DUIWindow *pWnd):DMEventArgs(pWnd),m_nNewSel(-1),m_nOldSel(-1){}
		enum{EventID=DMEVT_LB_SELCHANGED};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_LB_SELCHANGED);}
		int						 m_nNewSel;
		int						 m_nOldSel;
	};

	/// <summary>
	///		PANELѡ����¼�
	/// </summary>
	class DM_EXPORT DMEventOfPanelArgs : public DMEventArgs
	{
	public:
		DMEventOfPanelArgs(DUIWindow* pPanel, DMEventArgs *pOrgEvt)
			:DMEventArgs(pPanel),m_pPanel(pPanel),m_pOrgEvt(pOrgEvt){}
		enum{EventID=DMEVT_OFPANEL};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_OFPANEL);}

		PVOID					m_pPanel; // ������ת����DUIItemPanel
		DMEventArgs*			m_pOrgEvt;
	};

	/// <summary>
	///		PANEL������¼�
	/// </summary>
	class DM_EXPORT DMEventOfPanelClickArgs : public DMEventArgs
	{
	public:
		DMEventOfPanelClickArgs(DUIWindow* pPanel)
			:DMEventArgs(pPanel),m_pPanel(pPanel){}
		enum{EventID=DMEVT_OFPANELCLICK};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_OFPANELCLICK);}
		PVOID					m_pPanel; // ������ת����DUIItemPanel
	};

	/// <summary>
	///		PANEL���һ��¼�
	/// </summary>
	class DM_EXPORT DMEventOfPanelRClickArgs : public DMEventArgs
	{
	public:
		DMEventOfPanelRClickArgs(DUIWindow* pPanel)
			:DMEventArgs(pPanel),m_pPanel(pPanel){}
		enum{EventID=DMEVT_OFPANELRCLICK};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_OFPANELRCLICK);}

		PVOID					m_pPanel; // ������ת����DUIItemPanel
	};

	/// <summary>
	///		COMBOX�¼�
	/// </summary>
	class DM_EXPORT DMEventCBSelChangeArgs : public DMEventArgs
	{
	public:
		DMEventCBSelChangeArgs(DUIWindow *pWnd,int nCurSel):DMEventArgs(pWnd),m_nCurSel(nCurSel){}
		enum{EventID=DMEVT_CB_SELCHANGE};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_CB_SELCHANGE);}
		int						m_nCurSel;
	};

	/// <summary>
	///		TREECTRLѡ�����¼�
	/// </summary>
	class DM_EXPORT DMEventTCSelChangingArgs : public DMEventArgs
	{
	public:
		DMEventTCSelChangingArgs(DUIWindow *pWnd):DMEventArgs(pWnd),m_bCancel(FALSE){}
		enum{EventID=DMEVT_TC_SELCHANGING};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_TC_SELCHANGING);}
		HDMTREEITEM				m_hOldSel;
		HDMTREEITEM				m_hNewSel;
		BOOL					m_bCancel;
	};

	/// <summary>
	///		TREECTRLѡ����¼�
	/// </summary>
	class DM_EXPORT DMEventTCSelChangedArgs : public DMEventArgs
	{
	public:
		DMEventTCSelChangedArgs(DUIWindow *pWnd):DMEventArgs(pWnd){}
		enum{EventID=DMEVT_TC_SELCHANGED};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_TC_SELCHANGED);}
		HDMTREEITEM				m_hOldSel;
		HDMTREEITEM				m_hNewSel;
	};

	/// <summary>
	///		TREECTRL Check�¼�
	/// </summary>
	class DM_EXPORT DMEventTCCheckStateArgs : public DMEventArgs
	{
	public:
		DMEventTCCheckStateArgs(DUIWindow *pWnd):DMEventArgs(pWnd){}
		enum{EventID=DMEVT_TC_CHECKSTATE};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_TC_CHECKSTATE);}
		HDMTREEITEM				 m_hItem;
		UINT					 m_uCheckState;
	};

	/// <summary>
	///		TREECTRL չ���¼�
	/// </summary>
	class DM_EXPORT DMEventTCExpandArgs : public DMEventArgs
	{
	public:
		DMEventTCExpandArgs(DUIWindow *pWnd):DMEventArgs(pWnd){}
		enum{EventID=DMEVT_TC_EXPAND};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_TC_EXPAND);}
		HDMTREEITEM				 m_hItem;
		BOOL					 m_bCollapsed;
	};

	class DM_EXPORT DMEventTCDbClickArgs : public DMEventArgs
	{
	public:
		DMEventTCDbClickArgs(DUIWindow *pWnd):DMEventArgs(pWnd){}
		enum{EventID=DMEVT_TC_DBCLICK};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_TC_DBCLICK);}
		HDMTREEITEM				 m_hItem;  //˫��ѡ�еĽڵ�
	};

	/// <summary>
	///		�б�ͷ �¼�
	/// </summary>
	class DM_EXPORT DMEventHeaderClickArgs : public DMEventArgs
	{
	public:
		DMEventHeaderClickArgs(DUIWindow *pWnd):DMEventArgs(pWnd){}
		enum{EventID=DMEVT_HEADER_CLICK};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_HEADER_CLICK);}
		int						 m_iItem;
	};

	/// <summary>
	///		�б�ͷ�л����¼�
	/// </summary>
	class DM_EXPORT DMEventHeaderItemChangingArgs : public DMEventArgs
	{
	public:
		DMEventHeaderItemChangingArgs(DUIWindow *pWnd):DMEventArgs(pWnd),m_bCancel(FALSE){}
		enum{EventID=DMEVT_HEADER_ITEMCHANGING};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_HEADER_ITEMCHANGING);}
		int						m_iItem;
		int						m_nWidth;	//�ⲿ�������µĿ��
		BOOL                    m_bCancel;  //��ȡ������
	};

	/// <summary>
	///		�б�ͷ�л����¼�
	/// </summary>
	class DM_EXPORT DMEventHeaderItemChangedArgs : public DMEventArgs
	{
	public:
		DMEventHeaderItemChangedArgs(DUIWindow *pWnd):DMEventArgs(pWnd){}
		enum{EventID=DMEVT_HEADER_ITEMCHANGED};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_HEADER_ITEMCHANGED);}
		int						m_iItem;
		int						m_nWidth;
	};

	/// <summary>
	///		�б�ͷ�϶��¼�
	/// </summary>
	class DM_EXPORT DMEventHeaderItemSwapArgs : public DMEventArgs
	{
	public:
		DMEventHeaderItemSwapArgs(DUIWindow *pWnd):DMEventArgs(pWnd){}
		enum{EventID=DMEVT_HEADER_ITEMSWAP};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_HEADER_ITEMSWAP);}
		int					   m_iOldIndex;
		int					   m_iNewIndex;
	};

	/// <summary>
	///		LISTCTRL�¼�
	/// </summary>
	class DM_EXPORT DMEventLCGetDispInfoArgs : public DMEventArgs
	{
	public:
		DMEventLCGetDispInfoArgs(DUIWindow *pWnd):DMEventArgs(pWnd){}
		enum{EventID=DMEVT_LC_GETDISPINFO};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_LC_GETDISPINFO);}
		int						m_iItem;
		DUIWindow*				m_pItem;
		bool					m_bSel;
		bool					m_bHover;
	};

	/// <summary>
	///		LISTCTRL�ı����¼�
	/// </summary>
	class DM_EXPORT DMEventLCSelChangingArgs : public DMEventArgs
	{
	public:
		DMEventLCSelChangingArgs(DUIWindow *pWnd):DMEventArgs(pWnd),m_bCancel(false){}
		enum{EventID=DMEVT_LC_SELCHANGING};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_LC_SELCHANGING);}
		int						m_nNewSel;
		int						m_nOldSel;
		bool					m_bCancel;
	};

	/// <summary>
	///		LISTCTRL�ı���¼�
	/// </summary>
	class DM_EXPORT DMEventLCSelChangedArgs : public DMEventArgs
	{
	public:
		DMEventLCSelChangedArgs(DUIWindow *pWnd):DMEventArgs(pWnd){}
		enum{EventID=DMEVT_LC_SELCHANGED};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_LC_SELCHANGED);}
		int						m_nNewSel;
		int						m_nOldSel;
	};

	/// <summary>
	///		LISTCTRLɾ���¼�
	/// </summary>
	class DM_EXPORT DMEventLCItemDeletedArgs : public DMEventArgs
	{
	public:
		DMEventLCItemDeletedArgs(DUIWindow *pWnd) :DMEventArgs(pWnd){}
		enum{EventID=DMEVT_LC_ITEMDELETED};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_LC_ITEMDELETED);}
		int						m_nItem;
		DWORD					m_dwData;
	};

	/// <summary>
	///		Slider Pos�ı��¼�
	/// </summary>
	class DM_EXPORT DMEventSDChangingArgs : public DMEventArgs
	{
	public:
		DMEventSDChangingArgs(DUIWindow *pWnd) :DMEventArgs(pWnd),m_bCacel(false){}
		enum{EventID=DMEVT_SD_POSCHANG};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_SD_POSCHANG);}
		int                     m_nOldPos;
		int                     m_nNewPos;
		bool                    m_bCacel;
	};

	/// <summary>
	///		Slider Pos�ı���¼�
	/// </summary>
	class DM_EXPORT DMEventSDChangedArgs : public DMEventArgs
	{
	public:
		DMEventSDChangedArgs(DUIWindow *pWnd) :DMEventArgs(pWnd){}
		enum{EventID=DMEVT_SD_POSCHANGED};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_SD_POSCHANGED);}
		int                     m_nOldPos;
		int                     m_nNewPos;
	};

	/// <summary>
	///		�����¼�
	/// </summary>
	class DM_EXPORT DMEventOnScrollArgs : public DMEventArgs
	{
	public:
		DMEventOnScrollArgs(DUIWindow *pWnd) :DMEventArgs(pWnd),m_iSbCode(-1),m_iPos(0),m_bVert(true){}
		enum{EventID=DMEVT_SC_ONSCROLL};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_SC_ONSCROLL);}
		int						m_iSbCode;
		int                     m_iPos;
		bool                    m_bVert;

	};

	/// <summary>
	///		���� ��������ʱ����
	/// </summary>
	class DM_EXPORT DMEventCalenderSetDateArgs : public DMEventArgs
	{
	public:
		DMEventCalenderSetDateArgs(DUIWindow *pWnd) :DMEventArgs(pWnd),m_iYear(-1),m_iMonth(-1),m_iDay(-1){}
		enum{EventID=DMEVT_CL_SETDATE};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_CL_SETDATE);}
		int					   m_iYear;			
		int                    m_iMonth;
		int                    m_iDay;
	};

	/// <summary>
	///		���� CELL������ı�󴥷�
	/// </summary>
	class DM_EXPORT DMEventCalenderClickDateChangedArgs : public DMEventArgs
	{// ����¾����һ����,˵��������˻�ɫ��cell���Զ�ִ������ת
	public:
		DMEventCalenderClickDateChangedArgs(DUIWindow *pWnd) :DMEventArgs(pWnd),m_iOldYear(-1),m_iOldMonth(-1),m_iOldDay(-1),m_iNewYear(-1),m_iNewMonth(-1),m_iNewDay(-1){}
		enum{EventID=DMEVT_CL_CLICKDATECHANGED};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_CL_CLICKDATECHANGED);}
		int					   m_iOldYear;			
		int                    m_iOldMonth;
		int                    m_iOldDay;
		int					   m_iNewYear;			
		int                    m_iNewMonth;
		int                    m_iNewDay;
	};

	/// <summary>
	///		�ű��¼�
	/// </summary>
	class DM_EXPORT DMEventScriptStartArgs : public DMEventArgs
	{
	public:
		DMEventScriptStartArgs(DUIWindow *pWnd) :DMEventArgs(pWnd){}
		enum{EventID=DMEVT_SCRIPT_START};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_SCRIPT_START);}
	};

	class DM_EXPORT DMEventScriptEndArgs : public DMEventArgs
	{
	public:
		DMEventScriptEndArgs(DUIWindow *pWnd) :DMEventArgs(pWnd){}
		enum{EventID=DMEVT_SCRIPT_END};
		virtual UINT GetEventID(){return EventID;}
		LPCSTR GetEventName(){return EVEIDNAME(DMEVT_SCRIPT_END);}
	};

}//namespace DM