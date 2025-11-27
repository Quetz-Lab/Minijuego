// Unit tests for InputManager
// Requirements: 5.1
#include "../src/InputManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>

void testInitialState() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test Window");
    InputManager inputManager(window);
    
    // Initial state should be clean
    assert(inputManager.ShouldClose() == false);
    assert(inputManager.WasLeftClicked() == false);
    assert(inputManager.WasEscapePressed() == false);
    
    std::cout << "[PASS] Initial state" << std::endl;
    
    window.close();
}

void testProcessEventsWithEmptyQueue() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test Window");
    InputManager inputManager(window);
    
    // Should not crash with empty event queue
    inputManager.ProcessEvents();
    
    assert(inputManager.ShouldClose() == false);
    assert(inputManager.WasLeftClicked() == false);
    assert(inputManager.WasEscapePressed() == false);
    
    std::cout << "[PASS] ProcessEvents with empty queue" << std::endl;
    
    window.close();
}

void testResetFrameState() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test Window");
    InputManager inputManager(window);
    
    // Simulate some state (we can't easily inject events, so we test the reset mechanism)
    inputManager.ResetFrameState();
    
    // After reset, frame-specific states should be cleared
    assert(inputManager.WasLeftClicked() == false);
    assert(inputManager.WasEscapePressed() == false);
    
    std::cout << "[PASS] ResetFrameState" << std::endl;
    
    window.close();
}

void testGetMousePosition() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test Window");
    InputManager inputManager(window);
    
    // Should return a valid position (even if it's just the current mouse position)
    sf::Vector2i mousePos = inputManager.GetMousePosition();
    
    // Just verify it doesn't crash and returns something
    // We can't control the actual mouse position in automated tests
    (void)mousePos;  // Suppress unused variable warning
    
    std::cout << "[PASS] GetMousePosition" << std::endl;
    
    window.close();
}

void testMultipleProcessEventsCalls() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test Window");
    InputManager inputManager(window);
    
    // Multiple calls should work fine
    for (int i = 0; i < 10; i++) {
        inputManager.ProcessEvents();
    }
    
    std::cout << "[PASS] Multiple ProcessEvents calls" << std::endl;
    
    window.close();
}

void testResetBetweenFrames() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test Window");
    InputManager inputManager(window);
    
    // Simulate frame cycle
    inputManager.ProcessEvents();
    inputManager.ResetFrameState();
    
    // After reset, should be clean
    assert(inputManager.WasLeftClicked() == false);
    assert(inputManager.WasEscapePressed() == false);
    
    // Process again
    inputManager.ProcessEvents();
    inputManager.ResetFrameState();
    
    assert(inputManager.WasLeftClicked() == false);
    assert(inputManager.WasEscapePressed() == false);
    
    std::cout << "[PASS] Reset between frames" << std::endl;
    
    window.close();
}

void testShouldCloseInitiallyFalse() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test Window");
    InputManager inputManager(window);
    
    // Should not want to close initially
    assert(inputManager.ShouldClose() == false);
    
    std::cout << "[PASS] ShouldClose initially false" << std::endl;
    
    window.close();
}

void testProcessEventsDoesNotCrash() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test Window");
    InputManager inputManager(window);
    
    // Process events multiple times in a row
    inputManager.ProcessEvents();
    inputManager.ProcessEvents();
    inputManager.ProcessEvents();
    
    // Should not crash
    std::cout << "[PASS] ProcessEvents does not crash on repeated calls" << std::endl;
    
    window.close();
}

void testStateConsistencyAfterReset() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test Window");
    InputManager inputManager(window);
    
    // Initial state
    bool initialClose = inputManager.ShouldClose();
    bool initialClick = inputManager.WasLeftClicked();
    bool initialEscape = inputManager.WasEscapePressed();
    
    // Reset
    inputManager.ResetFrameState();
    
    // Frame-specific states should be reset
    assert(inputManager.WasLeftClicked() == false);
    assert(inputManager.WasEscapePressed() == false);
    
    // ShouldClose might persist (depends on implementation)
    // We just verify it doesn't crash
    (void)inputManager.ShouldClose();
    
    std::cout << "[PASS] State consistency after reset" << std::endl;
    
    window.close();
}

void testInputManagerLifecycle() {
    // Test that InputManager can be created and destroyed multiple times
    for (int i = 0; i < 3; i++) {
        sf::RenderWindow window(sf::VideoMode({800, 600}), "Test Window");
        InputManager inputManager(window);
        
        inputManager.ProcessEvents();
        inputManager.ResetFrameState();
        
        window.close();
    }
    
    std::cout << "[PASS] InputManager lifecycle (multiple create/destroy)" << std::endl;
}

void testAllMethodsCallable() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test Window");
    InputManager inputManager(window);
    
    // Verify all public methods are callable
    inputManager.ProcessEvents();
    bool shouldClose = inputManager.ShouldClose();
    sf::Vector2i mousePos = inputManager.GetMousePosition();
    bool wasClicked = inputManager.WasLeftClicked();
    bool wasEscape = inputManager.WasEscapePressed();
    inputManager.ResetFrameState();
    
    // Suppress unused variable warnings
    (void)shouldClose;
    (void)mousePos;
    (void)wasClicked;
    (void)wasEscape;
    
    std::cout << "[PASS] All methods callable" << std::endl;
    
    window.close();
}

int main() {
    std::cout << "=== InputManager Unit Tests ===" << std::endl;
    std::cout << "Testing Requirements: 5.1" << std::endl << std::endl;
    std::cout << "Note: These tests verify basic functionality without injecting events." << std::endl;
    std::cout << "Event injection tests are covered in property-based tests." << std::endl << std::endl;
    
    testInitialState();
    testProcessEventsWithEmptyQueue();
    testResetFrameState();
    testGetMousePosition();
    testMultipleProcessEventsCalls();
    testResetBetweenFrames();
    testShouldCloseInitiallyFalse();
    testProcessEventsDoesNotCrash();
    testStateConsistencyAfterReset();
    testInputManagerLifecycle();
    testAllMethodsCallable();
    
    std::cout << "\n=== Test Summary ===" << std::endl;
    std::cout << "All 11 tests passed!" << std::endl;
    
    return 0;
}
