#include "SkillList.h"
#include <iostream>

SkillList::SkillList()
    : head(nullptr)
{
}

SkillList::~SkillList()
{
    // Critical: Clear() deletes all nodes to prevent memory leaks
    // This ensures proper cleanup when SkillList goes out of scope
    Clear();
}

void SkillList::AddSkill(const std::string& data)
{
    Node* newNode = new Node(data);

    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        Node* temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    std::cout << "Habilidad agregada: " << data << std::endl;
}

void SkillList::DeleteHead()
{
    if (!head)
    {
        std::cerr << "Error: DeleteHead() - La lista esta vacia, no se puede eliminar la primera habilidad." << std::endl;
        return;
    }

    Node* newHead = head->next;
    std::cout << "Eliminando habilidad en indice 0: " << head->data << std::endl;
    delete head;
    head = newHead;
}

bool SkillList::DeleteSkillAt(int index)
{
    if (index < 0)
    {
        std::cerr << "Error: DeleteSkillAt() - Indice negativo (" << index << ") no es valido." << std::endl;
        return false;
    }

    if (!head)
    {
        std::cerr << "Error: DeleteSkillAt() - La lista esta vacia, no se puede eliminar en indice " << index << "." << std::endl;
        return false;
    }

    if (index == 0)
    {
        DeleteHead();
        return true;
    }

    Node* temp = head;
    int currentIndex = 0;

    // Get to the node before the one we're going to delete
    while (temp != nullptr && currentIndex < index - 1)
    {
        temp = temp->next;
        currentIndex++;
    }

    if (temp == nullptr || temp->next == nullptr)
    {
        std::cerr << "Error: DeleteSkillAt() - Indice " << index << " fuera de rango (lista tiene " << Count() << " elementos)." << std::endl;
        return false;
    }

    Node* nodeToDelete = temp->next;
    std::cout << "Eliminando habilidad en indice " << index
        << ": " << nodeToDelete->data << std::endl;

    temp->next = nodeToDelete->next;
    delete nodeToDelete;
    return true;
}

bool SkillList::ReplaceSkillAt(int index, const std::string& newData)
{
    if (index < 0)
    {
        std::cerr << "Error: ReplaceSkillAt() - Indice negativo (" << index << ") no es valido." << std::endl;
        return false;
    }

    if (!head)
    {
        std::cerr << "Error: ReplaceSkillAt() - La lista esta vacia, no se puede reemplazar en indice " << index << "." << std::endl;
        return false;
    }

    Node* temp = head;
    int currentIndex = 0;

    while (temp != nullptr && currentIndex < index)
    {
        temp = temp->next;
        currentIndex++;
    }

    if (temp == nullptr)
    {
        std::cerr << "Error: ReplaceSkillAt() - Indice " << index << " fuera de rango (lista tiene " << Count() << " elementos)." << std::endl;
        return false;
    }

    std::cout << "Reemplazando habilidad en indice " << index
        << " (" << temp->data << ") por: " << newData << std::endl;

    temp->data = newData;
    return true;
}

void SkillList::Show() const
{
    if (!head)
    {
        std::cout << "No hay habilidades en la lista." << std::endl;
        return;
    }

    const Node* temp = head;
    int index = 0;

    std::cout << "===== Lista de habilidades =====" << std::endl;
    while (temp != nullptr)
    {
        std::cout << "[" << index << "] " << temp->data << std::endl;
        temp = temp->next;
        index++;
    }
    std::cout << "================================" << std::endl;
}

void SkillList::Clear()
{
    // Traverse the entire list and delete each node
    Node* temp = head;
    while (temp != nullptr)
    {
        Node* next = temp->next;
        delete temp;  // Free memory for current node
        temp = next;
    }
    head = nullptr;  // Reset head to indicate empty list
}

int SkillList::Count() const
{
    int count = 0;
    const Node* temp = head;
    while (temp != nullptr)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

std::string SkillList::GetSkillAt(int index) const
{
    if (index < 0)
    {
        std::cerr << "Error: GetSkillAt() - Indice negativo (" << index << ") no es valido." << std::endl;
        return "";
    }

    if (!head)
    {
        std::cerr << "Error: GetSkillAt() - La lista esta vacia, no se puede acceder al indice " << index << "." << std::endl;
        return "";
    }

    const Node* temp = head;
    int currentIndex = 0;

    while (temp != nullptr && currentIndex < index)
    {
        temp = temp->next;
        currentIndex++;
    }

    if (temp == nullptr)
    {
        std::cerr << "Error: GetSkillAt() - Indice " << index << " fuera de rango (lista tiene " << Count() << " elementos)." << std::endl;
        return "";
    }

    return temp->data;
}
