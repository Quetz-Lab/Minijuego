#pragma once

#include <string>
#include <iostream>

struct SkillNode
{
    std::string data;
    SkillNode* next;

    SkillNode(const std::string& d)
        : data(d), next(nullptr)
    {
    }
};

class SkillList
{
public:
    SkillList();
    ~SkillList();

    void AddSkill(const std::string& skillName);
    bool RemoveLastSkill();
    bool RemoveSkillAt(int index);

    void PrintSkills() const;

private:
    SkillNode* m_head;
};
