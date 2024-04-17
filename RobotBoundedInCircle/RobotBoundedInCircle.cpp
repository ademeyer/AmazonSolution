// RobotBoundedInCircle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;

bool isRobotBounded(string instructions) 
{
    vector<vector<int>> dir = { {0,1}, {1,0}, {0,-1}, {-1,0} }; //==> North, East, South, West
    pair<int, int> temp;
    int k = 0;
    for (const auto c: instructions)
    {
        if (c == 'G')
        {
            temp.first += dir[k][0];
            temp.second += dir[k][1];
        }
        else
        {
            if (c == 'L')
                k = (k + 1) % 4;
            else
                k = ((k - 1) + 4) % 4;
        }
    }
    return (temp == pair<int, int>{0, 0} || k > 0);
}

int main()
{
    std::cout << (isRobotBounded("GGLLGG") ? "true":"false") << endl;
    std::cout << (isRobotBounded("GG") ? "true" : "false") << endl;
    std::cout << (isRobotBounded("GL") ? "true" : "false") << endl;
    std::cout << (isRobotBounded("GLRLLGLL") ? "true" : "false") << endl;
    std::cout << (isRobotBounded("GLRLGLLGLGRGLGL") ? "true" : "false") << endl;
    std::cout << (isRobotBounded("GGGGGGGRRRRRRRR") ? "true" : "false") << endl;
}
