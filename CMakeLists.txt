cmake_minimum_required(VERSION 3.10)
project(NovaScript)

# Set the build directory
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

# Compiler settings (use Clang)
set(CMAKE_C_COMPILER "clang")
set(CMAKE_C_STANDARD 11)

# Add debug flags
set(CMAKE_C_FLAGS_DEBUG "-g")

# Source files
file(GLOB SOURCES "src/*.c")

# Executable
add_executable(nova ${SOURCES})

# Include directories
target_include_directories(nova PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link directories
target_link_directories(nova PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Debug rule
add_custom_target(debug
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
    COMMENT "Switch CMAKE_BUILD_TYPE to Debug"
)

# Clean rule
add_custom_target(clean-all
    COMMAND ${CMAKE_BUILD_TOOL} clean
    COMMAND rm -rf ${CMAKE_BINARY_DIR}
    COMMENT "Cleaning up..."
)

add_dependencies(clean-all debug)
