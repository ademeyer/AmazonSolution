// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <numeric>
#include <vector>
using namespace std;



int solve(vector<int>nums, int mask, int countOfOp, vector<int>& dp, vector<vector<int>>& Gcd)
{
    int m = nums.size(), n = nums.size() / 2;
    if (countOfOp >= n)
    {
        return 0;
    }
    if (dp[mask] != -1)
        return dp[mask];
    int maxScore = 0;
    for (int i = 0; i < m; i++)
    {
        if (((mask >> i) & 1) == 1)
            continue;
        for (int j = i + 1; j < m; j++)
        {
            if (((mask >> j) & 1) == 1)
                continue;
            int newMask = mask | (1 << i) | (1 << j);
            int currScore = (countOfOp + 1) * Gcd[i][j];
            int remaingScore = solve(nums, newMask, countOfOp + 1, dp, Gcd);
            maxScore = max(maxScore, currScore + remaingScore);
        }
    }

    return dp[mask] = maxScore;
}

int maxScore(vector<int>& nums)
{
    int m = nums.size();
    int maxMaskValue = 1 << m; 
    vector<int>dp(maxMaskValue, -1);
    vector<vector<int>> Gcd(m, vector<int>(m, 0));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
            Gcd[i][j] = gcd(nums[i], nums[j]);
    }
    return solve(nums, 0, 0, dp, Gcd);
}

int main()
{
    vector<int> nums = {1, 2};
    std::cout << maxScore(nums) << "\n";
    nums = { 3, 4, 6, 8 };
    std::cout << maxScore(nums) << "\n";
    nums = { 1, 2, 3, 4, 5, 6 };
    std::cout << maxScore(nums) << "\n";
}