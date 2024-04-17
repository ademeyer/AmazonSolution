// BinaryTreeTraversal.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;
    Node(int data):data(data), left(nullptr), right(nullptr) {}
};

Node* Insert(Node* root, int data)
{
    if (root == NULL)
    {
        return new Node(data);        
    }

    if (root->data > data)
    {
        root->left = Insert(root->left, data);
    }
    else if (root->data < data)
    {
        root->right = Insert(root->right, data);
    }

    return root;
}

Node* BuildTreeFromArr(const vector<int>& arr)
{
    Node* root = NULL;
    Node* newNode = NULL;
    Node* iter = root;

    root = Insert(root, arr[0]);

    for (int i = 1; i < arr.size(); i++)
    {
        root = Insert(root, arr[i]);
    }

    return root;
}

void InOrder(Node* root)
{
    if (root == NULL) return;
    InOrder(root->left);
    cout << root->data << " ";
    InOrder(root->right);
}

void PreOrder(Node* root)
{
    if (root == NULL) return;
    cout << root->data << " ";
    PreOrder(root->left);
    PreOrder(root->right);
}

void PostOrder(Node* root)
{
    if (root == NULL) return;
    PostOrder(root->left);
    PostOrder(root->right);
    cout << root->data << " ";
}

int main()
{
    vector<int> data{ 10, 14, 12, 13, 1, 2, 3, 4, 5, 7, 8, 6, 9, 0 };
    Node* root = BuildTreeFromArr(data);
    InOrder(root);
    cout << "\n";
    PreOrder(root);
    cout << "\n";
    PostOrder(root);
    cout << "\n";
}
