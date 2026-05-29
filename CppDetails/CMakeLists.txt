cmake_minimum_required(VERSION 3.15)

project(LeetCode
    VERSION 1.0
    DESCRIPTION "C++'s unique language details")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include("$ENV{PROJECT_GIT_DIR}/cmake/AddSuitTests.cmake")

AddSuitTests(
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/for_classes"
    COMMON_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)
