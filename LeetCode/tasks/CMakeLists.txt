include("$ENV{PROJECT_GIT_DIR}/cmake/AddSuitTests.cmake")
AddSuitTests(
    SOURCE_DIR "$CMAKE_CURRENT_SOURCE_DIR/Easy"
    COMMON_FILES "main.cpp" "support.h"
)
AddSuitTests("$CMAKE_CURRENT_SOURCE_DIR/Medium")
AddSuitTests("$CMAKE_CURRENT_SOURCE_DIR/Hard")