@echo off
REM Compile tests
REM This requires Visual Studio Developer Command Prompt or vcvarsall.bat to be run first

echo Compiling SkillList property tests...
cl /EHsc /std:c++17 /I"..\src" test_skilllist_properties.cpp ..\src\SkillList.cpp ..\src\Node.cpp /Fe:test_skilllist_properties.exe

if %ERRORLEVEL% EQU 0 (
    echo SkillList tests compiled successfully!
    echo Running SkillList property tests...
    test_skilllist_properties.exe
    echo.
) else (
    echo SkillList tests compilation failed!
)

echo Compiling StoryNode unit tests...
cl /EHsc /std:c++17 /I"..\src" test_storynode.cpp ..\src\StoryNode.cpp /Fe:test_storynode.exe

if %ERRORLEVEL% EQU 0 (
    echo StoryNode tests compiled successfully!
    echo Running StoryNode unit tests...
    test_storynode.exe
    echo.
) else (
    echo StoryNode tests compilation failed!
)

echo Compiling StoryManager property tests...
cl /EHsc /std:c++17 /I"..\src" test_storymanager_properties.cpp ..\src\StoryManager.cpp ..\src\StoryNode.cpp /Fe:test_storymanager_properties.exe

if %ERRORLEVEL% EQU 0 (
    echo StoryManager tests compiled successfully!
    echo Running StoryManager property tests...
    test_storymanager_properties.exe
    echo.
) else (
    echo StoryManager tests compilation failed!
)

echo All tests complete!
