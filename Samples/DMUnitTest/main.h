#pragma once

#pragma once

class DMEnvironment: public testing::Environment
{
public:
	virtual void SetUp();
	virtual void TearDown();

public://ȫ�ֹ������
	DMApp*						 m_pDMApp;
};

extern DMEnvironment *pGlobalPtr;          // ȫ��ָ��