//
// Created by erik9 on 5/11/2024.
//

#ifndef VERSION_H
#define VERSION_H
#define WIN32_LEAN_AND_MEAN
#include <cstdint>
#include <Windows.h>
#include "memory/Memory.h"
namespace proxies::version {
    struct Export
    {
        void* addr;
        const char* name;
    };

    #pragma optimize("", off)
    static volatile uint16_t volatileWord;
    static void CALL_DUMMY() { volatileWord = 0; }

    // Proxy header generated for version.dll (64 bit)
    static_assert(sizeof(void*) == 8, "The proxied DLL must match the architecture of the proxy DLL");
    inline HMODULE hOriginalDLL = LoadLibraryA("C:/Windows/System32/version.dll");

    // #1: GetFileVersionInfoA
    void DUMMY0()
    {
        #pragma comment(linker, "/EXPORT:GetFileVersionInfoA=" __FUNCDNAME__)
        CALL_DUMMY();
        volatileWord = 0x9090909090909090;
    }

    // #2: GetFileVersionInfoByHandle
    void DUMMY1()
    {
        #pragma comment(linker, "/EXPORT:GetFileVersionInfoByHandle=" __FUNCDNAME__)
        CALL_DUMMY();
        volatileWord = 0x9090909090909090;
    }


    // #3: GetFileVersionInfoExA
    void DUMMY2()
    {
        #pragma comment(linker, "/EXPORT:GetFileVersionInfoExA=" __FUNCDNAME__)
        CALL_DUMMY();
        volatileWord = 0x9090909090909090;
    }


    // #4: GetFileVersionInfoExW
    void DUMMY3()
    {
        #pragma comment(linker, "/EXPORT:GetFileVersionInfoExW=" __FUNCDNAME__)
        CALL_DUMMY();
        volatileWord = 0x9090909090909090;
    }


    // #5: GetFileVersionInfoSizeA
    void DUMMY4()
    {
        #pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeA=" __FUNCDNAME__)
        CALL_DUMMY();
        volatileWord = 0x9090909090909090;
    }


    // #6: GetFileVersionInfoSizeExA
    void DUMMY5()
    {
        #pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeExA=" __FUNCDNAME__)
        CALL_DUMMY();
        volatileWord = 0x9090909090909090;
    }


    // #7: GetFileVersionInfoSizeExW
    void DUMMY6()
    {
        #pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeExW=" __FUNCDNAME__)
        CALL_DUMMY();
        volatileWord = 0x9090909090909090;
    }


    // #8: GetFileVersionInfoSizeW
    void DUMMY7()
    {
        #pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeW=" __FUNCDNAME__)
        CALL_DUMMY();
        volatileWord = 0x9090909090909090;
    }
    // #9: GetFileVersionInfoW
    void DUMMY8()
    {
        #pragma comment(linker, "/EXPORT:GetFileVersionInfoW=" __FUNCDNAME__)
        CALL_DUMMY();
        volatileWord = 0x9090909090909090;
    }

    // #10: VerFindFileA
    void DUMMY9()
    {
        #pragma comment(linker, "/EXPORT:VerFindFileA=" __FUNCDNAME__)
        CALL_DUMMY();
        volatileWord = 0x9090909090909090;
    }

    // #11: VerFindFileW
    void DUMMY10()
    {
    #pragma comment(linker, "/EXPORT:VerFindFileW=" __FUNCDNAME__)
        CALL_DUMMY();
        volatileWord = 0x9090909090909090;
    }

    // #12: VerInstallFileA
    void DUMMY11()
    {
        #pragma comment(linker, "/EXPORT:VerInstallFileA=" __FUNCDNAME__)
        CALL_DUMMY();
        volatileWord = 0x9090909090909090;
    }


    // #13: VerInstallFileW
    void DUMMY12()
    {
        #pragma comment(linker, "/EXPORT:VerInstallFileW=" __FUNCDNAME__)
        CALL_DUMMY();
        volatileWord = 0x9090909090909090;
    }

    // #14: VerLanguageNameA
    void DUMMY13()
    {
        #pragma comment(linker, "/EXPORT:VerLanguageNameA=" __FUNCDNAME__)
        CALL_DUMMY();
        volatileWord = 0x9090909090909090;
    }


    // #15: VerLanguageNameW
    void DUMMY14()
    {
        #pragma comment(linker, "/EXPORT:VerLanguageNameW=" __FUNCDNAME__)
        CALL_DUMMY();
        volatileWord = 0x9090909090909090;
    }


    // #16: VerQueryValueA
    void DUMMY15()
    {
        #pragma comment(linker, "/EXPORT:VerQueryValueA=" __FUNCDNAME__)
        CALL_DUMMY();
        volatileWord = 0x9090909090909090;
    }


    // #17: VerQueryValueW
    void DUMMY16()
    {
        #pragma comment(linker, "/EXPORT:VerQueryValueW=" __FUNCDNAME__)
        CALL_DUMMY();
        volatileWord = 0x9090909090909090;
    }

    #pragma optimize("", on)

    static Export exports[] = {
        {DUMMY0, "GetFileVersionInfoA"},
        {DUMMY1, "GetFileVersionInfoByHandle"},
        {DUMMY2, "GetFileVersionInfoExA"},
        {DUMMY3, "GetFileVersionInfoExW"},
        {DUMMY4, "GetFileVersionInfoSizeA"},
        {DUMMY5, "GetFileVersionInfoSizeExA"},
        {DUMMY6, "GetFileVersionInfoSizeExW"},
        {DUMMY7, "GetFileVersionInfoSizeW"},
        {DUMMY8, "GetFileVersionInfoW"},
        {DUMMY9, "VerFindFileA"},
        {DUMMY10, "VerFindFileW"},
        {DUMMY11, "VerInstallFileA"},
        {DUMMY12, "VerInstallFileW"},
        {DUMMY13, "VerLanguageNameA"},
        {DUMMY14, "VerLanguageNameW"},
        {DUMMY15, "VerQueryValueA"},
        {DUMMY16, "VerQueryValueW"}
    };

    static void Setup() {

        for (auto& entry : exports) {
            auto funcAddr = static_cast<unsigned char*>(entry.addr);
            #ifdef _DEBUG
            if (*funcAddr == 0xE9) //If we have a jmp instruction and we have debug, then we in the symbol table
            {
                int jmpOffset = *reinterpret_cast<int*>(funcAddr + 1); // Skip the jmp, take the jmp offset
                funcAddr += jmpOffset + 5; // Add the offset and the size of the jmp instruction
            }
            #endif

            auto jmpAddr = reinterpret_cast<unsigned char *>(GetProcAddress(hOriginalDLL, entry.name));
            memory::CreateDetour(funcAddr, jmpAddr);
        }
		CloseHandle(hOriginalDLL);
    }

}
#endif //VERSION_H
