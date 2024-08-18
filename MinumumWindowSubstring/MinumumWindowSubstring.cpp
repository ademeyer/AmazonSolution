// MinumumWindowSubstring.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>

using namespace std;

string minWindow(string s, string t) // sliding window algorithm
{
    if (s.empty() || t.empty() || t.size() > s.size()) return "";

    unordered_map<char, int> Window;
    // create map for window and substring
    for (auto ch : t)
    {
        Window[ch]++;
    }
    int i = 0, j = 0;
    int count = Window.size();
    int minLength = s.size();
    int left = 0, right = minLength - 1;
    bool found = false;

    while (j < s.size())
    {
        char ch = s[j++];
        if (Window.find(ch) != Window.end())
        {
            Window[ch]--;
            if(Window[ch] == 0)
                count--;
        }
        if (count > 0) continue;

        while (count == 0)
        {
            char sch = s[i++];
            if (Window.find(sch) != Window.end())
            {
                Window[sch]++;
                if (Window[sch] > 0)
                    count++;
            }
        }
        if ((j - i) < minLength)
        {
            left = i;
            right = j;
            minLength = j - i;
            found = true;
        }
    }
    return found ? s.substr(left-1, right) : "";
}

int main()
{
    cout << minWindow("ADOBECODEBANC", "ABC") << endl;
    cout << minWindow("a", "a") << endl;
    cout << minWindow("a", "aa") << endl;
    cout << minWindow("aa", "aa") << endl;
    cout << minWindow("abc", "b") << endl;
    cout << minWindow("abcaasdsdaba", "aa") << endl;
}
