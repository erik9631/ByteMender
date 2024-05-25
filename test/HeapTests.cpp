//
// Created by erik9 on 5/16/2024.
//
#include <catch_amalgamated.hpp>
#include <iostream>
#include "memory/Scanner.h"
#define enable 1
#if enable
TEST_CASE("Heap scan test", "[HeapScanTest]")
{
    constexpr size_t heapSize = 1024;
    auto* heap = new unsigned char[heapSize]{5};
    auto list = GetHeapList();

    HEAPENTRY32 entry;
    entry.dwAddress = reinterpret_cast<ULONG_PTR>(heap);
    auto closestEntry = --list->lower_bound(entry); // To get the cloest entry from the bottom
    if (closestEntry == list->end())
        FAIL("Addess not found in heap list");
    if (closestEntry->dwAddress > reinterpret_cast<ULONG_PTR>(heap))
        FAIL("Closest heap address too high");
    if (closestEntry->dwAddress + closestEntry->dwBlockSize <= reinterpret_cast<ULONG_PTR>(heap))
        FAIL("Closest heap address too small");
    if (closestEntry->dwAddress + closestEntry->dwBlockSize < reinterpret_cast<ULONG_PTR>(heap) + heapSize)
        FAIL("Heap entry larger than the block");
}

#endif

