//
// Created by erik9 on 4/28/2024.
//
#include <catch_amalgamated.hpp>
#include <fstream>
#include "../src/utils/Profiler.h"
#include "algorithms/KmpSearcher.h"
#include "utils/Utils.h"

TEST_CASE("kmp failure function test 1", "[kmpFailureFunction1]") {
    SECTION("Equal string test") {
        std::string pattern = "ssssssssssssss";
        algorithms::KmpSearcher searcher{pattern.data(), pattern.size()};
        REQUIRE(searcher.GetPatternIndexTable()[0] == 0);
        REQUIRE(searcher.GetPatternIndexTable()[1] == 1);
        REQUIRE(searcher.GetPatternIndexTable()[2] == 2);
        REQUIRE(searcher.GetPatternIndexTable()[3] == 3);
        REQUIRE(searcher.GetPatternIndexTable()[4] == 4);
        REQUIRE(searcher.GetPatternIndexTable()[5] == 5);
        REQUIRE(searcher.GetPatternIndexTable()[6] == 6);
        REQUIRE(searcher.GetPatternIndexTable()[7] == 7);
        REQUIRE(searcher.GetPatternIndexTable()[8] == 8);
        REQUIRE(searcher.GetPatternIndexTable()[9] == 9);
        REQUIRE(searcher.GetPatternIndexTable()[10] == 10);
        REQUIRE(searcher.GetPatternIndexTable()[11] == 11);
        REQUIRE(searcher.GetPatternIndexTable()[12] == 12);
        REQUIRE(searcher.GetPatternIndexTable()[13] == 13);

    }

    SECTION("Complex string test 1") {
        std::string pattern = "erikjerkerikjerkokerkoeokerkoe";
        algorithms::KmpSearcher<char> searcher{pattern.data(), pattern.size()};
        REQUIRE(searcher.GetPatternIndexTable()[0] == 0);
        REQUIRE(searcher.GetPatternIndexTable()[1] == 0);
        REQUIRE(searcher.GetPatternIndexTable()[2] == 0);
        REQUIRE(searcher.GetPatternIndexTable()[3] == 0);
        REQUIRE(searcher.GetPatternIndexTable()[4] == 0);
        REQUIRE(searcher.GetPatternIndexTable()[5] == 1);
        REQUIRE(searcher.GetPatternIndexTable()[6] == 2);
        REQUIRE(searcher.GetPatternIndexTable()[7] == 0);
        REQUIRE(searcher.GetPatternIndexTable()[8] == 1);
        REQUIRE(searcher.GetPatternIndexTable()[9] == 2);
        REQUIRE(searcher.GetPatternIndexTable()[10] == 3);
        REQUIRE(searcher.GetPatternIndexTable()[11] == 4);
        REQUIRE(searcher.GetPatternIndexTable()[12] == 5);
        REQUIRE(searcher.GetPatternIndexTable()[13] == 6);
        REQUIRE(searcher.GetPatternIndexTable()[14] == 7);
        REQUIRE(searcher.GetPatternIndexTable()[15] == 8);
        REQUIRE(searcher.GetPatternIndexTable()[16] == 0);
        REQUIRE(searcher.GetPatternIndexTable()[17] == 0);
        REQUIRE(searcher.GetPatternIndexTable()[18] == 1);
        REQUIRE(searcher.GetPatternIndexTable()[19] == 2);
        REQUIRE(searcher.GetPatternIndexTable()[20] == 0);
        REQUIRE(searcher.GetPatternIndexTable()[21] == 0);
        REQUIRE(searcher.GetPatternIndexTable()[22] == 1);
        REQUIRE(searcher.GetPatternIndexTable()[23] == 0);
        REQUIRE(searcher.GetPatternIndexTable()[24] == 0);
        REQUIRE(searcher.GetPatternIndexTable()[25] == 1);
        REQUIRE(searcher.GetPatternIndexTable()[26] == 2);
        REQUIRE(searcher.GetPatternIndexTable()[27] == 0);
        REQUIRE(searcher.GetPatternIndexTable()[28] == 0);
        REQUIRE(searcher.GetPatternIndexTable()[29] == 1);
    }

    SECTION("Complex string test 2") {
        std::string pattern = "abcdabcdabcedabced";
        algorithms::KmpSearcher<char> searcher{pattern.data(), pattern.size()};
        REQUIRE(searcher.GetPatternIndexTable()[0] == 0);
        REQUIRE(searcher.GetPatternIndexTable()[1] == 0);
        REQUIRE(searcher.GetPatternIndexTable()[2] == 0);
        REQUIRE(searcher.GetPatternIndexTable()[3] == 0);
        REQUIRE(searcher.GetPatternIndexTable()[4] == 1);
        REQUIRE(searcher.GetPatternIndexTable()[5] == 2);
        REQUIRE(searcher.GetPatternIndexTable()[6] == 3);
        REQUIRE(searcher.GetPatternIndexTable()[7] == 4);
        REQUIRE(searcher.GetPatternIndexTable()[8] == 5);
        REQUIRE(searcher.GetPatternIndexTable()[9] == 6);
        REQUIRE(searcher.GetPatternIndexTable()[10] == 7);
        REQUIRE(searcher.GetPatternIndexTable()[11] == 0);
        REQUIRE(searcher.GetPatternIndexTable()[12] == 0);
        REQUIRE(searcher.GetPatternIndexTable()[13] == 1);
        REQUIRE(searcher.GetPatternIndexTable()[14] == 2);
        REQUIRE(searcher.GetPatternIndexTable()[15] == 3);
        REQUIRE(searcher.GetPatternIndexTable()[16] == 0);
        REQUIRE(searcher.GetPatternIndexTable()[17] == 0);
    }


    SECTION("1 char string test") {
        std::string pattern = "a";
        algorithms::KmpSearcher<char> searcher{pattern.data(), pattern.size()};
        REQUIRE(searcher.GetPatternIndexTable()[0] == 0);
    }

}

TEST_CASE("KMP search test 1", "[kmpSearch1]") {
    SECTION("Equal string test") {
        std::string pattern = "ssssssssssssss";
        algorithms::KmpSearcher<char> searcher{pattern.data(), pattern.size()};
        std::string data = "ssssssssssssss";
        const auto results = searcher.Search(data.data(), data.size());

        auto resultString = std::string(results.at(0).data);

        REQUIRE(resultString.size() == 14);
        REQUIRE(resultString == "ssssssssssssss");
    }

    SECTION("Simple string test") {
        std::string pattern = "ababbcbc";
        algorithms::KmpSearcher<char> searcher{pattern.data(), pattern.size()};
        std::string data = "abababbcbc";
        const auto results = searcher.Search(data.data(), data.size());

        auto resultString = std::string(results.at(0).data, pattern.size());

        REQUIRE(resultString.size() == pattern.size());
        REQUIRE(resultString == "ababbcbc");
    }

    SECTION("Complex string test") {
        std::string pattern = "erikjerkerikjerkokerkoeokerkoe";
        algorithms::KmpSearcher<char> searcher{pattern.data(), pattern.size()};
        std::string data = "erikjerkoesdxerikjerkokererikjererikjerkerikjerkokerkoeokerkoekokerkoekoe";
        const auto results = searcher.Search(data.data(), data.size());

        auto resultString = std::string(results.at(0).data, pattern.size());

        REQUIRE(resultString.size() == pattern.size());
        REQUIRE(resultString == "erikjerkerikjerkokerkoeokerkoe");
    }

    SECTION("Complex string test multiple") {
        std::string pattern = "erikjerkerikjerkokerkoeokerkoe";
        algorithms::KmpSearcher<char> searcher{pattern.data(), pattern.size()};
        std::string data = "erikjererikjerkerikjerkokerkoeokerkoekoesdxerikjerkokererikjererikjerkerikjerkokerkoeokerkoekokerkoekoeerikjerkerikjerkokerkoeokerkoe";
        const auto results = searcher.Search(data.data(), data.size());

        auto resultString1 = std::string(results.at(0).data, pattern.size());
        auto resultString2 = std::string(results.at(1).data, pattern.size());
        auto resultString3 = std::string(results.at(2).data, pattern.size());

        REQUIRE(resultString1.size() == pattern.size());
        REQUIRE(resultString1 == "erikjerkerikjerkokerkoeokerkoe");
        REQUIRE(resultString2.size() == pattern.size());
        REQUIRE(resultString2 == "erikjerkerikjerkokerkoeokerkoe");
        REQUIRE(resultString3.size() == pattern.size());
        REQUIRE(resultString3 == "erikjerkerikjerkokerkoeokerkoe");
    }
}

TEST_CASE("KMP search test 2", "[kmpSearch2]") {
    SECTION("Equal int test") {
        int pattern[8] = {1,1,1,1,1,1,1,1};
        int data[8] = {1,1,1,1,1,1,1,1};
        algorithms::KmpSearcher<int> searcher{static_cast<const int*>(pattern), 8};
        const auto results = searcher.Search(data, 8);

        auto result = results.at(0);

        for (int i = 0; i < 8; ++i) {
            REQUIRE(result.data[i] == 1);
        }
    }

    SECTION("Equal int test complex") {
        int pattern[] = {1,5,9,1,5,9,181,1,5,181,1,5};
        int data[] = {1,5,9,2,7,8,4,5, 7, 8, 1,8,1,1,5,9,1,5,9,181,1,5,181,1,5,154,854,84};
        algorithms::KmpSearcher<int> searcher{static_cast<const int*>(pattern), ArraySize(pattern)};
        const auto results = searcher.Search(data, ArraySize(data));

        auto result = results.at(0);
        REQUIRE(result.data[0] == 1);
        REQUIRE(result.data[1] == 5);
        REQUIRE(result.data[2] == 9);
        REQUIRE(result.data[3] == 1);
        REQUIRE(result.data[4] == 5);
        REQUIRE(result.data[5] == 9);
        REQUIRE(result.data[6] == 181);
        REQUIRE(result.data[7] == 1);
        REQUIRE(result.data[8] == 5);
        REQUIRE(result.data[9] == 181);
        REQUIRE(result.data[10] == 1);
        REQUIRE(result.data[11] == 5);

    }

}

TEST_CASE("KMP wildcard search test", "[kmpWildCardSearch]") {
    unsigned char searchData[] = {1, 7, 1, 1, 4, 7, 4, 7, 8, 7, 4, 54, 45, 124, 41, 74, 41, 8, 90, 81, 74, 85, 41, 4, 7,};
    unsigned char pattern [] = {1, 1, 4, 7, 0, 0, 0, 7, 4, 54, 45};

    unsigned char expectedResult [] = {1, 1, 4, 7, 4, 7, 8, 7, 4, 54, 45};

    auto searcher = algorithms::KmpSearcher{pattern, ArraySize(pattern)};

    auto results = searcher.Search(searchData, ArraySize(searchData));

    REQUIRE(results.size() == 1);
    auto result = results.at(0);

    for (int i = 0; i < ArraySize(pattern); ++i) {
        REQUIRE(result.data[i] == expectedResult[i]);
    }

}

TEST_CASE("KMP binnary file search test", "[kmpBinnary]") {
    unsigned char pattern[] = {0x01, 0x82, 0x2F, 0xFF, 0x74, 0xF2};

    SECTION("5MB binnary test") {
        std::ifstream binnaryFile{"files/5mb.bin", std::ios::binary};

        REQUIRE(binnaryFile.is_open());

        binnaryFile.seekg(0, std::ios::end);
        size_t binnaryFileSize = binnaryFile.tellg();
        binnaryFile.seekg(0, std::ios::beg);
        auto* binnaryFileBuffer = new unsigned char[binnaryFileSize];
        binnaryFile.read(reinterpret_cast<char*>(binnaryFileBuffer), binnaryFileSize);

        algorithms::KmpSearcher searcher{pattern, ArraySize(pattern)};
        const auto results = searcher.Search(binnaryFileBuffer, binnaryFileSize);
        REQUIRE(results.size() == 8);
        for (const auto& result : results) {
            for (int i = 0; i < ArraySize(pattern); ++i) {
                REQUIRE(result.data[i] == pattern[i]);
            }
        }

        REQUIRE(results[0].offset == 0x5f9);
        REQUIRE(results[1].offset == 0x605);
        REQUIRE(results[2].offset == 0x1019);
        REQUIRE(results[3].offset == 0x1025);
        REQUIRE(results[4].offset == 0x33adc9);
        REQUIRE(results[5].offset == 0x33add5);
        REQUIRE(results[6].offset == 0x4f2879);
        REQUIRE(results[7].offset == 0x4f2885);
    }

    SECTION("50MB binnary test") {
        std::ifstream binnaryFile{"files/50mb.bin", std::ios::binary};

        REQUIRE(binnaryFile.is_open());

        binnaryFile.seekg(0, std::ios::end);
        size_t binnaryFileSize = binnaryFile.tellg();
        binnaryFile.seekg(0, std::ios::beg);
        auto* binnaryFileBuffer = new unsigned char[binnaryFileSize];
        binnaryFile.read(reinterpret_cast<char*>(binnaryFileBuffer), binnaryFileSize);

        algorithms::KmpSearcher searcher{pattern, ArraySize(pattern)};
        const auto results = searcher.Search(binnaryFileBuffer, binnaryFileSize);
        REQUIRE(results.size() == 12);
        for (const auto& result : results) {
            for (int i = 0; i < ArraySize(pattern); ++i) {
                REQUIRE(result.data[i] == pattern[i]);
            }
        }

        REQUIRE(results[0].offset == 0xe9);
        REQUIRE(results[1].offset == 0xf5);
        REQUIRE(results[2].offset == 0x11e9);
        REQUIRE(results[3].offset == 0x11f5);
        REQUIRE(results[4].offset == 0x1a122d9);
        REQUIRE(results[5].offset == 0x1a122e5);
        REQUIRE(results[6].offset == 0x210d709);
        REQUIRE(results[7].offset == 0x210d715);
        REQUIRE(results[8].offset == 0x316f139);
        REQUIRE(results[9].offset == 0x316f145);
        REQUIRE(results[10].offset == 0x31fffd9);
        REQUIRE(results[11].offset == 0x31fffe5);
    }

    SECTION("5G binnary test") {
        std::ifstream binnaryFile{"files/5g.bin", std::ios::binary};

        REQUIRE(binnaryFile.is_open());

        binnaryFile.seekg(0, std::ios::end);
        size_t binnaryFileSize = binnaryFile.tellg();
        binnaryFile.seekg(0, std::ios::beg);
        auto* binnaryFileBuffer = new unsigned char[binnaryFileSize];
        binnaryFile.read(reinterpret_cast<char*>(binnaryFileBuffer), binnaryFileSize);

        algorithms::KmpSearcher searcher{pattern, ArraySize(pattern)};
        Profiler profiler{"SerialSearch"};
        const auto results = searcher.Search(binnaryFileBuffer, binnaryFileSize);
        REQUIRE(results.size() == 7);
        for (const auto& result : results) {
            for (int i = 0; i < ArraySize(pattern); ++i) {
                REQUIRE(result.data[i] == pattern[i]);
            }
        }
    }


}

TEST_CASE("Parallel KMP binnary file search test", "[kmpBinnaryParallel]") {
        unsigned char pattern[] = {0x01, 0x82, 0x2F, 0xFF, 0x74, 0xF2};

    SECTION("5MB binnary test") {
        std::ifstream binnaryFile{"files/5mb.bin", std::ios::binary};

        REQUIRE(binnaryFile.is_open());

        binnaryFile.seekg(0, std::ios::end);
        size_t binnaryFileSize = binnaryFile.tellg();
        binnaryFile.seekg(0, std::ios::beg);
        auto* binnaryFileBuffer = new unsigned char[binnaryFileSize];
        binnaryFile.read(reinterpret_cast<char*>(binnaryFileBuffer), binnaryFileSize);

        algorithms::KmpSearcher searcher{pattern, ArraySize(pattern)};
        auto results = searcher.ParallelSearch(binnaryFileBuffer, binnaryFileSize);
        REQUIRE(results.size_approx()== 8);
        algorithms::KmpResult<unsigned char> result{};
        while (!results.try_dequeue(result)) {
            for (int i = 0; i < ArraySize(pattern); ++i) {
                REQUIRE(result.data[i] == pattern[i]);
            }
        }
    }

    SECTION("50MB binnary test") {
        std::ifstream binnaryFile{"files/50mb.bin", std::ios::binary};

        REQUIRE(binnaryFile.is_open());

        binnaryFile.seekg(0, std::ios::end);
        size_t binnaryFileSize = binnaryFile.tellg();
        binnaryFile.seekg(0, std::ios::beg);
        auto* binnaryFileBuffer = new unsigned char[binnaryFileSize];
        binnaryFile.read(reinterpret_cast<char*>(binnaryFileBuffer), binnaryFileSize);

        algorithms::KmpSearcher searcher{pattern, ArraySize(pattern)};
        auto results = searcher.ParallelSearch(binnaryFileBuffer, binnaryFileSize);
        REQUIRE(results.size_approx() == 12);

        algorithms::KmpResult<unsigned char> result{};
        while (!results.try_dequeue(result)) {
            for (int i = 0; i < ArraySize(pattern); ++i) {
                REQUIRE(result.data[i] == pattern[i]);
            }
        }
    }

    SECTION("5G binnary test") {
        std::ifstream binnaryFile{"files/5g.bin", std::ios::binary};

        REQUIRE(binnaryFile.is_open());

        binnaryFile.seekg(0, std::ios::end);
        size_t binnaryFileSize = binnaryFile.tellg();
        binnaryFile.seekg(0, std::ios::beg);
        auto* binnaryFileBuffer = new unsigned char[binnaryFileSize];
        binnaryFile.read(reinterpret_cast<char*>(binnaryFileBuffer), binnaryFileSize);

        algorithms::KmpSearcher searcher{pattern, ArraySize(pattern)};
        Profiler profiler{"ParallelSearch"};
        auto results = searcher.ParallelSearch(binnaryFileBuffer, binnaryFileSize);
        REQUIRE(results.size_approx() == 7);

        algorithms::KmpResult<unsigned char> result{};
        while (!results.try_dequeue(result)) {
            for (int i = 0; i < ArraySize(pattern); ++i) {
                REQUIRE(result.data[i] == pattern[i]);
            }
        }
    }

}