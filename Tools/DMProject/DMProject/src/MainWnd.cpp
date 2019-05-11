#include "StdAfx.h"
#include "MainWnd.h"

BEGIN_MSG_MAP(CMainWnd)
	MSG_WM_INITDIALOG(OnInitDialog)
	CHAIN_MSG_MAP(DMHWnd)// ��δ�������Ϣ����DMHWnd����
END_MSG_MAP()
BEGIN_EVENT_MAP(CMainWnd)
	EVENT_NAME_COMMAND(L"closebutton",OnClose)
	EVENT_NAME_COMMAND(L"minbutton", OnMinimize)
	EVENT_NAME_COMMAND(L"opensolubtn", OnOpenSoluDir)
	EVENT_NAME_COMMAND(L"makebtn", OnMake)
END_EVENT_MAP()

BOOL CMainWnd::OnInitDialog(HWND wndFocus, LPARAM lInitParam)
{
	m_pSoluPathEdit = FindChildByNameT<DUIEdit>(L"solupath");DMASSERT(m_pSoluPathEdit);
	m_pSoluNameEdit = FindChildByNameT<DUIEdit>(L"soluname");DMASSERT(m_pSoluNameEdit);
	m_pProjNameEdit = FindChildByNameT<DUIEdit>(L"projname");DMASSERT(m_pProjNameEdit);
	return TRUE;
}

DMCode CMainWnd::OnClose()
{
	DestroyWindow(); 
	return DM_ECODE_OK;
}

DMCode CMainWnd::OnMinimize()
{
	SendMessage(WM_SYSCOMMAND,SC_MINIMIZE);
	return DM_ECODE_OK;
}

DMCode CMainWnd::OnOpenSoluDir()
{
	wchar_t path[MAX_PATH] = {0};
	BROWSEINFOW bi = {0};
	bi.ulFlags = BIF_STATUSTEXT| BIF_RETURNONLYFSDIRS|BIF_VALIDATE;
	bi.lpszTitle = L"��ѡ��DM�½�������Ĵ��λ�ã�Ŀǰ��֧���ļ��з�ʽ��";
	bi.hwndOwner = m_hWnd;//����ӵ�д���
	bi.lpfn = NULL;	//ָ���ص�������ַ
	ITEMIDLIST *pIDL = SHBrowseForFolderW(&bi);
	if (pIDL!=NULL)
	{
		if (SHGetPathFromIDListW(pIDL,path) == TRUE) //����path�д洢�˾����û�ѡ����Ŀ¼������·��.
		{
			m_pSoluPathEdit->SetWindowText(path);
		}
		// free memory used   
		IMalloc * imalloc = 0;   
		if (SUCCEEDED(SHGetMalloc( &imalloc)))   
		{   
			imalloc->Free(pIDL);   
			imalloc->Release();   
		}   
	}
	return DM_ECODE_OK;
}

bool CopyDirectory(CStringW strSrcDir,CStringW strDestDir)
{
	bool bRet = false;
	do 
	{
		if (strSrcDir.IsEmpty()||strDestDir.IsEmpty())		
		{
			break;
		}
		wchar_t szSrcFolder[MAX_PATH+1] = {0};
		wcscpy_s(szSrcFolder,strSrcDir.GetBuffer());strSrcDir.ReleaseBuffer();
		szSrcFolder[strSrcDir.GetLength()] =  L'\0';
		szSrcFolder[strSrcDir.GetLength()+1] = L'\0';

		wchar_t szDestFolder[MAX_PATH+1] = {0};
		wcscpy_s(szDestFolder,strDestDir.GetBuffer());strDestDir.ReleaseBuffer();
		szDestFolder[strDestDir.GetLength()] =  L'\0';
		szDestFolder[strDestDir.GetLength()+1] = L'\0';

		SHFILEOPSTRUCTW FileOp; 
		ZeroMemory(&FileOp, sizeof(SHFILEOPSTRUCT)); 
		FileOp.fFlags |= FOF_SILENT;        /*����ʾ����*/
		FileOp.fFlags |= FOF_NOERRORUI ;    /*�����������Ϣ*/
		FileOp.fFlags |= FOF_NOCONFIRMATION;/*������ȷ��*/
		FileOp.hNameMappings = NULL;
		FileOp.hwnd = NULL;
		FileOp.lpszProgressTitle = NULL;
		FileOp.wFunc = FO_COPY;
		FileOp.pFrom = szSrcFolder;        /*ԴĿ¼��������2��\0��β*/
		FileOp.pTo = szDestFolder;          /*Ŀ��Ŀ¼��������2��\0��β*/    
		if (0!= SHFileOperationW(&FileOp))
		{
			break;
		}

		bRet = true;
	} while (false);
	return bRet;
}

DMCode CMainWnd::OnMake()
{
	DMCode iErr = DM_ECODE_FAIL;
	do 
	{
		CStringW  strSoluPath = m_pSoluPathEdit->GetWindowText();
		if (strSoluPath.IsEmpty())
		{
			MessageBox(L"δѡ��������·��");
			break;
		}
		CStringW strSoluName =  m_pSoluNameEdit->GetWindowText();
		if (strSoluName.IsEmpty())
		{
			MessageBox(L"δѡ������������");
			break;
		}
		if (strSoluPath.Right(1)!=L"\\")
		{
			strSoluPath += L"\\";
		}

		CStringW strSolu = strSoluPath + strSoluName;
		if (PathFileExists(strSolu))
		{
			MessageBox(L"��������ļ����Ѵ��ڣ�������ѡ��");
			break;
		}

		CStringW strProjName = m_pProjNameEdit->GetWindowText();
		if (strProjName.IsEmpty())
		{
			MessageBox(L"δѡ����Ŀ��������");
			break;
		}

		// �����ļ��й�ȥ
		wchar_t szSrcPath[MAX_PATH] = {0};
		DM::GetRootFullPath(L".\\YYYY",szSrcPath,MAX_PATH);
		if (false == CopyDirectory(szSrcPath,strSolu))
		{
			MessageBox(L"�����������ʧ��");
			break;
		}

		
		{// �޸�MAKELIST1
			CStringW strMakeList = strSolu + L"\\CMakeLists.txt";
			DWORD dwSize = GetFileSizeW((LPWSTR)(LPCWSTR)strMakeList);
			DMBufT<byte>pBuf;pBuf.Allocate(dwSize);
			DWORD dwRead;
			GetFileBufW((LPWSTR)(LPCWSTR)strMakeList, (void**)&pBuf,dwSize,dwRead);
			CStringA strMakeListBuf((const char*)pBuf.get(),dwSize);
			CStringW strWMakeListBuf = DMA2W(strMakeListBuf,CP_UTF8);
			strWMakeListBuf.Replace(L"YYYY",strSoluName);
			strWMakeListBuf.Replace(L"XXXX",strProjName);
			strMakeListBuf = DMW2A(strWMakeListBuf,CP_UTF8);

			HANDLE hFile = CreateFile(strMakeList,GENERIC_WRITE,FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
			DWORD dwWrite = 0;
			WriteFile(hFile,strMakeListBuf.GetBuffer(),strMakeListBuf.GetLength(),&dwWrite,NULL);
			CloseHandle(hFile);
			hFile = NULL;
		}
		

		// �޸�XXXX�ļ�����
		CStringW strXXXXDir = strSolu + L"\\XXXX";
		CStringW strProjDir = strSolu + L"\\";strProjDir += strProjName;
		MoveFile(strXXXXDir,strProjDir);

		// �޸�XXXX.cpp
		CStringW strXXXXCpp = strProjDir + L"\\src\\XXXX.cpp";
		CStringW strProjCpp = strProjDir + L"\\src\\";strProjCpp += strProjName; strProjCpp += L".cpp";
		MoveFile(strXXXXCpp,strProjCpp);

		{// �޸�MAKELIST2
			CStringW strMakeList = strProjDir + L"\\CMakeLists.txt";
			DWORD dwSize = GetFileSizeW((LPWSTR)(LPCWSTR)strMakeList);
			DMBufT<byte>pBuf;pBuf.Allocate(dwSize);
			DWORD dwRead;
			GetFileBufW((LPWSTR)(LPCWSTR)strMakeList, (void**)&pBuf,dwSize,dwRead);
			CStringA strMakeListBuf((const char*)pBuf.get(),dwSize);
			CStringW strWMakeListBuf = DMA2W(strMakeListBuf,CP_UTF8);
			strWMakeListBuf.Replace(L"YYYY",strSoluName);
			strWMakeListBuf.Replace(L"XXXX",strProjName);
			strMakeListBuf = DMW2A(strWMakeListBuf,CP_UTF8);

			HANDLE hFile = CreateFile(strMakeList,GENERIC_WRITE,FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
			DWORD dwWrite = 0;
			WriteFile(hFile,strMakeListBuf.GetBuffer(),strMakeListBuf.GetLength(),&dwWrite,NULL);
			CloseHandle(hFile);
			hFile = NULL;
		}

		iErr = DM_ECODE_OK;
		MessageBox(L"������������ɹ�");
	} while (false);
	return iErr;
}
