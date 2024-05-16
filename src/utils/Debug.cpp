//
// Created by erik9 on 5/15/2024.
//
#include "Debug.h"

#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>


void byteMender::debug::SetupHardwareBreakpoint(HANDLE thread, unsigned char *addr, unsigned char breakPointNum, Condition condition, Length len) {
    CONTEXT ctx = {0};
    // Ensure context is set up for debug registers
    ctx.ContextFlags = CONTEXT_FULL | CONTEXT_DEBUG_REGISTERS; //This is in/out

    // Get current thread context
    if (!GetThreadContext(thread, &ctx))
        throw std::runtime_error("Failed to get thread context with error: " + std::to_string(GetLastError()));

    // Set the breakpoint address (DR0)
    printf("Setting breakpoint at: %p for thread %lu\n", addr, GetThreadId(thread));

    auto debugRegister = (&ctx.Dr0) + breakPointNum;

    *debugRegister = reinterpret_cast<DWORD64>(addr);

    ctx.Dr7 = 0;
    ctx.Dr7 |= (1 << (breakPointNum*2));  // Enable L0 (local breakpoint 0)
    ctx.Dr7 |= (condition << (16+(breakPointNum * 4))); // Set condition to write (01b is for write, and bits 16-17 of DR7 are for DR0 condition)
    ctx.Dr7 |= (len << (18+(breakPointNum * 4))); // Set breakpoint len

    // Apply the modified context to the thread
    std::cout << "setting Dr7 with" << ctx.Dr7 << std::endl;
    if (!SetThreadContext(thread, &ctx))
        throw std::runtime_error("Failed to get thread context with error: " + std::to_string(GetLastError()));
}

void byteMender::debug::ClearHardwareBreakpoint(HANDLE thread,  unsigned char breakPointNum) {
    CONTEXT ctx = {};
    ctx.ContextFlags = CONTEXT_FULL | CONTEXT_DEBUG_REGISTERS; //This is in/out
    if(!GetThreadContext(thread, &ctx))
        throw std::runtime_error("Failed to get thread context with error: " + std::to_string(GetLastError()));

    auto debugRegister = (&ctx.Dr0) + breakPointNum;

    *debugRegister = 0;
    ctx.Dr7 = 0;
    ctx.Dr7 &= (0 << (breakPointNum*2));  // Enable L0 (local breakpoint 0)
    ctx.Dr7 &= (0 << (16+(breakPointNum * 4))); // Set condition to write (01b is for write, and bits 16-17 of DR7 are for DR0 condition)
    ctx.Dr7 &= (0 << (17+(breakPointNum * 4))); // Set condition to write (01b is for write, and bits 16-17 of DR7 are for DR0 condition)
    ctx.Dr7 &= (0 << (18+(breakPointNum * 4))); // Set breakpoint len
    ctx.Dr7 &= (0 << (19+(breakPointNum * 4))); // Set breakpoint len

}