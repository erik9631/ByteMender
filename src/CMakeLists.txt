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

set(utils
        utils/utils.cpp
)

set(utils_headers
        utils/utils.h
        utils/Profiler.h
)

set(all_headers
        ${datatypes_headers}
        ${algorithms_headers}
        ${utils_headers}
)

set(all_sources
        ${all_headers}
        ${datatypes}
        ${algorithms}
        ${utils}
        main.cpp
)


add_executable(ByteMender ${all_sources} )
target_link_libraries(ByteMender PUBLIC concurrent_queue)

add_library(ByteMenderLib STATIC ${all_sources})
target_link_libraries(ByteMenderLib PUBLIC concurrent_queue)

target_include_directories(ByteMenderLib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

