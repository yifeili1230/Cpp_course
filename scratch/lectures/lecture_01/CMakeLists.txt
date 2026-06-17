cmake_minimum_required(VERSION 3.16)

project(lecture_01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_STRICT_WARNINGS "Enable common compiler warnings" ON)

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/project_warnings.cmake)

add_library(lecture01_tools STATIC
    src/tools.cpp
)
target_include_directories(lecture01_tools
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_compile_features(lecture01_tools PUBLIC cxx_std_17)
enable_project_warnings(lecture01_tools)

add_executable(lecture01_notes
    src/lecture01_notes.cpp
)
target_link_libraries(lecture01_notes PRIVATE lecture01_tools)
enable_project_warnings(lecture01_notes)

add_executable(namespace_demo
    examples/namespace_a.cpp
    examples/namespace_b.cpp
    examples/namespace_demo.cpp
)
target_include_directories(namespace_demo PRIVATE include)
enable_project_warnings(namespace_demo)
