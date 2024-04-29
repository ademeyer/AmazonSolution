// CyclicDetectionInGraph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;

bool isCyclicDFS(int node, vector<bool>& visited, vector<bool>& recStack, vector<int> adj[])
{
    visited[node] = true;
    recStack[node] = true;

    for (auto nextNode : adj[node])
    {
        if (!visited[nextNode])
        {
            //visited[nextNode] = true;
            //recStack[nextNode] = true;
            if (isCyclicDFS(nextNode, visited, recStack, adj)) return true;
        }
        else if (visited[nextNode] && recStack[nextNode])
            return true;

    }
    recStack[node] = false;
    return false;
}

bool isCyclic(vector<int> adj[], int V)
{
    vector<bool> visited(V, false);
    vector<bool> recStack(V, false);

    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
        {
            if (isCyclicDFS(i, visited, recStack, adj)) return true;
        }
    }
    return false;
}

void addEdge(vector<int> adj[], int src, int dest)
{
    adj[src].push_back(dest);
}

int main()
{
    const int V = 10;
    vector<int> adj[V];

    addEdge(adj, 1, 2);
    addEdge(adj, 2, 3);
    addEdge(adj, 3, 4);
    addEdge(adj, 3, 6);
    addEdge(adj, 4, 5);
    addEdge(adj, 6, 5);
    addEdge(adj, 7, 2);
    addEdge(adj, 7, 8);
    addEdge(adj, 8, 9);
    addEdge(adj, 9, 7);

    cout << "cyclic " << (isCyclic(adj, V) ? "" : "does not ") << "exists!" << endl;
    cout << "\n";

    const int v = 5;
    vector<int> adj1[v];
    addEdge(adj1, 0, 1);
    addEdge(adj1, 0, 4);
    addEdge(adj1, 0, 3);
    addEdge(adj1, 2, 0);
    addEdge(adj1, 3, 2);
    addEdge(adj1, 4, 1);
    addEdge(adj1, 4, 3);

    cout << "cyclic " << (isCyclic(adj1, v) ? "" : "does not ") << "exists!" << endl;
    cout << "\n";
}
