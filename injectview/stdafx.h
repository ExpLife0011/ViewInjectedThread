// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <string>
#include <iostream>
#include <TlHelp32.h>
#include <iomanip>
#include <psapi.h>
#include <winternl.h>'
#include <vector>



// TODO: reference additional headers your program requires here



//defines for Native calls
#define ThreadQuerySetWin32StartAddress 9
#define ProcessProtectionInformation 61

#define DEBUG

//typedefs

typedef struct _PROCESS_BASIC_INFORMATION_WOW64 {
	PVOID Reserved1[2];
	PVOID64 PebBaseAddress;
	PVOID Reserved2[4];
	ULONG_PTR UniqueProcessId[2];
	PVOID Reserved3[2];
} PROCESS_BASIC_INFORMATION_WOW64;

typedef struct RTL_USER_PROCESS_PARAMETERS_I
{
	BYTE Reserved1[16];
	PVOID Reserved2[10];
	UNICODE_STRING ImagePathName;
	UNICODE_STRING CommandLine;
};

typedef struct PEB_INTERNAL
{
	BYTE Reserved1[2];
	BYTE BeingDebugged;
	BYTE Reserved2[1];
	PVOID Reserved3[2];
	struct PEB_LDR_DATA* Ldr;
	RTL_USER_PROCESS_PARAMETERS_I* ProcessParameters;
	BYTE Reserved4[104];
	PVOID Reserved5[52];
	struct PS_POST_PROCESS_INIT_ROUTINE* PostProcessInitRoutine;
	BYTE Reserved6[128];
	PVOID Reserved7[1];
	ULONG SessionId;
};

typedef struct _PROCESS_EXTENDED_BASIC_INFORMATION_WOW64
{
	SIZE_T Size; // set to sizeof structure on input
	PROCESS_BASIC_INFORMATION_WOW64 BasicInfo;
	union
	{
		ULONG Flags;
		struct
		{
			ULONG IsProtectedProcess : 1;
			ULONG IsWow64Process : 1;
			ULONG IsProcessDeleting : 1;
			ULONG IsCrossSessionCreate : 1;
			ULONG IsFrozen : 1;
			ULONG IsBackground : 1;
			ULONG IsStronglyNamed : 1;
			ULONG IsSecureProcess : 1;
			ULONG IsSubsystemProcess : 1;
			ULONG SpareBits : 23;
		};
	};
} PROCESS_EXTENDED_BASIC_INFORMATION_WOW64, *PPROCESS_EXTENDED_BASIC_INFORMATION_WOW64;

typedef struct _PROCESS_EXTENDED_BASIC_INFORMATION
{
	SIZE_T Size; // set to sizeof structure on input
	PROCESS_BASIC_INFORMATION BasicInfo;
	union
	{
		ULONG Flags;
		struct
		{
			ULONG IsProtectedProcess : 1;
			ULONG IsWow64Process : 1;
			ULONG IsProcessDeleting : 1;
			ULONG IsCrossSessionCreate : 1;
			ULONG IsFrozen : 1;
			ULONG IsBackground : 1;
			ULONG IsStronglyNamed : 1;
			ULONG IsSecureProcess : 1;
			ULONG IsSubsystemProcess : 1;
			ULONG SpareBits : 23;
		};
	};
} PROCESS_EXTENDED_BASIC_INFORMATION, *PPROCESS_EXTENDED_BASIC_INFORMATION;

//Function Pointer Definitions
typedef NTSTATUS(WINAPI *NtQueryThreadPointer)(HANDLE, LONG, PVOID, ULONG, PULONG);
typedef NTSTATUS(NTAPI *NtQueryProcessInformationPointer)(HANDLE, PROCESSINFOCLASS, PVOID, ULONG, PULONG);
typedef ULONG(NTAPI* RtlNtStatusToDosErrorPtr)(NTSTATUS);

//others
#define Padding 30