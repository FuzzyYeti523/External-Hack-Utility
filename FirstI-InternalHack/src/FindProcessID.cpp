#include"pch.h"
#include<FindProcessID.h>
DWORD FindProcessID(const wchar_t* ProcessName)
{
	DWORD ProcessID = 0;
	HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,NULL);
	if (hsnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 ProcessEntry;
		ProcessEntry.dwSize = sizeof(ProcessEntry);
		if (Process32First(hsnap, &ProcessEntry))
		{
			do
			{
				if (!_wcsicmp(ProcessName, ProcessEntry.szExeFile))
				{
					ProcessID = ProcessEntry.th32ProcessID;
					return ProcessID;
				}
			}

			while (Process32Next(hsnap, &ProcessEntry));
		}
	}
	CloseHandle(hsnap);
	return ProcessID;

}