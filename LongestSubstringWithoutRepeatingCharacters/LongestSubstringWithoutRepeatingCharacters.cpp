// LongestSubstringWithoutRepeatingCharacters.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>
#include <queue>

using namespace std;

int lengthOfLongestSubstring(string s)
{
    unordered_map<char, int> cache;
    int n = s.size();
    int i = 0;
    int Size = 0;
    while (i < n)
    {
        for (int j = 0; j < n; j++)
        {
            if (cache.find(s[j]) == cache.end())
            {
                cache.insert(pair<char, int>{ s[j] , j + 1});
            }
            else
            {
                i = max(i, cache[s[j]]);
                cache[s[j]] = j + 1; 
            }
            Size = max(Size, j - i + 1);
        }
    }

    return Size;
}




int main()
{
    std::cout << lengthOfLongestSubstring("abcabcbb") << "\n";
    std::cout << lengthOfLongestSubstring("bbbbb") << "\n";
    std::cout << lengthOfLongestSubstring("pwwkew") << "\n";
    std::cout << lengthOfLongestSubstring("") << "\n";
    std::cout << lengthOfLongestSubstring(" ") << "\n";
    std::cout << lengthOfLongestSubstring("dvdf") << "\n";
    std::cout << lengthOfLongestSubstring("au") << "\n";
}
