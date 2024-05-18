//
// Created by erik9 on 5/18/2024.
//

#pragma once
#include <memory>

#include "DynArray.h"
#include "Patch.h"
#include  <yaml-cpp/yaml.h>

#include "utils/Utils.h"

namespace byteMender::datatypes {
    template<typename T>
    struct PatchDescriptor {
        std::unique_ptr<DynArray<T>> pattern = nullptr;
        unsigned long long continueAddrOffset = 0;
        bool relative = true;
        std::unique_ptr<Patch> patch = nullptr;
    };

    template<typename T>
    PatchDescriptor<T> LoadPatchDescriptor(const std::string &path) {
        auto node = YAML::LoadFile(path+"descriptor.yaml");
        PatchDescriptor<T> descriptor;
        descriptor.patch = std::make_unique<Patch>(std::move(LoadPatch(path+"patch.bin")));
        auto pattern = node["patch"]["pattern"].as<std::string>();
        descriptor.pattern = utils::PatternToBytes<unsigned char>(pattern);
        descriptor.relative = node["patch"]["relative"].as<bool>();
        descriptor.continueAddrOffset = node["patch"]["continueAddrOffset"].as<unsigned long long>();
        return descriptor;
    }
}
