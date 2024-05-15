//
// Created by erik9 on 5/12/2024.
//
#include "Utils.h"

#include <stdexcept>
#include <Windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <string>


void byteMender::utils::IterateThreads(const std::function<void(HANDLE)>& threadAction) {
    HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
    THREADENTRY32 te32;

    // Take a snapshot of all running threads
    hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hThreadSnap == INVALID_HANDLE_VALUE) return;

    te32.dwSize = sizeof(THREADENTRY32);

    // Retrieve information about the first thread,
    // and exit if unsuccessful
    if (!Thread32First(hThreadSnap, &te32)) {
        CloseHandle(hThreadSnap);
        throw std::runtime_error("Failed to retrieve information about the first thread.");
    }

    // Get the current process ID
    DWORD currentProcessId = GetCurrentProcessId();

    // Now walk the thread list of the system,
    // and suspend each thread
    do {
        if(te32.th32OwnerProcessID != currentProcessId)
            continue;

        if (te32.th32ThreadID != GetCurrentThreadId()) {
            HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, te32.th32ThreadID);
            if (hThread == NULL)
                continue;
            threadAction(hThread);
            CloseHandle(hThread);
        }
    } while (Thread32Next(hThreadSnap, &te32));

    CloseHandle(hThreadSnap);
}

void byteMender::utils::SuspendAllThreads() {
    IterateThreads(SuspendThread);
}

void byteMender::utils::ResumeAllThreads() {
    IterateThreads(ResumeThread);
}