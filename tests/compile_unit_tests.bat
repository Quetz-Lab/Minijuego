@echo off
echo ========================================
echo Compiling Unit Tests
echo ========================================
echo.

REM Check if we're in a Developer Command Prompt
where cl >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: cl.exe not found. Please run this from a Visual Studio Developer Command Prompt.
    echo.
    echo To open Developer Command Prompt:
    echo 1. Press Windows key
    echo 2. Type "Developer Command Prompt"
    echo 3. Select "Developer Command Prompt for VS 2022" or your VS version
    pause
    exit /b 1
)

echo Compiling SkillList unit tests...
cl /EHsc /std:c++17 /I"..\src" test_skilllist_unit.cpp ..\src\SkillList.cpp ..\src\Node.cpp /Fe:test_skilllist_unit.exe
if %ERRORLEVEL% NEQ 0 (
    echo Failed to compile SkillList unit tests
    pause
    exit /b 1
)
echo [OK] SkillList unit tests compiled
echo.

echo Compiling StoryManager unit tests...
cl /EHsc /std:c++17 /I"..\src" test_storymanager_unit.cpp ..\src\StoryManager.cpp ..\src\StoryNode.cpp /Fe:test_storymanager_unit.exe
if %ERRORLEVEL% NEQ 0 (
    echo Failed to compile StoryManager unit tests
    pause
    exit /b 1
)
echo [OK] StoryManager unit tests compiled
echo.

echo Compiling RenderManager unit tests...
cl /EHsc /std:c++17 /I"..\src" /I"..\SFML-3.0.2\include" test_rendermanager_unit.cpp ..\src\RenderManager.cpp ..\src\SkillList.cpp ..\src\Node.cpp ..\src\StoryNode.cpp /Fe:test_rendermanager_unit.exe /link /LIBPATH:"..\SFML-3.0.2\lib" sfml-graphics.lib sfml-window.lib sfml-system.lib
if %ERRORLEVEL% NEQ 0 (
    echo Failed to compile RenderManager unit tests
    pause
    exit /b 1
)
echo [OK] RenderManager unit tests compiled
echo.

echo Compiling InputManager unit tests...
cl /EHsc /std:c++17 /I"..\src" /I"..\SFML-3.0.2\include" test_inputmanager_unit.cpp ..\src\InputManager.cpp /Fe:test_inputmanager_unit.exe /link /LIBPATH:"..\SFML-3.0.2\lib" sfml-graphics.lib sfml-window.lib sfml-system.lib
if %ERRORLEVEL% NEQ 0 (
    echo Failed to compile InputManager unit tests
    pause
    exit /b 1
)
echo [OK] InputManager unit tests compiled
echo.

echo ========================================
echo All unit tests compiled successfully!
echo ========================================
echo.
echo To run the tests, execute: run_unit_tests.bat
echo.
pause
