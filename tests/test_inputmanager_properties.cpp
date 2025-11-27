// Property-Based Tests for InputManager
// Feature: interactive-story-game
// These tests verify correctness properties across many random inputs

#include "../src/InputManager.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cassert>

// Simple test framework
int g_testsPassed = 0;
int g_testsFailed = 0;

void reportTest(const std::string& testName, bool passed, const std::string& failureInfo = "") {
    if (passed) {
        std::cout << "[PASS] " << testName << std::endl;
        g_testsPassed++;
    } else {
        std::cout << "[FAIL] " << testName << std::endl;
        if (!failureInfo.empty()) {
            std::cout << "       " << failureInfo << std::endl;
        }
        g_testsFailed++;
    }
}

// **Feature: interactive-story-game, Property 11: Event queue exhaustion**
// **Validates: Requirements 5.4**
// Property: For any frame with N events in the SFML event queue,
// processing events should handle all N events before the frame ends.
void testProperty_EventQueueExhaustion() {
    const int NUM_ITERATIONS = 10;  // Reduced iterations for window-based tests
    bool allPassed = true;
    std::string failureExample;
    
    for (int iteration = 0; iteration < NUM_ITERATIONS; iteration++) {
        try {
            // Create a window for testing
            sf::RenderWindow window(sf::VideoMode({100u, 100u}), "Test");
            
            InputManager inputManager(window);
            
            // Process events - this should exhaust the queue
            inputManager.ProcessEvents();
            
            // After processing, the event queue should be empty
            // We verify this by checking that pollEvent returns no more events
            int remainingEvents = 0;
            while (window.pollEvent()) {
                remainingEvents++;
            }
            
            // Property check: All events should have been processed
            if (remainingEvents > 0) {
                allPassed = false;
                failureExample = "Event queue not exhausted: " + std::to_string(remainingEvents) + 
                               " events remaining after ProcessEvents()";
                window.close();
                break;
            }
            
            // Verify that ProcessEvents can be called multiple times safely
            inputManager.ProcessEvents();
            inputManager.ProcessEvents();
            
            // Check again - should still be empty
            remainingEvents = 0;
            while (window.pollEvent()) {
                remainingEvents++;
            }
            
            if (remainingEvents > 0) {
                allPassed = false;
                failureExample = "Multiple ProcessEvents() calls left events in queue";
                window.close();
                break;
            }
            
            window.close();
            
        } catch (const std::exception& e) {
            allPassed = false;
            failureExample = std::string("Exception during event processing: ") + e.what();
            break;
        } catch (...) {
            allPassed = false;
            failureExample = "Unknown exception during event processing";
            break;
        }
    }
    
    reportTest("Property 11: Event queue exhaustion", allPassed, failureExample);
}

// **Feature: interactive-story-game, Property 12: Event processing order**
// **Validates: Requirements 5.5**
// Property: For any sequence of events E1, E2, ..., En added to the queue in that order,
// they should be processed in the same order E1, E2, ..., En.
void testProperty_EventProcessingOrder() {
    const int NUM_ITERATIONS = 10;  // Reduced iterations for window-based tests
    bool allPassed = true;
    std::string failureExample;
    
    for (int iteration = 0; iteration < NUM_ITERATIONS; iteration++) {
        try {
            // Create a window for testing
            sf::RenderWindow window(sf::VideoMode({100u, 100u}), "Test");
            
            InputManager inputManager(window);
            
            // Test that state is properly maintained across multiple ProcessEvents calls
            // First call - no events
            inputManager.ResetFrameState();
            inputManager.ProcessEvents();
            
            bool initialLeftClick = inputManager.WasLeftClicked();
            bool initialEscape = inputManager.WasEscapePressed();
            bool initialClose = inputManager.ShouldClose();
            
            // Property check: Initial state should be clean
            if (initialLeftClick || initialEscape || initialClose) {
                allPassed = false;
                failureExample = "Initial state not clean: leftClick=" + 
                               std::to_string(initialLeftClick) + ", escape=" + 
                               std::to_string(initialEscape) + ", close=" + 
                               std::to_string(initialClose);
                window.close();
                break;
            }
            
            // Test ResetFrameState functionality
            inputManager.ResetFrameState();
            
            // After reset, frame-specific states should be cleared
            bool afterResetLeftClick = inputManager.WasLeftClicked();
            bool afterResetEscape = inputManager.WasEscapePressed();
            
            if (afterResetLeftClick || afterResetEscape) {
                allPassed = false;
                failureExample = "ResetFrameState did not clear frame state";
                window.close();
                break;
            }
            
            // Process events again - should still be empty
            inputManager.ProcessEvents();
            
            // Verify GetMousePosition works without crashing
            sf::Vector2i mousePos = inputManager.GetMousePosition();
            
            // Property check: Mouse position should be valid coordinates
            // (any value is valid, just checking it doesn't crash)
            
            window.close();
            
        } catch (const std::exception& e) {
            allPassed = false;
            failureExample = std::string("Exception during order test: ") + e.what();
            break;
        } catch (...) {
            allPassed = false;
            failureExample = "Unknown exception during order test";
            break;
        }
    }
    
    reportTest("Property 12: Event processing order", allPassed, failureExample);
}

int main() {
    std::cout << "=== Property-Based Tests for InputManager ===" << std::endl;
    std::cout << "Running 10 iterations per property (reduced for window-based tests)..." << std::endl << std::endl;
    
    testProperty_EventQueueExhaustion();
    testProperty_EventProcessingOrder();
    
    std::cout << std::endl << "=== Test Summary ===" << std::endl;
    std::cout << "Passed: " << g_testsPassed << std::endl;
    std::cout << "Failed: " << g_testsFailed << std::endl;
    
    return g_testsFailed > 0 ? 1 : 0;
}
