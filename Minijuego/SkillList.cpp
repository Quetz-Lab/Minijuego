#include "SkillList.h"

SkillList::SkillList()
    : m_head(nullptr)
{
}

SkillList::~SkillList()
{
    SkillNode* current = m_head;
    while (current != nullptr)
    {
        SkillNode* next = current->next;
        delete current;
        current = next;
    }
    m_head = nullptr;
}

void SkillList::AddSkill(const std::string& skillName)
{
    SkillNode* newNode = new SkillNode(skillName);

    if (m_head == nullptr)
    {
        m_head = newNode;
    }
    else
    {
        SkillNode* temp = m_head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    std::cout << "Added skill: " << skillName << std::endl;
}

bool SkillList::RemoveLastSkill()
{
    if (m_head == nullptr)
        return false;

    if (m_head->next == nullptr)
    {
        std::cout << "Removing skill: " << m_head->data << std::endl;
        delete m_head;
        m_head = nullptr;
        return true;
    }

    SkillNode* temp = m_head;
    while (temp->next->next != nullptr)
    {
        temp = temp->next;
    }

    std::cout << "Removing skill: " << temp->next->data << std::endl;
    delete temp->next;
    temp->next = nullptr;
    return true;
}

bool SkillList::RemoveSkillAt(int index)
{
    if (index < 0 || m_head == nullptr)
        return false;

    if (index == 0)
    {
        SkillNode* nodeToDelete = m_head;
        m_head = m_head->next;
        std::cout << "Removing skill at index 0: " << nodeToDelete->data << std::endl;
        delete nodeToDelete;
        return true;
    }

    SkillNode* temp = m_head;
    int currentIndex = 0;
    while (temp->next != nullptr && currentIndex < index - 1)
    {
        temp = temp->next;
        ++currentIndex;
    }

    if (temp->next == nullptr)
        return false;

    SkillNode* nodeToDelete = temp->next;
    std::cout << "Removing skill at index " << index << ": " << nodeToDelete->data << std::endl;
    temp->next = nodeToDelete->next;
    delete nodeToDelete;
    return true;
}

void SkillList::PrintSkills() const
{
    SkillNode* temp = m_head;
    int index = 0;
    while (temp != nullptr)
    {
        std::cout << index << ": " << temp->data << std::endl;
        temp = temp->next;
        ++index;
    }
}
