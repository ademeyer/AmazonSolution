// FibonacciSequenceByDP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

unsigned long Fib_2(int n) // bottom-up approach
{
    if (n == 1 || n == 2)
        return 1;
    vector<unsigned long>bottomup(n+1);
    bottomup[1] = 1;
    bottomup[2] = 1;
    for (int i = 3; i <= n; i++)
    {
        bottomup[i] = bottomup[i - 1] + bottomup[i - 2];
    }

    return bottomup[n];
}

unsigned long Fib_1(int n, vector<unsigned long>& memo) // Momoized approach
{
    unsigned long result = 0;
    if (memo[n] != -1)
        return memo[n];
    if (n == 1 || n == 2)
        result = 1;
    else
    {
        result = Fib_1(n - 1, memo) + Fib_1(n - 2, memo);
        memo[n] = result;
    }

    return result;
}

unsigned long Fib_1(int n) // Memoize
{
    vector<unsigned long> memo(n + 1, -1);
    return Fib_1(n, memo);
}

unsigned long Fib(int n) // recurse
{
    int result = 0;
    if (n == 1 || n == 2)
        return 1;
    else
    {
        result = Fib(n - 1) + Fib(n - 2);
    }

    return result;
}

int main()
{
    //cout << "Fib: " << Fib(100) << endl;

    //cout << "Fib_1: " << Fib_1(10000) << endl;

    cout << "Fib_2: " << Fib_2(10000) << endl;
}
