//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: IDMImgDecoder.h 
// File Des:
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-20	1.0			
//-------------------------------------------------------
#pragma once

namespace DM
{
	/// <summary>
	///		�ο�WIC��ͼƬ���������ж�֡(Frame)
	/// <summary>
	class IDMImgFrame:public DMRefNum
	{
	public:
		virtual DMCode GetSize(UINT &ulWid,UINT &ulHei) = 0;		///< ֡��С
		virtual DMCode SetDelay(UINT ulDelay) = 0;					///< ����֡�ӳ�
		virtual DMCode GetDelay(UINT &ulDelay) = 0;				    ///< ֡�ӳ�,���GIF�ȶ�֡

		/// -------------------------------------------------
		/// @brief			 ������������
		/// @param[int]		 cbStride  ��32λDIB��Ϊ��ҳ,�������ǿ�*4
		/// @param[int]		 lpRect    Ҫ���ƵĴ�С,ΪNULL��ʾ������֡
		/// @return DM_ECODE_OKΪ�ɹ�
		virtual DMCode CopyPixels(LPVOID lpBuf, UINT ulSize,UINT cbStride,const RECT *lpRect=NULL) = 0;
	};

	/// <summary>
	///		��Դ���������չ�ӿ�,classtype=<see cref="DMREG_ImgDecoder"/>
	/// </summary>
	class IDMImgDecoder:public DMBase
	{
		DMDECLARE_CLASS_NAME(IDMImgDecoder,L"IDMImgDecoder",DMREG_ImgDecoder);
	public:
		virtual ~IDMImgDecoder(){};

		virtual DMCode LoadFromMemory(void *pBuf,size_t bufLen) = 0;		///< ���ڴ��м���
		virtual DMCode LoadFromFile(LPCWSTR pszFileName) = 0;				///< ���ļ��м���
		virtual DMCode GetFrameCount(UINT &ulCount) = 0;					///< ��õ�ǰ�洢֡����Ŀ

		/// -------------------------------------------------
		/// @brief ����ͼƬ�����Ķ�֡ѭ������
		/// @param[out]		 ulCount    ͼƬ�����Ķ�֡ѭ������(-1��ʾ��Զѭ��)
		/// @remark ��GIF���߼�,����״̬��1.û��ѭ����Ϣ��1�Σ� 2.��ѭ����Ϣ��������3.��ѭ����Ϣ��0�α�ʾ��Զѭ����
		/// @return DM_ECODE_OKΪ�ɹ�
		virtual DMCode GetTotalLoopCount(UINT &ulCount) = 0;	

		/// -------------------------------------------------
		/// @brief ����֡����
		/// @param[in]  iFrame		Ҫ��ȡ��֡index
		/// @param[out] ppFrame		Ҫ��ȡ��֡
		/// @remark �ڲ����Լ��������ü���,�ⲿ����ʹ������ָ��
		/// @return DM_ECODE_OKΪ�ɹ�
		virtual DMCode GetFrame(UINT iFrame, IDMImgFrame**ppFrame) = 0;   
	};

}//namespace DM