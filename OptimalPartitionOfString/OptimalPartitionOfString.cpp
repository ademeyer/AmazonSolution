// OptimalPartitionOfString.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;

/*int partitionString(string s) {
    int counter = 1;
    int occurrenceBits = 0;

    for (const char& ch : s) {
        int charPositionBit = 1 << (ch - 'a');

        if (occurrenceBits & charPositionBit) {
            ++counter;
            occurrenceBits = 0;
        }

        occurrenceBits |= charPositionBit;
    }

    return counter;
}*/


int partitionString(string s)
{
    vector<string> sub;
    string temp;
    
    for (size_t i = 0; i < s.size(); i++)
    {
        if (temp.find(s[i]) != string::npos)
        {
            sub.push_back(temp);
            temp.clear();
        }

        temp += s[i];        
    }
    sub.push_back(temp);

    return sub.size();
}

int main()
{
    std::cout << partitionString("abacaba") << "\n";
    std::cout << partitionString("ssssss") << "\n";
    std::cout << partitionString("kakkakakak") << "\n";
}
