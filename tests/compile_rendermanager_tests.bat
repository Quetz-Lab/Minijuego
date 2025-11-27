@echo off
REM Compile RenderManager property tests
REM This requires Visual Studio Developer Command Prompt or vcvarsall.bat to be run first

echo Compiling RenderManager property tests...

REM Set SFML paths
set SFML_INCLUDE=..\SFML-3.0.2\include
set SFML_LIB=..\SFML-3.0.2\lib

REM Compile with all dependencies
cl /EHsc /std:c++17 /I"..\src" /I"%SFML_INCLUDE%" test_rendermanager_properties.cpp ..\src\RenderManager.cpp ..\src\StoryNode.cpp ..\src\SkillList.cpp ..\src\Node.cpp /Fe:test_rendermanager_properties.exe /link /LIBPATH:"%SFML_LIB%" sfml-graphics.lib sfml-window.lib sfml-system.lib

if %ERRORLEVEL% EQU 0 (
    echo RenderManager tests compiled successfully!
    echo.
    echo Running RenderManager property tests...
    test_rendermanager_properties.exe
    echo.
) else (
    echo RenderManager tests compilation failed!
)
