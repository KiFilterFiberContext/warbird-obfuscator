#include <stdio.h>
#include <stdint.h>
#include <Windows.h>

namespace Warbird
{
    enum class Arm64XType
    {

    };

    class CObfuscatorBase;
}

extern "C" __declspec(dllexport) int GetObfuscator( Warbird::CObfuscatorBase** ObfuscatorBase )
{
    printf( "Sussy baka\n" );

    return 0;
}

extern "C" __declspec(dllexport) int CreateObfuscator2( WCHAR* szWbrdCfgFilename, WCHAR* szWbrdSchemaFilename, WCHAR* szWbrdLogFilename, WCHAR* szWbrdSummaryFilename, unsigned long WbrdFlags, Warbird::Arm64XType ArmType, Warbird::CObfuscatorBase** ObfuscatorBase )
{
    printf( "Sussy baka 2\n" );

    return 0;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

