// Unit tests for StoryNode
#include "../src/StoryNode.h"
#include <iostream>
#include <cassert>

void testStoryNodeConstruction() {
    StoryNode node;
    assert(node.id.empty());
    assert(node.title.empty());
    assert(node.text.empty());
    assert(node.options.empty());
    assert(node.isEnding == false);
    assert(node.outcome.empty());
    assert(node.endingText.empty());
    std::cout << "[PASS] StoryNode construction" << std::endl;
}

void testHasOptions() {
    StoryNode node;
    
    // Empty node should have no options
    assert(node.HasOptions() == false);
    
    // Add an option
    StoryOption opt;
    opt.id = "A";
    opt.text = "Go left";
    opt.nextNodeId = "n2";
    node.options.push_back(opt);
    
    // Now should have options
    assert(node.HasOptions() == true);
    
    std::cout << "[PASS] HasOptions()" << std::endl;
}

void testGetOption() {
    StoryNode node;
    
    // Add multiple options
    StoryOption opt1;
    opt1.id = "A";
    opt1.text = "Go left";
    opt1.nextNodeId = "n2";
    node.options.push_back(opt1);
    
    StoryOption opt2;
    opt2.id = "B";
    opt2.text = "Go right";
    opt2.nextNodeId = "n3";
    node.options.push_back(opt2);
    
    // Test finding existing option
    const StoryOption* found = node.GetOption("A");
    assert(found != nullptr);
    assert(found->id == "A");
    assert(found->text == "Go left");
    assert(found->nextNodeId == "n2");
    
    // Test finding another option
    found = node.GetOption("B");
    assert(found != nullptr);
    assert(found->id == "B");
    
    // Test not finding non-existent option
    found = node.GetOption("C");
    assert(found == nullptr);
    
    std::cout << "[PASS] GetOption()" << std::endl;
}

void testStoryNodeWithEnding() {
    StoryNode node;
    node.id = "ending1";
    node.title = "The End";
    node.text = "You have reached the end.";
    node.isEnding = true;
    node.outcome = "final_bueno";
    node.endingText = "Congratulations!";
    
    assert(node.isEnding == true);
    assert(node.outcome == "final_bueno");
    assert(node.HasOptions() == false);
    
    std::cout << "[PASS] StoryNode with ending" << std::endl;
}

int main() {
    std::cout << "=== StoryNode Unit Tests ===" << std::endl;
    
    testStoryNodeConstruction();
    testHasOptions();
    testGetOption();
    testStoryNodeWithEnding();
    
    std::cout << "\nAll tests passed!" << std::endl;
    return 0;
}
