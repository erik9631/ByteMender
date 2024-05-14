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

void byteMender::utils::SetupHardwareBreakpoint(HANDLE thread, unsigned char *addr){
    CONTEXT ctx = {0};
    // Ensure context is set up for debug registers
    ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS; //This is in/out

    // Get current thread context
    if (!GetThreadContext(thread, &ctx))
        throw std::runtime_error("Failed to get thread context with error: " + std::to_string(GetLastError()));

    // Set the breakpoint address (DR0)
    printf("Setting breakpoint at: %p for thread %lu\n", addr, GetThreadId(thread));
    ctx.Dr0 = reinterpret_cast<DWORD_PTR>(addr);

    ctx.Dr7 = 0;
    ctx.Dr7 |= (1 << 0);  // Enable L0 (local breakpoint 0)
    // ctx.Dr7 |= (1 << 16); // Set condition to write (01b is for write, and bits 16-17 of DR7 are for DR0 condition)

    // Apply the modified context to the thread
    std::cout << "setting Dr7 with" << ctx.Dr7 << std::endl;
    if (!SetThreadContext(thread, &ctx))
        throw std::runtime_error("Failed to get thread context with error: " + std::to_string(GetLastError()));
}

void byteMender::utils::ClearHardwareBreakpoint(HANDLE thread, void *addr, LONG(*exceptionHandler)(PEXCEPTION_POINTERS),
    ULONG first) {
}

void byteMender::utils::SuspendAllThreads() {
    IterateThreads(SuspendThread);
}

void byteMender::utils::ResumeAllThreads() {
    IterateThreads(ResumeThread);
}