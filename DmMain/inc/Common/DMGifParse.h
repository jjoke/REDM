//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMGifParse.h 
// File Des: ����GIF89a������ʽ����������wic��xp���޷��������ӳ�ʱ�䣬���Լ���˹��ܣ�������ʵ�����ؽ���,���˲���֤��������׼ȷ����ͨ��gtest����
// File Summary: �ο��ṹ:http://blog.csdn.net/friendwaters/article/details/2737328 & gif�ٷ�89a�ĵ�
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-21	1.0			
//-------------------------------------------------------
#pragma once

namespace DM
{
	typedef struct               //ͼ����չ����
	{   
		bool active;             //���ṹ�е����������Ƿ����
		bool userInputFlag;      //�Ƿ��ڴ��û�����
		bool trsFlag;            //�Ƿ���͸��ɫ
		WORD delayTime;          //��ʱʱ�䣨��λ1/100�룩
		UINT disposalMethod;     //����������gif89a.doc���ɺ��ԣ�
		UINT trsColorIndex;      //͸��ɫ��ɫ������
	}GCTRLEXT;

	typedef struct                //GIF�ļ���ȫ�ֲ���
	{  
		UINT frames;             //�ļ���ͼ��֡��
		WORD scrWidth,scrHeight; //�߼���Ļ�Ŀ�Ⱥ͸߶ȣ���λ���أ�
		bool gFlag;              //�Ƿ���ȫ�ֵ�ɫ�壨����������ɫ������Ƿ���Ч��
		UINT colorRes;           //ɫ�ʷֱ��ʣ���ʹ�ã�
		bool gSort;              //ȫ�ֵ�ɫ���Ƿ���������
		UINT gSize;              //ȫ�ֵ�ɫ���С���ж��ٸ�ʵ����ڣ�
		UINT BKColorIdx;         //����ɫ�ĵ�ɫ������
		UINT pixelAspectRatio;   //���س������
		UINT totalLoopCount;     //loop����,0��ʾ����
		bool bLoop;              //�Ƿ����loop��Ϣ��û�о���һ��
		//BYTE *gColorTable;     //ָ��ȫ�ֵ�ɫ���ָ�루256����ڣ�ÿ��������ֽڣ�
		//��ɫ���ʽ��ο�gif89a.doc
	}GIFGLOBALINFO;
	typedef GIFGLOBALINFO *LPGLOBAL_INFO;

	typedef struct  
	{
		WORD imageLPos;          //ͼ������ص��߼���Ļ�ľ��루��λ���أ�
		WORD imageTPos;          //ͼ���ϱ��ص��߼���Ļ�ľ��루��λ���أ�
		WORD imageWidth;         //ͼ��Ŀ�ȣ���λ���أ�
		WORD imageHeight;        //ͼ��ĸ߶ȣ���λ���أ�
		GCTRLEXT ctrlExt;        //ͼ����չ��������͸�������Ͷ����йأ�
	}GIFFRAME,*GIFFRAMEPTR;

	/// <summary>
	/// ����gif����Ҫ�ǻ�ȡXP�µ��ӳ�ʱ�䣬xp��ʹ��wic�ɻ��֡�����޷�ȡ���ӳ�ʱ��
	/// </summary>
	class DM_EXPORT DMGifParse:public DMRefNum
							  ,public DMArrayT<GIFFRAMEPTR>
	{
	public:
		DMGifParse();
		virtual~DMGifParse();

	public:
		/// -------------------------------------------------
		/// @brief ���ļ��н���gif
		/// @param[in]		 lpszFilePath    gif��·��
		/// @return true:�����ɹ�
		bool LoadFromFile(LPCWSTR lpszFilePath);

		/// -------------------------------------------------
		/// @brief ���ļ��н���gif
		/// @param[in]		 pBuf			gif��buf��ʼ
		/// @param[in]		 bufLen			gif��buf��С
		/// @return true:�����ɹ�
		bool LoadFromMemory(BYTE *pBuf,int bufLen);

		/// -------------------------------------------------
		/// @brief ȡ��ָ��֡
		/// @param[in]		 iElement		ָ��֡��
		/// @return ʧ�ܷ���null
		GIFFRAMEPTR GetFrame(int iElement);

		/// -------------------------------------------------
		/// @brief ȡ��ȫ��ֵ��ȫ��ֵ������ͼ��֡����ѭ��������
		/// @return 
		LPGLOBAL_INFO GetGlobalInfo(){return &m_gInfo;}

	public:// ����
		bool GetAllFrames(FILE*fp);
		bool ParseExtension(FILE*fp,GCTRLEXT&ctrlExt);
		bool ParseFrame(FILE*fp);
		
		bool GetAllFrames(BYTE *pBuf,int bufLen);
		bool ParseExtension(BYTE *pBuf,int bufLen,GCTRLEXT&ctrlExt);
		bool ParseFrame(BYTE *pBuf,int bufLen);

	public:
		virtual void PreArrayObjRemove(const GIFFRAMEPTR &obj);
	private:
		int                 m_nOffset;              ///< �����ڴ����ȫ��
		GIFGLOBALINFO		m_gInfo;				///< GIF�ļ���ȫ�ֲ���
		GCTRLEXT		    m_ctrlExt;				///< ͼ����չ��������������ʱ��ʱʹ�ã�
	};

}//namespace DM
