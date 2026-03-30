#include"GetBaseModuleAddress.h"
uintptr_t GetBaseModuleAddress(DWORD ProcessID, const wchar_t* ProcessName)
{
	uintptr_t BaseMoudleAddress = 0;
	HANDLE SnapShotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcessID);
	if (SnapShotHandle != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 ModuleEntry;
		ModuleEntry.dwSize = sizeof(ModuleEntry);
		if (Module32First(SnapShotHandle, &ModuleEntry))
		{
			do
			{
				if (!_wcsicmp(ModuleEntry.szModule,ProcessName))
				{
					BaseMoudleAddress = (uintptr_t)(ModuleEntry.modBaseAddr);
					//In c type casting is reinterpret_cast in c++
					break;
				}
			} while (Module32Next(SnapShotHandle, &ModuleEntry));
		}
	}
	CloseHandle(SnapShotHandle);
	return BaseMoudleAddress;
}