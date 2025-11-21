call %~dp0vars.bat

call cmake ^
-GNinja ^
-DCMAKE_C_COMPILER=clang-cl.exe ^
-DCMAKE_CXX_COMPILER=clang-cl.exe ^
-S %CURRENT_INSTANCE_DIR% ^
-B %BUILD_DIR%