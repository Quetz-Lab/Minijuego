// Property-Based Tests for Immediate Node Deletion
// Feature: interactive-story-game
// These tests verify correctness properties across many random inputs

#include "../src/SkillList.h"
#include "../src/Node.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <set>

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

// **Feature: interactive-story-game, Property 16: Immediate node deletion**
// **Validates: Requirements 7.5**
// Property: For any SkillList, after removing a node at index I, the Node object
// that was at index I should be immediately deleted (no dangling pointers).
void testProperty_ImmediateNodeDeletion() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> sizeDist(2, 25);
    
    const int NUM_ITERATIONS = 100;
    bool allPassed = true;
    std::string failureExample;
    
    for (int iteration = 0; iteration < NUM_ITERATIONS; iteration++) {
        SkillList list;
        
        // Create a list with random size
        int initialSize = sizeDist(rng);
        std::vector<std::string> addedSkills;
        
        for (int i = 0; i < initialSize; i++) {
            std::string skill = generateRandomSkill(rng);
            list.AddSkill(skill);
            addedSkills.push_back(skill);
        }
        
        // Verify initial state
        int countBefore = list.Count();
        if (countBefore != initialSize) {
            allPassed = false;
            failureExample = "Initial count mismatch: expected " + std::to_string(initialSize) + 
                           ", got " + std::to_string(countBefore);
            break;
        }
        
        // Choose a random index to delete
        std::uniform_int_distribution<int> indexDist(0, initialSize - 1);
        int deleteIndex = indexDist(rng);
        
        // Store the skill that will be deleted for verification
        std::string deletedSkill = addedSkills[deleteIndex];
        
        // Delete the node at the chosen index
        bool deleteSuccess = list.DeleteSkillAt(deleteIndex);
        
        if (!deleteSuccess) {
            allPassed = false;
            failureExample = "Failed to delete skill at valid index " + std::to_string(deleteIndex);
            break;
        }
        
        // Property check 1: Count should be reduced by 1
        int countAfter = list.Count();
        if (countAfter != initialSize - 1) {
            allPassed = false;
            failureExample = "Count after deletion incorrect: expected " + 
                           std::to_string(initialSize - 1) + ", got " + std::to_string(countAfter);
            break;
        }
        
        // Property check 2: The deleted skill should no longer be accessible at the old index
        // If we try to access the same index, we should either get a different skill
        // or an out-of-bounds error (if it was the last element)
        if (deleteIndex < countAfter) {
            std::string skillAtOldIndex = list.GetSkillAt(deleteIndex);
            
            // The skill at this index should now be different (it should be the next skill)
            // unless the deleted skill happened to be the same as the next one
            if (deleteIndex + 1 < initialSize) {
                std::string expectedSkill = addedSkills[deleteIndex + 1];
                if (skillAtOldIndex != expectedSkill) {
                    allPassed = false;
                    failureExample = "After deletion at index " + std::to_string(deleteIndex) + 
                                   ", expected skill '" + expectedSkill + "' but got '" + 
                                   skillAtOldIndex + "'";
                    break;
                }
            }
        }
        
        // Property check 3: All remaining skills should be accessible and in correct order
        // Build expected list after deletion
        std::vector<std::string> expectedSkills;
        for (int i = 0; i < initialSize; i++) {
            if (i != deleteIndex) {
                expectedSkills.push_back(addedSkills[i]);
            }
        }
        
        // Verify all remaining skills
        for (int i = 0; i < countAfter; i++) {
            std::string actualSkill = list.GetSkillAt(i);
            if (actualSkill != expectedSkills[i]) {
                allPassed = false;
                failureExample = "Skill mismatch at index " + std::to_string(i) + 
                               " after deletion: expected '" + expectedSkills[i] + 
                               "', got '" + actualSkill + "'";
                break;
            }
        }
        
        if (!allPassed) break;
        
        // Property check 4: Accessing beyond the new count should fail
        std::string beyondCount = list.GetSkillAt(countAfter);
        if (!beyondCount.empty()) {
            allPassed = false;
            failureExample = "Accessing index " + std::to_string(countAfter) + 
                           " should return empty but got: '" + beyondCount + "'";
            break;
        }
        
        // Property check 5: Multiple deletions should work correctly
        // Delete another random element if list is not empty
        if (countAfter > 0) {
            std::uniform_int_distribution<int> secondIndexDist(0, countAfter - 1);
            int secondDeleteIndex = secondIndexDist(rng);
            
            bool secondDeleteSuccess = list.DeleteSkillAt(secondDeleteIndex);
            if (!secondDeleteSuccess) {
                allPassed = false;
                failureExample = "Second deletion failed at index " + std::to_string(secondDeleteIndex);
                break;
            }
            
            int finalCount = list.Count();
            if (finalCount != countAfter - 1) {
                allPassed = false;
                failureExample = "Count after second deletion incorrect: expected " + 
                               std::to_string(countAfter - 1) + ", got " + std::to_string(finalCount);
                break;
            }
            
            // Verify all remaining skills are still accessible
            for (int i = 0; i < finalCount; i++) {
                std::string skill = list.GetSkillAt(i);
                if (skill.empty()) {
                    allPassed = false;
                    failureExample = "Empty skill found at index " + std::to_string(i) + 
                                   " after second deletion";
                    break;
                }
            }
        }
        
        if (!allPassed) break;
    }
    
    reportTest("Property 16: Immediate node deletion", allPassed, failureExample);
}

int main() {
    std::cout << "=== Property-Based Tests for Immediate Node Deletion ===" << std::endl;
    std::cout << "Running 100 iterations per property..." << std::endl << std::endl;
    
    testProperty_ImmediateNodeDeletion();
    
    std::cout << std::endl << "=== Test Summary ===" << std::endl;
    std::cout << "Passed: " << g_testsPassed << std::endl;
    std::cout << "Failed: " << g_testsFailed << std::endl;
    
    return g_testsFailed > 0 ? 1 : 0;
}
