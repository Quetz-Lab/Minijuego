@echo off
REM Setup Visual Studio environment and compile tests

echo Setting up Visual Studio environment...
call "C:\Program Files\Microsoft Visual Studio\18\Community\Common7\Tools\VsDevCmd.bat"

echo.
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

echo Compiling story.json UTF-8 encoding verification...
cl /EHsc /std:c++17 /I"..\src" verify_story_encoding.cpp ..\src\StoryManager.cpp ..\src\StoryNode.cpp /Fe:verify_story_encoding.exe

if %ERRORLEVEL% EQU 0 (
    echo Encoding verification compiled successfully!
    echo Running encoding verification...
    verify_story_encoding.exe
    echo.
) else (
    echo Encoding verification compilation failed!
)

echo All tests complete!
pause
