@echo off
setlocal enabledelayedexpansion

set "ROOT_DIR=%~dp0"
set "VCPKG_DIR=%ROOT_DIR%vcpkg"
set "CMAKE_EXE=%ROOT_DIR%cmake-portable\bin\cmake.exe"
set "TOOLCHAIN_FILE=%VCPKG_DIR%\scripts\buildsystems\vcpkg.cmake"
set "BUILD_DIR=%ROOT_DIR%build"

if not exist "%VCPKG_DIR%\" (
    git clone https://github.com/microsoft/vcpkg.git "%VCPKG_DIR%"
    if errorlevel 1 (
        exit /b 1
    )
)


if not exist "%VCPKG_DIR%\vcpkg.exe" (
    pushd "%VCPKG_DIR%"
    call bootstrap-vcpkg.bat
    if errorlevel 1 (
        exit /b 1
    )
    popd
)

pushd "%ROOT_DIR%"
"%VCPKG_DIR%\vcpkg.exe" install
if errorlevel 1 (
pause
    exit /b 1
)
popd

if not exist "%BUILD_DIR%" (
    mkdir "%BUILD_DIR%"
)


cd /d "%BUILD_DIR%"

"%CMAKE_EXE%" .. -DCMAKE_TOOLCHAIN_FILE="%TOOLCHAIN_FILE%"
if errorlevel 1 (

    exit /b 1
)

pause
