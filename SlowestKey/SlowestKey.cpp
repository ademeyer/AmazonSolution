// SlowestKey.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

char slowestKey(vector<int>& releaseTimes, string keysPressed)
{
    int Max = releaseTimes[0];
    char ch = keysPressed[0];

    int n = releaseTimes.size();

    for (int i = 1; i < n; i++)
    {
        int diff = releaseTimes[i] - releaseTimes[i - 1];
        if (diff > Max)
        {
            Max = diff;
            ch = keysPressed[i];
        }
        else if (diff == Max && keysPressed[i] > ch)
            ch = keysPressed[i];
    }

    return ch;
}
/*char slowestKey(vector<int>& releaseTimes, string keysPressed)
{
    priority_queue<pair<char, int>> pq;
    pq.push(pair<char, int>(keysPressed[0], releaseTimes[0]));
    for (int i = 1; i < releaseTimes.size(); i++)
    {
        pq.push(pair<char, int>(keysPressed[i], releaseTimes[i] - releaseTimes[i - 1]));
    }
    
    pair<char, int> res;

    while (!pq.empty())
    {
        cout << pq.top().first << ": " << pq.top().second << endl;
        res = pq.top();
        pq.pop();
        if (res.first != pq.top().first && res.second > pq.top().second || res.first > pq.top().first) break;

    }

    return res.first;
}*/

int main()
{
    vector<int> releaseTimes = {9, 29, 49, 50};
    std::cout << slowestKey(releaseTimes, "cbcd") << "\n";
    releaseTimes = { 12,23,36,46,62 };
    std::cout << slowestKey(releaseTimes, "spuda") << "\n";
    releaseTimes = { 23,34,43,59,62,80,83,92,97 };
    std::cout << slowestKey(releaseTimes, "qgkzzihfc") << "\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
