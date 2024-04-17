// FindTheIndexOfTheFirstOccurrenceInAString.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <vector>
#include <iostream>
using namespace std;

vector<int> getTable(string needle)
{
    int i = 1, j = 0;
    vector<int> PiTable(needle.size(), 0);
    while (i < needle.size())
    {
        if (needle[i] == needle[j])
        {
            j++;
            PiTable[i] = j;
            i++;
        }
        else
        {
            if (j != 0)
                j = PiTable[j - 1];
            else
            {
                PiTable[i] = 0;
                i++;
            }
        }
    }

    return PiTable;
}

int strStr(string haystack, string needle)
{
    if (needle.size() > haystack.size()) return -1;
    int i = 0, j = 0;
    auto ans = getTable(needle);

    while(haystack.size() - i >= needle.size() - j)
    {
        if (needle[j] == haystack[i])
        { 
            i++;
            j++;
        }
        if (j == needle.size())
        {
            return i - j;
            // j = ans[j-1];
        }
        // If mismatch occur after j matches
        else if(i < haystack.size() && needle[j] != haystack[i]) 
        {
            if (j != 0) 
                j = ans[j - 1];
            else
                i++;
        }        
    }

    return -1;
}


int main()
{
   auto ans = getTable("abcdabca");
    for(int k = 0; k < ans.size(); k++)
        std::cout << ans[k] << ",";
    cout << "\n";

    ans = getTable("AAACAAAA");
    for (int k = 0; k < ans.size(); k++)
        std::cout << ans[k] << ",";
    cout << "\n";

    ans = getTable("AAAA");
    for (int k = 0; k < ans.size(); k++)
        std::cout << ans[k] << ",";
    cout << "\n";

    ans = getTable("aabaabaaa");
    for (int k = 0; k < ans.size(); k++)
        std::cout << ans[k] << ",";
    cout << "\n";

    std::cout << strStr("sadbutsad", "sad") << "\n";
    std::cout << strStr("leetcode", "leeto") << "\n";
    std::cout << strStr("mississippi", "issip") << "\n";
    std::cout << strStr("mississippi", "issi") << "\n";

}
