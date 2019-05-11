//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DDMDispatchMgr.h 
// File Des:ͳһ����ַ���ת����
// File Summary: MgrΪManager��д
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-17	1.0			
//-------------------------------------------------------
#pragma once

namespace DM
{

	/// <summary>
	///		�Ծ�̬��ʽת��xml���Խ�������<see cref="IDMAttribute"/>
	/// </summary>
	class DM_EXPORT DMAttributeDispatch
	{
	public:
		static void SetAttributeDispatch(IDMAttribute* pAttributeObj);
		static DMCode ParseInt(LPCWSTR lpszValue,int&Obj);				
		static DMCode ParseBool(LPCWSTR lpszValue,bool&Obj);			
		static DMCode ParseColor(LPCWSTR lpszValue,DMColor&Obj);		
		static DMCode ParseSize(LPCWSTR lpszValue,DM::CSize&Obj);		
		static DMCode ParsePoint(LPCWSTR lpszValue,DM::CPoint&Obj);	
		static DMCode ParseRect(LPCWSTR lpszValue,DM::CRect&Obj);		
	public: static IDMAttribute *m_pAttributeObj;
	};

	/// <summary>
	///		�Ծ�̬��ʽת��Log����<see cref="IDMLog"/>
	/// </summary>
	class DM_EXPORT DMLogDispatch
	{
	public:
		static void SetLogDispatch(IDMLog* pLogObj);
		static DMCode LogW(DMLOGLEVEL iLevel,LPCWSTR lpszFuncName, LPCWSTR lpszFileName, int iLine,LPCWSTR szFmt,...);
	public:static IDMLog *m_pLogObj;
		   static DMLock  m_Lock;
	};

}//namespace DM

namespace DMAttr
{
	class DM_EXPORT DMInitAttrDispatch
	{
	public:
		static wchar_t* GetAttrValue(wchar_t* cls,wchar_t *pBuf);
	};
}