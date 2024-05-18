set(testSrc
        KmpTests.cpp
        MemoryTests.cpp
        BreakpointTests.cpp
        HeapTests.cpp
        PatternTests.cpp
        PatchLoaderTests.cpp
)

add_executable(tests ${testSrc})
target_link_libraries(tests PRIVATE ByteMender)
target_link_libraries(tests PRIVATE catch_amalgamated)



# Get the directory path of the currently running executable


get_filename_component(EXECUTABLE_DIR "${CMAKE_CURRENT_BINARY_DIR}/files" ABSOLUTE)

if(NOT EXISTS "${EXECUTABLE_DIR}")
    file(MAKE_DIRECTORY "${EXECUTABLE_DIR}")
endif()

# Install files from the "files" directory to the executable directory
install(DIRECTORY "${CMAKE_SOURCE_DIR}/files/"
        DESTINATION "${EXECUTABLE_DIR}"
        FILES_MATCHING PATTERN "*")