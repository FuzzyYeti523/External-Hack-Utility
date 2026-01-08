#include "FindDMAAddy.h"
#include"FindDMAAddy.h"
uintptr_t FindDMAAddy(HANDLE ProcessID,uintptr_t BaseModuleAddress, std::vector<unsigned int> offsets)
{
    uintptr_t addr = BaseModuleAddress;
    for (unsigned int i = 0; i < offsets.size(); ++i)
    {
        ReadProcessMemory(ProcessID, (BYTE*)addr, &addr, sizeof(addr), 0);
        addr += offsets[i];
    }
    return addr;
}
