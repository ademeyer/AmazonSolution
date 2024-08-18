// AmazonOnlineAssessment2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>
#include <string>

#define NUM_MAX_STR_SIZE 32

using namespace std;

typedef enum {
    STATUS_SUCCESS,
    STATUS_INVALID,
    STATUS_DIVIDE_BY_ZERO
} FuncStatus_t;


using namespace std;
FuncStatus_t evaluatePostfix(const size_t postfix_size, const char* postfix[], int32_t* result)
{
    // /* Warning: You can use stdout for debugging, but doing so will cause the test cases to fail. */
    stack<int32_t> st;

    for (size_t i = 0; i < postfix_size; ++i)
    {
        string t = postfix[i];

        if (isdigit(t[0]) || (t[0] == '-' && isdigit(t[1])))
        {
            st.push(stoi(t));
        }
        else if (t == "+" || t == "-" || t == "*" || t == "/")
        {
            if (st.size() < 2)
                return STATUS_INVALID;


            // check inside stack
            int32_t b = st.top(); st.pop();
            int32_t a = st.top(); st.pop();

            int32_t result;

            if (t == "+")
                result = a + b;
            else if (t == "-")
                result = a - b;
            else if (t == "*")
                result = a * b;
            else if (t == "/")
            {
                if (b == 0)
                    return STATUS_DIVIDE_BY_ZERO;
                result = a / b;
            }

            st.push(result);
        }
        else
        {
            return STATUS_INVALID;
        }
    }

    if (st.size() != 1)
        return STATUS_INVALID;

    *result = st.top();
    return STATUS_SUCCESS;
}

int main()
{
    std::cout << "Hello World!\n";
}

