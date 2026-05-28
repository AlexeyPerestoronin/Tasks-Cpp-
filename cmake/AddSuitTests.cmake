include(CMakeParseArguments)
include("$ENV{PROJECT_GIT_DIR}/cmake/FindAllSourceFiles.cmake")

find_package(GTest REQUIRED)

function(AddSuitTest)
    set(options "")
    set(oneValueArgs TARGET_FILE)
    set(multiValueArgs COMMON_FILES INCLUDE_DIRS)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    message("[add suit-test: ${ARG_TARGET_FILE}] begin")

    get_filename_component(fileNameWithoutExtension ${ARG_TARGET_FILE} NAME_WE)
    set(suitTestExeName ${fileNameWithoutExtension})

    add_executable(${suitTestExeName}
        ${ARG_TARGET_FILE}
        ${ARG_COMMON_FILES}
    )

    target_include_directories(${suitTestExeName}
        PRIVATE
        ${ARG_INCLUDE_DIRS}
        ${gtest_SOURCE_DIR}/include
        ${gmock_SOURCE_DIR}/include
    )

    target_link_libraries(${suitTestExeName} PRIVATE gtest::gtest)

    message("[add suit-test: ${ARG_TARGET_FILE}] end")
endfunction()


function(AddSuitTests)
    set(options "")
    set(oneValueArgs SOURCE_DIR)
    set(multiValueArgs COMMON_FILES INCLUDE_DIRS)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    message("[AddSuitTests] begin")

    # Ищем все файлы в указанной директории SOURCE_DIR
    file(GLOB_RECURSE sources_list "${ARG_SOURCE_DIR}/*")
    
    foreach(source ${sources_list})
        if(NOT IS_DIRECTORY ${source})
            get_filename_component(sourceExt ${source} EXT)
            if(${sourceExt} STREQUAL ".cpp")
                AddSuitTest(
                    TARGET_FILE ${source}
                    COMMON_FILES ${ARG_COMMON_FILES}
                    INCLUDE_DIRS ${ARG_INCLUDE_DIRS}
                )
            endif()
        endif()
    endforeach()

    message("[AddSuitTests] end")
endfunction()
