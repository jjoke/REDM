//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DUIStylePool.h 
// File Des:  ��������style,��skin��һ�¹���
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-30	1.0			
//-------------------------------------------------------
#pragma once

namespace DM
{
	/// <summary>
	///		Style�ĳض���,����֧�־ֲ�Style
	/// </summary>
	class DMStylePoolItem:public DMRefNum, public DMMapT<CStringW,DMXmlNode>
	{
	public:
		DMStylePoolItem(CStringW strName,DMXmlNode &xmlNodes);

	public:
		void AddStyles(DMXmlNode &XmlStyles);
		DMXmlNode GetStyle(CStringW strId);

	public:
		DMXmlDocument               m_Doc;
		CStringW                    m_strName;
	};
	typedef DMStylePoolItem* DMStylePoolItemPtr; 

	/// <summary>
	///		����Style�ĳ��б�
	/// </summary>
	/// <remarks>
	///		���ó��б�ĺô��ǿ����Ƴ�ĳЩ�ֲ��ĳ�,��ĳ��Style�������ж���ֻ��ĳ�����ڣ����������ٺ󣬾Ϳ��Կ��ǰ�������Ƴ�
	/// </remarks>
	class DM_EXPORT DUIStylePool:public DMMapT<CStringW, DMStylePoolItemPtr>
	{
	public:
		~DUIStylePool();
	public:
		/// -------------------------------------------------
		/// @brief  ����һ��style�أ���style���Ѵ���,������������
		/// @param[in]  XmlNode		xml�ڵ�
		/// @return  DMCode
		DMCode AddStylePoolItem(DMXmlNode &XmlNode);

		/// -------------------------------------------------
		/// @brief  �Ƴ�һ��style��
		/// @param[in]  lpszName	style�ص�����
		/// @return  DMCode
		DMCode RemoveStylePoolItem(LPCWSTR lpszName);
	
		/// -------------------------------------------------
		/// @brief  �Ƴ����е�style��
		/// @return  DMCode
		DMCode RemoveAllStylePoolItem();

		/// -------------------------------------------------
		/// @brief  ����style
		/// @param[in]  lpszKey			���ڲ���style��key
		/// @param[in]  lpszName		���ڲ���style�ص�name
		/// @param[in]  bLoopFind		�Ƿ�������гز���
		/// @remark Ĭ������lpszName��style�����ң�����Ҳ���,����bLoopFindΪ�棬��ȫ��������
		/// @return style��xmlnode
		DMXmlNode FindStyle(LPCWSTR lpszKey,LPCWSTR lpszName,bool bLoopFind = true);

		/// -------------------------------------------------
		/// @brief   ����style
		/// @param[in]  lpszBuf			style�ص�����:style��key
		/// @return style��xmlnode
		DMXmlNode FindStyle(LPCWSTR lpszBuf,bool bLoopFind = true);

		/// -------------------------------------------------
		/// @brief  ȫ�������Ҳ���style
		/// @param[in]  lpszKey			���ڲ���style��key
		/// @return style��xmlnode
		DMXmlNode FindStyleFromAll(LPCWSTR lpszKey);

	public:
		virtual void PreMapKeyRemove(const DMStylePoolItemPtr &obj);

	};


}//namespace DM