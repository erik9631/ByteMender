//
// Created by erik9 on 5/18/2024.
//

#pragma once
#include <array>
namespace byteMender::utils {
    constexpr std::array<unsigned char, 256> generateHexTable() {
        std::array<unsigned char, 256> table{};
        table['0'] = 0x0;
        table['1'] = 0x1;
        table['2'] = 0x2;
        table['3'] = 0x3;
        table['4'] = 0x4;
        table['5'] = 0x5;
        table['6'] = 0x6;
        table['7'] = 0x7;
        table['8'] = 0x8;
        table['9'] = 0x9;
        table['A'] = 0xA;
        table['B'] = 0xB;
        table['C'] = 0xC;
        table['D'] = 0xD;
        table['E'] = 0xE;
        table['F'] = 0xF;
        table['a'] = 0xA;
        table['b'] = 0xB;
        table['c'] = 0xC;
        table['d'] = 0xD;
        table['e'] = 0xE;
        table['f'] = 0xF;
        return table;
    }
}
