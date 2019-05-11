// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	Helper.h
// File mark:   
// File summary:
// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2016-7-7
// ----------------------------------------------------------------
#pragma once

bool IsDirectoryExist(CStringW strDir);///< �ж�·���Ƿ�Ϊ�ļ���
bool OpenFolderAndSelectFile(CStringW strFilePath);///< ����ļ����Ѿ��򿪣��Ͳ��������´�һ�Σ�ֱ���ö���ʾ����ѡ��Ŀ���ļ�http://www.cnblogs.com/shankun/p/4088860.html
bool CopyDirectory(CStringW strSrcDir,CStringW strDestDir);///< �����ļ��У�ע�⣬���Ŀ���ļ����Ѵ��ڣ�����Դ�ļ���Ϊ�����Ƶ�Ŀ���ļ��е���Ŀ¼��
bool SetLogInfo(CStringW strInfo);
DMXmlDocument* GetExistXmlDoc(LPCWSTR lpszType,LPCWSTR lpszResName);///< ����ѽ�������xml doc(δ����ʱ���ܺ�xml�ļ���ͬ��

int DM_MessageBox(LPCWSTR lpText,UINT uType = MB_OK, LPCWSTR lpCaption = L"MSG",HWND hWnd = NULL); 
int StringToInt(CStringW str);
CStringW IntToString(int id);
bool IsUseDgSkin();

// ���ƺ������η�װ
DMCode AutoDrawText(IDMCanvas*pCanvas,CStringW strFont,DMColor TextClr,LPCWSTR lpString, int nCount, LPRECT lpRect, UINT uFormat,BYTE alpha=0xFF);
DMCode AutoDrawRoundRect(IDMCanvas*pCanvas,DMColor TextClr,int iStyle,int iWidth,LPCRECT lpRect,POINT &pt);
DMCode AutoFillRoundRect(IDMCanvas*pCanvas,DMColor BrushClr,LPCRECT lpRect,POINT &pt);

// Hook���η�װ,hook�����ڴ���prop��ϵͳ������(��ɫ�������),�޹ش���,���Դ˲���hook����Դ
class DMHook
{
public:
	DMHook();
	~DMHook();
	HMODULE m_hDll;
};

// ÿ��xml���԰�һ��DMXmlInitAttr,�������ִ������Ƿ��ѱ�ʹ��,��ʹ�õ����Բ��������expand����
class DMXmlInitAttr
{
public:
	DMXmlInitAttr(DMXmlAttribute& XmlAttr);
	~DMXmlInitAttr();

public:
	DMXmlAttributePtr      m_pAttr;
	bool                   m_bUse;
	CStringW               m_strReserve;
};
typedef DMXmlInitAttr* DMXmlInitAttrPtr;

// DMAttr.xml��¼���������Ե�prop����,��ʼֵ,����,����DM���Զ�����.
// DMCls.xml��¼�˿ؼ�->���Լ���
// DMAdd.xml���ڼ�¼addģʽ��Ĭ�ϵ�����
// DMDesigner.xml��¼������򿪵���Ŀ
class DMCtrlXml
{
public:
	DMCtrlXml();
	~DMCtrlXml();
	
	bool Parse(DMXmlAttributePtr ptr,CStringW &strType,CStringW &strName,CStringW& strValue,CStringW &strDesc);
	bool ParseName(DMXmlAttributePtr ptr,CStringW &strType,CStringW &strName);
	bool Parse(CStringW strClsName,CStringWList &strList);///< ��cls�н�����������Ĳ�ͬ���Լ���

	DMXmlNode Parse(CStringW strReg);///< ��ע��������������Ĭ��XmlNode
	DMXmlNode GetAttrNode(CStringW strNode);

	bool SetCopyNode(DMXmlNodePtr pNode, CRect rcWnd);
	
	bool AddRecentResDir(CStringW strNewDir);
	bool RemoveRecentResDir(CStringW strNewDir);
public:
	DMXmlDocument	m_AttrDoc;
	DMXmlDocument   m_ClsDoc;  
	DMXmlDocument   m_AddDoc;
	DMXmlDocument   m_AddDgDoc;

	// copy
	DMXmlDocument   m_CopyDoc;
	DMXmlNode       m_CopyNode;
	CRect           m_rcCopy;

	// recent
	DMXmlDocument   m_RecentDoc;
};

static MultStr g_stAttrDesc[] = \
{  // ����       Ĭ������														prop����        Ĭ��ֵ
	{L"COLOR",	 L"��ɫʹ��Ԥ�˷�ʽPBGRA:\r\n clr=\"PBGRA(ff,ff,ff,ff)\"",		L"propclr",		L"pbgra(ff,ff,ff,ff)"},
	{L"INT",	 L"�������и�����;,���ڲ�������",								L"propint",		L"0"},
	{L"RECT",	 L"һ������ָ���ĸ�ֵ,����9����,�ǿͻ��˵��ıߵ�",				L"proprect",	L"0,0,0,0"},
	{L"BYTE",	 L"����һ������ָ��alpha,������[0-255]֮��",					L"propbyte",	L"255"},
	{L"FONT",	 L"����ʹ���ַ���������,�Զ��ŷָ�",							L"propfont",	L"weight:400,underline:0,italic:0,strike:0,size:14,face:������"},
	{L"accel",   L"��ݼ��������",												L"propaccel",	L""},
	{L"SIZE",    L"һ������ָ��2��ֵ,�����С",									L"propsize",	L"0,0"},
	{L"POINT",   L"һ������ָ��2��ֵ,��������",									L"propsize",	L"0,0"},
	{L"bool",    L"�����Ϳ�ʹ��0���0,���ַ���yes��no",							L"propoption",  L""},
	{L"OPTION",	 L"��ѡ��������ѡ�������:\r\n align=\"left\"",					L"propoption",	L""},
	{L"STRING",  L"�ַ����и�����;,���ڲ�������",								L"propstring",	L""},
	{L"SKIN",	 L"Ƥ��ָ����ĳ��ͼƬ�Ļ��Ʒ�ʽ",								L"propstring",	L""},
};
