#include "extglobal.h"
#include "flash-control.h"
#include "flash-event-sink.h"
#include "dcf-terminal-def.h"
#include "dcf-utils.h"
#include <shlobj.h>
#include "dcf-logger.h"

namespace
{
	HMODULE g_specific_flash_module_ = NULL;
}

class CControlContainer:public IOleClientSite,public IOleInPlaceSite
{
	HWND m_hWnd;
	ULONG m_refCnt;
public:
	CControlContainer(HWND hWnd)
	{
		m_hWnd = hWnd;
		m_refCnt = 1;
	}
	~CControlContainer()
	{
		_ASSERT(m_refCnt == 0);
	}
	//IUnknown
	STDMETHOD_(ULONG,AddRef())
	{
		return ++m_refCnt;
	}
	STDMETHOD_(ULONG,Release())
	{
		if (--m_refCnt == 0)
		{
			delete this;
			return 0;
		}
		return m_refCnt;
	}
	STDMETHOD(QueryInterface(REFIID riid,void **ppvObject))
	{
		*ppvObject = NULL;
		if ( IID_IUnknown == riid)
		{
			*ppvObject = (IUnknown*)(IOleInPlaceSite*)this;
		}
		else if (IID_IOleClientSite == riid)
		{
			*ppvObject = (IOleClientSite*)this;
		}
		else if (IID_IOleWindow == riid)
		{
			*ppvObject = (IOleWindow*)this;
		}
		else if (IID_IOleInPlaceSite == riid)
		{
			*ppvObject = (IOleInPlaceSite*)this;
		}
		else
			return E_NOINTERFACE;
		AddRef();
		return S_OK;
	}
	//IOleControlSite
	STDMETHOD(SaveObject())
	{
		return E_NOTIMPL;
	}
	STDMETHOD(GetMoniker(DWORD,DWORD,IMoniker**))
	{
		return E_NOTIMPL;
	}
	STDMETHOD(GetContainer(IOleContainer **ppContainer))
	{
		return E_NOINTERFACE;
	}
	STDMETHOD(ShowObject())
	{
		return S_OK;
	}
	STDMETHOD(OnShowWindow(BOOL bShow))
	{
        _YY_UNUSED( bShow );
		return S_OK;
	}
	STDMETHOD(RequestNewObjectLayout())
	{
		return E_NOTIMPL;
	}
	//IOleWindow
	STDMETHOD(GetWindow(HWND * pHwnd))
	{
		*pHwnd = m_hWnd;
		return S_OK;
	}
	STDMETHOD(ContextSensitiveHelp(BOOL bEnterMode))
	{
        _YY_UNUSED( bEnterMode );
		return S_OK;
	}
	//IOleInPlaceSite
	STDMETHOD(CanInPlaceActivate())
	{
		return S_OK;
	}
	STDMETHOD(OnInPlaceActivate())
	{
		return S_OK;
	}
	STDMETHOD(OnUIActivate())
	{
		return S_OK;
	}
	STDMETHOD(GetWindowContext(/* [out] */ IOleInPlaceFrame **ppFrame,
		/* [out] */ IOleInPlaceUIWindow **ppDoc,
		/* [out] */ LPRECT lprcPosRect,
		/* [out] */ LPRECT lprcClipRect,
		/* [out][in] */ LPOLEINPLACEFRAMEINFO lpFrameInfo))
	{
		*ppFrame = NULL;
		*ppDoc = NULL;

		GetClientRect(m_hWnd,lprcPosRect);
		GetClientRect(m_hWnd,lprcClipRect);

		lpFrameInfo->fMDIApp = FALSE;
		lpFrameInfo->hwndFrame = m_hWnd;
		lpFrameInfo->haccel = NULL;
		lpFrameInfo->cAccelEntries = 0;

		return S_OK;
	}
	STDMETHOD(Scroll(SIZE scrollSize))
	{
		return S_OK;
	}
	STDMETHOD(OnUIDeactivate(BOOL bUndoable))
	{
        _YY_UNUSED( bUndoable );
		return S_OK;
	}
	STDMETHOD(OnInPlaceDeactivate())
	{
		return S_OK;
	}
	STDMETHOD(DiscardUndoState())
	{
		return S_OK;
	}
	STDMETHOD(DeactivateAndUndo())
	{
		return S_OK;
	}
	STDMETHOD(OnPosRectChange(LPCRECT lprcPosRect))
	{
		return S_OK;
	}
};

HRESULT __stdcall MyCoCreateInstance(
									 LPCTSTR szDllName,
									 IN REFCLSID rclsid,
									 IUnknown* pUnkOuter,
									 IN REFIID riid,
									 OUT LPVOID FAR* ppv)
{
	HRESULT hr = REGDB_E_KEYMISSING;

	g_specific_flash_module_ = ::LoadLibrary(szDllName);
	if (g_specific_flash_module_ == 0)
		return hr;

	typedef HRESULT (__stdcall *pDllGetClassObject)(IN REFCLSID rclsid, 
		IN REFIID riid, OUT LPVOID FAR* ppv);

	pDllGetClassObject GetClassObject = 
		(pDllGetClassObject)::GetProcAddress(g_specific_flash_module_, "DllGetClassObject");
	if (GetClassObject == 0)
	{
		::FreeLibrary(g_specific_flash_module_);
		return hr;
	}

	IClassFactory *pIFactory;

	hr = GetClassObject(rclsid, IID_IClassFactory, (LPVOID *)&pIFactory);

	if (!SUCCEEDED(hr))
		return hr;

	hr = pIFactory->CreateInstance(pUnkOuter, riid, ppv);
	pIFactory->Release();

	return hr;
}

HRESULT CreateAxControl(HWND hWnd,const wchar_t * ProgId,IUnknown ** ppControlUnknown,IUnknown ** ppContainerUnknown)
{
	HRESULT hr;
	CLSID cls;
	IOleObject * pObject = NULL;
	CControlContainer * pContainer = NULL;
	hr = CLSIDFromProgID(ProgId,&cls);
	if (FAILED(hr)) goto exit1;

	{
		// 直接指定flash ocx版本
		TCHAR buffer[MAX_PATH] = {0};
		SHGetSpecialFolderPath( NULL,buffer,CSIDL_APPDATA,NULL );
		std::wstring path = std::wstring( buffer ) + L"\\duowan\\yy\\flash\\flash.ocx";
		hr = MyCoCreateInstance(path.c_str(), cls, NULL, IID_IOleObject, (void**)&pObject);
	}

	// 如果指定的版本有问题，就用本地安装的版本
	if (FAILED(hr))
	{
		DCFLogError << L"duowan\\yy\\flash\\flash.ocx load fail, try to use local flash";
		hr = CoCreateInstance(cls,NULL,CLSCTX_INPROC_SERVER|CLSCTX_INPROC_HANDLER|CLSCTX_LOCAL_SERVER,IID_IOleObject,(void**)&pObject);
	}

	if (FAILED(hr)) goto exit1;

	pContainer = new CControlContainer(hWnd);
	hr = pObject->SetClientSite(pContainer);
	if (FAILED(hr)) goto exit1;
	hr = pObject->DoVerb(OLEIVERB_SHOW,0,pContainer,0,hWnd,0);
	if (FAILED(hr)) goto exit1;

    pObject->QueryInterface(IID_IUnknown,(void**)ppControlUnknown);
	pContainer->QueryInterface(IID_IUnknown,(void**)ppContainerUnknown);
	hr = S_OK;
exit1:
	if (pObject) pObject->Release();
	if (pContainer) pContainer->Release();
	return hr;
}

HRESULT DispSetProperty(IUnknown * pUnk,const wchar_t * prop,VARIANT * pVal)
{
	IDispatch * pDisp = NULL;
	HRESULT hr;
	DISPID propId;
	const wchar_t * ppNames[] = {prop};
	DISPPARAMS dispparams;
	DISPID paramDispId;
	hr = pUnk->QueryInterface(IID_IDispatch,(void**)&pDisp);
	if (FAILED(hr)) return hr;
	//Query prop id
	hr = pDisp->GetIDsOfNames(IID_NULL,(LPOLESTR*)ppNames,1,LANG_SYSTEM_DEFAULT,&propId);
	if (FAILED(hr)) goto exit1;
	//call
	paramDispId = DISPID_PROPERTYPUT;
	dispparams.cArgs = 1;
	dispparams.cNamedArgs = 1;
	dispparams.rgdispidNamedArgs =&paramDispId;
	dispparams.rgvarg = pVal;
	hr = pDisp->Invoke(propId,IID_NULL,LOCALE_SYSTEM_DEFAULT,DISPATCH_PROPERTYPUT,&dispparams,NULL,NULL,NULL);
exit1:
	if (pDisp) pDisp->Release();
	return hr;
}

HRESULT DisGetInvoke(IUnknown * pUnk, const wchar_t * name, VARIANT * param1)
{
	IDispatch * pDisp = NULL;
	HRESULT hr;
	DISPID methId;
	const wchar_t * ppNames[] = {name};
	DISPPARAMS dispparams;
	hr = pUnk->QueryInterface(IID_IDispatch,(void**)&pDisp);
	if (FAILED(hr)) return hr;
	//query names
	hr = pDisp->GetIDsOfNames(IID_NULL,(LPOLESTR*)ppNames,1,LANG_SYSTEM_DEFAULT,&methId);
	if (FAILED(hr)) goto exit1;
	//call
	dispparams.cArgs = 0;
	dispparams.cNamedArgs = 0;
	dispparams.rgdispidNamedArgs = NULL;
	dispparams.rgvarg = param1;
	hr = pDisp->Invoke(methId,IID_NULL,LOCALE_SYSTEM_DEFAULT,DISPATCH_METHOD,&dispparams,param1,NULL,NULL);

exit1:
	if (pDisp) pDisp->Release();
	return hr;
}

HRESULT DispInvoke1(IUnknown * pUnk,const wchar_t * name,VARIANT * param1)
{
	IDispatch * pDisp = NULL;
	HRESULT hr;
	DISPID methId;
	const wchar_t * ppNames[] = {name};
	DISPPARAMS dispparams;
	hr = pUnk->QueryInterface(IID_IDispatch,(void**)&pDisp);
	if (FAILED(hr)) return hr;
	//query names
	hr = pDisp->GetIDsOfNames(IID_NULL,(LPOLESTR*)ppNames,1,LANG_SYSTEM_DEFAULT,&methId);
	if (FAILED(hr)) goto exit1;
	//call
	dispparams.cArgs = 1;
	dispparams.cNamedArgs = 0;
	dispparams.rgdispidNamedArgs = NULL;
	dispparams.rgvarg = param1;
	hr = pDisp->Invoke(methId,IID_NULL,LOCALE_SYSTEM_DEFAULT,DISPATCH_METHOD,&dispparams,NULL,NULL,NULL);

exit1:
	if (pDisp) pDisp->Release();
	return hr;
}

FlashControl::FlashControl() :
    parent_hwnd_(NULL),
	p_control_(NULL),
    event_listener_(NULL),
    m_flahsWindowHandle(NULL)
{
	OleInitialize(NULL);
}

FlashControl::~FlashControl()
{
	unsetEventHandler();
	Destoy();
}

BOOL FlashControl::Create(HWND parent_hwnd)
{
	if (NULL != p_control_)
	{
		return FALSE;
	}

	parent_hwnd_ = parent_hwnd;
	IUnknown * pContainer = NULL;
	HRESULT hr = CreateAxControl(parent_hwnd_, L"ShockwaveFlash.ShockwaveFlash", &p_control_, &pContainer);
	if (NULL != pContainer)
	{
		pContainer->Release();
		pContainer = NULL;
	}

	if (FAILED(hr))
	{
		const wchar_t * errstr;
		if (FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
			0, hr, LANG_SYSTEM_DEFAULT, (LPWSTR)&errstr, 0, 0)!=0)
		{
			//MessageBoxW(parent_hwnd_, errstr, L"Error", MB_OK);
			LocalFree((HLOCAL)errstr);
		}

		if (NULL != p_control_)
		{
			p_control_->Release();
			p_control_ = NULL;
		}
		return FALSE;
	}

	AxAdviseAll(p_control_, this);

    IOleInPlaceObject * pInPlaceObject;
    if ( SUCCEEDED(p_control_->QueryInterface(IID_IOleInPlaceObject,(void**)&pInPlaceObject)))
    {
        pInPlaceObject->GetWindow(&m_flahsWindowHandle);
        pInPlaceObject->Release();
    }

	return TRUE;
}

BOOL FlashControl::MoveWindow( const RECT& rc )
{
    if( !p_control_ )
    {
        return FALSE;
    }

    IOleInPlaceObject * pInPlaceObject;
    if ( SUCCEEDED(p_control_->QueryInterface(IID_IOleInPlaceObject,(void**)&pInPlaceObject)))
    {
        HWND hwnd = NULL;
        HRESULT hr = pInPlaceObject->GetWindow(&hwnd);
        if (FAILED(hr))
        {
            return FALSE;
        }

        hr = pInPlaceObject->SetObjectRects(&rc, &rc);

        pInPlaceObject->Release();
    }
    return TRUE;
}

BOOL FlashControl::SetParent( HWND parent )
{
    if( !p_control_ )
    {
        return FALSE;
    }

    IOleInPlaceObject * pInPlaceObject;
    if ( SUCCEEDED(p_control_->QueryInterface(IID_IOleInPlaceObject,(void**)&pInPlaceObject)))
    {
        HWND hwnd = NULL;
        HRESULT hr = pInPlaceObject->GetWindow(&hwnd);
        if (FAILED(hr))
        {
            return FALSE;
        }

        ::SetParent( hwnd, parent );

        pInPlaceObject->Release();
    }
    return TRUE;
}

BOOL FlashControl::Play(LPCTSTR flash_file)
{
	if (NULL != p_control_)
	{
		VARIANT src;
		src.vt = VT_BSTR;
		src.bstrVal = SysAllocString(flash_file);
		HRESULT hr = DispSetProperty(p_control_, L"movie", &src);
        ::VariantClear( &src );

		if (FAILED(hr))
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}
}

void FlashControl::Destoy()
{
	if (NULL != p_control_)
	{
		IOleObject * pObject = NULL;
		if (SUCCEEDED(p_control_->QueryInterface(IID_IOleObject, (void**)&pObject)))
		{
			if (NULL != pObject)
			{
				pObject->Close(0);
				pObject->Release();
				pObject = NULL;
			}
		}
		p_control_->Release();
		p_control_ = NULL;
	}

	if (g_specific_flash_module_)
	{
		::FreeLibrary(g_specific_flash_module_);
		g_specific_flash_module_ = NULL;
	}
}

void FlashControl::OnFsCommand(LPCTSTR command, LPCTSTR args)
{
    _YY_UNUSED( command );
    _YY_UNUSED( args );
}

void FlashControl::OnFlashCall( LPCTSTR invokeXml )
{
    if (NULL != p_control_)
    {
        std::wstring returnXml;
        if( event_listener_ )
        {
            event_listener_->CallCPlusPlus( invokeXml, returnXml );
        }

        if( !returnXml.empty())
        {
            VARIANT returnString;
            returnString.vt = VT_BSTR;
            returnString.bstrVal = SysAllocString( returnXml.c_str());
            //调用SetReturnValue来设置返回值
            DispInvoke1(p_control_, L"SetReturnValue", &returnString);
            ::VariantClear( &returnString );
        }
    }
}

void FlashControl::CallFunction(LPCTSTR request)
{
	if (NULL != p_control_)
	{
		VARIANT src;
		src.vt = VT_BSTR;
		src.bstrVal = SysAllocString(request);
		DispInvoke1(p_control_, L"CallFunction", &src);
        ::VariantClear( &src );
	}
}

int FlashControl::GetVersion()
{
	if (NULL != p_control_)
	{
		VARIANT src;
		src.vt = VT_I4;
		DisGetInvoke(p_control_, L"flashversion", &src);
		return src.intVal;
	}
	return 0;
}

BOOL FlashControl::ShowWindow( bool show )
{
    if( !p_control_ )
    {
        return FALSE;
    }

    IOleInPlaceObject * pInPlaceObject;
    if ( SUCCEEDED(p_control_->QueryInterface(IID_IOleInPlaceObject,(void**)&pInPlaceObject)))
    {
        HWND hwnd = NULL;
        HRESULT hr = pInPlaceObject->GetWindow(&hwnd);
        if (FAILED(hr))
        {
            return FALSE;
        }

        if( show )
        {
			//::SetWindowLong( hwnd, GWL_USERDATA, YY_SDK_CONTAINER_HWND_DATA);
            ::ShowWindow(hwnd, SW_SHOW);
        }
        else
        {
			//::SetWindowLong( hwnd, GWL_USERDATA, 0); //窗口影藏就没必要刷新了
            ::ShowWindow(hwnd, SW_HIDE);
        }
        pInPlaceObject->Release();
    }
    return TRUE;
}

void FlashControl::setEventHandler( IFlashEventHandler* listenner )
{
    assert( listenner );
    event_listener_ = listenner;
}

void FlashControl::unsetEventHandler()
{
    event_listener_ = NULL;
}

void FlashControl::EnableMenu( bool enable )
{
    if ( !p_control_ )
    {
        return;
    }

    VARIANT src;
    src.vt = VT_BSTR;

    src.bstrVal = SysAllocString( enable ? L"true" : L"false" );
    DispSetProperty(p_control_, L"menu", &src);
    ::VariantClear( &src );
}

void FlashControl::SetQuality( const WCHAR* quality )
{
    if ( !p_control_ )
    {
        return;
    }

    if( !quality )
    {
        return;
    }

    VARIANT src;
    src.vt = VT_BSTR;

    src.bstrVal = SysAllocString( quality );
    DispSetProperty(p_control_, L"quality", &src);
    ::VariantClear( &src );
}

HWND FlashControl::getWindowHandle() const
{
    return m_flahsWindowHandle;
}

void FlashControl::SetWMode( const WCHAR* wmode )
{
    if ( !p_control_ )
    {
        return;
    }

    if( !wmode )
    {
        return;
    }

    VARIANT src;
    src.vt = VT_BSTR;

    src.bstrVal = SysAllocString( wmode );
    DispSetProperty(p_control_, L"wmode", &src);
    ::VariantClear( &src );
}
