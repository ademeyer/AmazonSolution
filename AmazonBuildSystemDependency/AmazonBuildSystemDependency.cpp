/* Question
* Amazon uses an internal build system to ensure that software dependencies are properly built for a project. 
* We are looking to write our next generation build system. You are given two variables: pkg_graph and pkg, 
* where pkg_graph is a map whose key is a package name (string) and value is a list of its dependencies (list of strings)
* and pkg is a string for the desired package to be built. Given pkg_graph and pkg, write a function that will 
* return a pkg's necessary dependencies that need to be built in order, with no duplicates, including the given package.
*/

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

using package_graph = unordered_map<string, vector<string>>;

void DFS(const package_graph& pkg_graph, const string& pkg, unordered_set<string>& visited, vector<string>& results)
{
    if (visited.count(pkg))
    {
        return;
    }

    visited.insert(pkg);

    for (auto& other_pkg : pkg_graph.at(pkg)) //
    {
        DFS(pkg_graph, other_pkg, visited, results);
    }

    results.push_back(pkg);
}

vector<string> GetDependencies(const package_graph& pkg_graph, const string& pkg)
{
    unordered_set<string> visited;
    vector<string> results;

    DFS(pkg_graph, pkg, visited, results);

    return results;
}

int main()
{
    package_graph pkg_graph =
    {
        {"A", {"B", "C"}},
        {"B", {"C", "D"}},
        {"C", {"D"}},
        {"D", {}}
    };

    auto res = GetDependencies(pkg_graph, "A");
    for (auto& dep : res)
        cout << dep << endl;
    cout << "\n";

    res = GetDependencies(pkg_graph, "B");
    for (auto& dep : res)
        cout << dep << endl;
    cout << "\n";

    res = GetDependencies(pkg_graph, "C");
    for (auto& dep : res)
        cout << dep << endl;
    cout << "\n";

    res = GetDependencies(pkg_graph, "D");
    for (auto& dep : res)
        cout << dep << endl;
    cout << "\n";
}
