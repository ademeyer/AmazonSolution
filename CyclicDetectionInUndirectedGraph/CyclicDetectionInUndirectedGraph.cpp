// CyclicDetectionInUndirectedGraph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    bool isCyclicUtil(int node, vector<int> adj[], vector<bool>& visited)
    {
        visited[node] = true;
        for (auto& nextNode : adj[node])
        {
            if (!visited[nextNode])
            {
                if (isCyclicUtil(nextNode, adj, visited)) return true;
            }
            else if (nextNode != node)
                return true;
        }
        return false;
    }
public:
    // Function to detect cycle in an undirected graph.
    bool isCycle(int V, vector<int> adj[])
    {
    }
};

int main()
{
    Solution s;
    vector<int> adj[] = { {1}, {0, 2, 4}, {1, 3}, {2, 4}, {1, 3} };
    //cout << "Graph is " << (s.isCycle(adj) ? "" : "");
}