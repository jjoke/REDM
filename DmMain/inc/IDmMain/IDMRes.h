//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: IDMRes.h 
// File Des:
// File Summary: 
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
	///		��Դ���������չ�ӿ�,classtype=<see cref="DMREG_Res"/>
	/// </summary>
	class DM_EXPORT IDMRes:public DMBase
	{
		DMDECLARE_CLASS_NAME(IDMRes,L"IDMRes",DMREG_Res);
	public:
		/// -------------------------------------------------
		/// @brief ������Դ��չ�ӿ�
		/// @param[in]		 wp     �����ڲ�ʹ�õĲ���1������Դ·���ȣ����Լ���չʵ�����
		/// @param[in]		 lp     �����ڲ�ʹ�õĲ���2������Դ·���ȣ����Լ���չʵ�����
		/// @remark 
		/// @return DM_ECODE_OKΪ�ɹ�
		virtual DMCode LoadResPack(WPARAM wp, LPARAM lp) = 0;

		/// -------------------------------------------------
		/// @brief �ж���Դ��ĳ���Ƿ������չ�ӿ�
		/// @param[in]		 lpszType    �����ڲ�ʹ�õĲ���1��һ��Ϊ�����ͣ����Լ���չʵ�����
		/// @param[in]		 lpszName    �����ڲ�ʹ�õĲ���2��һ��Ϊ�����ƣ����Լ���չʵ�����
		/// @param[in]		 lpszThemeName     �����������ΪNULL����ʹ�õ�ǰ����������Լ���չʵ�����
		/// @remark 
		/// @return DM_ECODE_OKΪ�ɹ�
		virtual DMCode IsItemExists(LPCWSTR lpszType, LPCWSTR lpszName,LPCWSTR lpszThemeName=NULL) = 0;

		/// -------------------------------------------------
		/// @brief ��ȡ ��Դ��ĳ����ڴ��С
		/// @param[in]		 lpszType    �����ڲ�ʹ�õĲ���1��һ��Ϊ�����ͣ����Լ���չʵ�����
		/// @param[in]		 lpszName    �����ڲ�ʹ�õĲ���2��һ��Ϊ�����ƣ����Լ���չʵ�����
		/// @param[out]		 ulSize		 ��ȡ�ڴ��С
		/// @param[in]		 lpszThemeName     �����������ΪNULL����ʹ�õ�ǰ����������Լ���չʵ�����
		/// @remark DMMain�����Ȼ�ȡ��С���ٷ����С���ٿ����ڴ�Ĳ���
		/// @return DM_ECODE_OKΪ�ɹ�
		virtual DMCode GetItemSize(LPCWSTR lpszType, LPCWSTR lpszName, unsigned long& ulSize,LPCWSTR lpszThemeName=NULL) = 0;

		/// -------------------------------------------------
		/// @brief ���� ��Դ��ĳ����ڴ�
		/// @param[in]		 lpszType    �����ڲ�ʹ�õĲ���1��һ��Ϊ�����ͣ����Լ���չʵ�����
		/// @param[in]		 lpszName    �����ڲ�ʹ�õĲ���2��һ��Ϊ�����ƣ����Լ���չʵ�����
		/// @param[in]		 lpBuf		 �ⲿ�����ڴ�ָ��
		/// @param[in]		 ulSize		 �ⲿ�����ڴ��С
			/// @param[in]		 lpszThemeName     �����������ΪNULL����ʹ�õ�ǰ����������Լ���չʵ�����
		/// @remark DMMain�����Ȼ�ȡ��С���ٷ����С���ٿ����ڴ�Ĳ��������<see cref="GetItemSize"/>
		/// @return DM_ECODE_OKΪ�ɹ�
		virtual DMCode GetItemBuf(LPCWSTR lpszType, LPCWSTR lpszName, LPVOID lpBuf, unsigned long ulSize,LPCWSTR lpszThemeName=NULL) = 0;

		/// -------------------------------------------------
		/// @brief ���������
		/// @param[in]		 wp     �����ڲ�ʹ�õĲ���1������Դ·���ȣ����Լ���չʵ�����
		/// @param[in]		 lp     �����ڲ�ʹ�õĲ���2������Դ·���ȣ����Լ���չʵ�����
		/// @remark �˺��������ڴ��ⲿ��̬������������ؽ�ȥ
		/// @return DM_ECODE_OKΪ�ɹ�
		virtual DMCode LoadTheme(WPARAM wp, LPARAM lp) = 0;

		/// -------------------------------------------------
		/// @brief ���õ�ǰ�����
		/// @param[in]		 lpszName     ���������
		/// @param[in]		 lpszOldName  ��ǰʹ�õ���������� �����ⲿ�����㹻��buf
		/// @remark Ĭ�ϻ�ʹ������ΪDefault�������
		/// @return DM_ECODE_OKΪ�ɹ�
		virtual DMCode SetCurTheme(LPCWSTR lpszName, LPCWSTR lpszOldName=NULL) = 0;
	};

}//namespace DM