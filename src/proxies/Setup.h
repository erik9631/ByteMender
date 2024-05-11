//
// Created by erik9 on 5/11/2024.
//

#ifndef SETUP_H
#define SETUP_H
#include <Windows.h>
#include "memory/Memory.h"
namespace proxies {
    static volatile uint16_t volatileWord;
    static void CALL_DUMMY() { volatileWord = 0; }
    // Proxy header generated for version.dll (64 bit)
    static_assert(sizeof(void*) == 8, "The proxied DLL must match the architecture of the proxy DLL");

    struct Export
    {
        void* addr;
        const char* name;
    };

    template <int T>
    struct ExportDir
    {
        Export exports[T]{};
        HMODULE originalDll{};
    };

    template <int T>
    static void Setup(const ExportDir<T>& exportDir) {

        for (auto& entry : exportDir.exports) {
            auto funcAddr = static_cast<unsigned char*>(entry.addr);
            #ifdef _DEBUG
            if (*funcAddr == 0xE9) //If we have a jmp instruction and we have debug, then we in the symbol table
            {
                int jmpOffset = *reinterpret_cast<int*>(funcAddr + 1); // Skip the jmp, take the jmp offset
                funcAddr += jmpOffset + 5; // Add the offset and the size of the jmp instruction
            }
            #endif

            auto jmpAddr = reinterpret_cast<unsigned char *>(GetProcAddress(exportDir.originalDll, entry.name));
            memory::CreateDetour(funcAddr, jmpAddr);
        }
        CloseHandle(exportDir.originalDll);
    }
}


#endif //SETUP_H
