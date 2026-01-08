#include"mem.h"
#include"FindProcessID.h"
#include"GetBaseModuleAddress.h"
#include"FindDMAAddy.h"
#include<iostream>
int main()
{
	DWORD ProcessID;
	uintptr_t BaseModuleAddress;
	uintptr_t PlayerLocalEntity;
	uintptr_t PlayerHealthAddress;
	bool UseRecoil = false;
	bool InfintyBollet = false;
	bool InfintyHealth = true;

	ProcessID = FindProcessID(L"ac_client.exe");
	if (ProcessID != NULL)
	{

		std::cout << "Process ID : " << ProcessID << '\n';

		HANDLE Hprocess = OpenProcess(PROCESS_ALL_ACCESS, false, ProcessID);
				

		BaseModuleAddress = GetBaseModuleAddress(ProcessID, L"ac_client.exe");
		
		std::cout << "Base Moudle Address : " <<std::hex << BaseModuleAddress << '\n';

		PlayerLocalEntity = BaseModuleAddress + 0x10F4F4;
		std::cout << std::hex << "Player Entity Pointer Address " << PlayerLocalEntity << '\n';

		PlayerHealthAddress = FindDMAAddy(Hprocess, PlayerLocalEntity, { 0xF8 });
		std::cout << std::hex << "Player Health Address " << PlayerHealthAddress << '\n';

		DWORD exit;
		while (GetExitCodeProcess(Hprocess, &exit) && exit == STILL_ACTIVE)
		{
			if (GetAsyncKeyState(VK_NUMPAD7)&1)
			{
				UseRecoil = !UseRecoil;
				if (UseRecoil==false)
				{
					std::cout << "Not Use No Recoil Hack " << '\n';
					mem::PatchEX((BYTE*)(BaseModuleAddress + 0x63786), (BYTE*)"\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2", 10, Hprocess);
				}
				else
				{
					std::cout << "Use Recoil Hack " << '\n';
					mem::NopEX((BYTE*)(BaseModuleAddress + 0x63786), 10, Hprocess);
				}

			}

			if (GetAsyncKeyState(VK_NUMPAD8) & 1)
			{
				InfintyBollet = !InfintyBollet;
				if (InfintyBollet == false)
				{
					mem::PatchEX((BYTE*)(BaseModuleAddress + 0x637E9), (BYTE*)"\xFF\x0E", 2, Hprocess);
				}
				else
				{
					mem::NopEX((BYTE*)(BaseModuleAddress + 0x637E9), 2, Hprocess);
				}

			}


			if (GetAsyncKeyState(VK_NUMPAD9) & 1)
			{
				InfintyHealth = !InfintyHealth;
				if (InfintyHealth == true)
				{
					std::cout << "Use Infinity Health Hack " << '\n';
				}
				else
				{
					std::cout << "Not Use Infinity Health Hack " << '\n';
				}
				
			}
			int health = 999;
			if (InfintyHealth == true)
			{
				mem::PatchEX((BYTE*)(PlayerHealthAddress),(BYTE*)&health, sizeof(health), Hprocess);
			}
			Sleep(10);
		}


	}
	else
	{
		std::cout << "Can't find Process ID of ac_client.exe " << '\n';
	}

	return 0;
}

