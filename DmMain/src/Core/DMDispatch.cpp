#include "DmMainAfx.h"
#include "DMDispatch.h"
#include <stdarg.h>

namespace DM
{
	/// DMAttributeDispatch------------------------------
	IDMAttribute *DMAttributeDispatch::m_pAttributeObj=NULL;
	void DMAttributeDispatch::SetAttributeDispatch(IDMAttribute* pAttributeObj)
	{
		DMASSERT_EXPR(NULL!=pAttributeObj, L"m_pAttributeObjΪ��!");
		m_pAttributeObj = pAttributeObj;
	}

	DMCode DMAttributeDispatch::ParseInt(LPCWSTR lpszValue,int&Obj)
	{
		DMASSERT_EXPR(NULL!=m_pAttributeObj, L"m_pAttributeObjδ��ʼ��!");
		return m_pAttributeObj->ParseInt(lpszValue, Obj);
	}

	DMCode DMAttributeDispatch::ParseBool(LPCWSTR lpszValue,bool&Obj)
	{
		DMASSERT_EXPR(NULL!=m_pAttributeObj, L"m_pAttributeObjδ��ʼ��!");
		return m_pAttributeObj->ParseBool(lpszValue, Obj);
	}

	DMCode DMAttributeDispatch::ParseColor(LPCWSTR lpszValue,DMColor&Obj)
	{
		DMASSERT_EXPR(NULL!=m_pAttributeObj, L"m_pAttributeObjδ��ʼ��!");
		return m_pAttributeObj->ParseColor(lpszValue, Obj);
	}

	DMCode DMAttributeDispatch::ParseSize(LPCWSTR lpszValue,DM::CSize&Obj)
	{
		DMASSERT_EXPR(NULL!=m_pAttributeObj, L"m_pAttributeObjδ��ʼ��!");
		return m_pAttributeObj->ParseSize(lpszValue, Obj);
	}

	DMCode DMAttributeDispatch::ParsePoint(LPCWSTR lpszValue,DM::CPoint&Obj)
	{
		DMASSERT_EXPR(NULL!=m_pAttributeObj, L"m_pAttributeObjδ��ʼ��!");
		return m_pAttributeObj->ParsePoint(lpszValue, Obj);
	}

	DMCode DMAttributeDispatch::ParseRect(LPCWSTR lpszValue,DM::CRect&Obj)
	{
		DMASSERT_EXPR(NULL!=m_pAttributeObj, L"m_pAttributeObjδ��ʼ��!");
		return m_pAttributeObj->ParseRect(lpszValue, Obj);
	}

	// DMLogDispatch------------------------------------
	IDMLog *DMLogDispatch::m_pLogObj = NULL;
	DMLock  DMLogDispatch::m_Lock;
	void DMLogDispatch::SetLogDispatch(IDMLog* pLogObj)
	{
		DMAutoLock autolock(&m_Lock);
		m_pLogObj = pLogObj;
	}
	DMCode DMLogDispatch::LogW(DMLOGLEVEL iLevel,LPCWSTR lpszFuncName, LPCWSTR lpszFileName, int iLine,LPCWSTR szFmt,...)
	{
		DMCode iErr = DM_ECODE_OK;
		do 
		{
			if (NULL == m_pLogObj)
			{
				iErr = DM_ECODE_FAIL;
				break;
			}
			DMAutoLock autolock(&m_Lock);
			va_list arg;
			va_start(arg, szFmt);
			int len = _vscwprintf(szFmt, arg);
			DMBufT<wchar_t> pBuf;pBuf.Allocate(len+1);
			vswprintf_s(pBuf, (len+1), szFmt, arg);
			va_end(arg);
			iErr = m_pLogObj->LogW(iLevel, lpszFuncName, lpszFileName, iLine, pBuf);
		} while (false);

		return iErr;
	}
}//namespace DM

namespace DMAttr
{
	// ----------------------------------------------------
	// �ڲ�ǿ�ƹ涨XML�����ַ������巽ʽ
	wchar_t* DMInitAttrDispatch::GetAttrValue(wchar_t* cls,wchar_t *pBuf)
	{  
		wchar_t*pLow = wcsstr(pBuf,L"_");
		if (!pLow){DMASSERT_EXPR(0,L"��ʹ������_���巽ʽ,��INT_ihei");}
		pLow++;
		return pLow;
	}
}