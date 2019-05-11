//! 实现一个flash控件
/*! 
 * \flash-control.h
 * \author lihansi
 * \date 2011-06-14
 *
 * 广州华多网络科技有限公司 版权所有 (c) 2005-2010 DuoWan.com [多玩游戏]
 */

#ifndef FLASH_CONTROL_H
#define FLASH_CONTROL_H

#include <windows.h>
#include <string>
#include "flash-control-i.h"
namespace DCF
{
	namespace dac
	{
		struct IDACAddonDeconator;
	}
};

extern "C"
{
	//创建一个ActiveX 控件
	HRESULT CreateAxControl(
		HWND hWnd, const wchar_t * ProgId,IUnknown ** ppControlUnknown,IUnknown ** ppContainerUnknown);
	
	//设置一个ActiveX控件的变量值
	HRESULT DispSetProperty(IUnknown * pUnk, const wchar_t * prop, VARIANT * pVal);
	
	//执行一个ActiveX控件的内部接口
	HRESULT DispInvoke1(IUnknown * pUnk, const wchar_t * name, VARIANT * param1);

	//执行一个具有返回值的操作
	HRESULT DisGetInvoke(IUnknown * pUnk, const wchar_t * name, VARIANT * param1);
};


class FlashControl : public IFlashControl
{
public:
	FlashControl();
	virtual ~FlashControl();

	//创建
	BOOL Create(HWND parent_hwnd);

    //显示和隐藏
    BOOL ShowWindow( bool show );

	//设置位置
	BOOL MoveWindow( const RECT& rc );

    //设置父窗口
    BOOL SetParent( HWND parent );

	//播放
	BOOL Play(LPCTSTR flash_file);

	//销毁
	void Destoy();

	//调用Flash函数
    virtual void CallFunction(LPCTSTR request);
    virtual HWND getWindowHandle() const;

	//获取Flash播放器的版本
	int GetVersion();

	//fscommand的事件
	void OnFsCommand(LPCTSTR command, LPCTSTR args);

    void OnFlashCall(LPCTSTR invokeXml);

    void EnableMenu( bool enable );

    // 可能的取值 low, autolow, autohigh, medium, high, best
    void SetQuality( const WCHAR* quality );

    // 可能的取值transparent, direct 
    void SetWMode( const WCHAR* wmode );

    // 注册事件监听
    void setEventHandler( IFlashEventHandler* listenner );
    void unsetEventHandler();

protected:
	HWND       parent_hwnd_;   //父窗口句柄
	IUnknown * p_control_;     //控件

    //Flash控件窗口句柄
    HWND m_flahsWindowHandle;

    IFlashEventHandler* event_listener_;	
};
#endif //FLASH_CONTROL_H