//
// Created by erik9 on 4/28/2024.
//

#include "Patch.h"
#include <fstream>
#include <windows.h>

datatypes::Patch::Patch(size_t size) {
    patchAddr = std::make_unique<unsigned char[]>(size);
    this->size = size;
    DWORD oldProtect;
    if (!VirtualProtect(patchAddr.get(), size, PAGE_EXECUTE_READWRITE, &oldProtect)) {
        throw std::runtime_error("Failed to change memory protection");
    }
}

datatypes::Patch datatypes::LoadPatch(const std::wstring &path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    auto size = file.tellg();
    file.seekg(0, std::ios::beg);
    Patch patch{size};

    file.read(reinterpret_cast<char *>(patch.patchAddr.get()), size);
    patch.size = size;

    return patch;
}
