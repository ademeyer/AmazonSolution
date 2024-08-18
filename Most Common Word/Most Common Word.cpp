// Most Common Word.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>
#include <sstream>
using namespace std;


class Solution
{
    string ToLower(string str)
    {
        string result;
        for (char& c : str)
            result += tolower(c);
        return result;
    }

public:
    void Print(const unordered_map<string, int>& wc)
    {
        for (auto n : wc)
        {
            cout << n.first << ": " << n.second << endl;
        }
    }
    string mostCommonWord(string paragraph, vector<string>& banned)
    {
        //! Normalize the string (replace non-alphanumeric characters, and make lower case  letters)
        for (int i = 0; i < paragraph.length(); ++i)
        {
            auto c = paragraph[i];
            if (!isalnum(c))
            {
                paragraph.replace(i, 1, " ");
            }
        }
        paragraph = ToLower(paragraph);
        //cout << paragraph << endl;
        //! Tally up every non-banned word
        unordered_map<string, int> wordCount;
        stringstream wordStream(paragraph);
        paragraph.clear();
        while (getline(wordStream, paragraph, ' '))
        {
            //cout << paragraph << endl;
            if (banned.end() == find(banned.begin(), banned.end(), paragraph) && paragraph != "")
                ++wordCount[paragraph];
        }
        //! Find the word with the max word count
        int maxCount = 0;
        string mostCommonWord;
        for (const auto& entry : wordCount)
        {
            if (entry.second > maxCount)
            {
                maxCount = entry.second;
                mostCommonWord = entry.first;
            }
        }
        //Print(wordCount);  // For debugging purposes to print the word count map.
        return mostCommonWord;
    }
};


int main()
{
    Solution sol;
    string paragraph = "Bob hit a ball, the hit BALL flew far after it was hit.";
    vector<string> banned = { "hit" };
    //cout << sol.mostCommonWord(paragraph, banned) << endl;

    paragraph = "a, a, a, a, b,b,b,c, c";
    banned = { "a" };
    cout << sol.mostCommonWord(paragraph, banned) << endl;

    return 0;
}