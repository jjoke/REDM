// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	IDMTrans.h
// File mark:   
// File summary:������ӿ�
// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2016-11-21
// ----------------------------------------------------------------
#pragma once

namespace DM
{
	/// <summary>
	///		�����������չ�ӿ�,classtype=<see cref="DMREG_Trans"/>
	/// </summary>
	class DM_EXPORT IDMTrans : public DMBase
	{
		DMDECLARE_CLASS_NAME(IDMTrans,L"IDMTrans",DMREG_Trans);
	public:
		/// -------------------------------------------------
		/// @brief ���ط������չ�ӿ�
		/// @param[in]		 wp					�����ڲ�ʹ�õĲ���1���緭��XML·���ȣ����Լ���չʵ����أ�����Ϊxml��ld��xmlȫ·��
		/// @param[in]		 lp					�����ڲ�ʹ�õĲ���2���緭��XML�ȣ����Լ���չʵ�����,����0��ʾxml id��ʽ,1��ʾxml�����exe��·��
		/// @return DM_ECODE_OKΪ�ɹ�
		virtual DMCode LoadTrans(WPARAM wp, LPARAM lp = 0) = 0;

		/// -------------------------------------------------
		/// @brief ����Ĭ�����԰�
		// @param[in]		 strLanguageName	��Ӧ�����԰�Ψһ��ʶ�������NULL,��ʹ�÷��� 
		/// @return DM_ECODE_OKΪ�ɹ�
		virtual DMCode SetTrans(CStringW strLanguageName) = 0;

		/// -------------------------------------------------
		/// @brief �¼ӷ����ַ���
		/// @param[in]		 strSrc				XML�����õ��ַ���
		/// @param[in]		 strTrans			��������ַ���
		/// @param[in]		 strNodeName		�Ƿ�ָ��Ϊ�ض�������,ΪNULL��ʾ��ͨ�õ������в���
		/// @param[in]		 strLanguageName	��Ӧ�����԰�Ψһ��ʶ,ΪNULLʹ�õ�ǰSetTransָ�������԰�
		/// @return DM_ECODE_OKΪ�ɹ�
		virtual DMCode AddTransItem(CStringW strSrc, CStringW strTrans,CStringW strNodeName = L"",CStringW strLanguageName = L"") = 0;
		
		/// -------------------------------------------------
		/// @brief ��÷����ַ���
		/// @param[in]		 strSrc				XML�����õ��ַ���
		/// @param[in]		 strNodeName		�Ƿ�ָ��Ϊ�ض�������
		/// @param[in]		 strLanguageName	��Ӧ�����԰�Ψһ��ʶ,ΪNULLʹ�õ�ǰSetTransָ�������԰�
		/// @return ת������ַ���
		virtual CStringW GetTrans(CStringW strSrc,CStringW strNodeName = L"",CStringW strLanguageName = L"") = 0;
	};
}