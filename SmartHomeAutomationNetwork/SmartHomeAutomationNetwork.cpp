// SmartHomeAutomationNetwork.cpp : This file contains the 'main' function. Program execution begins and ends there.

/*
You are developing firmware for an embedded system used in a smart home automation network. The network consists of various devices (sensors, actuators, controllers) organized in a hierarchical manner. Each device communicates with its parent device, forming a tree-like structure where the root represents the central hub or gateway.
Write a program that finds and returns the communication path from the central hub to a specified device in the network.
*/

#include <iostream>
#include <functional>
#include <vector>
#include <stack>
using namespace std;

struct TreeNode
{
    string name;
    vector<TreeNode*> children;
    TreeNode(const string& n) : name(n) {}
    void addChildren(TreeNode* child) { children.push_back(child); }
};

vector <string> findPathDFSIterative(TreeNode* root, const string& targetHub)
{
    if (!root) return {};

    stack<pair<TreeNode*, vector<string>>> st; // node, children path
    st.push({ root , {root->name}});

    while (!st.empty())
    {
        auto [node, path] = st.top(); st.pop(); // requires C++20

        // is this is the node are looking for, return it's path
        if (node->name == targetHub)
            return path;

        // add its children to the stack
        for (auto child : node->children)
        {
            auto newPath = path;
            newPath.push_back(child->name);
            st.push({ child, newPath });
        }
    }
    return {};
}

vector <string> findPathDFSRecursive(TreeNode* root, const string& targetHub)
{
    vector<string> result;

    function<bool(TreeNode*)> dfs = [&](TreeNode* node)
    {
        if (!root) return false;
        result.push_back(node->name);

        // check to see if this is the targetHub
        if (node->name == targetHub)
            return true;

        //recursive check children node
        for (const auto n : node->children)
        {
            if (dfs(n))
            {
                return true;
            }
        }
        result.pop_back();
        return false;
    };

    dfs(root);
    return result;
}

TreeNode* buildSampleHub()
{
    // Central hub
    TreeNode* root = new TreeNode("Hub");

    // First Level hubs
    TreeNode* livingRoom = new TreeNode("LivingRoom");
    TreeNode* kitchen = new TreeNode("Kitchen");
    TreeNode* bedRoom = new TreeNode("BedRoom");

    // add them to the central hub
    root->addChildren(livingRoom);
    root->addChildren(kitchen);
    root->addChildren(bedRoom);


    // Second Level hubbs
    // Living Room devices
    livingRoom->addChildren(new TreeNode("Thermostat-1"));
    livingRoom->addChildren(new TreeNode("Light-1"));

    // Kitchen devices
    kitchen->addChildren(new TreeNode("Fridge"));
    kitchen->addChildren(new TreeNode("Oven"));
    kitchen->addChildren(new TreeNode("Light-2"));

    // BedRoom devices
    bedRoom->addChildren(new TreeNode("Thermostat-2"));
    bedRoom->addChildren(new TreeNode("MotionSensor"));
    bedRoom->addChildren(new TreeNode("Light-3"));

    // Third Level hub
    livingRoom->children[0]->addChildren(new TreeNode("TempSensor"));
    
    return root;   
}

void Print(const vector<string>& res)
{
    cout << "[";
    for (const auto& r : res)
        cout << r << ",";
    cout << "]\n";
}


int main()
{
    auto root = buildSampleHub();
    auto r = findPathDFSRecursive(root, "TempSensor");
    cout << "result: ";
    Print(r);

    root = buildSampleHub();
    r = findPathDFSRecursive(root, "Oven");
    cout << "result: ";
    Print(r);

    root = buildSampleHub();
    r = findPathDFSRecursive(root, "Light-3");
    cout << "result: ";
    Print(r);
}
