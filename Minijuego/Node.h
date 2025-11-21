#pragma once
#include <string>
struct Node
{
	std::string data; // Skill name
	Node* next;    // Pointer to the next node in the list

	Node(const std::string& data);
};

