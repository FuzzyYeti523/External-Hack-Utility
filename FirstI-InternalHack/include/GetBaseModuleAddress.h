#include"Windows.h"  //For Windows Api
#include<TlHelp32.h> //For CreateToolhelp32Snapshot, MODULEENTRY32

uintptr_t GetBaseModuleAddress(DWORD ProcessID, const wchar_t* ProcessName);
