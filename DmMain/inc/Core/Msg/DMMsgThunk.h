//-------------------------------------------------------
// Copyright (c) DuiMagic
// All rights reserved.
// 
// File Name: DMMsgThunk.h 
// File Des:�˴�������atl:atlstdthunk.h����Ӧԭ��_stdcallthunk
// File Summary: 
// Cur Version: 1.0
// Author:
// Create Data:
// History:
// 		<Author>	<Time>		<Version>	  <Des>
//      guoyou		2015-1-11	1.0			
//-------------------------------------------------------
#pragma once

namespace DM
{
#if defined(_M_IX86)
	#pragma pack(push, 1)
	/// <summary>
	///		thunk��������hwnd͵����thisָ�룬�Ӷ�ʵ��ȫ�ֺ����л������Ա����
	/// </summary>
	class DM_EXPORT DMMsgThunk
	{
	public:
		void Init(DWORD_PTR proc, void* pThis);	
		void* GetCodeAddress();
	public:
		DWORD			m_mov;		// 4���ֽ�
		DWORD			m_this;
		BYTE			m_jmp;
		DWORD			m_relproc;
	};
	#pragma pack(pop)
#elif defined(_M_AMD64)
	#pragma pack(push,2)
	class DM_EXPORT DMMsgThunk
	{
	public:
		void Init(DWORD_PTR proc, void* pThis);	
		void* GetCodeAddress();
	public:
		USHORT			RcxMov;    // mov rcx, pThis
		ULONG64			RcxImm;    // 
		USHORT			RaxMov;    // mov rax, target
		ULONG64			RaxImm;    //
		USHORT			RaxJmp;    // jmp target
	};
	#pragma pack(pop)
#endif
	/// <summary>
	///		thunk����,Ҫ������������ڣ����Բ���Ϊ����ģʽ
	/// </summary>
	class DM_EXPORT DMMsgThunkTool
	{
	public:
		DMMsgThunkTool();
		virtual~DMMsgThunkTool();
	public:
		bool MsgThunkInit();										///< thunk��ʼ��,����thunk��
		bool MsgThunkRun(HWND hWnd, DWORD_PTR proc, PVOID pThis);	///< ִ��thunk
		void MsgThunkUnInit();					
		PVOID MsgThunkGetCodeAddress();

	protected:
		HANDLE                m_hHeap;
		DMMsgThunk            *m_pThunk;
	};	


}//namespace DM