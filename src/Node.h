#pragma once
#include <string>

/**
 * @struct Node
 * @brief Node structure for the SkillList linked list
 * 
 * Simple singly-linked list node containing skill data and a pointer
 * to the next node. Used exclusively by SkillList class.
 */
struct Node
{
    std::string data; // Skill name
    Node* next;       // Pointer to the next node in the list

    Node(const std::string& data);
};
