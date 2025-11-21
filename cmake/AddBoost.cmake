cmake_minimum_required(VERSION 3.21) 

include(FetchContent)

# brief: add Boost to current project
function(AddBoost)
    message("[AddBoost] begin")

    set(BOOST_ENABLE_CMAKE ON)
    FetchContent_Declare(
        build_boost
        GIT_REPOSITORY https://github.com/boostorg/boost.git
        GIT_TAG boost-1.80.0
        GIT_PROGRESS true
    )

    FetchContent_MakeAvailable(build_boost)

    message("[AddBoost] end")
endfunction(AddBoost)
