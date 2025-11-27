// Unit tests for SkillList
// Requirements: 4.2, 4.4
#include "../src/SkillList.h"
#include <iostream>
#include <cassert>
#include <sstream>

// Helper to suppress console output during tests
class OutputSuppressor {
public:
    OutputSuppressor() : oldBuf(std::cout.rdbuf()) {
        std::cout.rdbuf(buffer.rdbuf());
    }
    ~OutputSuppressor() {
        std::cout.rdbuf(oldBuf);
    }
private:
    std::stringstream buffer;
    std::streambuf* oldBuf;
};

void testEmptyList() {
    SkillList list;
    assert(list.Count() == 0);
    std::cout << "[PASS] Empty list initialization" << std::endl;
}

void testAddSingleSkill() {
    SkillList list;
    list.AddSkill("Fireball");
    
    assert(list.Count() == 1);
    assert(list.GetSkillAt(0) == "Fireball");
    
    std::cout << "[PASS] Add single skill" << std::endl;
}

void testAddMultipleSkills() {
    SkillList list;
    list.AddSkill("Fireball");
    list.AddSkill("Ice Spike");
    list.AddSkill("Healing");
    
    assert(list.Count() == 3);
    assert(list.GetSkillAt(0) == "Fireball");
    assert(list.GetSkillAt(1) == "Ice Spike");
    assert(list.GetSkillAt(2) == "Healing");
    
    std::cout << "[PASS] Add multiple skills" << std::endl;
}

void testDeleteHead() {
    SkillList list;
    list.AddSkill("First");
    list.AddSkill("Second");
    list.AddSkill("Third");
    
    list.DeleteHead();
    
    assert(list.Count() == 2);
    assert(list.GetSkillAt(0) == "Second");
    assert(list.GetSkillAt(1) == "Third");
    
    std::cout << "[PASS] Delete head" << std::endl;
}

void testDeleteHeadFromEmptyList() {
    SkillList list;
    
    // Should not crash
    list.DeleteHead();
    assert(list.Count() == 0);
    
    std::cout << "[PASS] Delete head from empty list (graceful)" << std::endl;
}

void testDeleteSkillAtBeginning() {
    SkillList list;
    list.AddSkill("First");
    list.AddSkill("Second");
    list.AddSkill("Third");
    
    bool result = list.DeleteSkillAt(0);
    
    assert(result == true);
    assert(list.Count() == 2);
    assert(list.GetSkillAt(0) == "Second");
    
    std::cout << "[PASS] Delete skill at beginning" << std::endl;
}

void testDeleteSkillAtMiddle() {
    SkillList list;
    list.AddSkill("First");
    list.AddSkill("Second");
    list.AddSkill("Third");
    
    bool result = list.DeleteSkillAt(1);
    
    assert(result == true);
    assert(list.Count() == 2);
    assert(list.GetSkillAt(0) == "First");
    assert(list.GetSkillAt(1) == "Third");
    
    std::cout << "[PASS] Delete skill at middle" << std::endl;
}

void testDeleteSkillAtEnd() {
    SkillList list;
    list.AddSkill("First");
    list.AddSkill("Second");
    list.AddSkill("Third");
    
    bool result = list.DeleteSkillAt(2);
    
    assert(result == true);
    assert(list.Count() == 2);
    assert(list.GetSkillAt(0) == "First");
    assert(list.GetSkillAt(1) == "Second");
    
    std::cout << "[PASS] Delete skill at end" << std::endl;
}

void testDeleteSkillAtInvalidIndex() {
    SkillList list;
    list.AddSkill("First");
    list.AddSkill("Second");
    
    bool result1 = list.DeleteSkillAt(-1);
    bool result2 = list.DeleteSkillAt(5);
    
    assert(result1 == false);
    assert(result2 == false);
    assert(list.Count() == 2);  // List unchanged
    
    std::cout << "[PASS] Delete skill at invalid index (returns false)" << std::endl;
}

void testReplaceSkillAtValidIndex() {
    SkillList list;
    list.AddSkill("Fireball");
    list.AddSkill("Ice Spike");
    list.AddSkill("Healing");
    
    bool result = list.ReplaceSkillAt(1, "Lightning Bolt");
    
    assert(result == true);
    assert(list.Count() == 3);
    assert(list.GetSkillAt(0) == "Fireball");
    assert(list.GetSkillAt(1) == "Lightning Bolt");
    assert(list.GetSkillAt(2) == "Healing");
    
    std::cout << "[PASS] Replace skill at valid index" << std::endl;
}

void testReplaceSkillAtInvalidIndex() {
    SkillList list;
    list.AddSkill("Fireball");
    
    bool result1 = list.ReplaceSkillAt(-1, "New Skill");
    bool result2 = list.ReplaceSkillAt(5, "New Skill");
    
    assert(result1 == false);
    assert(result2 == false);
    assert(list.Count() == 1);
    assert(list.GetSkillAt(0) == "Fireball");  // Unchanged
    
    std::cout << "[PASS] Replace skill at invalid index (returns false)" << std::endl;
}

void testClearList() {
    SkillList list;
    list.AddSkill("Skill1");
    list.AddSkill("Skill2");
    list.AddSkill("Skill3");
    
    assert(list.Count() == 3);
    
    list.Clear();
    
    assert(list.Count() == 0);
    
    std::cout << "[PASS] Clear list" << std::endl;
}

void testClearEmptyList() {
    SkillList list;
    
    // Should not crash
    list.Clear();
    assert(list.Count() == 0);
    
    std::cout << "[PASS] Clear empty list (graceful)" << std::endl;
}

void testCountWithDifferentSizes() {
    SkillList list;
    
    assert(list.Count() == 0);
    
    list.AddSkill("Skill1");
    assert(list.Count() == 1);
    
    list.AddSkill("Skill2");
    assert(list.Count() == 2);
    
    list.AddSkill("Skill3");
    assert(list.Count() == 3);
    
    list.DeleteHead();
    assert(list.Count() == 2);
    
    list.Clear();
    assert(list.Count() == 0);
    
    std::cout << "[PASS] Count with different sizes" << std::endl;
}

void testGetSkillAtInvalidIndex() {
    SkillList list;
    list.AddSkill("Skill1");
    
    std::string result1 = list.GetSkillAt(-1);
    std::string result2 = list.GetSkillAt(5);
    
    assert(result1.empty());
    assert(result2.empty());
    
    std::cout << "[PASS] GetSkillAt invalid index (returns empty string)" << std::endl;
}

void testShowMethod() {
    OutputSuppressor suppressor;
    
    SkillList list;
    list.AddSkill("Skill1");
    list.AddSkill("Skill2");
    
    // Should not crash
    list.Show();
    
    std::cout << "[PASS] Show method executes without crash" << std::endl;
}

void testMemoryManagement() {
    // Test that destructor properly cleans up
    {
        SkillList list;
        list.AddSkill("Skill1");
        list.AddSkill("Skill2");
        list.AddSkill("Skill3");
        // Destructor called here
    }
    
    // If we reach here without crash, memory was managed correctly
    std::cout << "[PASS] Memory management (destructor cleanup)" << std::endl;
}

int main() {
    std::cout << "=== SkillList Unit Tests ===" << std::endl;
    std::cout << "Testing Requirements: 4.2, 4.4" << std::endl << std::endl;
    
    testEmptyList();
    testAddSingleSkill();
    testAddMultipleSkills();
    testDeleteHead();
    testDeleteHeadFromEmptyList();
    testDeleteSkillAtBeginning();
    testDeleteSkillAtMiddle();
    testDeleteSkillAtEnd();
    testDeleteSkillAtInvalidIndex();
    testReplaceSkillAtValidIndex();
    testReplaceSkillAtInvalidIndex();
    testClearList();
    testClearEmptyList();
    testCountWithDifferentSizes();
    testGetSkillAtInvalidIndex();
    testShowMethod();
    testMemoryManagement();
    
    std::cout << "\n=== Test Summary ===" << std::endl;
    std::cout << "All 17 tests passed!" << std::endl;
    
    return 0;
}
