cmake_minimum_required(VERSION 3.27)
project(ByteMender)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib/catch2)
add_subdirectory(lib/concurrentQueue)
add_subdirectory(lib/yaml-cpp-0.8.0)

add_subdirectory(src)
add_subdirectory(test)

