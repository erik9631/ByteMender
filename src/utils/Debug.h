//
// Created by erik9 on 5/15/2024.
//

#ifndef DEBUG_H
#define DEBUG_H
#include <functional>
#include <windows.h>

namespace byteMender::debug {
    enum Condition {
        EXECUTE = 0,
        WRITE = 1,
        IO = 2,
        READWRITE = 3
    };

    enum Length {
        BYTE = 0,
        WORD = 1,
        DWORD = 3,
        QWORD = 2
    };

    void SetupHardwareBreakpoint(HANDLE thread, unsigned char *addr, unsigned char breakPointNum = 0, Condition condition = EXECUTE, Length len = BYTE);
    void ClearHardwareBreakpoint(HANDLE thread, void *addr, LONG(*exceptionHandler)(PEXCEPTION_POINTERS), ULONG first = 1);
}

#endif //DEBUG_H
