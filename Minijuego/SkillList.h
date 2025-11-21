#pragma once
#include <string>
#include "Node.h"

class SkillList
{
public:
    SkillList();
    ~SkillList();

	// Add skill to the end of the list
    void AddSkill(const std::string& data);

    // Delete skill at index 0
    void DeleteHead();

    // Delete skill by index (0, 1, 2, ...)
    bool DeleteSkillAt(int index);

	// Replace skill at index with new data
    bool ReplaceSkillAt(int index, const std::string& newData);

	// Show all skills in the list
    void Show() const;

	// Empty the entire list
    void Clear();

	// Count the number of skills in the list
    int Count() const;

private:
    Node* head;
};