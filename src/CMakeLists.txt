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
        datatypes/PatchDescriptor.h
        datatypes/DynArray.h
        datatypes/HeapEntry.h
)

set(memory
        memory/Memory.cpp
        memory/Scanner.cpp
)

set(memory_headers
        memory/Memory.h
        memory/Scanner.h
)

set(utils
        utils/Debug.cpp
        utils/Utils.cpp)

set(utils_headers
    utils/Utils.h
    utils/Profiler.h
    utils/Debug.h
        utils/HexTable.h
)

set(proxies_headers
        proxies/version.h
        proxies/dxgi.h
)
set(all_headers
        ${datatypes_headers}
        ${algorithms_headers}
        ${memory_headers}
        ${utils_headers}
        ${proxies_headers}
)

set(all_sources
        ${all_headers}
        ${datatypes}
        ${algorithms}
        ${memory}
        ${utils}
        ${proxies}
        main.cpp
)

add_library(ByteMender STATIC ${all_sources})
target_link_libraries(ByteMender PUBLIC concurrent_queue)
target_link_libraries(ByteMender PUBLIC yaml-cpp)
target_include_directories(ByteMender PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})



# Get the directory path of the currently running executable
get_filename_component(EXECUTABLE_DIR "${CMAKE_CURRENT_BINARY_DIR}/include" ABSOLUTE)

if(NOT EXISTS "${EXECUTABLE_DIR}")
    file(MAKE_DIRECTORY "${EXECUTABLE_DIR}")
endif()

# Install header files while preserving the subdirectory structure
foreach(header_file ${all_headers})
    get_filename_component(header_dir "${header_file}" DIRECTORY)
    install(FILES "${header_file}"
            DESTINATION "${EXECUTABLE_DIR}/${header_dir}")
endforeach()