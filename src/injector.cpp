#include "pch.h"
#include "hook.h"
#include "config.h"

extern "C" __declspec(dllexport) VOID DummyExport() {}

char* g_sServerAddress = nullptr;
long g_nServerPort = 0;

void ProcessCommandLine() {
    char sAddress[16];
    long nPort;
    if (sscanf_s(GetCommandLineA(), "%s %d", sAddress, sizeof(sAddress), &nPort) == 2) {
        g_sServerAddress = reinterpret_cast<char*>(malloc(strlen(sAddress) + 1));
        strcpy_s(g_sServerAddress, strlen(sAddress) + 1, sAddress);
        g_nServerPort = nPort;
    }
}

void InitConsole() {
    AllocConsole();
    FILE* stream;
    freopen_s(&stream, "CONOUT$", "w", stdout);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    InitConsole();  // Creates a console window for debugging

    switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hinstDLL);
        ProcessCommandLine();
        AttachSystemHooks();
        break;
    case DLL_PROCESS_DETACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    }
    return TRUE;
}