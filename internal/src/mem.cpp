#include "mem.h"

void mem::PatchEX(BYTE *Destination, BYTE *Start, unsigned int size)
{
    DWORD oldprotect;
    VirtualProtect(Destination, size, PAGE_EXECUTE_READWRITE, &oldprotect);
    memcpy(Destination, Start, size);
    VirtualProtect(Destination, size, oldprotect, &oldprotect);
}

void mem::NopEX(BYTE *Destination, unsigned int size)
{
    DWORD oldprotect;
    VirtualProtect(Destination, size, PAGE_EXECUTE_READWRITE, &oldprotect);
    memset(Destination, 0x90, size);
    VirtualProtect(Destination, size, oldprotect, &oldprotect);
}