//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DUISkinPool.h 
// File Des:  ��������skin
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
	///		Skin�ĳض���,����֧�־ֲ�skin
	/// </summary>
	class DMSkinPoolItem:public DMRefNum,public DMMapT<CStringW,IDMSkinPtr>
	{
	public:
		virtual ~DMSkinPoolItem();

	public:// �������غ���
	   void PreMapKeyRemove(const IDMSkinPtr &obj);
	};
	typedef DMSkinPoolItem* DMSkinPoolItemPtr; 

	/// <summary>
	///		����Skin�ĳ��б�
	/// </summary>
	/// <remarks>
	///		���ó��б�ĺô��ǿ����Ƴ�ĳЩ�ֲ��ĳ�,��ĳ��skin�������ж���ֻ��ĳ�����ڣ����������ٺ󣬾Ϳ��Կ��ǰ�������Ƴ�
	/// </remarks>
	class DM_EXPORT DUISkinPool:public DMMapT<CStringW, DMSkinPoolItemPtr>
	{
	public:
		~DUISkinPool();
	public:
		/// -------------------------------------------------
		/// @brief  ����һ��skin�أ���skin���Ѵ���,������������
		/// @param[in]  XmlNode		xml�ڵ�
		/// @return  DMCode
		DMCode AddSkinPoolItem(DMXmlNode &XmlNode);
		
		/// -------------------------------------------------
		/// @brief  �Ƴ�һ��skin�أ���skin���Ѵ���,������������
		/// @param[in]  lpszName	skin�ص�����
		/// @return  DMCode
		DMCode RemoveSkinPoolItem(LPCWSTR lpszName);

		/// -------------------------------------------------
		/// @brief  ɾ�����е�skin�أ�����ָ����key����
		/// @param[in]  lpszName			���ų���skin�ص�����
		/// @return DMCode
		DMCode RemoveAllSkinPoolItemExcept(LPCWSTR lpszName);
		
		/// -------------------------------------------------
		/// @brief  ���ڻ���
		/// @param[in]  wp		��Ҫ���µ�res�ַ�������;�ֿ�
		/// @param[in]  lp		��Ҫ���µ�res�ַ�������
		/// @return  DMCode
		DMCode UpdateSkin(WPARAM wp, LPARAM lp);
		bool   IsNeedUpdateSkin(IDMSkinPtr pSkin);  ///< ��ǰskinָ���Ƿ���Ҫ����
		DMCode ClearUpdateSkinArray();				///< �������µ�skin�б� 

		/// -------------------------------------------------
		/// @brief			��ָ��buf���õ�skin����
		/// @param[in]		pBuf				ͼƬ�ڴ�
		/// @param[in]		bufLen				ͼƬ�ڴ��С
		/// @param[in]		pszType				ͼƬ���ͣ�һ��Ĭ��Ϊpng
		/// @param[in]		lpszXml				����skin��xml
		/// @param[in]		lpszPoolName		skin������
		DMCode AddSkin(void *pBuf,size_t bufLen,LPCWSTR pszType,
			LPCWSTR lpszXml,LPCWSTR lpszPoolName=NULL);

		/// -------------------------------------------------
		/// @brief  �Ƴ�skin
		/// @param[in]  lpszKey			���ڲ���skin��key
		/// @param[in]  lpszName		���ڲ���skin�ص�name
		/// @remark Ĭ������lpszName��skin�����Ƴ�������Ҳ���,����bLoopFindΪ�棬��ȫ�������ҵ����Ƴ�
		/// @return ��skin�����Ƴ�skin,�������ü�����1
		DMCode RemoveSkin(LPCWSTR lpszKey,LPCWSTR lpszName,bool bLoopFind = true);

		/// -------------------------------------------------
		/// @brief  ȫ������ɾ��skin
		/// @param[in]  lpszKey			���ڲ���skin��key
		/// @return IDMSkinPtr��ΪNULL��ʾʧ��
		DMCode RemoveSkinFromAll(LPCWSTR lpszKey);

		/// -------------------------------------------------
		/// @brief  ����skin
		/// @param[in]  lpszKey			���ڲ���skin��key
		/// @param[in]  lpszName		���ڲ���skin�ص�name
		/// @remark Ĭ������lpszName��skin�����ң�����Ҳ���,����bLoopFindΪ�棬��ȫ��������
		/// @return IDMSkinPtr��ΪNULL��ʾʧ��
		IDMSkinPtr FindSkin(LPCWSTR lpszKey,LPCWSTR lpszName,bool bLoopFind = true);

		/// -------------------------------------------------
		/// @brief  �Ҳ���skin
		/// @param[in]  lpszBuf			skin�ص�����:skin��key
		/// @return IDMSkinPtr��ΪNULL��ʾʧ��
		IDMSkinPtr FindSkin(LPCWSTR lpszBuf,bool bLoopFind = true);

		/// -------------------------------------------------
		/// @brief  ȫ�������Ҳ���skin
		/// @param[in]  lpszKey			���ڲ���skin��key
		/// @return IDMSkinPtr��ΪNULL��ʾʧ��
		IDMSkinPtr FindSkinFromAll(LPCWSTR lpszKey);

	public:
		virtual void PreMapKeyRemove(const DMSkinPoolItemPtr &obj);

	public:// ����Ƥ���б�
		CArray<IDMSkinPtr>			m_UpdateSkinArray;							///< Ŀǰ����skin����ʹ�ã�������չ��һ����
	};


}//namespace DM