#include <Windows.h>
//#define __DEBUG FALSE

// author - saurux | 2023
// discord: _saurux

#include <Streams/CGeneralStream.hpp>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD64 dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH) {
        //AllocConsole();
        //freopen("CONOUT$", "w", stdout);

        //std::cout << GetCommandLineA() << std::endl;

        CGeneralStream::Begin();
    }
    return TRUE;
}

