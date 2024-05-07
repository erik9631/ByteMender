set(algorithms
)

set(algorithms_headers
        algorithms/KmpSearcher.h
        algorithms/KmpResult.h
)

set(datatypes
        datatypes/Patch.cpp
)

set(datatypes_headers
        datatypes/Patch.h
)

set(memory
        memory/Memory.cpp
)

set(memory_headers
        memory/Memory.h
)

set(utils)
set(utils_headers
    utils/Utils.h
    utils/Profiler.h
)

set(all_headers
        ${datatypes_headers}
        ${algorithms_headers}
        ${memory_headers}
        ${utils_headers}
)

set(all_sources
        ${all_headers}
        ${datatypes}
        ${algorithms}
        ${memory}
        ${utils}
        main.cpp
)


add_executable(ByteMender ${all_sources} )
target_link_libraries(ByteMender PUBLIC concurrent_queue)

add_library(ByteMenderLib STATIC ${all_sources})
target_link_libraries(ByteMenderLib PUBLIC concurrent_queue)

target_include_directories(ByteMenderLib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

