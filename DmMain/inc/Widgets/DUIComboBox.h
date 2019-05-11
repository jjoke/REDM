//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name:DUIComboBox.h 
// File Des:
// File Summary:
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-3-2	1.0			
//--------------------------------------------------------
#pragma once
#include "DUIComboBoxHelper.h"
#include "DUIListBox.h"
namespace DMAttr
{
	/// <summary>
	///		<see cref="DM::DUIComboBox"/>��xml���Զ���
	/// </summary>
	class DUIComboBoxAttr:public DUIComboBoxBaseAttr
	{
	public:
		static wchar_t* STRING_clslistbox;                                            ///< ָ��listbox����ʹ�õ�����,���������Զ���listbox��Ĭ��ʹ������
		static wchar_t* ITEM_sublistbox;                                              ///< �ӿؼ�listbox��XML��ʶ
	};
	DMAttrValueInit(DUIComboBoxAttr,STRING_clslistbox)DMAttrValueInit(DUIComboBoxAttr,ITEM_sublistbox)
}
namespace DM
{
	/// <summary>
	///		 DUIComboBox������ʵ��
	/// </summary>
	class DM_EXPORT DUIComboBox : public DUIComboBoxBase
	{
		DMDECLARE_CLASS_NAME(DUIComboBox, DUINAME_ComboxBox,DMREG_Window)
	public:
		DUIComboBox();
		virtual ~DUIComboBox();

	public:
		//---------------------------------------------------
		// Function Des: ����ӿ�
		//---------------------------------------------------
		LPARAM GetItemData(UINT iItem) const;
		int SetItemData(UINT iItem, LPARAM lParam);
		int InsertItem(UINT iPos,LPCTSTR pszText,int nHei=-1,int iIcon=-1,LPARAM lParam=0);
		bool DeleteString(UINT iItem);
		void ResetContent();
		DUIListBox* GetListBox();

	public:
		//---------------------------------------------------
		// Function Des: IDMDropDownOwnerʵ��
		//---------------------------------------------------                  
		virtual DMCode OnDropDown(DMDropWnd *pDropDown);
		virtual DMCode OnCloseUp(DMDropWnd *pDropDown,UINT uCode);

	public:
		//---------------------------------------------------
		// Function Des: ����
		//---------------------------------------------------
		virtual int GetCount()const;
		virtual int GetListBoxHeight();
		virtual int GetCurSel()const;
		virtual CStringW GetLBText(int iItem);
		virtual bool SetCurSel(int iSel);
		virtual bool CreateListBox(DMXmlNode &XmlNode);
		virtual void OnSelChanged();

		//---------------------------------------------------
		// Function Des: ����DUIWindow
		//---------------------------------------------------
		virtual DMCode DV_FireEvent(DMEventArgs &Evt);
	public:
		DM_BEGIN_ATTRIBUTES()
			DM_STRING_ATTRIBUTE(DMAttr::DUIComboBoxAttr::STRING_clslistbox,m_strClsListBox,DM_ECODE_OK)
		DM_END_ATTRIBUTES()
	public:
		DMSmartPtrT<DUIListBox>					m_pListBox; 
		CStringW                                m_strClsListBox;
	};
	


}//namespace DM