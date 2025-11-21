// Minijuego.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "SFML/Graphics.hpp"
#include <string>
#include "RendeerManager.h"

using namespace std;

struct Node
{
    string data;   // Nombre de la habilidad
    Node* next;

    Node(const string& data)
    {
        this->data = data;
        this->next = nullptr;
    }
};

class SkillList
{
public:
    Node* head;
    SkillList():head(nullptr){}
    ~SkillList()
    {
        Clear();
    }
};

// Add skill at the end of the list, if there are no other skills, then it becomes the head.
void AddSkill(const string& data)
{
    Node* newNode = new Node(data);

    if (head == nullptr) head = newNode;
    else
    {
        Node* temp = head;
        while (temp->next != nullptr) temp = temp->next;
        temp->next = newNode;
    }
    cout << "Skill added!!" << data << endl;
}

// Delete head, first hability (only if it exists, if not, debug an error message.
void DeleteHead()
{
    if (!head)
    {
        cout << "List is empty, can't remove first hability." << endl;
        return;
    }

    Node* newHead = head->next;
    cout << "Removing skill, index 0" << head->data << endl;
    delete head;
    head = newHead;
}

// Delete skill by index, same as before, if it does not exists, it shows a message in console
bool DeleteSkillAt(int index)
{
    if (index < 0 || !head)
    {
        cout << "Index invalid, empty list of skills." << endl;
        return false;
    }

    // Case of index 0 -> Head, the we call DeleteHead();
    if (index == 0)
    {
        DeleteHead();
        return true;
    }

    Node* temp = head;
    int currentIndex = 0;

    while (temp != nullptr || temp->next == nullptr)
    {
        temp = temp->next;
        currentIndex++;
    }

    if (temp == nullptr || temp->next == nullptr)
    {
        cout << "Index out of range. No skill was removed." << endl;
        return false;
    }

    Node* nodeToDelete = temp->next;
    cout << "Removing skill, index"<< index << nodeToDelete->data << endl;
    temp->next = nodeToDelete->next;
    delete nodeToDelete;
    return true;
}



int main()
{
    std::cout << "Hello World!\n";
}
