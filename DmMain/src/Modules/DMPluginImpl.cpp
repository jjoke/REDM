#include "DmMainAfx.h"
#include "DMPluginImpl.h"
#include "DMLogImpl.h"
#include "DMAttributeImpl.h"
#include "DMImgDecoderImpl.h"
#include "DMResFolderImpl.h"
#include "DMRenderImpl.h"
#include "DMDrawImpl.h"
#include "DMImg9SkinImpl.h"
#include "DMScrollBarSkinImpl.h"
#include "DMStyleImpl.h"
#include "DMLayoutImpl.h"
#include "DMTooltipImpl.h"
#include "DMTransImpl.h"
#include "DMTaskRunnerImpl.h"

#include "DUIButton.h"
#include "DUIScrollBase.h"
#include "DUITabCtrl.h"
#include "DUITreeCtrl.h"
#include "DUIListBox.h"
#include "DUIListBoxEx.h"
#include "DUIEdit.h"
#include "DUIStatic.h"
#include "DUILink.h"
#include "DUIComboBox.h"
#include "DUIActiveX.h"
#include "DUIGif.h"
#include "DUIPngGif.h"
#include "DUIFlash.h"
#include "DUIIE.h"
#include "DUIHeaderCtrl.h"
#include "DUIListCtrlEx.h"
#include "DUIGroup.h"
#include "DUICheckBox.h"
#include "DUIRadioButton.h"
#include "DUISliderCtrl.h"
#include "DUIProcessCtrl.h"
#include "DUIHotKeyCtrl.h"
#include "DUIPAddressCtrl.h"
#include "DUITreeCtrlEx.h"
#include "DUIMonthCalCtrl.h"

#include "DUIFlowLayout.h"



namespace DM
{
	const wchar_t* DMPluginImpl::GetName()const 
	{
		return L"{6C27EB26-12F8-4807-95E9-578C781CD61E}";
	}

	void DMPluginImpl::Install()
	{
		DMCode iErr = DM_ECODE_OK;
		// Ĭ��Log -----------------------------
#ifdef DMLOG_ON
		iErr = g_pDMApp->Register(DMRegHelperT<DMLogImpl>(),true);
		DMASSERT_EXPR(DMSUCCEEDED(iErr), L"ע��DMLogImplʧ��!");
		iErr = g_pDMApp->SetDefRegObj(DMLogImpl::GetClassName(),DMLogImpl::GetClassType());
		DMASSERT_EXPR(DMSUCCEEDED(iErr), L"����DMLogImplΪĬ��Log����ʧ��!");
#endif //DMLOG_ON 

		// Ĭ��Attribute,��������������֮ǰ����Ϊ����������ʵ������ʹ�õ���
		iErr = g_pDMApp->Register(DMRegHelperT<DMAttributeImpl>(),true);
		DMASSERT_EXPR(DMSUCCEEDED(iErr), L"ע��DMAttributeImplʧ��!");
		iErr = g_pDMApp->SetDefRegObj(DMAttributeImpl::GetClassName(),DMAttributeImpl::GetClassType());
		DMASSERT_EXPR(DMSUCCEEDED(iErr), L"����DMAttributeImplΪĬ��Attr����ʧ��!");

		// Ĭ�Ͻ����� ----------------------------
		iErr = g_pDMApp->Register(DMRegHelperT<DMImgDecoderImpl>(),true);
		DMASSERT_EXPR(DMSUCCEEDED(iErr), L"ע��DMImgDecoderImplʧ��!");
		iErr = g_pDMApp->SetDefRegObj(DMImgDecoderImpl::GetClassName(),DMImgDecoderImpl::GetClassType());
		DMASSERT_EXPR(DMSUCCEEDED(iErr), L"����DMImgDecoderImplΪĬ��Decoder����ʧ��!");

		// Ĭ��Res -------------------------------
		iErr = g_pDMApp->Register(DMRegHelperT<DMResFolderImpl>(),true);
		DMASSERT_EXPR(DMSUCCEEDED(iErr), L"ע��DMResFolderImplʧ��!");
		iErr = g_pDMApp->SetDefRegObj(DMResFolderImpl::GetClassName(),DMResFolderImpl::GetClassType());
		DMASSERT_EXPR(DMSUCCEEDED(iErr), L"����DMResFolderImplΪĬ��Res����ʧ��!");

		// Ĭ��Render-----------------------------
		iErr = g_pDMApp->Register(DMRegHelperT<DMRenderImpl>(),true);
		DMASSERT_EXPR(DMSUCCEEDED(iErr), L"ע��DMRenderImplʧ��!");
		iErr = g_pDMApp->SetDefRegObj(DMRenderImpl::GetClassName(),DMRenderImpl::GetClassType());
		DMASSERT_EXPR(DMSUCCEEDED(iErr), L"����DMRenderImplΪĬ��Render����ʧ��!");

		// Ĭ��Draw-----------------------------
		iErr = g_pDMApp->Register(DMRegHelperT<DMDrawImpl>(),true);
		DMASSERT_EXPR(DMSUCCEEDED(iErr), L"ע��DMDrawImplʧ��!");
		iErr = g_pDMApp->SetDefRegObj(DMDrawImpl::GetClassName(),DMDrawImpl::GetClassType());
		DMASSERT_EXPR(DMSUCCEEDED(iErr), L"����DMDrawImplΪĬ��Render����ʧ��!");

		// Ĭ��Skin -----------------------------
		iErr = g_pDMApp->Register(DMRegHelperT<DMImgListSkinImpl>(),true);
		DMASSERT_EXPR(DMSUCCEEDED(iErr), L"ע��DMImgListSkinImplʧ��!");
		iErr = g_pDMApp->SetDefRegObj(DMImgListSkinImpl::GetClassName(),DMImgListSkinImpl::GetClassType());
		iErr = g_pDMApp->Register(DMRegHelperT<DMImg9SkinImpl>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DMScrollBarSkinImpl>(),true);
		DMASSERT_EXPR(DMSUCCEEDED(iErr), L"ע��DMImg9SkinImplʧ��!");

		// Ĭ��Style -----------------------------
		iErr = g_pDMApp->Register(DMRegHelperT<DMStyleImpl>(),true);
		DMASSERT_EXPR(DMSUCCEEDED(iErr), L"ע��DMStyleImplʧ��!");
		iErr = g_pDMApp->SetDefRegObj(DMStyleImpl::GetClassName(),DMStyleImpl::GetClassType());

		// Ĭ��Layout ----------------------------
		iErr = g_pDMApp->Register(DMRegHelperT<DMLayoutImpl>(),true);
		DMASSERT_EXPR(DMSUCCEEDED(iErr), L"ע��DMLayoutImplʧ��!");
		iErr = g_pDMApp->SetDefRegObj(DMLayoutImpl::GetClassName(),DMLayoutImpl::GetClassType());

		// ����Tooltip ---------------------------
		iErr = g_pDMApp->Register(DMRegHelperT<DMTooltipImpl>(),true);
		DMASSERT_EXPR(DMSUCCEEDED(iErr), L"ע��DMTooltipImplʧ��!");
		iErr = g_pDMApp->SetDefRegObj(DMTooltipImpl::GetClassName(),DMTooltipImpl::GetClassType());

		// ����Trans ---------------------------
		iErr = g_pDMApp->Register(DMRegHelperT<DMTransImpl>(),true);
		DMASSERT_EXPR(DMSUCCEEDED(iErr), L"ע��DMTransImplʧ��!");
		iErr = g_pDMApp->SetDefRegObj(DMTransImpl::GetClassName(),DMTransImpl::GetClassType());

		// ����TaskRunner-----------------------
		iErr = g_pDMApp->Register(DMRegHelperT<DMTaskRunnerImpl>(),true);
		DMASSERT_EXPR(DMSUCCEEDED(iErr), L"ע��DMTaskRunnerImplʧ��!");
		iErr = g_pDMApp->SetDefRegObj(DMTaskRunnerImpl::GetClassName(),DMTaskRunnerImpl::GetClassType());

		// ����Widget ----------------------------
		iErr = g_pDMApp->Register(DMRegHelperT<DUIWindow>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DUIButton>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DUIScrollBase>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DUITabPage>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DUITabCtrl>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DUITreeCtrl>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DUIListBox>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DUIListBoxEx>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DUIRichEdit>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DUIEdit>(),true);
		new DUIEditHelper;// ��edit���
		iErr = g_pDMApp->Register(DMRegHelperT<DUIStatic>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DUILink>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DUIComboBox>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DUIGif>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DUIPngGif>(),true);
#if !defined(_WIN64)// flash�ݲ�֧��X64,����������
		iErr = g_pDMApp->Register(DMRegHelperT<DUIFlash>(),true);
#endif
		iErr = g_pDMApp->Register(DMRegHelperT<DUIIE>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DUIHeaderCtrl>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DUIListCtrlEx>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DUIGroup>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DUICheckBox>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DUIRadioButton>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DUISliderCtrl>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DUIProcessCtrl>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DUIHotKeyCtrl>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DUIPEdit>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DUIPAddressCtrl>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DUITreeCtrlEx>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DUIMonthCalCtrl>(),true);
		

		// ����FlowLayout ----------------------------
		iErr = g_pDMApp->Register(DMRegHelperT<DUIVLayout>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DUIHLayout>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DUIWrapLayout>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DUITabLayout>(),true);
		iErr = g_pDMApp->Register(DMRegHelperT<DUISplitLayout>(),true);
	}

	void DMPluginImpl::Uninstall()
	{
		g_pDMApp->UnRegister(DUIRichEdit::GetClassName(),DUIRichEdit::GetClassType());
		g_pDMApp->UnRegister(DUIEdit::GetClassName(),DUIEdit::GetClassType());
		delete DUIEditHelper::getSingletonPtr();// ��edit���


#if 0 // ֻ������ʾ��,Ĭ�ϲ�����������
		DMCode iErr = DM_ECODE_OK;
		// Ĭ��Log -----------------------------
#ifdef DMLOG_ON
		iErr = g_pDMApp->UnRegister(DMLogImpl::GetClassName(),DMLogImpl::GetClassType());
		DMASSERT_EXPR(DMSUCCEEDED(iErr), L"��ע��DMLogImplʧ��!");
#endif //DMLOG_ON 

		// Ĭ��Attribute,��������������֮ǰ����Ϊ����������ʵ������ʹ�õ���
		iErr = g_pDMApp->UnRegister(DMAttributeImpl::GetClassName(),DMAttributeImpl::GetClassType());
		DMASSERT_EXPR(DMSUCCEEDED(iErr), L"��ע��DMAttributeImplʧ��!");
		

		// Ĭ�Ͻ����� ----------------------------
		iErr = g_pDMApp->UnRegister(DMImgDecoderImpl::GetClassName(),DMImgDecoderImpl::GetClassType());
		DMASSERT_EXPR(DMSUCCEEDED(iErr), L"��ע��DMImgDecoderImplʧ��!");
	
		// Ĭ��Res -------------------------------
		iErr = g_pDMApp->UnRegister(DMResFolderImpl::GetClassName(),DMResFolderImpl::GetClassType());
		DMASSERT_EXPR(DMSUCCEEDED(iErr), L"ע��DMResFolderImplʧ��!");

		// Ĭ��Render-----------------------------
		iErr = g_pDMApp->UnRegister(DMRenderImpl::GetClassName(),DMRenderImpl::GetClassType());
		DMASSERT_EXPR(DMSUCCEEDED(iErr), L"��ע��DMRenderImplʧ��!");

		// Ĭ��Skin -----------------------------
		iErr = g_pDMApp->UnRegister(DMImgListSkinImpl::GetClassName(),DMImgListSkinImpl::GetClassType());
		iErr = g_pDMApp->UnRegister(DMImg9SkinImpl::GetClassName(),DMImg9SkinImpl::GetClassType());
		iErr = g_pDMApp->UnRegister(DMScrollBarSkinImpl::GetClassName(),DMScrollBarSkinImpl::GetClassType());

		// Ĭ��Style -----------------------------
		iErr = g_pDMApp->UnRegister(DMStyleImpl::GetClassName(),DMStyleImpl::GetClassType());
		DMASSERT_EXPR(DMSUCCEEDED(iErr), L"��ע��DMStyleImplʧ��!");
	
		// Ĭ��Layout ----------------------------
		iErr = g_pDMApp->UnRegister(DMLayoutImpl::GetClassName(),DMLayoutImpl::GetClassType());
		DMASSERT_EXPR(DMSUCCEEDED(iErr), L"��ע��DMLayoutImplʧ��!");
	
		// ����Widget ----------------------------
		iErr = g_pDMApp->UnRegister(DUIWindow::GetClassName(),DUIWindow::GetClassType());

		// ����FlowLayout ----------------------------
		iErr = g_pDMApp->UnRegister(DUIVLayout::GetClassName(),DUIVLayout::GetClassType());
		iErr = g_pDMApp->UnRegister(DUIHLayout::GetClassName(),DUIHLayout::GetClassType());
		iErr = g_pDMApp->UnRegister(DUIWrapLayout::GetClassName(),DUIWrapLayout::GetClassType());
#endif //
	}

	void DMPluginImpl::Initialise()
	{
	
	}

	void DMPluginImpl::Shutdown()
	{

	}

}//namespace DM