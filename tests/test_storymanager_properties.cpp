// Property-Based Tests for StoryManager
// Feature: interactive-story-game
// These tests verify correctness properties across many random inputs

#include "../src/StoryManager.h"
#include "../src/StoryNode.h"
#include "../src/json.hpp"
#include <iostream>
#include <fstream>
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

// Helper to create a temporary JSON file with N nodes
std::string createTestStoryJSON(int numNodes, const std::string& startNodeId, std::mt19937& rng) {
    nlohmann::json j;
    j["startNodeId"] = startNodeId;
    j["nodes"] = nlohmann::json::array();
    
    std::uniform_int_distribution<int> optionCountDist(0, 3);
    
    for (int i = 0; i < numNodes; i++) {
        std::string nodeId = "n" + std::to_string(i + 1);
        nlohmann::json node;
        node["id"] = nodeId;
        node["title"] = "Título " + std::to_string(i + 1);
        node["text"] = "Texto del nodo " + std::to_string(i + 1);
        
        // Add random options (except for last node which is an ending)
        if (i < numNodes - 1) {
            int numOptions = optionCountDist(rng);
            node["options"] = nlohmann::json::array();
            
            for (int opt = 0; opt < numOptions; opt++) {
                nlohmann::json option;
                option["id"] = std::string(1, 'A' + opt);
                option["text"] = "Opción " + std::string(1, 'A' + opt);
                
                // Point to next node or random node
                std::uniform_int_distribution<int> nextNodeDist(i + 1, numNodes - 1);
                int nextNodeIdx = nextNodeDist(rng);
                option["nextNodeId"] = "n" + std::to_string(nextNodeIdx + 1);
                
                node["options"].push_back(option);
            }
        } else {
            // Last node is an ending
            node["ending"] = true;
            node["outcome"] = "final_test";
            node["textEnding"] = "Final del test";
        }
        
        j["nodes"].push_back(node);
    }
    
    // Write to temporary file
    std::string filename = "test_story_temp.json";
    std::ofstream file(filename);
    file << j.dump(2);
    file.close();
    
    return filename;
}

// Helper to clean up temporary file
void cleanupTestFile(const std::string& filename) {
    std::remove(filename.c_str());
}

// **Feature: interactive-story-game, Property 1: Node count consistency**
// **Validates: Requirements 1.2**
// Property: For any valid story JSON file with N nodes, parsing should create
// exactly N StoryNode objects accessible in the system.
void testProperty_NodeCountConsistency() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> nodeDist(2, 20); // At least 2 nodes to avoid ending node issue
    
    const int NUM_ITERATIONS = 100;
    bool allPassed = true;
    std::string failureExample;
    
    for (int iteration = 0; iteration < NUM_ITERATIONS; iteration++) {
        int expectedNodeCount = nodeDist(rng);
        std::string startNodeId = "n1";
        
        // Create test JSON file
        std::string filename = createTestStoryJSON(expectedNodeCount, startNodeId, rng);
        
        // Load the story
        StoryManager manager;
        bool loadSuccess = manager.LoadFromFile(filename);
        
        if (!loadSuccess) {
            allPassed = false;
            failureExample = "Failed to load valid JSON with " + std::to_string(expectedNodeCount) + " nodes";
            cleanupTestFile(filename);
            break;
        }
        
        // Count accessible nodes by trying to navigate to each expected node
        // We need to navigate from a non-ending node
        int actualNodeCount = 0;
        
        // First, go to the start node (which is not an ending)
        manager.Start();
        
        for (int i = 0; i < expectedNodeCount; i++) {
            std::string nodeId = "n" + std::to_string(i + 1);
            
            // For non-ending nodes, navigate to them
            if (i < expectedNodeCount - 1) {
                bool navSuccess = manager.NavigateToNode(nodeId);
                if (navSuccess) {
                    const StoryNode* node = manager.GetCurrentNode();
                    if (node && node->id == nodeId) {
                        actualNodeCount++;
                    }
                }
            } else {
                // For the ending node, navigate to it from a non-ending node
                manager.NavigateToNode("n1"); // Go back to start
                bool navSuccess = manager.NavigateToNode(nodeId);
                if (navSuccess) {
                    const StoryNode* node = manager.GetCurrentNode();
                    if (node && node->id == nodeId) {
                        actualNodeCount++;
                    }
                }
            }
        }
        
        // Property check: Count should match
        if (actualNodeCount != expectedNodeCount) {
            allPassed = false;
            failureExample = "Node count mismatch: expected " + std::to_string(expectedNodeCount) + 
                           ", got " + std::to_string(actualNodeCount);
            cleanupTestFile(filename);
            break;
        }
        
        cleanupTestFile(filename);
    }
    
    reportTest("Property 1: Node count consistency", allPassed, failureExample);
}

// **Feature: interactive-story-game, Property 2: UTF-8 round trip**
// **Validates: Requirements 1.4**
// Property: For any string containing UTF-8 Spanish characters (tildes, ñ, special symbols),
// parsing from JSON and converting back should preserve the exact character sequence.
void testProperty_UTF8RoundTrip() {
    std::random_device rd;
    std::mt19937 rng(rd());
    
    // Spanish characters to test
    std::vector<std::string> spanishStrings = {
        "El mago está en la torre",
        "¿Dónde está el dragón?",
        "¡Cuidado con la tormenta!",
        "Año nuevo, magia nueva",
        "Círculo de protección",
        "Señor de las ruinas",
        "Absorción de energía",
        "Más allá del horizonte",
        "José y María fueron al castillo",
        "El niño aprendió la lección"
    };
    
    const int NUM_ITERATIONS = 100;
    bool allPassed = true;
    std::string failureExample;
    
    for (int iteration = 0; iteration < NUM_ITERATIONS; iteration++) {
        // Pick a random Spanish string
        std::uniform_int_distribution<int> stringDist(0, spanishStrings.size() - 1);
        std::string originalText = spanishStrings[stringDist(rng)];
        
        // Create a simple JSON with this text
        nlohmann::json j;
        j["startNodeId"] = "n1";
        j["nodes"] = nlohmann::json::array();
        
        nlohmann::json node;
        node["id"] = "n1";
        node["title"] = originalText;
        node["text"] = originalText;
        node["ending"] = true;
        node["textEnding"] = originalText;
        
        j["nodes"].push_back(node);
        
        // Write to file
        std::string filename = "test_utf8_temp.json";
        std::ofstream file(filename);
        file << j.dump(2);
        file.close();
        
        // Load the story
        StoryManager manager;
        bool loadSuccess = manager.LoadFromFile(filename);
        
        if (!loadSuccess) {
            allPassed = false;
            failureExample = "Failed to load JSON with UTF-8 text: " + originalText;
            cleanupTestFile(filename);
            break;
        }
        
        // Get the node and check if text matches
        const StoryNode* node_ptr = manager.GetCurrentNode();
        if (!node_ptr) {
            allPassed = false;
            failureExample = "Current node is null";
            cleanupTestFile(filename);
            break;
        }
        
        // Property check: Text should be preserved exactly
        if (node_ptr->title != originalText) {
            allPassed = false;
            failureExample = "Title mismatch: expected '" + originalText + 
                           "', got '" + node_ptr->title + "'";
            cleanupTestFile(filename);
            break;
        }
        
        if (node_ptr->text != originalText) {
            allPassed = false;
            failureExample = "Text mismatch: expected '" + originalText + 
                           "', got '" + node_ptr->text + "'";
            cleanupTestFile(filename);
            break;
        }
        
        if (node_ptr->endingText != originalText) {
            allPassed = false;
            failureExample = "EndingText mismatch: expected '" + originalText + 
                           "', got '" + node_ptr->endingText + "'";
            cleanupTestFile(filename);
            break;
        }
        
        cleanupTestFile(filename);
    }
    
    reportTest("Property 2: UTF-8 round trip", allPassed, failureExample);
}

// **Feature: interactive-story-game, Property 3: Start node identification**
// **Validates: Requirements 1.5**
// Property: For any valid story JSON with a startNodeId field, after loading,
// the current node's ID should match the startNodeId value.
void testProperty_StartNodeIdentification() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> nodeDist(3, 15);
    std::uniform_int_distribution<int> startNodeDist(0, 10);
    
    const int NUM_ITERATIONS = 100;
    bool allPassed = true;
    std::string failureExample;
    
    for (int iteration = 0; iteration < NUM_ITERATIONS; iteration++) {
        int numNodes = nodeDist(rng);
        int startNodeIdx = startNodeDist(rng) % numNodes;
        std::string expectedStartNodeId = "n" + std::to_string(startNodeIdx + 1);
        
        // Create test JSON file with random start node
        std::string filename = createTestStoryJSON(numNodes, expectedStartNodeId, rng);
        
        // Load the story
        StoryManager manager;
        bool loadSuccess = manager.LoadFromFile(filename);
        
        if (!loadSuccess) {
            allPassed = false;
            failureExample = "Failed to load valid JSON";
            cleanupTestFile(filename);
            break;
        }
        
        // Property check: Current node should be the start node
        const StoryNode* currentNode = manager.GetCurrentNode();
        if (!currentNode) {
            allPassed = false;
            failureExample = "Current node is null after loading";
            cleanupTestFile(filename);
            break;
        }
        
        if (currentNode->id != expectedStartNodeId) {
            allPassed = false;
            failureExample = "Start node mismatch: expected '" + expectedStartNodeId + 
                           "', got '" + currentNode->id + "'";
            cleanupTestFile(filename);
            break;
        }
        
        cleanupTestFile(filename);
    }
    
    reportTest("Property 3: Start node identification", allPassed, failureExample);
}

// **Feature: interactive-story-game, Property 5: Navigation correctness**
// **Validates: Requirements 2.3**
// Property: For any StoryNode and any valid option on that node, selecting the option
// should transition to the node whose ID matches the option's nextNodeId.
void testProperty_NavigationCorrectness() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> nodeDist(5, 15);
    
    const int NUM_ITERATIONS = 100;
    bool allPassed = true;
    std::string failureExample;
    
    for (int iteration = 0; iteration < NUM_ITERATIONS; iteration++) {
        int numNodes = nodeDist(rng);
        std::string startNodeId = "n1";
        
        // Create test JSON file
        std::string filename = createTestStoryJSON(numNodes, startNodeId, rng);
        
        // Load the story
        StoryManager manager;
        bool loadSuccess = manager.LoadFromFile(filename);
        
        if (!loadSuccess) {
            allPassed = false;
            failureExample = "Failed to load valid JSON";
            cleanupTestFile(filename);
            break;
        }
        
        // Test navigation through several nodes
        manager.Start();
        
        for (int step = 0; step < 5 && step < numNodes - 1; step++) {
            const StoryNode* currentNode = manager.GetCurrentNode();
            
            if (!currentNode || currentNode->options.empty()) {
                break; // Reached ending or node without options
            }
            
            // Select first option
            const StoryOption& option = currentNode->options[0];
            std::string expectedNextNodeId = option.nextNodeId;
            
            // Navigate using SelectOption
            bool selectSuccess = manager.SelectOption(option.id);
            
            if (!selectSuccess) {
                allPassed = false;
                failureExample = "SelectOption failed for valid option '" + option.id + "'";
                cleanupTestFile(filename);
                break;
            }
            
            // Property check: Should be at the expected node
            const StoryNode* nextNode = manager.GetCurrentNode();
            if (!nextNode) {
                allPassed = false;
                failureExample = "Current node is null after navigation";
                cleanupTestFile(filename);
                break;
            }
            
            if (nextNode->id != expectedNextNodeId) {
                allPassed = false;
                failureExample = "Navigation mismatch: expected '" + expectedNextNodeId + 
                               "', got '" + nextNode->id + "'";
                cleanupTestFile(filename);
                break;
            }
        }
        
        if (!allPassed) break;
        
        cleanupTestFile(filename);
    }
    
    reportTest("Property 5: Navigation correctness", allPassed, failureExample);
}

// **Feature: interactive-story-game, Property 6: Ending node finality**
// **Validates: Requirements 2.4**
// Property: For any StoryNode with ending flag set to true, attempting to navigate
// to another node should fail or be prevented.
void testProperty_EndingNodeFinality() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> nodeDist(3, 10);
    
    const int NUM_ITERATIONS = 100;
    bool allPassed = true;
    std::string failureExample;
    
    for (int iteration = 0; iteration < NUM_ITERATIONS; iteration++) {
        int numNodes = nodeDist(rng);
        std::string startNodeId = "n1";
        
        // Create test JSON file (last node is always an ending)
        std::string filename = createTestStoryJSON(numNodes, startNodeId, rng);
        
        // Load the story
        StoryManager manager;
        bool loadSuccess = manager.LoadFromFile(filename);
        
        if (!loadSuccess) {
            allPassed = false;
            failureExample = "Failed to load valid JSON";
            cleanupTestFile(filename);
            break;
        }
        
        // Navigate to the ending node (last node)
        std::string endingNodeId = "n" + std::to_string(numNodes);
        bool navSuccess = manager.NavigateToNode(endingNodeId);
        
        if (!navSuccess) {
            allPassed = false;
            failureExample = "Failed to navigate to ending node";
            cleanupTestFile(filename);
            break;
        }
        
        // Verify it's an ending
        const StoryNode* endingNode = manager.GetCurrentNode();
        if (!endingNode || !endingNode->isEnding) {
            allPassed = false;
            failureExample = "Node is not marked as ending";
            cleanupTestFile(filename);
            break;
        }
        
        // Property check: Attempting to navigate from ending should fail
        bool shouldFail = manager.NavigateToNode("n1");
        
        if (shouldFail) {
            allPassed = false;
            failureExample = "Navigation from ending node should be prevented";
            cleanupTestFile(filename);
            break;
        }
        
        // Verify still at ending node
        const StoryNode* stillAtEnding = manager.GetCurrentNode();
        if (!stillAtEnding || stillAtEnding->id != endingNodeId) {
            allPassed = false;
            failureExample = "Current node changed after failed navigation from ending";
            cleanupTestFile(filename);
            break;
        }
        
        cleanupTestFile(filename);
    }
    
    reportTest("Property 6: Ending node finality", allPassed, failureExample);
}

int main() {
    std::cout << "=== Property-Based Tests for StoryManager ===" << std::endl;
    std::cout << "Running 100 iterations per property..." << std::endl << std::endl;
    
    testProperty_NodeCountConsistency();
    testProperty_UTF8RoundTrip();
    testProperty_StartNodeIdentification();
    testProperty_NavigationCorrectness();
    testProperty_EndingNodeFinality();
    
    std::cout << std::endl << "=== Test Summary ===" << std::endl;
    std::cout << "Passed: " << g_testsPassed << std::endl;
    std::cout << "Failed: " << g_testsFailed << std::endl;
    
    return g_testsFailed > 0 ? 1 : 0;
}
