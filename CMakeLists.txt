cmake_minimum_required(VERSION 3.1.0)

project(Tasks)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Z7")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od")

include("${CMAKE_SOURCE_DIR}/cmake/AddGoogleTests.cmake")
AddGoogleTests()

include("${CMAKE_SOURCE_DIR}/cmake/AddSuitTests.cmake")

AddSuitTests("${CMAKE_SOURCE_DIR}/src/CheckPoints")
AddSuitTests("${CMAKE_SOURCE_DIR}/src/OpenSources/LetCode")
