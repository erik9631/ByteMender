//
// Created by erik9 on 4/28/2024.
//
#include <Windows.h>
#include "Memory.h"

#include <stdexcept>
#include "utils/Utils.h"
using namespace memory;

unsigned char *memory::CreateDetour(unsigned char *startAddress, unsigned char *newAddress) {
    unsigned char jmpPatch[] = {0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90};
    auto** jmpAddressParam = reinterpret_cast<unsigned char**>(jmpPatch + 6);
    *jmpAddressParam = newAddress;

    auto jmpPatchSize = ArraySize(jmpPatch);

    DWORD oldProtect;
    if (!VirtualProtect(startAddress, jmpPatchSize, PAGE_EXECUTE_READWRITE, &oldProtect)) {
        throw std::runtime_error("Failed to change memory protection");
    }
    memcpy(startAddress, jmpPatch, jmpPatchSize);
    VirtualProtect(startAddress, jmpPatchSize, oldProtect, &oldProtect);
    return startAddress + jmpPatchSize;
}

void memory::PatchMemory(unsigned char *address, const datatypes::Patch &patch) {
    auto* continueAddress = CreateDetour(address, patch.patchAddr);
    auto** patchReturnAddr = reinterpret_cast<unsigned char**> (patch.patchAddr + patch.size - 8);
    *patchReturnAddr = continueAddress;
}
