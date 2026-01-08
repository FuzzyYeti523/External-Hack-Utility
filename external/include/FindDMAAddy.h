#pragma once
#include<Windows.h>
#include<vector>
uintptr_t FindDMAAddy(HANDLE ProcessId,uintptr_t BaseModuleAddress, std::vector<unsigned int>offset);
