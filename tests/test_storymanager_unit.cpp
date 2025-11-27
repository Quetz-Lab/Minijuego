// Unit tests for StoryManager
// Requirements: 1.3, 2.3
#include "../src/StoryManager.h"
#include <iostream>
#include <cassert>
#include <fstream>

// Helper function to create a temporary JSON file
void createTempJSONFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    file << content;
    file.close();
}

void testLoadValidJSON() {
    std::string validJSON = R"({
        "startNodeId": "n1",
        "nodes": [
            {
                "id": "n1",
                "title": "Test Node",
                "text": "This is a test node.",
                "options": [
                    {
                        "id": "A",
                        "text": "Go to node 2",
                        "nextNodeId": "n2"
                    }
                ]
            },
            {
                "id": "n2",
                "title": "Second Node",
                "text": "This is the second node.",
                "ending": true,
                "outcome": "test_ending",
                "textEnding": "Test ending text"
            }
        ]
    })";
    
    createTempJSONFile("test_story.json", validJSON);
    
    StoryManager manager;
    bool result = manager.LoadFromFile("test_story.json");
    
    assert(result == true);
    
    // Clean up
    std::remove("test_story.json");
    
    std::cout << "[PASS] Load valid JSON" << std::endl;
}

void testLoadInvalidJSONFile() {
    StoryManager manager;
    bool result = manager.LoadFromFile("nonexistent_file.json");
    
    assert(result == false);
    
    std::cout << "[PASS] Load invalid JSON file (returns false)" << std::endl;
}

void testLoadMalformedJSON() {
    std::string malformedJSON = R"({
        "startNodeId": "n1",
        "nodes": [
            {
                "id": "n1"
                "title": "Missing comma"
            }
        ]
    })";
    
    createTempJSONFile("test_malformed.json", malformedJSON);
    
    StoryManager manager;
    bool result = manager.LoadFromFile("test_malformed.json");
    
    assert(result == false);
    
    // Clean up
    std::remove("test_malformed.json");
    
    std::cout << "[PASS] Load malformed JSON (returns false)" << std::endl;
}

void testStartNavigation() {
    std::string validJSON = R"({
        "startNodeId": "start",
        "nodes": [
            {
                "id": "start",
                "title": "Beginning",
                "text": "The story begins.",
                "options": []
            }
        ]
    })";
    
    createTempJSONFile("test_start.json", validJSON);
    
    StoryManager manager;
    manager.LoadFromFile("test_start.json");
    manager.Start();
    
    const StoryNode* currentNode = manager.GetCurrentNode();
    assert(currentNode != nullptr);
    assert(currentNode->id == "start");
    assert(currentNode->title == "Beginning");
    
    // Clean up
    std::remove("test_start.json");
    
    std::cout << "[PASS] Start navigation" << std::endl;
}

void testNavigateToValidNode() {
    std::string validJSON = R"({
        "startNodeId": "n1",
        "nodes": [
            {
                "id": "n1",
                "title": "Node 1",
                "text": "First node.",
                "options": []
            },
            {
                "id": "n2",
                "title": "Node 2",
                "text": "Second node.",
                "options": []
            }
        ]
    })";
    
    createTempJSONFile("test_nav.json", validJSON);
    
    StoryManager manager;
    manager.LoadFromFile("test_nav.json");
    manager.Start();
    
    bool result = manager.NavigateToNode("n2");
    
    assert(result == true);
    const StoryNode* currentNode = manager.GetCurrentNode();
    assert(currentNode != nullptr);
    assert(currentNode->id == "n2");
    
    // Clean up
    std::remove("test_nav.json");
    
    std::cout << "[PASS] Navigate to valid node" << std::endl;
}

void testNavigateToInvalidNode() {
    std::string validJSON = R"({
        "startNodeId": "n1",
        "nodes": [
            {
                "id": "n1",
                "title": "Node 1",
                "text": "First node.",
                "options": []
            }
        ]
    })";
    
    createTempJSONFile("test_nav_invalid.json", validJSON);
    
    StoryManager manager;
    manager.LoadFromFile("test_nav_invalid.json");
    manager.Start();
    
    const StoryNode* beforeNav = manager.GetCurrentNode();
    bool result = manager.NavigateToNode("nonexistent");
    
    assert(result == false);
    // Current node should remain unchanged
    const StoryNode* afterNav = manager.GetCurrentNode();
    assert(afterNav == beforeNav);
    
    // Clean up
    std::remove("test_nav_invalid.json");
    
    std::cout << "[PASS] Navigate to invalid node (returns false, stays at current)" << std::endl;
}

void testSelectValidOption() {
    std::string validJSON = R"({
        "startNodeId": "n1",
        "nodes": [
            {
                "id": "n1",
                "title": "Node 1",
                "text": "First node.",
                "options": [
                    {
                        "id": "A",
                        "text": "Go to node 2",
                        "nextNodeId": "n2"
                    }
                ]
            },
            {
                "id": "n2",
                "title": "Node 2",
                "text": "Second node.",
                "options": []
            }
        ]
    })";
    
    createTempJSONFile("test_option.json", validJSON);
    
    StoryManager manager;
    manager.LoadFromFile("test_option.json");
    manager.Start();
    
    bool result = manager.SelectOption("A");
    
    assert(result == true);
    const StoryNode* currentNode = manager.GetCurrentNode();
    assert(currentNode != nullptr);
    assert(currentNode->id == "n2");
    
    // Clean up
    std::remove("test_option.json");
    
    std::cout << "[PASS] Select valid option" << std::endl;
}

void testSelectInvalidOption() {
    std::string validJSON = R"({
        "startNodeId": "n1",
        "nodes": [
            {
                "id": "n1",
                "title": "Node 1",
                "text": "First node.",
                "options": [
                    {
                        "id": "A",
                        "text": "Option A",
                        "nextNodeId": "n2"
                    }
                ]
            },
            {
                "id": "n2",
                "title": "Node 2",
                "text": "Second node.",
                "options": []
            }
        ]
    })";
    
    createTempJSONFile("test_option_invalid.json", validJSON);
    
    StoryManager manager;
    manager.LoadFromFile("test_option_invalid.json");
    manager.Start();
    
    const StoryNode* beforeSelect = manager.GetCurrentNode();
    bool result = manager.SelectOption("Z");  // Non-existent option
    
    assert(result == false);
    // Should stay at current node
    const StoryNode* afterSelect = manager.GetCurrentNode();
    assert(afterSelect == beforeSelect);
    
    // Clean up
    std::remove("test_option_invalid.json");
    
    std::cout << "[PASS] Select invalid option (returns false, stays at current)" << std::endl;
}

void testIsAtEnding() {
    std::string validJSON = R"({
        "startNodeId": "n1",
        "nodes": [
            {
                "id": "n1",
                "title": "Node 1",
                "text": "First node.",
                "options": [
                    {
                        "id": "A",
                        "text": "Go to ending",
                        "nextNodeId": "ending"
                    }
                ]
            },
            {
                "id": "ending",
                "title": "The End",
                "text": "Story ends.",
                "ending": true,
                "outcome": "final_test",
                "textEnding": "Test ending"
            }
        ]
    })";
    
    createTempJSONFile("test_ending.json", validJSON);
    
    StoryManager manager;
    manager.LoadFromFile("test_ending.json");
    manager.Start();
    
    assert(manager.IsAtEnding() == false);
    
    manager.SelectOption("A");
    
    assert(manager.IsAtEnding() == true);
    
    // Clean up
    std::remove("test_ending.json");
    
    std::cout << "[PASS] IsAtEnding detection" << std::endl;
}

void testGetCurrentNodeBeforeStart() {
    std::string validJSON = R"({
        "startNodeId": "n1",
        "nodes": [
            {
                "id": "n1",
                "title": "Node 1",
                "text": "First node.",
                "options": []
            }
        ]
    })";
    
    createTempJSONFile("test_before_start.json", validJSON);
    
    StoryManager manager;
    manager.LoadFromFile("test_before_start.json");
    
    // Before calling Start(), GetCurrentNode should return nullptr
    const StoryNode* node = manager.GetCurrentNode();
    assert(node == nullptr);
    
    // Clean up
    std::remove("test_before_start.json");
    
    std::cout << "[PASS] GetCurrentNode before Start (returns nullptr)" << std::endl;
}

void testUTF8Characters() {
    std::string utf8JSON = R"({
        "startNodeId": "n1",
        "nodes": [
            {
                "id": "n1",
                "title": "Título con tildes",
                "text": "Texto con ñ, á, é, í, ó, ú y ¿símbolos?",
                "options": []
            }
        ]
    })";
    
    createTempJSONFile("test_utf8.json", utf8JSON);
    
    StoryManager manager;
    bool result = manager.LoadFromFile("test_utf8.json");
    
    assert(result == true);
    manager.Start();
    
    const StoryNode* node = manager.GetCurrentNode();
    assert(node != nullptr);
    // Just verify it loaded without crashing
    assert(!node->title.empty());
    assert(!node->text.empty());
    
    // Clean up
    std::remove("test_utf8.json");
    
    std::cout << "[PASS] UTF-8 character handling" << std::endl;
}

int main() {
    std::cout << "=== StoryManager Unit Tests ===" << std::endl;
    std::cout << "Testing Requirements: 1.3, 2.3" << std::endl << std::endl;
    
    testLoadValidJSON();
    testLoadInvalidJSONFile();
    testLoadMalformedJSON();
    testStartNavigation();
    testNavigateToValidNode();
    testNavigateToInvalidNode();
    testSelectValidOption();
    testSelectInvalidOption();
    testIsAtEnding();
    testGetCurrentNodeBeforeStart();
    testUTF8Characters();
    
    std::cout << "\n=== Test Summary ===" << std::endl;
    std::cout << "All 11 tests passed!" << std::endl;
    
    return 0;
}
