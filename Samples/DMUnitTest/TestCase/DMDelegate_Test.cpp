//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMDelegate_Test.cpp 
// File Des: ����ί�д���Ĳ�������
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-8	1.0			
//-------------------------------------------------------
#pragma once
#include "DMUintTestAfx.h"
#include "DMDelegate.h"

/// ����ģ��
class IBase
{
public:
	typedef DMDelegate<bool()> t_BaseFun1;
	t_BaseFun1    m_fun_BaseFun1;	
};
class Base
{
public:
	Base():m_pDelegate(NULL){};
	bool BaseFun1()
	{
		printf("BaseFun1\n");
		return true;
	}
public:// ��ʼ��
	virtual IBase* GetDelegate()// �����Ϊ�麯��
	{
		if (NULL == m_pDelegate)
		{
			m_pDelegate = new IBase;
		}
		DMDLBIND(m_pDelegate->m_fun_BaseFun1, DMBind(&Base::BaseFun1,this))
		return m_pDelegate;
	}

public:
	IBase*  m_pDelegate;
};

/// A�̳���B
class IA:public IBase
{
public:
	typedef DMDelegate<int(int x,int y)> t_AFun1;
	t_AFun1   m_fun_AFun1;
};

class A:public Base
{
public:
	int AFun1(int x,int y)
	{
		printf("AFun1-x:%d,y:%d\n",x,y);
		return x+y;
	}
public:
	virtual IBase* GetDelegate()
	{
		if (NULL == m_pDelegate)
		{
			m_pDelegate = new IA;
		}
		DMDLBIND(((IA*)m_pDelegate)->m_fun_AFun1,DMBind(&A::AFun1,this))
		return __super::GetDelegate();// �ø��������ʼ��
	}
};

class B:public Base
{
public:
	bool BaseFun1()// ���ʹ��Base*p=new B,������Ӧ���Ǹ��麯�����ܱ����õ������������ת��
	{
		printf("B-Fun1\n");
		return true;
	}
public:
	virtual IBase* GetDelegate()
	{
		if (NULL == m_pDelegate)
		{
			m_pDelegate = new IBase;
		}
		
		DMDLBIND(m_pDelegate->m_fun_BaseFun1,DMBind(&B::BaseFun1,this))
		return __super::GetDelegate();
	}
};

class DMDelegateTest:public::testing::Test
{
public:
	virtual void SetUp()
	{
		m_pBase = new Base;
		m_pA    = new A;
		m_pB    = new B;

	}
	virtual void TearDown()
	{
		DM_DELETE(m_pBase);
		DM_DELETE(m_pA);
		DM_DELETE(m_pB);
	}

protected:
	Base        *m_pBase;
	Base        *m_pA;
	Base        *m_pB;
};


TEST_F(DMDelegateTest, Test1)
{
	IBase*p = m_pBase->GetDelegate();
	p->m_fun_BaseFun1();

	IA* pA = (IA*)m_pA->GetDelegate();
	pA->m_fun_AFun1(10,20);

	IBase*pB = m_pB->GetDelegate();
	pB->m_fun_BaseFun1();
}

