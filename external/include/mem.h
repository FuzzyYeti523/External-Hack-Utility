#pragma once
#include<windows.h>
namespace mem
{
	void PatchEX(BYTE* Destination, BYTE* Start, unsigned int, HANDLE hProcess);
	void NopEX(BYTE* Destination,unsigned int, HANDLE hProcess);

}

