//
// Created by erik9 on 5/18/2024.
//
#include <catch_amalgamated.hpp>

#include "datatypes/PatchDescriptor.h"

TEST_CASE("PatchLoader YAML test", "[PatchLoaderYaml]") {
    auto descriptor = byteMender::datatypes::LoadPatchDescriptor<unsigned char>("files/patch1/loadablePatch.yaml");
    unsigned char parsedPattern[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00, 0x1A, 0x47, 0x00, 0xD7, 0xAE, 0x1A, 0x2F, 0xE3, 0x00, 0x00, 0x00, 0x2A};

    REQUIRE(descriptor.name == "loadablePatch.bin");
    REQUIRE(descriptor.continueAddrOffset == 0x0);
    REQUIRE(descriptor.relative == true);
    REQUIRE(descriptor.pattern->size == byteMender::utils::ArraySize(parsedPattern));
    for (size_t i = 0; i < descriptor.pattern->size; i++) {
        REQUIRE(descriptor.pattern->data[i] == parsedPattern[i]);
    }
}