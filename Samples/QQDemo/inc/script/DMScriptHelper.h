// ----------------------------------------------------------------
// Copyright (c) tencent 
// All rights reserved.
// 
// File name:	DMScriptHelper.h
// File mark:   
// File summary:�������ش���ű�
 
// Author:		guoyouhuang
// Edition:     1.0
// Create date:  
// ----------------------------------------------------------------
#pragma  once
#include "DUICheckBox.h"

#define DMEVT_SCRIPT_TIMER     DMEVT_SCRIPT_START+1
class DMEventScriptTimerArgs : public DMEventArgs
{
public:
	DMEventScriptTimerArgs(DUIWindow *pWnd) :DMEventArgs(pWnd){}
	enum{EventID=DMEVT_SCRIPT_TIMER};
	virtual UINT GetEventID(){return EventID;}
	LPCSTR GetEventName(){return EVEIDNAME(DMEVT_SCRIPT_TIMER);}
};

class DMScriptHelper
{
public:
	DMScriptHelper();

	void InitScriptHelper(DMHWnd* pMainWnd);
	void RunScriptTimer();
	
	DMCode OnStrBtn(DMEventArgs* pEvent);
	DMCode OnFileBtn(DMEventArgs* pEvent);
	DMCode OnBufBtn(DMEventArgs* pEvent);
	DMCode OnStopBtn(DMEventArgs* pEvent);
	
private:
	void LogStart();
	void LogEnd();

public:
	DMSmartPtrT<IDMScript>          m_pScript;	///< ���Խű�
	DMHWnd*                         m_pMainWnd; ///< ָ��widgetwnd
	DUIRichEdit*                    m_pLogEdit; ///< ���к��lua�ձ�
	DUIRichEdit*                    m_pStrEdit; ///< Ҫ���е�lua�ű�
	DUICheckBox*					m_pCheckBox;

};