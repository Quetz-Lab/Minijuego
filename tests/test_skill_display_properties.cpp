// Property-Based Tests for Skill Display Completeness
// Feature: interactive-story-game
// These tests verify correctness properties across many random inputs

#include "../src/SkillList.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>

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
        "Círculo de Luz", "Sello de Runas", "Absorción de Tormenta",
        "Portal Dimensional", "Barrera Mágica", "Rayo Cósmico"
    };
    std::uniform_int_distribution<int> dist(0, 15);
    return skills[dist(rng)];
}

// **Feature: interactive-story-game, Property 9: Skill display completeness**
// **Validates: Requirements 4.3**
// Property: For any SkillList with N skills, iterating through the list should
// yield exactly N skills with indices 0 through N-1.
void testProperty_SkillDisplayCompleteness() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> sizeDist(0, 30);
    
    const int NUM_ITERATIONS = 100;
    bool allPassed = true;
    std::string failureExample;
    
    for (int iteration = 0; iteration < NUM_ITERATIONS; iteration++) {
        SkillList list;
        
        // Create a list with random size
        int expectedSize = sizeDist(rng);
        std::vector<std::string> addedSkills;
        
        for (int i = 0; i < expectedSize; i++) {
            std::string skill = generateRandomSkill(rng);
            list.AddSkill(skill);
            addedSkills.push_back(skill);
        }
        
        // Property check 1: Count should match expected size
        int actualCount = list.Count();
        if (actualCount != expectedSize) {
            allPassed = false;
            failureExample = "Count mismatch: expected " + std::to_string(expectedSize) + 
                           ", got " + std::to_string(actualCount);
            break;
        }
        
        // Property check 2: All indices [0, N-1] should be accessible
        for (int i = 0; i < expectedSize; i++) {
            std::string skill = list.GetSkillAt(i);
            
            if (skill.empty()) {
                allPassed = false;
                failureExample = "Skill at index " + std::to_string(i) + 
                               " is empty (expected: '" + addedSkills[i] + "')";
                break;
            }
            
            // Verify it matches what we added
            if (skill != addedSkills[i]) {
                allPassed = false;
                failureExample = "Skill mismatch at index " + std::to_string(i) + 
                               ": expected '" + addedSkills[i] + "', got '" + skill + "'";
                break;
            }
        }
        
        if (!allPassed) break;
        
        // Property check 3: Index N should return empty (out of bounds)
        std::string outOfBounds = list.GetSkillAt(expectedSize);
        if (!outOfBounds.empty()) {
            allPassed = false;
            failureExample = "Index " + std::to_string(expectedSize) + 
                           " should be out of bounds but returned: '" + outOfBounds + "'";
            break;
        }
        
        // Property check 4: Negative index should return empty
        std::string negativeIndex = list.GetSkillAt(-1);
        if (!negativeIndex.empty()) {
            allPassed = false;
            failureExample = "Negative index should return empty but returned: '" + 
                           negativeIndex + "'";
            break;
        }
        
        // Property check 5: Iteration completeness - verify we can iterate through all skills
        // by checking that each index from 0 to N-1 is accessible exactly once
        std::vector<bool> indexAccessed(expectedSize, false);
        int iterationCount = 0;
        
        for (int i = 0; i < expectedSize; i++) {
            std::string skill = list.GetSkillAt(i);
            if (!skill.empty()) {
                indexAccessed[i] = true;
                iterationCount++;
            }
        }
        
        if (iterationCount != expectedSize) {
            allPassed = false;
            failureExample = "Iteration count mismatch: expected " + 
                           std::to_string(expectedSize) + " iterations, got " + 
                           std::to_string(iterationCount);
            break;
        }
        
        // Verify all indices were accessed
        for (int i = 0; i < expectedSize; i++) {
            if (!indexAccessed[i]) {
                allPassed = false;
                failureExample = "Index " + std::to_string(i) + " was not accessible during iteration";
                break;
            }
        }
        
        if (!allPassed) break;
    }
    
    reportTest("Property 9: Skill display completeness", allPassed, failureExample);
}

int main() {
    std::cout << "=== Property-Based Tests for Skill Display ===" << std::endl;
    std::cout << "Running 100 iterations per property..." << std::endl << std::endl;
    
    testProperty_SkillDisplayCompleteness();
    
    std::cout << std::endl << "=== Test Summary ===" << std::endl;
    std::cout << "Passed: " << g_testsPassed << std::endl;
    std::cout << "Failed: " << g_testsFailed << std::endl;
    
    return g_testsFailed > 0 ? 1 : 0;
}
