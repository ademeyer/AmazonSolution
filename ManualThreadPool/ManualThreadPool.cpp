// ManualThreadPool.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <queue>
#include <functional>
#include <mutex>
#include <boost/asio.hpp>

using namespace std;

class ThreadPool
{
public:
    ThreadPool(size_t num_thread = thread::hardware_concurrency())
    {
        //cout << num_thread << "\n";
        for (size_t i = 0; i < num_thread; i++)
        {
            _threads.emplace_back([this] {
                while (true)
                {
                    // We need to bring task from queue and run it
                    function<void()> task;

                    {
                        // Grab mutex
                        unique_lock<mutex> lock(_queue_lock);
                        // check whether queue is empty or not
                        _update.wait(lock, [this] { return (!_tasks.empty() || _stop); });

                        // Even if we are asked to stop, wait till we completed all task before exiting
                        if (_stop && _tasks.empty()) return;

                        task = move(_tasks.front()); 
                        _tasks.pop();
                    }

                    task();

                }

                });
        }
    }
    ~ThreadPool()
    {
        {
            //Force a close-down
            unique_lock<mutex> lock(_queue_lock);
            _stop = true;
        }
        // Inform pending thread we are closing up
        _update.notify_all();

        for (auto& thd : _threads)
        {
            thd.join();
        }
    }

    void EnqueueTask(function<void()> task)
    {
        {
            unique_lock<mutex> lock(_queue_lock);
            _tasks.push(move(task));
        }
        _update.notify_one();
    }

private:
    vector<thread> _threads;
    queue<function<void()>> _tasks;
    bool _stop{ false };
    condition_variable _update;
    mutex _queue_lock;
};

int main()
{
    const int SIZE = 10;

    {
        ThreadPool pool(3);
        for (int i = 0; i < SIZE; i++)
        {
            pool.EnqueueTask([i] {
                cout << "Task: " << i << " is running on " << this_thread::get_id() << "\n";
                this_thread::sleep_for(chrono::seconds(5));
                });
        }
    }

    std::cout << "We are Done\n";

    return 0;
}

