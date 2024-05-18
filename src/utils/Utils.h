//
// Created by erik9 on 5/7/2024.
//

#pragma once

#include <functional>
#include <memory>
#include <string>
#include <windows.h>

#include "HexTable.h"
#include "datatypes/DynArray.h"

namespace byteMender::utils {
    template <typename T, size_t N>
    constexpr size_t ArraySize(T (&)[N]) { return N; }
    void IterateThreads(const std::function<void(HANDLE)>& threadAction);
    void SuspendAllThreads();
    void ResumeAllThreads();
    template <typename T>
    std::unique_ptr<DynArray<T>> PatternToBytes(const std::string &pattern, long long wildCard = 0) {
        auto hexTable = generateHexTable();
        hexTable['?'] = wildCard;

        size_t calculatedSize = (pattern.size() + 1) / ((sizeof(T)*2)+1);
        std::unique_ptr<DynArray<T>> parsedArray = std::make_unique<DynArray<T>>(calculatedSize);

        auto parsedData = parsedArray->data;
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



