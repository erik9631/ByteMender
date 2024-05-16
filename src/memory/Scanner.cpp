//
// Created by erik9 on 5/16/2024.
//
#include "Scanner.h"

#include <iostream>

std::set<HEAPENTRY32, HeapEntryCompare> GetHeapList(HANDLE targetProcess) {
    std::set<HEAPENTRY32, HeapEntryCompare> heapList;
    HEAPLIST32 hl;
    hl.dwSize = sizeof(HEAPLIST32);
    if(targetProcess == nullptr)
        targetProcess = GetCurrentProcess(); // Get the current process handle (if not provided
    DWORD processId = GetProcessId(targetProcess);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST, processId);
    if (snapshot == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to create snapshot" << std::endl;
        return heapList; // Return an empty list if snapshot creation failed
    }

    if (!Heap32ListFirst(snapshot, &hl)) {
        CloseHandle(snapshot);
        return heapList; // Return an empty list if no heaps were found
    }
    SetLastError(0);

    do {
        HEAPENTRY32 he;
        he.dwSize = sizeof(HEAPENTRY32);
        if (Heap32First(&he, processId, hl.th32HeapID)) {
            do {
                heapList.emplace(he);
            } while (Heap32Next(&he));
        } else {
            std::cerr << "Failed to list heap entries for heap ID: " << hl.th32HeapID << " With error: " << GetLastError() << std::endl;
        }
    } while (Heap32ListNext(snapshot, &hl));

    CloseHandle(snapshot);
    return heapList;
}
