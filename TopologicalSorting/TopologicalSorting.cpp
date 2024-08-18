// TopologicalSorting.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <stack>
#include <vector>
using namespace std;

class TopoSort
{
    int V;
    list<int>* adj;
    void TopologicalSortUtil(int v, vector<bool>& visited, stack<int>& Stack);

public:
    TopoSort(int v) : V(v), adj(new list<int>[v]){}
    void addEdge(int v, int w);
    void TopologicalSort();
};

void TopoSort::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

void TopoSort::TopologicalSortUtil(int v, vector<bool>& visited, stack<int>& Stack)
{
    visited[v] = true;

    for (auto n : adj[v])
    {
        if(!visited[n])
            TopologicalSortUtil(n, visited, Stack);
    }
    Stack.push(v);
}

void TopoSort::TopologicalSort()
{
    stack<int> Stack;
    vector<bool> visited(V, false);

    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
            TopologicalSortUtil(i, visited, Stack);
    }

    while (!Stack.empty())
    {
        cout << Stack.top() << ",";
        Stack.pop();
    }
    cout << "\n";

}
int main()
{
    TopoSort tp(6);
    tp.addEdge(5, 2);
    tp.addEdge(5, 0);
    tp.addEdge(4, 0);
    tp.addEdge(4, 1);
    tp.addEdge(2, 3);
    tp.addEdge(3, 1);

    cout << "Topological sorting: ";
    tp.TopologicalSort();
}