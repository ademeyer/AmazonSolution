// ShortestPathInBinaryMatrix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <queue>
#include <set>
using namespace std;

struct field
{
    int r;
    int c;
    int len;
};

int shortestPathBinaryMatrix(vector<vector<int>>& grid) 
{
    const vector<pair<int, int>> direction{ {1,-1},  {0,1},  {1,0},  {1,1},
                                            {-1,0}, {0,-1}, {-1,-1}, {-1,1} };
    int N = grid.size();
    queue<field> q;
    set<pair<int,int>> visited;
    field f = { 0,0,1 };
    q.push(f);
    visited.insert(make_pair(0, 0));

    while (!q.empty())
    {
        field f = q.front();
        q.pop();
        int row = f.r;
        int col = f.c;
        int Length = f.len;
        // if we pass boundaries, has visited or is blocked, then continue
        if (min(row, col) < 0 || max(row, col) >= N || grid[row][col] == 1)
        {
            continue;
        }
        // if we have reached our result
        if (row == N - 1 && col == N - 1)
        {
            return Length;
        }

        for (int i = 0; i < direction.size(); i++)
        {
            auto dir = direction[i];
            if (!visited.count(make_pair(row + dir.first, col + dir.second)))
            {
                field Nf = { row + dir.first, col + dir.second, (Length + 1) };
                q.push(Nf);
                visited.insert(make_pair(row + dir.first, col + dir.second));
            }
        }
    }
    return -1;

}
int main()
{
    vector<vector<int>> grid{ {0,1},{1,0} };
    cout << "shortest path is " << shortestPathBinaryMatrix(grid) << endl;
}