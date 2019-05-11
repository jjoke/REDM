//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: IDUIWeb.h 
// File Des:�ṩWeb����ӿ�
// File Summary:
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-4-7	1.0			   
//--------------------------------------------------------
#pragma once

namespace DM
{
	/// <summary>
	///		 Dispatch�¼�����,����˵����ο�https://msdn.microsoft.com/en-us/library/aa752084.aspx
	/// </summary>
	class IDMWebEvent
	{
	public:
		virtual HRESULT BeforeNavigate2(DUIWND hWnd, DMIN IDispatch *pDisp, DMIN wchar_t *pUrl,DMIN int Flags,DMIN wchar_t *pTargetFrameName,DMIN VARIANT *pPostData,DMIN wchar_t *pHeaders,DMINOUT VARIANT_BOOL *bCancel){return S_OK;}
		virtual HRESULT ClientToHostWindow(DUIWND hWnd, DMIN long *pCx, DMINOUT long *pCy){return S_OK;}
		virtual HRESULT CommandStateChange(DUIWND hWnd, DMIN LONG command, DMIN VARIANT_BOOL enable){return S_OK;}
		virtual HRESULT DocumentComplete(DUIWND hWnd,DMIN IDispatch *pDisp,DMIN wchar_t *pUrl){return S_OK;}
		virtual HRESULT DownloadBegin(DUIWND hWnd){return S_OK;}
		virtual HRESULT DownloadComplete(DUIWND hWnd){return S_OK;}
		virtual HRESULT FileDownload(DUIWND hWnd, DMIN VARIANT_BOOL ActiveDocument,DMINOUT VARIANT_BOOL *Cancel){return S_OK;}
		virtual HRESULT NavigateComplete2(DUIWND hWnd,DMIN IDispatch *pDisp,DMIN wchar_t *pUrl){return S_OK;}
		virtual HRESULT NavigateError(DUIWND hWnd, DMIN IDispatch *pDisp,DMIN wchar_t *pUrl,DMIN wchar_t *pTargetFrameName,DMIN int statusCode,DMINOUT VARIANT_BOOL *bCancel){return S_OK;}
		virtual HRESULT NewWindow2(DUIWND hWnd, DMINOUT IDispatch **pDisp,DMINOUT VARIANT_BOOL *bCancel){return S_OK;}
		virtual HRESULT NewWindow3(DUIWND hWnd, DMINOUT IDispatch **pDisp,DMINOUT VARIANT_BOOL *bCancel,DMIN DWORD dwFlags,DMIN wchar_t *pUrlContext,DMIN wchar_t *pUrl){return S_OK;}
		virtual HRESULT OnFullScreen(DUIWND hWnd, DMIN VARIANT_BOOL bFullScreen){return S_OK;}
		virtual HRESULT OnMenuBar(DUIWND hWnd, DMIN VARIANT_BOOL bMenuBar){return S_OK;}
		virtual HRESULT OnQuit(DUIWND hWnd){return S_OK;}
		virtual HRESULT OnStatusBar(DUIWND hWnd, DMIN VARIANT_BOOL bStatusBar){return S_OK;}
		virtual HRESULT OnTheaterMode(DUIWND hWnd, DMIN VARIANT_BOOL bTheaterMode){return S_OK;}
		virtual HRESULT OnToolBar(DUIWND hWnd, DMIN VARIANT_BOOL bToolBar){return S_OK;}
		virtual HRESULT OnVisible(DUIWND hWnd, DMIN VARIANT_BOOL bVisible){return S_OK;}
		virtual HRESULT PrintTemplateInstantiation(DUIWND hWnd,DMIN IDispatch *pDisp){return S_OK;}
		virtual HRESULT PrintTemplateTeardown(DUIWND hWnd,DMIN IDispatch *pDisp){return S_OK;}
		virtual HRESULT PrivacyImpactedStateChange(DUIWND hWnd, DMIN VARIANT_BOOL bPrivacyImpacted){return S_OK;}
		virtual HRESULT ProgressChange(DUIWND hWnd, DMIN LONG Progress,DMIN LONG ProgressMax){return S_OK;}
		virtual HRESULT PropertyChange(DUIWND hWnd, DMIN wchar_t *pProperty){return S_OK;}
		virtual HRESULT SetPhishingFilterStatus(DUIWND hWnd, DMIN LONG phishingFilterStatus){return S_OK;}
		virtual HRESULT SetSecureLockIcon(DUIWND hWnd, DMIN int SecureLockIcon){return S_OK;}
		virtual HRESULT StatusTextChange(DUIWND hWnd,DMIN wchar_t *pText){return S_OK;}
		virtual HRESULT TitleChange(DUIWND hWnd, DMIN wchar_t *pText){return S_OK;}
		virtual HRESULT WindowClosing(DUIWND hWnd, DMIN VARIANT_BOOL IsChildWindow,DMINOUT VARIANT_BOOL *bCancel){return S_OK;}
		virtual HRESULT WindowSetHeight(DUIWND hWnd, DMIN LONG height){return S_OK;}
		virtual HRESULT WindowSetLeft(DUIWND hWnd, DMIN LONG left){return S_OK;}
		virtual HRESULT WindowSetResizable(DUIWND hWnd, DMIN VARIANT_BOOL bResizable){return S_OK;}
		virtual HRESULT WindowSetTop(DUIWND hWnd, DMIN LONG top){return S_OK;}
		virtual HRESULT WindowSetWidth(DUIWND hWnd, DMIN LONG width){return S_OK;}
		virtual HRESULT WindowStateChanged(DUIWND hWnd, DMIN DWORD dwFlags,DMIN DWORD dwValidFlagsMask){return S_OK;}
		virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames(DUIWND hWnd, REFIID riid, LPOLESTR* rgszNames,UINT cNames, LCID lcid, DISPID* rgDispId){return S_OK;}
		virtual HRESULT STDMETHODCALLTYPE Invoke(DUIWND hWnd, DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags,DISPPARAMS* pDispParams, VARIANT* pVarResult, EXCEPINFO* pExcepInfo,UINT* puArgErr){return S_OK;}

		// ���ֽӿ�Ϊwebkit����
		virtual HRESULT OnPreKeyEvent(DUIWND hWnd, MSG* pMsg){return E_NOTIMPL;}
	};

	/// <summary>
	///		 Web����ӿ�
	/// </summary>
	class IDUIWeb
	{
	public:
		enum{DMWEBTYPE_IE,DMWEBTYPE_WEBKIT,DMWEBTYPE_OSRWEBKIT,};
		/// @brief ���ص�ǰ������(ie/webkit/����webkit)
		/// @return Ĭ��ΪIE
		virtual int GetWebType(){return DMWEBTYPE_IE;};

		/// @brief �����¼�������
		/// @param[in]		pEventHandler		�¼�������ָ��
		/// @return HRESULT��S_OK
		virtual HRESULT SetEvtHandler(IDMWebEvent* pEventHandler){return E_NOTIMPL;};

		/// @brief ��ָ��ҳ��
		/// @param[in]		pszURL		��Ҫ�򿪵�url�ַ���
		/// @return HRESULT��ʧ��ΪS_FALSE
		virtual HRESULT OpenUrl(LPCWSTR pszURL,int iFlags = 0,LPCWSTR pszTargetFrameName = NULL,LPCWSTR pszHeaders = NULL, LPCSTR pszPostData = NULL,int iPostDataLen = 0){return E_NOTIMPL;};

		/// @brief ��ָ��ҳ��
		/// @param[in]		pszURL		���յ�ǰurl���ַ���������
		/// @param[in]		nMaxLen		�ַ�������������󳤶�
		/// @return HRESULT��ʧ��ΪS_FALSE
		virtual HRESULT GetUrl(LPWSTR pszUrl, int nMaxLen){return E_NOTIMPL;};

		/// @brief ������������轹��
		virtual HRESULT SetWebFocus(){return E_NOTIMPL;};

		/// @brief ���OLE���ھ��
		/// @return HWND��ʧ��ΪNULL
		virtual HWND GetOleWindow(){return NULL;};

		/// @brief ��������Web������
		/// @return HRESULT��ʧ��ΪS_FALSE
		virtual HRESULT UpdateWebRect(LPRECT lpRect){return E_NOTIMPL;}

		/// @brief BUSY״̬
		/// @return ture or false
		virtual bool IsBusy(){return false;};

		/// @brief ֹͣ
		/// @return HRESULT��ʧ��ΪS_FALSE
		virtual HRESULT Stop(){return E_NOTIMPL;};

		/// @brief �ر������
		/// @return HRESULT��ʧ��ΪS_FALSE
		virtual HRESULT Quit(){return E_NOTIMPL;};

		/// @brief ˢ��
		/// @return HRESULT��ʧ��ΪS_FALSE
		virtual HRESULT Refresh(){return E_NOTIMPL;};

		/// @brief ָ��ˢ�¼���ˢ��
		/// @param[in]		nLevel		ˢ�³����� ���˲������ͣ� REFRESH_NORMAL 0x0 / REFRESH_IFEXPIRED 0x01 / REFRESH_COMPLETELY 0x03
		/// @return HRESULT��ʧ��ΪS_FALSE
		virtual HRESULT Refresh2(UINT32 nLevel){return E_NOTIMPL;};

		/// @brief ����
		/// @return HRESULT��ʧ��ΪS_FALSE
		virtual HRESULT GoBack(){return E_NOTIMPL;};

		/// @brief ǰ��
		/// @return HRESULT��ʧ��ΪS_FALSE
		virtual HRESULT GoForward(){return E_NOTIMPL;};

		/// @brief �ڵ�ǰ�������������ִ�нű�
		/// @return HRESULT��ʧ��ΪS_FALSE
		virtual HRESULT ExecuteScript(LPCWSTR pszScript){return E_NOTIMPL;};

		/// @brief ִ��ָ���������ֵĽű�
		/// @param[in]		 strFun			ָ��Ҫ�ű�ִ�еĺ�������
		/// @param[in]		 vecParams		����Ҫ�ű�ִ�еĺ����Ĳ����б�
		/// @param[out]		 strResult		���ؽű�����ִ�еĽ��
		/// @param[in]		 nMaxLen		���ؽű�����ִ�еĽ������������󳤶�
		/// @return HRESULT��ʧ��ΪE_FAIL
		virtual HRESULT ExecuteScriptFuntion(LPCWSTR pszFun, const DM::CArray<LPCWSTR>& vecParams, LPWSTR strResult = NULL,int nMaxLen = -1){return E_NOTIMPL;};

		/// @brief ��ֹ�ű�����
		/// @param[in]		 bDisable		�Ƿ��ֹ
		/// @return HRESULT��ʧ��ΪE_FAIL
		virtual HRESULT DisableScriptWarning(bool bDisable){return E_NOTIMPL;};

		/// @brief �Ƿ���ʾWeb�Ĺ�����
		/// @param[in]		 bShow			�Ƿ���ʾ
		/// @return
		virtual HRESULT SetScrollBarShow(bool bShow){return E_NOTIMPL;};

		/// @brief �Ƿ���ʾWeb���Ҽ��˵�
		/// @param[in]		 bShow			�Ƿ���ʾ
		/// @return
		virtual HRESULT SetContextMenuShow(bool bShow){return E_NOTIMPL;};

		/// @brief ת��Web��SetAttribute
		/// @param[in]		 bShow			�Ƿ���ʾ
		/// @return
		virtual HRESULT WebSetAttribute(LPCWSTR pszAttribute,LPCWSTR pszValue,bool bLoadXml){return E_NOTIMPL;};


		//---------------------------------------------------------
		// �������½ӿڣ��Լ��ݾɰ�

		/// @brief �Ƿ�ɵ�������
		/// @return ture or false
		virtual bool CanGoBack(){return false;}

		/// @brief �Ƿ�ɵ���ǰ��
		/// @return ture or false
		virtual bool CanGoForward(){return false;}
	};

}