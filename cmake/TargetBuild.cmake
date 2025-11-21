# brief: build genral-target-lib
function(TargetBuild)
    message("[${TASKS_LIB_NAME} building] begin")

    add_library(${TASKS_LIB_NAME})

    # choose target c++ standart
    set_property(TARGET ${TASKS_LIB_NAME} PROPERTY CXX_STANDARD ${TASKS_LIB_CXX_STANDART})

    # choose the alias for your library
    add_library(${TASKS_LIB_NAME}::${TASKS_LIB_NAME} ALIAS ${TASKS_LIB_NAME})

    # include specific functions
    include("${CMAKE_SOURCE_DIR}/ComposeFileBySourceGroup.cmake")
    include("${CMAKE_SOURCE_DIR}/FindAllSourceFiles.cmake")

    include(GenerateExportHeader)
    generate_export_header(${TASKS_LIB_NAME}
        EXPORT_FILE_NAME "${CMAKE_SOURCE_DIR}/src/${TASKS_LIB_NAME}/export.hpp")

    if(DEFINED MYLIB_SHARED_LIBS)
        set(BUILD_SHARED_LIBS ${MYLIB_SHARED_LIBS})
    endif()

    if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
        set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
    endif()

    # it allows to hide external visibility for all content by default
    set_target_properties(${TASKS_LIB_NAME} PROPERTIES CXX_VISIBILITY_PRESET hidden)
    # it allows to hide external visibility for inline content by defatul
    set_target_properties(${TASKS_LIB_NAME} PROPERTIES VISIBILITY_INLINES_HIDDEN ON)


    # set include directories
    include_directories("${CMAKE_SOURCE_DIR}/src")

    # find all source files for this project
    set(listAvalibleFilesTemplates ".+\\.h" ".+\\.hpp" ".+\\.cpp")
    set(listIngnoredDirectoryes "${CMAKE_SOURCE_DIR}/tests" "${CMAKE_SOURCE_DIR}/build" "${CMAKE_SOURCE_DIR}/.git")
    FindAllSourceFiles("Find all files for the ${TASKS_LIB_NAME}" "${CMAKE_CURRENT_SOURCE_DIR}" "${listIngnoredDirectoryes}" "${listAvalibleFilesTemplates}" listTargetSourceFiles)

    # compose all founded source files by directory
    ComposeFileBySourceGroup("${CMAKE_CURRENT_SOURCE_DIR}" "${listTargetSourceFiles}")

    # create library
    target_sources(${TASKS_LIB_NAME} PRIVATE ${listTargetSourceFiles})

    message("[${TASKS_LIB_NAME} building] end")
endfunction(TargetBuild)
