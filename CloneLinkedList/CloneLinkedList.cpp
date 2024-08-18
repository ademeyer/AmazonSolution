// CloneLinkedList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <unordered_map>
using namespace std;

//Clone Linked List with next and random pointer
/*
     +---------------------------+
     |                           |
     |             +-------------+-------------+
     |             |             |             |
     v             |             |             v
 +------+      +---+--+      +---+--+      +------+      +------+
 |      |      |      |      |      |      |      |      |      |
 |   1  +----->|   2  +----->|   3  +----->|   4  +----->|   5  |
 |      |      |      |      |      |      |      |      |      |
 +---+--+      +------+      +------+      +---+--+      +-+----+
     |            ^              ^             |           | ^
     |            |              |             |           | |
     |            |              +-------------+           | |
     |            |                                        | |
     |            +----------------------------------------+ |
     |                                                       |
     +-------------------------------------------------------+
*/

struct Node
{
    int data;
    Node* next;
    Node* random;
    Node(int d) : data(d), next(nullptr), random(nullptr) {};
};

Node* clone(Node* head)
{
    if (!head) return nullptr;

    unordered_map<Node*, Node*> nodemap; // old, newNode, 
    Node* cur = head;

    while (cur)
    {
        nodemap[cur] = new Node(cur->data); // n = size of node
        cur = cur->next;
    }

    cur = head;

    while (cur)
    {
        nodemap[cur]->next = nodemap[cur->next];
        nodemap[cur]->random = nodemap[cur->random];
        cur = cur->next;
    }

    return nodemap[head];
}

// Function to print the linked list
void printList(Node* head) 
{
    while (head) 
    {
        std::cout << "Data: " << head->data;
        if (head->random) 
        {
            std::cout << ", Random: " << head->random->data << std::endl;
        }
        else 
        {
            std::cout << ", Random: nullptr" << std::endl;
        }
        head = head->next;
    }
}

int main() 
{
    // Create a linked list with next and random pointers
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);

    // Setting up random pointers
    head->random = head->next->next;
    head->next->random = head->next->next->next;
    head->next->next->random = head->next->next->next->next;
    head->next->next->next->random = head;
    head->next->next->next->next->random = head->next;

    std::cout << "Original list:\n";
    printList(head);

    Node* clonedHead = clone(head);

    std::cout << "\nCloned list:\n";
    printList(clonedHead);

    return 0;
}

