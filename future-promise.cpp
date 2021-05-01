/*
    Promise and Future ( <future>, std::future, std::promise )

    std::promise
        - Used to set values or exceptions

    std::promise
        - Used to get values from promise
        - Ask promise if value is available, and waits for the promise's response

*/

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <future>
using namespace std;
using namespace chrono;
typedef long int ull;

void findOdd(std::promise<ull> OddSumPromise, ull start, ull end)
{
    ull OddSum = 0;
    for (ull i = start; i <= end; i++)
    {
        if (i & 1)
        {
            OddSum += 1;
        }
    }
    OddSumPromise.set_value(OddSum);
}

int main()
{
    ull start = 0, end = 190000000;

    // Create promise object
    std::promise<ull> OddSum;
    // Create future from the promise
    std::future<ull> OddFuture = OddSum.get_future();

    cout << "Thread Created!" << endl;

    // Send the promise to the thread
    thread t1(findOdd, std::move(OddSum), start, end);

    cout << "Waiting for Result..." << endl;

    // Wait until promise fulfilled
    cout << "Odd Sum: " << OddFuture.get() << endl;

    cout << "Completed!" << endl;
    t1.join();

    return 0;
}