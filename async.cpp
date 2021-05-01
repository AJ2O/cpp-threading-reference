/*
    Async ( std::async )
        - runs a function asynchronously (potentially in a new thread) and
          returns a std::future object that holds the result

    Launch Policies for creating tasks
        - a. std::launch::async
            - Immediately creates and starts a task

        - b. std::launch::deferred
            - Doesn't immediately create a task, but creates an entry for a task
              to be held for a later time
            - The actual task is created when we want to return a value from
              the future

        - c. std::launch::async | std::launch::deferred


*/

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <algorithm>
#include <future>
using namespace std;
using namespace chrono;
typedef long int ull;

ull findOdd(ull start, ull end)
{
    ull OddSum = 0;
    cout << "ThreadID of Main: " << this_thread::get_id() << endl;
    for (ull i = start; i <= end; i++)
    {
        if (i & 1)
        {
            OddSum += 1;
        }
    }
    return OddSum;
}

int main()
{
    ull start = 0, end = 190000000;

    // Create promise object
    cout << "ThreadID of FindOdd: " << this_thread::get_id() << endl;
    cout << "Thread Created if policy is std::launch::async!" << endl;
    std::future<ull> OddSum = std::async(std::launch::async, findOdd, start, end);

    cout << "Waiting for Result..." << endl;

    // Wait until promise fulfilled
    cout << "Odd Sum: " << OddSum.get() << endl;

    cout << "Completed!" << endl;
    return 0;
}
