//
// Created by erik9 on 5/16/2024.
//
#include <catch_amalgamated.hpp>
#include <iostream>
#include "memory/Scanner.h"

TEST_CASE("Heap scan test", "[HeapScanTest]")
{
    unsigned char* heap = new unsigned char[1024]{5};
    auto list = GetHeapList();
    bool found = false;
    std::cout << "Heap is " << (void*)heap << std::endl;
    HEAPENTRY32 entry;
    entry.dwAddress = (DWORD)heap;
    auto closestEntry = list.equal_range(entry);
    printf("%p %llu", heap, closestEntry.first->dwAddress);
    // 000002367A9444B0

    REQUIRE(found);
}