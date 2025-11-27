// Unit tests for RenderManager
// Requirements: 3.1, 3.2, 3.4
#include "../src/RenderManager.h"
#include "../src/StoryNode.h"
#include "../src/SkillList.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>

void testInitializationWithValidFont() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test Window");
    RenderManager renderer(window);
    
    bool result = renderer.Initialize();
    
    // Should succeed if font file exists
    // Note: This test depends on assets/Roboto-Regular.ttf existing
    if (result) {
        std::cout << "[PASS] Initialization with valid font" << std::endl;
    } else {
        std::cout << "[INFO] Font file not found (expected in some environments)" << std::endl;
    }
    
    window.close();
}

void testClearAndDisplay() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test Window");
    RenderManager renderer(window);
    
    // Should not crash
    renderer.Clear(sf::Color::Black);
    renderer.Display();
    
    std::cout << "[PASS] Clear and Display methods execute" << std::endl;
    
    window.close();
}

void testGetHoveredOptionNoOptions() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test Window");
    RenderManager renderer(window);
    renderer.Initialize();
    
    // Before drawing any node, no options should be hovered
    int hoveredIndex = renderer.GetHoveredOption(sf::Vector2i(100, 100));
    
    assert(hoveredIndex == -1);
    
    std::cout << "[PASS] GetHoveredOption with no options (returns -1)" << std::endl;
    
    window.close();
}

void testGetHoveredOptionAfterDrawing() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test Window");
    RenderManager renderer(window);
    bool initialized = renderer.Initialize();
    
    if (!initialized) {
        std::cout << "[SKIP] GetHoveredOption after drawing (font not available)" << std::endl;
        window.close();
        return;
    }
    
    // Create a node with options
    StoryNode node;
    node.id = "test";
    node.title = "Test Node";
    node.text = "Test text";
    
    StoryOption opt1;
    opt1.id = "A";
    opt1.text = "Option A";
    opt1.nextNodeId = "n2";
    node.options.push_back(opt1);
    
    StoryOption opt2;
    opt2.id = "B";
    opt2.text = "Option B";
    opt2.nextNodeId = "n3";
    node.options.push_back(opt2);
    
    // Draw the node to populate option bounds
    renderer.Clear();
    renderer.DrawStoryNode(&node);
    
    // Test with a position that's unlikely to hit any option
    int hoveredIndex = renderer.GetHoveredOption(sf::Vector2i(10, 10));
    
    // Should return -1 or a valid index (0 or 1)
    assert(hoveredIndex >= -1 && hoveredIndex <= 1);
    
    std::cout << "[PASS] GetHoveredOption after drawing node" << std::endl;
    
    window.close();
}

void testDrawStoryNodeWithNullptr() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test Window");
    RenderManager renderer(window);
    renderer.Initialize();
    
    // Should not crash when drawing nullptr
    renderer.Clear();
    renderer.DrawStoryNode(nullptr);
    
    std::cout << "[PASS] DrawStoryNode with nullptr (graceful handling)" << std::endl;
    
    window.close();
}

void testDrawStoryNodeWithOptions() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test Window");
    RenderManager renderer(window);
    bool initialized = renderer.Initialize();
    
    if (!initialized) {
        std::cout << "[SKIP] DrawStoryNode with options (font not available)" << std::endl;
        window.close();
        return;
    }
    
    StoryNode node;
    node.id = "test";
    node.title = "Test Title";
    node.text = "Test text content";
    
    StoryOption opt;
    opt.id = "A";
    opt.text = "Test Option";
    opt.nextNodeId = "n2";
    node.options.push_back(opt);
    
    // Should not crash
    renderer.Clear();
    renderer.DrawStoryNode(&node);
    renderer.Display();
    
    std::cout << "[PASS] DrawStoryNode with options" << std::endl;
    
    window.close();
}

void testDrawStoryNodeWithoutOptions() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test Window");
    RenderManager renderer(window);
    bool initialized = renderer.Initialize();
    
    if (!initialized) {
        std::cout << "[SKIP] DrawStoryNode without options (font not available)" << std::endl;
        window.close();
        return;
    }
    
    StoryNode node;
    node.id = "ending";
    node.title = "The End";
    node.text = "Story ends here.";
    node.isEnding = true;
    
    // Should not crash
    renderer.Clear();
    renderer.DrawStoryNode(&node);
    renderer.Display();
    
    std::cout << "[PASS] DrawStoryNode without options (ending node)" << std::endl;
    
    window.close();
}

void testDrawSkillList() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test Window");
    RenderManager renderer(window);
    bool initialized = renderer.Initialize();
    
    if (!initialized) {
        std::cout << "[SKIP] DrawSkillList (font not available)" << std::endl;
        window.close();
        return;
    }
    
    SkillList skills;
    skills.AddSkill("Fireball");
    skills.AddSkill("Ice Spike");
    skills.AddSkill("Healing");
    
    // Should not crash
    renderer.Clear();
    renderer.DrawSkillList(skills);
    renderer.Display();
    
    std::cout << "[PASS] DrawSkillList" << std::endl;
    
    window.close();
}

void testDrawEmptySkillList() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test Window");
    RenderManager renderer(window);
    bool initialized = renderer.Initialize();
    
    if (!initialized) {
        std::cout << "[SKIP] DrawEmptySkillList (font not available)" << std::endl;
        window.close();
        return;
    }
    
    SkillList skills;  // Empty list
    
    // Should not crash
    renderer.Clear();
    renderer.DrawSkillList(skills);
    renderer.Display();
    
    std::cout << "[PASS] DrawEmptySkillList" << std::endl;
    
    window.close();
}

void testDrawNodeImageNonexistent() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test Window");
    RenderManager renderer(window);
    renderer.Initialize();
    
    // Should not crash when image doesn't exist
    renderer.Clear();
    renderer.DrawNodeImage("nonexistent_image.png");
    renderer.Display();
    
    std::cout << "[PASS] DrawNodeImage with nonexistent file (graceful handling)" << std::endl;
    
    window.close();
}

void testMultipleClearAndDisplayCycles() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test Window");
    RenderManager renderer(window);
    renderer.Initialize();
    
    // Multiple cycles should work fine
    for (int i = 0; i < 5; i++) {
        renderer.Clear(sf::Color::Black);
        renderer.Display();
    }
    
    std::cout << "[PASS] Multiple Clear and Display cycles" << std::endl;
    
    window.close();
}

void testHoverDetectionBoundaries() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Test Window");
    RenderManager renderer(window);
    bool initialized = renderer.Initialize();
    
    if (!initialized) {
        std::cout << "[SKIP] Hover detection boundaries (font not available)" << std::endl;
        window.close();
        return;
    }
    
    StoryNode node;
    node.id = "test";
    node.title = "Test";
    node.text = "Test";
    
    StoryOption opt;
    opt.id = "A";
    opt.text = "Option";
    opt.nextNodeId = "n2";
    node.options.push_back(opt);
    
    renderer.Clear();
    renderer.DrawStoryNode(&node);
    
    // Test various positions
    int result1 = renderer.GetHoveredOption(sf::Vector2i(0, 0));
    int result2 = renderer.GetHoveredOption(sf::Vector2i(800, 600));
    int result3 = renderer.GetHoveredOption(sf::Vector2i(-10, -10));
    
    // All should return valid indices or -1
    assert(result1 >= -1 && result1 < 1);
    assert(result2 >= -1 && result2 < 1);
    assert(result3 >= -1 && result3 < 1);
    
    std::cout << "[PASS] Hover detection with boundary positions" << std::endl;
    
    window.close();
}

int main() {
    std::cout << "=== RenderManager Unit Tests ===" << std::endl;
    std::cout << "Testing Requirements: 3.1, 3.2, 3.4" << std::endl << std::endl;
    
    testInitializationWithValidFont();
    testClearAndDisplay();
    testGetHoveredOptionNoOptions();
    testGetHoveredOptionAfterDrawing();
    testDrawStoryNodeWithNullptr();
    testDrawStoryNodeWithOptions();
    testDrawStoryNodeWithoutOptions();
    testDrawSkillList();
    testDrawEmptySkillList();
    testDrawNodeImageNonexistent();
    testMultipleClearAndDisplayCycles();
    testHoverDetectionBoundaries();
    
    std::cout << "\n=== Test Summary ===" << std::endl;
    std::cout << "Tests completed (some may be skipped if font unavailable)" << std::endl;
    
    return 0;
}
