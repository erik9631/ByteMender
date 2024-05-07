//
// Created by erik9 on 5/7/2024.
//

#ifndef UTILS_H
#define UTILS_H

template <typename T, size_t N>
constexpr size_t ArraySize(T (&)[N]) { return N; }

#endif //UTILS_H
