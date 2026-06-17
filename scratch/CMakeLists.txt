cmake_minimum_required(VERSION 3.16)

project(cpp_build_playground VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_STRICT_WARNINGS "Enable common compiler warnings" ON)

include(${CMAKE_CURRENT_LIST_DIR}/cmake/project_warnings.cmake)

file(GLOB lecture_entries LIST_DIRECTORIES true RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/lectures" "${CMAKE_CURRENT_SOURCE_DIR}/lectures/*")
list(SORT lecture_entries)

foreach(entry IN LISTS lecture_entries)
    set(lecture_path "${CMAKE_CURRENT_SOURCE_DIR}/lectures/${entry}")
    if(IS_DIRECTORY "${lecture_path}" AND EXISTS "${lecture_path}/CMakeLists.txt")
        add_subdirectory("${lecture_path}" "lectures/${entry}")
    endif()
endforeach()
