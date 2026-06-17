cmake_minimum_required(VERSION 3.16)

project(lecture_03 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_STRICT_WARNINGS "Enable common compiler warnings" ON)

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/project_warnings.cmake)

add_executable(lecture03_notes
    src/lecture03_notes.cpp
)
enable_project_warnings(lecture03_notes)
