// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	IProp.h
// File mark:   
// File summary:Prop��������Զ���ӿ�
// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2016-7-29
// ----------------------------------------------------------------
#pragma once

namespace DM
{
	/// <summary>
	///		�������Խӿڣ�������չ
	/// </summary>
	class DUIPropList;
	class IProp : public DMBase
	{
	public:
		enum ClickArea{ClickExpandBox,ClickName,ClickValue,ClickDrag,ClickDescription};
		virtual DMCode SetOwner(DUIPropList *pOwner) = 0;								///< �������Լ��������б��ӵ����
		virtual DMCode SetParent(IProp* pParent) = 0;									///< ���ø�����
		virtual DMCode Expand(bool bExpand = true) = 0;									///< չ��������
		virtual DMCode Reposition(int& y) = 0;											///< ���²���
		virtual DMCode Invalidate() = 0;												///< ˢ��
		virtual DMCode AddSubItem(IProp* pProp) = 0;									///< ������������
		virtual DMCode RemoveSubItem(IProp* &pProp,bool bDelete = true) = 0;            ///< ɾ����������
		virtual DMCode RemoveAllSubItem(bool bDelete = true) = 0 ;						///< ɾ�����е�����
		virtual DMCode PreDelete() = 0;													///< ��Delete֮ǰԤ����
	
		virtual bool IsSubItem(IProp* pSubProp) = 0;									///< pSubProp�Ƿ�Ϊ��������					
		virtual bool IsParentExpanded() = 0;											///< �������Ƿ�Ϊչ��״̬
		virtual bool IsExpanded() = 0;													///< �Ƿ�չ��
		virtual bool IsInPlaceEdit() = 0;												///< �Ƿ���value�ؼ���ʾ״̬
		virtual bool IsGroup() = 0;														///< �Ƿ�Ϊgroup,groupֻ��name��û��value
		virtual IProp* HitTest(CPoint pt, IProp::ClickArea* pnArea = NULL) = 0;			///< pt����ĵط�
		virtual int GetHierarchyLevel() = 0;                                            ///< ����Լ����ڵڼ��㣨���������Ϊ0�㣩
		virtual int GetHeiWithSub() = 0;                                                ///< ����Լ�����������ĸ߶�
		virtual DUIPropList* GetOwner() = 0;
		virtual IProp* GetParent() = 0;
		virtual LPARAM GetData() = 0;
		virtual void SetData(LPARAM lpData) = 0;
		virtual IProp* FindSubItemByData(LPARAM lpData) = 0;
		virtual void UpdateSubXml(DMXmlNode &XmlNode) = 0;
		virtual CStringW GetName() = 0;
		virtual CStringW GetValue() = 0;
	
		// ����
		virtual DMCode OnRender(IDMCanvas* pCanvas) = 0;
		virtual DMCode OnDrawExpandBox(IDMCanvas* pCanvas,CRect rcExpand) = 0;
		virtual DMCode OnDrawName(IDMCanvas* pCanvas, CRect rcName) = 0;
		virtual DMCode OnDrawValue(IDMCanvas* pCanvas, CRect rcValue) = 0;
		virtual DMCode OnDrawDesc(IDMCanvas* pCanvas, CRect rcDesc) = 0;
		

		// ���
		virtual DMCode OnClickValue(UINT uiMsg, CPoint point) = 0;
		virtual DMCode OnClickName(UINT uiMsg, CPoint point) = 0;
		virtual DMCode OnClickDrag(UINT uiMsg, CPoint point) = 0;

		// ���Ե�InPlace���ڴ�������ʾ����
		virtual DMCode OnCreateInPlaceCtrl() = 0;
		virtual DMCode OnInPlaceCtrlShow(bool bShow = true) = 0;
	};
	typedef IProp* IPropPtr;

}//namespace DM