@echo off
echo ========================================
echo Running Unit Tests
echo ========================================
echo.

REM Check if executables exist
if not exist test_skilllist_unit.exe (
    echo ERROR: test_skilllist_unit.exe not found
    echo Please run compile_unit_tests.bat first
    pause
    exit /b 1
)

if not exist test_storymanager_unit.exe (
    echo ERROR: test_storymanager_unit.exe not found
    echo Please run compile_unit_tests.bat first
    pause
    exit /b 1
)

if not exist test_rendermanager_unit.exe (
    echo ERROR: test_rendermanager_unit.exe not found
    echo Please run compile_unit_tests.bat first
    pause
    exit /b 1
)

if not exist test_inputmanager_unit.exe (
    echo ERROR: test_inputmanager_unit.exe not found
    echo Please run compile_unit_tests.bat first
    pause
    exit /b 1
)

echo ========================================
echo Running SkillList Unit Tests
echo ========================================
test_skilllist_unit.exe
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [FAILED] SkillList unit tests failed
    pause
    exit /b 1
)
echo.

echo ========================================
echo Running StoryManager Unit Tests
echo ========================================
test_storymanager_unit.exe
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [FAILED] StoryManager unit tests failed
    pause
    exit /b 1
)
echo.

echo ========================================
echo Running RenderManager Unit Tests
echo ========================================
test_rendermanager_unit.exe
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [FAILED] RenderManager unit tests failed
    pause
    exit /b 1
)
echo.

echo ========================================
echo Running InputManager Unit Tests
echo ========================================
test_inputmanager_unit.exe
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo [FAILED] InputManager unit tests failed
    pause
    exit /b 1
)
echo.

echo ========================================
echo All Unit Tests Passed!
echo ========================================
echo.
pause
