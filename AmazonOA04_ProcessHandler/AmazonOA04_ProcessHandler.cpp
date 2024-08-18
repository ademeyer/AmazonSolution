/*
Suppose we have 2 processes:
 - A which generates events and
 - B which processes the events.
 Process A has higher priority than B,
    if task A generates too many events
    exceeding certain limit, the system should
    start dropping old event and keep only last
    N events available for B to process.
 Your task is to implement the data structure needed
    to fulfill the requirements and write
    sample application code for both tasks A & B.

 We have limit
 Thread safety optional
*/

#include <iostream>
#include <vector>
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <string>

using namespace std;

template<typename T>
class CircularBuffer
{
    vector<T> _buffer;
    int head;
    int tail;
    int count;
    const int capacity;
    mutex _mutex;
    condition_variable _update;

public:
    CircularBuffer(const int size) : capacity(size), _buffer(vector<T>(size)), count(0), head(0), tail(0){}
    ~CircularBuffer(){}

    void Insert(const T& item)
    {
        const lock_guard<mutex> lock(_mutex);
        _buffer[tail] = item;
        tail = (tail + 1) % capacity;
        if (count == capacity)
        {
            head = (head + 1) % capacity; // overwrite old item
        }
        else
        {
            ++count;
        }
        _update.notify_one();
    }

    bool Remove(T& item)
    {
        unique_lock<mutex> lock(_mutex);
        _update.wait(lock, [this] { return count > 0; });

        if (count > 0)
        {
            item = _buffer[head];
            head = (head + 1) % capacity;
            --count;
            return true;
        }
        return false;
    }
};

struct Events
{
    string ID;
    string msg;
    Events(const string _id, const string _msg) :
        ID(_id), msg(_msg) {}
};

class ProcessHandler
{
    CircularBuffer<Events*> events;
    int id_count;
    int MAX_EVENT;
    void printEvent(Events* e)
    {
        cout << e->ID << ": " << e->msg << endl;
    }
    string IDGenerator()
    {
        string IDstr = "ID" + to_string(id_count);
        ++id_count;
        if (id_count == INT_MAX)
            id_count = 0;
        return IDstr;
    }
public:
    ProcessHandler(const int buffer_size, int max) : MAX_EVENT(max), events(buffer_size), id_count(0) {}
    ~ProcessHandler(){}

    // Process A
    void EventsGenerator()
    {
        // Generate events
        while(true)
        {
            Events* newEvents = new Events(IDGenerator(), "Event messages");
            // Add to queue+
            events.Insert(newEvents);
            this_thread::sleep_for(chrono::milliseconds(80));
            --MAX_EVENT;
            if (MAX_EVENT == 0) break;
        }
    }
    // Process B
    void EventsProcessor()
    {
        bool status = true;
        Events* e = NULL;
        while (status)
        {                            
            status = events.Remove(e);
            
            if (status)
                printEvent(e);

            this_thread::sleep_for(chrono::milliseconds(110));
        } 
    }
};

int main()
{
    int events = 500;
    ProcessHandler P(20, events);

    thread taskA([&] {
            P.EventsGenerator();
    });

    thread taskB([&] {
            P.EventsProcessor();
    });

    taskA.join();
    taskB.detach();

    cout << "\n\nTest Completed\n";
}
