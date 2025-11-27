# Tests for Interactive Story Game

This directory contains both unit tests and property-based tests that verify correctness of the game components.

## Unit Test Files

- `test_skilllist_unit.cpp` - Unit tests for SkillList data structure (Requirements 4.2, 4.4)
  - Empty list initialization
  - Add single and multiple skills
  - Delete head, at beginning, middle, end
  - Delete from empty list (graceful)
  - Delete at invalid index
  - Replace skill at valid/invalid index
  - Clear list
  - Count with different sizes
  - GetSkillAt with invalid index
  - Memory management

- `test_storymanager_unit.cpp` - Unit tests for StoryManager (Requirements 1.3, 2.3)
  - Load valid JSON
  - Load invalid/nonexistent JSON file
  - Load malformed JSON
  - Start navigation
  - Navigate to valid/invalid node
  - Select valid/invalid option
  - IsAtEnding detection
  - GetCurrentNode before Start
  - UTF-8 character handling

- `test_rendermanager_unit.cpp` - Unit tests for RenderManager (Requirements 3.1, 3.2, 3.4)
  - Initialization with valid font
  - Clear and Display methods
  - GetHoveredOption with no options
  - GetHoveredOption after drawing
  - DrawStoryNode with nullptr
  - DrawStoryNode with/without options
  - DrawSkillList (empty and populated)
  - DrawNodeImage with nonexistent file
  - Multiple Clear/Display cycles
  - Hover detection boundaries

- `test_inputmanager_unit.cpp` - Unit tests for InputManager (Requirements 5.1)
  - Initial state
  - ProcessEvents with empty queue
  - ResetFrameState
  - GetMousePosition
  - Multiple ProcessEvents calls
  - Reset between frames
  - ShouldClose initially false
  - State consistency after reset
  - InputManager lifecycle

## Property-Based Test Files

- `test_skilllist_properties.cpp` - Property tests for SkillList data structure
  - Property 8: Skill addition increases count (Requirements 4.2)
  - Property 10: List integrity after removal (Requirements 4.4)
  - Property 14: SkillList memory cleanup (Requirements 7.1)

- `test_storynode.cpp` - Unit tests for StoryNode and StoryOption
  - Tests construction and initialization
  - Tests HasOptions() method
  - Tests GetOption() method
  - Tests ending node configuration

- `test_inputmanager_properties.cpp` - Property tests for InputManager
  - Property 11: Event queue exhaustion (Requirements 5.4)
  - Property 12: Event processing order (Requirements 5.5)

## Compilation

### Option 1: Using Visual Studio Developer Command Prompt (Recommended)

1. Open "Developer Command Prompt for VS 2022" (or your VS version)
2. Navigate to the tests directory
3. Run: `compile_unit_tests.bat` for unit tests
4. Run: `compile_tests.bat` for property-based tests

### Option 2: Manual Compilation

Unit tests:
```cmd
cl /EHsc /std:c++17 /I"..\src" test_skilllist_unit.cpp ..\src\SkillList.cpp ..\src\Node.cpp /Fe:test_skilllist_unit.exe

cl /EHsc /std:c++17 /I"..\src" test_storymanager_unit.cpp ..\src\StoryManager.cpp ..\src\StoryNode.cpp /Fe:test_storymanager_unit.exe

cl /EHsc /std:c++17 /I"..\src" /I"..\SFML-3.0.2\include" test_rendermanager_unit.cpp ..\src\RenderManager.cpp ..\src\SkillList.cpp ..\src\Node.cpp ..\src\StoryNode.cpp /Fe:test_rendermanager_unit.exe /link /LIBPATH:"..\SFML-3.0.2\lib" sfml-graphics.lib sfml-window.lib sfml-system.lib

cl /EHsc /std:c++17 /I"..\src" /I"..\SFML-3.0.2\include" test_inputmanager_unit.cpp ..\src\InputManager.cpp /Fe:test_inputmanager_unit.exe /link /LIBPATH:"..\SFML-3.0.2\lib" sfml-graphics.lib sfml-window.lib sfml-system.lib
```

Property-based tests:
```cmd
cl /EHsc /std:c++17 /I"..\src" test_skilllist_properties.cpp ..\src\SkillList.cpp ..\src\Node.cpp /Fe:test_skilllist_properties.exe

cl /EHsc /std:c++17 /I"..\src" test_storynode.cpp ..\src\StoryNode.cpp /Fe:test_storynode.exe

cl /EHsc /std:c++17 /I"..\src" /I"..\SFML-3.0.2\include" test_inputmanager_properties.cpp ..\src\InputManager.cpp /Fe:test_inputmanager_properties.exe /link /LIBPATH:"..\SFML-3.0.2\lib" sfml-graphics.lib sfml-window.lib sfml-system.lib
```
Note: SFML-based tests require SFML DLLs to be in the tests directory or in PATH.

### Option 3: Add to Visual Studio Project

1. Add test files to the project
2. Temporarily change the project to build the test as the main executable
3. Build and run

## Running Tests

After compilation:

Unit tests:
```cmd
run_unit_tests.bat
```

Or individually:
```cmd
test_skilllist_unit.exe
test_storymanager_unit.exe
test_rendermanager_unit.exe
test_inputmanager_unit.exe
```

Property-based tests:
```cmd
test_skilllist_properties.exe
test_storynode.exe
test_inputmanager_properties.exe
```

Property tests run multiple iterations with random inputs to verify properties hold across many cases.
- SkillList and StoryManager tests: 100 iterations
- InputManager tests: 10 iterations (reduced due to window creation overhead)

## Expected Output

Unit tests:
```
=== SkillList Unit Tests ===
Testing Requirements: 4.2, 4.4

[PASS] Empty list initialization
[PASS] Add single skill
[PASS] Add multiple skills
...
All 17 tests passed!

=== StoryManager Unit Tests ===
Testing Requirements: 1.3, 2.3

[PASS] Load valid JSON
[PASS] Load invalid JSON file (returns false)
...
All 11 tests passed!

=== RenderManager Unit Tests ===
Testing Requirements: 3.1, 3.2, 3.4

[PASS] Initialization with valid font
[PASS] Clear and Display methods execute
...
Tests completed (some may be skipped if font unavailable)

=== InputManager Unit Tests ===
Testing Requirements: 5.1

[PASS] Initial state
[PASS] ProcessEvents with empty queue
...
All 11 tests passed!
```

Property-based tests:
```
=== Property-Based Tests for SkillList ===
Running 100 iterations per property...

[PASS] Property 8: Skill addition increases count
[PASS] Property 10: List integrity after removal
[PASS] Property 14: SkillList memory cleanup

=== Test Summary ===
Passed: 3
Failed: 0
```

StoryNode unit tests:
```
=== StoryNode Unit Tests ===
[PASS] StoryNode construction
[PASS] HasOptions()
[PASS] GetOption()
[PASS] StoryNode with ending

All tests passed!
```

InputManager property tests:
```
=== Property-Based Tests for InputManager ===
Running 10 iterations per property (reduced for window-based tests)...

[PASS] Property 11: Event queue exhaustion
[PASS] Property 12: Event processing order

=== Test Summary ===
Passed: 2
Failed: 0
```

## Notes

- Unit tests focus on specific examples and edge cases
- Property-based tests verify properties across many random inputs
- Tests suppress SkillList's console output during execution
- Property 14 (memory cleanup) verifies operations complete without crashes
- RenderManager tests may skip some tests if font file is not available
- For full memory leak detection, use Visual Studio's memory profiler or Valgrind

## Test Coverage

The unit tests provide comprehensive coverage of:
- **SkillList**: 17 tests covering all operations and edge cases
- **StoryManager**: 11 tests covering JSON loading, navigation, and error handling
- **RenderManager**: 12 tests covering initialization, rendering, and hover detection
- **InputManager**: 11 tests covering event processing and state management

Combined with property-based tests, this provides strong confidence in component correctness.
