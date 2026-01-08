#pragma once
#include<windows.h>
namespace mem
{
	void PatchEX(BYTE* Destination, BYTE* Start, unsigned int);
	void NopEX(BYTE* Destination,unsigned int);

}

