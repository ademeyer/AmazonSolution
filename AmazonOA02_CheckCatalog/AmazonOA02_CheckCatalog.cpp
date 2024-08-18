// AmazonOA02_CheckCatalog.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;


bool hasCycle(string key, unordered_set<string>& visited,
    unordered_set<string>& recStack,
    unordered_map<string, vector<string>>& catalog)
{
    recStack.insert(key);
    visited.insert(key);

    for (const auto& dependency : catalog[key])
    {
        if (visited.find(dependency) == visited.end())
        {
            if (hasCycle(dependency, visited, recStack, catalog))
            {
                return true;
            }
        }
        else if (recStack.find(dependency) != recStack.end())
        {
            return true;
        }
    }
    recStack.erase(key);

    return false;
}

bool isCatalogValid(unordered_map<string, vector<string>> catalog)
{
    unordered_set<string> visited, recStack;

    for (const auto& cat : catalog)
    {
        if (visited.find(cat.first) == visited.end())
        {
            if (hasCycle(cat.first, visited, recStack, catalog))
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    unordered_map<string, vector<std::string>> catalog = 
    {
        {"Databases", {"Security", "Logging"}},
        {"Security", {"Databases", "Logging"}},
        {"Logging", {}}
    };
    bool valid = isCatalogValid(catalog);
    if (valid)
        cout << "Catalog is valid\n";
    else
        cout << "Catalog is not valid\n";
    cout << "\n";
}

