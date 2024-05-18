//
// Created by erik9 on 5/18/2024.
//
#include <catch_amalgamated.hpp>

#include "utils/Utils.h"

TEST_CASE("Pattern parser test", "[patteParserTest]") {
    auto pattern = "AA BB CC DD EE FF ?? 1A 47 ?? D7 AE 1A 2F E3 ?? ?? ?? 2A";
    unsigned char parsedPattern[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00, 0x1A, 0x47, 0x00, 0xD7, 0xAE, 0x1A, 0x2F, 0xE3, 0x00, 0x00, 0x00, 0x2A};
    auto parsedArray = byteMender::utils::PatternToBytes<unsigned char>(pattern, 0);
    REQUIRE(parsedArray.size == byteMender::utils::ArraySize(parsedPattern));

    for (size_t i = 0; i < parsedArray.size; i++) {
        REQUIRE(parsedArray.data[i] == parsedPattern[i]);
    }
}