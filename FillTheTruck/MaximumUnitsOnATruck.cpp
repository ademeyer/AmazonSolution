// FillTheTruck.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int maximumUnits(vector<vector<int>>& boxTypes, int truckSize)
{
    sort(boxTypes.begin(), boxTypes.end(), [](const auto& a, const auto& b) { return a[1] > b[1]; });

    int totalUnits = 0;

    for (const auto& boxType : boxTypes)
    {
        int numberOfBoxes = boxType[0];
        int unitsPerBox = boxType[1];

        int boxesToTake = min(truckSize, numberOfBoxes);

        totalUnits += unitsPerBox * boxesToTake;

        truckSize -= boxesToTake;

        if (truckSize <= 0) break;
    }

    return totalUnits;
}

int main()
{
    vector<vector<int>> boxTypes = { {1,3}, {2,2}, {3,1} };
    std::cout << maximumUnits(boxTypes, 4) << "\n";
    boxTypes = { {5,10}, {2,5}, {4,7}, {3,9} };
    std::cout << maximumUnits(boxTypes, 10) << "\n";
}