#include "mem.h"

void mem::PatchEX(BYTE* Destination, BYTE* Start, unsigned int size, HANDLE hProcess)
{
	DWORD oldprotect;
	VirtualProtectEx(hProcess, Destination, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	WriteProcessMemory(hProcess, Destination, Start, size, nullptr);
	VirtualProtectEx(hProcess, Destination, size, oldprotect, &oldprotect);
}

void mem::NopEX(BYTE* Destination, unsigned int size, HANDLE hProcess)
{
	BYTE* nopArray = new BYTE[size];
	memset(nopArray, 0x90, size);
	PatchEX(Destination, nopArray, size, hProcess);
	delete[] nopArray;
}
