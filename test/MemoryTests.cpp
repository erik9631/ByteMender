//
// Created by erik9 on 5/10/2024.
//
#include "catch_amalgamated.hpp"

#include <iostream>
#include "memory/Memory.h"
#include "algorithms/KmpSearcher.h"
#include "utils/Utils.h"

#include <windows.h>
#include <psapi.h>

int patchableFunctionTest(int iterations, int b) {
    for(int i = 0; i < iterations; i++) {
        b += i;
    }
    b *=2;
    return b;
}

TEST_CASE("Basic patch load test", "[PatchTest]") {
    datatypes::Patch patch{0};
    try {
        patch = datatypes::LoadPatch(L"files/operationsFunction.bin");
    }
    catch(std::runtime_error& e) {
        FAIL(e.what());
    }
    auto *operationFunction = reinterpret_cast<int (*)(int, int)>(patch.patchAddr);
    REQUIRE(operationFunction(1, 2) == 5151);
    REQUIRE(operationFunction(5, 8) == 5670);
    REQUIRE(operationFunction(781, 123) == 98231);
}


TEST_CASE("Basic patch test", "[Patchtest2]") {
    unsigned char pattern[] = {0x89, 0x54, 0x24, 0x10, 0x89, 0x4C, 0x24, 0x08, 0x57, 0x48, 0x83, 0xEC, 0, 0xC7, 0x04, 0x24, 0, 0, 0, 0, 0xEB, 0};
    datatypes::Patch patch{0};
    try {
        patch = datatypes::LoadPatch(L"files/patchableFunctionTestPatch.bin");
    }
    catch(std::runtime_error& e) {
        FAIL(e.what());
    }


    HMODULE appModuleHandle = GetModuleHandle(nullptr);
    HANDLE processHandle = GetCurrentProcess();
    MODULEINFO exeInfo;
    GetModuleInformation(processHandle, appModuleHandle, &exeInfo, sizeof(MODULEINFO));
    auto startAddress = reinterpret_cast<unsigned char*>(exeInfo.lpBaseOfDll);
    size_t moduleSize = exeInfo.SizeOfImage;

    algorithms::KmpSearcher searcher{pattern, ArraySize(pattern)};
    auto results = searcher.ParallelSearch(startAddress, moduleSize);
    REQUIRE(results.size_approx() == 1);


    algorithms::KmpResult<unsigned char> result{};
    results.try_dequeue(result);
    memory::PatchMemory(result.data, patch, 0x3D);
    REQUIRE(patchableFunctionTest(100, 0) == 100);
    REQUIRE(patchableFunctionTest(5, 5) == 10);
    REQUIRE(patchableFunctionTest(10, 5) == 15);
}