@echo off
REM Compile InputManager property tests
REM This requires Visual Studio Developer Command Prompt or vcvarsall.bat to be run first

echo Compiling InputManager property tests...
cl /EHsc /std:c++17 /I"..\src" /I"..\SFML-3.0.2\include" test_inputmanager_properties.cpp ..\src\InputManager.cpp /Fe:test_inputmanager_properties.exe /link /LIBPATH:"..\SFML-3.0.2\lib" sfml-graphics.lib sfml-window.lib sfml-system.lib

if %ERRORLEVEL% EQU 0 (
    echo InputManager tests compiled successfully!
    echo Running InputManager property tests...
    test_inputmanager_properties.exe
    echo.
) else (
    echo InputManager tests compilation failed!
)
