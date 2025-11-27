// Property-Based Tests for SkillList
// Feature: interactive-story-game
// These tests verify correctness properties across many random inputs

#include "../src/SkillList.h"
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

// Random string generator
std::string generateRandomSkill(std::mt19937& rng) {
    static const char* skills[] = {
        "Fireball", "Ice Spike", "Lightning Bolt", "Healing", "Shield",
        "Teleport", "Invisibility", "Strength", "Speed", "Wisdom",
        "Círculo de Luz", "Sello de Runas", "Absorción de Tormenta"
    };
    std::uniform_int_distribution<int> dist(0, 12);
    return skills[dist(rng)];
}

// **Feature: interactive-story-game, Property 8: Skill addition increases count**
// **Validates: Requirements 4.2**
// Property: For any SkillList with count N, adding a skill should result in count N+1,
// and the new skill should be accessible at index N.
void testProperty_SkillAdditionIncreasesCount() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> initialSizeDist(0, 20);
    
    const int NUM_ITERATIONS = 100;
    bool allPassed = true;
    std::string failureExample;
    
    for (int iteration = 0; iteration < NUM_ITERATIONS; iteration++) {
        SkillList list;
        
        // Create a list with random initial size
        int initialSize = initialSizeDist(rng);
        std::vector<std::string> addedSkills;
        
        for (int i = 0; i < initialSize; i++) {
            std::string skill = generateRandomSkill(rng);
            list.AddSkill(skill);
            addedSkills.push_back(skill);
        }
        
        // Verify initial count
        int countBefore = list.Count();
        if (countBefore != initialSize) {
            allPassed = false;
            failureExample = "Initial count mismatch: expected " + std::to_string(initialSize) + 
                           ", got " + std::to_string(countBefore);
            break;
        }
        
        // Add a new skill
        std::string newSkill = generateRandomSkill(rng);
        list.AddSkill(newSkill);
        
        // Property check 1: Count should increase by 1
        int countAfter = list.Count();
        if (countAfter != countBefore + 1) {
            allPassed = false;
            failureExample = "Count did not increase by 1: before=" + std::to_string(countBefore) + 
                           ", after=" + std::to_string(countAfter);
            break;
        }
        
        // Property check 2: New skill should be accessible at index N
        std::string retrievedSkill = list.GetSkillAt(countBefore);
        if (retrievedSkill != newSkill) {
            allPassed = false;
            failureExample = "New skill not at correct index: expected '" + newSkill + 
                           "', got '" + retrievedSkill + "' at index " + std::to_string(countBefore);
            break;
        }
    }
    
    reportTest("Property 8: Skill addition increases count", allPassed, failureExample);
}

// **Feature: interactive-story-game, Property 10: List integrity after removal**
// **Validates: Requirements 4.4**
// Property: For any SkillList, after removing a skill at any valid index,
// traversing the list from head to end should visit all remaining nodes exactly once
// without encountering null pointers prematurely.
void testProperty_ListIntegrityAfterRemoval() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> sizeDist(1, 20);
    
    const int NUM_ITERATIONS = 100;
    bool allPassed = true;
    std::string failureExample;
    
    for (int iteration = 0; iteration < NUM_ITERATIONS; iteration++) {
        SkillList list;
        
        // Create a list with random size
        int initialSize = sizeDist(rng);
        std::vector<std::string> skills;
        
        for (int i = 0; i < initialSize; i++) {
            std::string skill = generateRandomSkill(rng);
            list.AddSkill(skill);
            skills.push_back(skill);
        }
        
        // Remove a skill at a random valid index
        std::uniform_int_distribution<int> indexDist(0, initialSize - 1);
        int removeIndex = indexDist(rng);
        
        bool removeSuccess = list.DeleteSkillAt(removeIndex);
        if (!removeSuccess) {
            allPassed = false;
            failureExample = "Failed to remove skill at valid index " + std::to_string(removeIndex);
            break;
        }
        
        // Property check 1: Count should be reduced by 1
        int newCount = list.Count();
        if (newCount != initialSize - 1) {
            allPassed = false;
            failureExample = "Count after removal incorrect: expected " + 
                           std::to_string(initialSize - 1) + ", got " + std::to_string(newCount);
            break;
        }
        
        // Property check 2: All remaining skills should be accessible
        for (int i = 0; i < newCount; i++) {
            std::string skill = list.GetSkillAt(i);
            if (skill.empty()) {
                allPassed = false;
                failureExample = "Null pointer encountered at index " + std::to_string(i) + 
                               " after removing index " + std::to_string(removeIndex);
                break;
            }
        }
        
        if (!allPassed) break;
        
        // Property check 3: Accessing beyond the new count should fail gracefully
        std::string beyondSkill = list.GetSkillAt(newCount);
        if (!beyondSkill.empty()) {
            allPassed = false;
            failureExample = "Accessing beyond count should return empty string";
            break;
        }
    }
    
    reportTest("Property 10: List integrity after removal", allPassed, failureExample);
}

// **Feature: interactive-story-game, Property 14: SkillList memory cleanup**
// **Validates: Requirements 7.1**
// Property: For any SkillList with N nodes, after destruction,
// all N Node objects should be deallocated (no memory leaks).
void testProperty_MemoryCleanup() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> sizeDist(1, 50);
    
    const int NUM_ITERATIONS = 100;
    bool allPassed = true;
    std::string failureExample;
    
    // Note: This test verifies that Clear() and destructor work without crashes
    // Actual memory leak detection requires tools like Valgrind or Visual Studio's
    // memory profiler. This test ensures the operations complete successfully.
    
    for (int iteration = 0; iteration < NUM_ITERATIONS; iteration++) {
        try {
            SkillList* list = new SkillList();
            
            // Create a list with random size
            int size = sizeDist(rng);
            
            for (int i = 0; i < size; i++) {
                std::string skill = generateRandomSkill(rng);
                list->AddSkill(skill);
            }
            
            // Verify count
            int count = list->Count();
            if (count != size) {
                allPassed = false;
                failureExample = "Count mismatch before cleanup: expected " + 
                               std::to_string(size) + ", got " + std::to_string(count);
                delete list;
                break;
            }
            
            // Test Clear() method
            list->Clear();
            int countAfterClear = list->Count();
            if (countAfterClear != 0) {
                allPassed = false;
                failureExample = "Clear() did not empty the list: count = " + 
                               std::to_string(countAfterClear);
                delete list;
                break;
            }
            
            // Test destructor (should not crash)
            delete list;
            
        } catch (const std::exception& e) {
            allPassed = false;
            failureExample = std::string("Exception during memory cleanup: ") + e.what();
            break;
        } catch (...) {
            allPassed = false;
            failureExample = "Unknown exception during memory cleanup";
            break;
        }
    }
    
    reportTest("Property 14: SkillList memory cleanup", allPassed, failureExample);
}

int main() {
    std::cout << "=== Property-Based Tests for SkillList ===" << std::endl;
    std::cout << "Running 100 iterations per property..." << std::endl << std::endl;
    
    // Suppress SkillList output during tests
    std::cout.setstate(std::ios_base::failbit);
    
    testProperty_SkillAdditionIncreasesCount();
    testProperty_ListIntegrityAfterRemoval();
    testProperty_MemoryCleanup();
    
    // Re-enable output
    std::cout.clear();
    
    std::cout << std::endl << "=== Test Summary ===" << std::endl;
    std::cout << "Passed: " << g_testsPassed << std::endl;
    std::cout << "Failed: " << g_testsFailed << std::endl;
    
    return g_testsFailed > 0 ? 1 : 0;
}
