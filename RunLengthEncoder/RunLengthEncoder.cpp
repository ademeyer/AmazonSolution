// RunLengthEncoder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    string encode(const string& str)
    {
        if (str.empty()) return "";
        vector<pair<char, int>> enc;
        pair<char, int>cur{ str[0], 1 };

        for (int i = 1; i <= str.size(); ++i)
        {
            if (i < str.size())
            {
                if (cur.first == str[i])
                {
                    ++cur.second;
                    continue;
                }
            }

            enc.push_back(cur);

            if (i < str.size())
                cur = { str[i], 1 };
        }

        // make encoded string
        string res = "";
        for (const auto& e : enc)
            res += e.first + to_string(e.second);

        return res;
    }
};


int main(int argc, char* argv[])
{
    Solution s;
    string str = "abcccdeea"; //a1b1c3d1e2a1
    cout << s.encode(str) << endl;

    str = "abcaaaaaaaa"; //a1b1c1a8
    cout << s.encode(str) << endl;

    str = "aaaaaaaaaaaaaaaaa"; //a17
    cout << s.encode(str) << endl;

    str = "aaaaaaaaaaaaaaaaz"; //a16z1
    cout << s.encode(str) << endl;

    str = "aaaa"; //a4
    cout << s.encode(str) << endl;

    //return 0;
}