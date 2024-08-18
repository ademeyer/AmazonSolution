// MaxSubArray.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

int maxSubArray(vector<int>& nums)
{
    int maxi = nums[0];
    int sum = 0;

    for (auto i : nums)
    {
        sum += i;
        maxi = max(maxi, sum);
        if (sum < 0) sum = 0;
    }
    return maxi;
}

int main()
{
    vector<int> nums{ -2,1,-3,4,-1,2,1,-5,4 };
    cout << "Maximum Sub array = " << maxSubArray(nums) << endl;

    vector<int> num1{ 5,4,-1,7,8 };
    cout << "Maximum Sub array = " << maxSubArray(num1) << endl;
}

