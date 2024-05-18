//
// Created by erik9 on 5/18/2024.
//

#pragma once
template<typename T>
struct DynArray {
    T* data;
    size_t size = 0;

    template<typename... Args>
    explicit DynArray(size_t size, Args&&... args) : size(size) {
        data = new T[size];
        std::uninitialized_fill(data, data + size, T(std::forward<Args>(args)...));
    }
    ~DynArray() {
        delete[] data;
    }
    T& operator[](size_t index) {
        return data[index];
    }
};
