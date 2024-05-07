//
// Created by erik9 on 4/28/2024.
//
#include "utils.h"
using namespace utils;

unsigned highestPowerof2(unsigned x) {
    // check for the set bits
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;

    return x ^ (x >> 1);
}