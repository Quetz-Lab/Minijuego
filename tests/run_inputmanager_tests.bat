@echo off
REM Run InputManager property tests with Visual Studio environment

echo Setting up Visual Studio environment...
call "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

echo.
echo Compiling and running InputManager property tests...
call compile_inputmanager_tests.bat
