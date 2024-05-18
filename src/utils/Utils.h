//
// Created by erik9 on 5/7/2024.
//

#pragma once

#include <functional>
#include <memory>
#include <string>
#include <windows.h>

#include "datatypes/DynArray.h"

namespace byteMender::utils {
    inline std::unordered_map<unsigned char, unsigned char> hexTable = {
        { '0', 0x0 },
        { '1', 0x1 },
        { '2', 0x2 },
        { '3', 0x3 },
        { '4', 0x4 },
        { '5', 0x5 },
        { '6', 0x6 },
        { '7', 0x7 },
        { '8', 0x8 },
        { '9', 0x9 },
        { 'A', 0xA },
        { 'B', 0xB },
        { 'C', 0xC },
        { 'D', 0xD },
        { 'E', 0xE },
        { 'F', 0xF }
    };


    template <typename T, size_t N>
    constexpr size_t ArraySize(T (&)[N]) { return N; }
    void IterateThreads(const std::function<void(HANDLE)>& threadAction);
    void SuspendAllThreads();
    void ResumeAllThreads();
    template <typename T>
    DynArray<T> PatternToBytes(const std::string& pattern, long long wildCard = 0) {
        hexTable['?'] = wildCard;
        size_t calculatedSize = (pattern.size() + 1) / ((sizeof(T)*2)+1);
        DynArray<T> parsedArray = DynArray<T>{calculatedSize};

        auto parsedData = parsedArray.data;
        auto stringData = pattern.data();
        auto stringDataEnd = stringData + pattern.size();

        for (; stringData != stringDataEnd; ++stringData) {
            if (*stringData == ' ')
                continue;

            // -1 cause We don't shift the last value
            auto sizeEnd = (stringData + sizeof(T)*2)-1;
            while (stringData != sizeEnd) {
                *parsedData += hexTable[*stringData];
                *parsedData <<= 4;
                stringData++;
            }
            // Add the last value but don't shift it
            *parsedData += hexTable[*stringData];
            ++parsedData;
        }
        return parsedArray;
    }
}



