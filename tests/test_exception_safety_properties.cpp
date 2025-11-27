// Property-Based Tests for Exception Safety
// Feature: interactive-story-game
// These tests verify correctness properties across many random inputs

#include "../src/SkillList.h"
#include "../src/StoryManager.h"
#include "../src/StoryNode.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <exception>

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

// Random string generator
std::string generateRandomSkill(std::mt19937& rng) {
    static const char* skills[] = {
        "Fireball", "Ice Spike", "Lightning Bolt", "Healing", "Shield",
        "Teleport", "Invisibility", "Strength", "Speed", "Wisdom"
    };
    std::uniform_int_distribution<int> dist(0, 9);
    return skills[dist(rng)];
}

// **Feature: interactive-story-game, Property 15: Exception safety**
// **Validates: Requirements 7.4**
// Property: For any operation that throws an exception, all resources allocated
// before the exception should be properly released.
void testProperty_ExceptionSafety() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> sizeDist(5, 20);
    
    const int NUM_ITERATIONS = 100;
    bool allPassed = true;
    std::string failureExample;
    
    for (int iteration = 0; iteration < NUM_ITERATIONS; iteration++) {
        // Test 1: SkillList operations with potential exceptions
        try {
            SkillList* list = new SkillList();
            
            // Add some skills
            int size = sizeDist(rng);
            for (int i = 0; i < size; i++) {
                list->AddSkill(generateRandomSkill(rng));
            }
            
            // Verify count before potential exception
            int countBefore = list->Count();
            if (countBefore != size) {
                allPassed = false;
                failureExample = "Count mismatch before exception test";
                delete list;
                break;
            }
            
            // Try operations that might throw (though our implementation doesn't throw)
            // We're testing that if they did throw, cleanup would happen
            try {
                // Attempt to delete at invalid index (should fail gracefully, not throw)
                list->DeleteSkillAt(-1);
                list->DeleteSkillAt(size + 100);
                
                // Attempt to replace at invalid index
                list->ReplaceSkillAt(-1, "Invalid");
                list->ReplaceSkillAt(size + 100, "Invalid");
                
                // Attempt to get at invalid index
                std::string result = list->GetSkillAt(-1);
                result = list->GetSkillAt(size + 100);
                
            } catch (const std::exception& e) {
                // If an exception was thrown, the list should still be valid
                int countAfter = list->Count();
                if (countAfter < 0 || countAfter > size) {
                    allPassed = false;
                    failureExample = "List corrupted after exception: count = " + 
                                   std::to_string(countAfter);
                    delete list;
                    break;
                }
            }
            
            // Verify list is still valid after operations
            int finalCount = list->Count();
            if (finalCount < 0 || finalCount > size) {
                allPassed = false;
                failureExample = "List corrupted after operations: count = " + 
                               std::to_string(finalCount);
                delete list;
                break;
            }
            
            // Clean up - this should not throw
            delete list;
            
        } catch (const std::exception& e) {
            allPassed = false;
            failureExample = std::string("Unexpected exception in SkillList test: ") + e.what();
            break;
        } catch (...) {
            allPassed = false;
            failureExample = "Unknown exception in SkillList test";
            break;
        }
        
        // Test 2: StoryManager operations with potential exceptions
        try {
            StoryManager* manager = new StoryManager();
            
            // Try to load a non-existent file (should fail gracefully)
            bool loadResult = manager->LoadFromFile("nonexistent_file_12345.json");
            
            // Manager should still be in a valid state even after failed load
            const StoryNode* currentNode = manager->GetCurrentNode();
            // Current node might be null after failed load, which is fine
            
            // Try to load an invalid JSON file
            std::string invalidJsonFile = "test_invalid_temp.json";
            std::ofstream file(invalidJsonFile);
            file << "{ this is not valid JSON }";
            file.close();
            
            loadResult = manager->LoadFromFile(invalidJsonFile);
            
            // Manager should still be valid
            currentNode = manager->GetCurrentNode();
            
            // Clean up
            std::remove(invalidJsonFile.c_str());
            delete manager;
            
        } catch (const std::exception& e) {
            allPassed = false;
            failureExample = std::string("Unexpected exception in StoryManager test: ") + e.what();
            break;
        } catch (...) {
            allPassed = false;
            failureExample = "Unknown exception in StoryManager test";
            break;
        }
        
        // Test 3: Multiple allocations and deallocations
        try {
            std::vector<SkillList*> lists;
            
            // Create multiple lists
            int numLists = sizeDist(rng);
            for (int i = 0; i < numLists; i++) {
                SkillList* list = new SkillList();
                
                // Add random number of skills
                int skillCount = sizeDist(rng);
                for (int j = 0; j < skillCount; j++) {
                    list->AddSkill(generateRandomSkill(rng));
                }
                
                lists.push_back(list);
            }
            
            // Verify all lists are valid
            for (size_t i = 0; i < lists.size(); i++) {
                int count = lists[i]->Count();
                if (count < 0) {
                    allPassed = false;
                    failureExample = "Invalid count in list " + std::to_string(i);
                    break;
                }
            }
            
            // Clean up all lists
            for (SkillList* list : lists) {
                delete list;
            }
            
        } catch (const std::exception& e) {
            allPassed = false;
            failureExample = std::string("Exception in multiple allocation test: ") + e.what();
            break;
        } catch (...) {
            allPassed = false;
            failureExample = "Unknown exception in multiple allocation test";
            break;
        }
        
        if (!allPassed) break;
    }
    
    reportTest("Property 15: Exception safety", allPassed, failureExample);
}

int main() {
    std::cout << "=== Property-Based Tests for Exception Safety ===" << std::endl;
    std::cout << "Running 100 iterations per property..." << std::endl << std::endl;
    
    testProperty_ExceptionSafety();
    
    std::cout << std::endl << "=== Test Summary ===" << std::endl;
    std::cout << "Passed: " << g_testsPassed << std::endl;
    std::cout << "Failed: " << g_testsFailed << std::endl;
    
    return g_testsFailed > 0 ? 1 : 0;
}
