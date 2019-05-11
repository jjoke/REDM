//! ʵ��һ��flash�ؼ�
/*! 
 * \flash-control.h
 * \author lihansi
 * \date 2011-06-14
 *
 * ���ݻ�������Ƽ����޹�˾ ��Ȩ���� (c) 2005-2010 DuoWan.com [������Ϸ]
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
	//����һ��ActiveX �ؼ�
	HRESULT CreateAxControl(
		HWND hWnd, const wchar_t * ProgId,IUnknown ** ppControlUnknown,IUnknown ** ppContainerUnknown);
	
	//����һ��ActiveX�ؼ��ı���ֵ
	HRESULT DispSetProperty(IUnknown * pUnk, const wchar_t * prop, VARIANT * pVal);
	
	//ִ��һ��ActiveX�ؼ����ڲ��ӿ�
	HRESULT DispInvoke1(IUnknown * pUnk, const wchar_t * name, VARIANT * param1);

	//ִ��һ�����з���ֵ�Ĳ���
	HRESULT DisGetInvoke(IUnknown * pUnk, const wchar_t * name, VARIANT * param1);
};


class FlashControl : public IFlashControl
{
public:
	FlashControl();
	virtual ~FlashControl();

	//����
	BOOL Create(HWND parent_hwnd);

    //��ʾ������
    BOOL ShowWindow( bool show );

	//����λ��
	BOOL MoveWindow( const RECT& rc );

    //���ø�����
    BOOL SetParent( HWND parent );

	//����
	BOOL Play(LPCTSTR flash_file);

	//����
	void Destoy();

	//����Flash����
    virtual void CallFunction(LPCTSTR request);
    virtual HWND getWindowHandle() const;

	//��ȡFlash�������İ汾
	int GetVersion();

	//fscommand���¼�
	void OnFsCommand(LPCTSTR command, LPCTSTR args);

    void OnFlashCall(LPCTSTR invokeXml);

    void EnableMenu( bool enable );

    // ���ܵ�ȡֵ low, autolow, autohigh, medium, high, best
    void SetQuality( const WCHAR* quality );

    // ���ܵ�ȡֵtransparent, direct 
    void SetWMode( const WCHAR* wmode );

    // ע���¼�����
    void setEventHandler( IFlashEventHandler* listenner );
    void unsetEventHandler();

protected:
	HWND       parent_hwnd_;   //�����ھ��
	IUnknown * p_control_;     //�ؼ�

    //Flash�ؼ����ھ��
    HWND m_flahsWindowHandle;

    IFlashEventHandler* event_listener_;	
};
#endif //FLASH_CONTROL_H