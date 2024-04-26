// FindMedianFromDataStream.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class MedianFinder
{
    priority_queue<int> MaxHeap; //Small buffer
    priority_queue<int, vector<int>, greater<int>> MinHeap; //Big Buffer
public:
    MedianFinder()
    {

    }

    void addNum(int num)
    {
        MaxHeap.push(num);
        MinHeap.push(MaxHeap.top());
        MaxHeap.pop();
        // checking size
        if (MaxHeap.size() < MinHeap.size())
        {
            MaxHeap.push(MinHeap.top());
            MinHeap.pop();
        }
    }

    double findMedian()
    {
        return ((MaxHeap.size() > MinHeap.size()) ? MaxHeap.top() : ((MaxHeap.top() + MinHeap.top())/2.0));
    }
};

int main()
{
    MedianFinder mf;
    mf.addNum(1);
    mf.addNum(2);
    cout << "Median: " << mf.findMedian() << "\n";
    mf.addNum(3);
    cout << "Median: " << mf.findMedian() << "\n";
    std::cout << "\nDone Testing\n";
}
