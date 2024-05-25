//
// Created by erik9 on 5/16/2024.
//

#pragma once
#include <future>
#include <memory>
#include <set>
#include <windows.h>
#include <set>
#include <thread>
#include <vector>

#include "datatypes/DynArray.h"
#include "datatypes/HeapEntry.h"
#include "concurrentqueue.h"

struct HeapEntryCompare {
    bool operator()(const HeapEntry& lhs, const HeapEntry& rhs) const {
        return lhs.address < rhs.address;
    }
};

std::unique_ptr<std::set<HeapEntry, HeapEntryCompare>> GetHeapList(HANDLE targetProcess = nullptr);

template<typename T>
void ScanHeapEntry(const HeapEntry& entry, concurrentQueue::ConcurrentQueue<T>& output) {

}


template<typename T>
std::unique_ptr<concurrentQueue::ConcurrentQueue<T>> ScanMemory(HANDLE targetProcess, T value, const unsigned char* startAddress = nullptr) {
    auto heapList = GetHeapList(targetProcess);
    HeapEntry inputEntry;
    auto results = std::make_unique<concurrentQueue::ConcurrentQueue<T>>();
    inputEntry.address = reinterpret_cast<unsigned long long>(startAddress);
    auto currentEntry = heapList->lower_bound(inputEntry);
    long long entryCount = std::distance(currentEntry, heapList->end());
    long long threadCount = std::thread::hardware_concurrency();
    auto splits = div(entryCount, threadCount);
    std::future<void> tasks[threadCount] = {};

    for (int i = 0; i < threadCount - 1; i++) {
        auto threadStartEntry = currentEntry;
        auto threadEndEntry = currentEntry;
        std::advance(threadEndEntry, splits.quot);
        tasks += std::async(std::launch::async, [=] {
            for (auto it = threadStartEntry; it != threadEndEntry; ++it) {
                ScanHeapEntry(*it, *results);
            }
        });
        std::advance(currentEntry, splits.quot);
    }

    // For the last thread
    auto threadEndEntry = currentEntry;
    std::advance(threadEndEntry, splits.rem);
    tasks += std::async(std::launch::async, [=] {
        for (auto it = currentEntry; it != threadEndEntry; ++it) {
            ScanHeapEntry(*it, *results);
        }
    });


    for (auto& task : tasks) {
        task.get();
    }

    return results;
}

template<typename T>
DynArray<T> FilterMemoryDelta(DynArray<T>& oldScan);
