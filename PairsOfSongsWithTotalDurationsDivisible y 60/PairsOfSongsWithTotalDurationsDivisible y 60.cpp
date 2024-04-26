// PairsOfSongsWithTotalDurationsDivisible y 60.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>
using namespace std;

int numPairsDivisibleBy60(vector<int>& time)
{
    int count = 0;
    unordered_map<int, int> mp;
    for (int i = 0; i < time.size(); i++)
    {
        long x = time[i];
        if (!(x % 60))
        {
            count += mp[0];
        }
        else
        {
            count += mp[(60 - (x % 60))];
        }

        mp[(x % 60)]++;
    }

    return count;
}

int main()
{
    vector<int> songlist{ 30,20,150,100,40 };  
    cout << numPairsDivisibleBy60(songlist) << "\n";
    songlist = { 60,60,60 };
    cout << numPairsDivisibleBy60(songlist) << "\n";
    std::cout << "\nDone Testing";
}
