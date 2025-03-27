// TopologicalSort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <stack>
#include <unordered_map>
#include <vector>


class Graph 
{
private:
    int Vertices; // number of vertices
    std::unordered_map<int, std::list<int>> adj; // Adjacency list

    // topological sort utility function
    void topologicalSortUtil(int i, std::vector<bool>& visited, std::stack<int>& st)
    {
        visited[i] = true;

        // recursively call for all the vertices in the adjancy to this vertex
        for (const auto& n : adj[i])
        {
            if (!visited[n])
            {
                topologicalSortUtil(n, visited, st);
            }
        }

        st.push(i);
    }

public:
    Graph(int v) : Vertices(v) {}

    // Function to add an edge to the graph
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
    }

    std::vector<int> topologicalSort()
    {
        std::stack<int> st;
        std::vector<bool> visited(Vertices, false); // mark all as not visited

        // recursively call helper function to store topological sort
        for (int i = 0; i < Vertices; ++i)
        {
            if (!visited[i])
            {
                topologicalSortUtil(i, visited, st);
            }
        }

        std::vector<int> result;

        while (!st.empty())
        {
            result.push_back(st.top());
            st.pop();
        }

        return result;
    }
};

int main()
{
    // Create a graph with 6 vertices
    Graph g(6);

    // Add edges to the graph
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    // Perform topological sort
    std::vector<int> sortedOrder = g.topologicalSort();

    // Print the topological order
    std::cout << "Topological Sort Order: ";
    for (int vertex : sortedOrder) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;

    return 0;
}