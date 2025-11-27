@echo off
REM Verify story.json UTF-8 encoding
REM This requires Visual Studio Developer Command Prompt or vcvarsall.bat to be run first

echo Compiling story.json encoding verification...
cl /EHsc /std:c++17 /I"..\src" verify_story_encoding.cpp ..\src\StoryManager.cpp ..\src\StoryNode.cpp /Fe:verify_story_encoding.exe

if %ERRORLEVEL% EQU 0 (
    echo Compilation successful!
    echo.
    echo Running verification...
    echo.
    verify_story_encoding.exe
) else (
    echo Compilation failed!
)
