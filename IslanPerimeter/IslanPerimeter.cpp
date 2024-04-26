// IslanPerimeter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;

/*int islandPerimeter(vector<vector<int>>& grid)
{
    int perimeter = 0;
    int r = grid.size(), c = grid[0].size();

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < r; j++)
        {
            if (grid[i][j] == 0) continue;

            perimeter += 4;
            if (i > 0) perimeter -= grid[i - 1][j];
            if (j > 0) perimeter -= grid[i][j - 1];
            if (i < r-1) perimeter -= grid[i + 1][j];
            if (j < c-1) perimeter -= grid[i][j+1];
        }
    }
    return perimeter;
}
*/

void dfs(vector<vector<int>>& grid, int i, int j, int& perimeter)
{
    grid[i][j] = -1;
    if (i == 0 || grid[i][j] == 0) perimeter++;
    if (i == grid.size()-1 || grid[i+1][j] == 0) perimeter++;
    if (j == 0 || grid[i][j-1] == 0) perimeter++;
    if (i == grid[0].size() - 1 || grid[i][j+1] == 0) perimeter++;

    if (i > 0 && grid[i - 1][j] == 1)dfs(grid, i - 1, j, perimeter);
    //if(i == )

}

int islandPerimeter(vector<vector<int>>& grid)
{
    int perimeter = 0;
    int r = grid.size(), c = grid[0].size();
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < r; j++)
        {
            if (grid[i][j] == 0)
                dfs(grid, i, j, perimeter);
        }
    }
    return perimeter;
}

int main()
{
    vector<vector<int>> grid{ {0, 1, 0, 0}, { 1, 1, 1, 0 }, { 0, 1, 0, 0 }, { 1,1,0,0 } };
    
    std::cout << islandPerimeter(grid) << "\n";
}

