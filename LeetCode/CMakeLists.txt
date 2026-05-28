cmake_minimum_required(VERSION 3.15)

project(LeetCode
    VERSION 1.0
    DESCRIPTION "LeetCode's problem solving project")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory($CMAKE_CURRENT_SOURCE_DIR/tasks)
