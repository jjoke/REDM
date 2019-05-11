#include "DMDesignerAfx.h"
#include "TipWnd.h"

bool AttrTipWnd::InitAttr(DMXmlInitAttrPtr ptr)
{
	bool bRet = false;
	do 
	{
		CStringW strType,strName,strValue,strDesc;
		FindChildByNameT<DUIStatic>(L"ds_attr")->SetAttribute(L"text",L"δ֪����");
		FindChildByNameT<DUIStatic>(L"ds_type")->SetAttribute(L"text",strType);
		FindChildByNameT<DUIStatic>(L"ds_name")->SetAttribute(L"text",strName);
		FindChildByNameT<DUIStatic>(L"ds_desc")->SetAttribute(L"text",strDesc);
		if (NULL == ptr)
		{
			break;
		}
	
		g_pAttr->Parse(ptr->m_pAttr,strType,strName,strValue,strDesc);
		FindChildByNameT<DUIStatic>(L"ds_attr")->SetAttribute(L"text",ptr->m_pAttr->GetName());
		FindChildByNameT<DUIStatic>(L"ds_type")->SetAttribute(L"text",strType);
		FindChildByNameT<DUIStatic>(L"ds_name")->SetAttribute(L"text",strName);
		FindChildByNameT<DUIStatic>(L"ds_desc")->SetAttribute(L"text",strDesc);

		bRet = true;
	} while (false);
	return bRet;
}


//AddTipWnd---------------------------------------------------
MultStr g_AddInfo[] = \
{
	{L"Window",		 L"�����ؼ�",		L"ϵͳ��������",		L""},
	{L"Button",		 L"�����ؼ�",		L"ͨ�õİ�ť",			L""},
	{L"Static",		 L"�����ؼ�",		L"��̬��",				L"��̬����Ӧ��Ϣ"},
	{L"Group",		 L"�����ؼ�",		L"���",				L""},
	{L"CheckBox",	 L"�����ؼ�",		L"ѡ���",				L""},
	{L"Link",		 L"�����ؼ�",		L"����",				L""},
	{L"Combobox",	 L"�����ؼ�",		L"���Ͽ�",				L""},
	{L"HotKey",		 L"�����ؼ�",		L"�ȼ�",				L""},

	{L"IPAddress",	 L"�����ؼ�",		L"IP��",				L""},
	{L"RadioButton", L"�����ؼ�",		L"��ѡ��",				L""},
	{L"SliderCtrl",	 L"�����ؼ�",		L"������",				L""},
	{L"ProcessCtrl", L"�����ؼ�",		L"������",				L""},
	{L"TabCtrl",	 L"�����ؼ�",		L"Tab�ؼ�",				L""},
	{L"TabPage",	 L"�����ؼ�",		L"Tabҳ",				L"�����ڲ��뵽TabCtrl"},
	{L"RichEdit",	 L"�����ؼ�",		L"�༭��(֧�ֶ���)",	L""},
	{L"Edit",		 L"�����ؼ�",		L"�༭��",				L""},
	{L"ListBox",	 L"�����ؼ�",		L"�б��",				L"��ˮƽ������"},
	{L"ListBoxEx",	 L"��չ�ؼ�",		L"��չ�б��",			L""},
	{L"TreeCtrl",	 L"�����ؼ�",		L"���οؼ�",			L""},
	{L"TreeCtrlEX",	 L"��չ�ؼ�",		L"��չ���οؼ�",		L""},
	{L"HeaderCtrl",	 L"�����ؼ�",		L"�б�ͷ",				L""},
	{L"ListCtrlEx",	 L"��չ�ؼ�",		L"��չ�б�view",		L""},
	{L"Gif",		 L"�����ؼ�",		L"Gif����",				L""},
	{L"PngGif",		 L"�����ؼ�",		L"PngGif�ؼ�",		    L""},
	{L"IE",			 L"�����ؼ�",		L"IE�ؼ�",				L""},
	{L"SplitLayout", L"�����ؼ�",		L"SplitLayout�ؼ�",		L"�ָ���������"},
	{L"MonthCalCtrl", L"�����ؼ�",		L"�����ؼ�",			L""}, 
}; 
bool AddTipWnd::InitAdd(CStringW strInfo)
{
	bool bFind = false;
	int nCount = countof(g_AddInfo);
	for (int i=0; i<nCount; i++)
	{
		if (0 == g_AddInfo[i].strOne.CompareNoCase(strInfo))
		{
			FindChildByNameT<DUIStatic>(L"ds_add_text1")->DV_SetWindowText(g_AddInfo[i].strOne);
			FindChildByNameT<DUIStatic>(L"ds_add_text2")->DV_SetWindowText(g_AddInfo[i].strTwo);
			FindChildByNameT<DUIStatic>(L"ds_add_text3")->DV_SetWindowText(g_AddInfo[i].strThree);
			FindChildByNameT<DUIStatic>(L"ds_add_text4")->DV_SetWindowText(g_AddInfo[i].strFour);
			bFind = true;
		}
	}
	if (!bFind)
	{
		FindChildByNameT<DUIStatic>(L"ds_add_text1")->DV_SetWindowText(strInfo);
		FindChildByNameT<DUIStatic>(L"ds_add_text2")->DV_SetWindowText(L"�����ؼ�");
		FindChildByNameT<DUIStatic>(L"ds_add_text3")->DV_SetWindowText(L"�����ؼ�");
		FindChildByNameT<DUIStatic>(L"ds_add_text4")->DV_SetWindowText(L"");
	}
	return true;
}
