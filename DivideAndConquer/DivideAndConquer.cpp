// DivideAndConquer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

// using recursion to find max element of an array

int MaxRecursive(vector<int> arr, int arrSize)
{
    if (arrSize == 1)
    {
        return arr[0];
    }
    else
    {
        int max = MaxRecursive(arr, arrSize-1);
        if (max > arr[arrSize - 1])
            return max;
        else
            return arr[arrSize - 1];
    }
}

int MaxDivideAndConquer(vector<int>arr, int start, int end)
{
    if (start == end)
        return arr[start];
    else
    {
        int half = (start + end) / 2;
        int left = MaxDivideAndConquer(arr, start, half);
        int right = MaxDivideAndConquer(arr, half+1, end);
        if (left > right)
            return left;
        else
            return right;
    }
}

void merge(vector<int>& arr, int l, int mid, int r)
{
    vector<int> temp = arr;
    int i = l, j = mid+1, k = l;
    while (i <= mid && j <= r)
    {
        if (temp[i] <= temp[j])
        {
            arr[k++] = temp[i];
            i++;
        }
        else
        {
            arr[k++] = temp[j];
            j++;
        }
    }
    while (i <= mid)
    {
        arr[k++] = temp[i];
        i++;
    }
    while (j <= r)
    {
        arr[k++] = temp[j];
        j++;
    }
}

void mergesort(vector<int>& arr, int l, int r)
{
    if (l < r)
    {
        int mid = (l + r) / 2;
        mergesort(arr, l, mid);
        mergesort(arr, mid+1, r);
        merge(arr, l, mid, r);
    }
}

void mergesort(vector<int>& arr)
{
    mergesort(arr, 0, (arr.size()-1));
}

int main()
{
    vector<int> arr{ 2, 21, 17, 12, 19, 1, 2, 6, 9, 10, 23, 32, 14, 16, 15 };
    cout << "Find Max value recursively: " << MaxRecursive(arr, arr.size()) << endl;
    cout << "Find Max value with divideAndConquer: " << MaxDivideAndConquer(arr, 0, arr.size()-1) << endl;
    mergesort(arr);
    for (auto i : arr)
        cout << i << ", ";
    std::cout << "\n";
}

