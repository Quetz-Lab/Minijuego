@echo off
REM Setup Visual Studio environment and compile StoryManager tests

call "C:\Program Files\Microsoft Visual Studio\18\Community\Common7\Tools\VsDevCmd.bat" >nul 2>&1

echo Compiling StoryManager property tests...
cl /EHsc /std:c++17 /I"..\src" test_storymanager_properties.cpp ..\src\StoryManager.cpp ..\src\StoryNode.cpp /Fe:test_storymanager_properties.exe >nul 2>&1

if %ERRORLEVEL% EQU 0 (
    echo StoryManager tests compiled successfully!
    echo.
    echo Running StoryManager property tests...
    test_storymanager_properties.exe
) else (
    echo StoryManager tests compilation failed!
    exit /b 1
)
