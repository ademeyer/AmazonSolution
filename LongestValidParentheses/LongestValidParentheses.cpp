// LongestValidParentheses.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stack>
#include <vector>
using namespace std;


int longestValidParentheses(string S)
{
    int ans = 0;
    stack<int> st;
    st.push(-1);

    for (int i = 0; i < S.size(); i++)
    {
        if (S[i] == '(')
        {
            st.push(i);
        }
        else
        {
            st.pop();
            if (st.empty())
                st.push(i);
            else
            {
                ans = max(ans, i - st.top());
            }
        }
    }
    return ans;
}

int main()
{
    cout << "Longest Parentheses: " << longestValidParentheses("(()") << endl;

    cout << "Longest Parentheses: " << longestValidParentheses(")()())") << endl;

    cout << "Longest Parentheses: " << longestValidParentheses("") << endl;

    return 0;
}