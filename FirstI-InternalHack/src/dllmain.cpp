// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include<iostream>
#include<Windows.h>
#include<TlHelp32.h>
#include"mem.h"

DWORD WINAPI HackThread(HMODULE module)
{
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << "OG for a fee, stay sippin' fam\n";

    uintptr_t ModuleAdress = (uintptr_t)GetModuleHandle(L"ac_client.exe");
    uintptr_t PlayerAddress = ModuleAdress + 0x10F4F4;
   
    uintptr_t PlayerHealthAddress = FindDMAAddy(PlayerAddress, { 0xF8 });
   // uintptr_t PlayerAmmoAddress = FindDMAAddy(PlayerAddress, { 0xF8 });

    bool bheath = false;
    bool bammo = false;
    bool brecoil = false;

    int health = 999;
    while (true)
    {
        if (GetAsyncKeyState(VK_NUMPAD7) & 1)
        {
            brecoil = !brecoil;
            if (brecoil == false)
            {
                std::cout << "Recoil off " << '\n';
                mem::PatchEX((BYTE*)(ModuleAdress + 0x63786), (BYTE*)"\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2", 10);
            }
            else
            {
                std::cout << "Recoil on " << '\n';
                mem::NopEX((BYTE*)(ModuleAdress + 0x63786),10);
            }
        }
        if (GetAsyncKeyState(VK_NUMPAD8) & 1)
        {
            bheath = !bheath;
            if (bheath == false)
            {
                uintptr_t* player_health = (uintptr_t*)(PlayerHealthAddress);
                *(player_health) = 999;
            }
            else
            {
                uintptr_t* player_health = (uintptr_t*)(PlayerHealthAddress);
                *(player_health) = 10;
            }

        }
        if (GetAsyncKeyState(VK_NUMPAD9) & 1)
        {

        }
    }
}

BOOL APIENTRY DllMain(HMODULE hModule,DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}