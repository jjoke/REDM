#include "StdAfx.h"
#include "MainWnd.h"

BEGIN_MSG_MAP(CMainWnd)
	MSG_WM_INITDIALOG(OnInitDialog)
	CHAIN_MSG_MAP(DMHWnd)// 将未处理的消息交由DMHWnd处理
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
	bi.lpszTitle = L"请选择DM新解决方案的存放位置（目前仅支持文件夹方式）";
	bi.hwndOwner = m_hWnd;//设置拥有窗口
	bi.lpfn = NULL;	//指定回调函数地址
	ITEMIDLIST *pIDL = SHBrowseForFolderW(&bi);
	if (pIDL!=NULL)
	{
		if (SHGetPathFromIDListW(pIDL,path) == TRUE) //变量path中存储了经过用户选择后的目录的完整路径.
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
		FileOp.fFlags |= FOF_SILENT;        /*不显示进度*/
		FileOp.fFlags |= FOF_NOERRORUI ;    /*不报告错误信息*/
		FileOp.fFlags |= FOF_NOCONFIRMATION;/*不进行确认*/
		FileOp.hNameMappings = NULL;
		FileOp.hwnd = NULL;
		FileOp.lpszProgressTitle = NULL;
		FileOp.wFunc = FO_COPY;
		FileOp.pFrom = szSrcFolder;        /*源目录，必须以2个\0结尾*/
		FileOp.pTo = szDestFolder;          /*目的目录，必须以2个\0结尾*/    
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
			MessageBox(L"未选择解决方案路径");
			break;
		}
		CStringW strSoluName =  m_pSoluNameEdit->GetWindowText();
		if (strSoluName.IsEmpty())
		{
			MessageBox(L"未选择解决方案名字");
			break;
		}
		if (strSoluPath.Right(1)!=L"\\")
		{
			strSoluPath += L"\\";
		}

		CStringW strSolu = strSoluPath + strSoluName;
		if (PathFileExists(strSolu))
		{
			MessageBox(L"解决方案文件夹已存在，请重新选择");
			break;
		}

		CStringW strProjName = m_pProjNameEdit->GetWindowText();
		if (strProjName.IsEmpty())
		{
			MessageBox(L"未选择项目工程名字");
			break;
		}

		// 拷贝文件夹过去
		wchar_t szSrcPath[MAX_PATH] = {0};
		DM::GetRootFullPath(L".\\YYYY",szSrcPath,MAX_PATH);
		if (false == CopyDirectory(szSrcPath,strSolu))
		{
			MessageBox(L"创建解决方案失败");
			break;
		}

		
		{// 修改MAKELIST1
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
		

		// 修改XXXX文件夹名
		CStringW strXXXXDir = strSolu + L"\\XXXX";
		CStringW strProjDir = strSolu + L"\\";strProjDir += strProjName;
		MoveFile(strXXXXDir,strProjDir);

		// 修改XXXX.cpp
		CStringW strXXXXCpp = strProjDir + L"\\src\\XXXX.cpp";
		CStringW strProjCpp = strProjDir + L"\\src\\";strProjCpp += strProjName; strProjCpp += L".cpp";
		MoveFile(strXXXXCpp,strProjCpp);

		{// 修改MAKELIST2
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
		MessageBox(L"创建解决方案成功");
	} while (false);
	return iErr;
}
