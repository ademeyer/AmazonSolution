// FindTheIndexOfTheFirstOccurrenceInAString.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <vector>
#include <iostream>
using namespace std;
/*
    const int m = haystack.length();
    const int n = needle.length();

    for (int i = 0; i < m - n + 1; i++)
      if (haystack.substr(i, n) == needle)
        return i;

*/

vector<int> getTable(string needle)
{
    int i = 0, j = 0;
    vector<int> PiTable(needle.size(), 0);
    for (i = 1; i < needle.size(); i++)
    {
        if (needle[i] == needle[j])
        {
            PiTable[i] = ++j;
        }
        else //if (j > 0)
        {
            while(j > 0 && needle[i] != needle[j])
                j = PiTable[j - 1];
        }

    }
    PiTable[i-1] = ++j;

    return PiTable;
}

int strStr(string haystack, string needle)
{
    if (needle.size() > haystack.size()) return -1;
    int index = -1, track = 0, i = 0;
    auto ans = getTable(needle);

    while(i < haystack.size()) //for (int i = 0; i < haystack.size(); i++)
    {

        if (needle[track] != haystack[i])
        {
            if (track > 0)
                track = ans[track - 1];
            else 
                i++;
            index = -1;
            //continue;
        }
        else
        {
            ++track;
            if (index == -1) index = i;
            if (track == needle.size()) return index;
            i++;
        }

        
    }

    return -1;
}


int main()
{
   /* auto ans = getTable("abcdabca");
    for(int k = 0; k < ans.size(); k++)
        std::cout << ans[k] << ",";
    cout << "\n";

    ans = getTable("aabaabaaa");
    for (int k = 0; k < ans.size(); k++)
        std::cout << ans[k] << ",";
    cout << "\n";

    std::cout << strStr("sadbutsad", "sad") << "\n";
    std::cout << strStr("leetcode", "leeto") << "\n";
    std::cout << strStr("mississippi", "issip") << "\n";
    std::cout << strStr("mississippi", "issi") << "\n";*/

    const int data = 234;

    const int* ptr = &data;

    cout << "*ptr = " << *ptr << "\n";
    *ptr++;
    cout << "*ptr = " << *ptr << "\n";

}
