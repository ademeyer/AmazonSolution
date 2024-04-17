// SumRootToLeafNumber.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

struct TreeNode 
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

TreeNode* Insert(TreeNode* root, int data)
{
    if (root == NULL)
    {
        return new TreeNode(data);
    }

    if (root->val > data)
    {
        root->left = Insert(root->left, data);
    }
    else if (root->val < data)
    {
        root->right = Insert(root->right, data);
    }

    return root;
}

TreeNode* BuildTreeFromArr(const vector<int>& arr)
{
    TreeNode* root = NULL;
    TreeNode* newNode = NULL;
    TreeNode* iter = root;

    root = Insert(root, arr[0]);

    for (int i = 1; i < arr.size(); i++)
    {
        root = Insert(root, arr[i]);
    }

    return root;
}

class Solution
{
    int ans{ 0 };
    void  dfs(TreeNode* root, long long value)
    {
        if (root == NULL) return;

        value = value * 10;
        value += root->val;

        if (root->left == NULL && root->right == NULL)
        {
            ans += value;
            return;
        }

        dfs(root->left, value);
        dfs(root->right, value);
    }
public: 
    int sumNumbers(TreeNode* root)
    {
        if (root == NULL) return 0;
        dfs(root, 0);
        return ans;
    }
};


int main()
{
    Solution s;
    vector<int> data{ 1, 2, 3 };
    TreeNode* root = BuildTreeFromArr(data);
    std::cout << s.sumNumbers(root) << "\n";
    delete root;
    root = NULL;
    data = { 4, 9, 0, 5, 1 };
    root = BuildTreeFromArr(data);
    std::cout << s.sumNumbers(root) << "\n";
}