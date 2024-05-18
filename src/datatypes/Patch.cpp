//
// Created by erik9 on 4/28/2024.
//

#include "Patch.h"
#include <fstream>
#include <windows.h>
using namespace byteMender;

datatypes::Patch::Patch(size_t size): size(size)  {
    unsigned char* executableMemory = static_cast<unsigned char*>(VirtualAlloc(nullptr, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));
    patchAddr = executableMemory;
}

datatypes::Patch::Patch(size_t size, const unsigned char *patchAddr) : Patch(size) {
    memcpy(this->patchAddr, patchAddr, size);
}

datatypes::Patch::~Patch() {
    VirtualFree(patchAddr, size, MEM_RELEASE);
}

datatypes::Patch datatypes::LoadPatch(const std::string &path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);
    Patch patch{size};

    file.read(reinterpret_cast<char *>(patch.patchAddr), size);
    return patch;
}
