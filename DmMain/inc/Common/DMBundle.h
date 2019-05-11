// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	DMBundle.h
// File mark:   
// File summary:DMBundle�ڲ�ʹ����new DMBundleImpl��ʵ��,ֱ����������,����Ҫnew���ڸ�ֵ����Ϊ��������ʱ,�ڲ���DMBundleImpl���ü������Զ�+1-1�����Բ��õ��Ŀ�ģ�鴫��ʱ,�ڴ汻ͻȻ�ͷ�
// ʹ�÷�ʽ�� DMBundle bundle;
//            DMBundle bundle1 = bundle; // ָ��ͬһ��DMBundleImpl�ڴ棬���ü���+1
//            DMBundle bundle2(bundle);  // ָ��ͬһ��DMBundleImpl�ڴ棬���ü���+1
//            DMBundle bundle3 = bundle.Clone();// ����һ���µ�DMBundleImpl�ڴ�,bundle3��ʼ���ü���Ϊ1
// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2019-2-24
// ----------------------------------------------------------------
#pragma once
#include "DMSmartPtrT.h"
#include "DMDelegate.h"

namespace DM
{
	/// <summary>
	///		���ð�����
	/// <summary>
	class DMBundleImpl;
	class DM_EXPORT DMBundle
	{
	public:
		DMBundle();
		DMBundle(const DMBundle& src);
		DMBundle& operator=(const DMBundle& src);
		~DMBundle();

	public:
		DMBundle Clone();										///< ���Ƶ�ǰBundle
		void Clear();											///< �Ƴ���ǰBundleӳ���е�����Ԫ��
		int Size();											    ///< �õ���ǰBundle��ӳ���С
		bool Remove(LPCWSTR key);								///< �Ƴ���ǰBundle��ӳ��Key
		bool HasKey(LPCWSTR key);								///< ��ǰBundle��ӳ��Key�Ƿ����,DM_ECODE_OK��ʾ����

		bool PutBool(LPCWSTR key, bool value);
		bool GetBool(LPCWSTR key, bool defaultValue=false) const;

		bool PutByte(LPCWSTR key, byte value);
		byte GetByte(LPCWSTR key, byte defaultValue=0) const;

		bool PutChar(LPCWSTR key, char value);
		char GetChar(LPCWSTR key, char defaultValue=0) const;

		bool PutDword(LPCWSTR key, DWORD value);
		DWORD GetDword(LPCWSTR key, DWORD defaultValue=0) const;

		bool PutDouble(LPCWSTR key, double value);
		double GetDouble(LPCWSTR key, double defaultValue=0.0f) const;

		bool PutFloat(LPCWSTR key, float value);
		float GetFloat(LPCWSTR key, float defaultValue=0.0f) const;

		bool PutInt(LPCWSTR key, int value);
		int  GetInt(LPCWSTR key, int defaultValue=0) const;

		bool PutInt64(LPCWSTR key, INT64 value);
		INT64 GetInt64(LPCWSTR key, INT64 defaultValue=0) const;

		bool PutShort(LPCWSTR key, short value);
		short GetShort(LPCWSTR key, short defaultValue=0) const;

		bool PutString(LPCWSTR key, LPCSTR value);
		LPCSTR GetString(LPCWSTR key, LPCSTR defaultValue="") const;

		bool PutStringW(LPCWSTR key, LPCWSTR value);
		LPCWSTR GetStringW(LPCWSTR key, LPCWSTR defaultValue=L"") const;

		bool PutSize(LPCWSTR key, CSize value);
		CSize GetSize(LPCWSTR key, CSize defaultValue=CSize()) const;

		bool PutRect(LPCWSTR key, CRect value);
		CRect GetRect(LPCWSTR key, CRect defaultValue=CRect()) const;

		bool PutVoidPtr(LPCWSTR key, void* value);
		void* GetVoidPtr(LPCWSTR key, void* defaultValue=NULL) const;

		bool PutIUnknownPtr(LPCWSTR key, IUnknown* value);
		IUnknown* GetIUnknownPtr(LPCWSTR key, IUnknown* defaultValue=NULL) const;

		bool PutXmlNode(LPCWSTR key, DMXmlNode value);
		DMXmlNode GetXmlNode(LPCWSTR key) const;

	public:
		DM::DMSmartPtrT<DMBundleImpl>					   m_pBundleImpl;		///< Bundle�ڴ���ʱ��m_pBundleImpl�Զ�+1���Ӷ���֤BundleImpl����������		
	};

	/// <summary>
	///		���ͷ�
	/// </summary>
	enum DMEventSenderID{DMESenderID_Unknown,DMESenderID_Base};
	class DM_EXPORT DMEventSender
	{
	public:
		DMEventSender():m_dwSize(sizeof(DMEventSender)),m_dwId(DMESenderID_Unknown){}
	public:
		DWORD                                         m_dwSize;
		DWORD                                         m_dwId;
	};


	/// <summary>
	///		�¼���bool function(const DMEventSender& , const DMBundle&)�������г���
	/// </summary>
	typedef DM::DMDelegate< bool(const DMEventSender& sender, const DMBundle& evt) > DMSlot;

}//namespace DM