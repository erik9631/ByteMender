//
// Created by erik9 on 5/18/2024.
//
#include <catch_amalgamated.hpp>

#include "utils/Utils.h"

TEST_CASE("Pattern parser test", "[patteParserTest]") {
    SECTION("Byte pattern parser test") {
        auto pattern = "AA BB CC DD EE FF ?? 1A 47 ?? D7 AE 1A 2F E3 ?? ?? ?? 2A";
        unsigned char parsedPattern[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00, 0x1A, 0x47, 0x00, 0xD7, 0xAE, 0x1A, 0x2F, 0xE3, 0x00, 0x00, 0x00, 0x2A};
        auto parsedArray = byteMender::utils::PatternToBytes<unsigned char>(pattern, 0);
        REQUIRE(parsedArray.size == byteMender::utils::ArraySize(parsedPattern));

        for (size_t i = 0; i < parsedArray.size; i++) {
            REQUIRE(parsedArray.data[i] == parsedPattern[i]);
        }
    }

    SECTION("WORD pattern parser test") {
        auto pattern = "AABB CCDD EEEE ???? 1A47 ???? D7AE 1A2F E3A1 ???? 2AA0";
        unsigned short parsedPattern[] = {0xAABB, 0xCCDD, 0xEEEE, 0x0000, 0x1A47, 0x0000, 0xD7AE, 0x1A2F, 0xE3A1, 0x0000, 0x2AA0};
        auto parsedArray = byteMender::utils::PatternToBytes<unsigned short>(pattern, 0);
        REQUIRE(parsedArray.size == byteMender::utils::ArraySize(parsedPattern));

        for (size_t i = 0; i < parsedArray.size; i++) {
            REQUIRE(parsedArray.data[i] == parsedPattern[i]);
        }
    }

    SECTION("DWORD pattern parser test") {
        auto pattern = "AABBCCDD EEEEEEEE ???????? 1A471A47 ???????? D7AE1A2F E3A1E3A1 ???????? 2AA02AA0";
        unsigned int parsedPattern[] = {0xAABBCCDD, 0xEEEEEEEE, 0x00000000, 0x1A471A47, 0x00000000, 0xD7AE1A2F, 0xE3A1E3A1, 0x00000000, 0x2AA02AA0};
        auto parsedArray = byteMender::utils::PatternToBytes<unsigned int>(pattern, 0);
        REQUIRE(parsedArray.size == byteMender::utils::ArraySize(parsedPattern));

        for (size_t i = 0; i < parsedArray.size; i++) {
            REQUIRE(parsedArray.data[i] == parsedPattern[i]);
        }
    }

    SECTION("QWORD pattern parser test") {
        auto pattern = "AABBCCDDEEEEEEEE ???????????????? 1A471A471A471A47 ???????????????? D7AE1A2FD7AE1A2F E3A1E3A1E3A1E3A1 ???????????????? 2AA02AA02AA02AA0";
        unsigned long long parsedPattern[] = {0xAABBCCDDEEEEEEEE, 0x0000000000000000, 0x1A471A471A471A47, 0x0000000000000000, 0xD7AE1A2FD7AE1A2F, 0xE3A1E3A1E3A1E3A1, 0x0000000000000000, 0x2AA02AA02AA02AA0};
        auto parsedArray = byteMender::utils::PatternToBytes<unsigned long long>(pattern, 0);
        REQUIRE(parsedArray.size == byteMender::utils::ArraySize(parsedPattern));

        for (size_t i = 0; i < parsedArray.size; i++) {
            REQUIRE(parsedArray.data[i] == parsedPattern[i]);
        }
    }

}