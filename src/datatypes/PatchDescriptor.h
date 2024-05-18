//
// Created by erik9 on 5/18/2024.
//

#pragma once
#include <memory>

#include "DynArray.h"
#include "Patch.h"
#include  <yaml-cpp/yaml.h>
#include "utils/Utils.h"
#include <filesystem>

namespace byteMender::datatypes {
    template<typename T>
    struct PatchDescriptor {
        std::unique_ptr<DynArray<T>> pattern = nullptr;
        unsigned long long continueAddrOffset = 0;
        bool relative = true;
        std::unique_ptr<Patch> patch = nullptr;
        std::string name;
    };

    template<typename T>
    PatchDescriptor<T> LoadPatchDescriptor(const std::string &yamlPath) {
        auto node = YAML::LoadFile(yamlPath);

        std::filesystem::path folderPath = std::filesystem::path{yamlPath}.parent_path();

        PatchDescriptor<T> descriptor;
        auto pattern = node["patch"]["pattern"].as<std::string>();
        auto parsedBytes = utils::PatternToBytes<T>(pattern);
        descriptor.pattern = std::move(parsedBytes);
        descriptor.relative = node["patch"]["relative"].as<bool>();
        descriptor.continueAddrOffset = node["patch"]["continueAddrOffset"].as<unsigned long long>();
        descriptor.name = node["patch"]["name"].as<std::string>();

        auto binpath = folderPath / descriptor.name;
        descriptor.patch = std::make_unique<Patch>(LoadPatch(binpath.string()));
        return descriptor;
    }
}
