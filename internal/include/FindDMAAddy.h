#pragma once
#include<Windows.h>
#include<vector>
uintptr_t FindDMAAddy(uintptr_t BaseModuleAddress, std::vector<unsigned int>offset);