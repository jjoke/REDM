
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMDef.h 
// File Des: �����궨��
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-7	1.0			
//-------------------------------------------------------
#pragma once
#include "DMWidgetDef.h"

namespace DM
{

typedef int											  DMCode;					///< �������ʶ
typedef unsigned long                                 DUIWND,*DUIWNDPtr;        ///< ģ����ƴ��ھ����Ҳ������Ϊģ���Ӵ��ڵ�Ψһ��ʶ                 
typedef ULONG_PTR									  HDMTREEITEM;				///< ���οؼ��Ķ���    

// ----------------------------------------------------
// �������
#define DMIN
#define DMOUT
#define DMINOUT

#ifdef _WIN64
#define GWL_WNDPROC    GWLP_WNDPROC
#endif//_WIN64

// ----------------------------------------------------
// ����
#define DMADDEVENT(EventId)                          m_EventMgr;//.AddEvent(EventId);///< Ĭ�ϲ���Ҫ��ǰ����                                    

// ----------------------------------------------------
// ��������λ
#define DMASSERT									  assert
#define DMASSERT_EXPR(expr, msg)                      _ASSERT_EXPR(expr, msg)   ///;LOG_ERR(msg)
#define DM_INVALID_VALUE                              ((LONG_PTR)-1)			///< ͨ�õķǷ�����

// ----------------------------------------------------
// HSLA�仯
enum{DM_H=0,DM_S,DM_L,DM_A};

// ----------------------------------------------------
// ���غ��߼���λת����
#define DMHIMETRIC_PER_INCH							 2540
#define DMMAP_LOGHIM_TO_PIX(x,ppli)					 MulDiv((ppli), (x), DMHIMETRIC_PER_INCH)
#define DMMAP_PIX_TO_LOGHIM(x,ppli)					 MulDiv(DMHIMETRIC_PER_INCH, (x), (ppli))

// ----------------------------------------------------
// SPY������λ
#define WM_DMSPY                                      WM_USER+1314              ///< spy++��Ϣ

#define	EVEIDNAME(x)								  #x

static LPCWSTR MSGSTR(UINT uMsg)												///< ��ӡMSG
{// ��OXC014����ΪIDLEʱ��Ϣ�����ã�LOG_USER("[msg]:%s\n",MSGSTR(uMsg));
#define MSGDEF(x) if(uMsg==x) return L#x
	MSGDEF(WM_SETCURSOR);
	MSGDEF(WM_NCHITTEST);
	MSGDEF(WM_NCPAINT);
	MSGDEF(WM_PAINT);
	MSGDEF(WM_ERASEBKGND);
	MSGDEF(WM_NCMOUSEMOVE);  
	MSGDEF(WM_MOUSEMOVE);
	MSGDEF(WM_MOUSELEAVE);
	MSGDEF(WM_MOUSEHOVER);   
	MSGDEF(WM_NOTIFY);
	MSGDEF(WM_COMMAND);
	MSGDEF(WM_MEASUREITEM);
	MSGDEF(WM_DRAWITEM);   
	MSGDEF(WM_LBUTTONDOWN);
	MSGDEF(WM_LBUTTONUP);
	MSGDEF(WM_LBUTTONDBLCLK);
	MSGDEF(WM_RBUTTONDOWN);
	MSGDEF(WM_RBUTTONUP);
	MSGDEF(WM_RBUTTONDBLCLK);
	MSGDEF(WM_SETFOCUS);
	MSGDEF(WM_KILLFOCUS);  
	MSGDEF(WM_MOVE);
	MSGDEF(WM_SIZE);
	MSGDEF(WM_INITDIALOG);
	MSGDEF(WM_SIZING);
	MSGDEF(WM_MOVING);
	MSGDEF(WM_GETMINMAXINFO);
	MSGDEF(WM_CAPTURECHANGED);
	MSGDEF(WM_WINDOWPOSCHANGED);
	MSGDEF(WM_WINDOWPOSCHANGING);   
	MSGDEF(WM_NCCALCSIZE);
	MSGDEF(WM_NCCREATE);
	MSGDEF(WM_NCDESTROY);
	MSGDEF(WM_TIMER);
	MSGDEF(WM_KEYDOWN);
	MSGDEF(WM_KEYUP);
	MSGDEF(WM_CHAR);
	MSGDEF(WM_SYSKEYDOWN);
	MSGDEF(WM_SYSKEYUP);
	MSGDEF(WM_SYSCOMMAND);
	MSGDEF(WM_SYSCHAR);
	MSGDEF(WM_VSCROLL);
	MSGDEF(WM_HSCROLL);
	MSGDEF(WM_CHAR);
	MSGDEF(WM_SHOWWINDOW);
	MSGDEF(WM_PARENTNOTIFY);
	MSGDEF(WM_CREATE);
	MSGDEF(WM_NCACTIVATE);
	MSGDEF(WM_ACTIVATE);
	MSGDEF(WM_ACTIVATEAPP);   
	MSGDEF(WM_CLOSE);
	MSGDEF(WM_DESTROY);
	MSGDEF(WM_GETICON);   
	MSGDEF(WM_GETTEXT);
	MSGDEF(WM_GETTEXTLENGTH); 
	MSGDEF(WM_IME_SETCONTEXT);
	MSGDEF(WM_STYLECHANGING);
	MSGDEF(WM_STYLECHANGED);
	MSGDEF(WM_SETTEXT);
	MSGDEF(WM_IME_NOTIFY);
	MSGDEF(WM_IME_CONTROL);
	MSGDEF(WM_IME_COMPOSITIONFULL);
	MSGDEF(WM_IME_SELECT);
	MSGDEF(WM_IME_CHAR);
	MSGDEF(WM_NCLBUTTONDOWN);
	MSGDEF(WM_ENTERSIZEMOVE);
	MSGDEF(WM_EXITSIZEMOVE);
	MSGDEF(WM_ENTERMENULOOP);
	MSGDEF(WM_INITMENU);
	MSGDEF(WM_INITMENUPOPUP);
	MSGDEF(WM_MENUSELECT);
	MSGDEF(WM_MENUCHAR);
	MSGDEF(WM_ENTERIDLE);
	MSGDEF(WM_MENURBUTTONUP);
	MSGDEF(WM_MENUDRAG);
	MSGDEF(WM_MENUGETOBJECT);
	MSGDEF(WM_UNINITMENUPOPUP);
	MSGDEF(WM_MENUCOMMAND);
	MSGDEF(WM_EXITMENULOOP);
	MSGDEF(WM_DROPFILES);

	static wchar_t szMsg[10];
	::swprintf_s(szMsg, 10, L"0x%04X", uMsg);
	return szMsg;
}

// ----------------------------------------------------
// �ര��
#define DM_DEF_CLASS_NAME							 L"DMClass"					///< Ĭ������
#define DM_DEF_SHADOWCLASS_NAME						 L"DMShadowClass"		    ///< Ĭ����Ӱ����
#define DM_DEF_WINDOW_NAME							 L"DMWindow"                ///< Ĭ�ϴ�����
//#define DM_DEF_STYLE                                 WS_POPUP|WS_CLIPCHILDREN|WS_TABSTOP
#define DM_DEF_STYLE                                 WS_POPUP|WS_CLIPCHILDREN|WS_TABSTOP|WS_MINIMIZEBOX

enum
{
	NOMAL_PAINT = 0,       ///< ��ͨ�������
	DUMMY_PAINT = 1,       ///< �ɰ洦�����
};

enum DMOLEDCFLAGS
{	
	DMOLEDC_NODRAW		= 0x1,		///< ��ȡ������ת������
	DMOLEDC_PAINTBKGND	= 0x2,		///< ץ�����������ɳ�ʼ�Ļ�����ת������
	DMOLEDC_OFFSCREEN	= 0x4       ///< ץ�����������ɳ�ʼ�Ļ�����ת������
};

// ----------------------------------------------------
// �ַ���
#ifndef	   countof
#define    countof(x)								(sizeof(x) / sizeof((x)[0]))
#endif

#ifndef    IsValidString
#define    IsValidString(x)							((x) && (x)[0])
#endif

#ifndef    SAFE_STR
#define    SAFE_STR(a)								 IsValidString(a) ? a :L""
#endif

#ifndef    __STR2WSTR
#define	   __STR2WSTR(str)						     L##str
#endif

#define	   ID2NAME(x)								 L#x
#define    DMABS(x)                                 ((x)>=0?(x):-(x))
#define	   DMMAX(a,b)								(((a) > (b)) ? (a) : (b))
#define    DMMIN(a,b)							    (((a) < (b)) ? (a) : (b))

// ----------------------------------------------------
// ����Delegate,��δʹ��,���ܲ���OK
#define    DMDLBIND(_xxx_,_bbb_)					if(!_xxx_){_xxx_ = _bbb_;}	///< ��ֹ�����������

// ----------------------------------------------------
//  XML�ڵ��
#define    RES_GLOBAL                               L"global"                   ///< ȫ��
#define	   RES_LAYOUT								L"layout"					///< ����
#define    RES_THEMES								L"themes"					///< ������б�

#define	   MAINWND_NODE								L"dm"                       ///< ÿ�������ڵ���ʼSection��
#define    DUIROOT_NODE								L"root"                     ///< ���������
#define    SUB_NODE								    L"sub"                      ///< ֧��sub���

// ----------------------------------------------------
// DUIWindow��Ϣ����
#ifndef  WM_NCMOUSEFIRST
#define  WM_NCMOUSEFIRST WM_NCMOUSEMOVE
#define  WM_NCMOUSELAST  WM_NCMBUTTONDBLCLK
#endif

// ȫ�ֶ�ʱ��,���������า��!!
#define  TIMER_NEXTFRAME							2

// ----------------------------------------------------
// �����಻��Ҫ�ĸ��ƹ��캯�������Ʋ������Լ���ʽ�Ĺ��캯��,����Chrome��src\base\basictypes.h
#define DM_DISALLOW_COPY(TypeName)					TypeName(const TypeName&)
#define DM_DISALLOW_ASSIGN(TypeName)				void operator=(const TypeName&)
#define DM_DISALLOW_COPY_AND_ASSIGN(TypeName)       TypeName(const TypeName&); void operator=(const TypeName&)
#define DM_DISALLOW_EVIL_CONSTRUCTORS(TypeName)     DM_DISALLOW_COPY_AND_ASSIGN(TypeName)  
#define DM_DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName) TypeName(); DM_DISALLOW_COPY_AND_ASSIGN(TypeName)


// ----------------------------------------------------
// LOG
#ifdef   DMLOG_ON
#define  LOG_TRACE(fmt, ...)						 //DMLogDispatch::LogW(DMLOG_TRACE,__FUNCTIONW__,__FILEW__, __LINE__,__STR2WSTR(fmt),__VA_ARGS__)
#define  LOG_DEBUG(fmt, ...)						 //DMLogDispatch::LogW(DMLOG_DEBUG,__FUNCTIONW__,__FILEW__, __LINE__,__STR2WSTR(fmt),__VA_ARGS__)
#define  LOG_INFO(fmt, ...)							 //DMLogDispatch::LogW(DMLOG_INFO,__FUNCTIONW__,__FILEW__, __LINE__,__STR2WSTR(fmt),__VA_ARGS__)
#define  LOG_WARN(fmt, ...)							 //DMLogDispatch::LogW(DMLOG_WARN,__FUNCTIONW__,__FILEW__, __LINE__,__STR2WSTR(fmt),__VA_ARGS__)
#define  LOG_ERR(fmt, ...)							 DMLogDispatch::LogW(DMLOG_ERR,__FUNCTIONW__,__FILEW__, __LINE__,__STR2WSTR(fmt),__VA_ARGS__)
#define  LOG_FATAL(fmt, ...)						 DMLogDispatch::LogW(DMLOG_FATAL,__FUNCTIONW__,__FILEW__, __LINE__,__STR2WSTR(fmt),__VA_ARGS__)
#else
#define  LOG_TRACE(fmt, ...)
#define  LOG_DEBUG(fmt, ...)
#define  LOG_INFO(fmt, ...)
#define  LOG_WARN(fmt, ...)
#define  LOG_ERR(fmt, ...)
#define  LOG_FATAL(fmt, ...)
#endif//DMLOG_ON
// LOG_USER������VS�����¶�λ����ʹ�ã�ʹ����������!!
#define  LOG_USER(fmt, ...)							 DMLogDispatch::LogW(DMLOG_INFO,__FUNCTIONW__,__FILEW__, __LINE__,__STR2WSTR(fmt),__VA_ARGS__)

// ----------------------------------------------------
// ����ɾ���궨��
#define DM_DELETE_ARRAY(_xxx_) \
{\
	if (_xxx_) \
{ \
	delete [] _xxx_; \
	_xxx_ = NULL; \
}\
}

#define DM_DELETE(_xxx_) \
{\
	if (_xxx_) \
{ \
	delete _xxx_; \
	_xxx_ = NULL; \
}\
}

#define DM_CLOSEHANDLE(_xxx_) \
{\
	if (_xxx_) \
{ \
	CloseHandle(_xxx_); \
	_xxx_ = NULL; \
}\
}

#define DM_DELETE_OBJECT(_xxx_) \
{\
	if (_xxx_) \
{ \
	::DeleteObject(_xxx_) ; \
	_xxx_ = NULL; \
}\
}

}//namespace DM


