//
// Created by erik9 on 4/28/2024.
//

#include "Patch.h"
#include <fstream>

datatypes::Patch datatypes::LoadPatch(const std::wstring &path) {
    Patch patch{};
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    file.seekg(0, std::ios::end);
    auto size = file.tellg();
    file.seekg(0, std::ios::beg);

    file.read(reinterpret_cast<char *>(patch.patch), size);
    patch.size = size;
    return patch;
}
