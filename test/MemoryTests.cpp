//
// Created by erik9 on 5/10/2024.
//
#include <windows.h>
#include <psapi.h>
#include <iostream>

#include "catch_amalgamated.hpp"
#include "memory/Memory.h"

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
        patch = datatypes::LoadPatch(L"files/operationsFunction");
    }
    catch(std::runtime_error& e) {
        FAIL(e.what());
    }
    auto *operationFunction = reinterpret_cast<int (*)(int, int)>(patch.patchAddr);
    REQUIRE(operationFunction(1, 2) == 5151);
    REQUIRE(operationFunction(5, 8) == 5670);
    REQUIRE(operationFunction(781, 123) == 98231);
}
