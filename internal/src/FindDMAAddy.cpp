#include"FindDMAAddy.h"
uintptr_t FindDMAAddy(uintptr_t BaseModuleAddress, std::vector<unsigned int> offsets)
{
    uintptr_t addr = BaseModuleAddress;
    for (unsigned int i = 0; i < offsets.size(); ++i)
    {
        addr = *(uintptr_t*)addr;
        addr += offsets[i];
    }
    return addr;
}