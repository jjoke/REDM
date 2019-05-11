#pragma once  

class CMainWnd : public DMHWnd
{
public:
	DECLARE_MESSAGE_MAP()						// ��MFC��Ϣӳ��꣬Ҳ����ʹ��BEGIN_MSG_MAPT��ʹ��Ϣ������ͷ�ļ�
	DECLARE_EVENT_MAP()							// �¼��ַ�ӳ���,Ҳ����ʹ��BEGIN_EVENT_MAPT��ʹ�¼�������ͷ�ļ�

	//---------------------------------------------------
	// Function Des: ��Ϣ�ַ�ϵ�к���
	//---------------------------------------------------
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
	void OnSize(UINT nType, CSize size);

	//---------------------------------------------------
	// Function Des: �¼��ַ�ϵ�к���
	//---------------------------------------------------
	DMCode OnClose();
	DMCode OnMinimize();

	DMCode OnOpenSoluDir();
	DMCode OnMake();
public:
	DUIEdit*							      m_pSoluPathEdit;
	DUIEdit*							      m_pSoluNameEdit;
	DUIEdit*							      m_pProjNameEdit;
};