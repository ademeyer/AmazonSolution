// GraphTransversal.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

void BFS(vector<vector<int>>& adjList, int startNode, vector<bool>& visited)
{
    queue<int> q;

    visited[startNode] = true;
    q.push(startNode); 

    while (!q.empty())
    {
        // Get the top element and process
        auto currentNode = q.front();
        q.pop();
        cout << currentNode << " ";

        // Get all neighbouring node and mark them as visited
        for (auto& neighbour : adjList[currentNode])
        {
            if (!visited[neighbour])
            {
                visited[neighbour] = true;
                q.push(neighbour);
            }
        }
    }
}

void DFS(vector<vector<int>>& adjList, int startNode, vector<bool>& visited)
{
    stack<int> s;

    // start with the first Node
    s.push(startNode);
    visited[startNode] = true;

    while (!s.empty())
    {
        auto currentNode = s.top();
        s.pop();
        cout << currentNode << " ";

        for (auto& neighbour : adjList[currentNode])
        {
            if (!visited[neighbour])
            {
                s.push(neighbour);
                visited[neighbour] = true;
            }
        }
    }
}

void addEdge(vector<vector<int>>& adj, int src, int dest)
{
    adj[src].push_back(dest);
}


int main()
{
    // Create First Test Nodes
    const int vertices = 5;

    // Create adjacency list
    vector<vector<int>> adjList(vertices, vector<int>());
    addEdge(adjList, 0, 1);
    addEdge(adjList, 0, 2);
    addEdge(adjList, 1, 3);
    addEdge(adjList, 1, 4);
    addEdge(adjList, 2, 4);

    vector<bool> visited(vertices, false);

    // Start Testing Transversal methods
    cout << "BFS transversal starting from \'0\': ";
    BFS(adjList, 0, visited);
    cout << "\n";
    visited = vector<bool>(vertices, false);
    cout << "DFS transversal starting from \'0\': ";
    DFS(adjList, 0, visited);
    cout << "\n";

    // Create Second Test Nodes
    const int vertices1 = 6;

    // Create adjacency list
    vector<vector<int>> adjList1(vertices1, vector<int>());
    vector<bool> visited1(vertices1, false);

    addEdge(adjList1, 0, 1);
    addEdge(adjList1, 0, 2);
    addEdge(adjList1, 1, 2);
    addEdge(adjList1, 2, 0);
    addEdge(adjList1, 2, 3);
    addEdge(adjList1, 3, 3);

    // Start Testing Transversal methods
    cout << "BFS transversal starting from \'0\': ";
    BFS(adjList1, 0, visited1);
    cout << "\n";
    visited1 = vector<bool>(vertices1, false);
    cout << "DFS transversal starting from \'0\': ";
    DFS(adjList1, 0, visited1);
    cout << "\n";
}

