//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMRegMgr.h 
// File Des:ע����ͳһ����
// File Summary: MgrΪManager��д
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-7	1.0			
//-------------------------------------------------------
#pragma once

namespace DM
{	
	/// <summary>
	///		<see cref="DefRegName"/>�����ڶ���Ĭ��ע������������
	///     ����xml����ʵ������м���ע���࣬��ʱ����Ҫͨ������ָ����ǰʹ����һ�ף�
	/// </summary>
	class DMRegTypeItem:public DMArrayT<IDMRegPtr>
	{
	public:
		DMRegTypeItem();
		virtual ~DMRegTypeItem();

	public:// �������غ���

		void PreArrayObjRemove(const IDMRegPtr &obj);
	    bool EqualArrayObj(const IDMRegPtr &objsrc, const IDMRegPtr &objdest);

	public:
		CStringW                    m_DefRegName;   ///< ����Ĭ��ע����������
	};

	/// <summary>
	///		��<see cref="DMREGTYPE"/>����������е�ע����
	/// </summary>
	class DMRegMgr
	{
	public:
		DMRegMgr();
		~DMRegMgr();
	public:
		DMCode Register(IDMReg &RegObj, bool bReplace=false);
		DMCode CreateRegObj(void** ppObj, LPCWSTR lpszClassName,int RegType);
		DMCode UnRegister(LPCWSTR lpszClassName,int RegType);
		DMCode SetDefRegObj(LPCWSTR lpszClassName,int RegType);
		DMCode GetDefRegObj(CStringW &szName,int RegType);

	public:// ����
		DMCode RegisterByType(DMRegTypeItem &RtItem, IDMReg &RegObj, bool bReplace);
		DMCode CreateRegObjByType(DMRegTypeItem &RtItem, void** ppObj, LPCWSTR lpszClassName);
		DMCode UnRegisterByType(DMRegTypeItem &RtItem, LPCWSTR lpszClassName);
		DMCode SetDefRegObjByType(DMRegTypeItem &RtItem, LPCWSTR lpszClassName);

	public:
		DMRegTypeItem						m_RtSkin;
		DMRegTypeItem                       m_RtStyle;
		DMRegTypeItem                       m_RtAttribute;
		DMRegTypeItem                       m_RtWindow;
		DMRegTypeItem                       m_RtLayout;
		DMRegTypeItem                       m_RtImgDecoder;
		DMRegTypeItem                       m_RtRes;
		DMRegTypeItem                       m_RtRender;
		DMRegTypeItem                       m_RtDraw;
		DMRegTypeItem                       m_RtLog;
		DMRegTypeItem                       m_RtFlowLayout;
		DMRegTypeItem                       m_RtAnimate;
		DMRegTypeItem                       m_RtToolTip;
		DMRegTypeItem                       m_RtScript;
		DMRegTypeItem                       m_RtTrans;
		DMRegTypeItem                       m_RtTaskRunner;

	};

}//namespace DM