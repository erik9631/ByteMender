//
// Created by erik9 on 5/13/2024.
//
#include <catch_amalgamated.hpp>
#include <condition_variable>
#include <thread>

#include "utils/Debug.h"
#include "utils/Profiler.h"
#include "utils/Utils.h"
using namespace byteMender::utils;

static bool  breakpointTriggered = false;

static void _declspec(noinline) debuggableFunction() {
    std::cout << "Debuggable function was called!" << std::endl;
}

LONG WINAPI testExceptionHandler(PEXCEPTION_POINTERS pExceptionInfo) {

    // Check if it's a single-step exception
    if (pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_SINGLE_STEP) {
        std::cout << "Breakpoint triggered!" << std::endl;

        breakpointTriggered = true;

        // Check if we hit a JMP instruction and handle it
        BYTE* instructionPtr = reinterpret_cast<BYTE*>(pExceptionInfo->ContextRecord->Rip);

        // Example of handling a JMP (0xE9 is a relative JMP)
        if (*instructionPtr == 0xE9) {
            // Handle relative JMP
            std::cout << "Relative JMP detected!" << std::endl;
            INT32 offset = *reinterpret_cast<INT32*>(instructionPtr + 1);
            pExceptionInfo->ContextRecord->Rip += (offset + 5);
            return EXCEPTION_CONTINUE_EXECUTION;
        }

        pExceptionInfo->ContextRecord->Rip++;
        return EXCEPTION_CONTINUE_EXECUTION;
    }

    std::cout << "Exception address: " << pExceptionInfo->ExceptionRecord->ExceptionAddress << std::endl;
    return EXCEPTION_CONTINUE_SEARCH;
}

TEST_CASE("Execution debugger test", "[DebuggerTest]") {
    std::mutex signalMutex;
    std::condition_variable cv;
    bool wasNotified = false;
    std::cout<< "Execution thread " << GetCurrentThreadId() << std::endl;
    std::thread debuggerThread([&]() {
        std::unique_lock signalLock{signalMutex};
        SuspendAllThreads();
        IterateThreads([&](HANDLE thread) {
            try {
                byteMender::debug::SetupHardwareBreakpoint(thread, reinterpret_cast<unsigned char*>(debuggableFunction));
            }
            catch (std::runtime_error& e) {
                std::cout << e.what() << std::endl;
                CHECK(false);

        }});
        AddVectoredExceptionHandler(1, testExceptionHandler);
        ResumeAllThreads();
        cv.notify_all();
        wasNotified = true;
    });
    std::unique_lock signalLock{signalMutex};
    cv.wait(signalLock, [&]{return wasNotified;});
    debuggableFunction();
    debuggerThread.join();
    CHECK(breakpointTriggered == true);
}