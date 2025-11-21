set CURRENT_INSTANCE_DIR=%~dp0
set CURRENT_INSTANCE_DIR=%CURRENT_INSTANCE_DIR:\=/%
IF %CURRENT_INSTANCE_DIR:~-1%==/ SET CURRENT_INSTANCE_DIR=%CURRENT_INSTANCE_DIR:~0,-1%
echo Current instance dir: %CURRENT_INSTANCE_DIR%

set BUILD_DIR=%CURRENT_INSTANCE_DIR%/build
echo Current build dir: %BUILD_DIR%

@REM set PATH=C:/Program Files/LLVM/bin;%PATH%
@REM set PATH=C:/tools/msys64/clang64/bin;%PATH%

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\vsdevcmd" -arch=x64
