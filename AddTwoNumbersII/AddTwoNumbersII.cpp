// AddTwoNumbersII.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct ListNode
{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
{
    auto iter1 = l1;
    auto iter2 = l2;
    stack<int> st1, st2, st3;
    while (iter1 != NULL || iter2 != NULL)
    {
        if (iter1 != NULL)
        {
            st1.push(iter1->val);
            iter1 = iter1->next;
        }

        if (iter2 != NULL)
        {
            st2.push(iter2->val);
            iter2 = iter2->next;
        }
    }
    int addRem = 0;
    /// add the list values
    while ((!st1.empty() || !st2.empty()) || addRem > 0)
    {
        int val1 = 0, val2 = 0;
        if (!st1.empty())
        {
            val1 = st1.top();
            st1.pop();
        }
        if (!st2.empty())
        {
            val2 = st2.top();
            st2.pop();
        }
        addRem += (val1 + val2);
        st3.push(addRem%10);
        addRem /= 10;
    }

    //reconstruct the list
    ListNode* head = NULL;
    ListNode* iter = NULL;
    while (!st3.empty())
    {
        ListNode* NewNode = new ListNode(st3.top());
        st3.pop();
        if (head == NULL)
        {
            head = NewNode;
            iter = head;
        }
        else
        {
            iter->next = NewNode;
            iter = iter->next;
        }
    }
    return head;
}

ListNode* CreateNodeFromArr(vector<int> arr)
{
    ListNode* head = NULL;
    ListNode* iter = NULL;
    for (auto ele : arr)
    {
        ListNode* NewNode = new ListNode(ele);

        if (head == NULL)
        {
            head = NewNode;
            iter = head;
        }
        else
        {
            iter->next = NewNode;
            iter = iter->next;
        }
    }

    return head;
}

void PrintNode(ListNode* Node)
{
    auto iter = Node;
    while (iter != NULL)
    {
        cout << iter->val << " -> ";
        iter = iter->next;
    }
    cout << endl;
}

int main()
{
    auto l1 = CreateNodeFromArr({7,2,4,3});
    auto l2 = CreateNodeFromArr({5,6,4});
    auto l3 = addTwoNumbers(l1, l2);
    PrintNode(l3);

    cout << "";
}

