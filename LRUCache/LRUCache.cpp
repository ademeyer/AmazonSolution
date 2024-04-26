// LRUCache.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

class LRUCache 
{
    //Create a Node
    struct Node
    {
        int value;
        int key;
        Node* prev;
        Node* next;
        Node(int k, int val) : key(k), value(val), next(nullptr), prev(nullptr)
        {}
    };

    unordered_map<int, Node*> cache;
    int _size;
    Node* head;
    Node* tail;

    void InsertNode(Node* node)
    {
        Node* temp = head->next;
        head->next = node;
        node->prev = head;
        temp->prev = node;
        node->next = temp;
        cache.insert(pair<int, Node*>(node->key, node));
    }

    void DeleteNode(Node* node)
    {
        //remove from Node
        Node* prev = node->prev;
        Node* next = node->next;
        if(prev != NULL)
            prev->next = next;
        if (next != NULL)
            next->prev = prev;
        cache.erase(node->key);
        delete node;
    }


public:

    LRUCache(int capacity) : _size(capacity)
    {
        head = new Node(0,0);
        tail = new Node(0,0);
        head->next = tail;
        tail->prev = head;
    }

    int get(int key)
    {
        int result = -1;
        if (cache.find(key) != cache.end())
        {
            auto node = cache[key];
            result = node->value;

            //remove it
            DeleteNode(node);
            // readd to Node
            InsertNode(new Node(key, result));
        }

        return result;
    }

    void put(int key, int value)
    {
        if (_size == 0) return;
        // Need to check if it is not there
        if (cache.find(key) == cache.end())
        {
            //check size of the container
            if (cache.size() == _size)
            {
                //assume that last node's next is pointing to tail
                Node* lastNode = tail->prev;
                DeleteNode(lastNode);
            }
        }
        else
        {
            // else it there, delete it and re-add
            auto node = cache[key];
            DeleteNode(node);
        }    
        InsertNode(new Node(key, value));
    }

    void DisplayLRUCache()
    {
        cout << "\nInner Debugging [";
        for (auto& mp : cache)
        {
            cout << "[" << mp.first << "," << mp.second->value << "] ";
        }
        cout << "]\n";
    }
};




int main()
{
/*
Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]
 */
    cout << "[";
    LRUCache c1(2);
    c1.put(1, 1);
    c1.put(2, 2);
    cout << c1.get(1) << ",";
    c1.put(3, 3);
    cout << c1.get(2) << ",";
    c1.put(4, 4);
    cout << c1.get(1) << ",";
    cout << c1.get(3) << ",";
    cout << c1.get(4) << ",";
    cout << "]\n";
    c1.DisplayLRUCache();



    std::cout << "\nDone Testing\n";
}

