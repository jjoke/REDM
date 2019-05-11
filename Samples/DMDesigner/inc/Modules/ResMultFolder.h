// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	ResMultFolder.h
// File mark:   
// File summary:���ڹ�������DMDesigner����Դ��Ҫ�༭����Դ
// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2016-7-8
// ----------------------------------------------------------------
#pragma once
#include "ResFolder.h"
/// <summary>
///		���ļ��й���,0�ļ���Ϊ�����������Դ(ȫ��ds_��ͷ),1�ļ���ΪҪ�༭����Դ
/// </summary>
typedef ResFolder* ResFolderPtr;
class ResMultFolder: public IDMRes,public DMArrayT<ResFolderPtr>
{
	DMDECLARE_CLASS_NAME(ResMultFolder,L"ResMultFolder",DMREG_Res);
public:
	ResMultFolder();
	~ResMultFolder();

public:
	virtual DMCode LoadResPack(WPARAM wp, LPARAM lp);
	virtual DMCode IsItemExists(LPCWSTR lpszType, LPCWSTR lpszName,LPCWSTR lpszThemeName=NULL);
	virtual DMCode GetItemSize(LPCWSTR lpszType, LPCWSTR lpszName, unsigned long& ulSize,LPCWSTR lpszThemeName=NULL);
	virtual DMCode GetItemBuf(LPCWSTR lpszType, LPCWSTR lpszName, LPVOID lpBuf, unsigned long ulSize,LPCWSTR lpszThemeName=NULL);
	virtual DMCode LoadTheme(WPARAM wp, LPARAM lp);
	virtual DMCode SetCurTheme(LPCWSTR lpszName, LPCWSTR lpszOldName=NULL);
	virtual DMCode SendExpandInfo(WPARAM wp, LPARAM lp);

protected:
	virtual void PreArrayObjRemove(const ResFolderPtr &obj);
	bool IsDMDesignerRes(CStringW strName);
	ResFolderPtr GetResFolderPtr(CStringW strName);
};