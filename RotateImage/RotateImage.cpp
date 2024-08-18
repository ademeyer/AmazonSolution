// RotateImage.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

// Brute force approach

void rotateImg(vector<vector<int>>& matrix)
{
    int row = matrix.size();

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            swap(matrix[i][j], matrix[j][i]);
        }
    }

    for (int i = 0; i < row; i++)
        reverse(matrix[i].begin(), matrix[i].end());
}

void printresult(vector<vector<int>>& matrix)
{
    cout << "{ ";
    for (auto vec : matrix)
    {
        cout << "{ ";
        for (auto v : vec)
        {
            cout << v << ", ";
        }
        cout << "}, ";
    }
    cout << " }" << endl;
}

int main()
{
    vector<vector<int>> matrix = { {1,2,3}, {4,5,6}, {7,8,9} };
    rotateImg(matrix);
    printresult(matrix);

    matrix = { {5,1,9,11}, {2,4,8,10}, {13,3,6,7}, {15,14,12,16} };
    rotateImg(matrix);
    printresult(matrix);
    std::cout << "\n";
}

