// BipatriteGraph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

/*
* Bipatrite Graphs are graphs whose adjacency node can have two different color (or opposite properties) for all of it's node
*/
bool BFS(int node, int col, vector<int>& color, vector<int> adj[])
{
    return false;
}

bool DFS(int node, int col, vector<int>& color, vector<int> adj[])
{
    color[node] = col;

    for (auto nextInNode : adj[node])
    {
        
        if (color[nextInNode] == -1)
        {
            if (!DFS(nextInNode, !col, color, adj))
                return false;
        }
        else if (color[nextInNode] == col) return false; // Not bipatrite
    }
    return true;
}

bool isBipatrite(int V, vector<int> adj[], int method = 0)
{
    vector<int> color(V, -1);

    for (int i = 0; i < V; i++)
    {
        if (color[i] == -1) // node have not been colored
        {
            if (method == 0)
            {
                if (!DFS(i, 0, color, adj)) return false;
            }
            else
            {
                if (!BFS(i, 0, color, adj)) return false;
            }
                
        }
    }
    return true;
}

void addEdge(vector<int> adj[], int src, int dest)
{
    adj[src].push_back(dest);
}

int main()
{
    const int V = 9;
    vector<int> adj[V];
    addEdge(adj, 1, 2);
    addEdge(adj, 2, 3);
    addEdge(adj, 2, 6);
    addEdge(adj, 2, 1);
    addEdge(adj, 3, 4);
    addEdge(adj, 3, 2);
    addEdge(adj, 6, 5);
    addEdge(adj, 6, 2);
    addEdge(adj, 5, 4);
    addEdge(adj, 5, 6);
    addEdge(adj, 4, 7);
    addEdge(adj, 4, 3);
    addEdge(adj, 4, 5);
    addEdge(adj, 7, 8);
    addEdge(adj, 7, 4);
    addEdge(adj, 8, 7);

    cout << "is graph is " << (isBipatrite(V, adj) ? "" : "Not ") << "bipatrite" << endl;
    cout << "\n";
}
