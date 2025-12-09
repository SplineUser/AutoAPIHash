#pragma once
#include <windows.h>
#include <cstdint>     // <-- REQUIRED FOR uintptr_t
#include <cstring>     // <-- strlen
#include <cwchar>      // <-- _wcsicmp

#define EXPORT_DIRECTORY_INDEX 0

// Cross-compiler version of __readgsqword
static inline uintptr_t ReadGsQword(DWORD offset)
{
    uintptr_t value;

#if defined(_MSC_VER)
    value = __readgsqword(offset);
#else
    __asm__ __volatile__(
        "movq %%gs:(%1), %0"
        : "=r"(value)
        : "r"(offset)
    );
#endif

    return value;
}

DWORD djb2_hash(char* name_of_function) {
    DWORD hash_val = 5381;
    int len_of_func = strlen(name_of_function);
    for (int i = 0; i < len_of_func; i++) {
        hash_val = ((hash_val << 5) + hash_val) + (BYTE)(name_of_function[i]);
    }
    return (DWORD)hash_val;
}

FARPROC ResolveProcByHash(HMODULE hMod, DWORD target_hash) {
    if (!hMod) return NULL;

    BYTE* base = (BYTE*)hMod;
    IMAGE_DOS_HEADER* dos_hdr = (IMAGE_DOS_HEADER*)base;

    if (dos_hdr->e_magic != IMAGE_DOS_SIGNATURE)
        return NULL;

    IMAGE_NT_HEADERS* nt_hdr = (IMAGE_NT_HEADERS*)(base + dos_hdr->e_lfanew);
    DWORD exp_rva = nt_hdr->OptionalHeader.DataDirectory[EXPORT_DIRECTORY_INDEX].VirtualAddress;
    if (!exp_rva) return NULL;

    IMAGE_EXPORT_DIRECTORY* export_dir = (IMAGE_EXPORT_DIRECTORY*)(base + exp_rva);

    DWORD* name_rvas = (DWORD*)(base + export_dir->AddressOfNames);
    WORD* ordinals   = (WORD*)(base + export_dir->AddressOfNameOrdinals);
    DWORD* functions = (DWORD*)(base + export_dir->AddressOfFunctions);

    for (UINT i = 0; i < export_dir->NumberOfNames; i++) {
        char* name_ptr = (char*)(base + name_rvas[i]);
        if (!name_ptr) continue;

        if (djb2_hash(name_ptr) == target_hash) {
            WORD ord = ordinals[i];
            if (ord >= export_dir->NumberOfFunctions) continue;

            DWORD func_rva = functions[ord];
            if (!func_rva) continue;

            FARPROC resolved = (FARPROC)(base + func_rva);
            if (resolved) return resolved;
        }
    }

    return NULL;
}


// ===== PEB STRUCTS =====

typedef struct _UNICODE_STRING32 {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR  Buffer;
} UNICODE_STRING32;

typedef struct _LDR_DATA_TABLE_ENTRY64 {
    LIST_ENTRY InLoadOrderLinks;
    LIST_ENTRY InMemoryOrderLinks;
    LIST_ENTRY InInitializationOrderLinks;
    PVOID      DllBase;
    PVOID      EntryPoint;
    ULONG      SizeOfImage;
    UNICODE_STRING32 FullDllName;
    UNICODE_STRING32 BaseDllName;
} LDR_DATA_TABLE_ENTRY64;

typedef struct _PEB_LDR_DATA64 {
    ULONG      Length;
    BOOLEAN    Initialized;
    PVOID      SsHandle;
    LIST_ENTRY InLoadOrderModuleList;
    LIST_ENTRY InMemoryOrderModuleList;
    LIST_ENTRY InInitializationOrderModuleList;
} PEB_LDR_DATA64;

typedef struct _PEB64 {
    BYTE Reserved1[2];
    BYTE BeingDebugged;
    BYTE Reserved2[1];
    PVOID Reserved3[2];
    PEB_LDR_DATA64* Ldr;
} PEB64;


// ===== FIXED FetchModuleBaseByName() =====

HMODULE FetchModuleBaseByName(const wchar_t* targetModuleName)
{
    PEB64* pebStruct = (PEB64*)ReadGsQword(0x60);
    if (!pebStruct) return NULL;

    PEB_LDR_DATA64* ldrData = pebStruct->Ldr;
    if (!ldrData) return NULL;

    LIST_ENTRY* listHead = &ldrData->InMemoryOrderModuleList;
    LIST_ENTRY* currentNode = listHead->Flink;

    while (currentNode != listHead) {
        LDR_DATA_TABLE_ENTRY64* dataEntry =
            CONTAINING_RECORD(currentNode, LDR_DATA_TABLE_ENTRY64, InMemoryOrderLinks);

        if (_wcsicmp(dataEntry->BaseDllName.Buffer, targetModuleName) == 0)
            return (HMODULE)dataEntry->DllBase;

        currentNode = currentNode->Flink;
    }

    return NULL;
}

typedef LPVOID (WINAPI* mmyVirtualAlloc)(LPVOID, SIZE_T, DWORD, DWORD);
mmyVirtualAlloc myVirtualAlloc = (mmyVirtualAlloc)ResolveProcByHash(FetchModuleBaseByName(L"Kernel32.dll"), 53423);

typedef BOOL (WINAPI* mmyVirtualFree)(LPVOID, SIZE_T, DWORD);
mmyVirtualFree myVirtualFree = (mmyVirtualFree)ResolveProcByHash(FetchModuleBaseByName(L"Kernel32.dll"), 2344234);

