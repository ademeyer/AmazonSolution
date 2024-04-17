// FizzBuzzMultithreaded.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <functional>
#include <atomic>
//#include <boost>
using namespace std;

class FizzBuzz {
private:
    int                 n;
    mutex               mtx;
    condition_variable  cv;
    int                 item = 1;
    
public:
    
    FizzBuzz(int n) {
        this->n = n;
    }
    
    /*
     * While item has not reached n, we wait until a condition is met. If the condition
     * is met, we execute a function and wake all the others waiting for a condition to 
     * be met.
     */
    #define CONSUMER(cond, fn) while (item <= n) {                          \
                                    unique_lock<mutex> lck(mtx);            \
                                    if (!(cond)) {                          \
                                        cv.wait(lck);                       \
                                        continue;                           \
                                    }                                       \
                                    fn; item++; cv.notify_all();            \
                                }   
    
    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) { 
        CONSUMER(!(item % 3) && (item % 5), printFizz()); 
    }
    
    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        CONSUMER((item % 3) && !(item % 5), printBuzz())
    }
    
    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        CONSUMER(!(item % 3) && !(item % 5), printFizzBuzz())
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        CONSUMER((item % 3) && (item % 5), printNumber(item));
    }
};

void PrintFizz()
{
    cout << "fizz, ";
}

void PrintBuzz()
{
    cout << "buzz, ";
}

void PrintFizzBuzz()
{
    cout << "fizzbuzz, ";
}

void PrintNumber(int x)
{
    cout << x << ", ";
}

int main()
{
    FizzBuzz F(20);

    thread TestNumber([&]{ 
        F.number(PrintNumber);
        });

    thread TestFizz([&] {
        F.fizz(PrintFizz);
        });

    thread TestBuzz([&] {
        F.buzz(PrintBuzz);
        });

    thread TestFizzBuzz([&] {
        F.fizzbuzz(PrintFizzBuzz);
        });


    if(TestFizz.joinable())
        TestFizz.join();
    if (TestBuzz.joinable())
        TestBuzz.join();
    if (TestFizzBuzz.joinable())
        TestFizzBuzz.join();
    if (TestNumber.joinable())
        TestNumber.join();

    std::cout << "Done All\n";
}
