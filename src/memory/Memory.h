//
// Created by erik9 on 4/28/2024.
//

#ifndef UTILS_H
#define UTILS_H
#include <string>
#include "datatypes/Patch.h"

namespace memory {
    void* FindPattern(const unsigned char* pattern);

    void CreateDetour(void* startAddress, void* newAddress);

    /// Last 4 or 8 bytes of the patch should be 0x90 (NOP) and will be replaced with the return address
    void CreatePatch(void* address, void* returnAddress, const datatypes::Patch& patch);

    datatypes::Patch LoadPatch(const std::wstring& path);
}


#endif //UTILS_H
