#include "SkillList.h"
#include <iostream>

SkillList::SkillList()
    : head(nullptr)
{
}

SkillList::~SkillList()
{
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
        std::cout << "La lista esta vacia, no se puede eliminar la primera habilidad." << std::endl;
        return;
    }

    Node* newHead = head->next;
    std::cout << "Eliminando habilidad en indice 0: " << head->data << std::endl;
    delete head;
    head = newHead;
}

bool SkillList::DeleteSkillAt(int index)
{
    if (index < 0 || !head)
    {
        std::cout << "Indice invalido o lista vacia." << std::endl;
        return false;
    }

    if (index == 0)
    {
        DeleteHead();
        return true;
    }

    Node* temp = head;
    int currentIndex = 0;

    // Llegar al nodo anterior al que vamos a borrar
    while (temp != nullptr && currentIndex < index - 1)
    {
        temp = temp->next;
        currentIndex++;
    }

    if (temp == nullptr || temp->next == nullptr)
    {
        std::cout << "Indice fuera de rango, no se elimino nada." << std::endl;
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
        std::cout << "Indice invalido." << std::endl;
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
        std::cout << "Indice fuera de rango, no se reemplazo nada." << std::endl;
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
    Node* temp = head;
    while (temp != nullptr)
    {
        Node* next = temp->next;
        delete temp;
        temp = next;
    }
    head = nullptr;
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