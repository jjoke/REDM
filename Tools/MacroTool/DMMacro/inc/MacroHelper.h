// ----------------------------------------------------------------
// Copyright (c)  
// All rights reserved.
// 
// File name:	MacroHelper.h
// File mark:   
// File summary:
// Author:		guoyouhuang
// Edition:     1.0
// Create date: 2016-10-31
// ----------------------------------------------------------------
#pragma once
#include <vector>
using namespace std;

typedef struct stMACRO
{
	CStringW		strDef;			// �궨����:MSG_WM_INITDIALOG(func)
	CStringW		strContent;     // ���Ӧ������
	CStringW        strMainDef;     // ������ǰ������,��MSG_WM_INITDIALOG
	CStringW        strDot;			// ���������ڵ�����,��fun
	CStringWList    strParamList;   // ��strDot�����ŷֿ�
}MACRO,*PMACRO;

class CMacroHelper
{
public:
	bool LoadFile(CStringW strPath,CStringW strStart); 
	CStringW Convert(CStringW strMacro);

private:
	bool AddMacroItem(CStringW strFind);
	PMACRO FindMacroItem(CStringW strMainDef,int nParamCount);
	void TermSpace(CStringW& str);

public:

	vector<PMACRO>                       m_VecMacro;

};