// AmazonOnlineAssessment1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int max_consecutive_states(uint32_t switchs_states, int state)
{
    int max_count = 0;
    int count = 0;
    uint32_t bitmask = 0x03;

    for (int i = 0; i < 16; ++i)
    {
        int now_state = (switchs_states >> (i * 2)) & bitmask;
        if (now_state == state)
        {
            ++count;
            if (count > max_count)
            {
                max_count = count;
            }
        }
        else
        {
            count = 0;
        }
    }

    return max_count;
}

int main()
{
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
