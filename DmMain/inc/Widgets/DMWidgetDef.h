//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMWidgetDef.h 
// File Des: ���ÿؼ��ļ򵥶���
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-2-9	1.0			
//--------------------------------------------------------
#pragma once

namespace DM
{
// ----------------------------------------------------
// ���ô��ڶ���
#define      DUINAME_Static     L"Static"                       // DUI Static
#define      DUINAME_Group      L"Group"                        // DUI Group
#define      DUINAME_CheckBox   L"CheckBox"                     // DUI CheckBox
#define      DUINAME_Link       L"Link"                         // DUI Link
#define      DUINAME_ComboxBox  L"Combobox"                     // DUI Combobox
#define      DUINAME_Button     L"Button"                       // DUI Button
#define      DUINAME_HotKey     L"HotKey"                       // DUI HotKey
#define      DUINAME_IPEdit	    L"IPEdit"						// DUI IPEdit
#define      DUINAME_IPAddress  L"IPAddress"                    // DUI IPAddress
#define      DUINAME_RadioButton L"RadioButton"					// DUI RadioButton
#define      DUINAME_SliderCtrl L"SliderCtrl"					// DUI SliderCtrl
#define      DUINAME_ProcessCtrl L"ProcessCtrl"					// DUI ProcessCtrl
#define      DUINAME_TabCtrl    L"TabCtrl"                      // DUI TabCtrl
#define      DUINAME_TabPage    L"TabPage"                      // DUI TabPage
#define      DUINAME_TabAnimate L"TabAnimate"                   // DUI TabAnimate
#define      DUINAME_ActiveX    L"ActiveX"                      // DUI ActiveX
#define      DUINAME_Flash      L"Flash"                        // DUI Flash
#define      DUINAME_IE         L"IE"                           // DUI IE
#define      DUINAME_ScrollBar  L"ScrollBar"                    // DUI ScrollBar
#define      DUINAME_Panel	    L"Panel"                        // DUI Panel
#define      DUINAME_ScrollView	L"ScrollView"                   // DUI ScrollView
#define      DUINAME_RichEdit	L"RichEdit"                     // DUI RichEdit
#define      DUINAME_Edit	    L"Edit"                         // DUI Edit
#define      DUINAME_ListCtrl	L"ListCtrl"                     // DUI ListCtrl
#define      DUINAME_ListBox	L"ListBox"                      // DUI ListBox
#define      DUINAME_ListBoxEx	L"ListBoxEx"                    // DUI ListBoxEx
#define      DUINAME_TreeCtrl	L"TreeCtrl"                     // DUI TreeCtrl
#define      DUINAME_TreeCtrlEx	L"TreeCtrlEx"                   // DUI TreeCtrlEx
#define      DUINAME_HeaderCtrl	L"HeaderCtrl"                   // DUI HeaderCtrl
#define      DUINAME_ListCtrlEx	L"ListCtrlEx"                   // DUI ListCtrlEx
#define      DUINAME_Gif     	L"Gif"                          // DUI Gif
#define      DUINAME_ScrollBase L"ScrollBase"                   // DUI ScrollBase
#define      DUINAME_MonthCalCtrl L"MonthCalCtrl"				// DUI MonthCalCtrl
#define      DUINAME_DateTimeCtrl L"DUIDateTimeCtrl"		    // DUI DateTimeCtrl

// ----------------------------------------------------
// scroll
// ״̬:������ͣ������������á���Active
#define    DMSBST_NORMAL                             0							///< ����״̬
#define    DMSBST_HOVER                              1							///< hover״̬
#define    DMSBST_PUSHDOWN                           2							///< ����״̬
#define    DMSBST_DISABLE                            3							///< ����״̬
#define    DMSBST_NOACTIVE							 4							///< �Ǽ���״̬

// ��������ʾ״̬
#define	   DMSB_NULL								 0
#define	   DMSB_HORZ								 1
#define	   DMSB_VERT								 2
#define	   DMSB_BOTH								(DMSB_HORZ|DMSB_VERT)

struct SBSTATEINFO
{
	SBSTATEINFO()
	{
		sbCode = -1;
		nState = 0;
		bVert  = false;
	}
	SBSTATEINFO(LONG obj)
	{
		memcpy(this,&obj,4);
	}
	bool operator !=(const SBSTATEINFO &obj)
	{
		return memcmp(this,&obj,sizeof(SBSTATEINFO))!=0;
	}
	LONG sbCode:16;
	LONG nState:8;
	bool bVert :8;
};

// �ؼ�:�ϼ�ͷ���¼�ͷ����ֱ����������ֱ���ۡ����ͷ���Ҽ�ͷ��ˮƽ��������ˮƽ���ۡ�С�߽�
#define    SB_CORNOR								10
#define    MAKESBSTATE(sbCode,nState,bVert)         MAKELONG((sbCode),MAKEWORD((nState),(bVert)))
#define	   TIMER_SBWAIT								1         // �������������Ķ�ʱ��
#define    TIMER_SBGO								2         // ���������Ķ�ʱ��
}// namespace DM