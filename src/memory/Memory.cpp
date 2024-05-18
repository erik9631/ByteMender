//
// Created by erik9 on 4/28/2024.
//
#include <Windows.h>
#include "Memory.h"

#include <stdexcept>
#include "utils/Utils.h"
using namespace byteMender;

/**
 * Creates a detour at the startAddress that jumps to newAddress
 * @param startAddress address where the detour will be created
 * @param newAddress address where the detour will jump to
 * @return the address right after the detour jmp instruction
 */
unsigned char* memory::CreateDetour(unsigned char *startAddress, unsigned char *newAddress) {
    unsigned char jmpPatch[] = {0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    auto** jmpAddressParam = reinterpret_cast<unsigned char**>(jmpPatch + 6);
    *jmpAddressParam = newAddress;

    auto jmpPatchSize = byteMender::utils::ArraySize(jmpPatch);

    DWORD oldProtect;
    if (!VirtualProtect(startAddress, jmpPatchSize, PAGE_EXECUTE_READWRITE, &oldProtect)) {
        throw std::runtime_error("Failed to change memory protection");
    }
    memcpy(startAddress, jmpPatch, jmpPatchSize);
    VirtualProtect(startAddress, jmpPatchSize, oldProtect, &oldProtect);
    return startAddress + jmpPatchSize;
}

/**
 *
 * @param address address where detour will be created
 * @param patch patch to be applied.
 * @param continueAddrOffset offset from right after the detour jmp to the address where the execution should continue. At
 *                           0 the execution will continue right after the detour jmp instruction.
 * @param relative if true the continueAddrOffset will be relative to the addr right after the jmp instruction, otherwise it will be an absolute addr
 */
void memory::PatchMemory(unsigned char *address, const datatypes::Patch &patch, unsigned long long continueAddrOffset, bool relative) {
    unsigned char* continueAddress;
    if (relative)
        continueAddress = CreateDetour(address, patch.patchAddr) + continueAddrOffset;
    else
        continueAddress = reinterpret_cast<unsigned char *>(continueAddrOffset);

    auto** patchReturnAddr = reinterpret_cast<unsigned char**> (patch.patchAddr + patch.size - 8);
    *patchReturnAddr = continueAddress;
}
