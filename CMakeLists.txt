cmake_minimum_required(VERSION 3.14)
project(client)


# Set a system env variable for MAPLESTORY_DIR if you just need to quickly auto build to your MapleStory folder (if you don't have a proper VS solution built).
if(DEFINED ENV{MAPLESTORY_DIR})
    set(MAPLESTORY_DIR $ENV{MAPLESTORY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${MAPLESTORY_DIR}")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${MAPLESTORY_DIR}")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${MAPLESTORY_DIR}")
endif()


set(CMAKE_CXX_STANDARD 17)

set(CUSTOM_BINARY_DIR
    $ENV{CUSTOM_BINARY_DIR}
)

# Build External Dependencies
add_subdirectory(external)

# Build Injector and Launcher
add_subdirectory(src)
