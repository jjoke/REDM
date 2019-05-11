#include "DmMainAfx.h"
#include "DMGifParse.h"

namespace DM
{
	DMGifParse::DMGifParse()
	{
		m_nOffset = 0;
		memset(&m_ctrlExt,0,sizeof(GCTRLEXT));
		memset(&m_gInfo,0,sizeof(GIFGLOBALINFO));
	}

	DMGifParse::~DMGifParse()
	{	
		RemoveAll();
	}

	bool DMGifParse::LoadFromFile(LPCWSTR lpszFilePath)
	{
		bool bRet = false;
		FILE *fp = NULL;
		do 
		{
			_wfopen_s(&fp, lpszFilePath, L"rb");
			if (!fp)
			{
				break;
			}

			/// ͷ��(6���ֽ�)
			char szSignature[7] = {0};
			fread(szSignature,1,6, fp);						// ��ʶ��(3 �ֽ�) ---GIF
			if (0 != strncmp(szSignature,"GIF89a",6))		// �汾(3 �ֽ�)  89a-����ֻ֧��89�汾��hgy note
			{
				break;
			}

			fread((char*)&m_gInfo.scrWidth,1,2, fp);		// �߼���Ļ��(2�ֽ�)
			fread((char*)&m_gInfo.scrHeight,1,2, fp);		// �߼���Ļ��(2�ֽ�)

			BYTE be;
			fread((char*)&be,1,1,fp);						// Packed Fields, Global Color Table Flag(1�ֽ�)
			if ((be&0x80) != 0)
			{
				m_gInfo.gFlag = true;
			}
			else
			{
				m_gInfo.gFlag = false;
			}
			m_gInfo.colorRes = ((be&0x70)>>4)+1;			// ɫ�ʷֱ���
			if (m_gInfo.gFlag)
			{	
				if((be&0x08) != 0)
					m_gInfo.gSort = true;					// ȫ�ֵ�ɫ���Ƿ���������
				else
					m_gInfo.gSort = false;			
				m_gInfo.gSize = 1;
				m_gInfo.gSize <<= ((be&0x07)+1);
			}
			fread((char*)&be,1,1,fp);
			m_gInfo.BKColorIdx = be;						// Background Color Index����ɫ�ĵ�ɫ������(1�ֽ�)
			fread((char*)&be,1,1,fp);				
			m_gInfo.pixelAspectRatio = be;					// Pixel Aspect Ratio���س������(1�ֽ�)

			// �����ȫ��ɫ�������߼�����������֮��ռ�õ��ֽ���Ϊ3*2^��ȫ��ɫ��ߴ�+1��
			if (m_gInfo.gFlag)
			{	
				fseek(fp, m_gInfo.gSize*3,SEEK_CUR);
			}

			bRet = GetAllFrames(fp);
			if (bRet)
			{
				m_gInfo.frames = (UINT)GetCount();
			}
		} while (false);
		if (fp)
		{
			fclose(fp);
		}
		return bRet;
	}

	bool DMGifParse::LoadFromMemory(BYTE *pBuf,int bufLen)
	{
		bool bRet = false;
		do 
		{
			m_nOffset = 0;
			if (NULL == pBuf||bufLen<=380)
			{
				break;
			}

			/// ͷ��(6���ֽ�)
			if (0 != strncmp((char*)pBuf+m_nOffset,"GIF89a",6))
			{
				break;
			}
			m_nOffset += 6;

			memcpy((void*)&m_gInfo.scrWidth, pBuf+m_nOffset,2);m_nOffset+=2;	// �߼���Ļ��(2�ֽ�)
			memcpy((char*)&m_gInfo.scrHeight, pBuf+m_nOffset,2);m_nOffset+=2;	// �߼���Ļ��(2�ֽ�)

			BYTE be;
			memcpy((char*)&be, pBuf+m_nOffset,1);m_nOffset+=1;					// Packed Fields, Global Color Table Flag(1�ֽ�)
			if ((be&0x80) != 0)
			{
				m_gInfo.gFlag = true;
			}
			else
			{
				m_gInfo.gFlag = false;
			}
			m_gInfo.colorRes = ((be&0x70)>>4)+1;								// ɫ�ʷֱ��ʣ���ʹ�ã�
			if (m_gInfo.gFlag)
			{	
				if((be&0x08) != 0)
					m_gInfo.gSort = true;										// ȫ�ֵ�ɫ���Ƿ���������
				else
					m_gInfo.gSort = false;			
				m_gInfo.gSize = 1;
				m_gInfo.gSize <<= ((be&0x07)+1);
			}
			memcpy((char*)&be, pBuf+m_nOffset,1);m_nOffset+=1;
			m_gInfo.BKColorIdx = be;											// Background Color Index����ɫ�ĵ�ɫ������(1�ֽ�)
			//fread((char*)&be,1,1,fp);		
			memcpy((char*)&be, pBuf+m_nOffset,1);m_nOffset+=1;
			m_gInfo.pixelAspectRatio = be;										// Pixel Aspect Ratio���س������(1�ֽ�)

			// �����ȫ��ɫ�������߼�����������֮��ռ�õ��ֽ���Ϊ3*2^��ȫ��ɫ��ߴ�+1��
			if (m_gInfo.gFlag)
			{	
				m_nOffset+=m_gInfo.gSize*3;
			}

			bRet = GetAllFrames(pBuf,bufLen);
			if (bRet)
			{
				m_gInfo.frames = (UINT)GetCount();
			}
		} while (false);
		return bRet;
	}

	GIFFRAMEPTR DMGifParse::GetFrame(int iElement)
	{
		GIFFRAMEPTR pf = NULL;
		GetObj(iElement,pf);
		return pf;
	}

	bool DMGifParse::GetAllFrames(FILE*fp)
	{	
		bool bRet = true;
		BYTE be;
		bool fileEnd = false;			// β��¼,����ָʾ���������Ľ�����ȡ�̶�ֵ0x3b.
		while (!feof(fp)&&!fileEnd)
		{
			fread((char*)&be,1,1,fp);	//(1�ֽ�)
			switch (be)
			{	
			case 0x21:					// Extension Introducer - ��ʶ����һ����չ�飬�̶�ֵ0��21,���Ǹ����п��޵Ŀ飬�еĻ���������
				{
					if (!ParseExtension(fp, m_ctrlExt))
					{
						break;
					}
				}
				break;
			case 0x2c:				   // ͼ��ָ��� - ����ʶ��ͼ���������Ŀ�ʼ��ȡ�̶�ֵ0x2c
				{
					if (!ParseFrame(fp))
					{
						break;
					}
				}
				break;

			case 0x3b:				  // β��¼,����ָʾ���������Ľ�����ȡ�̶�ֵ0x3b.
				{
					fileEnd = true;
				}
				break;

			case 0x00:
				break;

			default:
				{
					bRet = false;
				}
				break;
			}
		}
		return bRet;
	}


	bool DMGifParse::ParseExtension(FILE*fp,GCTRLEXT&ctrlExt)
	{
		bool bRet = true;
		BYTE be;
		fread((char*)&be,1,1,fp);//(1�ֽ�)
		switch (be)
		{	
		case 0xf9:// Graphic Control Label - ��ʶ����һ��ͼ�ο�����չ�飬�̶�ֵ0xF9
			{
				while (!feof(fp))
				{	
					fread((char*)&be,1,1,fp);
					if (0 == be)// ���սᣬ�̶�ֵ0
						break;
					if (4 == be)// Block Size - ���������ս������̶�ֵ4
					{
						ctrlExt.active = true;
						fread((char*)&be,1,1,fp);
						ctrlExt.disposalMethod = (be&0x1c)>>2;
						if ((be&0x02) != 0)
							ctrlExt.userInputFlag = true;
						else
							ctrlExt.userInputFlag = false;
						if((be&0x01) != 0)
							ctrlExt.trsFlag = true;
						else
							ctrlExt.trsFlag = false;
						fread((char*)&ctrlExt.delayTime,1,2,fp);//Delay Time - ��λ1/100��(2�ֽڣ�
						fread((char*)&be,1,1,fp);
						ctrlExt.trsColorIndex = be;
					}
					else
						fseek(fp, be, SEEK_CUR);// ����be���ֽ�
				}
			}
			break;
		case 0xfe:// Comment Label - ��ʶ����һ��ע�Ϳ飬�̶�ֵ0xFE
		case 0x01:
		case 0xff:// Application Extension Label - ��ʶ����һ��Ӧ�ó�����չ�飬�̶�ֵ0xFF
			{
				if (false == m_gInfo.bLoop)
				{
					char byChar[17] = {0x0B,'N','E','T','S','C','A','P','E','2','.','0',0x03,0x01,0x00,0x00,0x00};
					DWORD pos = ftell(fp);
					char byChar1[17]= {0};
					fread(byChar1,1,17,fp);
					if (0 == strncmp(byChar1,byChar,14))
					{	
						int iHigh = (int)(byte)byChar1[15];int iLow = (int)(byte)byChar1[14];
						m_gInfo.totalLoopCount = iLow+iHigh*256;
						m_gInfo.bLoop = true;
					}
					fseek(fp, pos, SEEK_SET);
				}
			
				while (!feof(fp)) // ����������һ�飬���ն����и����սᣬ�̶�ֵ0
				{	
					fread((char*)&be,1,1,fp);
					if (0 == be)// ���սᣬ�̶�ֵ0
						break;
					fseek(fp, be, SEEK_CUR);// ����be���ֽ�
				}
			}
			break;
		default:
			bRet = false;
			break;
		}
		return bRet;
	}

	bool DMGifParse::ParseFrame(FILE*fp)
	{
		GIFFRAMEPTR pf = new GIFFRAME;
		memset(pf, 0,sizeof(GIFFRAME));

		fread((char*)&pf->imageLPos,1,2,fp);
		fread((char*)&pf->imageTPos,1,2,fp);
		fread((char*)&pf->imageWidth,1,2,fp);
		fread((char*)&pf->imageHeight,1,2,fp);

		BYTE be;
		UINT lSize = 1;
		bool lFlag = false;
		fread((char*)&be,1,1,fp);
		if ((be&0x80) != 0)
			lFlag = true;
		lSize <<= ((be&0x07)+1);// ��ɫ�б��λ��
		if (lFlag)
			fseek(fp,lSize*3,SEEK_CUR);
		fread((char*)&be,1,1,fp);
		while (!feof(fp))
		{	
			fread((char*)&be,1,1,fp);
			if (0 == be)
				break;
			fseek(fp, be, SEEK_CUR);// ����be���ֽ�
		}

		if(m_ctrlExt.active)
		{
			pf->ctrlExt = m_ctrlExt;
			m_ctrlExt.active = false;
		}

		AddObj(pf);
		return true;
	}

#define CMPLEN(x,y)  if(x>y){return false;}
	bool DMGifParse::GetAllFrames(BYTE *pBuf,int bufLen)
	{
		bool bRet = true;
		BYTE be;
		bool fileEnd = false;// β��¼,����ָʾ���������Ľ�����ȡ�̶�ֵ0x3b.
		while (m_nOffset<=bufLen&&!fileEnd)
		{
			memcpy((char*)&be,pBuf+m_nOffset,1);m_nOffset+=1;//(1�ֽ�)
			switch (be)
			{	
			case 0x21:			// Extension Introducer - ��ʶ����һ����չ�飬�̶�ֵ0��21,���Ǹ����п��޵Ŀ飬�еĻ���������
				{
					if (!ParseExtension(pBuf,bufLen, m_ctrlExt))
					{
						break;
					}
				}
				break;
			case 0x2c:         // ͼ��ָ��� - ����ʶ��ͼ���������Ŀ�ʼ��ȡ�̶�ֵ0x2c
				{
					if (!ParseFrame(pBuf,bufLen))
					{
						break;
					}
				}
				break;

			case 0x3b:		 // β��¼,����ָʾ���������Ľ�����ȡ�̶�ֵ0x3b.
				{
					fileEnd = true;
				}
				break;

			case 0x00:
				break;

			default:
				{
					bRet = false;
				}
				break;
			}
		}
		return bRet;
	}

	bool DMGifParse::ParseExtension(BYTE *pBuf,int bufLen,GCTRLEXT&ctrlExt)
	{
		bool bRet = true;
		BYTE be;
		memcpy((char*)&be,pBuf+m_nOffset,1);m_nOffset+=1;CMPLEN(m_nOffset,bufLen);//(1�ֽ�)
		switch (be)
		{	
		case 0xf9:// Graphic Control Label - ��ʶ����һ��ͼ�ο�����չ�飬�̶�ֵ0xF9
			{
				while (m_nOffset<=bufLen)
				{	
					memcpy((char*)&be,pBuf+m_nOffset,1);m_nOffset+=1;
					if (0 == be)// ���սᣬ�̶�ֵ0
						break;
					if (4 == be)// Block Size - ���������ս������̶�ֵ4
					{
						ctrlExt.active = true;
						memcpy((char*)&be,pBuf+m_nOffset,1);m_nOffset+=1;CMPLEN(m_nOffset,bufLen);;
						ctrlExt.disposalMethod = (be&0x1c)>>2;
						if ((be&0x02) != 0)
							ctrlExt.userInputFlag = true;
						else
							ctrlExt.userInputFlag = false;
						if((be&0x01) != 0)
							ctrlExt.trsFlag = true;
						else
							ctrlExt.trsFlag = false;
						memcpy((char*)&ctrlExt.delayTime,pBuf+m_nOffset,2);m_nOffset+=2;CMPLEN(m_nOffset,bufLen);//Delay Time - ��λ1/100��(2�ֽڣ�
						memcpy((char*)&be,pBuf+m_nOffset,1);m_nOffset+=1;CMPLEN(m_nOffset,bufLen);
						ctrlExt.trsColorIndex = be;
					}
					else
						m_nOffset += (int)(byte)be;CMPLEN(m_nOffset,bufLen);// ����be���ֽ�
				}
			}
			break;
		case 0xfe:// Comment Label - ��ʶ����һ��ע�Ϳ飬�̶�ֵ0xFE
		case 0x01:
		case 0xff:// Application Extension Label - ��ʶ����һ��Ӧ�ó�����չ�飬�̶�ֵ0xFF
			{
				if (false == m_gInfo.bLoop)
				{
					char byChar[17] = {0x0B,'N','E','T','S','C','A','P','E','2','.','0',0x03,0x01,0x00,0x00,0x00};
					char byChar1[17]= {0};
					m_nOffset+=17;CMPLEN(m_nOffset,bufLen);m_nOffset-=17;
					memcpy(byChar1, pBuf+m_nOffset,17);CMPLEN(m_nOffset,bufLen);
					if (0 == strncmp(byChar1,byChar,14))
					{	
						int iHigh = (int)(byte)byChar1[15];int iLow = (int)(byte)byChar1[14];
						m_gInfo.totalLoopCount = iLow+iHigh*256;
						m_gInfo.bLoop = true;
					}
				}

				while (m_nOffset<=bufLen) // ����������һ�飬���ն����и����սᣬ�̶�ֵ0
				{	
					memcpy((char*)&be,pBuf+m_nOffset,1);m_nOffset+=1;CMPLEN(m_nOffset,bufLen);
					if (0 == be)// ���սᣬ�̶�ֵ0
						break;
					m_nOffset+=be;CMPLEN(m_nOffset,bufLen);// ����be���ֽ�
				}
			}
			break;
		default:
			bRet = false;
			break;
		}
		return bRet;
	}

#define CMPLENDEL(x,y,z)  if(x>y){delete[]z;return false;}
	bool DMGifParse::ParseFrame(BYTE *pBuf,int bufLen)
	{
		GIFFRAMEPTR pf = new GIFFRAME;

		memcpy((char*)&pf->imageLPos,pBuf+m_nOffset,2);m_nOffset+=2;CMPLENDEL(m_nOffset,bufLen,pf);
		memcpy((char*)&pf->imageTPos,pBuf+m_nOffset,2);m_nOffset+=2;CMPLENDEL(m_nOffset,bufLen,pf);
		memcpy((char*)&pf->imageWidth,pBuf+m_nOffset,2);m_nOffset+=2;CMPLENDEL(m_nOffset,bufLen,pf);
		memcpy((char*)&pf->imageHeight,pBuf+m_nOffset,2);m_nOffset+=2;CMPLENDEL(m_nOffset,bufLen,pf);

		BYTE be;
		UINT lSize = 1;
		bool lFlag = false;
		memcpy((char*)&be,pBuf+m_nOffset,1);m_nOffset+=1;CMPLENDEL(m_nOffset,bufLen,pf);
		if ((be&0x80) != 0)
			lFlag = true;
		lSize <<= ((be&0x07)+1);// ��ɫ�б��λ��
		if (lFlag)
			m_nOffset+=lSize*3;CMPLENDEL(m_nOffset,bufLen,pf);
		memcpy((char*)&be,pBuf+m_nOffset,1);m_nOffset+=1;CMPLENDEL(m_nOffset,bufLen,pf);
		while (m_nOffset<=bufLen)
		{	
			memcpy((char*)&be,pBuf+m_nOffset,1);m_nOffset+=1;CMPLENDEL(m_nOffset,bufLen,pf);
			if (0 == be)
				break;
			m_nOffset+=be;CMPLENDEL(m_nOffset,bufLen,pf);// ����be���ֽ�
		}

		if(m_ctrlExt.active)
		{
			pf->ctrlExt = m_ctrlExt;
			m_ctrlExt.active = false;
		}

		AddObj(pf);
		return true;
	}

	void DMGifParse::PreArrayObjRemove(const GIFFRAMEPTR &obj)
	{
		delete obj;
	}

}//namespace DM