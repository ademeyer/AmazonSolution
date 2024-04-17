// BoundedBlockingQueue.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <queue>
#include <condition_variable>
#include <mutex>
#include <thread>

using namespace std;
class BoundedBlockingQueue
{
    int _capacity;
    int _count;
    queue<int> q;

    condition_variable notEmpty;
    condition_variable notFilled;

    mutex _mutex;

public:
    BoundedBlockingQueue(int capacity) : _capacity(capacity), _count(0)
    {
    }

    void enqueue(int element)
    {
        // Get Lock
        unique_lock<mutex> lock(_mutex);

        // Wait for free space
        notFilled.wait(lock, [&] { return _count < _capacity; });

        // Insert the element
        q.push(element);
        _count++;

        // Notify not empty
        notEmpty.notify_one();
    }

    int dequeue()
    {
        // Get Lock
        unique_lock<mutex> lock(_mutex);
        // Wait for free space
        notEmpty.wait(lock, [&] { return _count > 0; });

        int val = q.front();
        q.pop();
        _count--;

        notFilled.notify_one();
        return val;
    }

    int size()
    {
        lock_guard<mutex> lock(_mutex);
        return _count;
    }
};


int main()
{
    const int SIZE = 100;
    BoundedBlockingQueue Q(SIZE);

    thread RemoveFromQueue([&] {
        for (int i = 0; i < SIZE; i++)
        {
            cout << Q.dequeue() << "\n";
        }
        });

    thread InsertToQueue( [&]{
        for (int i = 0; i < SIZE; i++)
        {
            cout << "Inserting " << i << "\n";
            Q.enqueue(i);
        }
        } );


    InsertToQueue.join();
    RemoveFromQueue.join();

    std::cout << "DONE!!!\n";
}