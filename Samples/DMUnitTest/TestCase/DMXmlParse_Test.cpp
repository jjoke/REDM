//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMXmlParse_Test.cpp 
// File Des: ����Xml������װ��
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-11	1.0			
//-------------------------------------------------------
#pragma once
#include "DMUintTestAfx.h"
#include "DMXmlParse.h"

class DMXmlParseTest:public::testing::Test
{
public:
	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{

	}
};

TEST_F(DMXmlParseTest,test1)
{
	DMXmlDocument doc;
	EXPECT_EQ(doc.LoadFromFile(L"UTRes\\UTTest\\UTXmlParse.xml"), true);

	// ���ڴ�ӡXml����
	// ��������
	DMXmlNode XmlElementNoFind = doc.Root(L"hgy");
	EXPECT_EQ(XmlElementNoFind.IsValid(), false);// ��û��hgy�����
	DMXmlNode XmlElementRoot = doc.Root();
	XmlElementRoot.SetAttributeInt64(L"I64",123456789012);// ����һ��I64
	EXPECT_EQ(XmlElementRoot.AttributeInt64(L"I64"),123456789012);
	XmlElementRoot.SetAttribute(L"0x64",L"0x9876543210");// ���ַ����ķ�ʽ����һ��I64
	EXPECT_EQ(XmlElementRoot.AttributeInt64(L"0x64"),0x9876543210);
	DMXmlNode XmlElementRoot1 = doc.Root(L"xmlui");
	EXPECT_EQ(XmlElementRoot.IsEqual(XmlElementRoot1), true);
	EXPECT_EQ(XmlElementRoot.IsEqual(XmlElementNoFind), false);

	DMXmlNode XmlElement = XmlElementRoot.FirstChild().FirstChild().FirstChild();
	LPCWSTR szName = XmlElement.GetName();
	LPCWSTR szValue = XmlElement.GetValue();
	XmlElement = XmlElement.NextSibling();

	DMXmlAttribute XmlAttribute;
	EXPECT_EQ(XmlAttribute.IsValid(), false);
	XmlAttribute = XmlElement.FirstAttribute();
	EXPECT_EQ(XmlAttribute.IsValid(), true);
	XmlAttribute = XmlAttribute.NextAttribute();
	szName = XmlAttribute.GetName();
	szValue = XmlAttribute.GetValue();
}

