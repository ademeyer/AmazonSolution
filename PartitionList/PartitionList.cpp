// PartitionList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
    
};

ListNode* partition(ListNode* head, int x) 
{
    auto* iter = head;
    ListNode* left = NULL;
    ListNode* right = NULL;
    ListNode* rightHead = NULL;
    ListNode* leftHead = NULL;

    while (iter != NULL)
    {
        if (iter->val < x)
        {
            if (leftHead == NULL)
            {
                leftHead = iter;
                left = leftHead;
            }
            else
            {
                left->next = iter;
                left = left->next;
            }
        }
        else
        {
            if (rightHead == NULL)
            {
                rightHead = iter;
                right = rightHead;
            }
            else
            {
                right->next = iter;
                right = right->next;
            }
        }
        iter = iter->next;
    }
    // join left and right
    if (left != NULL)
    {
        if(right != NULL)
            right->next = NULL;
        left->next = rightHead;
        return leftHead;
    }
    return rightHead;    
}

ListNode* CreateNodeFromArr(vector<int>& arr)
{
    ListNode* head = NULL;
    ListNode* iter = NULL;
    for (auto ch : arr)
    {
        ListNode* NewNode = new ListNode(ch);
        if (head == NULL)
        {
            head = NewNode;
            iter = head;
            continue;
        }
        iter->next = NewNode;
        iter = iter->next;
    }

    return head;
}

void printListNode(ListNode* head)
{
    auto* iter = head;
    while (iter != NULL)
    {
        cout << iter->val << ", ";
        iter = iter->next;
    }
    cout << "\n";
}

int main()
{
    vector<int> arr{ 1, 4, 3, 2, 5, 2 };
    auto* head = CreateNodeFromArr(arr);
    auto* newHead = partition(head, 2);
    printListNode(newHead);
    
}
