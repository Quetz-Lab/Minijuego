@echo off
REM Compile Option Display Property Test
REM This requires Visual Studio Developer Command Prompt or vcvarsall.bat to be run first

echo Compiling Option Display Property Test...

REM Set SFML paths
set SFML_INCLUDE=..\SFML-3.0.2\include
set SFML_LIB=..\SFML-3.0.2\lib

REM Compile with all dependencies
cl /EHsc /std:c++17 /I"..\src" /I"%SFML_INCLUDE%" test_option_display_properties.cpp ..\src\RenderManager.cpp ..\src\StoryNode.cpp ..\src\SkillList.cpp ..\src\Node.cpp /Fe:test_option_display_properties.exe /link /LIBPATH:"%SFML_LIB%" sfml-graphics.lib sfml-window.lib sfml-system.lib

if %ERRORLEVEL% EQU 0 (
    echo Option Display tests compiled successfully!
    echo.
    echo Running Option Display property tests...
    test_option_display_properties.exe
    echo.
) else (
    echo Option Display tests compilation failed!
)
